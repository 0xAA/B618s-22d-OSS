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
 

#ifndef __LOGINCONTROLINI_H__
#define __LOGINCONTROLINI_H__

#include "atptypes.h"
#include "msgapi.h"


enum ATP_LCTRLAPI_MSGTYPES_EN
{
    ATP_MSG_LCTRLAPI_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_LIBLOGINCONTROLAPI), // = 0x2CF00 = 184064

    /* 登录校验并记录 */
    ATP_MSG_LCTRLAPI_LOGIN, 
    /* 仅判断 */
    ATP_MSG_LCTRLAPI_CHECK,
    /* 设置参数 */
    ATP_MSG_LCTRLAPI_SET_MAXFAILEDTIMES,
    /* 清除forbidden列表 */
    ATP_MSG_LCTRLAPI_CLEAR_FORBID_LIST,
};


/*!< 校验的业务 */
typedef enum tag_atp_sctrl_service_type_en
{
    ATP_SCTRL_SERVICE_FTP = 0,
    ATP_SCTRL_SERVICE_SAMBA,
    ATP_SCTRL_SERVICE_WEB,
    ATP_SCTRL_SERVICE_CWMP,
    ATP_SCTRL_SERVICE_UPNP,
    ATP_SCTRL_SERVICE_TELNET,
    ATP_SCTRL_SERVICE_CLI,
    ATP_SCTRL_SERVICE_SSH,
    ATP_SCTRL_SERVICE_CABINET,
    ATP_SCTRL_SERVICE_TEST,    
}ATP_SCTRL_SERVICE_TYPE_EN;


/*!< 登录信息结构体 */
typedef struct tag_atp_sctrl_login_info_st
{
    ATP_SCTRL_SERVICE_TYPE_EN enService;
    VOS_CHAR    acIPAddress[64];
    VOS_CHAR    acUsername[64];
    VOS_BOOL    bSuccess;
}ATP_SCTRL_LOGIN_INFO_ST;

typedef enum
{
    ATP_SCTRL_LOGIN_RET_SUCCESS = 0,    /* 登录成功,此时ulErrorTimes和ulMaxFailTimes无效 */
    ATP_SCTRL_LOGIN_RET_FORBIDDEN,      /* 被禁止,此时ulErrorTimes和ulMaxFailTimes有效 */
    ATP_SCTRL_LOGIN_RET_FULL,           /* 链表满,此时ulErrorTimes和ulMaxFailTimes无效 */
    ATP_SCTRL_LOGIN_RET_OTHER,          /* 其他错误,如不支持的业务 */
    ATP_SCTRL_LOGIN_RET_CONTROL,        /* 处于禁用期间，导致登陆被forbidden，不含非禁用期间的账号检查失败场景。 */
}ATP_SCTRL_LOGIN_RET_EN;

/*!< 登录结果结构体 */
typedef struct tag_atp_sctrl_login_ret_st
{
    VOS_UINT32    ulErrorTimes;         /* 总错误次数 */
    VOS_UINT32    ulMaxFailTimes;       /* 每轮最大失败次数 */
    ATP_SCTRL_LOGIN_RET_EN    enRet;    /* 错误类型 */
    ATP_SCTRL_LOGIN_RET_EN    enForbiddenType;    /* 禁止类型 */
}ATP_SCTRL_LOGIN_RET_ST;


typedef struct tag_atp_sctrl_maxfailedtimes_set_st
{
    ATP_SCTRL_SERVICE_TYPE_EN enService;
    VOS_UINT32 ulMaxFailedTimes;
}ATP_SCTRL_LOGIN_MAXFAILEDTIMES_SET_ST;


/*!< 校验时回调用结构体 */
typedef struct tag_atp_sctrl_check_user_st
{
    VOS_CHAR    acUsername[66];
    VOS_CHAR    acIPAddress[64];
    ATP_SCTRL_SERVICE_TYPE_EN enService;
    VOS_INT32   lPid;
    VOS_BOOL    bIn;
    VOS_BOOL    bRemote;
    VOS_BOOL    bSuccess;
    VOS_UINT32  ulCheckMask; 
    VOS_UINT32  stTime;
}ATP_SCTRL_CHECK_USER_ST;


#if defined(__cplusplus)
extern "C"
{
#endif


extern VOS_UINT32 ATP_LCTRLAPI_Login(ATP_SCTRL_LOGIN_INFO_ST* pstLoginInfo, ATP_SCTRL_LOGIN_RET_ST* pstLoginRet);



extern VOS_UINT32 ATP_LCTRLAPI_Check(ATP_SCTRL_LOGIN_INFO_ST* pstLoginInfo, ATP_SCTRL_LOGIN_RET_ST* pstLoginRet);


/* 最小失败错误次数 */
#define ATP_SCTRL_MIN_MAX_FAILED_TIMES  (3)


extern VOS_UINT32 ATP_LCTRLAPI_SetMaxFailedTimes(ATP_SCTRL_LOGIN_MAXFAILEDTIMES_SET_ST* pstMaxFailedPara);



extern VOS_VOID ATP_LCTRLAPI_ClearForbiddenList(ATP_SCTRL_SERVICE_TYPE_EN enService);


#if defined(__cplusplus)
}
#endif
    
#endif


