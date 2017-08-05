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



#ifndef __ATP_LOOP_API_H__
#define __ATP_LOOP_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * Public API for LOOP
 */
struct tagATP_UV_LOOP_ST;
typedef struct tagATP_UV_LOOP_ST ATP_UV_LOOP_ST;

VOS_VOID ATP_UV_LoopInit(ATP_UV_LOOP_ST *pstLoop);

ATP_UV_LOOP_ST *ATP_UV_LoopGetDefault();

VOS_VOID ATP_UV_LoopUpdateSelectTimeout(ATP_UV_LOOP_ST *pstLoop, struct timeval *timeout);

VOS_UINT32 ATP_UV_LoopGetIdleTime(const ATP_UV_LOOP_ST *pstLoop);

VOS_VOID ATP_UV_LoopSetIdleTime(ATP_UV_LOOP_ST *pstLoop, VOS_UINT32 ulIdleTime);

VOS_INT32 ATP_UV_LoopGetMaxFd(const ATP_UV_LOOP_ST *pstLoop);

VOS_UINT32 ATP_UV_LoopRun(ATP_UV_LOOP_ST *pstLoop, VOS_UINT32 ulIdleTime);

VOS_VOID ATP_UV_LoopStop(ATP_UV_LOOP_ST *pstLoop);

VOS_UINT32 ATP_UV_LoopSafeFree(ATP_UV_LOOP_ST *pstLoop, VOS_VOID *pvData);

/**
 * Public API for Handle
 */
enum
{
    // Internal FLAG
    ATP_UV_WATCHER_FLAG_ACTIVE  = 0x4000,
    ATP_UV_WATCHER_FLAG_REF     = 0x2000,
    ATP_UV_WATCHER_FLAG_CLOSING = 0x1000,

    // Internal TYPE
    ATP_UV_TYPE_TIMER           = 0x0001,
    ATP_UV_TYPE_IDLE            = 0x0002,
    ATP_UV_TYPE_IO              = 0x0004,

    // Extended TYPE
    ATP_UV_TYPE_SOCKBASE        = 0x0010,
    ATP_UV_TYPE_MSG             = 0x0020,
    ATP_UV_TYPE_UDP             = 0x0040,
};

#define ATP_UV_IS_WATCHER_CLOSE(watcher)(watcher->ulFlag & ATP_UV_WATCHER_FLAG_CLOSING)
#define ATP_UV_IS_TIMER(watcher)        (watcher->ulFlag & ATP_UV_TYPE_TIMER)
#define ATP_UV_IS_IO(watcher)           (watcher->ulFlag & ATP_UV_TYPE_IO)
#define ATP_UV_IS_SOCKBASE(watcher)     (watcher->ulFlag & ATP_UV_TYPE_SOCKBASE)
#define ATP_UV_IS_MSG(watcher)          (watcher->ulFlag & ATP_UV_TYPE_MSG)
#define ATP_UV_IS_IDLE(watcher)         (watcher->ulFlag & ATP_UV_TYPE_IDLE)

/**
 *  Base Class for all other watchers
 *  Do not change this structure
 *  Other inherited structues must be the same as this one
 */
typedef struct tagATP_UV_WATCHER_ST
{
    struct tagATP_UV_WATCHER_ST *pstNext;
    struct tagATP_UV_LOOP_ST    *pstLoop;
    VOS_UINT32                  ulFlag;
    VOS_VOID                    *pvData;
} ATP_UV_WATCHER_ST;
typedef VOS_UINT32 (*PFWatcherIterateProc)(const ATP_UV_WATCHER_ST *pstWatcher, const VOS_VOID *pvCookie);

VOS_UINT32 ATP_UV_WatcherInit(ATP_UV_LOOP_ST *pstLoop, ATP_UV_WATCHER_ST *pstWatcher, VOS_UINT32 ulType);
VOS_UINT32 ATP_UV_WatcherStart(ATP_UV_WATCHER_ST *pstWatcher);
VOS_UINT32 ATP_UV_WatcherDelete(ATP_UV_WATCHER_ST *pstWatcher);
VOS_UINT32 ATP_UV_WatcherIterateItem(const ATP_UV_LOOP_ST* pstLoop, const VOS_VOID *pvCookie, PFWatcherIterateProc pfIterateProc);

/**
 * Public API for Timer Watcher
 */
typedef VOS_VOID (* PfUtilTimerProc)(VOS_VOID *pvArg);

typedef struct tagATP_UTIL_TIMER_ST
{
    // Inherited from ATP_UV_WATCHER_ST, must not change
    struct tagATP_UTIL_TIMER_ST     *pstNext;
    struct tagATP_UV_LOOP_ST        *pstLoop;
    VOS_UINT32                      ulFlag;
    VOS_VOID                        *pvData;

    // Extended fields add here
    struct timeval                  stExpireTime;/*!<  When the event will expire, 0 means stopped timer*/
    VOS_UINT32                      ulPeriod;   /*!<  The event period, 0 means stopped timer*/
    VOS_UINT32                      ulRepeat;/*!<  Event repeat count, 0 means repeat forever*/
    PfUtilTimerProc                 pfProc;
} ATP_UTIL_TIMER_ST;

