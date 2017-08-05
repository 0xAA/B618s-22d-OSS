/*****************************************************************************
 *               Copyright (C) 2011, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/


#ifndef __ATP_MSG_API_H__
#define __ATP_MSG_API_H__

#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <grp.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <linux/version.h>
#include "atptypes.h"
#include "sysutil.h"

#include "dbapi.h"





#define ATP_MSG_CATEGORY_DEF(x)          (((x) & 0xFFF) << 8)

#define ATP_MSG_RECV_TIMEOUT_D           (1000 * 5) /*!<  5 seconds*/

#include "micmsgtypes.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

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

#ifdef SUPPORT_ATP_PKTSOURCEMAC_IN_28
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
#include "eventapi.h"
#include "listapi.h"

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
    ATP_MSG_RET_MKDIR_ERR,
    ATP_MSG_RET_CHOWN_ERR
} ATP_MSG_RET_CODE_EN;

typedef enum tagATP_MIC_BROADCAST_CMDTYPES_EN
{
    ATP_MIC_BROADCAST_DMALLOC_SHUTDOWN = 0,
    ATP_MIC_BROADCAST_LLT,
}ATP_MIC_BROADCAST_CMDTYPES_EN;


typedef VOS_VOID (*AtpMsgProc)(const ATP_MSG_HEADER_ST *pstMsg);
typedef ATP_MSG_HEADER_ST *(*AtpSyncMsgProc)(const ATP_MSG_HEADER_ST *pstMsg);

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

extern ATP_THREAD_SAFE ATP_MSG_CONTEXT_ST g_stMsgCtx;

/*********************************************************************************************
   
  brief      对消息结构体中的元素做字节序的转换
  param[in]  *pstMsg: 待转换的消息结果体
  return     
   注意事项： 
1、调用该函数会对消息结构体中的数字型元素做字节序的转换，调用之前需要通过函数ATP_MSG_NEED_ENDIAN_SWAP
判断是否需要转换
retval 
***********************************************************************************************/ 
VOS_VOID ATP_MSG_HeaderEndianSwap(ATP_MSG_HEADER_ST *pstMsg);

/*********************************************************************************************
   
  brief      将消息添加到消息缓存队列
  param[in]  **ppstMsgQueue: 消息缓存队列
  param[in]  *pstMsg: 待缓存消息
  return     VOS_OK:添加成功
             其他:添加失败
   注意事项： 
1、将消息加入到消息队列之后，消息不会立即发送，而是在空闲时发送
retval  ATP_MSG_RET_PARA_ERR:入参输入错误，入参为空
        ATP_MSG_RET_MEM_ERR:内存申请错误，内存不足
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_QueueAppend(
                                ATP_MSG_QUEUE_ST        **ppstMsgQueue,
                                ATP_MSG_HEADER_ST       *pstMsg);
/*********************************************************************************************
   
  brief      销毁消息缓存队列
  param[in]  *pstMsgQueue: 消息缓存队列
  return     
   注意事项： 
1、暂无
retval  
***********************************************************************************************/ 
VOS_VOID ATP_MSG_QueueDestroy(ATP_MSG_QUEUE_ST *pstMsgQueue);

/*********************************************************************************************
   
  brief      初始化消息组件
  param[in]  *pszAppName: 进程名称，可以为空。为空时，消息服务器随机分配进程名称。
  return     VOS_OK:添加成功
             其他:添加失败
   注意事项： 
1、如果初始化的时候只能进程的名称，需要确保进程名称的唯一性，否则会出现问题
2、初始化的时候会发送消息给mic进行注册，此消息默认是缓存在队列中延迟发送的，针对需要立即成功的场景
需要特殊处理
retval  ATP_MSG_RET_SOCKET_ERR:创建socket失败
        ATP_MSG_RET_MEM_ERR:内存不够，malloc失败
        ATP_MSG_RET_PARA_ERR；注册时参数输入错误
        ATP_MSG_RET_OVERFLOW:注册消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:注册消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息注册发生其他的错误
        在支持notifyclient的情况下还会返回
        ATP_NOTIFY_RET_APPNAME_ERR:notifyclient初始化的时候ulMID输出非法
        ATP_NOTIFY_RET_SOCKET_ERR:创建notifyclient socket失败
        ATP_NOTIFY_RET_PEER_DEAD:notify client注册失败
        ATP_NOTIFY_RET_MEM_ERR:malloc失败
        ATP_NOTIFY_RET_OVERFLOW:注册消息发送失败，选择fd错误
        ATP_NOTIFY_RET_INTERNAL_ERR:消息注册发生其他的错误
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_Init(const VOS_CHAR *pszAppName);

/*********************************************************************************************
   
  brief      去初始化消息队列
  param[in]  
  return     
   注意事项： 
1、暂无
retval  
***********************************************************************************************/ 
VOS_VOID ATP_MSG_Destroy(VOS_VOID);


