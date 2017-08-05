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



#ifndef __ATP_WANCMS_MSGTYPES_H__
#define __ATP_WANCMS_MSGTYPES_H__

#define ATP_CBBID_WANCMS_NAME "wan"

#define ATP_REDIRECT_ADD  "add"
#define ATP_REDIRECT_CANCEL "cancel"
#define WAN_IAPD_PREFIX_FILE                   "/var/wan/%s/iapdprefix6"

/*prefix ValidLifeTime 信息*/
#define WAN_IAPD_VALID_TIME_FILE              "/var/wan/%s/iapdvalidtime6"

/*prefix PreferredLifeTime 信息*/
#define WAN_IAPD_PREFER_TIME_FILE             "/var/wan/%s/iapdprefertime6"

/*iana addr  信息*/
#define WAN_IANA_ADDR_FILE                    "/var/wan/%s/ianaaddr6"

/*iana addr ValidLifeTime 信息*/
#define WAN_IANA_VALID_TIME_FILE              "/var/wan/%s/ianavalidtime6"

/*iana addr PreferredLifeTime 信息*/
#define WAN_IANA_PREFER_TIME_FILE             "/var/wan/%s/ianaprefertime6"

/*ra prefix信息*/
#define WAN_RA_PREFIX_FILE                    "/var/wan/%s/raprefix6"

/*ra prefix ValidLifeTime 信息*/
#define WAN_RA_PREFIX_VALID_TIME_FILE         "/var/wan/%s/raprefixvalidtime6"

/*ra prefix PreferredLifeTime 信息*/
#define WAN_RA_PREFIX_PREFER_TIME_FILE        "/var/wan/%s/raprefixprefertime6"

/*RA里的 Managed Flag*/
#define WAN_RA_M_FLAG_FILE                    "/var/wan/%s/M_flag"
/*RA里的 Other Flag*/
#define WAN_RA_O_FLAG_FILE                    "/var/wan/%s/O_flag"
/*RA里的 router prefer flag*/
#define WAN_RA_ROUTER_PREFER_FLAG_FILE        "/var/wan/%s/rarouterprefer_flag"
/*RA里的 router life time*/
#define WAN_RA_ROUTER_LIFETIME_FILE           "/var/wan/%s/rarouterlifetime"

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


/* 接口名长度 */
#define ATP_PPPC_IFC_LEN  32
/* 接口名长度 */
#define ATP_PPPC_DEV_LEN  32
/* 用户名长度 */
#define ATP_PPPC_USER_LEN  132
/* 密码长度 */
#define ATP_PPPC_PASSWD_LEN  132
/* 绑定列表长度 */
#define ATP_PPPC_BIND_LEN  64
/*AT拨号指令长度*/
#define ATP_PPPC_DIALNUMBER_LEN  32
/*APN设置长度*/
#define ATP_PPPC_SETAPN_LEN  32
/* DNS列表长度 */
#define ATP_PPPC_DNS_LEN  64

/* 最后一次连接失败信息长度 */
#define ATP_PPPC_ERROR_LEN  64

/* IP地址长度 */
#define ATP_PPPC_IPADDR_LEN  16

#define WAN_PPP_SESSION_LEN 32

#define ATP_PPPOE_SERVICENAME_LEN  258
#define ATP_PPPOE_ACNAME_LEN  258

/* MAC地址长度 */
#define ATP_PPPC_MAC_LEN  32
/* 服务类型 */
#define ATP_PPPC_SERVICELIST_LEN  32
#ifndef ATP_MSG_CATEGORY_DEF
#define ATP_MSG_CATEGORY_DEF(x)          (((x) & 0xFFF) << 8)
#endif
enum ATP_WANCMS_MSGTYPES_EN
{
    ATP_MSG_WANCMS_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_WANCMS), // = 0x6800 = 26624  
    ATP_MSG_WAN_SBB_SYSLOG_WAN_UP, /*SBB SYSLOG wan up消息*/
} ;

enum ATP_WANCMS_SERVICE_TYPE_EN
{
    ATP_WANCMS_SERVICE = ATP_MSG_CATEGORY_DEF(ATP_MODULE_WANCMS) + 100, // = 0x6864 = 26724
};

enum ATP_LED_WAN_STATUS_EN
{
    ATP_LED_WAN_DISCONNECTED_STATUS,
    ATP_LED_WAN_CONNECTING_STATUS,
    ATP_LED_WAN_CONNECTED_STATUS,
    ATP_LED_WAN_DIAL_DISCONNECT_STATUS,
    ATP_LED_WAN_CONNECTFAILED_STATUS,
    ATP_LED_WAN_LINKUP_STATUS,
    ATP_LED_WAN_LINKDOWN_STATUS,
    ATP_LED_WAN_BRIDGE_MODE_STATUS = 1000,		/*BRIDGE WAN模式*/
};

/* 协议类型 */
typedef enum
{
    /* PPPOE拨号 */
    ATP_PPPC_PROTOCOL_PPPOE,
    /* PPPOA的LLC模式 */
    ATP_PPPC_PROTOCOL_PPPOA_LLC,
    /* PPPOA的VC模式 */
    ATP_PPPC_PROTOCOL_PPPOA_VC,
    /* PPP拨号 */
    ATP_PPPC_PROTOCOL_PPP_DIALUP,
    /* PPPOE2A */
    ATP_PPPC_PROTOCOL_PPPOE2A,
    /*L2TP里面的PPP拨号*/
    ATP_PPPC_PROTOCOL_L2TP,
}ATP_PPPC_PROTOCOL_EN;

