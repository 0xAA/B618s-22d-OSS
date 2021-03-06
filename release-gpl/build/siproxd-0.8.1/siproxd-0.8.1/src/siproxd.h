/*
    Copyright (C) 2002-2009  Thomas Ries <tries@gmx.net>

    This file is part of Siproxd.
    
    Siproxd is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    
    Siproxd is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with Siproxd; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
*/

/* $Id: siproxd.h 482 2011-06-12 18:45:17Z hb9xar $ */

#ifdef DMALLOC
 #include <dmalloc.h>
#endif
#include <limits.h>
#include "atpconfig.h"


#define TOS_RCV




#define SOCK_CREATE_BY_SIP  1
#define SOCK_CREATE_BY_RTP  2
#define SOCK_CREATE_BY_RTCP 3

#if defined(SUPPORT_ATP_TELMEX) || defined(SUPPORT_ATP_VOICE_DT)
#define SUPPORT_ALG_PRIVILEGE_USER 
#endif

#ifdef SUPPORT_ATP_TELMEX
#define PRIVILEGE_USER_DOMAIN "ims.telmex.com"
#elif SUPPORT_ATP_VOICE_DT
#define PRIVILEGE_USER_DOMAIN "t-online.de"
#endif

int ATP_SIP_ALG_QoS_SetMark(int ulSockfd, int nfmark, unsigned int ulTos);




typedef enum tagSIP_FW_COMMOND_TYPE
{
    FW_SIP_CMD_TYPE_OPEN = 0,       //insert ACCEPT rule
    FW_SIP_CMD_TYPE_REMOVE = 1,    //remove ACCEPT rule
}SIP_FW_COMMAND_TYPE_EN;

void proxy_control_wan_port(SIP_FW_COMMAND_TYPE_EN EN_ACTION, int iWanPort);


/*
 * table to hold the client registrations
 */
struct urlmap_s {
   int  active;
   int  expires;
#ifndef SUPPORT_ATP_SIPROXYD
   osip_uri_t *true_url;	// true URL of UA  (inbound URL)
   osip_uri_t *masq_url;	// masqueraded URL (outbound URL)
   osip_uri_t *reg_url;		// registered URL  (masq URL as wished by UA)
#endif

#ifdef SUPPORT_ALG_PRIVILEGE_USER
   int t_online;           /* TELMEX要求SIP ALG域名为ims.telmex.com的需要Qos，保证和网关自身一样的优先级 */
#endif /* SUPPORT_ATP_DT_QOS */

    struct sockaddr_in from;	/* received from */

#ifdef SUPPORT_ATP_SIPROXYD
    int wan_socket_fd; /*每个sip注册单独使用一个wan socket,绑定到不同的wan源端口*/
    int wan_port;  /*wan_port,上述socket的本地源端口号*/
    osip_list_t userlist;                         /**< 记录不同的用户用同一个ip+port */
#endif

};
/*
 * the difference between masq_url and reg_url is, 
 * the reg URL *always* holds the url registered by the UA.
 * the masq_url may contain a different URL due to an additional
 * masquerading feature (mask_host, masked_host config options)
 */



/*
 * Array of strings - used within configuration store
 */
#define CFG_STRARR_SIZE		128	/* max 128 entries in array */
typedef struct {
   int  used;
   char *string[CFG_STRARR_SIZE];
} stringa_t;

/*
 * global configuration option table
 */
struct siproxd_config {
   char *configfile;
   int   config_search;
   /* everything below here will be filled according to the config file */
   unsigned int debuglevel;
   int debugport;
   char *inbound_if;
   char *outbound_if;
   char *outbound_host;
   int sip_listen_port;
   int daemonize;
   int silence_log;
   int rtp_port_low;
   int rtp_port_high;
   int rtp_timeout;
   int rtp_dscp;
   int rtp_proxy_enable;
   int rtp_input_dejitter;
   int rtp_output_dejitter;
   char *user;
   char *chrootjail;
   char *hosts_allow_reg;
   char *hosts_allow_sip;
   char *hosts_deny_sip;
   char *proxy_auth_realm;
   char *proxy_auth_passwd;
   char *proxy_auth_pwfile;
   stringa_t mask_host;
   stringa_t masked_host;
   char *outbound_proxy_host;
   int  outbound_proxy_port;
   stringa_t outbound_proxy_domain_name;
   stringa_t outbound_proxy_domain_host;
   stringa_t outbound_proxy_domain_port;
   char *registrationfile;
   char *pid_file;
   int  default_expires;
   int  autosave_registrations;
   char *ua_string;
   int   use_rport;
   int   obscure_loops;
   char *plugin_dir;
   stringa_t load_plugin;
   int   sip_dscp;
   int   tcp_timeout;
   int   tcp_connect_timeout;
   int   tcp_keepalive;
   int   thread_stack_size;
};

