/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 *
 * mobile@huawei.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */


#ifndef __ATP_DHCP6CCMS_MSGTYPES_H__
#define __ATP_DHCP6CCMS_MSGTYPES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define ATP_CBBID_DHCP6C_NAME                  "dhcp6c"

/* WAN连接地址类型长度 */
#define DCHP6C_ADDRTYPE_LEN 8

/* WAN路径最大长度 */
#define DCHP6C_PATH_LEN 128

/* Ipv6Enable*/
#define IPV6_DHCPV6_ENABLE_FILE_PATH       "/proc/sys/net/ipv6/conf/%s/enable"
/* WAN接口名最大长度 */
#define DCHP6C_IFC_LEN  32

#define ACCEPT_RA_FILE_PATH                 "/proc/sys/net/ipv6/conf/%s/accept_ra"

#define ACCEPT_RA_AUTOCONF_FILE_PATH        "/proc/sys/net/ipv6/conf/%s/autoconf"

#define ACCEPT_FORWARDING_FILE_PATH         "/proc/sys/net/ipv6/conf/%s/forwarding"

#define ACCEPT_RA_DLF_ROUTE_FILE_PATH       "/proc/sys/net/ipv6/conf/%s/accept_ra_defrtr"

/* DHCP 前缀信息 */
#define WAN_IAPD_PREFIX_FILE                   "/var/wan/%s/iapdprefix6"

/*prefix ValidLifeTime 信息*/
#define WAN_IAPD_VALID_TIME_FILE                   "/var/wan/%s/iapdvalidtime6"

/*prefix PreferredLifeTime 信息*/
#define WAN_IAPD_PREFER_TIME_FILE                   "/var/wan/%s/iapdprefertime6"

/*iana addr  信息*/
#define WAN_IANA_ADDR_FILE                   "/var/wan/%s/ianaaddr6"

/*iana addr ValidLifeTime 信息*/
#define WAN_IANA_VALID_TIME_FILE                   "/var/wan/%s/ianavalidtime6"

/*iana addr PreferredLifeTime 信息*/
#define WAN_IANA_PREFER_TIME_FILE                   "/var/wan/%s/ianaprefertime6"

/*ra prefix信息*/
#define WAN_RA_PREFIX_FILE                     "/var/wan/%s/raprefix6"

/*ra prefix ValidLifeTime 信息*/
#define WAN_RA_PREFIX_VALID_TIME_FILE                   "/var/wan/%s/raprefixvalidtime6"

/*ra prefix PreferredLifeTime 信息*/
#define WAN_RA_PREFIX_PREFER_TIME_FILE                   "/var/wan/%s/raprefixprefertime6"

/*RA里的 Managed Flag*/
#define WAN_RA_M_FLAG_FILE                   "/var/wan/%s/M_flag"
/*RA里的 Other Flag*/
#define WAN_RA_O_FLAG_FILE                   "/var/wan/%s/O_flag"
/*RA里的 router prefer flag*/
#define WAN_RA_ROUTER_PREFER_FLAG_FILE                   "/var/wan/%s/rarouterprefer_flag"
/*RA里的 router life time*/
#define WAN_RA_ROUTER_LIFETIME_FILE                   "/var/wan/%s/rarouterlifetime"

/*ipv6 状态信息*/
#define WAN_STATUS6_FILE                    "/var/wan/%s/status6"

/* 默认网关 */
#define WAN_GW6_FILE                        "/var/wan/%s/gateway6"

/* IP地址列表 */
#define WAN_IPADDR6_FILE                    "/var/wan/%s/ipaddr6"

/* DHCP DNS 文件 */
#define WAN_DHCPC6_DNS                      "/var/wan/%s/dhcpdns6"

/* DHCP6C DUID文件 */
#define WAN_DHCP6C_DUID                      "/var/wan/%s/dhcp6cduid"

#define DHCP6C_PIDFILE                      "/var/wan/%s/dhcp6c.pid"