/*
 *    Message Dispatch Interfaces
 */
/*********************************************************************************************
   
  brief      注册消息处理函数
  param[in]  pFunc:消息处理函数
  return     
   注意事项： 
1、此处可以注册进程自己实现的每个消息的处理函数，但是必须在自己的回调函数里面调用ATP_MSG_DefaultMsgProc
才可以通过ATP_MSG_RegMsgProc的方式注册消息的处理函数
retval  
***********************************************************************************************/ 
VOS_VOID ATP_MSG_RegisterMsgProc(AtpMsgProc pFunc);


/*********************************************************************************************
   
  brief      启动消息分发循环
  param[in]  
  return     
   注意事项： 
1、暂无
retval  ATP_MSG_RET_TIMEOUT:消息分发超时 
        ATP_MSG_RET_INTERNAL_ERR:消息分发其他错误

***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_GetAndDispatch();



/*
 *    Message Sending & Recving Interfaces
 */

typedef VOS_UINT32 (*AtpMsgSendHookProc)(const ATP_MSG_HEADER_ST *pstMsg, VOS_BOOL *pbHooked, VOS_INT32 *pulSendSock);

extern AtpMsgSendHookProc g_pfMsgSendHook;

/*********************************************************************************************
   
  brief      消息发送接口
  param[in]  *pstMsg:消息指针
  return     VOS_OK:消息发送成功
             其他返回值:消息发送失败，具体原因参考错误码
   注意事项： 
1、在未指定g_pfMsgSendHook为空的时候，直接调用ATP_MSG_Send可能导致消息延迟发送
2、pstMsg的内存如果是malloc的，注意在调用ATP_MSG_Send之后进行释放
retval  ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_Send(ATP_MSG_HEADER_ST *pstMsg);
/*********************************************************************************************
   
  brief      消息发送接口
  param[in]  lSock:指定发送消息的sock
  param[in]  *pstMsg:消息指针
  return     VOS_OK:消息发送成功
             其他返回值:消息发送失败，具体原因参考错误码
   注意事项： 
1、在未指定g_pfMsgSendHook为空的时候，直接调用ATP_MSG_SendEx可能导致消息延迟发送
2、pstMsg的内存如果是malloc的，注意在调用ATP_MSG_SendEx之后进行释放
retval  ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_SendEx(VOS_INT32 lSock, ATP_MSG_HEADER_ST *pstMsg);


/*********************************************************************************************
   
  brief      发送消息，并且接收其回应消息
  param[in]  *pstMsg: 待发送的消息
  param[out] **ppstResp: 回应消息
  param[in]  ulTimeout: 超时时间，为0表示永久阻塞，单位ms
  return     VOS_OK:消息发送/接收成功
             其他返回值:消息发送/接收失败，具体原因参考错误码
   注意事项： 
1、pstMsg的内存如果是malloc的，注意在调用ATP_MSG_SendAndRecv之后进行释放
2、如果收到了回应消息，ppstResp中有内存申请，在使用完毕之后需要释放
retval  ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
        ATP_MSG_RET_TIMEOUT:回复消息接收超时
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_SendAndRecv(ATP_MSG_HEADER_ST  *pstMsg,
                                        ATP_MSG_HEADER_ST        **ppstResp,
                                        VOS_UINT32               ulTimeout);
/*********************************************************************************************
   
  brief      发送消息，并且接收其回应消息,校验发送消息的SendApp Name
              与接收消息的RecvApp Name是否相同
  param[in]  *pstMsg: 待发送的消息
  param[out] **ppstResp: 回应消息
  param[in]  ulTimeout: 超时时间，为0表示永久阻塞，单位ms
  return     VOS_OK:消息发送/接收成功
             其他返回值:消息发送/接收失败，具体原因参考错误码
   注意事项： 
1、pstMsg的内存如果是malloc的，注意在调用ATP_MSG_SendAndRecvWithAppName之后进行释放
2、如果收到了回应消息，ppstResp中有内存申请，在使用完毕之后需要释放
retval  ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
        ATP_MSG_RET_TIMEOUT:回复消息接收超时
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_SendAndRecvWithAppName(ATP_MSG_HEADER_ST   *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);

/*********************************************************************************************
  author      
  brief      异步回调消息处理    
  param[in]  *pstMsg: 发送消息
  param[in]  callback: 回调函数
  param[in]  ulTimeout: 超时时间
  param[in]  *pvData: 回调函数入参
  return     VOS_OK:消息发送接收成功
             其他返回值:消息发送接收失败，具体失败值参考错误码
   注意事项： 
1、 pstMsg的内存如果是malloc的，注意在调用ATP_MSG_AsyncSendAndRecv之后进行释放
2、 pvData需要指向接收到消息体中的结构体，需要在调用ATP_MSG_AsyncSendAndRecv进行malloc
3、 pvData使用完毕后需要释放
该函数调用为同步函数，多线程场景下概率出现阻塞
调用者必须确保该进程为单线程，如果为多线程请使用  ATP_MSG_Send 函数
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
         ATP_MSG_RET_NOT_INITED:消息未初始化
         ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
         ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
         ATP_MSG_RET_PEER_DEAD:socket已经被关闭
         ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_AsyncSendAndRecv(ATP_MSG_HEADER_ST  *pstMsg, VOS_UINT32 ulTimeout, VOS_VOID *pvData, PfMsgWatcherProc callback);
/*********************************************************************************************
   
  brief      消息发送并接收回应消息的MSGDATA  
  param[in]  *pcDest: 消息接收方
  param[in]  ulMsgType: 消息类型
  param[in]  ulMsgData: 消息中携带MSGDATA
  param[in]  ulTimeout: 消息超时时间
  param[in]  *pulMsgData: 返回消息中的MSGDATA
  return     VOS_OK:消息发送接收成功
             其他返回值:消息发送接收失败，具体失败值参考错误码
   注意事项： 
1、 暂无
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
         ATP_MSG_RET_NOT_INITED:消息未初始化
         ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
         ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
         ATP_MSG_RET_PEER_DEAD:socket已经被关闭
         ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
         ATP_MSG_RET_TIMEOUT:回复消息接收超时
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendAndRecvMsgData(const VOS_CHAR * pcDest, VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData, VOS_UINT32 ulTimeout, VOS_UINT32 *pulMsgData);
/*********************************************************************************************
   
  brief      根据消息类型接收消息  
  param[in]  ulMsgType: 消息类型
  param[out] **ppstResp: 接收到的消息
  param[in]  ulTimeout: 消息超时时间
  return     VOS_OK:消息接收成功
             其他返回值:消息接收失败，具体失败值参考错误码
   注意事项： 
1、 接收到的消息ppstResp有内存申请，使用完毕需要释放
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
         ATP_MSG_RET_PEER_DEAD:socket已经被关闭
         ATP_MSG_RET_TIMEOUT:回复消息接收超时
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvWithType(VOS_UINT32              ulMsgType,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);
/*********************************************************************************************
   
  brief      接收消息  
  param[in]  *pstMsg: 发送消息结构
  param[out] **ppstResp: 接收到的消息
  param[in]  ulTimeout: 消息超时时间
  return     VOS_OK:消息接收成功
             其他返回值:消息接收失败，具体失败值参考错误码
   注意事项： 
1、 接收到的消息ppstResp有内存申请，使用完毕需要释放
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
         ATP_MSG_RET_PEER_DEAD:socket已经被关闭
         ATP_MSG_RET_TIMEOUT:回复消息接收超时
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvResponse(const ATP_MSG_HEADER_ST *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);
/*********************************************************************************************
   
  brief      接收消息,校验发送消息的SendApp Name
              与接收消息的RecvApp Name是否相同
  param[in]  *pstMsg: 发送消息结构
  param[out] **ppstResp: 接收到的消息
  param[in]  ulTimeout: 消息超时时间
  return     VOS_OK:消息接收成功
             其他返回值:消息接收失败，具体失败值参考错误码
   注意事项： 
1、 接收到的消息ppstResp有内存申请，使用完毕需要释放
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
         ATP_MSG_RET_PEER_DEAD:socket已经被关闭
         ATP_MSG_RET_TIMEOUT:回复消息接收超时
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvResponseWithAppName(const ATP_MSG_HEADER_ST *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);

/*********************************************************************************************
   
  brief      从socket接收消息
  param[in]  sSock: socket描述符
  param[out] **ppstResp: 接收到的消息
  param[in]  ulTimeout: 消息超时时间，为0表示永久阻塞，单位ms
  return     VOS_OK:消息接收成功
             其他返回值:消息接收失败，具体失败值参考错误码
   注意事项： 
1、 接收到的消息ppstResp有内存申请，使用完毕需要释放
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
         ATP_MSG_RET_PEER_DEAD:socket已经被关闭
         ATP_MSG_RET_TIMEOUT:回复消息接收超时
         ATP_MSG_RET_MEM_ERR:内存申请失败
         ATP_MSG_RET_INTERNAL_ERR:消息接收时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_Recv(VOS_INT32           sSock,
                              ATP_MSG_HEADER_ST   **ppstMsg,
                              VOS_UINT32          ulTimeout);
/*********************************************************************************************
   
  brief      从socket接收消息，根据字节序调整数据
  param[in]  sSock: socket描述符
  param[out] **ppstResp: 接收到的消息
  param[in]  ulTimeout: 消息超时时间，为0表示永久阻塞，单位ms
  param[in]  bWithEndian: 字节序
  return     VOS_OK:消息接收成功
             其他返回值:消息接收失败，具体失败值参考错误码
   注意事项： 
1、 接收到的消息ppstResp有内存申请，使用完毕需要释放
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
         ATP_MSG_RET_PEER_DEAD:socket已经被关闭
         ATP_MSG_RET_TIMEOUT:回复消息接收超时
         ATP_MSG_RET_MEM_ERR:内存申请失败
         ATP_MSG_RET_INTERNAL_ERR:消息接收时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvWithEndian(VOS_INT32             sSock,
                              ATP_MSG_HEADER_ST     **ppstMsg,
                              VOS_UINT32            ulTimeout,
                              VOS_BOOL              bWithEndian);

/*
 *    Message Utilities
 */
