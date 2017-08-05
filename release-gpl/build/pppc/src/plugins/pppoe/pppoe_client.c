/* PPPoE support library "libpppoe"
 *
 * Copyright 2000 Michal Ostrowski <mostrows@styx.uwaterloo.ca>,
 *                Jamal Hadi Salim <hadi@cyberus.ca>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version
 *  2 of the License, or (at your option) any later version.
 */

#include "pppoe.h"

/* start 2010-1-12 PVC自动搜索接口 */
#include <sys/sysinfo.h>
int g_SendPadi = 0;
int g_WaitPado = 0;
extern int g_PvcSearchTime;
/* end 2010-1-12 PVC自动搜索接口 */
#if 0
#ifdef SUPPORT_ATP_IPV6
extern eui64_t eui64_ifc_id;
#endif
#endif
static int std_rcv_pado(struct session* ses,
                        struct pppoe_packet *p_in,
                        struct pppoe_packet **p_out){
    char path[128] = {0};
    char acname[ATP_PPPOE_ACNAME_LEN] = {0};
    
    if( verify_packet(ses, p_in) < 0)
        return -1;
    
    if(ses->state != PADO_CODE ){
        poe_error(ses,"Unexpected packet: %P",p_in);
        return 0;
    }
    
    TRACE_Print(ATP_TRACE_PPPC_RECV_PACKET, wanif_name, "PADO");
    if (DEB_DISC2) {
	poe_dbglog (ses,"PADO received: %P", p_in);
    }

    /* 收到PADO后再不需要PVC搜索 */
    if (g_SendPadi > 0)
    {
        system("echo 1 > /var/wan/pvcsearch");
        g_PvcSearchTime = -1;
        g_SendPadi = -1;
        notice("Recv PADO ...");
        //BSP_SYS_WakeupMonitorTask();
        notifywanstatus();
    }

    /* Telmex要求在PVC 不同时Internet LED灯不可闪烁，在收到PADO后再进行闪灯操作*/
    notifyPadoReceived();      
    
    memcpy(&ses->remote, &p_in->addr, sizeof(struct sockaddr_ll));
    memcpy( &ses->curr_pkt.addr, &ses->remote , sizeof(struct sockaddr_ll));
    
    ses->curr_pkt.hdr->code = PADR_CODE;
    
    /* The HOST_UNIQ has been verified already... there's no "if" about this */
    /* if(ses->filt->htag) */
    copy_tag(&ses->curr_pkt,get_tag(p_in->hdr,PTT_HOST_UNIQ));  
    
    if (ses->filt->ntag) {
        ses->curr_pkt.tags[TAG_AC_NAME]=NULL;
    }
    copy_tag(&ses->curr_pkt,get_tag(p_in->hdr,PTT_AC_NAME));
    
    snprintf(path, sizeof(path), "%s%s/%s", WAN_PATH, wanif_name, "acname");
    snprintf(acname, sizeof(acname), "%s", (char*)(ses->curr_pkt.tags[TAG_AC_NAME]+1));
    WriteToFile(path, acname);
    
    if(ses->filt->stag) {
        ses->curr_pkt.tags[TAG_SRV_NAME]=NULL;
    }
    if (strlen (atp_pppoe_srv_name) > 0)
    {
        copy_tag(&ses->curr_pkt,get_tag(p_in->hdr,PTT_SRV_NAME));
    }
    
    copy_tag(&ses->curr_pkt,get_tag(p_in->hdr,PTT_AC_COOKIE));
    copy_tag(&ses->curr_pkt,get_tag(p_in->hdr,PTT_RELAY_SID));
    
    ses->state = PADS_CODE;
    
    ses->retransmits = 0;
    
    send_disc(ses, &ses->curr_pkt);
    (*p_out) = &ses->curr_pkt;
    
    if (ses->np)
	return 1;
    
    return 0;
}

