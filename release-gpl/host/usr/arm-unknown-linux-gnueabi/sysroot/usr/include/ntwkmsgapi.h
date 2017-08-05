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



#ifndef __ATP_NTWK_MSGAPI_MSGTYPES_H__
#define __ATP_NTWK_MSGAPI_MSGTYPES_H__

#ifdef SUPPORT_ATP_CHANNEL_WLAN_GETASSOCLIST
#include "wlancmsapi.h"
#endif
VOS_UINT32 ATP_UTIL_DnsTtlListen_Reg(VOS_UINT32 ulType, const VOS_CHAR *pcDomainName);
VOS_UINT32 ATP_UTIL_DnsTtlListen_UnReg(VOS_UINT32 ulType, const VOS_CHAR *pcDomainName);

#ifdef SUPPORT_ATP_APP_CLASS_QOS
/*!
  \brief ����һ��socketfd�����ø�sockfd��markֵ�����ݸ�MARKֵ������QoS
  \param[in]  ulSockfd: ������socketfd
  \param[in]  ulMarkValue: ���õ�Markֵ
  \return �Ƿ����óɹ�
  \retval  0  ���óɹ�
  \retval -1 ����ʧ��
*/
VOS_INT32  ATP_UTIL_QosSetMark(const VOS_UINT32 ulSockfd, const VOS_UINT32 ulMarkValue);
VOS_INT32  ATP_UTIL_VoiceQosSetMark(const VOS_UINT32 ulSockfd, const VOS_UINT32 ulTosValue, const VOS_UINT32 ulMarkValue);
#endif

VOS_BOOL ATP_UTIL_MacQosGetEnable();

#define ATP_SYS_SMALL_LEN                   32
#define ATP_SYS_LARGE_LEN                   264
#define ATP_SYS_TINY_LEN                    16
#define ATP_ACTUAL_LEN_128                  128

#ifdef SUPPORT_ATP_CHANNEL_WLAN_GETASSOCLIST

/*Assoc����*/
typedef struct
{
    VOS_UINT32  ulWlInstId;/*Not used in wifi-client assoc and disassoc notify*/
    VOS_UINT32  iLeaseTime;/*Not used in wifi-client assoc and disassoc notify*/
    VOS_INT32   iWlDeviceAuth;/*Not used in wifi-client assoc and disassoc notify*/
    VOS_CHAR    InfcName[8];/*wlan interface name:wl0 or wl0.x, not in the same level of tr069 with other members*/
    VOS_CHAR    acWlDeviceName[32];/*client name*/
    VOS_CHAR    acAssocList[33];/*client mac*/
    VOS_CHAR    acAssocListIP[65];/*client IP*/
    VOS_UINT32  ulLastDataDownlinkRate; /*Rx rate*/
    VOS_UINT32  ulLastDataUplinkRate;   /*Tx rate*/
    VOS_UINT32  ulTxPktSum;    /*Tx success pkt*/
    VOS_UINT32  ulRxPktSum;    /*Rx success pkt*/
    VOS_CHAR    acAssocRssi[8];
    VOS_UINT32  ulTxBytes;
    VOS_UINT32  ulRxBytes;
#if defined(SUPPORT_ATP_UPNP_NTWKSYNC_DESC)
    VOS_CHAR    acUpTime[WLAN_12_LEN];
    VOS_CHAR    acTxRate[WLAN_12_LEN];
    VOS_CHAR    acRxRate[WLAN_12_LEN];
#endif
    VOS_CHAR    acAssocRate[16];
    VOS_CHAR    acAssocBandWidth[16];
    VOS_UINT32  ulStayTime;   /*sta on line time*/
    VOS_UINT32  ulTxPktFail;   /*Tx failed pkt*/
    VOS_UINT32  ulRxPktFail;   /*Tx failed pkt*/
    VOS_CHAR    acWlPhyType[16];   /*Sta Phy type*/
}WLAN_MSG_ASSOC_ST;


#endif

typedef struct tag_BRIDGE_AVAILABLE_INTERFACE
{
    VOS_UINT32 ulInterfaceKey;                     //�ӿ�ID��
    VOS_CHAR   acInterfaceType[ATP_SYS_SMALL_LEN]; //�ӿ�����
    VOS_CHAR   acInterfaceRef[ATP_SYS_LARGE_LEN];  //�ӿ�ȫ·��
    VOS_CHAR   X_InterfaceName[ATP_SYS_TINY_LEN];///�ӿ���,eth0.3...etc
    VOS_CHAR   X_InterfaceAlias[ATP_ACTUAL_LEN_128];//�ӿڱ���
    VOS_UINT32 ulFlag;                             //��ʵ������������ֻ��ʵ�����������κ�һ���Ǳ��ڶ��ζ��Ż������������
} ATP_BRIDGE_AVAILABLE_INTERFACE_ST;               //��ǰ���õ�LAN��WAN�ӿ�

//InternetGatewayDevice.Layer2Bridging.Filter.{i}
VOS_UINT32 ATP_BRIDGE_FilterGetBridgeKeyByInterfaceKey(const VOS_UINT32 ulByInfKey, VOS_INT32 *plBridgeKey);

//InternetGatewayDevice.Layer2Bridging.AvailableInterface.{i}
VOS_UINT32 ATP_BRIDGE_GetAIFByInterfaceName(const VOS_CHAR *acIntfName, ATP_BRIDGE_AVAILABLE_INTERFACE_ST *pstAIF);