VOS_UINT32 ATP_UV_TimerInit(ATP_UV_LOOP_ST *pstLoop, ATP_UTIL_TIMER_ST *pstTimerWatcher);
VOS_UINT32 ATP_UV_TimerStart(ATP_UTIL_TIMER_ST *pstTimerWatcher,
                            VOS_UINT32      ulPeriod,   // ms
                            VOS_UINT32      ulRepeatCnt,
                            PfUtilTimerProc pfProc,
                            VOS_VOID        *pvData);

VOS_UINT32 ATP_UV_TimerDelete(ATP_UTIL_TIMER_ST *pstTimerWatcher);
VOS_UINT32 ATP_UV_RunTimers(ATP_UV_LOOP_ST *pstLoop, struct timeval *pstNextWakeupIntv);

/*
 * Timer utilities
 */
ATP_UTIL_TIMER_ST *ATP_UTIL_TimerAdd(
                            VOS_UINT32      ulPeriod,    /*!<  MSeconds*/
                            VOS_UINT32      ulRepeatCnt,
                            PfUtilTimerProc pfProc,
                            VOS_VOID        *pvData);
/*
  * Do not call this function in a timer callback function
  */
VOS_VOID ATP_UTIL_TimerDel(ATP_UTIL_TIMER_ST *pstTimer);

VOS_VOID ATP_UTIL_TimerChgPeriod(ATP_UTIL_TIMER_ST *pstTimer, VOS_UINT32 ulPeriod);

VOS_VOID ATP_UTIL_TimerGetIntv(const struct timeval* pstNewTime,
                               const struct timeval* pstOldTime,
                               struct timeval* pstDelta);

/**
 * Public API for Idle Watcher
 */
struct tagATP_UV_IDLE_ST;
typedef struct tagATP_UV_IDLE_ST ATP_UV_IDLE_ST;
typedef VOS_VOID (*PfIdleProc)(ATP_UV_IDLE_ST *pstIdleWatcher);
struct tagATP_UV_IDLE_ST
{
    // Inherited from ATP_UV_WATCHER_ST, must not change
    struct tagATP_UV_IDLE_ST    *pstNext;
    struct tagATP_UV_LOOP_ST    *pstLoop;
    VOS_UINT32                  ulFlag;
    VOS_VOID                    *pvData;

    // Extended fields add here
    PfIdleProc                  pfIdleProc;
} ;

ATP_UV_IDLE_ST *ATP_UV_IdleStart(ATP_UV_LOOP_ST *pstLoop, PfIdleProc pfProc);
VOS_UINT32 ATP_UV_IdleStop(ATP_UV_IDLE_ST *pstIdleWatcher);

/**
 * Public API for IO Watcher
 */
#define ATP_UV_IO_READ  1
#define ATP_UV_IO_WRITE 2
#define ATP_UV_IO_ERROR 4
#define ATP_UV_IO_EVENT_MASK (ATP_UV_IO_READ | ATP_UV_IO_WRITE | ATP_UV_IO_ERROR)

struct tagATP_UV_IO_ST;
typedef struct tagATP_UV_IO_ST ATP_UV_IO_ST;

typedef VOS_VOID (* PfIOProc)(ATP_UV_IO_ST *pstIOWatcher, VOS_UINT32 ulEvent);
struct tagATP_UV_IO_ST
{
    // Inherited from ATP_UV_WATCHER_ST, must not change
    struct tagATP_UV_IO_ST      *pstNext;
    struct tagATP_UV_LOOP_ST    *pstLoop;
    VOS_UINT32                  ulFlag;
    VOS_VOID                    *pvHook;

    // Extended fields add here
    VOS_INT32                   fd;
    VOS_UINT32                  ulEvents;
    PfIOProc                    pfIOProc;
};

VOS_UINT32 ATP_UV_IOInit(ATP_UV_LOOP_ST *pstLoop, ATP_UV_IO_ST *pstIOWatcher, VOS_INT32 lFd, PfIOProc pfProc);
VOS_UINT32 ATP_UV_IOStart(ATP_UV_IO_ST *pstIOWatcher, VOS_UINT32 ulEvent);
VOS_UINT32 ATP_UV_IOStop(ATP_UV_IO_ST *pstIOWatcher, VOS_UINT32 ulEvents);
VOS_UINT32 ATP_UV_IODelete(ATP_UV_IO_ST *pstIOWatcher);
VOS_UINT32 ATP_UV_IOForcedLoop(ATP_UV_IO_ST *pstIOWatcher, VOS_UINT32 ulEvent);
VOS_UINT32 ATP_UV_IOSkipLoop(const ATP_UV_IO_ST *pstIOWatcher, VOS_BOOL bSkip);
ATP_UV_IO_ST* ATP_UV_IOFindByFd(ATP_UV_LOOP_ST *pstLoop, VOS_INT32 fd);