static int std_init_disc(struct session* ses,
			 struct pppoe_packet *p_in,
			 struct pppoe_packet **p_out){
    
    memset(&ses->curr_pkt,0, sizeof(struct pppoe_packet));

    
    /* Check if already connected */
    if( ses->state != PADO_CODE ){
	return 1;
    }
    
    ses->curr_pkt.hdr = (struct pppoe_hdr*) ses->curr_pkt.buf;
    ses->curr_pkt.hdr->ver  = 1;
    ses->curr_pkt.hdr->type = 1;
    ses->curr_pkt.hdr->code = PADI_CODE;
    
    
    memcpy( &ses->curr_pkt.addr, &ses->remote , sizeof(struct sockaddr_ll));
    
    poe_info (ses,"Sending PADI");
    if (DEB_DISC)
	poe_dbglog (ses,"Sending PADI");

    /* start 2010-1-12 PVC自动搜索接口 */
    if (g_PvcSearchTime > 0)
    {
        struct sysinfo info;
        sysinfo(&info);
        
        if (g_SendPadi == 0)
        {
            g_WaitPado = info.uptime;
            g_SendPadi++;
            notice("Init discovery[%d]", g_PvcSearchTime);
        }
        else if (info.uptime - g_WaitPado > g_PvcSearchTime)
        {
            system("echo 2 > /var/wan/pvcsearch");
            g_PvcSearchTime = -1;
            notice("Send PADI time out.");
            //BSP_SYS_WakeupMonitorTask();
            notifywanstatus();
        }
    }
    /* end 2010-1-12 PVC自动搜索接口 */
    
    ses->retransmits = 0 ;
    
    if(ses->filt->ntag) {
	ses->curr_pkt.tags[TAG_AC_NAME]=ses->filt->ntag;
	poe_info(ses,"overriding AC name\n");
    }
    
    if(ses->filt->stag)
	ses->curr_pkt.tags[TAG_SRV_NAME]=ses->filt->stag;
    
    if(ses->filt->htag)
	ses->curr_pkt.tags[TAG_HOST_UNIQ]=ses->filt->htag;
    
    send_disc(ses, &ses->curr_pkt);
    (*p_out)= &ses->curr_pkt;

    return 0;
}

char sesinfo[PATHLENGTH] = {0};

static int std_rcv_pads(struct session* ses,
			struct pppoe_packet *p_in,
			struct pppoe_packet **p_out)
{
    FILE *pf;
    char path[64]="";
    unsigned char   remote[ETH_ALEN] = {0};
    
    if( verify_packet(ses, p_in) < 0)
	return -1;
    
    if (DEB_DISC)
	poe_dbglog (ses,"Got connection: %x",
		    ntohs(p_in->hdr->sid));
    poe_info (ses,"Got connection: %x", ntohs(p_in->hdr->sid));
    TRACE_Print(ATP_TRACE_PPPC_RECV_PACKET, wanif_name, "PADS");
    
    ses->sp.sa_family = AF_PPPOX;
    ses->sp.sa_protocol = PX_PROTO_OE;
    ses->sp.sa_addr.pppoe.sid = p_in->hdr->sid;
	#ifdef SUPPORT_ATP_PPP_TOGGLE_DT_W723V
    //注意需同步ses->name和devnam
    memcpy(ses->name,devnam,IFNAMSIZ);
	#endif
    memcpy(ses->sp.sa_addr.pppoe.dev,ses->name, IFNAMSIZ);
    memcpy(ses->sp.sa_addr.pppoe.remote, p_in->addr.sll_addr, ETH_ALEN);
    
    /*保存对端mac地址和本次拨号的会话id*/
    memcpy(remote, ses->sp.sa_addr.pppoe.remote, ETH_ALEN);

    sprintf(sesinfo, "%02x%02x%02x%02x%02x%02x/%04x", remote[0], remote[1], remote[2],
		remote[3], remote[4], remote[5], ses->sp.sa_addr.pppoe.sid);   

    sprintf(path, "/var/wan/%s/sesinfo", wanif_name);
    pf = fopen(path, "w");
    if (pf == NULL) 
    {
    	printf("Failed to create session.");
    	return -1;
    }
    fprintf(pf, "%02x%02x%02x%02x%02x%02x/%04x",
            remote[0],
            remote[1],
            remote[2],
            remote[3],
            remote[4],
            remote[5],
            ses->sp.sa_addr.pppoe.sid);
    fclose(pf);
    
    return 1;
}

static int std_rcv_padt(struct session* ses,
			struct pppoe_packet *p_in,
			struct pppoe_packet **p_out){
    ses->state = PADO_CODE;

    TRACE_Print(ATP_TRACE_PPPC_RECV_PACKET, wanif_name, "PADT");
    return 0;
}


