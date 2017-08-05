/*
 * fsm.c - {Link, IP} Control Protocol Finite State Machine.
 *
 * Copyright (c) 1989 Carnegie Mellon University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Carnegie Mellon University.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */


/*
 * TODO:
 * Randomize fsm id on link/init.
 * Deal with variable outgoing MTU.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "pppd.h"
#include "fsm.h"
#include "atplog.h"

static const char rcsid[] = RCSID;

static void fsm_timeout __P((void *));
static void fsm_rconfreq __P((fsm *, int, u_char *, int));
static void fsm_rconfack __P((fsm *, int, u_char *, int));
static void fsm_rconfnakrej __P((fsm *, int, int, u_char *, int));
static void fsm_rtermreq __P((fsm *, int, u_char *, int));
static void fsm_rtermack __P((fsm *));
static void fsm_rcoderej __P((fsm *, u_char *, int));
static void fsm_sconfreq __P((fsm *, int));

#define PROTO_NAME(f)	((f)->callbacks->proto_name)

int peer_mru[NUM_PPP];

/*
 * fsm_init - Initialize fsm.
 *
 * Initialize fsm state.
 */
void
fsm_init(f)
    fsm *f;
{
    f->state = INITIAL;
    f->flags = 0;
#ifdef SUPPORT_ATP_EUAP	
    f->flags |= OPT_RESTART;
#endif	
    f->id = 0;				/* XXX Start with random id? */
    f->timeouttime = DEFTIMEOUT;

#ifdef SUPPORT_TD_CARD
    if ( 3 == dial_protocol )
    {
        /*HSPA??*/
        f->maxconfreqtransmits = USBMAXCONFREQS;
    }
    else
#endif
    {
        f->maxconfreqtransmits = DEFMAXCONFREQS;
    }
    f->maxtermtransmits = DEFMAXTERMREQS;
    f->maxnakloops = DEFMAXNAKLOOPS;
    f->term_reason_len = 0;
}


/*
 * fsm_lowerup - The lower layer is up.
 */
void
fsm_lowerup(f)
    fsm *f;
{
    switch( f->state ){
    case INITIAL:
	f->state = CLOSED;
	break;

    case STARTING:
	if( f->flags & OPT_SILENT )
	    f->state = STOPPED;
	else {
	    /* Send an initial configure-request */
	    fsm_sconfreq(f, 0);
	    f->state = REQSENT;
	}
	break;

    default:
	FSMDEBUG(("%s: Up event in state %d!", PROTO_NAME(f), f->state));
    }
}


/*
 * fsm_lowerdown - The lower layer is down.
 *
 * Cancel all timeouts and inform upper layers.
 */
void
fsm_lowerdown(f)
    fsm *f;
{
    switch( f->state ){
    case CLOSED:
	f->state = INITIAL;
	break;

    case STOPPED:
	f->state = STARTING;
	if( f->callbacks->starting )
	    (*f->callbacks->starting)(f);
	break;

    case CLOSING:
	f->state = INITIAL;
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	break;

    case STOPPING:
    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
	f->state = STARTING;
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	break;

    case OPENED:
	if( f->callbacks->down )
	    (*f->callbacks->down)(f);
	f->state = STARTING;
	break;

    default:
	FSMDEBUG(("%s: Down event in state %d!", PROTO_NAME(f), f->state));
    }
}


/*
 * fsm_open - Link is allowed to come up.
 */
void
fsm_open(f)
    fsm *f;
{
    switch( f->state ){
    case INITIAL:
	f->state = STARTING;
	if( f->callbacks->starting )
	    (*f->callbacks->starting)(f);
	break;

    case CLOSED:
	if( f->flags & OPT_SILENT )
	    f->state = STOPPED;
	else {
	    /* Send an initial configure-request */
	    fsm_sconfreq(f, 0);
	    f->state = REQSENT;
	}
	break;

    case CLOSING:
	f->state = STOPPING;
	/* fall through */
    case STOPPED:
    case OPENED:
	if( f->flags & OPT_RESTART ){
	    fsm_lowerdown(f);
	    fsm_lowerup(f);
	}
	break;
    }
}

/*
 * terminate_layer - Start process of shutting down the FSM
 *
 * Cancel any timeout running, notify upper layers we're done, and
 * send a terminate-request message as configured.
 */