/*********************************************************************************************
   
  brief      修改trace消息的fd
  param[in]  lNewFd: 跟踪tracelog的fd
  return     
   注意事项： 
1、 暂无
  retval 
***********************************************************************************************/
VOS_VOID ATP_MSG_TraceProc(VOS_INT32 lNewFd);
/*********************************************************************************************
   
  brief      注册消息默认处理函数
  param[in]  *pstMsg: 接收消息结构体信息
  return     
   注意事项： 
1、 暂无
  retval 
***********************************************************************************************/
VOS_VOID ATP_MSG_MsgFilterProc(const ATP_MSG_HEADER_ST *pstMsg);
/*********************************************************************************************
   
  brief      申请一个消息体长度为ulMsgSize的消息
  param[in]  *pstMsg: 接收消息结构体信息
  return     申请成功，返回指针，申请失败，返回NULL
   注意事项： 
1、 这个函数有内存申请，且返回值做了偏移，在释放的时候需要先调用ATP_MSG_GetMsgHead获取头指针，之后进行free
  retval 
***********************************************************************************************/
VOS_VOID* ATP_MSG_GetMsgBlock(VOS_UINT32 ulMsgSize);
/*********************************************************************************************
   
  brief      根据Msg结构的头指针查找MSG BODY
  param[in]  *pstMsgHead: 消息结构头指针
  return     查找成功，返回指针，查找失败，返回NULL
   注意事项： 
1、 暂无
  retval 
***********************************************************************************************/
VOS_VOID* ATP_MSG_GetMsgByHead(ATP_MSG_HEADER_ST* pstMsgHead);
/*********************************************************************************************
   
  brief      根据Msg Body指针查找MSG Header
  param[in]  *pvMsg: 消息结构Body指针
  return     查找成功，返回指针，查找失败，返回NULL
   注意事项： 
1、 暂无
  retval 
***********************************************************************************************/
ATP_MSG_HEADER_ST* ATP_MSG_GetMsgHead(VOS_VOID* pvMsg);

/*
 *    Message Structure Utilities
 */

/*********************************************************************************************
   
  brief      通过消息发送FD
  param[in]  lFdToSend: 待发送的FD指针
  return     VOS_OK:发送成功
             其他返回值:发送失败，原因参考错误码
   注意事项： 
1、 暂无
  retval ATP_MSG_RET_NOT_INITED:消息未初始化
         ATP_MSG_RET_MEM_ERR:内存不足，malloc失败
         ATP_MSG_RET_INTERNAL_ERR:消息发送失败
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendFd(VOS_INT32 lFdToSend);
/*********************************************************************************************
   
  brief      通过消息接收FD
  param[out] *plFdToRecv: 接收到的FD
  param[in]  ulTimeout: 接收超时时间
  return     VOS_OK:接收成功
             其他返回值:接收失败，原因参考错误码
   注意事项： 
1、 暂无
  retval ATP_MSG_RET_PARA_ERR:参数输入错误
         ATP_MSG_RET_NOT_INITED:消息没有初始化
         ATP_MSG_RET_MEM_ERR:内存不足，malloc失败
         ATP_MSG_RET_INTERNAL_ERR:消息发送失败
         ATP_MSG_RET_TIMEOUT:接收超时
         ATP_MSG_RET_PEER_DEAD:socket已经被关闭
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvFd(VOS_INT32 *plFdToRecv, VOS_UINT32 ulTimeout);

/*********************************************************************************************
   
  brief      简单消息构造接口
  param[in]  *pstMsg: 消息结构指针
  param[in]  *pcDest: 消息接收方
  param[in]  ulMsgType: 消息类型
  param[in]  ulMsgData: 简单消息发送内容
  return     
   注意事项： 
1、 消息结构的内存需要在外部指定，如果外部有申请内存，注意释放
2、 本消息只能携带数字型的消息内容发送，对于结构体和字符串需要调用其他接口进行构造
  retval 
***********************************************************************************************/
VOS_VOID ATP_MSG_SimpleBuilder(ATP_MSG_HEADER_ST *pstMsg, const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData);
/*********************************************************************************************
   
  brief      同步消息统一构造回应消息接口
  param[in]  *pstReq: 消息结构指针
  param[in]  ulBuffLen: 回应消息携带内容长度，与pvMsgBuff对应
  param[in]  pvMsgBuff: 回应消息携带内容
  param[in]  ulMsgData: 回应消息携带内容
  return     构造成功，返回消息指针
             构造失败，返回NULL
   注意事项： 
1、 调用这个函数存在内存申请，用完之后需要释放
2、 如果回应消息只需要携带一个数字，直接填充ulMsgData即可，pvMsgBuff可以为空
  retval 
***********************************************************************************************/
ATP_MSG_HEADER_ST *ATP_MSG_MsgResponseBuilder(const ATP_MSG_HEADER_ST *pstReq, VOS_UINT32 ulMsgData,
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen);
/*********************************************************************************************
   
  brief      构造简单消息，并发送
  param[in]  *pcDest: 消息接收方
  param[in]  ulMsgType: 消息类型
  param[in]  ulMsgData: 消息携带内容
  return     VOS_OK:构造发送成功
             其他:构造或发送失败
   注意事项： 
1、 该接口只能构造简单消息，消息中只能携带数字，如果需要发送结构体或者字符串，需要调用其他接口
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendSimpleMsg(const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData);
/*********************************************************************************************
   
  brief      构造携带序列号的简单消息，并发送
  param[in]  *pcDest: 消息接收方
  param[in]  ulMsgType: 消息类型
  param[in]  ulMsgData: 消息携带内容
  param[in]  ulSeqNum: 序列号
  return     VOS_OK:构造发送成功
             其他:构造或发送失败
   注意事项： 
1、 该接口只能构造简单消息，消息中只能携带数字，如果需要发送结构体或者字符串，需要调用其他接口
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendSimpleMsgWithSeqNum(const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData, VOS_UINT32 ulSeqNum);

/*********************************************************************************************
   
  brief      注册事件关注
  param[in]  ulEvtType: 关注事件
  return     VOS_OK:构造发送成功
             其他:构造或发送失败
   注意事项： 
1、 暂无
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
#define ATP_MSG_SubscribeEvent(ulEvtType)   ATP_MSG_SendSimpleMsg(NULL, ATP_MSG_SUBSCRIBE_EVT, (ulEvtType))
/*********************************************************************************************
   
  brief      去注册事件关注
  param[in]  ulEvtType: 关注事件
  return     VOS_OK:构造发送成功
             其他:构造或发送失败
   注意事项： 
1、 暂无
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
#define ATP_MSG_UnSubscribeEvent(ulEvtType) ATP_MSG_SendSimpleMsg(NULL, ATP_MSG_UNSUBSCRIBE_EVT, (ulEvtType))
/*********************************************************************************************
   
  brief      为其他进程注册事件关注
  param[in]  ulEvtType: 事件类型
  param[in]  *pcName: 进程名字
  return     VOS_OK:注册成功
             其他:注册失败
   注意事项： 
1、 该函数用于给其他进程注册事件关注，注意在注册的进程内部实现事件发生时的回调函数
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SubscribeEventForOtherApp(VOS_UINT32 ulEvtType, const VOS_CHAR *pcName);
/*********************************************************************************************
   
  brief      为其他进程去注册事件关注
  param[in]  ulEvtType: 事件类型
  param[in]  *pcName: 进程名字
  return     VOS_OK:去注册成功
             其他:去注册失败
   注意事项： 
1、 该函数用于给其他进程去注册事件关注，注意在其他进程内部需要知道这个去注册操作
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_UnSubscribeEventForOtherApp(VOS_UINT32 ulEvtType, const VOS_CHAR *pcName);
/*********************************************************************************************
   
  brief      构造消息内容并发送
  param[in]  *pcProcName: 消息接收方
  param[in]  ulMsgType: 事件类型
  param[in]  *pvMsgBuff: 消息内容
  param[in]  ulBuffLen: 消息内容长度
  return     VOS_OK:发送成功
             其他:发送失败
   注意事项： 
1、 该函数用于需要发送结构体或者字符串的场景
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendMsgData(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType,
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen);
/*********************************************************************************************
   
  brief      获取当前进程MSGCTL个数
  param[in]  *pcName: 消息接收方
  return     VOS_OK:发送成功
             其他:发送失败
   注意事项： 
1、 暂无
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
        ATP_MSG_RET_TIMEOUT:回复消息接收超时
***********************************************************************************************/
VOS_UINT32 ATP_MSG_GetNumOfProcesses(const VOS_CHAR *pcName);
/*********************************************************************************************
   
  brief      当前进程安全退出
  param[in]  *pcName: 退出进程名称
  return     VOS_OK:成功
             其他:失败
   注意事项： 
1、 暂无
  retval ATP_MSG_RET_PARA_ERR:消息指针入参错误 
        ATP_MSG_RET_NOT_INITED:消息未初始化
        ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
        ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
        ATP_MSG_RET_PEER_DEAD:socket已经被关闭
        ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
        ATP_MSG_RET_TIMEOUT:回复消息接收超时
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SafeExitProcesses(const VOS_CHAR *pcName);
/*********************************************************************************************
   
  brief      拷贝消息
  param[in]  *pstMsg: 待拷贝消息
  return     成功，返回拷贝后的消息指针
             失败，返回NULL
   注意事项： 
1、 暂无
  retval 
***********************************************************************************************/
ATP_MSG_HEADER_ST *ATP_MSG_Dup(const ATP_MSG_HEADER_ST *pstMsg);

