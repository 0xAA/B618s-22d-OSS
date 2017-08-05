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


#ifndef __ATP_MSG_API_H__
#define __ATP_MSG_API_H__

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <linux/version.h>
#include "atptypes.h"
#include "sysutil.h"

#define ATP_MSG_CATEGORY_DEF(x)          (((x) & 0xFFF) << 8)

#define ATP_MSG_RECV_TIMEOUT_D           (1000 * 5) /*!<  5 seconds*/

#include "micmsgtypes.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*!<  Empty string*/
extern const VOS_CHAR *g_pcEmptyStr;

#define ATP_MSG_MAX_NAME_LEN     (11)

#define IPV6_FROMLAN             (96)
#define IP_FROMLAN               (24)
#ifdef SUPPORT_ATP_LANDEV_IN_27  
#define IP_ORIGINDEV             (27)
#else
#define IP_ORIGINDEV             (21)
#endif

#if LINUX_VERSION_CODE == KERNEL_VERSION(3,3,8)
#define IP_PKTSOURCEMAC          (28)
#else
#define IP_PKTSOURCEMAC          (22)
#endif

#define IPV6_ORIGINDEV           (97)


/* Message Header */
typedef struct tagATP_MSG_HEADER_ST
{
    VOS_UINT32  ulMsgType;
    VOS_UINT32  ulSeqNum;

    VOS_CHAR    aucSendApp[ATP_MSG_MAX_NAME_LEN + 1];    /*!< 发送进程名字 */
    VOS_CHAR    aucRecvApp[ATP_MSG_MAX_NAME_LEN + 1];    /*!< 接收进程名字 */

    VOS_UINT32  ulMsgData;
    VOS_UINT32  ulDataLen;
}ATP_MSG_HEADER_ST;

#define PRINT_MSG_PATTERN             "msg type:[0x%x] app:[%s] data:[%d] len:[%d] dst:[%s] src:[%s]"

#define PRINT_MSG_ARGS(pstMsg)          (pstMsg)->ulMsgType, g_stMsgCtx.aucAppName, (pstMsg)->ulMsgData, (pstMsg)->ulDataLen, (pstMsg)->aucRecvApp, (pstMsg)->aucSendApp

typedef struct tagATP_UTIL_NV_PAIR_ST
{
    struct tagATP_UTIL_NV_PAIR_ST   *pstNext;
    const VOS_CHAR                  *pcName;
    const VOS_CHAR                  *pcValue;
} ATP_UTIL_NV_PAIR_ST;

ATP_UTIL_NV_PAIR_ST *ATP_UTIL_NVPairSet(
                ATP_UTIL_NV_PAIR_ST     **ppstPairs,
                const VOS_CHAR          *pcName,
                const VOS_CHAR          *pcValue);

const VOS_CHAR *ATP_UTIL_NVPairGetValue(
                    ATP_UTIL_NV_PAIR_ST     *pstPairs,
                    const VOS_CHAR          *pcName);

VOS_VOID ATP_UTIL_NVPairDelByName(
                ATP_UTIL_NV_PAIR_ST     **ppstPairs,
                const VOS_CHAR          *pcName);

VOS_VOID ATP_UTIL_NVPairDelAll(ATP_UTIL_NV_PAIR_ST *pstPairs);

VOS_VOID ATP_UTIL_NVPairPrint(const ATP_UTIL_NV_PAIR_ST *pstPairs);

const ATP_UTIL_NV_PAIR_ST *ATP_UTIL_NVPairFindByName(
                const ATP_UTIL_NV_PAIR_ST     *pstPairs,
                const VOS_CHAR                *pcName);

/*
 *  General List Utilities
 */
typedef struct tagATP_UTIL_LIST_ST
{
    struct tagATP_UTIL_LIST_ST      *pstNext;
} ATP_UTIL_LIST_ST;
typedef VOS_VOID (* PFUtilListItemDestroyProc)(ATP_UTIL_LIST_ST *pstItem);
typedef VOS_BOOL (* PFUtilListItemCompareProc)(const ATP_UTIL_LIST_ST *pstItem, const VOS_VOID *pvCompare);
typedef VOS_UINT32 (* PFUtilListItemIterateProc)(const ATP_UTIL_LIST_ST *pstItem, const VOS_VOID *pvCookie);

VOS_VOID ATP_UTIL_ListDeleteAll(
                        ATP_UTIL_LIST_ST            *pstList,
                        PFUtilListItemDestroyProc   pfDestroy);

VOS_VOID ATP_UTIL_ListDeleteItem(
                        ATP_UTIL_LIST_ST            **ppstStart,
                        ATP_UTIL_LIST_ST            *pstDelItem,
                        PFUtilListItemDestroyProc   pfDestroy);

VOS_VOID ATP_UTIL_ListDeleteItemEx(
                        ATP_UTIL_LIST_ST            **ppstStart,
                        ATP_UTIL_LIST_ST            *pstDelItem);


VOS_UINT32 ATP_UTIL_ListGetCount(ATP_UTIL_LIST_ST *pstList);

VOS_VOID ATP_UTIL_ListAppend(
                        ATP_UTIL_LIST_ST            **ppstList,
                        ATP_UTIL_LIST_ST            *pstItem);

ATP_UTIL_LIST_ST *ATP_UTIL_ListFindItem(const ATP_UTIL_LIST_ST *pstList, const VOS_VOID *pvData,
                                        PFUtilListItemCompareProc pfCompareProc);

VOS_UINT32 ATP_UTIL_ListIterateItem(const ATP_UTIL_LIST_ST *pstList, const VOS_VOID *pvCookie,
                                      PFUtilListItemIterateProc pfIterateProc);

#define LIST_NEXT(item) \
        (item ? item->pstNext: NULL)
#define LIST_FOR_EACH_SAFE(item, nextItem, list) \
        for (item = list, nextItem = LIST_NEXT(item); item != NULL; item = nextItem, nextItem = LIST_NEXT(nextItem))


/*
 *  List with Orders Utilities
 */
typedef struct tagATP_UTIL_ORDER_LIST_ST
{
    struct tagATP_UTIL_ORDER_LIST_ST *pstNext;
    VOS_UINT32                       ulOrder;
} ATP_UTIL_ORDER_LIST_ST;

/*
 *  Append pstItem to ppstList according to the ulOrder
 *      1) If ulOrder is -1, pstItem will be appended to the last of the list
 *      2) Else ulOrder will be inserted in the asendding order
 *
 *      If pstItem is already in the ppstList, pstItem will be moved to the correct postion in asending order
 */
