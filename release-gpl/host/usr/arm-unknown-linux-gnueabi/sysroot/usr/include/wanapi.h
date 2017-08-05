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

/*prefix ValidLifeTime ��Ϣ*/
#define WAN_IAPD_VALID_TIME_FILE              "/var/wan/%s/iapdvalidtime6"

/*prefix PreferredLifeTime ��Ϣ*/
#define WAN_IAPD_PREFER_TIME_FILE             "/var/wan/%s/iapdprefertime6"

/*iana addr  ��Ϣ*/
#define WAN_IANA_ADDR_FILE                    "/var/wan/%s/ianaaddr6"

/*iana addr ValidLifeTime ��Ϣ*/
#define WAN_IANA_VALID_TIME_FILE              "/var/wan/%s/ianavalidtime6"

/*iana addr PreferredLifeTime ��Ϣ*/
#define WAN_IANA_PREFER_TIME_FILE             "/var/wan/%s/ianaprefertime6"

/*ra prefix��Ϣ*/
#define WAN_RA_PREFIX_FILE                    "/var/wan/%s/raprefix6"

/*ra prefix ValidLifeTime ��Ϣ*/
#define WAN_RA_PREFIX_VALID_TIME_FILE         "/var/wan/%s/raprefixvalidtime6"

/*ra prefix PreferredLifeTime ��Ϣ*/
#define WAN_RA_PREFIX_PREFER_TIME_FILE        "/var/wan/%s/raprefixprefertime6"

/*RA��� Managed Flag*/
#define WAN_RA_M_FLAG_FILE                    "/var/wan/%s/M_flag"
/*RA��� Other Flag*/
#define WAN_RA_O_FLAG_FILE                    "/var/wan/%s/O_flag"
/*RA��� router prefer flag*/
#define WAN_RA_ROUTER_PREFER_FLAG_FILE        "/var/wan/%s/rarouterprefer_flag"
/*RA��� router life time*/
#define WAN_RA_ROUTER_LIFETIME_FILE           "/var/wan/%s/rarouterlifetime"

/*ipv6 ״̬��Ϣ*/
#define WAN_STATUS6_FILE                    "/var/wan/%s/status6"

/* Ĭ������ */
#define WAN_GW6_FILE                        "/var/wan/%s/gateway6"

/* IP��ַ�б� */
#define WAN_IPADDR6_FILE                    "/var/wan/%s/ipaddr6"

/* DHCP DNS �ļ� */
#define WAN_DHCPC6_DNS                      "/var/wan/%s/dhcpdns6"

/* DHCP6C DUID�ļ� */
#define WAN_DHCP6C_DUID                      "/var/wan/%s/dhcp6cduid"


/* �ӿ������� */
#define ATP_PPPC_IFC_LEN  32
/* �ӿ������� */
#define ATP_PPPC_DEV_LEN  32
/* �û������� */
#define ATP_PPPC_USER_LEN  132
/* ���볤�� */
#define ATP_PPPC_PASSWD_LEN  132
/* ���б��� */
#define ATP_PPPC_BIND_LEN  64
/*AT����ָ���*/
#define ATP_PPPC_DIALNUMBER_LEN  32
/*APN���ó���*/
#define ATP_PPPC_SETAPN_LEN  32
/* DNS�б��� */
#define ATP_PPPC_DNS_LEN  64

/* ���һ������ʧ����Ϣ���� */
#define ATP_PPPC_ERROR_LEN  64

/* IP��ַ���� */
#define ATP_PPPC_IPADDR_LEN  16

#define WAN_PPP_SESSION_LEN 32

#define ATP_PPPOE_SERVICENAME_LEN  258
#define ATP_PPPOE_ACNAME_LEN  258

/* MAC��ַ���� */
#define ATP_PPPC_MAC_LEN  32
/* �������� */
#define ATP_PPPC_SERVICELIST_LEN  32
#ifndef ATP_MSG_CATEGORY_DEF
#define ATP_MSG_CATEGORY_DEF(x)          (((x) & 0xFFF) << 8)
#endif
enum ATP_WANCMS_MSGTYPES_EN
{
    ATP_MSG_WANCMS_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_WANCMS), // = 0x6800 = 26624  
    ATP_MSG_WAN_SBB_SYSLOG_WAN_UP, /*SBB SYSLOG wan up��Ϣ*/
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
    ATP_LED_WAN_BRIDGE_MODE_STATUS = 1000,		/*BRIDGE WANģʽ*/
};