static void
terminate_layer(f, nextstate)
    fsm *f;
    int nextstate;
{
    if( f->state != OPENED )
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
    else if( f->callbacks->down )
	(*f->callbacks->down)(f);	/* Inform upper layers we're down */

    /* Init restart counter and send Terminate-Request */
    f->retransmits = f->maxtermtransmits;

    if(PPP_IPCP == f->protocol)
    {
        //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Termination Request");
        ppp_log("PPP IPCP Send Termination Request");
    }
    else if (PPP_LCP == f->protocol)
    {
        //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Termination Request");
        ppp_log("PPP LCP Send Termination Request");

    }

    fsm_sdata(f, TERMREQ, f->reqid = ++f->id,
	      (u_char *) f->term_reason, f->term_reason_len);

    if (f->retransmits == 0) {
	/*
	 * User asked for no terminate requests at all; just close it.
	 * We've already fired off one Terminate-Request just to be nice
	 * to the peer, but we're not going to wait for a reply.
	 */
	f->state = nextstate == CLOSING ? CLOSED : STOPPED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	return;
    }

    TIMEOUT(fsm_timeout, f, f->timeouttime);
    --f->retransmits;

    f->state = nextstate;
}

/*
 * fsm_close - Start closing connection.
 *
 * Cancel timeouts and either initiate close or possibly go directly to
 * the CLOSED state.
 */
void
fsm_close(f, reason)
    fsm *f;
    char *reason;
{
    f->term_reason = reason;
    f->term_reason_len = (reason == NULL? 0: strlen(reason));
    switch( f->state ){
    case STARTING:
	f->state = INITIAL;
	break;
    case STOPPED:
	f->state = CLOSED;
	break;
    case STOPPING:
	f->state = CLOSING;
	break;

    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
    case OPENED:
	terminate_layer(f, CLOSING);
	break;
    }
}


/*
 * fsm_timeout - Timeout expired.
 */
