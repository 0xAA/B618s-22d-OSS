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

/* 字符串补齐长度 */
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

/*PPTP GMSG消息*/
typedef enum
{
    PPTP_GMSG_GET_ERROR = 1,
};

/*PPTP用于GMSG的错误码*/
typedef enum
{
    /*未知错误*/
    ATP_PPTP_DIAG_ERR_UNKNOWN,
    /*用户名或者密码错误*/
    ATP_PPTP_DIAG_ERR_AUTH_FAIL,
    /*拨号连接成功*/
    ATP_PPTP_DIAG_ERR_NONE,
};

/*PPTP用于GMSG的错误码对应的错误信息定义*/
#define ATP_PPTP_ERR_CODE_STR_UNKNOWN        "Unknown"                      /*未知错误*/
#define ATP_PPTP_ERR_CODE_STR_AUTH_FAIL      "ERROR_AUTHENTICATION"  /*用户名或者密码错误*/
#define ATP_PPTP_ERR_CODE_STR_NONE           "ERROR_NONE"                   /*拨号连接成功*/


/*使用较大的ppp号码,如果仍与其它WAN冲突,*/

typedef struct _ATP_PPTP_LAC
{
    VOS_BOOL bEnable;//是否使能PPTP隧道功能
    VOS_BOOL bMppeEnable;//是否开启MPPE加密功能
    VOS_CHAR acServerAddr[PPTP_STR_LEN_256];//PPTP服务器地址,ip或域名
    VOS_CHAR acTunnleAddr[PPTP_STR_LEN_256];//PPTP客户端获取的隧道地址
    VOS_CHAR acGateWay[PPTP_IPADDR_LEN];//网关在pptp隧道里的ppp的对端IP,也即自己的gateway
    VOS_CHAR acVpnFileName[PPTP_VPNFILE_LEN];//vpn配置文件和参数的名字
    VOS_CHAR acWanIfc[PPTP_STR_LEN_128]; //以哪条WAN的IP作为源IP
    VOS_CHAR acPppUser[PPTP_STR_LEN_64];//网关自己做PPP拨号时的用户名
    VOS_CHAR acPppPass[PPTP_STR_LEN_64];//网关自己做PPP拨号时的密码
    VOS_CHAR acConnStatus[PPTP_WAN_STATUS_LEN];//网关自己拨号ppp 连接状态 
    VOS_BOOL ulInited; //是否已起了进程
    VOS_CHAR acConnMode[PPTP_CONN_MODE_LEN];//网关自己拨号ppp 连接模式,Auto/Manual自动或手动
    VOS_BOOL ulFireWallInited; //是否加了路由及防火墙规则
    VOS_CHAR acInterFaceName[PPTP_WAN_IFC_LEN];    //所在WAN的接口名
    VOS_CHAR acDefaultGW[PPTP_IPADDR_LEN];   //所在WAN 的默认网关地址
    VOS_CHAR acPPTPIfcName[PPTP_PPP_IFC_LEN];
    VOS_CHAR acPrimDns[ATP_SYS_IPADDR_LEN];     // 主DNS, 手动设置的DNS Server
    VOS_CHAR acSecDns[ATP_SYS_IPADDR_LEN];      // 备DNS, 手动设置的DNS Server
    VOS_CHAR acDnsServer[ATP_STRING_LEN_32];    // ppp 协商阶段获得的DNS Server
    VOS_BOOL ulWanConfigured;
}ATP_PPTP_LAC;

#if defined(__cplusplus)
extern "C" {
#endif

extern VOS_BOOL ATP_PPTP_GetEnable(VOS_VOID);


VOS_VOID ATP_PPTP_GetPPTPServerAddr(VOS_CHAR* pszServer, VOS_UINT32 ulLen);

/*!
  \brief PPTP VPN初始化函数
  \param[in] VOS_VOID: 
  \return 
  \retval VOS_OK/VOS_NOK
*/
VOS_UINT32  ATP_PPTP_Init(VOS_VOID);

/*!
  \brief 去初始化
  \param[in] VOS_VOID: 
  \return 
  \retval VOS_OK/VOS_NOK
*/
VOS_UINT32  ATP_PPTP_UnInit(VOS_VOID);

/*!
  \brief WAN删掉时，也删掉这条WAN上的PPTP规则
  \param[in]  pszWanPath: WAN路径名
  \param[in]  *pvHook: 先WAN模块注册用统一定义，暂时没用到
  \return 
  \retval VOS_OK
*/
VOS_UINT32 ATP_PPTP_WanRuleClear(VOS_VOID* pszWanPath, VOS_VOID *pvHook);

/*!
  \brief WAN 连接UP时，生效PPTP规则
  \param[in]  pszWanPath: 路径名
  \param[in]  *pvHook: 先WAN模块注册用统一定义，暂时没用到
  \return 
  \retval VOS_OK
*/
VOS_UINT32 ATP_PPTP_WanRuleStart(VOS_VOID* pszWanPath, VOS_VOID *pvHook);

/*!
  \brief WAN 连接Down掉时，去生效PPTP规则
  \param[in]  pszWanPath: 路径名
  \param[in]  *pvHook: 先WAN模块注册用统一定义，暂时没用到
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