VOS_VOID ATP_UTIL_OrderListAppend(
                    ATP_UTIL_ORDER_LIST_ST            **ppstList,
                    ATP_UTIL_ORDER_LIST_ST            *pstItem);

/*
 *  Reorder pstList from 1 to the end with no gaps
 */
VOS_VOID ATP_UTIL_OrderListReorder(ATP_UTIL_ORDER_LIST_ST *pstList);

#include "atploopapi.h"

#include "atptraceapi.h"
enum ATP_MSGCORE_MSGTYPES_EN
{
    ATP_MSG_MSGCORE_START    = ATP_MSG_CATEGORY_DEF(ATP_MODULE_MSGCORE), // = 0x100 = 256
	ATP_MSG_LOG_CTRL,
	ATP_MSG_TRACE_CTRL,
	ATP_MSG_REDIRECT_CTRL,
	ATP_MSG_DEBUG_CTRL,
	ATP_MSG_DIAGNOSTIC_CTRL,
	ATP_MSG_STATS_CTRL,
	ATP_MSG_DEBUG_TRACE_CTRL,
	ATP_MSG_UNRECHABLE_CTRL,
	ATP_MSG_WEBMODULE_REG,		/* 注册web模块 */
	ATP_MSG_WEBRESTFUL_REQ,		/* WebRestful 请求 */
	ATP_MSG_RESTFUL_MATCH_UPDATE,   /* RESTful接口匹配规则更新事件 */
	ATP_MSG_UPGRADE_SAMBA,      /* 发消息给从板配置从板samba信息 */
	ATP_MSG_WEBRESTFUL_REQ_ASYNC,   /* WebRestful 异步请求 */
	ATP_MSG_WEBRESTFUL_REQ_NOTIFY,
	ATP_MSG_WLAN_EVENT_TEST,
	ATP_MSG_WEBRESTFUL_LUA,
	ATP_MSG_MIC_BROADCAST
};

typedef enum tagATP_MSG_RET_CODE_EN
{
    ATP_MSG_RET_SOCKET_ERR        = ATP_MNT_ERR_CODE_DEF(ATP_TEAM_MNT, ATP_MODULE_MSGCORE), // = 0x10000 = 65536
    ATP_MSG_RET_PARA_ERR,
    ATP_MSG_RET_APPNAME_ERR,
    ATP_MSG_RET_NOT_INITED,
    ATP_MSG_RET_PEER_DEAD,
    ATP_MSG_RET_TIMEOUT,
    ATP_MSG_RET_MEM_ERR,
    ATP_MSG_RET_INTERNAL_ERR,
    ATP_MSG_RET_OVERFLOW,
    ATP_MSG_RET_FILE_NOT_EXIST,
    ATP_MSG_RET_NOT_FOUNDPWD,
    ATP_MSG_RET_UPROOT_FAIL,
    ATP_MSG_RET_NOT_FOUNDGROUP,
    ATP_MSG_RET_FILE_WRITE_FAIL,
    ATP_MSG_RET_PATH_PARA_NULL,
    ATP_MSG_RET_PATH_REALPATH_ERROR,
    ATP_MSG_RET_PATH_PATH_LONG,
    ATP_MSG_RET_PATH_PATH_EXCESS,
} ATP_MSG_RET_CODE_EN;

typedef enum tagATP_MIC_BROADCAST_CMDTYPES_EN
{
    ATP_MIC_BROADCAST_DMALLOC_SHUTDOWN = 0,
}ATP_MIC_BROADCAST_CMDTYPES_EN;


typedef VOS_VOID (*AtpMsgProc)(const ATP_MSG_HEADER_ST *pstMsg);

typedef struct tagATP_MSG_QUEUE_ST
{
	struct tagATP_MSG_QUEUE_ST 	*pstNext;
    ATP_MSG_HEADER_ST           *pstMsg;
} ATP_MSG_QUEUE_ST;

 /*!<  Top three bits are used for slave board index*/
#define ATP_MSG_TYPE_SLAVE_INDEX_MASK 0xE0000000

// Get real msg type with no mask
/*
 *      Msg type is 32 bit, lower 8 bits is used by package, middle 12 bits are for package index
 *      Higher 12 bits are reserved.
 */
#define ATP_MSG_TYPE_NO_MASK(ulMsgType)    ((VOS_UINT32)((ulMsgType) & 0xFFFFF))

 /*!< Get which slave board the msg is from by msg type */
#define ATP_MSG_TYPE_GET_SLAVE_BOARD_INDEX(ulMsgType)    ((VOS_UINT32)(((ulMsgType) & ATP_MSG_TYPE_SLAVE_INDEX_MASK) >> 29))

 /*!<  Set which slave board the msg to send by msg type*/
#define ATP_MSG_TYPE_SET_SLAVE_BOARD_INDEX(ulMsgType, ulSlaveIndex)    (ulMsgType) &= (~ATP_MSG_TYPE_SLAVE_INDEX_MASK); (ulMsgType) |= ((VOS_UINT32)((ulSlaveIndex) << 29))

/*!< Recvd big message with file */
#define ATP_MSG_TYPE_RECV_FILE_MASK             ((VOS_UINT32)(0x10000000))
#define ATP_MSG_TYPE_IS_RECV_FILE(ulIndex)      ((VOS_UINT32)((ulIndex) & ATP_MSG_TYPE_RECV_FILE_MASK))
#define ATP_MSG_TYPE_SET_RECV_FILE(ulMsgType)   (ulMsgType) |= (ATP_MSG_TYPE_RECV_FILE_MASK)

/*!< Board index for master board */
#define ATP_MSG_MASTER_BOARD_INDEX_NUM_D        7

typedef struct tagATP_MSG_CONTEXT_ST
{
    VOS_CHAR            aucAppName[ATP_MSG_MAX_NAME_LEN + 1];
    VOS_INT32           lSock;
    VOS_BOOL            bExitLoop;
    AtpMsgProc          pfMsgProc;
    VOS_UINT32          ulDbgLevel;
    FILE                *pfTraceFile;
    VOS_INT32           lTraceFd;
    ATP_MSG_QUEUE_ST    *pstMsgQueue;   /*!<  Internal usage*/
    VOS_INT32           lAccessMode;
    VOS_UINT32          ulMsgFlags;
    VOS_VOID            *handle;
    VOS_UINT32          ulSeqNum;

    // ipc
    VOS_INT32           lIpcSock;       /*!<   ipc sock fd */
    VOS_VOID            *pstIpcHandle;   /*!<  ipc msg handle*/
} ATP_MSG_CONTEXT_ST;