/* 认证方式 */
typedef enum
{
    /* AUTO */
    ATP_PPPC_AUTH_AUTO,
    /* PAP */
    ATP_PPPC_AUTH_PAP,
    /*CHAP */
    ATP_PPPC_AUTH_CHAP,
}ATP_PPPC_AUTH_EN;


#ifdef SUPPORT_ATP_DHCP_SPOOF
typedef struct tagATP_WAN_BRIDGEMODE_CONFIG_ST
{
    /* 拨号模式 */
    VOS_CHAR acConnTrigger[ATP_BUFFER_16];
    /* 拨号类型 */
    VOS_CHAR acConnType[ATP_BUFFER_16];
}ATP_WAN_BRIDGEMODE_CONFIG_ST;
#endif

typedef struct tagATP_WAN_STATUS_INFO_ST
{
    VOS_CHAR acPath[ATP_BUFFER_128];
    VOS_UINT32 ulUpTime;
    VOS_UINT32 ulIPv4Status;
    VOS_CHAR acIPv4Addr[ATP_BUFFER_16];
    VOS_CHAR acDnsServers[ATP_BUFFER_32];
    VOS_UINT32 ulIPv6Status;
    VOS_CHAR acIPv6Addr[ATP_BUFFER_64];
    VOS_CHAR acIPv6DnsServers[ATP_BUFFER_128];
    VOS_CHAR acMacAddr[ATP_BUFFER_32];
    VOS_UINT32 ulDevType;
	VOS_CHAR acMask[ATP_BUFFER_16];
    VOS_CHAR acXServiceList[ATP_BUFFER_32];
}ATP_WAN_STATUS_INFO_ST;

typedef struct tagATP_WAN_APN_SHARE_MSG_ST
{
    /*请求拨号的WAN路径*/
    VOS_CHAR acDialPath[ATP_BUFFER_128];
    /*实际已连接的WAN路径*/
    VOS_CHAR acSharePath[ATP_BUFFER_128];
    /*状态，断开或已连接*/
    VOS_UINT32 ulStatus;
}ATP_WAN_APN_SHARE_MSG_ST;

/* PPPOA QOS */
typedef struct
{
    unsigned int ulATMQoS;
    unsigned int ulATMPeakCellRate;
    unsigned int ulATMMaximumBurstSize;
    unsigned int ulATMSustainableCellRate;
}ATP_PPPC_ATMQOS_ST;

/* 配置参数结构 */
typedef struct
{
    /* PPP接口名 */
    char acInterface[ATP_BUFFER_32];
    /* PPP接口名 */
    char acDevice[ATP_BUFFER_32];
    /* 拨号用户名 */
    char acUserName[ATP_PPPC_USER_LEN];
    /* 密码 */
    char acPassWord[ATP_PPPC_PASSWD_LEN];
    /* 绑定列表 */
    char acBindList[ATP_BUFFER_64];
    /* 绑定功能标识 */
    unsigned char ucBindEnable;
    /* 代理功能标识 */
    unsigned char ucProxyEnable;
    /* 代理最大用户数 */
    unsigned char ucProxyNum;
    /* 协议类型 */
    unsigned char ucProtocol;
    /* 调试开关 */
    unsigned char ucDebugEnable;
    /* 保留 */
    unsigned char aucReserved[3];
    char acPppSessid[ATP_BUFFER_32];
	/************ATPV1R2C03 下发进程新增写配置项****************/
    /*认证方式*/
    unsigned int ulAuth;
    /*按需拨号空闲时间*/
    unsigned int ulIdleTime;
         /*B300 新增*/
    unsigned int ulRandomDialInterval;  //PPPOE开始拨号前随机等待时间的最大值。
    unsigned int ulRetryDialInterval;  //PPPOE拨号失败后等待的时间间隔。
    unsigned int ulRetrySendTimes;     //PPPOE一次拨号重试次数
    unsigned int ulRetrySendInterval;  //PPPOE一次拨号重试间隔
    unsigned int ulKeepAliveInterval;  //LCP发送时间间隔
    unsigned int ulRetryTimes; //LCP连续发送失败次数修改
#ifdef SUPPORT_ATP_WIRELESS
	/*AT拨号指令*/
	char acDialNumber[ATP_PPPC_DIALNUMBER_LEN];
	/*设置APN*/
	char acSetApn[ATP_PPPC_SETAPN_LEN];
#endif
    unsigned int ulMaxMru;
#ifdef SUPPORT_ATP_MTU
    /* 最大MTU */
    unsigned int ulMaxMtu;
#endif
    int iReqTime;
     /************ATPV1R2C03 下发进程新增写配置项****************/
     /*VHG需求 pppoe service name*/
    char acPppoeServiceName[ATP_PPPOE_SERVICENAME_LEN];
    char acPppoeAcName[ATP_PPPOE_ACNAME_LEN];
    /* 以太网虚拟PPPOA的MAC地址 */
    char acPppoe2aMacAddr[ATP_PPPC_MAC_LEN];
    /* 以太网虚拟PPPOA的会话ID */
    unsigned int ulPppoe2aSid;

    /* 是否启用IPv4功能 */
    unsigned int ulIpv4;
    /* 是否启用IPv6功能 */
    unsigned int ulIpv6;
    /* IPv6请求地址类型，如IANA或IAPD */
    unsigned int ulManagedAddress;

    unsigned int ulPvcSearchTime;
    char acServiceList[ATP_PPPC_SERVICELIST_LEN];
    char acRequestIP[ATP_PPPC_IPADDR_LEN];
}ATP_PPPC_CONFIG_ST;

#endif // End of __ATP_WANCMS_MSGTYPES_H__