/* Э������ */
typedef enum
{
    /* PPPOE���� */
    ATP_PPPC_PROTOCOL_PPPOE,
    /* PPPOA��LLCģʽ */
    ATP_PPPC_PROTOCOL_PPPOA_LLC,
    /* PPPOA��VCģʽ */
    ATP_PPPC_PROTOCOL_PPPOA_VC,
    /* PPP���� */
    ATP_PPPC_PROTOCOL_PPP_DIALUP,
    /* PPPOE2A */
    ATP_PPPC_PROTOCOL_PPPOE2A,
    /*L2TP�����PPP����*/
    ATP_PPPC_PROTOCOL_L2TP,
}ATP_PPPC_PROTOCOL_EN;

/* ��֤��ʽ */
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
    /* ����ģʽ */
    VOS_CHAR acConnTrigger[ATP_BUFFER_16];
    /* �������� */
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
    /*���󲦺ŵ�WAN·��*/
    VOS_CHAR acDialPath[ATP_BUFFER_128];
    /*ʵ�������ӵ�WAN·��*/
    VOS_CHAR acSharePath[ATP_BUFFER_128];
    /*״̬���Ͽ���������*/
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

/* ���ò����ṹ */
typedef struct
{
    /* PPP�ӿ��� */
    char acInterface[ATP_BUFFER_32];
    /* PPP�ӿ��� */
    char acDevice[ATP_BUFFER_32];
    /* �����û��� */
    char acUserName[ATP_PPPC_USER_LEN];
    /* ���� */
    char acPassWord[ATP_PPPC_PASSWD_LEN];
    /* ���б� */
    char acBindList[ATP_BUFFER_64];
    /* �󶨹��ܱ�ʶ */
    unsigned char ucBindEnable;
    /* �����ܱ�ʶ */
    unsigned char ucProxyEnable;
    /* ��������û��� */
    unsigned char ucProxyNum;
    /* Э������ */
    unsigned char ucProtocol;
    /* ���Կ��� */
    unsigned char ucDebugEnable;
    /* ���� */
    unsigned char aucReserved[3];
    char acPppSessid[ATP_BUFFER_32];
	/************ATPV1R2C03 �·���������д������****************/
    /*��֤��ʽ*/
    unsigned int ulAuth;
    /*���貦�ſ���ʱ��*/
    unsigned int ulIdleTime;
         /*B300 ����*/
    unsigned int ulRandomDialInterval;  //PPPOE��ʼ����ǰ����ȴ�ʱ������ֵ��
    unsigned int ulRetryDialInterval;  //PPPOE����ʧ�ܺ�ȴ���ʱ������
    unsigned int ulRetrySendTimes;     //PPPOEһ�β������Դ���
    unsigned int ulRetrySendInterval;  //PPPOEһ�β������Լ��
    unsigned int ulKeepAliveInterval;  //LCP����ʱ����
    unsigned int ulRetryTimes; //LCP��������ʧ�ܴ����޸�
#ifdef SUPPORT_ATP_WIRELESS
	/*AT����ָ��*/
	char acDialNumber[ATP_PPPC_DIALNUMBER_LEN];
	/*����APN*/
	char acSetApn[ATP_PPPC_SETAPN_LEN];
#endif
    unsigned int ulMaxMru;
#ifdef SUPPORT_ATP_MTU
    /* ���MTU */
    unsigned int ulMaxMtu;
#endif
    int iReqTime;
     /************ATPV1R2C03 �·���������д������****************/
     /*VHG���� pppoe service name*/
    char acPppoeServiceName[ATP_PPPOE_SERVICENAME_LEN];
    char acPppoeAcName[ATP_PPPOE_ACNAME_LEN];
    /* ��̫������PPPOA��MAC��ַ */
    char acPppoe2aMacAddr[ATP_PPPC_MAC_LEN];
    /* ��̫������PPPOA�ĻỰID */
    unsigned int ulPppoe2aSid;

    /* �Ƿ�����IPv4���� */
    unsigned int ulIpv4;
    /* �Ƿ�����IPv6���� */
    unsigned int ulIpv6;
    /* IPv6�����ַ���ͣ���IANA��IAPD */
    unsigned int ulManagedAddress;

    unsigned int ulPvcSearchTime;
    char acServiceList[ATP_PPPC_SERVICELIST_LEN];
    char acRequestIP[ATP_PPPC_IPADDR_LEN];
}ATP_PPPC_CONFIG_ST;

#endif // End of __ATP_WANCMS_MSGTYPES_H__