/*
 * control structure for config file parser
 */
typedef struct {
   int  int4;
   char *string;
} defval_t;
typedef struct {
   char *keyword;
   enum type {TYP_INT4, TYP_STRING, TYP_FLOAT, TYP_STRINGA} type;
   void *dest;
   defval_t defval;
} cfgopts_t;

/*
 * SIP ticket
 */
typedef struct {
   char *raw_buffer;		/* raw UDP packet */
   int  raw_buffer_len;		/* length of raw data */
   osip_message_t *sipmsg;	/* SIP */
   struct sockaddr_in from;	/* received from */

   struct sockaddr_in to;	/* received to */

#define PROTO_UNKN -1
#define PROTO_UDP  1
#define PROTO_TCP  2
   int protocol;		/* received by protocol */
#define DIRTYP_UNKNOWN		0
#define REQTYP_INCOMING		1
#define REQTYP_OUTGOING		2
#define RESTYP_INCOMING		3
#define RESTYP_OUTGOING		4
   int direction;		/* direction as determined by proxy */
   int index;        /* urlmap中对应的索引 */

#ifdef SUPPORT_ALG_PRIVILEGE_USER
   int tos;
#endif /* SUPPORT_ATP_DT_QOS */

   int readfd;
} sip_ticket_t;


/*
 * Client_ID - used to identify the two sides of a Call when one
 * call is routed twice (in->out and back out->in) through siproxd
 * e.g. local UA1 is calling local UA2 via an external Registrar
 */
#define CLIENT_ID_SIZE	128
typedef struct {
   char    idstring[CLIENT_ID_SIZE];
   struct  in_addr from_ip;
   /*... maybe more to come ...*/
} client_id_t;


/*
 * Function prototypes
 */

/*				function returns STS_* status values     vvv */

/* sock.c */
int sipsock_listen(void);						/*X*/
//int sipsock_wait(void);

#ifdef SUPPORT_ALG_PRIVILEGE_USER
int sipsock_waitfordata(char *buf, size_t bufsize,
                        struct sockaddr_in *from, int *protocol, int *tos, int *readfd);
#else
int sipsock_waitfordata(char *buf, size_t bufsize,
                        struct sockaddr_in *from, int *protocol, int *readfd);
#endif


void sipalg_rtpsock_setopt(int sock, int t_online, int direct, int tos, int type);


#ifdef SUPPORT_ALG_PRIVILEGE_USER
int sipsock_send(struct in_addr addr, int port, int protocol,
                 char *buffer, int size, int t_online, int direct, int tos, int index);
#else
int sipsock_send(struct in_addr addr, int port, int protocol,
                 char *buffer, size_t size, int direct, int index);
#endif

int sockbind(struct in_addr ipaddr, int localport, int protocol, int errflg, int sockflag);

int tcp_find(struct sockaddr_in dst_addr);

/* register.c */
void register_init(void);
#ifndef SUPPORT_ATP_SIPROXYD
void register_save(void);
#endif
int  register_client(sip_ticket_t *ticket, int force_lcl_masq);		/*X*/
void register_agemap(void);
int  register_response(sip_ticket_t *ticket, int flag);			/*X*/
int  register_set_expire(sip_ticket_t *ticket);				/*X*/
/* proxy.c */
int proxy_request (sip_ticket_t *ticket);				/*X*/
int proxy_response (sip_ticket_t *ticket);				/*X*/
int proxy_rewrite_invitation_body(sip_ticket_t *ticket, int direction); /*X*/
int proxy_rewrite_request_uri(osip_message_t *mymsg, int idx);		/*X*/
int proxy_rewrite_useragent(sip_ticket_t *ticket);			/*X*/

/* route_processing.c */
int route_preprocess(sip_ticket_t *ticket);				/*X*/
int route_add_recordroute(sip_ticket_t *ticket);			/*X*/
int route_purge_recordroute(sip_ticket_t *ticket);			/*X*/
int route_postprocess(sip_ticket_t *ticket);				/*X*/
int route_determine_nexthop(sip_ticket_t *ticket,
                            struct in_addr *dest, int *port);		/*X*/

/* utils.c */
int  get_ip_by_host(char *hostname, struct in_addr *addr);		/*X*/
void secure_enviroment (void);
int  get_ip_by_ifname(char *ifname, struct in_addr *retaddr);		/*X*/
int  get_interface_ip(int interface, struct in_addr *retaddr);		/*X*/
int  get_interface_real_ip(int interface, struct in_addr *retaddr);	/*X*/
char *utils_inet_ntoa(struct in_addr in);
int  utils_inet_aton(const char *cp, struct in_addr *inp);
int  createpidfile(char *pidfilename);					/*X*/
int  compare_client_id(client_id_t cid1, client_id_t cid2);		/*X*/
int  VerifyHostIPFormat( char* pValue );


/* sip_utils.c */
osip_message_t * msg_make_template_reply (sip_ticket_t *ticket, int code);
int  check_vialoop (sip_ticket_t *ticket);				/*X*/
int  is_via_local (osip_via_t *via);					/*X*/
int  compare_url(osip_uri_t *url1, osip_uri_t *url2);			/*X*/
int  compare_callid(osip_call_id_t *cid1, osip_call_id_t *cid2);	/*X*/
int  is_sipuri_local (sip_ticket_t *ticket);				/*X*/
int  sip_gen_response(sip_ticket_t *ticket, int code);			/*X*/
int  sip_add_myvia (sip_ticket_t *ticket, int interface);		/*X*/
int  sip_del_myvia (sip_ticket_t *ticket);				/*X*/
int  sip_rewrite_contact (sip_ticket_t *ticket, int direction);		/*X*/
int  sip_calculate_branch_id (sip_ticket_t *ticket, char *id);		/*X*/
int  sip_find_outbound_proxy(sip_ticket_t *ticket, struct in_addr *addr,
                             int *port);				/*X*/
int  sip_find_direction(sip_ticket_t *ticket, int *urlidx);		/*X*/
int  sip_fixup_asterisk(char *buff, size_t *buflen);			/*X*/
int  sip_obscure_callid(sip_ticket_t *ticket);				/*X*/
int  sip_add_received_param(sip_ticket_t *ticket);			/*X*/
int  sip_get_received_param(sip_ticket_t *ticket,
                            struct in_addr *dest, int *port);		/*X*/

#ifdef SUPPORT_ALG_PRIVILEGE_USER
int is_t_online(osip_message_t *msg, int ind_urlmap);
#endif /* SUPPORT_ATP_DT_QOS */

/* readconf.c */
int  read_config(char *name, int search, cfgopts_t cfgopts[], char *filter); /*X*/

/* rtpproxy.c */
int  rtpproxy_init( void );						/*X*/
#ifdef SUPPORT_ALG_PRIVILEGE_USER
int rtp_start_fwd (osip_call_id_t *callid, client_id_t client_id,
                   int direction, int call_direction, int media_stream_no,
                   struct in_addr local_ipaddr, int *local_port,
                   struct in_addr remote_ipaddr, int remote_port,
                   int isrtp,
                   int t_online,
                   int wan_port);
#else
int rtp_start_fwd (osip_call_id_t *callid, client_id_t client_id,
                   int direction, int call_direction, int media_stream_no,
                   struct in_addr local_ipaddr, int *local_port,
                   struct in_addr remote_ipaddr, int remote_port,
                   int isrtp,
                   int wan_port);
#endif

int  rtp_stop_fwd (osip_call_id_t *callid, int direction, int wan_port);		/*X*/

/* accessctl.c */
int  accesslist_check(struct sockaddr_in from);
int  process_aclist (char *aclist, struct sockaddr_in from);

/* security.c */
int  security_check_raw(char *sip_buffer, size_t size);			/*X*/
int  security_check_sip(sip_ticket_t *ticket);				/*X*/

/* auth.c */
int  authenticate_proxy(osip_message_t *sipmsg);			/*X*/
int  auth_include_authrq(osip_message_t *sipmsg);			/*X*/
void CvtHex(unsigned char *hash, unsigned char *hashstring);

/* fwapi.c */
int fwapi_start_rtp(int rtp_direction,
                    struct in_addr local_ipaddr, int local_port,
                    struct in_addr remote_ipaddr, int remote_port);
int fwapi_stop_rtp(int rtp_direction,
                   struct in_addr local_ipaddr, int local_port,
                   struct in_addr remote_ipaddr, int remote_port);

#if defined(SUPPORT_ATP_SIPPXY_RECORDDSTIP)
#define SYS_IP_LENGTH                   16
#define SYS_IP_BYTE_FOUR                3
#define SYS_BASE_DEC                    10
#define SYS_IP_MAX_NUMBER               255
#define SYS_IP_BYTE                     4
struct SipRouteInfoItem
{
    struct in_addr daddr;
    uint16_t  dport;
    uint32_t  proto;
    char *call_id;
    int call_id_len;
};

int getPrxoyDstIp(const osip_message_t *sipMsg, struct in_addr *dstIp);
int ValidateIpAddress(const char *pcIpAddr);
#endif


/* sip_layer.c */
int sip_message_parse(osip_message_t * sip,    const char *buf, size_t len);
int sip_message_to_str(osip_message_t * sip,   char **dest,     size_t *len);
int sip_body_to_str(const osip_body_t * body,  char **dest,     size_t *len);
int sip_message_set_body(osip_message_t * sip, const char *buf, size_t len);

