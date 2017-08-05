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

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#ifdef __BIONIC__
#include <mntent.h>
#endif
#define __ATP_DEPRECATED_H__

#include "atptypes.h"
#include "msgapi.h"
#include "atptraceapi.h"
//#include "securec.h"

/*
 *  Trace level string utilities
 */

const VOS_CHAR *g_pcEmptyStr = "";
const VOS_CHAR *m_aucAppName = "";

static const VOS_CHAR *m_apcTraceCliLevelMap[] =
{
    "none",
    "fatal",
    "error",
    "warning",
    "info",
    "debug",
};

static const ATP_UTIL_STR_IDX_MAP_ST m_astTraceLevelNames[] =
{
    {"none",        ATP_TRACE_LEVEL_OFF},
    {"fatal",       ATP_TRACE_LEVEL_EMERG},   
    {"error",       ATP_TRACE_LEVEL_ERR},
    {"warning",     ATP_TRACE_LEVEL_WARNING},
    {"info",        ATP_TRACE_LEVEL_INFO},
    {"debug",       ATP_TRACE_LEVEL_DEBUG},
    {"all",         ATP_TRACE_LEVEL_ALL},
    {NULL,                            -1}
};

VOS_UINT32 ATP_TRACE_GetLevelByString(const VOS_CHAR *pcLevel)
{
    VOS_INT32              lLevel;

    lLevel = ATP_UTIL_StrIdxArrayGetIdxByStr(pcLevel, m_astTraceLevelNames);
    if (-1 == lLevel)
    {
        return ATP_TRACE_LEVEL_OFF;
    }
    
    return (VOS_UINT32)lLevel;
}

const VOS_CHAR *ATP_TRACE_GetLevelStr(VOS_UINT32 ulLevel)
{
    const VOS_CHAR         *pcLevelStr;
    
    pcLevelStr = ATP_UTIL_StrIdxArrayGetStrByIdx(ulLevel, m_astTraceLevelNames);
    if (NULL == pcLevelStr)
    {
        return m_apcTraceCliLevelMap[0];
    }
    return pcLevelStr;
}

/**
 *  Trace level operation api
 */
static ATP_TRACE_CBB_LIST_ST *m_pstTraceList = NULL;

static ATP_TRACE_CBB_LIST_ST *TraceFindModuleByName(ATP_TRACE_CBB_LIST_ST *pstModuleList, const VOS_CHAR *pcName)
{
    ATP_TRACE_CBB_LIST_ST       *pstItem;

    pstItem = pstModuleList;
    while (NULL != pstItem)
    {
        if (0 == strcmp(pstItem->acName, pcName))
        {
            return pstItem;
        }
        pstItem = pstItem->pstNext;
    }
    return NULL;
}