typedef enum tagATP_MSG_FLAGS_EN
{
    ATP_MSG_FLAG_ENABLE_STATS           = (1 << 0),
    ATP_MSG_FLAG_NEED_ENDIAN_SWAP       = (1 << 1),
    ATP_MSG_FLAG_NEED_SLAVE_CONNECTED   = (1 << 2),
    ATP_MSG_FLAG_BODY_ENDIAN_SWAP       = (1 << 3),
} ATP_MSG_FLAGS_EN;

#define ATP_MSG_STATS_ENABLE        (0 != (g_stMsgCtx.ulMsgFlags & ((VOS_UINT32)ATP_MSG_FLAG_ENABLE_STATS)))

/*
  *  Endian Swap Flag for msg client
  */
#define ENDIAN32_SWAP(value) \
         ((((VOS_UINT32)((value) & 0x000000FF)) << 24) | \
         (((VOS_UINT32)((value) & 0x0000FF00)) << 8) | \
         (((VOS_UINT32)((value) & 0x00FF0000)) >> 8) | \
         (((VOS_UINT32)((value) & 0xFF000000)) >> 24))

/*!<  Check if the current msg client need to swap endian for recvd msg*/
#define ATP_MSG_NEED_ENDIAN_SWAP()   (0 != (g_stMsgCtx.ulMsgFlags & ((VOS_UINT32)ATP_MSG_FLAG_NEED_ENDIAN_SWAP)))
/*!<  Mark the the current msg client need to swap endian for recvd msg*/
#define ATP_MSG_SET_ENDIAN_SWAP()   (g_stMsgCtx.ulMsgFlags |= ((VOS_UINT32)ATP_MSG_FLAG_NEED_ENDIAN_SWAP))
/*!<  Clear the mark the the current msg client need to swap endian for recvd msg*/
#define ATP_MSG_CLR_ENDIAN_SWAP()   (g_stMsgCtx.ulMsgFlags &= ((VOS_UINT32)(~ATP_MSG_FLAG_NEED_ENDIAN_SWAP)))

 /*!<  Safe do 32 bit endian swap*/
#define ATP_MSG_SAFE_ENDIAN_SWAP(ulData) (ATP_MSG_NEED_ENDIAN_SWAP() ? (ENDIAN32_SWAP(ulData)) : (ulData))

/*
 *  Multi Board Communication Message Context
 */
 /*!< Recvd Message board index */
/*!< Top three bits are used for slave board index */
#define ATP_MSG_RECV_BOARD_INDEX_MASK ((VOS_UINT32)(0xE0000000))
#define ATP_MSG_GET_RECV_BOARD_INDEX()          ((VOS_UINT32)((g_stMsgCtx.ulMsgFlags & ATP_MSG_RECV_BOARD_INDEX_MASK) >> 29))
#define ATP_MSG_SET_RECV_BOARD_INDEX(ulIndex)   g_stMsgCtx.ulMsgFlags &= (~ATP_MSG_RECV_BOARD_INDEX_MASK); g_stMsgCtx.ulMsgFlags |= ((VOS_UINT32)((ulIndex) << 29))

#define ATP_MSG_DEST_BOARD_INDEX_MASK ((VOS_UINT32)(0x1C000000))
#define ATP_MSG_GET_DEST_BOARD_INDEX()          ((g_stMsgCtx.ulMsgFlags & ATP_MSG_DEST_BOARD_INDEX_MASK) >> 26)
#define ATP_MSG_SET_DEST_BOARD_INDEX(ulIndex)   g_stMsgCtx.ulMsgFlags &= (~ATP_MSG_DEST_BOARD_INDEX_MASK); g_stMsgCtx.ulMsgFlags |= ((VOS_UINT32)((ulIndex) << 26))

extern  ATP_MSG_CONTEXT_ST g_stMsgCtx;

VOS_VOID ATP_MSG_HeaderEndianSwap(ATP_MSG_HEADER_ST *pstMsg);

/*!<  Check if msg body need endian swap*/
VOS_BOOL ATP_MSG_BodyNeedEndianSwap(VOS_BOOL bSendingMsg);

/*!<  Message body safe endian swap for sending msg*/
#define ATP_MSG_SEND_BODY_SAFE_ENDIAN_SWAP(ulData) ((ATP_MSG_BodyNeedEndianSwap(VOS_TRUE))  ? (ENDIAN32_SWAP(ulData)) : (ulData))

/*!<  Message body safe endian swap for recvd msg*/
#define ATP_MSG_RECV_BODY_SAFE_ENDIAN_SWAP(ulData) ((ATP_MSG_BodyNeedEndianSwap(VOS_FALSE)) ? (ENDIAN32_SWAP(ulData)) : (ulData))

VOS_UINT32 ATP_MSG_QueueAppend(
                                ATP_MSG_QUEUE_ST        **ppstMsgQueue,
                                ATP_MSG_HEADER_ST       *pstMsg);

VOS_VOID ATP_MSG_QueueDestroy(ATP_MSG_QUEUE_ST *pstMsgQueue);

/*!
  \brief 初始化消息组件
  \param[in]  *pszAppName: 进程名称，可以为空。为空时，消息服务器随机分配进程名称。
  \return 
  \retval 
*/

VOS_UINT32 ATP_MSG_Init(const VOS_CHAR *pszAppName);

/*!< Slave app init */
VOS_UINT32 ATP_MSG_InitSlaveApp(const VOS_CHAR *pszAppName, const VOS_CHAR *pcDstIP, VOS_UINT32 ulDstPort);


/*!
  \brief 去初始化消息组件
  \param[in] VOS_VOID: 
  \return 
  \retval 无
*/

VOS_VOID ATP_MSG_Destroy(VOS_VOID);

//VOS_UINT32 ATP_MSG_GetAppName(VOS_CHAR *pszName);

/*
 *    Message Dispatch Interfaces
 */

/*!
  \brief 注册消息处理函数
  \param[in]  pFunc: 消息处理函数
  \return 
  \retval 无
*/

VOS_VOID ATP_MSG_RegisterMsgProc(AtpMsgProc pFunc);

/*!
  \brief 启动消息分发循环
  \return 
  \retval 无
*/

VOS_UINT32 ATP_MSG_GetAndDispatch();

//VOS_UINT32 VTOP_MSG_RegisterTrace(PFUNC_MSGHandler pFunc);

//VOS_UINT32 VTOP_MSG_UnRegTrace();

/*
 *    Message Sending & Recving Interfaces
 */

/*!
  \brief 发送一个消息
  \param[in]  *pstMsg: 消息指针
  \return 
  \retval 无
*/