/*!
  \brief ����Eth�ڵ����ֵõ��������ŵ�����
  \param[in]  *pszInfName: Eth�ӿ���
  \param[out]  plRetBridgeIntfName: �Žӿ���, br{bridgekey}
  \param[in]  iBrLen: �Žӿ�������
  \return �ɹ�����VOS_OK, ʧ�ܷ���VOS_NOK
*/
VOS_UINT32 ATP_BRIDGE_GetBridgeIntfNameByInterfaceName(const VOS_CHAR *pszInfName, VOS_CHAR * plRetBridgeIntfName, VOS_UINT32 iBrLen);

//interface Name-->AIF .interfaceKey -->Filter.BridgeKeyRef
VOS_UINT32 ATP_BRIDGE_GetBridgeKeyByInterfaceName(const VOS_CHAR *pszInfName,VOS_INT32* plRetBridgeKey);

VOS_BOOL ATP_NTWK_IsBridgeMode();

VOS_UINT32 ATP_UTIL_GetIntfType(const VOS_CHAR *pcIntf);
#ifdef SUPPORT_ATP_GUEST_NETWORK
typedef enum tagATP_GUESTNETWORKCMS_MSGTYPES_EN
{
    ATP_MSG_GUESTNETWORK_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_GUESTNETWORKCMS), // = 0x12500 = 75008
    ATP_MSG_GUESTNETWORK_HDTIMER,                 /*Ӳ����ʱ����Ϣ*/
    ATP_MSG_GUESTNETWORK_ISOLATE_ACCESSUI,
    ATP_MSG_GUESTNETWORK_GUESTWIFI_ISREADY,  /*����wifi�Ƿ�ready�¼�*/
} ATP_GUESTNETWORKCMS_MSGTYPES_EN;
#endif

#ifdef SUPPORT_ATP_CHANNEL_WLAN_GETASSOCLIST
VOS_VOID Wlan_GetAssocList(VOS_CHAR* pszInterface, VOS_UINT32 *pulAssocNum,
                                                  WLAN_MSG_ASSOC_ST *pstAssocList);
#endif
#ifdef SUPPORT_ATP_WLAN_MACFILTER_ENHANCE
VOS_BOOL  ATP_WLAN_GetMacFilterHostNameByMac(VOS_CHAR *pcInputMac, VOS_CHAR *pcOutputHostName, VOS_UINT32 ulLen);
VOS_BOOL ATP_WLAN_SetMacFilterHostNameByMac(VOS_CHAR *pcInputMac, VOS_CHAR *pcOutputHostName);
#endif
#ifdef SUPPORT_ATP_SNTP
enum ATP_SNTP_MSGTYPES_EN
{
    ATP_MSG_SNTP_SERVER = ATP_MSG_CATEGORY_DEF(ATP_MODULE_SNTP), // = 0x3B00 = 15104
    ATP_MSG_SNTP_UPDATE,
    ATP_MSG_SNTP_OLDTIME,  //ͬ���ɹ�
    ATP_MSG_SNTP_SET_TIME,
    ATP_MSG_SNTP_SYS_SUCCESS,
    ATP_MSG_SNTP_DST_CHANGE
} ;
#endif

#define ATP_SNTP_IS_SYNCED_STATUS_FILE      "/var/sntp/issyncedstatus"
#define SNTP_TIMESYNC_STATUS_FILE       "/var/sntp/timesyncstatus"

/*!
  \brief �жϵ�ǰʱ���Ƿ��Ѿ���SNTPͬ����
  \return 
  \retval VOS_TRUE  �Ѿ���ͬ��
          VOS_FALSE δ��ͬ��
*/
VOS_BOOL ATP_SNTP_HasSyncedOK();

//��ȡ��ǰʱ��ͬ��״̬
VOS_BOOL ATP_Time_HasSyncedOK();

#ifdef SUPPORT_ATP_CLAT
enum ATP_CLAT_MSGTYPES_EN
{
    ATP_MSG_CLAT_UP = ATP_MSG_CATEGORY_DEF(ATP_MODULE_CLATD), // = 0x3E00 = 15872
    ATP_MSG_CLAT_DOWN,
} ;
#endif

#ifdef SUPPORT_ATP_COMMON_CT_CLEAN
#include "commonctcleanmsgapi.h"
#endif

#ifdef SUPPORT_ATP_DNS_PRESERVE
#define ATP_DNS_DOMAINLIST_DIR         "/data/dns/"
#define ATP_DNS_DOMAINLIST_FILE_NAME   "domainlist"
#define ATP_DNS_DOMAINLIST_FILE        "/var/dnsdomainlist"
#define ATP_DNS_DOMAINLIST_ORIG        "/etc/domainlist"
#endif

#ifdef SUPPORT_ATP_DPI
#define ATP_QOS_DPIRULE_HOTA_DEVICE_NAME      "dpirule"
#define ATP_QOS_DPIRULE_FILE_NAME       "dpirule.tar"
#define ATP_QOS_DPIRULE_OTA_PATH       "/data/dpirule/"
#endif
typedef struct tagIPCHECK_IPINFO_ST
{ 
    struct tagIPCHECK_IPINFO_ST  *pstNext;
    const VOS_CHAR *pcipInfo;
} IPCHECK_IPINFO_ST;
VOS_UINT32 ATP_IPCHECK_HostInfoGetByAccessType(const VOS_CHAR *pcAccessType, VOS_CHAR **pcIpAddr);
#endif
