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
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>      /* open */
#include <unistd.h>     /* exit */
#include <sys/ioctl.h>  /* ioctl */
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#define __ATP_DEPRECATED_H__
#include "atpflashapi.h"
#include "atptypes.h"
#include "msgapi.h"
#include "atplog.h"
#include "gplrealloc.h"
#ifdef SUPPORT_ATP_LOG
#include "logapi.h"
#endif

#ifndef SUPPORT_DESKTOP
//#include "commondrv.h"
#endif


ATP_MSG_CONTEXT_ST g_stMsgCtx = {"", -1, 0, NULL, 0, NULL, -1, NULL, 0, 0, NULL, 0, -1, NULL};


#ifdef SUPPORT_ATP_TRACE_INFO
extern VOS_VOID TraceMsgInitRespProc(const ATP_TRACE_GOLBAL_INFO_ST *pstTraceGlobalInfo, VOS_UINT32 ulLen);
#endif
static VOS_UINT32 MsgRegister()
{
    VOS_CHAR acBuf[sizeof(ATP_MSG_HEADER_ST)];
    ATP_MSG_HEADER_ST    *pstSend;
    ATP_MSG_HEADER_ST    *pstRecv;
#ifdef SUPPORT_ATP_TRACE_INFO    
    ATP_MIC_MSGREGISTER  *pstRespRegister;
#endif
    VOS_UINT32 ulRet;

    memset((VOS_VOID *)acBuf, 0, sizeof(acBuf));

    pstSend = (ATP_MSG_HEADER_ST *)acBuf;
    pstSend->ulMsgType = ATP_MSG_REGISTER;
    pstSend->ulDataLen = 0;
    snprintf(pstSend->aucSendApp, (ATP_MSG_MAX_NAME_LEN + 1), "%s", g_stMsgCtx.aucAppName);

    pstRecv = NULL;
    ulRet = ATP_MSG_SendAndRecv(pstSend, &pstRecv, 0);
    
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }
    if (NULL == pstRecv)
    {
        return ATP_MSG_RET_PARA_ERR;
    }

    // Backup app name
    memcpy((VOS_VOID *)g_stMsgCtx.aucAppName, (VOS_VOID *)pstRecv->aucRecvApp,
           ATP_MSG_MAX_NAME_LEN);
    g_stMsgCtx.aucAppName[ATP_MSG_MAX_NAME_LEN] = '\0';
#ifdef SUPPORT_ATP_TRACE_INFO    
    pstRespRegister = (ATP_MIC_MSGREGISTER*)(pstRecv + 1);
    TraceMsgInitRespProc((ATP_TRACE_GOLBAL_INFO_ST*)(pstRespRegister + 1), pstRecv->ulDataLen - sizeof(ATP_MIC_MSGREGISTER));
