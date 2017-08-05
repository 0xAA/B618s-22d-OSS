/* PPPoE support library "libpppoe"
 *
 * Copyright 2000 Michal Ostrowski <mostrows@styx.uwaterloo.ca>,
 *		  Jamal Hadi Salim <hadi@cyberus.ca>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version
 *  2 of the License, or (at your option) any later version.
 */
#define __ATP_DEPRECATED_H__

#include "pppoe.h"
#include <sys/sysinfo.h>

/* start 2010-1-12 PVC自动搜索接口 */
extern int g_SendPadi;
extern int g_WaitPado;
extern int g_PvcSearchTime;
/* end 2010-1-12 PVC自动搜索接口 */
#include <sys/time.h>
unsigned int DhcpGetUpTime()
{
    struct sysinfo info;

    sysinfo(&info);
    return (unsigned int)(info.uptime);
}

int disc_sock=-1;

static int tag_map[] = { PTT_SRV_NAME,
			 PTT_AC_NAME,
			 PTT_HOST_UNIQ,
			 PTT_AC_COOKIE,
			 PTT_VENDOR,
			 PTT_RELAY_SID,
			 PTT_SRV_ERR,
			 PTT_SYS_ERR,
			 PTT_GEN_ERR,
			 PTT_EOL
};

int verify_packet( struct session *ses, struct pppoe_packet *p);

#define TAG_DATA(type,tag_ptr) ((type *) ((struct pppoe_tag*)tag_ptr)->tag_data)

/* start SUPPORT_PPPOE2A */ 
extern int pppoe2a_flag;
extern char pppoe2a_mac[32];
extern short pppoe2a_sid;
/* end SUPPORT_PPPOE2A */

/***************************************************************************
 *
 * Return the location where the next tag can be pu
 *
 **************************************************************************/
static  struct pppoe_tag *next_tag(struct pppoe_hdr *ph)
{
    return (struct pppoe_tag *)
	(((char *) &ph->tag) + ntohs(ph->length));
}

/**************************************************************************
 *
 * Update header to reflect the addition of a new tag
 *
 **************************************************************************/
static  void add_tag(struct pppoe_hdr *ph, struct pppoe_tag *pt)
{
    int len = (ntohs(ph->length) +
	       ntohs(pt->tag_len) +
	       sizeof(struct pppoe_tag));

    if (pt != next_tag(ph))
	printf("PPPoE add_tag caller is buggy\n");

    ph->length = htons(len);
}

/*************************************************************************
 *
 * Look for a tag of a specific type
 *
 ************************************************************************/
struct pppoe_tag *get_tag(struct pppoe_hdr *ph, u_int16_t idx)
{
    char *end = (char *) next_tag(ph);
    char *ptn = NULL;
    struct pppoe_tag *pt = &ph->tag[0];

    /*
     * Keep processing tags while a tag header will still fit.
     *
     * This check will ensure that the entire tag header pointed
     * to by pt will fit inside the message, and thus it will be
     * valid to check the tag_type and tag_len fields.
     */
    while ((char *)(pt + 1) <= end) {
	/*
	 * If the tag data would go past the end of the packet, abort.
	 */
	ptn = (((char *) (pt + 1)) + ntohs(pt->tag_len));
	if (ptn > end)
	    return NULL;

	if (pt->tag_type == idx)
	    return pt;

	pt = (struct pppoe_tag *) ptn;
    }

    return NULL;
}

struct pppoe_tag *get_nexttag(struct pppoe_hdr *ph, struct pppoe_tag* pt, u_int16_t idx)
{
    char *end = (char *) next_tag(ph);
    char *ptn = NULL;

	/*
	 * If the tag data would go past the end of the packet, abort.
	 */
    ptn = (((char *) (pt + 1)) + ntohs(pt->tag_len));
    if (ptn > end)
    {	    
	 return NULL;
    }
	    
    if (((struct pppoe_tag *)ptn)->tag_type == idx)
    {
	 return ptn;
    }

    return NULL;
}

