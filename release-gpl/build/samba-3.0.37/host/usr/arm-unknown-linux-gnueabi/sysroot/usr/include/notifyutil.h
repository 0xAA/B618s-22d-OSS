/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file notifyutil.h
  *
  *\copyright 2017-2030，华为技术有限公司
  *\author  
  *\date  2017-6-12
  
*/
#ifndef __ATP_NOTIFY_UTIL_H__
#define __ATP_NOTIFY_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*
 * Notify utility
 */
typedef VOS_UINT32 (*AtpNotifierProc)(VOS_VOID *pvNotifier, VOS_VOID *pvNotifyHook);
typedef VOS_BOOL (*AtpNotifierPostProc)(const VOS_VOID *pvNotifier, const VOS_VOID *pvNotifyHook, VOS_UINT32 ulRetVal);
typedef VOS_BOOL (*AtpNotifierFilterProc)(const VOS_VOID *pvNotifier, const VOS_VOID *pvNotifyHook, const VOS_VOID *pvArg);

typedef struct tagATP_UTIL_NOTIFY_HOOKS_ST
{
    AtpNotifierProc                         pfPreProc;
    AtpNotifierPostProc                     pfPostProc;
    AtpNotifierFilterProc                   pfFilterProc;
    const VOS_VOID                          *pvFilterArg;
} ATP_UTIL_NOTIFY_HOOKS_ST;

typedef struct tagATP_UTIL_NOTIFY_ENTRY_ST
{
    struct tagATP_UTIL_NOTIFY_ENTRY_ST      *pstNext;
    AtpNotifierProc                         pfProc;
    VOS_UINT32                              ulPriority;
    VOS_VOID                                *pvNotifyHook;
} ATP_UTIL_NOTIFY_ENTRY_ST;

typedef struct tagATP_UTIL_NOTIFIER_ST
{
    struct tagATP_UTIL_NOTIFIER_ST          *pstNext;
    VOS_VOID                                *pvNotifier;
    ATP_UTIL_NOTIFY_ENTRY_ST                *pstNotifyEntries;
} ATP_UTIL_NOTIFIER_ST;
/*********************************************************************************************
   
  brief      通知机制初始化
  param[in]  *pvNotifier: 注册时输入的回调变量
  param[in]  **ppstNewNotifyEntry: 初始化后的通知机制结构体
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 机制通常在cms中使用，由事件发送方初始化，其他模块注册关注信息，事件发生时，事件发送方通知其他模块
此函数是事件发送发使用
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_MEM_ERR:malloc失败，内存不足
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierInit(VOS_VOID               *pvNotifier,
                                      ATP_UTIL_NOTIFIER_ST   **ppstNewNotifyEntry);
/*********************************************************************************************
   
  brief      注册事件关注
  param[in]  *pstNotifier: 通知机制结构体
  param[in]  pfProc: 事件回调函数
  param[in]  ulPriority: 通知优先级
  param[in]  pvNotifyHook: 通知回调函数入参
  param[in]  ppstNotifyEntry: NotifyEntry结构体，一般情况下输入为NULL
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 机制通常在cms中使用，由事件发送方初始化，其他模块注册关注信息，事件发生时，事件发送方通知其他模块
此函数是事件关注方调用
2、 这个函数有内存申请，在使用完毕之后注意释放
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_MEM_ERR:malloc失败，内存不足
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierRegister(ATP_UTIL_NOTIFIER_ST           *pstNotifier,
                                            AtpNotifierProc                 pfProc,
                                            VOS_UINT32                      ulPriority,
                                            VOS_VOID                        *pvNotifyHook,
                                            const ATP_UTIL_NOTIFY_ENTRY_ST  **ppstNotifyEntry);
/*********************************************************************************************
   
  brief      注册事件关注，并按照优先级倒叙方式插入
  param[in]  *pstNotifier: 通知机制结构体
  param[in]  pfProc: 事件回调函数
  param[in]  ulPriority: 通知优先级
  param[in]  pvNotifyHook: 通知回调函数入参
  param[in]  ppstNotifyEntry: NotifyEntry结构体，一般情况下输入为NULL
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 机制通常在cms中使用，由事件发送方初始化，其他模块注册关注信息，事件发生时，事件发送方通知其他模块
此函数是事件关注方调用
2、 这个函数有内存申请，在使用完毕之后注意释放
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_MEM_ERR:malloc失败，内存不足
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierReverseRegister(ATP_UTIL_NOTIFIER_ST  *pstNotifier,
                                            AtpNotifierProc                 pfProc,
                                            VOS_UINT32                      ulPriority,
                                            VOS_VOID                        *pvNotifyHook,
                                            const ATP_UTIL_NOTIFY_ENTRY_ST  **ppstNotifyEntry);
/*********************************************************************************************
   
  brief      去注册事件关注
  param[in]  *pstNotifier: 通知机制结构体
  param[in]  ppstNotifyEntry: NotifyEntry结构体，一般情况下输入为NULL
  return     
  
   注意事项： 
1、 机制通常在cms中使用，由事件发送方初始化，其他模块注册关注信息，事件发生时，事件发送方通知其他模块
此函数是事件关注方调用
  retval  
***********************************************************************************************/
VOS_VOID ATP_UTIL_NotifierUnRegister(ATP_UTIL_NOTIFIER_ST *pstNotifier, ATP_UTIL_NOTIFY_ENTRY_ST *pstNotifyEntry);
/*********************************************************************************************
   
  brief      事件发布
  param[in]  *pstNotifier: 通知机制结构体
  param[in]  bStopWhenError: 错误时是否停止
  param[in]  *pstHooks: 发布时携带入参
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 机制通常在cms中使用，由事件发送方初始化，其他模块注册关注信息，事件发生时，事件发送方通知其他模块
此函数是事件发布方调用
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierDoNotifyEx(const ATP_UTIL_NOTIFIER_ST *pstNotifier,
                VOS_BOOL bStopWhenError, const ATP_UTIL_NOTIFY_HOOKS_ST *pstHooks);
/*********************************************************************************************
   
  brief      事件发布，携带trace信息
  param[in]  *pcFunc: 调用者信息
  param[in]  ulCbbId: 调用者CbbId
  param[in]  *pstNotifier: 通知机制结构体
  param[in]  bStopWhenError: 错误时是否停止
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 机制通常在cms中使用，由事件发送方初始化，其他模块注册关注信息，事件发生时，事件发送方通知其他模块
此函数是事件发布方调用
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierDoNotifyWrap(const VOS_CHAR *pcFunc, VOS_UINT32 ulCbbId, const ATP_UTIL_NOTIFIER_ST *pstNotifier, VOS_BOOL bStopWhenError);
/*********************************************************************************************
   
  brief      事件发布
  param[in]  *pstNotifier: 通知机制结构体
  param[in]  bStopWhenError: 错误时是否停止
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 机制通常在cms中使用，由事件发送方初始化，其他模块注册关注信息，事件发生时，事件发送方通知其他模块
此函数是事件发布方调用
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
***********************************************************************************************/
#define ATP_UTIL_NotifierDoNotify(pstNotifier, bStopWhenError) ATP_UTIL_NotifierDoNotifyWrap(__FUNCTION__, ATP_MODULE_IDX, (pstNotifier), (bStopWhenError))

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