extern int disc_sock;
int client_init_ses (struct session *ses, char* devnam)
{
    int i=0;
    int retval;
    char dev[IFNAMSIZ+1];
    int addr[ETH_ALEN];
    int sid;
    
    /* do error checks here; session name etc are valid */
//    poe_info (ses,"init_ses: creating socket");
    
    /* Make socket if necessary */
    if( disc_sock < 0 ){
	
	disc_sock = socket(PF_PACKET, SOCK_DGRAM, 0);
	if( disc_sock < 0 ){
	    poe_fatal(ses,
		      "Cannot create PF_PACKET socket for PPPoE discovery\n");
	    return 0;/*WAN <3.1.2Discover收到不可识别报文退出> porting by s60000658 20060505*/
	}

#ifdef SUPPORT_ATP_DT_QOS
        unsigned long ulMark = 0x07; /* The top priority */
        if (setsockopt(disc_sock, SOL_SOCKET, SO_MARK, &ulMark, sizeof(ulMark)) < 0) 
        {
            poe_fatal(ses, "Warning: QoS setsockopt error: %s\r\n");
            //return 0;
        }
#endif /* SUPPORT_ATP_DT_QOS */

    }
    
    /* Check for long format */
    retval =sscanf(devnam, FMTSTRING(IFNAMSIZ),addr, addr+1, addr+2,
		   addr+3, addr+4, addr+5,&sid,dev);
    if( retval != 8 ){
	/* Verify the device name , construct ses->local */
	retval = get_sockaddr_ll(devnam,&ses->local);
	if (retval < 0)
	    {
	    poe_fatal(ses, "client_init_ses: "
		      "Cannot create PF_PACKET socket for PPPoE discovery\n");
	    return 0;/*WAN <3.1.2Discover收到不可识别报文退出> porting by s60000658 20060505*/
	    }
	
	
	ses->state = PADO_CODE;

	memcpy(&ses->remote, &ses->local, sizeof(struct sockaddr_ll) );
	
	memset( ses->remote.sll_addr, 0xff, ETH_ALEN);
    }else{
	/* long form parsed */

	/* Verify the device name , construct ses->local */
	retval = get_sockaddr_ll(dev,&ses->local);
	if (retval < 0)
	    {
	    poe_fatal(ses,"client_init_ses(2): "
		      "Cannot create PF_PACKET socket for PPPoE discovery\n");
	    return 0;/*WAN <3.1.2Discover收到不可识别报文退出> porting by s60000658 20060505*/
	    }
	
	ses->state = PADS_CODE;
	ses->sp.sa_family = AF_PPPOX;
	ses->sp.sa_protocol = PX_PROTO_OE;
	ses->sp.sa_addr.pppoe.sid = sid;

	memcpy(&ses->remote, &ses->local, sizeof(struct sockaddr_ll) );
	
	for(; i < ETH_ALEN ; ++i ){
	    ses->sp.sa_addr.pppoe.remote[i] = addr[i];
	    ses->remote.sll_addr[i]=addr[i];
	}
	memcpy(ses->sp.sa_addr.pppoe.dev, dev, IFNAMSIZ);
	
	
	
    }
    if( retval < 0 )
	error("bad device name: %s",devnam);
    
    
    retval = bind( disc_sock ,
		   (struct sockaddr*)&ses->local,
		   sizeof(struct sockaddr_ll));
    
    
    if( retval < 0 ){
	error("bind to PF_PACKET socket failed: %m");
    }
    
	//atp
	if (ses->fd > 0)
		close(ses->fd);

    ses->fd = socket(AF_PPPOX,SOCK_STREAM,PX_PROTO_OE);
    if(ses->fd < 0)
    {
    	poe_fatal(ses,"Failed to create PPPoE socket: %m");
    	return 0;/*WAN <3.1.2Discover收到不可识别报文退出> porting by s60000658 20060505*/
    }
#if 0
#ifdef SUPPORT_ATP_IPV6
    memcpy(eui64_ifc_id.e8, ses->local.sll_addr, 3);
    memcpy(eui64_ifc_id.e8 + 5, ses->local.sll_addr + 3, 3);
    eui64_ifc_id.e8[3] = 0xFF;
    eui64_ifc_id.e8[4] = 0xFE;
    eui64_ifc_id.e8[0] ^= 2;
#endif
#endif  
    ses->init_disc = std_init_disc;
    ses->rcv_pado  = std_rcv_pado;
    ses->rcv_pads  = std_rcv_pads;
    ses->rcv_padt  = std_rcv_padt;
    
    
#ifdef SUPPORT_ATP_PPP_TOGGLE_DT_W723V
    ses->retries = turn_around_count;
#else
	/* this should be filter overridable */
    /* start 2010-1-12 PADI发送间隔及次数修改 */
    /*ses->retries = 5;*/
    if (0 < g_ulRetrySendTimes)
    {
        ses->retries = g_ulRetrySendTimes;
    }
    else
    {
        ses->retries = 5;
    }
    
    /* end 2010-1-12 PADI发送间隔及次数修改 */
 #endif
 #ifdef SUPPORT_ATP_VOX_CGN
    ses->retries = -1;
 #endif
    return ses->fd;
}

  
