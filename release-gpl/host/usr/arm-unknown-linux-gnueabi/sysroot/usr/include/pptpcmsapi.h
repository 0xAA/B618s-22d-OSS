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

#ifndef __PPTP_CMS_API_H__
#define __PPTP_CMS_API_H__

//#include "atputil.h"
#include "pptpcms.h"


#define ATP_CBBID_PPPD_NAME            "pppc"

#define ATP_CBBID_PPTPCMS_NAME         "pptp"

/* �ַ������볤�� */
#define ATP_PPTP_PAD  4

#define PPTP_STR_LEN_64                (64 + ATP_PPTP_PAD)
#define PPTP_STR_LEN_128               (128 + ATP_PPTP_PAD)
#define PPTP_STR_LEN_256               (256 + ATP_PPTP_PAD)
#define PPTP_IPADDR_LEN                (16 + ATP_PPTP_PAD)
#define PPTP_WAN_STATUS_LEN             32
#define PPTP_WAN_IFC_LEN                32
#define PPTP_VPNFILE_LEN                64
#define PPTP_CONN_MODE_LEN              8


#define PPTP_PPP_IFC_NAME               "ppp0"

/*PPTP GMSG��Ϣ*/
typedef enum
{
    PPTP_GMSG_GET_ERROR = 1,
};

/*PPTP����GMSG�Ĵ�����*/
typedef enum
{
    /*δ֪����*/
    ATP_PPTP_DIAG_ERR_UNKNOWN,
    /*�û��������������*/
    ATP_PPTP_DIAG_ERR_AUTH_FAIL,
    /*�������ӳɹ�*/
    ATP_PPTP_DIAG_ERR_NONE,
};

/*PPTP����GMSG�Ĵ������Ӧ�Ĵ�����Ϣ����*/
#define ATP_PPTP_ERR_CODE_STR_UNKNOWN        "Unknown"                      /*δ֪����*/
#define ATP_PPTP_ERR_CODE_STR_AUTH_FAIL      "ERROR_AUTHENTICATION"  /*�û��������������*/
#define ATP_PPTP_ERR_CODE_STR_NONE           "ERROR_NONE"                   /*�������ӳɹ�*/


/*ʹ�ýϴ��ppp����,�����������WAN��ͻ,*/

typedef struct _ATP_PPTP_LAC
{
    VOS_BOOL bEnable;//�Ƿ�ʹ��PPTP�������
    VOS_BOOL bMppeEnable;//�Ƿ���MPPE���ܹ���
    VOS_CHAR acServerAddr[PPTP_STR_LEN_256];//PPTP��������ַ,ip������
    VOS_CHAR acTunnleAddr[PPTP_STR_LEN_256];//PPTP�ͻ��˻�ȡ�������ַ
    VOS_CHAR acGateWay[PPTP_IPADDR_LEN];//������pptp������ppp�ĶԶ�IP,Ҳ���Լ���gateway
    VOS_CHAR acVpnFileName[PPTP_VPNFILE_LEN];//vpn�����ļ��Ͳ���������
    VOS_CHAR acWanIfc[PPTP_STR_LEN_128]; //������WAN��IP��ΪԴIP
    VOS_CHAR acPppUser[PPTP_STR_LEN_64];//�����Լ���PPP����ʱ���û���
    VOS_CHAR acPppPass[PPTP_STR_LEN_64];//�����Լ���PPP����ʱ������
    VOS_CHAR acConnStatus[PPTP_WAN_STATUS_LEN];//�����Լ�����ppp ����״̬ 
    VOS_BOOL ulInited; //�Ƿ������˽���
    VOS_CHAR acConnMode[PPTP_CONN_MODE_LEN];//�����Լ�����ppp ����ģʽ,Auto/Manual�Զ����ֶ�
    VOS_BOOL ulFireWallInited; //�Ƿ����·�ɼ�����ǽ����
    VOS_CHAR acInterFaceName[PPTP_WAN_IFC_LEN];    //����WAN�Ľӿ���
    VOS_CHAR acDefaultGW[PPTP_IPADDR_LEN];   //����WAN ��Ĭ�����ص�ַ
    VOS_CHAR acPPTPIfcName[PPTP_PPP_IFC_LEN];
    VOS_CHAR acPrimDns[ATP_SYS_IPADDR_LEN];     // ��DNS, �ֶ����õ�DNS Server
    VOS_CHAR acSecDns[ATP_SYS_IPADDR_LEN];      // ��DNS, �ֶ����õ�DNS Server
    VOS_CHAR acDnsServer[ATP_STRING_LEN_32];    // ppp Э�̽׶λ�õ�DNS Server
    VOS_BOOL ulWanConfigured;
}ATP_PPTP_LAC;