/* We want to use tag names to reference into arrays  containing the tag data.
   This takes an RFC 2516 tag identifier and maps it into a local one.
   The reverse mapping is accomplished via the tag_map array */
#define UNMAP_TAG(x) case PTT_##x : return TAG_##x
static inline int tag_index(int tag){
    switch(tag){
	UNMAP_TAG(SRV_NAME);
	UNMAP_TAG(AC_NAME);
	UNMAP_TAG(HOST_UNIQ);
	UNMAP_TAG(AC_COOKIE);
	UNMAP_TAG(VENDOR);
	UNMAP_TAG(RELAY_SID);
	UNMAP_TAG(SRV_ERR);
	UNMAP_TAG(SYS_ERR);
	UNMAP_TAG(GEN_ERR);
	UNMAP_TAG(EOL);
    };
    return -1;
}

/*************************************************************************
 *
 * Makes a copy of a tag into a PPPoE packe
 *
 ************************************************************************/
void copy_tag(struct pppoe_packet *dest, struct pppoe_tag *pt)
{
    struct pppoe_tag *end_tag = get_tag(dest->hdr, PTT_EOL);
    int tagid;
    int tag_len;
    if( !pt ) {
	return;
    }
    tagid = tag_index(pt->tag_type);

    tag_len = sizeof(struct pppoe_tag) + ntohs(pt->tag_len);

    if( end_tag ){
	memcpy(((char*)end_tag)+tag_len ,
	       end_tag, sizeof(struct pppoe_tag));

	dest->tags[tagid]=end_tag;
	dest->tags[TAG_EOL] = (struct pppoe_tag*)((char*)dest->tags[TAG_EOL] + tag_len);
	memcpy(end_tag, pt, tag_len);
	dest->hdr->length = htons(ntohs(dest->hdr->length) + tag_len);

    }else{
	memcpy(next_tag(dest->hdr),pt, tag_len);
	dest->tags[tagid]=next_tag(dest->hdr);
	add_tag(dest->hdr,next_tag(dest->hdr));
    }


}


/*************************************************************************
 *
 * Put tags from a packet into a nice array
 *
 ************************************************************************/
static void extract_tags(struct pppoe_hdr *ph, struct pppoe_tag** buf){
    int i=0;
    for(;i<MAX_TAGS;++i){
	buf[i] = get_tag(ph,tag_map[i]);
    }
}


/*************************************************************************
 *
 * Verify that a packet has a tag containint a specific value
 *
 ************************************************************************/
static int verify_tag(struct session* ses,
		      struct pppoe_packet* p,
		      unsigned short id,
		      char* data,
		      int data_len)
{
    int len;
    struct pppoe_tag *pt = p->tags[id];

    if( !pt ){
	poe_info(ses,"Missing tag %d. Expected %s\n",
		 id,data);
	return 0;
    }
    len = ntohs(pt->tag_len);
    if(len != data_len){
	poe_info(ses,"Length mismatch on tag %d: expect: %d got: %d\n",
		 id, data_len, len);
	return 0;
    }

    if( 0!=memcmp(pt->tag_data,data,data_len)){
	poe_info(ses,"Tag data mismatch on tag %d: expect: %s vs %s\n",
		 id, data,pt->tag_data);
	return 0;
    }
    return 1;
}


/*************************************************************************
 *
 * Verify the existence of an ethernet device.
 * Construct an AF_PACKET address struct to match.
 *
 ************************************************************************/