typedef VOS_UINT32 (*AtpMsgSendHookProc)(const ATP_MSG_HEADER_ST *pstMsg, VOS_BOOL *pbHooked, VOS_INT32 *pulSendSock);

extern AtpMsgSendHookProc g_pfMsgSendHook;

VOS_UINT32 ATP_MSG_Send(ATP_MSG_HEADER_ST *pstMsg);

VOS_UINT32 ATP_MSG_SendEx(VOS_INT32 lSock, ATP_MSG_HEADER_ST *pstMsg);

/*!
  \brief 发送消息，并且接收其回应消息
  \param[in]  *pstMsg: 待发送的消息
  \param[in]  **ppstResp: 回应消息
  \param[in]  ulTimeout: 超时时间，为0表示永久阻塞，单位ms
  \return 
  \retval 
*/

VOS_UINT32 ATP_MSG_SendAndRecv(ATP_MSG_HEADER_ST  *pstMsg,
                                        ATP_MSG_HEADER_ST        **ppstResp,
                                        VOS_UINT32               ulTimeout);

VOS_UINT32 ATP_MSG_SendAndRecvWithAppName(ATP_MSG_HEADER_ST   *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);

VOS_UINT32 ATP_MSG_AsyncSendAndRecv(ATP_MSG_HEADER_ST  *pstMsg, VOS_UINT32 ulTimeout, VOS_VOID *pvData, PfMsgWatcherProc callback);

VOS_UINT32 ATP_MSG_SendAndRecvMsgData(const VOS_CHAR * pcDest, VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData, VOS_UINT32 ulTimeout, VOS_UINT32 *pulMsgData);

VOS_UINT32 ATP_MSG_RecvWithType(VOS_UINT32              ulMsgType,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);

VOS_UINT32 ATP_MSG_RecvResponse(const ATP_MSG_HEADER_ST *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);

VOS_UINT32 ATP_MSG_RecvResponseWithAppName(const ATP_MSG_HEADER_ST *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);

/*!
  \brief 从socket接收消息
  \param[in]  sSock: socket描述符
  \param[in]  **ppstMsg:  输出消息指针
  \param[in]  ulTimeout: 超时时间，为0表示永久阻塞，单位ms
  \return 
  \retval 
*/

VOS_UINT32 ATP_MSG_Recv(VOS_INT32           sSock,
                              ATP_MSG_HEADER_ST   **ppstMsg,
                              VOS_UINT32          ulTimeout);

VOS_UINT32 ATP_MSG_RecvWithEndian(VOS_INT32             sSock,
                              ATP_MSG_HEADER_ST     **ppstMsg,
                              VOS_UINT32            ulTimeout,
                              VOS_BOOL              bWithEndian);

/*
 *    Message Utilities
 */
VOS_VOID ATP_MSG_TraceProc(VOS_INT32 lNewFd);

VOS_VOID ATP_MSG_MsgFilterProc(const ATP_MSG_HEADER_ST *pstMsg);

VOS_VOID* ATP_MSG_GetMsgBlock(VOS_UINT32 ulMsgSize);
VOS_VOID* ATP_MSG_GetMsgByHead(ATP_MSG_HEADER_ST* pstMsgHead);
ATP_MSG_HEADER_ST* ATP_MSG_GetMsgHead(VOS_VOID* pvMsg);

/*
 *    Message Structure Utilities
 */

VOS_UINT32 ATP_MSG_SendFd(VOS_INT32 lFdToSend);

VOS_UINT32 ATP_MSG_RecvFd(VOS_INT32 *plFdToRecv, VOS_UINT32 ulTimeout);


VOS_VOID ATP_MSG_SimpleBuilder(ATP_MSG_HEADER_ST *pstMsg, const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData);

VOS_UINT32 ATP_MSG_SendSimpleMsg(const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData);

VOS_UINT32 ATP_MSG_SendSimpleMsgWithSeqNum(const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData, VOS_UINT32 ulSeqNum);


#define ATP_MSG_SubscribeEvent(ulEvtType)   ATP_MSG_SendSimpleMsg(NULL, ATP_MSG_SUBSCRIBE_EVT, (ulEvtType))
#define ATP_MSG_UnSubscribeEvent(ulEvtType) ATP_MSG_SendSimpleMsg(NULL, ATP_MSG_UNSUBSCRIBE_EVT, (ulEvtType))


VOS_UINT32 ATP_MSG_SendMsgData(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType, 
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen);

VOS_UINT32 ATP_MSG_SendRealTimeMsg(VOS_UINT32 ulMsgData);

VOS_UINT32 ATP_MSG_GetNumOfProcesses(const VOS_CHAR *pcName);

VOS_UINT32 ATP_MSG_SafeExitProcesses(const VOS_CHAR *pcName);

ATP_MSG_HEADER_ST *ATP_MSG_Dup(const ATP_MSG_HEADER_ST *pstMsg);

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

VOS_UINT32 ATP_UTIL_NotifierInit(VOS_VOID               *pvNotifier,
                                      ATP_UTIL_NOTIFIER_ST   **ppstNewNotifyEntry);

VOS_UINT32 ATP_UTIL_NotifierRegister(ATP_UTIL_NOTIFIER_ST           *pstNotifier,
                                            AtpNotifierProc                 pfProc,
                                            VOS_UINT32                      ulPriority,
                                            VOS_VOID                        *pvNotifyHook,
                                            const ATP_UTIL_NOTIFY_ENTRY_ST  **ppstNotifyEntry);

VOS_UINT32 ATP_UTIL_NotifierReverseRegister(ATP_UTIL_NOTIFIER_ST  *pstNotifier,
                                            AtpNotifierProc                 pfProc,
                                            VOS_UINT32                      ulPriority,
                                            VOS_VOID                        *pvNotifyHook,
                                            const ATP_UTIL_NOTIFY_ENTRY_ST  **ppstNotifyEntry);

VOS_VOID ATP_UTIL_NotifierUnRegister(ATP_UTIL_NOTIFIER_ST *pstNotifier, ATP_UTIL_NOTIFY_ENTRY_ST *pstNotifyEntry);

VOS_UINT32 ATP_UTIL_NotifierDoNotifyEx(const ATP_UTIL_NOTIFIER_ST *pstNotifier,
                VOS_BOOL bStopWhenError, const ATP_UTIL_NOTIFY_HOOKS_ST *pstHooks);

VOS_UINT32 ATP_UTIL_NotifierDoNotifyWrap(const VOS_CHAR *pcFunc, VOS_UINT32 ulCbbId, const ATP_UTIL_NOTIFIER_ST *pstNotifier, VOS_BOOL bStopWhenError);