#ifdef SUPPORT_ATP_DEBUG_CMD
VOS_VOID ATP_UV_IORegDbgInfo(PFWatcherIterateProc pfProc);
#endif

/**
 * Public API for MSG Watcher
 */
struct tagATP_UV_MSG_ST;
typedef struct tagATP_UV_MSG_ST  ATP_UV_MSG_ST;

#define ATP_UV_WATCHER_OK       (0)
#define ATP_UV_WATCHER_TIMEOUT  (1)
typedef VOS_UINT32 (*PfMsgWatcherProc)(const VOS_VOID *pstMsg, VOS_UINT32 ulStatus, VOS_VOID * pvData);

// msg watcher
typedef VOS_UINT32 (*PfMsgDataLenProc)(const VOS_VOID *pstMsg, VOS_UINT32 *pulFlag);
typedef VOS_VOID (*PfMsgProc)(const VOS_VOID *pstMsg);
typedef VOS_BOOL (*PfMsgMatchProc)(const VOS_VOID *pstMsg, VOS_UINT32 ulType, VOS_UINT32 ulSeqNum);
typedef VOS_UINT32 (*PfMsgRecvFromFileProc)(VOS_VOID **pstMsg);

typedef struct tagATP_UV_MSG_WATCHER_ST
{
    struct tagATP_UV_MSG_WATCHER_ST *pstNext;
    VOS_UINT32          ulMsgType;
    VOS_UINT32          ulSeqNum;
    VOS_VOID            *pvData;
    PfMsgWatcherProc    pfWatcherProc;
    ATP_UV_MSG_ST       *handle;
    ATP_UTIL_TIMER_ST   *pstTimer;
}ATP_UV_MSG_WATCHER_ST;

//!\brief MSG
/*!
 *
 */
struct tagATP_UV_MSG_ST
{
    // Inherited from ATP_UV_IO_ST, must not change
    struct tagATP_UV_LOOP_ST    *pstLoop;
    ATP_UTIL_LIST_ST            stListHandleRef;
    VOS_UINT32                  ulFlag;
    VOS_VOID                    *pvData;
    VOS_INT32                   fd;
    VOS_UINT32                  ulEvents;
    PfIOProc                    pfIOProc;

    // Extended fields add here
    VOS_UINT32                  ulHeaderSize;           //! msg 头长度
    PfMsgDataLenProc            pfMsgGetDataLen;        //! 获取消息数据长度
    PfMsgProc                   pfMsgProc;              //! 消息处理函数
    PfMsgMatchProc              pfMsgMatchProc;         //! 消息类型消息号是否匹配
    PfMsgRecvFromFileProc       pfMsgRecvFromFile;    //! 从文件接收消息

    ATP_UV_MSG_WATCHER_ST       *pstWatcherList;    //! 异步消息观察者

    //PfMsgSyncWatcherProc pfMsgSyncWatcherProc;  //! 同步消息处理函数
    //PfMsgQueryAppendProc pfMsgQueryAppendProc;
    //PfMsgQueryClearProc  pfMsgQueryClearProc;
    //VOS_UINT32          ulMsgType;
    //VOS_UINT32          ulSeqNum;
    //VOS_UINT32          bSyncWatcher;
};

VOS_UINT32 ATP_UV_MsgInit(ATP_UV_LOOP_ST *pstLoop, ATP_UV_MSG_ST *pstMsgWatcher, VOS_INT32 lFd, PfMsgProc pfProc);
VOS_UINT32 ATP_UV_MsgStart(ATP_UV_MSG_ST *pstMsgWatcher);
VOS_UINT32 ATP_UV_MsgDelete(ATP_UV_MSG_ST *pstMsgWatcher);

VOS_UINT32 ATP_UV_MsgStartWatcher(ATP_UV_MSG_ST *pstMsgWatcher, VOS_UINT32 ulMsgType, VOS_UINT32 ulSeqNum, VOS_UINT32 ulTimeout, VOS_VOID *pvData,  PfMsgWatcherProc callback);


/**
 * Utility API
 */

//#define ATP_TIME_DEBUG 1
#ifdef ATP_TIME_DEBUG
VOS_VOID ATP_Socket_InputTimeToFile(VOS_CHAR *pcInputChar);
#endif

#ifdef ATP_DEBUG
#define ATP_UV_DEBUG(format, args...)       {printf("FILE: %s LINE: %d: ", __FILE__, __LINE__);printf(format, ##args);}
#else
#define ATP_UV_DEBUG(x...)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif
