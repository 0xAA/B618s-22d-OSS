/*****************************************************************************
 *               Copyright (C) 2011, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/



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
    ATP_UV_TYPE_PROCESS         = 0x0008,

    // Extended TYPE
    ATP_UV_TYPE_SOCKBASE        = 0x0010,
    ATP_UV_TYPE_MSG             = 0x0020,
    ATP_UV_TYPE_UDP             = 0x0040
};

#define ATP_UV_IS_WATCHER_CLOSE(watcher)(watcher->ulFlag & ATP_UV_WATCHER_FLAG_CLOSING)
#define ATP_UV_IS_TIMER(watcher)        (watcher->ulFlag & ATP_UV_TYPE_TIMER)
#define ATP_UV_IS_IO(watcher)           (watcher->ulFlag & ATP_UV_TYPE_IO)
#define ATP_UV_IS_SOCKBASE(watcher)     (watcher->ulFlag & ATP_UV_TYPE_SOCKBASE)
#define ATP_UV_IS_MSG(watcher)          (watcher->ulFlag & ATP_UV_TYPE_MSG)
#define ATP_UV_IS_IDLE(watcher)         (watcher->ulFlag & ATP_UV_TYPE_IDLE)
#define ATP_UV_IS_PROCESS(watcher)      (watcher->ulFlag & ATP_UV_TYPE_PROCESS)

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

};

VOS_UINT32 ATP_UV_MsgInit(ATP_UV_LOOP_ST *pstLoop, ATP_UV_MSG_ST *pstMsgWatcher, VOS_INT32 lFd, PfMsgProc pfProc);
VOS_UINT32 ATP_UV_MsgStart(ATP_UV_MSG_ST *pstMsgWatcher);
VOS_UINT32 ATP_UV_MsgDelete(ATP_UV_MSG_ST *pstMsgWatcher);

VOS_UINT32 ATP_UV_MsgStartWatcher(ATP_UV_MSG_ST *pstMsgWatcher, VOS_UINT32 ulMsgType, VOS_UINT32 ulSeqNum, VOS_UINT32 ulTimeout, VOS_VOID *pvData,  PfMsgWatcherProc callback);

/**
 * Process API
 */

struct tagATP_UV_PROCESS_ST;
typedef struct tagATP_UV_PROCESS_ST ATP_UV_PROCESS_ST;

typedef VOS_VOID (* PfUVProcessExitCallback)(ATP_UV_PROCESS_ST *pstProcess, VOS_INT32 lPid, VOS_INT32 lExitStatus, VOS_INT32 lTermSignal);
struct tagATP_UV_PROCESS_ST
{
    // Inherited from ATP_UV_WATCHER_ST, must not change
    struct tagATP_UV_IO_ST      *pstNext;
    struct tagATP_UV_LOOP_ST    *pstLoop;
    VOS_UINT32                  ulFlag;
    VOS_VOID                    *pvHook;

    // Extended fields add here
    VOS_INT32                   lPid;
    PfUVProcessExitCallback     pfExitCb;
    PfUVProcessExitCallback     pfExitSignalCb;
    VOS_INT32                   lExitStatus;
    VOS_UINT32                  bExited;
};

/*
 * These are the flags that can be used for the ATP_UV_PROCESS_OPTIONS_ST.ulFlags field.
 */
/*
 * Set the child process' user id. The user id is supplied in the `uid` field
 * of the options struct. This does not work on windows; setting this flag
 * will cause uv_spawn() to fail.
 */
#define UV_PROCESS_SETUID   1
#define UV_PROCESS_SETEUID  2
/*
 * Set the child process' group id. The user id is supplied in the `gid`
 * field of the options struct. This does not work on windows; setting this
 * flag will cause uv_spawn() to fail.
 */
#define UV_PROCESS_SETGID   4
/*
 * Spawn the child process in a detached state - this will make it a process
 * group leader, and will effectively enable the child to keep running after
 * the parent exits.  Note that the child process will still keep the
 * parent's event loop alive unless the parent process calls uv_unref() on
 * the child's process handle.
 */
#define UV_PROCESS_DETACHED 8

/*
 * Set the child process's umask
 */
#define UV_PROCESS_UMASK 16

/*
 * Set the child process's nocoredump
 */
#define UV_PROCESS_NOCOREDUMP  32

#define EXIT_CMD_NOT_FOUND    127
struct tagATP_UV_PROCESS_OPTIONS_ST;
typedef struct tagATP_UV_PROCESS_OPTIONS_ST ATP_UV_PROCESS_OPTIONS_ST;
typedef VOS_BOOL (* PfUVIsFdNeedReserve)(const ATP_UV_PROCESS_OPTIONS_ST *pstOptions, VOS_INT32 lFd);

struct tagATP_UV_PROCESS_OPTIONS_ST
{
  PfUVProcessExitCallback   pfExitSignalCb; /* Called in the SIGCHILD signal proc after the process exits, recomend print debug info only. */
  PfUVProcessExitCallback   pfExitCb; /* Called after the process exits. */
  PfUVIsFdNeedReserve       pfReserveFd; /* Should the fd be reserved after exec */
  const VOS_CHAR            *pcFile;   /* Path to program to execute. */
  /* Hook */
  VOS_VOID                  *pvHook;
  /*
   * Command line arguments. args[0] should be the path to the program. On
   * Windows this uses CreateProcess which concatenates the arguments into a
   * string this can cause some strange errors. See the note at
   * windows_verbatim_arguments.
   */
  VOS_CHAR                  **args;
  /*
   * This will be set as the environ variable in the subprocess. If this is
   * NULL then the parents environ will be used.
   */
  VOS_CHAR                  **env;
  /*
   * If non-null this represents a directory the subprocess should execute
   * in. Stands for current working directory.
   */
  const VOS_CHAR            *cwd;
  /*
   * Various flags that control how ATP_UV_ProcessSpawn() behaves. See the definition of
   * `enum ATP_UV_PROCESS_FLAGS_EN` below.
   */
  VOS_UINT32                ulFlags;
  /*
   * uv can change the child process' user/group id. This happens only when
   * the appropriate bits are set in the flags fields.
   */
  uid_t                     uid;
  gid_t                     gid;
  // supplementary groups size
  VOS_INT32                 groupSize;
  // supplementary groups
  gid_t                     *gids;

  // Child process umask
  VOS_INT32                 umask;
};

VOS_UINT32 ATP_UV_ProcessSpawn(ATP_UV_LOOP_ST *pstLoop, ATP_UV_PROCESS_ST **ppstProcess, const ATP_UV_PROCESS_OPTIONS_ST *pstOptions);

VOS_VOID ATP_UV_ProcessKill(const ATP_UV_PROCESS_ST *pstProcess, VOS_INT32 lSignal);

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