#define ATP_UTIL_NotifierDoNotify(pstNotifier, bStopWhenError) ATP_UTIL_NotifierDoNotifyWrap(__FUNCTION__, ATP_MODULE_IDX, (pstNotifier), (bStopWhenError))


/*
 *  File operation utilities
 */

/*!
  \brief  往文件中格式化写入字符串内容
  \param[in]  pcFileName: 待写的文件
  \param[in]  bAppend: VOS_FALSE表示覆盖文件原有的内容；VOS_TRUE表示往文件尾追加内容
  \param[in]  *fmt: 格式化的字符串
  \param[in]  ...: 
  \return 
  \retval -1:   出错
  \retval >=0:    写入的字符串个数
*/
//VOS_INT32 ATP_UTIL_FilePrintf(const VOS_CHAR *pcFileName, VOS_BOOL bAppend, VOS_CHAR *fmt, ...);

/*!
  \brief 文件读入缓存
  \param[in]  *pcFileName: 
  \param[in]  **ppcContent: 
  \param[in]  *pulLen: 
  \return 
  \retval ATP_MSG_RET_PARA_ERR 非法入参
  \retval ATP_MSG_RET_FILE_NOT_EXIST 文件不存在
  \retval ATP_MSG_RET_MEM_ERR no memry
  \retval VOS_OK 成功
*/
VOS_UINT32 ATP_UTIL_ReadFileToBuf(const VOS_CHAR *pcFileName, VOS_CHAR **ppcContent, VOS_UINT32 *pulLen);

/*!
  \brief 获取文件的长度
  \param[in]  pcFileName: 待处理文件名
  \return
  \retval -1:    出错
  \retval >=0:   文件大小
*/
VOS_INT32 ATP_UTIL_FileTell(const VOS_CHAR* pcFileName);
VOS_UINT32 ATP_UTIL_ReadPartFile(const VOS_CHAR *pcFileName, VOS_CHAR *pcContent, VOS_UINT32* pulLen,
    const VOS_UINT32 ulMaxLen, const VOS_UINT32 ulOffset);
/*!
  \brief 缓存写入文件
  \param[in]  *pcContent:
  \param[in]  ulLen:
  \param[in]  *pcFileName:
  \return
  \retval ATP_MSG_RET_PARA_ERR 非法入参
  \retval ATP_MSG_RET_FILE_NOT_EXIST 文件不存在
  \retval VOS_OK 成功
*/
VOS_UINT32 ATP_UTIL_WriteBufToFile(const VOS_CHAR *pcContent, VOS_UINT32 ulLen, const VOS_CHAR *pcFileName);

/*!
  \brief 文件读入缓存
  \param[in]  *pcFileName: 
  \param[in]  **ppcContent: 
  \param[in]  *pulLen: 
  \param[in]  uloffset: 
  \return 
  \retval ATP_MSG_RET_PARA_ERR 非法入参
  \retval ATP_MSG_RET_FILE_NOT_EXIST 文件不存在
  \retval ATP_MSG_RET_MEM_ERR no memry
  \retval VOS_OK 成功
*/
VOS_UINT32 ATP_UTIL_ReadFileToBuf_Ex(const VOS_CHAR *pcFileName
    , VOS_CHAR **ppcContent, VOS_UINT32 *pulLen, const VOS_UINT32 uloffset);

/*!
  \brief 缓存同步写入文件
  \param[in]  *pcContent: 
  \param[in]  ulLen: 
  \param[in]  *pcFileName: 
  \param[in]  uloffset: 
  \return 
  \retval ATP_MSG_RET_PARA_ERR 非法入参
  \retval ATP_MSG_RET_FILE_NOT_EXIST 文件不存在
  \retval VOS_OK 成功
*/

VOS_UINT32 ATP_UTIL_WriteBufToFile_Sync(const VOS_CHAR *pcContent
, VOS_UINT32 ulLen,const VOS_UINT32 uloffset, const VOS_CHAR *pcFileName);

/*!
  \brief 缓存写入文件
  \param[in]  *pcContent: 
  \param[in]  ulLen: 
  \param[in]  *pcFileName: 
  \param[in]  uloffset: 
  \return 
  \retval ATP_MSG_RET_PARA_ERR 非法入参
  \retval ATP_MSG_RET_FILE_NOT_EXIST 文件不存在
  \retval VOS_OK 成功
*/
VOS_UINT32 ATP_UTIL_WriteBufToFile_Ex(const VOS_CHAR *pcContent
, VOS_UINT32 ulLen,const VOS_UINT32 uloffset, const VOS_CHAR *pcFileName);


/*!
  \brief 更新动态应用程序是否被mic 启动
  \param[in]  *pcAppName: 需更新的应用程序名
  \param[in]  bStop: 是否停止当前被mic 启动进程
  \return 返回发送消息错误码
  \retval VOS_OK 更新消息发送成功
  \retval VOS_NOK pcAppName为NULL
  \retval ATP_MSG_RET_PARA_ERR  消息参数错误
  \retval ATP_MSG_RET_NOT_INITED 未初始化
  \retval ATP_MSG_RET_OVERFLOW  消息溢出
  \retval ATP_MSG_RET_PEER_DEAD  socket被peer关闭
  \retval ATP_MSG_RET_INTERNAL_ERR  内部错误
*/

VOS_UINT32 ATP_UTIL_Remove_Files(const VOS_CHAR* pszSrcDir);

VOS_UINT32 ATP_UTIL_CreatePidFile(const VOS_CHAR *pcPidFile);

VOS_UINT32 ATP_UTIL_UpdateDynAppStatus(const VOS_CHAR *pcAppName, VOS_BOOL bStart);

VOS_UINT32 ATP_UTIL_RestartDynApp(const VOS_CHAR *pcAppName);

VOS_UINT32 ATP_MSG_AtpSyncWait(const VOS_CHAR *pcEntry);

/*
 *  Version utility
 */
const VOS_CHAR * ATP_MSG_GetVersion(void);


/*!
  \brief  去除文件或文件夹的全局可写属性，只适用于eUAP产品
  \param[in]  *mod: 文件的期望权限属性，
                    本接口将用此mod传递给chmod生成该文件新的权限属性
  \param[in]  *path: 文件的绝对路径
  \return
  \retval NA
  \retval NA
*/
void ATP_UTIL_RemoveAndroidWPerm(char* path, char* mod);

