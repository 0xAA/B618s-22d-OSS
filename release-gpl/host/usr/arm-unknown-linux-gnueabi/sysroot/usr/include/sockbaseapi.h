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


#ifndef __ATP_SOCKBASE_API_H__
#define __ATP_SOCKBASE_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#include "atptypes.h"

/*
 *  Socket Layer
 *      This layer abastract TCP socket and SSL socket
 *      All http client and http server should use this layer to do data trans-recv
 */
/** Socket type */
typedef enum tagATP_SOCK_FLAG_EN
{
    ATP_SOCK_DFT        = 0,        // Default: TCP, no SSL, IPv4
    ATP_SOCK_UDP        = 0x01,     // Socket type, 0: TCP; 1: UDP
    ATP_SOCK_SSL        = 0x02,     // Whether SSL, 0: No SSL; 1: SSL
    ATP_SOCK_IP_VER     = 0x04,     // Version, 0: IPv4; 1: IPv6
    ATP_SOCK_UNIX       = 0x08,

    // Allowed combinations
    ATP_SOCK_TCP4_SSL   = ATP_SOCK_SSL,
    ATP_SOCK_TCP6_SSL   = ATP_SOCK_SSL | ATP_SOCK_IP_VER,
    ATP_SOCK_UDP6       = ATP_SOCK_UDP | ATP_SOCK_IP_VER,
} ATP_SOCK_FLAG_EN;

#define ATP_SSL_HANDSHAKE_STATE   (2)

typedef struct tagATP_SOCKET_ST
{
    VOS_INT32           lSock;
    VOS_UINT32          enSockFlag;     // todo: should be ulSockFlag, ref: ATP_SOCK_FLAG_EN
    VOS_VOID            *pstCtxObj;     // Dummy position
    VOS_VOID            *pstSslObj;     // Dummy position
    VOS_VOID            *pstMulCtxObj;
    VOS_BOOL            bSSLMode;
} ATP_SOCKET_ST;


typedef VOS_BOOL (*PFSockCtxMatchProc)(
                                VOS_VOID           *pstSocket,
                                VOS_VOID           *pvHook);

typedef struct tagATP_SOCKET_MUL_SSL_CTX
{    
    struct tagATP_SOCKET_MUL_SSL_CTX      *pstNext;
    VOS_VOID            *pstCtxObj;
    VOS_VOID            *pvHook;
    PFSockCtxMatchProc  pfSockMatchProc;
    VOS_BOOL            bDefault;
}ATP_SOCKET_MUL_SSL_CTX;

/*
 *  Sockbase utilities
 *      This module will listen to sockets, whenever new data or connections come,
 *           event call back will be called.
 *      All sockets event will be multiplexed by this module.
 */

typedef struct tagATP_SOCK_BASE_ST ATP_SOCK_BASE_ST;
typedef VOS_VOID (* PFUtilSockEvtProc)(const ATP_SOCK_BASE_ST *pstSockBase);

struct tagATP_SOCK_BASE_ST
{
    struct tagATP_SOCK_BASE_ST  *pstNext;
    struct tagATP_UV_LOOP_ST    *pstLoop;
    VOS_UINT32                  ulFlag;
    VOS_VOID                    *pvHook;

    VOS_INT32                   lSock;
    VOS_UINT32                  ulEvents;
    PfIOProc                    pfIOProc;

    PFUtilSockEvtProc           pfProc;
};

typedef enum tagATP_HTTP_STOP_STATE_EN
{
	 ATP_HTTP_STOP_BEFORE,
	 ATP_HTTP_STOP_AFTER,
	 ATP_HTTP_STOP_EXTERN
} ATP_HTTP_STOP_STATE_EN;

typedef VOS_BOOL (*PFATPHTTPConnectProc)(ATP_HTTP_STOP_STATE_EN enStopState);
extern PFATPHTTPConnectProc  g_pfConnectShouldStop;
extern VOS_INT32  g_lSocketSendTimeout;
extern VOS_INT32  g_lSocketRecvTimeout;
extern VOS_BOOL   g_bForceHttpHeaderInOnePackage;


VOS_INT32 ATP_UTIL_SockBaseGetMaxFd(VOS_VOID);

VOS_UINT32 ATP_UTIL_SockBaseReg(
                                VOS_INT32           lSock,
								ATP_SOCK_FLAG_EN    lSockFlag,
								PFUtilSockEvtProc   pfProc,
								VOS_BOOL            bListen,
								VOS_VOID            *pvHook,
								ATP_SOCK_BASE_ST    **ppstRet);

VOS_UINT32 ATP_UTIL_SockBaseRegEvtProc(VOS_VOID);

VOS_VOID ATP_UTIL_SockBaseListen(const ATP_SOCK_BASE_ST *pstSockBase, VOS_BOOL bListen);

VOS_VOID ATP_UTIL_SockBaseDirectDo(ATP_SOCK_BASE_ST *pstSockBase);

VOS_UINT32 ATP_UTIL_SockBaseForceLoop(const ATP_SOCK_BASE_ST* pstSockBase);

VOS_VOID ATP_UTIL_SockBaseDelete(ATP_SOCK_BASE_ST *pstSockBase);

VOS_VOID ATP_UTIL_SockBaseDestroy(VOS_VOID);

VOS_UINT32 ATP_UTIL_SockBaseStart(VOS_UINT32 ulMaxIdleTime);

VOS_VOID ATP_UTIL_SockBaseDeleteNew(VOS_INT32 lSock);

typedef struct tagATP_SOCKBASE_ASYNC_EVT_ST
{
    ATP_SOCK_BASE_ST        *pstSockBase;
    ATP_UTIL_TIMER_ST       *pstTimer;
    VOS_BOOL                bTimeout;
    VOS_VOID                *pvHook;
    PFUtilSockEvtProc       pfProc;
} ATP_SOCKBASE_ASYNC_EVT_ST;

ATP_SOCKBASE_ASYNC_EVT_ST *ATP_UTIL_SockbaseWaitSockResponseAsync(VOS_INT32 lSock, ATP_SOCK_FLAG_EN lSockFlag,
                VOS_UINT32 ulTimeout, VOS_VOID *pvHook, PFUtilSockEvtProc pfHook);

VOS_VOID ATP_UTIL_SockbaseAsyncEvtDestroy(ATP_SOCKBASE_ASYNC_EVT_ST *pstAyncEvt);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
