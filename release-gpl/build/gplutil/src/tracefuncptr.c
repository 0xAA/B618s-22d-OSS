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
#include "securec.h"
#include "atptypes.h"
#include "msgapi.h"

static VOS_BOOL m_bTraceFuncPtr = VOS_FALSE;

typedef struct tagSYMBOL_LIST
{
    struct tagSYMBOL_LIST *pstNext;
    VOS_VOID              *pfAddr;
    const VOS_CHAR        *pcSymbolName;
} SYMBOL_LIST;

static SYMBOL_LIST *m_pstSymbolList = NULL;

static SYMBOL_LIST *UtilSymbolFindByAddr(const VOS_VOID *func)
{
    SYMBOL_LIST *pstItem;

    pstItem = m_pstSymbolList;
    while (NULL != pstItem)
    {
        if (func == pstItem->pfAddr)
        {
            break;
        }
        pstItem = pstItem->pstNext;
    }
    return pstItem;
}

VOS_VOID *ATP_UTIL_SymbolListAdd(const VOS_CHAR *pcSymbolName, VOS_VOID *func)
{
    SYMBOL_LIST     *pstNew;

    if ((NULL == pcSymbolName) || (NULL == func))
    {
        return func;
    }

    if (VOS_FALSE == m_bTraceFuncPtr)
    {
        return func;
    }

    pstNew = UtilSymbolFindByAddr(func);
    if (NULL != pstNew)
    {
        return func;
    }

    pstNew = (SYMBOL_LIST *)malloc(sizeof(SYMBOL_LIST));
    if (NULL == pstNew)
    {
        return func;
    }
    //memset_s((VOS_VOID *)pstNew, sizeof(SYMBOL_LIST), 0, sizeof(SYMBOL_LIST));
    pstNew->pfAddr = NULL;
    pstNew->pstNext = NULL;
    pstNew->pcSymbolName = strdup(pcSymbolName);
    if (NULL == pstNew->pcSymbolName)
    {
        ATP_FREE(pstNew);
        return func;
    }
    pstNew->pfAddr = func;

    pstNew->pstNext = m_pstSymbolList;
    m_pstSymbolList = pstNew;

    return func;
}

VOS_VOID ATP_UTIL_TraceSymbolEnable(VOS_BOOL bEnable)
{
    m_bTraceFuncPtr = bEnable;
}

//lint -save -e10 -e2  CI PCLint has defined ATP_UTIL_GetSymbolNameByPtr as nothing, we ignore here
const VOS_CHAR *ATP_UTIL_GetSymbolNameByPtr(const VOS_VOID *func)
{
    SYMBOL_LIST     *pstItem;
    pstItem = UtilSymbolFindByAddr(func);
    if (NULL == pstItem)
    {
        return g_pcEmptyStr;
    }
    return pstItem->pcSymbolName;
}

VOS_VOID ATP_UTIL_TraceSymbolPrint(const VOS_CHAR *fmt, ...)
{
    va_list             vaArgList;

    if (VOS_FALSE == m_bTraceFuncPtr)
    {
        return;
    }

    va_start(vaArgList, fmt);
    //lint -save -e64
    vfprintf(stdout, fmt, vaArgList);
    //lint restore
    va_end(vaArgList);
}
//lint -restore