/*!
  \brief 进程权限临时切换至root
  \return 
  \retval ATP_MSG_RET_UPROOT_FAIL 权限提升失败
  \retval VOS_OK 成功
*/
VOS_UINT32 ATP_UTIL_UpRootPrivileges(VOS_VOID);

/*!
  \brief 恢复eUAP进程自己权限，设置为system权限
  \param[in]  NA
  \return
  \retval 
  \retval VOS_OK 权限设置成功
*/
VOS_UINT32 ATP_UTIL_DropAndroidRootPrivileges();

/*!
  \brief 恢复进程自己权限
  \param[in]  *pcAppName: 进程名称
  \return 
  \retval ATP_MSG_RET_NOT_FOUNDPWD /etc/passwd 找不到该进程名
  \retval VOS_OK 权限设置成功
*/
VOS_UINT32 ATP_UTIL_DropRootPrivileges(const VOS_CHAR *pcAppName);

/*!
  \brief 强制设置进程权限，不可恢复
  \param[in]  *pcAppName: 
  \return 
  \retval ATP_MSG_RET_NOT_FOUNDPWD /etc/passwd 找不到该进程名
*/
VOS_UINT32 ATP_UTIL_ForceSetPrivileges(const VOS_CHAR *pcAppName);

/*!
  \brief 
  \param[in]  *pcUserName: 用户名
  \param[in]  ulGroupId: 默认组
  \return 
  \retval 
*/
VOS_UINT32 ATP_UTIL_PrivilegesAddUser(const VOS_CHAR *pcUserName, VOS_UINT32 ulGroupId);

/*!
  \brief 用户是否存在
  \param[in]  *pcUserName: 
  \return 
  \retval VOS_TRUE 已存在此用户
  \retval VOS_FALSE 不存在此用户
*/
VOS_BOOL ATP_UTIL_PrivilegesIsUserExist(const VOS_CHAR *pcUserName);


/*
  * String Utilities
  */

/*!
  \brief 执行字符串strcat操作，将pcSrc中的内容连接在pcDst后面，安全编码。
  \param[in]  pcDst: 目的字符串
  \param[in]  size: 连接后的字符串长度
  \param[in]  pcSrc: 待连接字符串
  \return 连接后的字符串
  \retval pcDst
*/
const VOS_CHAR * ATP_UTIL_StrCat(VOS_CHAR * pcDst, VOS_UINT32 size, const VOS_CHAR * pcSrc);
/*!
  \brief 执行字符串Trim操作，去掉两头的空白字符,
          在原字符串上修改，未开辟空间,输入为空格时，直接返回
  \param[in]  *pszStr: 输入的字符串，可以为空
  \return  Trim后的字符串指针
  \retval pszStr  Trim后的字符串指针，可以为空
*/
VOS_CHAR * ATP_UTIL_StrTrim( VOS_CHAR *pszStr );

typedef struct tagATP_UTIL_STR_IDX_MAP_ST
{
    const VOS_CHAR      *pcStrInfo;
    VOS_INT32           lIdx;
} ATP_UTIL_STR_IDX_MAP_ST;


const VOS_CHAR *ATP_UTIL_StrIdxArrayGetStrByIdx(VOS_INT32 lIdx,const ATP_UTIL_STR_IDX_MAP_ST* pstSrcStrIdx);
VOS_INT32 ATP_UTIL_StrIdxArrayGetIdxByStr(const VOS_CHAR *pcStr,const ATP_UTIL_STR_IDX_MAP_ST* pstSrcStrIdx);

const VOS_CHAR *ATP_UTIL_GetStrFromIdx(VOS_INT32 lIdx, const VOS_CHAR * const apcBaseLine[],
                                  VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[]);

/*!
  \brief  在字符串指针数组中查找指定的字符串，返回该字符串的序号
  \param[in]  const VOS_CHAR *pcStr: 要查找的字符串
  \param[in]  const VOS_CHAR * const apcBaseLine[]: 字符串指针数组
  \param[in]  VOS_INT32 lBaseLineLen: apcBaseLine[]中字符串指针个数
  \param[in]  const VOS_CHAR * const apcExtension[]: 后备查找的字符串指针数组
  \param[in]  const VOS_CHAR * const apcExtension[]: 匹配时是否检查大小写
  \return 字符串指针序号
*/
VOS_INT32 ATP_UTIL_GetIdxFromStrEx(const VOS_CHAR *pcStr, const VOS_CHAR * const apcBaseLine[],
                                      VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[],
                                      VOS_BOOL bCaseSensitive);

VOS_INT32 ATP_UTIL_GetIdxFromStr(const VOS_CHAR *pcStr, const VOS_CHAR * const apcBaseLine[],
                                      VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[]);

#define ATP_UTIL_IsStrInArray(pcStr, apcArray) (ATP_UTIL_GetIdxFromStr((pcStr), (apcArray), ATP_ARRAY_LEN((apcArray)), NULL) >= 0)

VOS_VOID ATP_UTIL_Hex2Str(VOS_CHAR *pcdst, VOS_INT32 lDstlen, const VOS_CHAR *pcsrc, VOS_INT32 lStrlen);

VOS_VOID ATP_UTIL_Hex2StrEx(const VOS_UINT8 *pucSrc, VOS_UINT32 ulStrlen, VOS_UINT8 *pucDst,  VOS_UINT32 ulDstlen, VOS_BOOL bUpper );
VOS_VOID ATP_UTIL_HexStr2Bin(VOS_UINT8 *pDestStr, VOS_UINT32 ulDstlen, const VOS_CHAR *pSrcStr);


VOS_CHAR **ATP_UTIL_MSplit(VOS_CHAR *str, VOS_CHAR *sep, VOS_INT32 max_strs, VOS_INT32 *toks, VOS_CHAR meta);

VOS_VOID ATP_UTIL_MSplitFree(VOS_CHAR ***pbuf, VOS_INT32 num_toks);

/*!
  \brief 去掉源pszSrc字符串后的换行符，将结果保存在pszDst中
  \param[in]  VOS_CHAR *pszSrc 源字符串
  \param[in]  VOS_UINT32 ulDstLen  目的字符串可以存放的最大字节数，包含结束符
  \param[out] VOS_CHAR *pszDst 保存去掉换行符的字符串
  \return 无 
*/
VOS_VOID ATP_UTIL_GetRidOfNewlineSign(VOS_CHAR *pszSrc,  VOS_CHAR *pszDst, VOS_UINT32 ulDstLen);

/*!
  \brief 去掉源pszStr字符串最后的点
  \param[in]  VOS_CHAR *pszStr 源字符串  
  \param[out] VOS_CHAR *pszStr 保存去掉最后点的字符串
  \return 无 
*/
VOS_VOID ATP_UTIL_GetRidOfLastdot(VOS_CHAR *pszStr);