/* plugins.c */
int load_plugins (void);
int call_plugins(int stage, sip_ticket_t *ticket);
int unload_plugins(void);

/*
 * some constant definitions
 */
#define SIP_PORT	5060	/* default port to listen */
#define DEFAULT_MAXFWD	70	/* default Max-Forward count */
#define DEFAULT_EXPIRES	3600	/* default Expires timeout */

#define TCP_IDLE_TO	300	/* TCP connection idle timeout in seconds */
#define TCP_CONNECT_TO	500	/* TCP connect() timeout in msec */

#ifdef SUPPORT_ATP_SIPROXYD
#define URLMAP_SIZE	16	/* number of URL mapping table entries	*/
#else
#define URLMAP_SIZE	128	/* number of URL mapping table entries	*/
				/* this limits the number of clients!	*/
#endif

#define SOURCECACHE_SIZE 256	/* number of return addresses		*/
#define DEJITTERLIMIT	1500000	/* max value for dejitter configuration */

#define RTPPROXY_SIZE	256	/* number of rtp proxy entries		*/
				/* this limits the number of calls!	*/

#define BUFFER_SIZE	8196	/* input buffer for read from socket	*/
#define RTP_BUFFER_SIZE	1520	/* max size of an RTP frame		*/
				/* (assume approx one Ethernet MTU)	*/

#define PATH_STRING_SIZE 256	/* max size of an file path		*/
#define URL_STRING_SIZE	128	/* max size of an URL/URI string	*/
#define STATUSCODE_SIZE	5	/* size of string representation of status */
#define DNS_CACHE_SIZE	256	/* number of entries in internal DNS cache */
#define DNS_ATTEMPTS	3	/* number of attempts to resolve a name
				   before it is marked as bad */
#define DNS_GOOD_AGE	60	/* maximum age of a good cache entry (sec) */
#define DNS_BAD_AGE	600	/* maximum age of a bad cache entry (sec) */
#define IFADR_CACHE_SIZE 32	/* number of entries in internal IFADR cache */
#define IFADR_MAX_AGE	5	/* max. age of the IF address cache (sec) */
#define IFNAME_SIZE	16	/* max string length of a interface name */
#define HOSTNAME_SIZE	128	/* max string length of a hostname	*/
#define USERNAME_SIZE	128	/* max string length of a username (auth) */
#define PASSWORD_SIZE	128	/* max string length of a password (auth) */
#define IPSTRING_SIZE	16	/* stringsize of IP address xxx.xxx.xxx.xxx */
#define VIA_BRANCH_SIZE	128	/* max string length for via branch param */
				/* scratch buffer for gethostbyname_r() */

#if defined(PR_NETDB_BUF_SIZE)
   #define GETHOSTBYNAME_BUFLEN PR_NETDB_BUF_SIZE 
#else
   #define GETHOSTBYNAME_BUFLEN 1024
#endif

/* constants for security testing */
#define SEC_MINLEN	16	/* minimum received length */
#define SEC_MAXLINELEN	2048	/* maximum acceptable length of one line
				   in the SIP telegram (security check)
				   Careful: Proxy-Authorization lines may
				   get quite long */

/* symbols for access control */
#define ACCESSCTL_SIP	1	/* for access control - SIP allowed	*/
#define ACCESSCTL_REG	2	/* --"--              - registr. allowed */

/* symbolic return stati */
#define STS_SUCCESS	0	/* SUCCESS				*/
#define STS_TRUE	0	/* TRUE					*/
#define STS_FAILURE	1	/* FAILURE				*/
#define STS_FALSE	1	/* FALSE				*/
#define STS_NEED_AUTH	1001	/* need authentication			*/
#define STS_SIP_SENT	2001	/* SIP packet is already sent, end of dialog */

/* symbolic direction of data */
#define DIR_INCOMING	1
#define DIR_OUTGOING	2

/* Interfaces */
#define IF_OUTBOUND 0
#define IF_INBOUND  1

/* various */
#ifndef satoi
#define satoi atoi  /* used in libosips MSG_TEST_CODE macro ... */
#endif


/*
 * Macro that limits the frequency of this particular code
 * block to no faster than every 'a' seconds. Used for logging
 */
#define LIMIT_LOG_RATE(a) \
        static time_t last=0; \
        time_t now; \
        int dolog=0; \
        time(&now); \
        if ((last+(a)) <= now) {last=now; dolog=1;} \
        if (dolog)

/*
 * if the following symbol 'GPL' is defined, building siproxd will
 * include all features. If not defined, some features that will
 * conflict with a non-GPL distribution license will be disabled.
 *
 * If you wish to distribute siproxd under another license than GPL
 * (commercial License for example), contact the author to elaborate
 * the details.
 */
#define GPL