static void
fsm_timeout(arg)
    void *arg;
{
    fsm *f = (fsm *) arg;

    switch (f->state) {
    case CLOSING:
    case STOPPING:
        if( f->retransmits <= 0 ){
            /*
             * We've waited for an ack long enough.  Peer probably heard us.
             */
            pppoe_setlasterror("ERROR_ISP_TIME_OUT");
            f->state = (f->state == CLOSING)? CLOSED: STOPPED;
            if( f->callbacks->finished )
            (*f->callbacks->finished)(f);
        } else {
            /* Send Terminate-Request */

            if (PPP_IPCP == f->protocol)
            {
                        //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Termination Request");
                        ppp_log("PPP IPCP Send Termination Request");
            }
            else if (PPP_LCP == f->protocol)
            {
                        //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Termination Request");
                        ppp_log("PPP LCP Send Termination Request");
            }

            fsm_sdata(f, TERMREQ, f->reqid = ++f->id,
                  (u_char *) f->term_reason, f->term_reason_len);
            TIMEOUT(fsm_timeout, f, f->timeouttime);
            --f->retransmits;
        }
        break;

    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
#if defined(SUPPORT_ATP_IPV6_PPP_DIAL_ON_DEMAND) && defined(SUPPORT_ATP_PPPC6)
        if (f->retransmits <= 0 && (PPP_IPCP != f->protocol) && (PPP_IPV6CP != f->protocol)) {
#else
        if (f->retransmits <= 0) {
#endif
            ppp_log("%s: timeout sending Config-Requests\n", PROTO_NAME(f));
            warn("%s: timeout sending Config-Requests\n", PROTO_NAME(f));
            f->state = STOPPED;
            if( (f->flags & OPT_PASSIVE) == 0 && f->callbacks->finished )
                (*f->callbacks->finished)(f);
        } else {
            ppp_log("%s: LCP IPCP config no reply\n", PROTO_NAME(f));
            /* Retransmit the configure-request */
            if (f->callbacks->retransmit)
            (*f->callbacks->retransmit)(f);
            fsm_sconfreq(f, 1);		/* Re-send Configure-Request */
            if( f->state == ACKRCVD )
            f->state = REQSENT;
        }
        break;

        default:
    	FSMDEBUG(("%s: Timeout event in state %d!", PROTO_NAME(f), f->state));
    }
}


/*
 * fsm_input - Input packet.
 */
void
fsm_input(f, inpacket, l)
    fsm *f;
    u_char *inpacket;
    int l;
{
    u_char *inp;
    u_char code, id;
    int len;

    /*
     * Parse header (code, id and length).
     * If packet too short, drop it.
     */
    inp = inpacket;
    if (l < HEADERLEN) {
	FSMDEBUG(("fsm_input(%x): Rcvd short header.", f->protocol));
	return;
    }
    GETCHAR(code, inp);
    GETCHAR(id, inp);
    GETSHORT(len, inp);
    if (len < HEADERLEN) {
	FSMDEBUG(("fsm_input(%x): Rcvd illegal length.", f->protocol));
	return;
    }
    if (len > l) {
	FSMDEBUG(("fsm_input(%x): Rcvd short packet.", f->protocol));
	return;
    }
    len -= HEADERLEN;		/* subtract header length */

    if( f->state == INITIAL || f->state == STARTING ){
	FSMDEBUG(("fsm_input(%x): Rcvd packet in state %d.",
		  f->protocol, f->state));
	return;
    }

    /*
     * Action depends on code.
     */
    switch (code) {
    case CONFREQ:

        if (PPP_IPCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Receive Configuration Request");
                ppp_log("PPP IPCP Receive Configuration Request");
        }
        else if (PPP_LCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Receive Configuration Request");
                ppp_log("PPP LCP Receive Configuration Request");
        }

	fsm_rconfreq(f, id, inp, len);
	break;
    
    case CONFACK:

        if (PPP_IPCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Receive Configuration ACK");
                ppp_log("PPP IPCP Receive Configuration ACK");
        }
        else if (PPP_LCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Receive Configuration ACK");
                ppp_log("PPP LCP Receive Configuration ACK");
        }

	fsm_rconfack(f, id, inp, len);
	break;
    
    case CONFNAK:

        if (PPP_IPCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Receive Configuration NAK");
                ppp_log("PPP IPCP Receive Configuration NAK");
        }
        else if (PPP_LCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Receive Configuration NAK");
                ppp_log("PPP LCP Receive Configuration NAK");
        }

    case CONFREJ:

        if (PPP_IPCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Receive Configuration Reject");
                ppp_log("PPP IPCP Receive Configuration Reject");
        }
        else if (PPP_LCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Receive Configuration Reject");
                ppp_log("PPP LCP Receive Configuration Reject");
        }

	fsm_rconfnakrej(f, code, id, inp, len);
	break;
    
    case TERMREQ:

        if (PPP_IPCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Receive Termination Request");
                ppp_log("PPP IPCP Receive Termination Request");
        }
        else if (PPP_LCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Receive Termination Request");
                ppp_log("PPP LCP Receive Termination Request");
        }

    pppoe_setlasterror("ERROR_ISP_DISCONNECT");
	fsm_rtermreq(f, id, inp, len);
	break;
    
    case TERMACK:

        if (PPP_IPCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Receive Termination ACK");
                ppp_log("PPP IPCP Receive Termination ACK");
        }
        else if (PPP_LCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Receive Termination ACK");
                ppp_log("PPP LCP Receive Termination ACK");
        }

    	fsm_rtermack(f);
    	break;
    
    case CODEREJ:

        if (PPP_IPCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Receive Code Reject");
                ppp_log("PPP IPCP Receive Code Reject");
        }
        else if (PPP_LCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Receive Code Reject");
                ppp_log("PPP LCP Receive Code Reject");
        }

    	fsm_rcoderej(f, inp, len);
    	break;
    
    default:
	if( !f->callbacks->extcode
	   || !(*f->callbacks->extcode)(f, code, id, inp, len) )
	    fsm_sdata(f, CODEREJ, ++f->id, inpacket, len + HEADERLEN);
	break;
    }
}


/*
 * fsm_rconfreq - Receive Configure-Request.
 */
static void
fsm_rconfreq(f, id, inp, len)
    fsm *f;
    u_char id;
    u_char *inp;
    int len;
{
    int code, reject_if_disagree;

    switch( f->state ){
    case CLOSED:
    	/* Go away, we're closed */

        if (PPP_IPCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Termination ACK");
                ppp_log("PPP IPCP Send Termination ACK");
        }
        else if (PPP_LCP == f->protocol)
        {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Termination ACK");
                ppp_log("PPP LCP Send Termination ACK");
        }

    	fsm_sdata(f, TERMACK, id, NULL, 0);
    	return;
    case CLOSING:
    case STOPPING:
	return;

    case OPENED:
	/* Go down and restart negotiation */
	if( f->callbacks->down )
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	fsm_sconfreq(f, 0);		/* Send initial Configure-Request */
	f->state = REQSENT;
	break;

    case STOPPED:
	/* Negotiation started by our peer */
	fsm_sconfreq(f, 0);		/* Send initial Configure-Request */
	f->state = REQSENT;
	break;
    }

    /*
     * Pass the requested configuration options
     * to protocol-specific code for checking.
     */
    if (f->callbacks->reqci){		/* Check CI */
	reject_if_disagree = (f->nakloops >= f->maxnakloops);
	code = (*f->callbacks->reqci)(f, inp, &len, reject_if_disagree);
    } else if (len)
	code = CONFREJ;			/* Reject all CI */
    else
	code = CONFACK;

    switch (code)
    {
        case CONFREQ:
            if (PPP_IPCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Configuration Request");
                ppp_log("PPP IPCP Send Configuration Request");
            }
            else if (PPP_LCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Configuration Request");
                ppp_log("PPP LCP Send Configuration Request");
            }
            break;
            
        case CONFACK:
            if (PPP_IPCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Configuration ACK");
                ppp_log("PPP IPCP Send Configuration ACK");
            }
            else if (PPP_LCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Configuration ACK");
                ppp_log("PPP LCP Send Configuration ACK");
            }
            break;

       case CONFNAK:
            if (PPP_IPCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Configuration NAK");
                ppp_log("PPP IPCP Send Configuration NAK");
            }
            else if (PPP_LCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Configuration NAK");
                ppp_log("PPP LCP Send Configuration NAK");
            }
            break;

       case CONFREJ:
            if (PPP_IPCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Configuration Reject");
                ppp_log("PPP IPCP Send Configuration Reject");
            }
            else if (PPP_LCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Configuration Reject");
                ppp_log("PPP LCP Send Configuration Reject");
            }
            break;

        case TERMREQ:
            if (PPP_IPCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Termination Request");
                ppp_log("PPP IPCP Send Termination Request");
            }
            else if (PPP_LCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Termination Request");
                ppp_log("PPP LCP Send Termination Request");
            }
            break;

        case TERMACK:
            if (PPP_IPCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Termination Ack");
                ppp_log("PPP IPCP Send Termination Ack");
            }
            else if (PPP_LCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Termination Ack");
                ppp_log("PPP LCP Send Termination Ack");
            }
            break;

        case CODEREJ:
            if (PPP_IPCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Code Reject");
                ppp_log("PPP IPCP Send Code Reject");
            }
            else if (PPP_LCP == f->protocol)
            {
                //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Code Reject");
                ppp_log("PPP LCP Send Code Reject");
            }
            break;

        default:
            break;
    }

    /* send the Ack, Nak or Rej to the peer */
    fsm_sdata(f, code, id, inp, len);

    if (code == CONFACK) {
	if (f->state == ACKRCVD) {
	    UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	    f->state = OPENED;
	    if (f->callbacks->up)
		(*f->callbacks->up)(f);	/* Inform upper layers */
	} else
	    f->state = ACKSENT;
	f->nakloops = 0;

    } else {
	/* we sent CONFACK or CONFREJ */
	if (f->state != ACKRCVD)
	    f->state = REQSENT;
	if( code == CONFNAK )
	    ++f->nakloops;
    }
}


/*
 * fsm_rconfack - Receive Configure-Ack.
 */
static void
fsm_rconfack(f, id, inp, len)
    fsm *f;
    int id;
    u_char *inp;
    int len;
{
    if (id != f->reqid || f->seen_ack)		/* Expected id? */
	return;					/* Nope, toss... */
    if( !(f->callbacks->ackci? (*f->callbacks->ackci)(f, inp, len):
	  (len == 0)) ){
	/* Ack is bad - ignore it */
	error("Received bad configure-ack: %P", inp, len);
	return;
    }
    f->seen_ack = 1;

    switch (f->state) {
    case CLOSED:
    case STOPPED:
	fsm_sdata(f, TERMACK, id, NULL, 0);
	break;

    case REQSENT:
	f->state = ACKRCVD;
	f->retransmits = f->maxconfreqtransmits;
	break;

    case ACKRCVD:
	/* Huh? an extra valid Ack? oh well... */
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	fsm_sconfreq(f, 0);
	f->state = REQSENT;
	break;

    case ACKSENT:
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	f->state = OPENED;
	f->retransmits = f->maxconfreqtransmits;
        if (f->callbacks->up)
	        (*f->callbacks->up)(f);	/* Inform upper layers */
	break;

    case OPENED:
	/* Go down and restart negotiation */
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	fsm_sconfreq(f, 0);		/* Send initial Configure-Request */
	f->state = REQSENT;
	break;
    }
}


/*
 * fsm_rconfnakrej - Receive Configure-Nak or Configure-Reject.
 */
static void
fsm_rconfnakrej(f, code, id, inp, len)
    fsm *f;
    int code, id;
    u_char *inp;
    int len;
{
    int (*proc) __P((fsm *, u_char *, int));
    int ret;

    if (id != f->reqid || f->seen_ack)	/* Expected id? */
	return;				/* Nope, toss... */
    proc = (code == CONFNAK)? f->callbacks->nakci: f->callbacks->rejci;
    if (!proc || !(ret = proc(f, inp, len))) {
	/* Nak/reject is bad - ignore it */
	error("Received bad configure-nak/rej: %P", inp, len);
	return;
    }
    f->seen_ack = 1;

    switch (f->state) {
    case CLOSED:
    case STOPPED:
	fsm_sdata(f, TERMACK, id, NULL, 0);
	break;

    case REQSENT:
    case ACKSENT:
	/* They didn't agree to what we wanted - try another request */
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	if (ret < 0)
	    f->state = STOPPED;		/* kludge for stopping CCP */
	else
	    fsm_sconfreq(f, 0);		/* Send Configure-Request */
	break;

    case ACKRCVD:
	/* Got a Nak/reject when we had already had an Ack?? oh well... */
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	fsm_sconfreq(f, 0);
	f->state = REQSENT;
	break;

    case OPENED:
	/* Go down and restart negotiation */
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	fsm_sconfreq(f, 0);		/* Send initial Configure-Request */
	f->state = REQSENT;
	break;
    }
}


/*
 * fsm_rtermreq - Receive Terminate-Req.
 */
static void
fsm_rtermreq(f, id, p, len)
    fsm *f;
    int id;
    u_char *p;
    int len;
{
    switch (f->state) {
    case ACKRCVD:
    case ACKSENT:
	f->state = REQSENT;		/* Start over but keep trying */
	break;

    case OPENED:
	if (len > 0) {
	    info("%s terminated by peer (%0.*v)", PROTO_NAME(f), len, p);
	} else
	    info("%s terminated by peer", PROTO_NAME(f));
	f->retransmits = 0;
	f->state = STOPPING;
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	TIMEOUT(fsm_timeout, f, f->timeouttime);
	break;
    }

    if (PPP_IPCP == f->protocol)
    {
        //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Termination ACK");
        ppp_log("PPP IPCP Send Termination ACK");
    }
    else if (PPP_LCP == f->protocol)
    {
        //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Termination ACK");
        ppp_log("PPP LCP Send Termination ACK");
    }

    fsm_sdata(f, TERMACK, id, NULL, 0);
}


/*
 * fsm_rtermack - Receive Terminate-Ack.
 */
static void
fsm_rtermack(f)
    fsm *f;
{
    switch (f->state) {
    case CLOSING:
	UNTIMEOUT(fsm_timeout, f);
	f->state = CLOSED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	break;
    case STOPPING:
	UNTIMEOUT(fsm_timeout, f);
	f->state = STOPPED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	break;

    case ACKRCVD:
	f->state = REQSENT;
	break;

    case OPENED:
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	fsm_sconfreq(f, 0);
	f->state = REQSENT;
	break;
    }
}


/*
 * fsm_rcoderej - Receive an Code-Reject.
 */
static void
fsm_rcoderej(f, inp, len)
    fsm *f;
    u_char *inp;
    int len;
{
    u_char code, id;

    if (len < HEADERLEN) {
	FSMDEBUG(("fsm_rcoderej: Rcvd short Code-Reject packet!"));
	return;
    }
    GETCHAR(code, inp);
    GETCHAR(id, inp);
    warn("%s: Rcvd Code-Reject for code %d, id %d", PROTO_NAME(f), code, id);

    if( f->state == ACKRCVD )
	f->state = REQSENT;
}


/*
 * fsm_protreject - Peer doesn't speak this protocol.
 *
 * Treat this as a catastrophic error (RXJ-).
 */
void
fsm_protreject(f)
    fsm *f;
{
    switch( f->state ){
    case CLOSING:
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	/* fall through */
    case CLOSED:
	f->state = CLOSED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	break;

    case STOPPING:
    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	/* fall through */
    case STOPPED:
	f->state = STOPPED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	break;

    case OPENED:
	terminate_layer(f, STOPPING);
	break;

    default:
	FSMDEBUG(("%s: Protocol-reject event in state %d!",
		  PROTO_NAME(f), f->state));
    }
}


/*
 * fsm_sconfreq - Send a Configure-Request.
 */
static void
fsm_sconfreq(f, retransmit)
    fsm *f;
    int retransmit;
{
    u_char *outp;
    int cilen;

    if( f->state != REQSENT && f->state != ACKRCVD && f->state != ACKSENT ){
	/* Not currently negotiating - reset options */
	if( f->callbacks->resetci )
	    (*f->callbacks->resetci)(f);
	f->nakloops = 0;
    }

    if( !retransmit ){
	/* New request - reset retransmission counter, use new ID */
	f->retransmits = f->maxconfreqtransmits;
	f->reqid = ++f->id;
    }
	/*start of protocol WAN <3.1.3IPCP½×¶ÎACK±¨ÎÄ¶ªÊ§> porting by s60000658 20060505*/
    else if((unsigned char)1 == f->seen_ack)
    {
        f->retransmits = 1;
    }
	/*end of protocol WAN <3.1.3IPCP½×¶ÎACK±¨ÎÄ¶ªÊ§> porting by s60000658 20060505*/
    
    f->seen_ack = 0;

    /*
     * Make up the request packet
     */
    outp = outpacket_buf + PPP_HDRLEN + HEADERLEN;
    if( f->callbacks->cilen && f->callbacks->addci ){
	cilen = (*f->callbacks->cilen)(f);
	if( cilen > peer_mru[f->unit] - HEADERLEN )
	    cilen = peer_mru[f->unit] - HEADERLEN;
	if (f->callbacks->addci)
	    (*f->callbacks->addci)(f, outp, &cilen);
    } else
	cilen = 0;

    /* send the request to our peer */

    if (PPP_IPCP == f->protocol)
    {
        //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP IPCP Send Configuration Request");
        ppp_log("PPP IPCP Send Configuration Request");
    }
    else if (PPP_LCP == f->protocol)
    {
        //ATP_LOG_Printf(ATP_LOG_TYPE_WAN, ATP_LOG_LEVEL_NOTICE, 1, "PPP LCP Send Configuration Request");
        ppp_log("PPP LCP Send Configuration Request");
    }

    fsm_sdata(f, CONFREQ, f->reqid, outp, cilen);


    /* start the retransmit timer */
    --f->retransmits;
    TIMEOUT(fsm_timeout, f, f->timeouttime);
}


/*
 * fsm_sdata - Send some data.
 *
 * Used for all packets sent to our peer by this module.
 */
void
fsm_sdata(f, code, id, data, datalen)
    fsm *f;
    u_char code, id;
    u_char *data;
    int datalen;
{
    u_char *outp;
    int outlen;

    /* Adjust length to be smaller than MTU */
    outp = outpacket_buf;
    if (datalen > peer_mru[f->unit] - HEADERLEN)
	datalen = peer_mru[f->unit] - HEADERLEN;
    if (datalen && data != outp + PPP_HDRLEN + HEADERLEN)
	BCOPY(data, outp + PPP_HDRLEN + HEADERLEN, datalen);
    outlen = datalen + HEADERLEN;
    MAKEHEADER(outp, f->protocol);
    PUTCHAR(code, outp);
    PUTCHAR(id, outp);
    PUTSHORT(outlen, outp);
    output(f->unit, outpacket_buf, outlen + PPP_HDRLEN);
}