/*!
  \brief 比较两个DNS域名是否相同, 不区分大小写，考虑全域名(最后为点)
  \param[in]  VOS_CHAR *pszStr1 : 域名1
  \param[in]  VOS_CHAR *pszStr2 : 域名2 
  \return VOS_TRUE: 域名相同
*/
VOS_BOOL ATP_UTIL_CmpDnsDomain(const VOS_CHAR *pszStr1, const VOS_CHAR *pszStr2);
VOS_VOID ATP_UTIL_StripSlashes(VOS_CHAR *pcFilePath);
const VOS_CHAR *ATP_UTIL_StrRightChr(const VOS_CHAR *pcStr, VOS_CHAR cMatch);


typedef struct tagATP_MSG_HDL_LIST_ST
{
    struct tagATP_MSG_HDL_LIST_ST       *pstNext;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulPriority;
    AtpMsgProc                          pfProc;
} ATP_MSG_HDL_LIST_ST;

VOS_UINT32 ATP_MSG_RegMsgProc(VOS_UINT32 ulMsgType, AtpMsgProc pfProc, VOS_UINT32 ulPriority, ATP_MSG_HDL_LIST_ST **ppstMsgHdl);

VOS_VOID ATP_MSG_UnRegMsgProc(ATP_MSG_HDL_LIST_ST *ppstMsgHdl);

VOS_VOID ATP_MSG_DefaultMsgProc(const ATP_MSG_HEADER_ST *pstMsg);