#define DHCP6C_SENTOPTIONFILE               "/var/wan/%s/dhcp6csentoption"

#define DHCP6C_SENTOPTIONMAXNUM              255

//!配置参数长度
#define DHCP6C_PARA_LEN  128

//!option 长度
#define DHCP6C_OPTION_LEN  65535

#ifdef SUPPORT_ATP_TR181
//!option Tag的最小值和最大值
#define DHCP6C_OPTION_TAG_MIN 1
#define DHCP6C_OPTION_TAG_MAX 65535

//!option CodeID
  #define DH6OPT_CLIENTID	1
  #define DH6OPT_SERVERID	2
  #define DHCP6OPT_VENDOR_CLASS   16
  #define DH6OPT_IA_NA 3
  #define DH6OPT_IA_TA 4
  #define DH6OPT_IAADDR 5
  #define DH6OPT_ORO 6
  #define DH6OPT_PREFERENCE 7 
  #define DH6OPT_ELAPSED_TIME 8
  #define DH6OPT_RELAY_MSG 9
  #define DH6OPT_AUTH 11
  #define DH6OPT_UNICAST 12
  #define DH6OPT_STATUS_CODE 13
  #define DH6OPT_RAPID_COMMIT 14
  #define DH6OPT_USER_CLASS 15
  #define DH6OPT_VENDOR_CLASS 16
  #define DH6OPT_VENDOR_OPTS 17
  #define DH6OPT_INTERFACE_ID 18
  #define DH6OPT_RECONF_MSG 19

  #define DH6OPT_SIP_SERVER_D 21
  #define DH6OPT_SIP_SERVER_A 22
  #define DH6OPT_DNS 23
  #define DH6OPT_DNSNAME 24
  #define DH6OPT_IA_PD 25
  #define DH6OPT_IA_PD_PREFIX 26
  #define DH6OPT_NIS_SERVERS 27
  #define DH6OPT_NISP_SERVERS 28
  #define DH6OPT_NIS_DOMAIN_NAME 29
  #define DH6OPT_NISP_DOMAIN_NAME 30
  #define DH6OPT_NTP 31
  #define DH6OPT_REFRESHTIME 32
  #define DH6OPT_BCMCS_SERVER_D 33
  #define DH6OPT_BCMCS_SERVER_A 34
  #define DH6OPT_GEOCONF_CIVIC 36
  #define DH6OPT_REMOTE_ID 37
  #define DH6OPT_SUBSCRIBER_ID 38
  #define DH6OPT_CLIENT_FQDN 39
  #define DH6OPT_DSLITE_ADDR 80  
  #define DH6OPT_DSLITE_NAME 64

struct stDhcp6cServerInfo
{
    VOS_CHAR          acInterface[DCHP6C_IFC_LEN];        /*!< 接口名  */
    VOS_CHAR          acSourceAddress[DHCP6C_PARA_LEN];        /*!< server ip  */
    VOS_CHAR          acDUID[DHCP6C_PARA_LEN];    /*!< server duid */
    VOS_CHAR          acInformationRefreshTime[DHCP6C_PARA_LEN];    /*!< OPTION 32*/
};
  
struct stSentOptionInfo
{
    VOS_BOOL bEnable;
    VOS_UINT32 Tag;
    VOS_CHAR  acOptValue[DHCP6C_OPTION_LEN];
};

struct SentOptionListNode
{
    struct SentOptionListNode *pNext; 
    VOS_UINT32 ulInst;
    VOS_UINT32 ulSentOptionNum;
    struct stSentOptionInfo g_sentOptionList[DHCP6C_SENTOPTIONMAXNUM];    
};