#include "notifyutil.h"
#include "fileutil.h"
#include "sysapi.h"
#include "strutil.h"

typedef struct tagATP_MSG_HDL_LIST_ST
{
    struct tagATP_MSG_HDL_LIST_ST       *pstNext;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulPriority;
    AtpMsgProc                          pfProc;
    AtpSyncMsgProc                      pfSyncProc;
} ATP_MSG_HDL_LIST_ST;
/*********************************************************************************************
  author      
  brief      异步消息注册回调函数接口
  param[in]  ulMsgType : 消息类型
  param[in]  pfProc : 异步消息处理回调函数
  param[in]  ulPriority : 异步消息处理优先级
  param[in]  **ppstMsgHdl:回调函数入参消息体
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval  ATP_MSG_RET_MEM_ERR:malloc失败，内存不足          
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RegSyncMsgProc(VOS_UINT32 ulMsgType, AtpSyncMsgProc pfProc, VOS_UINT32 ulPriority, ATP_MSG_HDL_LIST_ST **ppstMsgHdl);

/*********************************************************************************************
   
  brief      同步消息注册回调函数接口
  param[in]  ulMsgType : 消息类型
  param[in]  pfProc : 同步消息处理回调函数
  param[in]  ulPriority : 同步消息处理优先级
  param[in]  **ppstMsgHdl:回调函数入参消息体
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval  ATP_MSG_RET_MEM_ERR:malloc失败，内存不足          
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RegMsgProc(VOS_UINT32 ulMsgType, AtpMsgProc pfProc, VOS_UINT32 ulPriority, ATP_MSG_HDL_LIST_ST **ppstMsgHdl);
/*********************************************************************************************
   
  brief      从消息处理列表中删除当前消息处理结构
  param[in]  *ppstMsgHdl:待删除消息处理结构
  return     
  
   注意事项： 
1、 暂无
  retval          
***********************************************************************************************/
VOS_VOID ATP_MSG_UnRegMsgProc(ATP_MSG_HDL_LIST_ST *ppstMsgHdl);
/*********************************************************************************************
   
  brief      默认消息处理函数
  param[in]  *pstMsg:接收到的消息
  return     
  
   注意事项： 
1、 进程需要优先调用这个函数，才能通过注册消息回调函数的方式来处理消息
  retval          
***********************************************************************************************/
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
#include "nlsapi.h"
/*
 *	Kernel version api
 */