static VOS_BOOL TraceIsForAllModules(const VOS_CHAR *pcName)
{
    if (NULL == pcName)
    {
        return VOS_TRUE;
    }

    if (0 == strcmp(pcName, ATP_DEBUG_MOD_ALL))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

//lint -save -e429
VOS_UINT32 TraceCtxSetPackageLevel(ATP_TRACE_CBB_LIST_ST **ppstTraceList, const VOS_CHAR *pcName, VOS_UINT32 ulLevel)
{
    ATP_TRACE_CBB_LIST_ST   *pstItem;

    if (NULL == pcName)
    {
        pcName = ATP_DEBUG_MOD_ALL;
    }

    // If set level for all packages, all previous packages will be destroyed first
    if (TraceIsForAllModules(pcName))
    {
        ATP_UTIL_ListDeleteAll((ATP_UTIL_LIST_ST *)(*ppstTraceList), NULL);
        (*ppstTraceList) = NULL;
    }

    // Get package item if exists
    pstItem = TraceFindModuleByName(*ppstTraceList, pcName);

    // If stop trace single package
    if (0 == ulLevel)
    {
        if (NULL == pstItem)
        {
            return VOS_OK;
        }
        ATP_UTIL_ListDeleteItem((ATP_UTIL_LIST_ST **)(ppstTraceList), (ATP_UTIL_LIST_ST *)pstItem, NULL);
        return VOS_OK;
    }

    // Set trace level for single package
    if (NULL == pstItem)
    {
        pstItem = (ATP_TRACE_CBB_LIST_ST *)malloc(sizeof(ATP_TRACE_CBB_LIST_ST));
        if (NULL == pstItem)
        {
            return ATP_MSG_RET_MEM_ERR;
        }
        memset((void *)pstItem, 0, sizeof(ATP_TRACE_CBB_LIST_ST));
        snprintf(pstItem->acName, 
        //            sizeof(pstItem->acName), 
                    sizeof(pstItem->acName) - 1,
                    "%s", 
                    pcName);
        ATP_UTIL_ListAppend((ATP_UTIL_LIST_ST **)(ppstTraceList), (ATP_UTIL_LIST_ST *)pstItem);
    }

    pstItem->ulLevel = ulLevel;
    return VOS_OK;
}
//lint -restore

VOS_UINT32 ATP_TRACE_SetPackageLevel(const VOS_CHAR *pcName, VOS_UINT32 ulLevel)
{
    return TraceCtxSetPackageLevel(&m_pstTraceList, pcName, ulLevel);
}
VOS_BOOL ATP_TRACE_IsModuleEnabled(const VOS_CHAR *pcModule, VOS_UINT32 ulLevel)
{
    const ATP_TRACE_CBB_LIST_ST     *pstItem;

    if (NULL == pcModule)
    {
        pcModule = ATP_DEBUG_MOD_ALL;
    }
    pstItem = TraceFindModuleByName(m_pstTraceList, pcModule);
    if (NULL == pstItem)
    {
        pstItem = TraceFindModuleByName(m_pstTraceList, ATP_DEBUG_MOD_ALL);
    }

    if (NULL == pstItem)
    {
        //printf("FILE: %s LINE: %d.\n", __FILE__, __LINE__);
        return VOS_FALSE;
    }

    if ((0 == pstItem->ulLevel) || (ulLevel > pstItem->ulLevel))
    {
        //printf("FILE: %s LINE: %d %d %d.\n", __FILE__, __LINE__, pstItem->ulLevel, ulLevel);
        return VOS_FALSE;
    }
    return VOS_TRUE;
}

//lint -save -e129
#ifdef SUPPORT_ATP_VOICE
 VOS_INT32      m_lCurPid = -1;
#else
VOS_INT32      m_lCurPid = -1;
#endif
//lint restore

VOS_INT32 ATP_UTIL_GetCurPid()
{
    if (m_lCurPid < 0)
    {
        m_lCurPid = getpid();
    }
    return m_lCurPid;
}

#define CLOCK2SECONDS(c)       ((c) / 1000)


/*!
  \brief :获取时间usec
  \param[in]  
 \return usec
  \retval 
*/
static VOS_UINT32  trace_gettimeofusec(VOS_VOID)
{
    struct timeval tv;

    /* get the usec of a day*/
    if ( 0 == gettimeofday( &tv, NULL ) )
    {
        return (VOS_UINT32)(tv.tv_usec);
    }
    else
    {
        return 0;
    }
}

/*!
  \brief :获取时间格式时:分:秒.毫秒
  \param[in]  
 \return VOS_CHAR *格式 字符串
  \retval 
*/
VOS_CHAR *ATP_UTIL_GetCurTimeStamp()
{
    static VOS_CHAR   acTime[32] = {0};
    struct tm *pTime = VOS_NULL;
    VOS_UINT32 us = 0;
    VOS_UINT32 ms = 0;
    time_t now; 

    time(&now);
    pTime = localtime(&now); 

    us = trace_gettimeofusec();
    ms = CLOCK2SECONDS(us);	

    if(VOS_NULL != pTime)
    {
    	snprintf(acTime, 
        //            sizeof(acTime), 
                    sizeof(acTime) - 1, 
                    "%02d:%02d:%02d.%d ", 
                    pTime->tm_hour, 
                    pTime->tm_min, 
                    pTime->tm_sec, 
                    ms);
    }

    return acTime;
}

#if DESC("Log output implementation")
// log 文件路径
#ifdef SUPPORT_ATP_EUAP
#define OSA_LOG_FILE_FULL_DIR          "/online/log"
#else
#define OSA_LOG_FILE_FULL_DIR          "/var/trace"
#endif

#define OSA_LOG_FILE_FULL_PATH         OSA_LOG_FILE_FULL_DIR"/webapp.log"

/*log输出的方式，1:打印到标准输出2:保存到文件4: 打印到SDT工具中*/
#define LOG_TO_STDOUT                   0
#define LOG_TO_FILE                     1

#define TRACE_LOG_FILE_MAX_SIZE         (1024)  // In KB
#define KB2B                            (1024) /*KB和B的换算*/

static FILE *m_fTraceFile = NULL;
static VOS_UINT64 m_fSize =  TRACE_LOG_FILE_MAX_SIZE;

VOS_VOID ATP_TRACE_SetFileMaxSize(VOS_UINT64 size)
{
    if(size > TRACE_LOG_FILE_MAX_SIZE)
    {
        m_fSize = size;
    }
    return;
}

VOS_UINT64 ATP_TRACE_GetFileMaxSize(VOS_VOID)
{
    return  m_fSize;
}

VOS_UINT32 ATP_TRACE_GetOutput(VOS_VOID)
{
    if ((NULL == m_fTraceFile) || (stdout == m_fTraceFile))
    {
        m_fTraceFile = stdout;
        return LOG_TO_STDOUT;
    }

    return LOG_TO_FILE;
}

VOS_VOID ATP_TRACE_SetOutput(VOS_UINT32 where)
{
    if (LOG_TO_STDOUT != where)
    {
        if ((NULL != m_fTraceFile) && (stdout != m_fTraceFile))
        {
            return;
        }

        // Create directory if necessary
        if ((access(OSA_LOG_FILE_FULL_DIR, F_OK)) == -1)
        {
            (VOS_VOID)mkdir(OSA_LOG_FILE_FULL_DIR, (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP));/*0750*/
        }

        // Open the file for read
        m_fTraceFile = fopen(OSA_LOG_FILE_FULL_PATH, "ab");
        return;
    }

    if (stdout == m_fTraceFile)
    {
        return;
    }
    if (NULL != m_fTraceFile)
    {
        fclose(m_fTraceFile);
    }
    m_fTraceFile = stdout;
}

static VOS_VOID TraceTruncateOutputFile()
{
    VOS_INT32   ret;
    struct stat buf;

    if (stdout == m_fTraceFile)
    {
        return;
    }

    ret = stat(OSA_LOG_FILE_FULL_PATH, &buf);
    if ((0 != ret) || (m_fSize <= (unsigned int)(buf.st_size) / KB2B))
    {
        (void)ftruncate(fileno(m_fTraceFile), 0);
    }
}
#endif

VOS_BOOL ATP_TRACE_PrintInfoEx(const VOS_CHAR *pcModule, VOS_UINT32 ulLevel, const VOS_INT8 *fmt, ...)
{
    va_list                         vaArgList;

    if (VOS_FALSE == ATP_TRACE_IsModuleEnabled(pcModule, ulLevel))
    {
        return VOS_FALSE;
    }

    if (NULL == pcModule)
    {
        pcModule = g_pcEmptyStr;
    }

    if (NULL == m_fTraceFile)
    {
        m_fTraceFile = stdout;
    }

    va_start(vaArgList, fmt);
    vfprintf(m_fTraceFile, fmt, vaArgList);
    va_end(vaArgList);

    fflush(stdout);

    TraceTruncateOutputFile();

    return VOS_TRUE;
}

VOS_BOOL ATP_TRACE_PrintInfo(const VOS_CHAR *pcFileName, VOS_UINT32 ulLineNo, VOS_BOOL bDbgMode, const VOS_CHAR *pcModule, VOS_UINT32 ulLevel, const VOS_INT8 *fmt, ...)
{
    va_list                         vaArgList;

    // TODO: Add module name to a list

    if ((VOS_FALSE == bDbgMode) && (VOS_FALSE == ATP_TRACE_IsModuleEnabled(pcModule, ulLevel)))
    {
        return VOS_FALSE;
    }

    if (NULL == pcModule)
    {
        pcModule = g_pcEmptyStr;
    }
    
    if (NULL == pcFileName)
    {
        pcFileName = g_pcEmptyStr;
    }
    if (NULL == m_fTraceFile)
    {
        m_fTraceFile = stdout;
    }
    fprintf(m_fTraceFile, "\r\n[(%s)%s %s:%d:%s %s:%d]: ", ATP_TRACE_GetLevelStr(ulLevel), ATP_UTIL_GetCurTimeStamp(),
           m_aucAppName, ATP_UTIL_GetCurPid(), pcModule, pcFileName, ulLineNo);

    va_start(vaArgList, fmt);
    vfprintf(m_fTraceFile, fmt, vaArgList);
    va_end(vaArgList);

    fflush(stdout);

    TraceTruncateOutputFile();

    return VOS_TRUE;
}