typedef struct tagDHCP6C_INFO_ST
{
    struct tagDHCP6C_INFO_ST   *pstNext;

    unsigned int  ulInstId;				/*!<结点实例号. */
    
    unsigned int bEnable;                 /*!<Enables or disables this Client entry. */

    char acInterfacePath[DCHP6C_PATH_LEN] ;                            /* 接口路径名 */

    char acInterface[DCHP6C_IFC_LEN];                            /* 接口名 */

    char acStatus[DCHP6C_IFC_LEN] ;                            /*  */

    char acDUID[DHCP6C_PARA_LEN];    /*!< cliend duid */

    unsigned int bRequestAddresses;                 /*!< Enables or disables inclusion of the Identity Association (IA) for Non-Temporary Address */

    unsigned int bRequestPrefixes;                       /*!< Enables or disables inclusion of the Identity Association (IA) for Prefix Delegation */

    unsigned int bRapidCommit;                       /*!< Enables or disables inclusion of the Rapid Commit option  */

    unsigned int bRenew;                       /*!<When set to true, the Client will renew its DHCPv6-supplied information   */ 

    int   lSuggestedT1;                 /*!<T1 value, in seconds, that the client SHOULD use when sending IA optionsn   */ 

    int   lSuggestedT2;                  /*!<T2 value, in seconds, that the client SHOULD use when sending IA optionsn   */ 

    char acSupportedOptions[DHCP6C_PARA_LEN];    /*!< The options that the client is able to process in server responses   */ 

    char acRequestedOptions[DHCP6C_PARA_LEN];    /*!<An ordered list of the top-level options (i.e. not encapsulated options) that the client will explicitly request from the server.   */
    
    unsigned int ulSendOptionNum;                /*Send Option Num*/
  
} DHCP6C_INFO_ST;

struct stDhcp6cOpt
{                             
    VOS_CHAR          acInterface[DCHP6C_IFC_LEN];        /*!< 接口名  */
    VOS_UINT32        ulOptTag;        /*!< option  code */
    VOS_UINT8         acOptValue[DHCP6C_OPTION_LEN];        /*!< option  value  */
    VOS_CHAR          acServer[DHCP6C_PARA_LEN];    /*!< option server */
};

#endif

//!\brief dhcp6c消息结构体
/*!
 * 携带接口名以及命令行参数等信息给dhcp6c进程
 */
struct stDhcp6cData
{
    VOS_UINT32        ulPid;                 /*!< dhcp6c pid */
    VOS_CHAR          acInterface[DCHP6C_IFC_LEN];        /*!< 接口名  */
    VOS_CHAR          inputoptions[DHCP6C_PARA_LEN];    /*!< 配置参数信息 */
#ifdef SUPPORT_ATP_TR181
    DHCP6C_INFO_ST stDhcp6cInfo;
#endif	
};

struct stDhcp6cStatus
{
    VOS_INT32          lStatus;                 /*!< dhcp6c Status */
    VOS_CHAR          acInterface[DCHP6C_IFC_LEN];        /*!< 接口名  */
};

enum ATP_DHCP6C_MSGTYPES_EN
{
    ATP_MSG_DHCP6C_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_DHCP6CCMS),    //启动DHCP6C进程      
    ATP_MSG_DHCP6C_STOP,         //停止DHCP6C进程
    ATP_MSG_DHCP6C_INITOVER,
#ifdef SUPPORT_ATP_TR181
    ATP_MSG_DHCP6C_GET_SERVER_INFO,   
    ATP_MSG_DHCP6C_GET_OPTION_INFO,
    ATP_MSG_IPV6_STATUS_CHANGE,
    ATP_MSG_DHCP6C_SEND_OPTION_INFO,
#endif
    ATP_MSG_DHCP6C_RENEW,
    ATP_MSG_DHCP6C_INIT,
    ATP_MSG_DHCP6C_RESTART,
} ;

#ifdef SUPPORT_ATP_CWMP_IPV6
typedef struct tagATP_DHCP6C_OPTION17_MSG_ST
{
    VOS_CHAR acIfc[32];
    VOS_CHAR acUrl[256];
    VOS_UINT32 ulUrlLen;
} ATP_DHCP6C_OPTION17_MSG_ST;
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