typedef enum tagATP_LINUX_VERSION_EN
{
	ATP_LINUX_VERSION_2_6_21 = 0,
	ATP_LINUX_VERSION_2_6_30 = 1,
	ATP_LINUX_VERSION_2_6_36 = 2,
} ATP_LINUX_VERSION_EN;

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

#if defined(SUPPORT_ATP_SMARTHOME) || defined(SUPPORT_ATP_OPEN_EE)
    #define ATP_MSG_WEB_RESTFUL_LEN    (128)
#else
    #define ATP_MSG_WEB_RESTFUL_LEN    (64)
#endif

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
/*********************************************************************************************
   
  brief      注册restful处理回调函数
  param[in]  *pszModuleName:restful接口对应的模块名称
  param[in]  *pstRestfulAPI:restful接口API名称和对应回调函数
  param[in]  bExactMatch:是否进行额外匹配
  return     VOS_OK:注册成功
             其他:失败
  
   注意事项： 
1、 pstRestfulAPI对应的是一个数组，一个api对应一个回调函数
  static ATP_UTIL_RESTFUL_ST m_astStaRestAPIExs[] =
  {
      {"wps-pbc",             sta_wps_pbc_restful},
      {"wps-cancel",          sta_wps_cancel_restful},
      {NULL, NULL}
  } ;

  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_MEM_ERR:malloc失败，内存不足
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RegRestfulProcsEx(
                const VOS_CHAR            *pszModuleName,
                const ATP_UTIL_RESTFUL_ST *pstRestfulAPI,
                VOS_BOOL                  bExactMatch);
/*********************************************************************************************
   
  brief      注册restful处理回调函数
  param[in]  *pszModuleName:restful接口对应的模块名称
  param[in]  *pstRestfulAPI:restful接口API名称和对应回调函数
  return     VOS_OK:注册成功
             其他:失败
  
   注意事项： 
1、 pstRestfulAPI对应的是一个数组，一个api对应一个回调函数
  static ATP_UTIL_RESTFUL_ST m_astStaRestAPIExs[] =
  {
      {"wps-pbc",             sta_wps_pbc_restful},
      {"wps-cancel",          sta_wps_cancel_restful},
      {NULL, NULL}
  } ;

  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_MEM_ERR:malloc失败，内存不足
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RegRestfulProcs(
                const VOS_CHAR* pszModuleName,
                const ATP_UTIL_RESTFUL_ST *pstRestfulAPI);

/*********************************************************************************************
   
  brief      构造restful请求消息
  param[in]  enType:restful类型
  param[in]  ulIntfType:restful接口注册消息配置工具名称
  param[in]  *pcModName:restful接口模块名
  param[in]  *pcFuncName:restful接口函数名
  param[in]  *pcBody:restful接口请求报文
  param[in]  lBodyLen:restful接口请求报文长度
  return     构造成功消息体:成功
             NULL:失败
  
   注意事项： 
1、 该函数有内存分配，在使用完毕后需要删除

  retval  
***********************************************************************************************/
ATP_MSG_HEADER_ST *ATP_MSG_BuildRestfulReqMsg(REQ_TYPE enType, VOS_UINT32 ulIntfType, const VOS_CHAR *pcModName,
                                                const VOS_CHAR *pcFuncName, const VOS_CHAR *pcBody, const VOS_INT32 lBodyLen);