#ifdef SUPPORT_ATP_BOOT_TRACK
#define ATP_UTIL_BOOT_TRACK(format, args...) \
    do { \
            struct timeval cur_time; \
            (VOS_VOID)ATP_UTIL_GetSysTime(&cur_time); \
            (VOS_VOID)ATP_UTIL_FilePrintf("/var/atp_boot_track.log", VOS_TRUE, "[tv_sec:%03ld tv_usec:%06ld] ", cur_time.tv_sec, cur_time.tv_usec); \
            (VOS_VOID)ATP_UTIL_FilePrintf("/var/atp_boot_track.log", VOS_TRUE, format, ##args); \
            (VOS_VOID)ATP_UTIL_FilePrintf("/var/atp_boot_track.log", VOS_TRUE, "\r\n"); \
    } while(0)

#else
#define ATP_UTIL_BOOT_TRACK(x...)
#endif

/*
 *  ATP_UTIL_ExecCmdNoHang execute mode function
 */
typedef enum tagATP_UTIL_EXEC_MODE_EN
{
    ATP_UTIL_EXEC_MODE_DFT,     /*!<  Default mode, using msleep to check if child process finished*/
    ATP_UTIL_EXEC_MODE_BLOCK,   /*!<  Wait util child process finished with waitpid*/
    ATP_UTIL_EXEC_MODE_SYSTEM,  /*!<  Use system directly*/
    ATP_UTIL_EXEC_MODE_BACKLOG  /*!<  No exec at all, just log to a file*/
} ATP_UTIL_EXEC_MODE_EN;

typedef struct tagATP_UTIL_EXEC_CTX_ST
{
    VOS_UINT32          ulMode;
    const VOS_CHAR      *pcBackTraceFile;
} ATP_UTIL_EXEC_CTX_ST;

extern const ATP_UTIL_EXEC_CTX_ST *g_pstExecCtx;

#include "atpdebugapi.h"

/*
 * ATP Kernel NLS support interface, this will substitute iconv library
 */

#ifdef SUPPORT_ATP_ATP_NLS
#define ATP_NLS_ENCODING_UTF8       "utf8"
#define ATP_NLS_ENCODING_GB2312     "cp936"
#define ATP_NLS_ENCODING_BIG5       "cp950"
#define ATP_NLS_ENCODING_ISO8859_1  "iso8859-1"
#else
#define ATP_NLS_ENCODING_UTF8       "UTF-8"
#define ATP_NLS_ENCODING_GB2312     "GBK"
#define ATP_NLS_ENCODING_BIG5       "BIG5"
#define ATP_NLS_ENCODING_ISO8859_1  "ISO-8859-1"
#endif

VOS_CHAR *ATP_NLS_GB2312Convert (const VOS_CHAR *pszInput, const char* tocode, const char* fromcode);
VOS_CHAR *ATP_NLS_IconvConvert (const VOS_CHAR *pszInput, const char* tocode, const char* fromcode);

VOS_INT32 ATP_NLS_ConvertGetLength(const VOS_CHAR *pcInputEncoding, const VOS_CHAR *pcInputStr, VOS_UINT32 ulInputLen, const VOS_CHAR *pcOutputEncoding, VOS_BOOL bForce);

VOS_CHAR *ATP_NLS_ConvertString(const VOS_CHAR *pcInputEncoding, const VOS_CHAR *pcInputStr, VOS_UINT32 ulInputLen, const VOS_CHAR *pcOutputEncoding, VOS_UINT32 *pulOutputlen);

VOS_BOOL ATP_NLS_IsStringUtf8(const VOS_UINT8 *pszStr);

VOS_CHAR *ATP_NLS_TryConvertToUtf8(const VOS_CHAR *pszInput);

const VOS_CHAR *ATP_NLS_TryConvertToUtf8NoFree(const VOS_CHAR *pszInput);

VOS_CHAR *ATP_UTIL_SafeStrDup(const VOS_CHAR *pcStr);

/*
 *	Kernel version api
 */
typedef enum tagATP_LINUX_VERSION_EN
{
	ATP_LINUX_VERSION_2_6_21 = 0,
	ATP_LINUX_VERSION_2_6_30 = 1,
	ATP_LINUX_VERSION_2_6_36 = 2,
} ATP_LINUX_VERSION_EN;

VOS_BOOL ATP_UTIL_MatchPrefixPath(const VOS_CHAR *pattern, const VOS_CHAR *string);

/*
*    WEB Restful 请求
*/
#ifndef REQ_TYPE_FLAG
#define REQ_TYPE_FLAG 1
typedef enum _REQ_TYPE   
{ 
    REQ_GET  = 1,    /*!< HTTP请求为GET*/
    REQ_POST = 2,    /*!< HTTP请求为POST*/
    REQ_HEAD = 4,    /*!< HTTP请求为HEAD*/
}REQ_TYPE;
#endif

#define ATP_MSG_WEB_RESTFUL_LEN (64)

typedef struct tagATP_MSG_WEBRESTFUL_REQ_ST
{
    VOS_UINT32  ulHttpDirect;                           /* 请求类型 */
    VOS_UINT32  ulIntfType;                             /* 配置工具类型    当前用户名 */
    VOS_CHAR    acModuleName[ATP_MSG_WEB_RESTFUL_LEN];  /*module 名字*/
    VOS_CHAR    acFunction[ATP_MSG_WEB_RESTFUL_LEN];    /* 请求的接口 */
    VOS_CHAR    acBodyBuff[0];                             /* 请求的BODY内容（文本）*/
} ATP_MSG_WEBRESTFUL_REQ_ST;

typedef VOS_UINT32 (*PFWebRestfulHandle)(const ATP_MSG_WEBRESTFUL_REQ_ST *pstRestfulReq, VOS_CHAR **pszResp);

typedef struct tagATP_UTIL_RESTFUL_ST
{
    const VOS_CHAR          *pcAPIName;
    PFWebRestfulHandle      pfHandle;
} ATP_UTIL_RESTFUL_ST;

VOS_UINT32 ATP_MSG_RegRestfulProcsEx(
                const VOS_CHAR            *pszModuleName,
                const ATP_UTIL_RESTFUL_ST *pstRestfulAPI,
                VOS_BOOL                  bExactMatch);

VOS_UINT32 ATP_MSG_RegRestfulProcs(
                const VOS_CHAR* pszModuleName,
                const ATP_UTIL_RESTFUL_ST *pstRestfulAPI);


ATP_MSG_HEADER_ST *ATP_MSG_BuildRestfulReqMsg(REQ_TYPE enType, VOS_UINT32 ulIntfType, const VOS_CHAR *pcModName,
                                                const VOS_CHAR *pcFuncName, const VOS_CHAR *pcBody, const VOS_INT32 lBodyLen);

VOS_UINT32 ATP_MSG_SendRestfulResponseMsg(const VOS_CHAR *pcProcName, VOS_UINT32 ulMsgType, 
    const VOS_CHAR* pvMsgBuff, VOS_UINT32 ulBuffLen, VOS_UINT32 ulMsgData, VOS_UINT32 ulSeqNum);

/**
*   IPC
*/
VOS_UINT32 ATP_IPC_Init (const VOS_CHAR* pszAppName);
VOS_UINT32 ATP_IPC_Send(ATP_MSG_HEADER_ST *pstMsg);
VOS_UINT32 ATP_IPC_SendSimpleMsg(const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData);

VOS_UINT32 ATP_IPC_SendMsgData(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType, 
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen);

VOS_UINT32 ATP_MSG_SendMsgDataWithData(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType, 
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen, VOS_UINT32 ulMsgData);
VOS_UINT32 ATP_MSG_SendMsgDataWithDataSeq(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType, 
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen, VOS_UINT32 ulMsgData, VOS_UINT32 ulSeqNum);


#ifdef ATP_DEBUG
#define ATP_MSG_DEBUG(format, args...)       {printf("FILE: %s LINE: %d: ", __FILE__, __LINE__);printf(format, ##args);}
#else
#define ATP_MSG_DEBUG(x...)
#endif

// Debug modules
#define ATP_MSG_MODULE_LOOP_D           "loop"
#define ATP_MSG_MODULE_MSG_D            "msg"
#define ATP_MSG_MODULE_TIMER_D          "timer"
#define ATP_MSG_MODULE_NOTIFY_D         "notify"
#define ATP_MSG_MODULE_SOCKBASE_D       "sockbase"

#include "sockbaseapi.h"
//#include "dnspubapi.h"


/*
 *  Socket and address api
 */
#if !defined(__KERNEL__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


VOS_UINT32 ATP_UTIL_Reboot(VOS_VOID);

VOS_INT32 ATP_UTIL_SocketClose(VOS_INT32      lSock);

VOS_UINT32 ATP_UTIL_SocketGetSourceAddr(
                                ATP_SOCKET_ST       *pstSocket,
                                VOS_CHAR			*pcAddr,
                                VOS_UINT32			ulBufLen);

VOS_UINT32 ATP_UTIL_SocketSetTTL(VOS_INT32 lSock, VOS_UINT8 ucTTLValue);
VOS_UINT32 ATP_UTIL_SocketSetMcastIf(VOS_INT32 lSock, const struct addrinfo *pstIpIf);
VOS_UINT32 ATP_UTIL_SocketJoinMcast(VOS_INT32 lSock, const VOS_CHAR *pcMCastIp, const struct addrinfo *pstLocalIp);
VOS_UINT32 ATP_UTIL_SocketJoinMcastEx(
                                        VOS_INT32               lSock,
                                        const VOS_CHAR          *pcMCastIp,
                                        const struct addrinfo   *pstLocalIp, 
                                        const VOS_CHAR          *pcInterface);

VOS_UINT32 ATP_UTIL_GetIpAddresses(
                                const VOS_CHAR          *pcHostName,
                                const struct addrinfo    *pstLocalInterface,
                                VOS_UINT32                ulRemotePort,
                                struct addrinfo            **ppstResovledAddr);

struct addrinfo *ATP_UTIL_CopyAddrInfo(const struct addrinfo *pstSrc, VOS_BOOL bCopyList);

VOS_BOOL ATP_UTIL_IsAddrInfoSame(const struct addrinfo *pstAddrL, const struct addrinfo *pstAddrR);

struct addrinfo *ATP_UTIL_ParseIPAddress(
                                VOS_UINT32              ulSockType,
                                const VOS_CHAR          *pcAddr,
                                VOS_UINT32              ulPort);

VOS_VOID ATP_UTIL_FreeAddrInfo(struct addrinfo *pstSockAddr);

struct addrinfo *ATP_UTIL_MakeAddrInfo(
                                VOS_UINT32               ulSockFlag,
                                const struct sockaddr   *pstSockAddr,
                                socklen_t                   socklen);

VOS_BOOL ATP_UTIL_IsAddrLoopback(const struct addrinfo *pstAddr);

VOS_CHAR *ATP_UTIL_UrlEncode(const VOS_CHAR *src);

typedef VOS_UINT32 (*PFUtilNameResolveFunc)(
                                const VOS_CHAR       *pcName,    /*!<  协议栈待解析的域名*/
                                const struct addrinfo *pstLocalInterface,   /*!<  协议栈所绑定的IP*/
                                VOS_UINT32             ulRemotePort,
                                struct addrinfo         **ppstResovledAddr);  /*!<  解析后的IP地址*/

VOS_VOID  ATP_UTIL_RegNameResolveFunc(PFUtilNameResolveFunc pfFunc);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif

