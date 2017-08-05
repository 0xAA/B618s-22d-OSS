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
#ifndef __LOGINCTL_H__
#define __LOGINCTL_H__
#include "atptypes.h"
#include "logincontrolapi.h"

#define LOGIN_OK	0
#define LOGIN_FAIL	1

#define LOGIN_VALID		1
#define LOGIN_INVALID		0

//#define LOGIN_DEBUG

#ifdef LOGIN_DEBUG
#define LoginDebugPrint(format, args...)       do{printf("FILE: %s FUNC: %s LINE: %d: ", __FILE__,__FUNCTION__, __LINE__);printf(format, ##args);}while(0)
#else
#define LoginDebugPrint(format, args...) 	
#endif

typedef enum ATP_LOGINRET_EN    //登录返回结果
{
    ATP_LOGINRET_OK        	= 0,   //表示该用户可继续登录
    ATP_LOGINRET_LOGINED,             //表示该用户已经登录过
    ATP_LOGINRET_TOOMANY_FAIL,           //表示当前用户登录失败次数已经超过限制次数
    ATP_LOGINRET_EXISTED,            //表示同一个用户同一个终端已经登录过一次
    
    ATP_LOGINRET_INNORMAL,         //表示不正常返回
    ATP_LOGINRET_END,
} ATP_LOGINRET_EN;

#define ATP_LOGINTYPE_REMOTE    0x8000

typedef enum ATP_LOGINTYPE_EN
{
    ATP_LOGINTYPE_NONE        	= 0,   //未知登录方式
    ATP_LOGINTYPE_FTP,             		//通过FTP 登录
    ATP_LOGINTYPE_SAMBA,          		//通过SAMBA 登录
    ATP_LOGINTYPE_FTPTIMEOUT,             		//通过FTP 登录后超时了

    ATP_LOGINTYPE_END = 0x7FFF
} ATP_LOGINTYPE_EN;
#ifdef SUPPORT_ATP_FTP_ACCESS_CONTROL
typedef enum ATP_FTPTYPE_EN
{
    ATP_FTPTYPE_NONE        	= 0,   //未知登录方式
    ATP_FTPTYPE_FTPNORMAL,          //未加密FTP连接
    ATP_FTPTYPE_FTPSEXPLICIT,       //显示加密FTP连接
    ATP_FTPTYPE_FTPSIMPLICIT,      //隐式加密FTP连接

    ATP_FTPTYPE_END
} ATP_FTPTYPE_EN;

typedef enum ATP_FROMTYPE_EN
{
    ATP_FROMTYPE_WAN        	= 0,   //wan测的连接
    ATP_FROMTYPE_LAN,                    //lan测的连接
    ATP_FROMTYPE_END
} ATP_FROMTYPE_EN;
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
VOS_UINT32 ATP_LoginCtlInit(VOS_UINT32 ulLogType);
ATP_SCTRL_LOGIN_RET_EN ATP_LoginCtlCheck(const VOS_CHAR *pszUsername ,const VOS_CHAR *pszIpAddr ,VOS_UINT32 ulLogType , 
                                                                VOS_UINT ulLogStatus);
VOS_INT32 ATP_LoginCtlLogout(const VOS_CHAR *pszUsername , const VOS_CHAR *pszAddrInfo,VOS_UINT32 ulLogintype);
VOS_INT32 ATP_LoginCtlAllowWanAcc(const VOS_CHAR *pszUsername , VOS_UINT32 ulLogintype);
#ifdef SUPPORT_ATP_FTP_ACCESS_CONTROL
VOS_INT32 ATP_LoginCtlCheckFtpAcc(const VOS_CHAR *pszUsername, VOS_UINT32 ulFtpType,VOS_UINT32 ulFromType);
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */



#endif  //end #ifndef __LOGINCTL_H__