/*********************************************************************************************
   
  brief      构造restful回应消息
  param[in]  *pcProcName:restful接口回应消息发送方
  param[in]  ulMsgType:restful接口回应消息类型
  param[in]  *pvMsgBuff:restful接口回应消息消息体
  param[in]  ulBuffLen:restful接口回应消息消息体长度
  param[in]  ulMsgData:restful接口回应消息MsgData
  param[in]  ulSeqNum:restful接口回应消息序列号
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 该函数有内存分配，在使用完毕后需要删除

  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_MEM_ERR:malloc失败，内存不足
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendRestfulResponseMsg(const VOS_CHAR *pcProcName, VOS_UINT32 ulMsgType,
    const VOS_CHAR* pvMsgBuff, VOS_UINT32 ulBuffLen, VOS_UINT32 ulMsgData, VOS_UINT32 ulSeqNum);
/*********************************************************************************************
  author      
  brief      构造消息
  param[in]  *pcProcName:消息发送方
  param[in]  ulMsgType:消息类型
  param[in]  *pvMsgBuff:消息消息体
  param[in]  ulBuffLen:消息消息体长度
  param[in]  ulMsgData:消息MsgData
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 该函数有内存分配，在使用完毕后需要删除

  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_MEM_ERR:malloc失败，内存不足
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendMsgDataWithData(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType,
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen, VOS_UINT32 ulMsgData);
/*********************************************************************************************
  author      
  brief      构造消息
  param[in]  *pcProcName:消息发送方
  param[in]  ulMsgType:消息类型
  param[in]  *pvMsgBuff:消息消息体
  param[in]  ulBuffLen:消息消息体长度
  param[in]  ulMsgData:消息MsgData
  param[in]  ulSeqNum:restful接口回应消息序列号
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 该函数有内存分配，在使用完毕后需要删除

  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_MEM_ERR:malloc失败，内存不足
***********************************************************************************************/
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

/*********************************************************************************************
  author      
  brief      统一reboot接口,先执行定制操作，然后发消息到mic 重启        
  param[in]  ulRebootType:重启类型
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 如果传入null，使用默认的reboot操作

  retval  
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_Reboot(VOS_UINT32 ulRebootType);
#include "socketutil.h"
#endif
#include "cfmdbapi.h"
#include "dmmsgapi.h"
#include "cfgmsgapi.h"

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