int get_sockaddr_ll(const char *devnam,struct sockaddr_ll* sll){
    struct ifreq ifr;
    int retval;

    if(disc_sock<0){

	disc_sock = socket(PF_PACKET, SOCK_DGRAM, 0);
	if( disc_sock < 0 ){
	    return -1;
	}
    }

    strncpy(ifr.ifr_name, devnam, sizeof(ifr.ifr_name));

    retval = ioctl( disc_sock , SIOCGIFINDEX, &ifr);

    if( retval < 0 ){
//	error("Bad device name: %s  (%m)",devnam);
	return 0;
    }

    if(sll) sll->sll_ifindex = ifr.ifr_ifindex;

    retval = ioctl (disc_sock, SIOCGIFHWADDR, &ifr);
    if( retval < 0 ){
//	error("Bad device name: %s  (%m)",devnam);
	return 0;
    }

    if (ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER) {
	error("Interface %s is not Ethernet!", devnam);
	return 0;
    }
    if(sll){
	sll->sll_family	= AF_PACKET;
	sll->sll_protocol= ntohs(ETH_P_PPP_DISC);
	sll->sll_hatype	= ARPHRD_ETHER;
	sll->sll_pkttype = PACKET_BROADCAST;
	sll->sll_hatype	= ETH_ALEN;
	memcpy( sll->sll_addr , ifr.ifr_hwaddr.sa_data, ETH_ALEN);
    }
    return 1;
}

static void print_trace_info(unsigned code)
{
    switch(code)
    {
    case PADI_CODE:
        TRACE_Print(ATP_TRACE_PPPC_SEND_PACKET, wanif_name, "PADI");
        break;
    case PADR_CODE:
        TRACE_Print(ATP_TRACE_PPPC_SEND_PACKET, wanif_name, "PADR");
        break;
    case PADT_CODE:
        TRACE_Print(ATP_TRACE_PPPC_SEND_PACKET, wanif_name, "PADT");
        break;
    }
}

/*************************************************************************
 *
 * Construct and send a discovery message.
 *
 ************************************************************************/
int send_disc(struct session *ses, struct pppoe_packet *p)
{
    char buf[MAX_PAYLOAD + sizeof(struct pppoe_hdr)];
    int data_len = sizeof(struct pppoe_hdr);

    struct pppoe_hdr *ph = NULL;
    struct pppoe_tag *tag = NULL;
    int i, err = 0;
    int got_host_uniq = 0;
    int got_srv_name = 0;
    int got_ac_name = 0;

    for (i = 0; i < MAX_TAGS; i++) {
	if (!p->tags[i])
	    continue;

	got_host_uniq |= (p->tags[i]->tag_type == PTT_HOST_UNIQ);

	/* Relay identifiers qualify as HOST_UNIQ's:
	   we need HOST_UNIQ to uniquely identify the packet,
	   PTT_RELAY_SID is sufficient for us for outgoing packets */
	got_host_uniq |= (p->tags[i]->tag_type == PTT_RELAY_SID);

	got_srv_name |= (p->tags[i]->tag_type == PTT_SRV_NAME);
	got_ac_name  |= (p->tags[i]->tag_type == PTT_AC_NAME);

	data_len += (ntohs(p->tags[i]->tag_len) +
		     sizeof(struct pppoe_tag));
    }

    ph = (struct pppoe_hdr *) buf;


    memcpy(ph, p->hdr, sizeof(struct pppoe_hdr));
    ph->length = __constant_htons(0);
    
    /* if no HOST_UNIQ tags --- add one with process id */
    if (!got_host_uniq && ph->code!=PADT_CODE){
	data_len += (sizeof(struct pppoe_tag) +
		     sizeof(struct session *));
	tag = next_tag(ph);
	tag->tag_type = PTT_HOST_UNIQ;
	tag->tag_len = htons(sizeof(struct session *));
	memcpy(tag->tag_data,
	       &ses,
	       sizeof(struct session *));

	add_tag(ph, tag);
    }
	
    if( !got_srv_name && ph->code!=PADT_CODE){
	data_len += sizeof(struct pppoe_tag);
	tag = next_tag(ph);
	tag->tag_type = PTT_SRV_NAME;
	tag->tag_len = 0;
	add_tag(ph, tag);
    }

    if(!got_ac_name && ph->code==PADO_CODE){
	data_len += sizeof(struct pppoe_tag);
	tag = next_tag(ph);
	tag->tag_type = PTT_AC_NAME;
	tag->tag_len = 0;
	add_tag(ph, tag);
    }

    for (i = 0; i < MAX_TAGS; i++) {
	if (!p->tags[i])
	    continue;

	tag = next_tag(ph);
	memcpy(tag, p->tags[i],
	       sizeof(struct pppoe_tag) + ntohs(p->tags[i]->tag_len));

	add_tag(ph, tag);
    }

    /* Now fixup the packet struct to make sure all of its pointers
       are self-contained */
    memcpy( p->hdr , ph, data_len );
    extract_tags( p->hdr, p->tags);
    
    print_trace_info(ph->code);
    
    err = sendto(disc_sock, buf, data_len, 0,
		   (struct sockaddr*) &p->addr,
		   sizeof(struct sockaddr_ll));

    if(err < 0)
	poe_error(ses,"sendto returned: %m\n");

    return err;
}