#if defined(__cplusplus)
extern "C" {
#endif

extern VOS_BOOL ATP_PPTP_GetEnable(VOS_VOID);


VOS_VOID ATP_PPTP_GetPPTPServerAddr(VOS_CHAR* pszServer, VOS_UINT32 ulLen);

/*!
  \brief PPTP VPN��ʼ������
  \param[in] VOS_VOID: 
  \return 
  \retval VOS_OK/VOS_NOK
*/
VOS_UINT32  ATP_PPTP_Init(VOS_VOID);

/*!
  \brief ȥ��ʼ��
  \param[in] VOS_VOID: 
  \return 
  \retval VOS_OK/VOS_NOK
*/
VOS_UINT32  ATP_PPTP_UnInit(VOS_VOID);

/*!
  \brief WANɾ��ʱ��Ҳɾ������WAN�ϵ�PPTP����
  \param[in]  pszWanPath: WAN·����
  \param[in]  *pvHook: ��WANģ��ע����ͳһ���壬��ʱû�õ�
  \return 
  \retval VOS_OK
*/
VOS_UINT32 ATP_PPTP_WanRuleClear(VOS_VOID* pszWanPath, VOS_VOID *pvHook);

/*!
  \brief WAN ����UPʱ����ЧPPTP����
  \param[in]  pszWanPath: ·����
  \param[in]  *pvHook: ��WANģ��ע����ͳһ���壬��ʱû�õ�
  \return 
  \retval VOS_OK
*/
VOS_UINT32 ATP_PPTP_WanRuleStart(VOS_VOID* pszWanPath, VOS_VOID *pvHook);

/*!
  \brief WAN ����Down��ʱ��ȥ��ЧPPTP����
  \param[in]  pszWanPath: ·����
  \param[in]  *pvHook: ��WANģ��ע����ͳһ���壬��ʱû�õ�
  \return 
  \retval VOS_OK
*/
VOS_UINT32 ATP_PPTP_WanRuleStop(VOS_VOID* pszWanPath, VOS_VOID *pvHook);

VOS_BOOL ATP_PPTP_IsUp(VOS_VOID);

ATP_PPTP_LAC* ATP_PPTP_GetInfo(VOS_VOID);

/*PPTP UP/DOWN Notify*/
VOS_UINT32 ATP_PPTP_Up_NotifyRegisterEx(AtpNotifierProc pfProc, VOS_UINT32 ulPriority,
                                            VOS_VOID *pvNotifyHook);
VOS_UINT32 PPTPUpNotifierDoNotify(VOS_CHAR * pszWanPath);
#define ATP_PPTP_Up_NotifyRegister(pfProc, ulPriority, pvNotifyHook) ATP_PPTP_Up_NotifyRegisterEx(FUNCTION_POINTER(pfProc), ulPriority, pvNotifyHook)


VOS_UINT32 ATP_PPTP_Down_NotifyRegisterEx(AtpNotifierProc pfProc, VOS_UINT32 ulPriority,
                                            VOS_VOID *pvNotifyHook);
VOS_UINT32 PPTPDownNotifierDoNotify(VOS_CHAR* pszWanPath);
#define ATP_PPTP_Down_NotifyRegister(pfProc, ulPriority, pvNotifyHook) ATP_PPTP_Down_NotifyRegisterEx(FUNCTION_POINTER(pfProc), ulPriority, pvNotifyHook)


#if defined(__cplusplus)
}
#endif

#endif