#endif
    free((VOS_VOID *)pstRecv);

    if ('\0' == g_stMsgCtx.aucAppName[0])
    {
        return ATP_MSG_RET_APPNAME_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 ATP_MSG_Init(const VOS_CHAR *pszAppName)
{
    VOS_UINT32 ulRet;
    VOS_INT32 lIra;
    struct sockaddr_un  stAddr;

    signal(SIGPIPE, SIG_IGN);

    // Already inited
    if (g_stMsgCtx.lSock >= 0)
    {
        return VOS_OK;
    }

    if (NULL != pszAppName)
    {
        snprintf(g_stMsgCtx.aucAppName, (ATP_MSG_MAX_NAME_LEN + 1), "%s", pszAppName);
    }
    else
    {
        g_stMsgCtx.aucAppName[0] = '\0';
    }

    // Create socket
    g_stMsgCtx.lSock = socket(AF_UNIX, SOCK_STREAM, 0);
    //g_stMsgCtx.lSock = socket(AF_INET, SOCK_STREAM, 0);
    if (g_stMsgCtx.lSock < 0)
    {
        return ATP_MSG_RET_SOCKET_ERR;
    }

    //Set some flags
    lIra = 1;
    setsockopt(g_stMsgCtx.lSock, SOL_SOCKET, SO_REUSEADDR, (VOS_CHAR *)&lIra, sizeof(lIra));
    lIra = 1;
    fcntl(g_stMsgCtx.lSock, F_SETFD, FD_CLOEXEC);

    // Connect
    memset((VOS_CHAR *)(&stAddr), 0, sizeof(stAddr));
    stAddr.sun_family = AF_UNIX;
    //stAddr.sin_family = AF_INET;
    snprintf(stAddr.sun_path, sizeof(stAddr.sun_path), "%s", ATP_MSG_SVR_PATH);
    //stAddr.sin_addr.s_addr = inet_addr(ATP_MSG_LOCAL_HOST);
    //stAddr.sin_port = htons(ATP_MSG_LOCAL_PORT);
    if (connect(g_stMsgCtx.lSock,
                    (struct sockaddr *)&stAddr,
                    sizeof(stAddr)) < 0)
    {
        close(g_stMsgCtx.lSock);
        g_stMsgCtx.lSock = -1;
        ATP_MSG_DEBUG("Connect to msgsvr failed %d.\n", errno);
        return ATP_MSG_RET_SOCKET_ERR;
    }

    ulRet = MsgRegister();
    if (VOS_OK != ulRet)
    {
        ATP_MSG_DEBUG("Register to msgsvr failed %x.\n", ulRet);
        ATP_MSG_Destroy();
    }

    return ulRet;
}


VOS_VOID ATP_MSG_Destroy()
{
    if (g_stMsgCtx.lSock > 0)
    {
        close(g_stMsgCtx.lSock);
    }
    memset((VOS_VOID *)(&g_stMsgCtx), 0, sizeof(g_stMsgCtx));
    g_stMsgCtx.lSock = -1;
}

/*
 *    Message Utility Interfaces
 */
VOS_VOID ATP_MSG_TraceProc(VOS_INT32 lNewFd)
{
    // Close old trace
    if (NULL != g_stMsgCtx.pfTraceFile)
    {
        fclose(g_stMsgCtx.pfTraceFile);
    }
    g_stMsgCtx.pfTraceFile = NULL;
    if (g_stMsgCtx.lTraceFd >= 0)
    {
        close(g_stMsgCtx.lTraceFd);
        g_stMsgCtx.lTraceFd = -1;
    }
    if (0 == g_stMsgCtx.ulDbgLevel)     // Close debug info
    {
        if (lNewFd >= 0)
        {
            close(lNewFd);
        }
        return;
    }
    if (lNewFd >= 0)
    {
        // Open new trace file
        g_stMsgCtx.pfTraceFile = fdopen(lNewFd, "w");
        if (NULL == g_stMsgCtx.pfTraceFile)
        {
            close(lNewFd);
            return;
        }
        g_stMsgCtx.lTraceFd = lNewFd;
    }
}


/*
 *    Message Sending & Recving Interfaces
 */
VOS_UINT32 ATP_MSG_SendEx(VOS_INT32 lSock, ATP_MSG_HEADER_ST *pstMsg)
{
    VOS_UINT32      ulTotalLen;
    VOS_UINT32      ulCnt;
    VOS_INT32       lRet;
    struct timeval  tv;
    fd_set          writeFds;

    if ((NULL == pstMsg) || (lSock < 0))
    {
        return ATP_MSG_RET_PARA_ERR;
    }

    // Need to check if it will overflow first
    //lint -save -e716
    while (1)
    {
        FD_ZERO(&writeFds);
        FD_SET(lSock, &writeFds);
        tv.tv_sec  = 10;
        tv.tv_usec = 0;
        lRet = select((lSock + 1), NULL, &writeFds, NULL, &tv);
        if ((lRet != 1) || (!(FD_ISSET(lSock, &writeFds))))
        {
            if ((lRet < 0) && ((EINTR == errno) || (EAGAIN == errno)))
            {
                //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!Wait to send msg interrupted.\n");
                continue;
            }
            printf("Send msg err %d:%d\n", lRet, errno);
            return ATP_MSG_RET_OVERFLOW;
        }
        break;
    }
    //lint restore

    // Send msg body
    ulCnt = 0;
    ulTotalLen = sizeof(ATP_MSG_HEADER_ST) + pstMsg->ulDataLen;
    while (ulCnt < ulTotalLen)
    {
        lRet = write(lSock, (((VOS_UINT8 *)pstMsg) + ulCnt), (ulTotalLen - ulCnt));
        if (lRet < 0)
        {
            // The socket is closed by peer
            if (errno == EPIPE)
            {
                return ATP_MSG_RET_PEER_DEAD;
            }
            else if ((EINTR == errno) || (EAGAIN == errno))
            {
                //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!Send msg interrupted.\n");
                continue;
            }
            return ATP_MSG_RET_INTERNAL_ERR;
        }
        ulCnt += (VOS_UINT32)lRet;
    }

    return VOS_OK;
}


VOS_UINT32 ATP_MSG_Send(ATP_MSG_HEADER_ST *pstMsg)
{
    if (NULL == pstMsg)
    {
        return ATP_MSG_RET_PARA_ERR;
    }

    // Must be inited 
    if (g_stMsgCtx.lSock < 0)
    {
        return ATP_MSG_RET_NOT_INITED;
    }

    snprintf(((ATP_MSG_HEADER_ST *)pstMsg)->aucSendApp, (ATP_MSG_MAX_NAME_LEN + 1), "%s", g_stMsgCtx.aucAppName);

    return ATP_MSG_SendEx(g_stMsgCtx.lSock, pstMsg);
}

static VOS_BOOL MsgWaitForData(VOS_INT32 fd, VOS_UINT32 ulTimeout)
{
    struct timeval tv;
    fd_set readFds;
    VOS_INT32 lRet;

    while (1)
    {
        FD_ZERO(&readFds);
        FD_SET(fd, &readFds);

        tv.tv_sec = (long)(ulTimeout / 1000);
        tv.tv_usec = (long)((ulTimeout % 1000) * 1000);
        lRet = select(fd+1, &readFds, NULL, NULL, &tv);
        if ((lRet == 1) && (FD_ISSET(fd, &readFds)))
        {
            return VOS_TRUE;
        }
        if (0 == lRet)  // It is really timeout
        {
            break;
        }
        // If error, just continue
        //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!Wait for data interrupted.\n");
        continue;
    }

    return VOS_FALSE;
}

VOS_UINT32 ATP_MSG_QueueAppend(
                                ATP_MSG_QUEUE_ST        **ppstMsgQueue,
                                ATP_MSG_HEADER_ST       *pstMsg)
{
    ATP_MSG_QUEUE_ST *pstItem;
    ATP_MSG_QUEUE_ST **ppstTmp;

    if ((NULL == ppstMsgQueue) || (NULL == pstMsg))
    {
        return ATP_MSG_RET_PARA_ERR;
    }

    pstItem = (ATP_MSG_QUEUE_ST *)malloc(sizeof(ATP_MSG_QUEUE_ST));
    if (NULL == pstItem)
    {
        return ATP_MSG_RET_MEM_ERR;
    }
    pstItem->pstMsg = pstMsg;
    pstItem->pstNext = NULL;

    ppstTmp = ppstMsgQueue;
    while (NULL != (*ppstTmp))
    {
        ppstTmp = &((*ppstTmp)->pstNext);
    }
    (*ppstTmp) = pstItem;
    return VOS_OK;
}

VOS_VOID ATP_MSG_QueueClear(ATP_MSG_QUEUE_ST    *pstMsgQueue)
{
    ATP_MSG_QUEUE_ST    *pstItem;
    ATP_MSG_QUEUE_ST    *pstTmp;

    pstItem = pstMsgQueue;
    while (NULL != pstItem)
    {
        pstTmp = pstItem->pstNext;

        (VOS_VOID)ATP_MSG_SendEx(g_stMsgCtx.lSock, pstItem->pstMsg);

        free((VOS_VOID *)(pstItem->pstMsg));
        free((VOS_VOID *)pstItem);
        pstItem = pstTmp;
    }
}


VOS_UINT32 ATP_MSG_SendAndRecv(ATP_MSG_HEADER_ST   *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout)
{
    VOS_UINT32          ulRet;
    VOS_BOOL            bContinue;
    ATP_MSG_HEADER_ST   *pstRet;

    // Check input parameter
    if ((NULL == pstMsg) || (NULL == ppstResp))
    {
        return ATP_MSG_RET_PARA_ERR;
    }
    (*ppstResp) = NULL;

    // Send request first
    ulRet = ATP_MSG_Send(pstMsg);
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    // Loop to receive response
    bContinue = VOS_TRUE;
    while (VOS_TRUE == bContinue)
    {
        // Recv msg first
        ulRet = ATP_MSG_Recv(g_stMsgCtx.lSock, &pstRet, ulTimeout);
        if (VOS_OK != ulRet)
        {
            break;
        }

        if ((ATP_MSG_UNRECHABLE_CTRL == pstRet->ulMsgType)
            && (pstMsg->ulMsgType == pstRet->ulMsgData))
        {
            ATP_MSG_DEBUG("dist unreachable %x.\n", pstRet->ulMsgType);
            ulRet = ATP_MSG_RET_PEER_DEAD;
            free( (VOS_VOID*)pstRet );
            pstRet = NULL;
            break;
        }

        // Check msg type
        if (pstMsg->ulMsgType != pstRet->ulMsgType)
        {
            ATP_MSG_DEBUG("Backup not matched msg %x.\n", pstRet->ulMsgType);
            if (VOS_OK != ATP_MSG_QueueAppend(&(g_stMsgCtx.pstMsgQueue), pstRet))
            {
                free((VOS_VOID *)pstRet);
                pstRet = NULL;
            }
            continue;
        }

        (*ppstResp) = pstRet;
        break;
    }

    // Restore all backup msg
    ATP_MSG_QueueClear(g_stMsgCtx.pstMsgQueue);
    g_stMsgCtx.pstMsgQueue = NULL;

    return ulRet;
}


VOS_UINT32 ATP_MSG_Recv(VOS_INT32             sSock,
                              ATP_MSG_HEADER_ST     **ppstMsg,
                              VOS_UINT32            ulTimeout)
{
    ATP_MSG_HEADER_ST    *pstMsg;
    VOS_INT32           lRet;
    VOS_UINT32          ulBytesRemain;
    VOS_CHAR            *pcBody;

    if ((sSock < 0) || (NULL == ppstMsg))
    {
        return ATP_MSG_RET_PARA_ERR;
    }

    // Wait if needed
    (*ppstMsg) = NULL;
    if (0 != ulTimeout)
    {
        if (VOS_FALSE == MsgWaitForData(sSock, ulTimeout))
        {
            return ATP_MSG_RET_TIMEOUT;
        }
    }

    // Alloc msg header
    pstMsg = (ATP_MSG_HEADER_ST *)malloc(sizeof(ATP_MSG_HEADER_ST));
    if (NULL == pstMsg)
    {
        return ATP_MSG_RET_MEM_ERR;
    }
	memset(pstMsg, 0, sizeof(ATP_MSG_HEADER_ST));
	
    // Recv msg header
    while (1)
    {
        lRet = read(sSock, (VOS_VOID *)pstMsg, sizeof(ATP_MSG_HEADER_ST));
        if ((lRet == 0) ||
            ((lRet == -1) && (errno == 131)))  /* new 2.6.21 kernel seems to give us this before rc==0 */
        {
            free((VOS_VOID *)pstMsg);
            return ATP_MSG_RET_PEER_DEAD;
        }
        else if (lRet < 0)
        {
            // Interrupted, just continue
            if ((EINTR == errno) || (EAGAIN == errno))
            {
                //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!Recv msg header interrupted.\n");
                continue;
            }
            free((VOS_VOID *)pstMsg);
            return ATP_MSG_RET_INTERNAL_ERR;
        }
        else if ((VOS_UINT32)lRet != sizeof(ATP_MSG_HEADER_ST))
        {
            free((VOS_VOID *)pstMsg);
            return ATP_MSG_RET_INTERNAL_ERR;
        }
        // Message header is OK
        break;
    }

    pstMsg->ulMsgType = ATP_MSG_TYPE_NO_MASK(pstMsg->ulMsgType);

    // If no msg body, return immediately
    if (0 == pstMsg->ulDataLen)
    {
        (*ppstMsg) = pstMsg;
        return VOS_OK;
    }

    // Realloc enough memory to recv data
    pstMsg = gpl_realloc(pstMsg, sizeof(ATP_MSG_HEADER_ST),(sizeof(ATP_MSG_HEADER_ST) + pstMsg->ulDataLen));
    if (NULL == pstMsg)
    {
        return ATP_MSG_RET_MEM_ERR;
    }

    // Continue to recv the remaining body
    pcBody = (VOS_CHAR *)(pstMsg + 1);
    ulBytesRemain = pstMsg->ulDataLen;
    while (ulBytesRemain > 0)
    {
        if (0 != ulTimeout)
        {
            if (VOS_FALSE == MsgWaitForData(sSock, ulTimeout))
            {
                free((VOS_VOID *)pstMsg);
                return ATP_MSG_RET_TIMEOUT;
            }
        }

        lRet = read(sSock, pcBody, ulBytesRemain);
        if ((lRet == 0) ||
            ((lRet == -1) && (errno == 131)))
        {
            free((VOS_VOID *)pstMsg);
            return ATP_MSG_RET_PEER_DEAD;
        }
        else if (lRet < 0)
        {
            // Interrupted, just continue
            if ((EINTR == errno) || (EAGAIN == errno))
            {
                //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!Recv msg body interrupted.\n");
                continue;
            }
            free((VOS_VOID *)pstMsg);
            return ATP_MSG_RET_INTERNAL_ERR;
        }

        pcBody += lRet;
        ulBytesRemain -= (VOS_UINT32)lRet;
    }

    (*ppstMsg) = pstMsg;
    return VOS_OK;
}

VOS_UINT32 ATP_MSG_GetNumOfProcesses(const VOS_CHAR *pcName)
{
    VOS_UINT32          ulRetVal;
    ATP_MSG_HEADER_ST   *pstMsg;
    ATP_MSG_HEADER_ST   *pstResp;
    VOS_CHAR            acMsg[sizeof(ATP_MSG_HEADER_ST) + ATP_MSG_MAX_NAME_LEN + 1];

    if (NULL == pcName)
    {
        return 0;
    }

    memset((void *)acMsg, 0, sizeof(acMsg));
    pstMsg = (ATP_MSG_HEADER_ST *)acMsg;
    pstMsg->ulMsgType = ATP_MSG_GET_NUM_OF_PROC;
    pstMsg->ulDataLen = (ATP_MSG_MAX_NAME_LEN + 1);
    snprintf((char *)(acMsg + sizeof(ATP_MSG_HEADER_ST)), (ATP_MSG_MAX_NAME_LEN + 1), "%s", pcName);
    ulRetVal = ATP_MSG_SendAndRecv(pstMsg, &pstResp, 5000);
    if (VOS_OK != ulRetVal)
    {
        return 0;
    }
    if (NULL == pstResp)
    {
        return 0;
    }
    ulRetVal = pstResp->ulMsgData;
    free((VOS_VOID *)pstResp);
    return ulRetVal;
}

/*
 *    Message Utilities
 */


//lint -save -e429
VOS_VOID* ATP_MSG_GetMsgBlock(VOS_UINT32 ulMsgSize)
{
    ATP_MSG_HEADER_ST* pstMsgHead;

    pstMsgHead = malloc(sizeof(ATP_MSG_HEADER_ST) + ulMsgSize);
    if (!pstMsgHead)
    {
        return VOS_NULL_PTR;
    }
    memset(pstMsgHead, 0, sizeof(ATP_MSG_HEADER_ST));
    pstMsgHead->ulDataLen = ulMsgSize;
    return (pstMsgHead + 1);
}
//lint restore

// 初始化外部分配的消息块
VOS_VOID* ATP_MSG_GetMsgBlockEx(VOS_VOID* pvBuff, VOS_UINT32 ulBuffLen)
{
    ATP_MSG_HEADER_ST* pstMsgHead;

    if (ulBuffLen < sizeof(ATP_MSG_HEADER_ST))
    {
        return VOS_NULL_PTR;
    }
    pstMsgHead = pvBuff;
    memset(pstMsgHead, 0, sizeof(ATP_MSG_HEADER_ST));
    pstMsgHead->ulDataLen = ulBuffLen - sizeof(ATP_MSG_HEADER_ST);
    return (pstMsgHead + 1);
}

VOS_UINT32 ATP_MSG_SetMsgProfile(VOS_VOID* pvMsg, const VOS_CHAR acRecvApp[ATP_MSG_MAX_NAME_LEN + 1], 
                            VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgLen)
{
    ATP_MSG_HEADER_ST* pstMsgHead;

    pstMsgHead = (ATP_MSG_HEADER_ST*)pvMsg - 1;
    snprintf(pstMsgHead->aucRecvApp, sizeof(pstMsgHead->aucRecvApp), "%s", acRecvApp);
    pstMsgHead->aucRecvApp[ATP_MSG_MAX_NAME_LEN] = '\0';
    pstMsgHead->ulMsgType = ulMsgType;
    if (ulMsgLen <= pstMsgHead->ulDataLen)
    {
        pstMsgHead->ulDataLen = ulMsgLen;
    }
    else
    {
        return ATP_MSG_RET_PARA_ERR;
    }
    
    return VOS_OK;
}

ATP_MSG_HEADER_ST* ATP_MSG_GetMsgHead(VOS_VOID* pvMsg)
{
    return (((ATP_MSG_HEADER_ST*)pvMsg) - 1);
}

VOS_VOID* ATP_MSG_GetMsgByHead(ATP_MSG_HEADER_ST* pstMsgHead)
{
    if (!pstMsgHead || pstMsgHead->ulDataLen == 0)
    {
        return VOS_NULL_PTR;
    }

    return (pstMsgHead + 1);
}

VOS_VOID ATP_MSG_SimpleBuilder(ATP_MSG_HEADER_ST *pstMsg, const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData)
{
    if (NULL == pstMsg)
    {
        return;
    }

    memset((VOS_VOID *)pstMsg, 0, sizeof(ATP_MSG_HEADER_ST));
    pstMsg->ulMsgType = ulMsgType;
    pstMsg->ulMsgData = ulMsgData;
    if (NULL == pcDest)
    {
        return;
    }
    snprintf(pstMsg->aucRecvApp, (ATP_MSG_MAX_NAME_LEN + 1), "%s", pcDest);
}

VOS_UINT32 ATP_MSG_SendSimpleMsg(const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData)
{
    ATP_MSG_HEADER_ST stMsg;

    ATP_MSG_SimpleBuilder(&stMsg, pcDest, ulMsgType, ulMsgData);
    return ATP_MSG_Send(&stMsg);
}

VOS_UINT32 ATP_MSG_SendMsgData(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType, 
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen)
{
    ATP_MSG_HEADER_ST* pstMsgHead;
    VOS_UINT32 ulRet;

    if (NULL == pvMsgBuff)
    {
        return ATP_MSG_SendSimpleMsg(pcProcName, ulMsgType, 0);
    }

    pstMsgHead = (ATP_MSG_HEADER_ST*)malloc(sizeof(ATP_MSG_HEADER_ST) + ulBuffLen);
    if (!pstMsgHead)
    {
        return ATP_MSG_RET_MEM_ERR;
    }
    memset((VOS_VOID*)pstMsgHead, 0, sizeof(ATP_MSG_HEADER_ST));
    if (NULL != pcProcName)
    {
        snprintf(pstMsgHead->aucRecvApp, (ATP_MSG_MAX_NAME_LEN + 1), "%s", pcProcName);
    }
    pstMsgHead->ulDataLen = ulBuffLen;
    pstMsgHead->ulMsgType = ulMsgType;
    memcpy((VOS_VOID*)(pstMsgHead + 1), pvMsgBuff, ulBuffLen);
    ulRet = ATP_MSG_Send(pstMsgHead);
    free(pstMsgHead);
    return ulRet;
}

#ifdef SUPPORT_ATP_LOG
VOS_BOOL logLogTypeCheck(VOS_UINT32 ulLogType)
{
    VOS_UINT32 ulCount = 0;
    VOS_UINT32 i;
    
    for (i = 0; i < ATP_LOG_TYPE_COUNT; i++)
    {
        if ((ulLogType & (1 << i)) != 0)
        {
            ulCount++;
        }
        if (ulCount > 1)
        {
            return VOS_FALSE;
        }
    }
    if (ulCount != 1)
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

VOS_BOOL logLogLevelCheck(VOS_UINT32 ulLogLevel)
{
    VOS_UINT32 ulCount = 0;
    VOS_UINT32 i;
    
    for (i = 0; i < ATP_LOG_LEVEL_COUNT; i++)
    {
        if ((ulLogLevel & (1 << i)) != 0)
        {
            ulCount++;
        }
        if (ulCount > 1)
        {
            return VOS_FALSE;
        }
    }
    if (ulCount != 1)
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

VOS_BOOL g_bLogEnable = VOS_TRUE;

VOS_UINT32 ATP_LOG_Printf(VOS_UINT32 ulLogType, VOS_UINT32 ulLogLevel,
                              VOS_UINT32 ulLogNum, const VOS_INT8 *fmt, ...)
{
    va_list             vaArgList;
    ATP_MSG_HEADER_ST   *pstMsgHeader;
    ATP_LOG_MSG_ST      *pstLogHeader;
    VOS_CHAR            *pcLogStr;
    VOS_UINT32          ulLen;
    VOS_CHAR            acLogMsg[sizeof(ATP_MSG_HEADER_ST) +
                            sizeof(ATP_LOG_MSG_ST) + ATP_LOG_MAX_CONTENT_LEN + 1];

    if ((ulLogNum == 0xFFFFFFFF) || (NULL == fmt))
    {
        return ATP_LOG_RET_PARA_ERR;
    }

    if (VOS_FALSE == logLogTypeCheck(ulLogType) ||
        VOS_FALSE == logLogLevelCheck(ulLogLevel))
    {
        return ATP_LOG_RET_PARA_ERR;
    }

    if (VOS_FALSE == g_bLogEnable)
    {
        return VOS_OK;
    }
    if (g_stMsgCtx.lSock <= 0)
    {
        return ATP_LOG_RET_NOT_INITED;
    }

    memset((VOS_VOID *)acLogMsg, 0, sizeof(acLogMsg));
    pstMsgHeader = (ATP_MSG_HEADER_ST *)acLogMsg;
    pstLogHeader = (ATP_LOG_MSG_ST *)(acLogMsg + sizeof(ATP_MSG_HEADER_ST));
    pcLogStr = ((VOS_CHAR*)pstLogHeader) + sizeof(ATP_LOG_MSG_ST);

    va_start(vaArgList, fmt);
    ulLen = (VOS_UINT32)vsnprintf(pcLogStr, ATP_LOG_MAX_CONTENT_LEN, fmt, vaArgList);
    va_end(vaArgList);
    if (ulLen > ATP_LOG_MAX_CONTENT_LEN)
    {
        return ATP_LOG_RET_TOO_LONG;
    }

    // Fill log msg data
    pstLogHeader->ulLogTypeLevel    |= (ulLogType << ATP_LOG_TYPE_OFFSET);
    pstLogHeader->ulLogTypeLevel    |= ulLogLevel;
    pstLogHeader->ulLogNum          = ulLogNum;
    pstLogHeader->usLogLen          = (VOS_UINT16)ulLen;

    // Fill msg header
    snprintf(pstMsgHeader->aucRecvApp, ATP_MSG_MAX_NAME_LEN + 1, "%s", ATP_CBBID_LOG_NAME);
    pstMsgHeader->ulMsgType     = ATP_MSG_LOG_ITEM;
    pstMsgHeader->ulDataLen     = (VOS_UINT32)(pstLogHeader->usLogLen +
                                    sizeof(ATP_LOG_MSG_ST));

    return ATP_MSG_Send(pstMsgHeader);
}

VOS_UINT32 ATP_LOG_RecordItem(VOS_UINT32 ulLogItemIdx, ...)
{
    va_list                   arg_ptr;
    VOS_UINT32                ulRet;
    VOS_INT8*                 pszArg;
    VOS_UINT32                ulBufLen;
    VOS_UINT32                ulParaNum = 0;

    VOS_INT8*                 pszSendBuf;
    ATP_MSG_HEADER_ST*        pszMsgAddr;
    ATP_LOG_LOGITEM_PARAS_ST* pszParaStAddr;
    VOS_INT8*                 pszParaStrAddr;

    ulBufLen = sizeof(ATP_LOG_LOGITEM_PARAS_ST);

    va_start(arg_ptr, ulLogItemIdx);
    while (VOS_NULL_PTR != (pszArg = va_arg(arg_ptr, VOS_INT8*)))
    {
        ulBufLen += strlen(pszArg)+1; // also add '\0'
    }
    va_end(arg_ptr);

    pszSendBuf = (VOS_INT8*)malloc(sizeof(ATP_MSG_HEADER_ST) + sizeof(ATP_LOG_LOGITEM_PARAS_ST)+ ulBufLen);
    if (VOS_NULL_PTR == pszSendBuf)
    {
        return ATP_LOG_RET_MEM;
    }
    pszMsgAddr = (ATP_MSG_HEADER_ST*)pszSendBuf;
    pszParaStAddr = (ATP_LOG_LOGITEM_PARAS_ST*)(pszSendBuf + sizeof(ATP_MSG_HEADER_ST));
    pszParaStrAddr = (VOS_INT8*)pszParaStAddr + sizeof(ATP_LOG_LOGITEM_PARAS_ST);

    va_start(arg_ptr, ulLogItemIdx);
    while (VOS_NULL_PTR != (pszArg = va_arg(arg_ptr, VOS_INT8*)))
    {
        memcpy(pszParaStrAddr, (VOS_UINT8*)pszArg, strlen(pszArg)+1);
        pszParaStrAddr += strlen(pszArg)+1;
        ulParaNum++;
    }
    va_end(arg_ptr);

    pszParaStAddr->ulFeatureIdOffset = ulLogItemIdx;
    pszParaStAddr->usParaNum = ulParaNum;
    pszParaStAddr->ulContentLen = ulBufLen - sizeof(ATP_LOG_LOGITEM_PARAS_ST);

    snprintf(pszMsgAddr->aucRecvApp, ATP_MSG_MAX_NAME_LEN + 1, "%s", ATP_CBBID_LOG_NAME);
    pszMsgAddr->ulMsgType = ATP_MSG_LOG_ITEM;
    pszMsgAddr->ulDataLen = sizeof(ATP_LOG_LOGITEM_PARAS_ST)+ ulBufLen;

    ulRet = ATP_MSG_Send(pszMsgAddr);
    free(pszSendBuf);
    return ulRet;
}

VOS_UINT32 ATP_LOG_KLogPrintf(VOS_UINT32 ulLogType, VOS_UINT32 ulLogLevel,
                              VOS_UINT32 ulLogNum, const VOS_INT8* pstLogString)
{
    ATP_MSG_HEADER_ST* pszMsgAddr;
    ATP_LOG_ITEM_ST*   pLogItem;
    VOS_UINT32         ulRet;
    if ((ulLogNum == 0xFFFFFFFF) || (NULL == pstLogString)
            || VOS_FALSE == logLogTypeCheck(ulLogType)
            || VOS_FALSE == logLogLevelCheck(ulLogLevel))
    {
        return ATP_LOG_RET_PARA_ERR;
    }
    pszMsgAddr = (ATP_MSG_HEADER_ST*)malloc(sizeof(ATP_MSG_HEADER_ST)+sizeof(ATP_LOG_ITEM_ST)+strlen(pstLogString)+1);
    if (VOS_NULL_PTR == pszMsgAddr)
    {
        ATP_LOG_DEBUG("ATP_LOG_KLogPrintf pszMsgAddr malloc error. \r\n");
        return ATP_LOG_RET_MEM;
    }
    memset(pszMsgAddr, 0, sizeof(ATP_MSG_HEADER_ST)+sizeof(ATP_LOG_ITEM_ST)+strlen(pstLogString)+1);
    pLogItem= (ATP_LOG_ITEM_ST*)(pszMsgAddr+1);
    pLogItem->ulLogTypeLevel |= (ulLogType << ATP_LOG_TYPE_OFFSET);
    pLogItem->ulLogTypeLevel |= ulLogLevel;
    pLogItem->ulLogNum = ulLogNum;
    pLogItem->stLogParasSt.ulFeatureIdOffset = (VOS_UINT32)((VOS_UINT32)ATP_LOG_KERNEL_FEATURE_ID << LOG_FEATUREID_OFFSET);
    pLogItem->stLogParasSt.usParaNum = 1;
    pLogItem->stLogParasSt.ulContentLen = (VOS_UINT16)(strlen(pstLogString)+1); // also add '\0'
    memcpy(pLogItem->stLogParasSt.pszContent, pstLogString, strlen(pstLogString)+1); // also add '\0'
    snprintf(pszMsgAddr->aucRecvApp, ATP_MSG_MAX_NAME_LEN + 1, "%s", ATP_CBBID_LOG_NAME);
    pszMsgAddr->ulMsgType = ATP_MSG_LOG_KERNEL_ITEM;
    pszMsgAddr->ulDataLen = sizeof(ATP_LOG_ITEM_ST)+strlen(pstLogString)+1;
    ulRet = ATP_MSG_Send(pszMsgAddr);
    free(pszMsgAddr);
    return ulRet;
}
#endif

void BSP_SYS_WakeupMonitorTask(void)
{
    ATP_MSG_Init(NULL);

    ATP_MSG_SendMsgData("cms", 1, NULL, 0);
}

VOS_VOID ATP_MSG_MsgFilterProc(const ATP_MSG_HEADER_ST *pstMsg)
{
#ifdef ATP_DEBUG
    if (NULL != pstMsg)
    {
        ATP_MSG_DEBUG("do msg with type [%x] and length [%d] from [%s] to [%s].\n",
            pstMsg->ulMsgType, pstMsg->ulDataLen, pstMsg->aucSendApp, pstMsg->aucRecvApp);
    }
#endif

    // Do default msg proc
    if (NULL != pstMsg)
    {
        switch (pstMsg->ulMsgType)
        {
        case ATP_MSG_LOG_CTRL:
        break;

        default:
        break;
        }
    }

    if (NULL != g_stMsgCtx.pfMsgProc)
    {
        g_stMsgCtx.pfMsgProc(pstMsg);
    }
}

#ifdef SUPPORT_ATP_DEBUG_CMD
VOS_VOID ModularDebugPrintAvailableModules(VOS_BOOL bWithEnd)
{
#ifdef ATP_PCLINT
    bWithEnd = bWithEnd;
#endif
}

VOS_UINT32 ATP_Debug_RegModCmds(
                const VOS_CHAR                  *pcModName, 
                const ATP_UTIL_Debug_CMD_ST     *astDebugCmds, 
                VOS_UINT32                      ulCmdNum)
{
#ifdef ATP_PCLINT
    pcModName = pcModName;
    astDebugCmds = astDebugCmds;
    ulCmdNum = ulCmdNum;
#endif
    return VOS_OK;
}
#endif

VOS_VOID ATP_Debug_Print(VOS_CHAR *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}