/*************************************************************************
 *
 * Verify that a packet is legal
 *
 *************************************************************************/
int verify_packet( struct session *ses, struct pppoe_packet *p){
    struct session * hu_val;
	int tmp_val = 0;
    /* This code here should do all of the error checking and
       validation on the incoming packet */

    /* If we receive any error tags, abort */
#define CHECK_TAG(name, val)					\
    if((NULL==p->tags[name])== val){				\
	poe_error(ses,"Tag error: " #name );			\
	return -1;						\
    }

    CHECK_TAG(TAG_SRV_ERR,0);
    CHECK_TAG(TAG_SYS_ERR,0);
    CHECK_TAG(TAG_GEN_ERR,0);

    /* A HOST_UNIQ must be present */
    CHECK_TAG(TAG_HOST_UNIQ,1);

    //host_uniq使用接口MAC地址而不是固定的变量地址值
    hu_val = TAG_DATA(struct session* ,p->tags[TAG_HOST_UNIQ]);    
    memcpy((char*)&tmp_val, (char*)hu_val, sizeof(tmp_val));

    if( tmp_val != ses )
    {
        poe_info(ses,"HOST_UNIQ mismatch: %08x %08x\n",tmp_val, (int)ses);
        return -1;
    }

    if(ses->filt->htag &&
       !verify_tag(ses,p,TAG_HOST_UNIQ,ses->filt->htag->tag_data,(int)ntohs(ses->filt->htag->tag_len)))
	return -1;
    else
	poe_info(ses,"HOST_UNIQ successful match\n");


    if(ses->filt->ntag &&
       !verify_tag(ses,p,TAG_AC_NAME,ses->filt->ntag->tag_data,(int)ntohs(ses->filt->ntag->tag_len))){
	    poe_info(ses,"AC_NAME failure");
	    return -1;
    }

    if(ses->filt->stag &&
       !verify_tag(ses,p,TAG_SRV_NAME,ses->filt->stag->tag_data,(int)ntohs(ses->filt->stag->tag_len))){
    	poe_info(ses,"SRV_NAME failure");
    	return -1;
    }
    return 0;
}


/*************************************************************************
 *
 * Receive and verify an incoming packet.
 *
 *************************************************************************/
static int recv_disc( struct session *ses,
		      struct pppoe_packet *p){
    int error = 0;
    unsigned int from_len = sizeof(struct sockaddr_ll);

    p->hdr = (struct pppoe_hdr*)p->buf;

    error = recvfrom( disc_sock, p->buf, 1500, 0,
		      (struct sockaddr*)&p->addr, &from_len);

    if(error < 0) return error;

    extract_tags(p->hdr,p->tags);

    return 1;
}


/*************************************************************************
 *
 * Send a PADT
 *
 *************************************************************************/
int session_disconnect(struct session *ses)
{
    int i;    
    int mac_addr[ETH_ALEN] = {0};
    int ret;
    int sid;
    struct pppoe_packet padt;

    memset(&padt,0,sizeof(struct pppoe_packet));
    memcpy(&padt.addr, &ses->remote, sizeof(struct sockaddr_ll));

    padt.hdr = (struct pppoe_hdr*) ses->curr_pkt.buf;
    padt.hdr->ver  = 1;
    padt.hdr->type = 1;
    padt.hdr->code = PADT_CODE;
    padt.hdr->sid  = ses->sp.sa_addr.pppoe.sid;

    if (padt.hdr->sid == 0) 
    {
        ret = sscanf(sesinfo, "%02x%02x%02x%02x%02x%02x/%04x", mac_addr, mac_addr+1, 
                    mac_addr+2, mac_addr+3, mac_addr+4, mac_addr+5, &sid);
        if (7 == ret) 
        {
    	    for(i = 0; i < ETH_ALEN ; i++ )
            {
    	        padt.addr.sll_addr[i] = mac_addr[i];
    	    }
            padt.hdr->sid = sid;
        }
    }

/* start SUPPORT_PPPOE2A */
    if (!pppoe2a_flag)
    {
        if( disc_sock < 0 )
        {	
        	disc_sock = socket(PF_PACKET, SOCK_DGRAM, 0);
        	bind(disc_sock ,
        	      (struct sockaddr*)&ses->local,
        	      sizeof(struct sockaddr_ll));
        }
     
        send_disc(ses,&padt);
    }
/* end SUPPORT_PPPOE2A */

    if(disc_sock > 0)
    {
        close(disc_sock);
        disc_sock = -1;
    }

    ses->sp.sa_addr.pppoe.sid = 0 ;
    ses->state = PADO_CODE;
    return 0;

}

static int session_reautocut(struct session *ses)
{
    int i;
    int ret;
    int sid;
    int mac_addr[ETH_ALEN] = {0};    
    struct pppoe_packet padt;

    memset(&padt,0,sizeof(struct pppoe_packet));
    memcpy(&padt.addr, &ses->remote, sizeof(struct sockaddr_ll));

    padt.hdr = (struct pppoe_hdr*) ses->curr_pkt.buf;
    padt.hdr->ver  = 1;
    padt.hdr->type = 1;
    padt.hdr->code = PADT_CODE;
    padt.hdr->sid  = ses->sp.sa_addr.pppoe.sid;

    if (0 == padt.hdr->sid)
    {
        ret = sscanf(sesinfo, "%02x%02x%02x%02x%02x%02x/%04x", mac_addr, mac_addr+1, 
                    mac_addr+2, mac_addr+3, mac_addr+4, mac_addr+5, &sid);
        if (7 == ret) 
        {
    	    for(i = 0; i < ETH_ALEN ; i++ )
            {
    	        padt.addr.sll_addr[i] = mac_addr[i];
    	    }
            padt.hdr->sid = sid;
        }
    }
    memset(sesinfo,0,sizeof(sesinfo));
    send_disc(ses,&padt);
    ses->sp.sa_addr.pppoe.sid = 0 ;
    ses->state = PADO_CODE;
    return 1;
}

extern int reautocut;
/*************************************************************************
 *
 * Make a connection -- behaviour depends on callbacks specified in "ses"
 *
 *************************************************************************/
int session_connect(struct session *ses)
{
    //int i=0;
    //int pkt_size=0;
    //int ret_pkt_size=0;
    //struct pppoe_tag *tags = NULL;
    struct pppoe_packet *p_out=NULL;
    struct pppoe_packet rcv_packet;
    int ret;
    int flag  = 0;
    unsigned int curtime = 0;
    unsigned int sendtime = 0;

    //不在轮询过程重复发送PADT
    //if (reautocut && (req_rediscon || strlen(sesinfo)))
    if (reautocut && strlen(sesinfo))
    {
        session_reautocut(ses);
        //sleep(1);
    }

    if(ses->init_disc){
        /*padi无应答记录日志*/
        ppp_log("PADI no reply");
    	ret = (*ses->init_disc)(ses, NULL, &p_out);
    	if( ret != 0 ) return ret;
    }

    /* main discovery loop */
    while(ses->retransmits < ses->retries || ses->retries==-1 ){
	fd_set in;
	struct timeval tv;
	FD_ZERO(&in);

	FD_SET(disc_sock,&in);

    /* start 2010-1-12 PVC自动搜索接口 */
    if ((g_PvcSearchTime > 0) && (g_SendPadi > 0))
    {
        struct sysinfo info;
        sysinfo(&info);

        if (info.uptime - g_WaitPado > g_PvcSearchTime)
        {
            system("echo 2 > /var/wan/pvcsearch");
            notice("Resend PADI time out.");
            g_PvcSearchTime = -1;            
            //BSP_SYS_WakeupMonitorTask();
            notifywanstatus();
        }
    }
    /* end 2010-1-12 PVC自动搜索接口 */ 

    flag = 0;
	if(ses->retransmits>=0)
    {
	    ++ses->retransmits;
	    flag = 1;
        /*B300 新增,同一PPPoE会话内的PADI报文重发时间*/
        if(g_ulRetrySendInterval > 0)
            tv.tv_sec = g_ulRetrySendInterval;
        else
        {
    	    tv.tv_sec = 1 << ses->retransmits;
            /* start 2010-1-12 PVC自动搜索接口 */
            if ((g_PvcSearchTime > 0) && (tv.tv_sec > 3))
    	    /*if (tv.tv_sec > 3)*/
            /* end 2010-1-12 PVC自动搜索接口 */ 
    	    {
    		    tv.tv_sec = 3;
    	    }
        }
#ifdef SUPPORT_ATP_PPP_TOGGLE_DT_W723V
			tv.tv_sec = 3;
#endif
#ifdef SUPPORT_ATP_VOX_CGN
        tv.tv_sec = GetWaitTime(ses->retransmits);
#endif
	    tv.tv_usec = 0;
	    ret = select(disc_sock+1, &in, NULL, NULL, &tv);
	}else{
	    ret = select(disc_sock+1, &in, NULL, NULL, NULL);
	}
/* 和记需求，每隔60秒发一次请求，每次请求不重发报文 */
#ifdef SUPPORT_HGC
    if (ret == 0)
    {
        return -1;
    }
#else    
	if( ret <= 0 ){
	    if( DEB_DISC ){
		poe_dbglog(ses, "Re-sending ...");
	    }
        notice("Resending ...");
        if (ret < 0)
        {
            printf("select break...\n");
        }

	    if( ses->timeout ){
        printf("session timeout...\n");
		ret = (*ses->timeout)(ses, NULL, &p_out);
		if( ret != 0 )
		    return ret;

	    }else if(p_out){
	    if (ses->retransmits < ses->retries || ses->retries == -1)		
        {
                sendtime = DhcpGetUpTime();
                 send_disc(ses,p_out);
        }
		
		/* 两次发送后即记录服务器未响应错误*/
        if ((p_out->hdr->code == PADI_CODE) && (ses->retries > 1))
        {
            pppoe_setlasterror("ERROR_NO_ANSWER");
        }
        if ((ses->retries > 0)
            && (ses->retransmits == ses->retries))
        {            
            if (p_out->hdr->code == PADR_CODE)
            {
                pppoe_setlasterror("ERROR_ISP_TIME_OUT");
            }
#ifdef SUPPORT_ATP_PPP_TOGGLE_DT_W723V
            PADI_fail_flag = 1;
    	    return -1;
#endif
            /* Return fail after ses->retries time */
    	    return -1;
        }
	    }
	    continue;
	}
#endif

	ret = recv_disc(ses, &rcv_packet);

	/* Should differentiate between system errors and
	   bad packets and the like... */
	if( ret < 0 && errno != EINTR){
        printf("recv disc err...\n");
	    return -1;
	}




	switch (rcv_packet.hdr->code) {

	case PADI_CODE:
	{
#if 0 
	    if(ses->rcv_padi){
		ret = (*ses->rcv_padi)(ses,&rcv_packet,&p_out);

		if( ret != 0){
		    return ret;
		}
	    }
#endif
        curtime =  DhcpGetUpTime();
        if(curtime - sendtime >= 3)
        {
            if( ses->timeout ){
            ret = (*ses->timeout)(ses, NULL, &p_out);

            if( ret != 0 ) 
                return ret;

            }else if(p_out){
                if ((ses->retries == -1)
                    || (ses->retransmits <= ses->retries))
                {
                    printf("Send PADI\n");
                    send_disc(ses,p_out);
                    sendtime = DhcpGetUpTime();
                    continue;
                }
            }
            
            if(ses->retransmits >= ses->retries)
            {
                continue;
            }

        }
        --ses->retransmits;
	    continue;
	}
	case PADO_CODE:		/* wait for PADO */
	{
	#ifdef SUPPORT_ATP_PPP_TOGGLE_DT_W723V
        get_pado_process();
	#endif
    if (0  != flag)
    {
       --ses->retransmits;
    }
	    if(ses->rcv_pado){
		ret = (*ses->rcv_pado)(ses,&rcv_packet,&p_out);

		if( ret != 0){
		    return ret;
		}
	    }
	    break;
	}

	case PADR_CODE:
	{
	    if(ses->rcv_padr){
		ret = (*ses->rcv_padr)(ses,&rcv_packet,&p_out);

		if( ret != 0){
		    return ret;
		}
	    }
	    break;
	}

	case PADS_CODE:
	{
	    if(ses->rcv_pads){
		ret = (*ses->rcv_pads)(ses,&rcv_packet,&p_out);
        
		if( ret != 0){
		    //close(disc_sock);
		    //disc_sock = -1;
		    return ret;
		}
	    }
	    break;
	}

	case PADT_CODE:
	{
#ifndef SUPPORT_ATP_PPP_TOGGLE_DT_W723V
	    if( rcv_packet.hdr->sid != ses->sp.sa_addr.pppoe.sid )
#else
		if(( rcv_packet.hdr->sid != ses->sp.sa_addr.pppoe.sid )||(0 == rcv_packet.hdr->sid))
#endif
		{
		--ses->retransmits;
		continue;
	    }
	    if(ses->rcv_padt){
		ret = (*ses->rcv_padt)(ses,&rcv_packet,&p_out);
        
		if( ret != 0){
		    return ret;
		}
	    }else{
		poe_error (ses,"connection terminated");
		return (-1);
	    }
	    break;
	}
	default:
	    poe_error(ses,"invalid packet %P",&rcv_packet);
	    break;
	}
	#ifdef SUPPORT_ATP_PPP_TOGGLE_DT_W723V
    if(ses->retransmits == ses->retries)
    {
        PADI_fail_flag = 1;
        return -1;
    }
	#endif

    if((ses->retries > 0) 
        && ses->retransmits == ses->retries)
    {
        /* Return fail after ses->retries time */
	    return -1;
    }    
    }
    return (0);
}


/*************************************************************************
 *
 * Register an ethernet address as a client of relaying services.
 *
 *************************************************************************/
int add_client(char *addr)
{
    struct pppoe_con* pc = (struct pppoe_con*)malloc(sizeof(struct pppoe_con));
    int ret;
    if(!pc)
	return -ENOMEM;

    memset(pc, 0 , sizeof(struct pppoe_con));

    memcpy(pc->client,addr, ETH_ALEN);
    memcpy(pc->key, addr, ETH_ALEN);

    pc->key_len = ETH_ALEN;

    if( (ret=store_con(pc)) < 0 ){
	free(pc);
    }
    return ret;

}

struct pppoe_tag *make_filter_tag(short type, short length, char* data)
{
    struct pppoe_tag *pt = (struct pppoe_tag* )malloc( sizeof(struct pppoe_tag) + length );

    if(pt == NULL) 
    {
        return NULL;
    }
    else
    {
        memset(pt, 0 , sizeof(struct pppoe_tag) + length);
    }
    
    pt->tag_len=htons(length);
    pt->tag_type=type;

    if(length>0 && data){
	memcpy( pt+1, data, length);
    }
    return pt;
}

