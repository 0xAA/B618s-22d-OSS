/******************************************************************************
  *         版权所有 (C), 2001-2020, 华为技术有限公司
*******************************************************************************/
#ifndef __LOGINCONTROLAPI_H__
#define __LOGINCONTROLAPI_H__

#include "atptypes.h"
#include "msgapi.h"


typedef enum tagATP_LOGINCTRLAPI_ERR_CODE_EN
{
    ATP_ERR_LOGINCTRLAPI_INVALID_PARA = ATP_MNT_ERR_CODE_DEF(ATP_TEAM_MNT, ATP_MODULE_LIBLOGINCONTROLAPI), 
    ATP_ERR_LOGINCTRLAPI_NO_RESPONSE,    
} ATP_LOGINCTRLAPI_ERR_CODE_EN;


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
    /* 获取并设置锁定总轮数 */
    ATP_MSG_LCTRLAPI_GET_TOTAL_FORBID_ROUND,
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


/* 查询锁定轮数 */
typedef struct tag_atp_sctrl_totalfailedround_st
{
    ATP_SCTRL_SERVICE_TYPE_EN enService;    //业务名称
    VOS_BOOL bGet;                              //是否获取
    VOS_BOOL bClear;                            //是否获取后清空
}ATP_SCTRL_LOGIN_TOTALFAILEDROUND_ST;


/* 获取被锁定轮数错误码            */
typedef enum
{
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_NONE = 0,          /* 无 */
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_SUCCESS,           /* 获取成功 */
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_NOTEXIST,          /* 业务不存在 */
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_INTERNAL,          /* 内部错误 */
}ATP_SCTRL_LOGIN_FAILEDROUND_RET_EN;

/* 查询锁定轮数结果 */
typedef struct tag_atp_sctrl_totalfailedround_ret_st
{
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_EN enRet;          //错误码
    VOS_UINT32 ulTotalFailedRound;                     //锁定轮数
}ATP_SCTRL_LOGIN_TOTALFAILEDROUND_RET_ST;


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

/*!
  \ 
  \brief         登录校验,并记录信息
  \param[in]  pstLoginInfo: 
  \param[in]  pstLoginRet: 
  \return 
  \retval ERROR_CODE 错误码说明
*/
extern VOS_UINT32 ATP_LCTRLAPI_Login(ATP_SCTRL_LOGIN_INFO_ST* pstLoginInfo, ATP_SCTRL_LOGIN_RET_ST* pstLoginRet);


/*!
  \ 
  \brief         登录校验,仅试探
  \param[in]  pstLoginInfo: 
  \param[in]  pstLoginRet: 
  \return 
  \retval ERROR_CODE 错误码说明
*/
extern VOS_UINT32 ATP_LCTRLAPI_Check(ATP_SCTRL_LOGIN_INFO_ST* pstLoginInfo, ATP_SCTRL_LOGIN_RET_ST* pstLoginRet);


/* 最小失败错误次数 */
#define ATP_SCTRL_MIN_MAX_FAILED_TIMES  (3)

/*!
  \ 
  \brief         修改指定模块的最大错误次数
  \param[in]  ulMaxFailedTimes: 
  \param[in]  enService: 
  \return 
  \retval ERROR_CODE 错误码说明
*/
extern VOS_UINT32 ATP_LCTRLAPI_SetMaxFailedTimes(ATP_SCTRL_LOGIN_MAXFAILEDTIMES_SET_ST* pstMaxFailedPara);


/*!
  \ 
  \brief       清除特定模块的定时器等信息，目前主要用于假关机时清除登陆失败后一定时间内不允许登陆的定时器。
  \param[in]   enService: 清除哪种类型的forbidden列表
  \return      void
  \retval ERROR_CODE 错误码说明
*/
extern VOS_VOID ATP_LCTRLAPI_ClearForbiddenList(ATP_SCTRL_SERVICE_TYPE_EN enService);


/*****************************************************************
Parameters    :  pstSettings    业务，获取，清空
                 pstRet         锁定轮数，业务错误码
Return        :  获取消息的错误码
Description   :  获取指定业务的防爆力破解锁定轮数，支持清空
Note          :  支持清空，但需要注意的是，一旦清空，其他模块通过该接口获取的数据实际也被清空了
*****************************************************************/
extern VOS_UINT32 ATP_LCTRLAPI_GetForbiddenRound(ATP_SCTRL_LOGIN_TOTALFAILEDROUND_ST *pstSettings, ATP_SCTRL_LOGIN_TOTALFAILEDROUND_RET_ST* pstRet);

#if defined(__cplusplus)
}
#endif
    
#endif


