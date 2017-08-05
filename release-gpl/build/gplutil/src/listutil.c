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
 
 #include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include "atptypes.h"
#include "msgapi.h"

/*
 *  General List Utilities
 */
VOS_UINT32 ATP_UTIL_ListGetCount(ATP_UTIL_LIST_ST *pstList)
{
    VOS_UINT32      ulCnt;
#ifdef ATP_PCLINT
    pstList = pstList;
#endif

    ulCnt = 0;
    while (NULL != pstList)
    {
        ulCnt++;
        pstList = pstList->pstNext;
    }
    return ulCnt;
}

VOS_VOID ATP_UTIL_ListDeleteItem(
                        ATP_UTIL_LIST_ST            **ppstStart,
                        ATP_UTIL_LIST_ST            *pstDelItem,
                        PFUtilListItemDestroyProc   pfDestroy)
{
    ATP_UTIL_LIST_ST        *pstPrev;

    if ((NULL == ppstStart) || (NULL == pstDelItem))
    {
        return;
    }

    if (pstDelItem == (*ppstStart))
    {
        (*ppstStart) = pstDelItem->pstNext;
        if (NULL != pfDestroy)
        {
            pfDestroy(pstDelItem);
        }
        ATP_FREE(pstDelItem);
        return;
    }
    pstPrev = (*ppstStart);
    while (NULL != pstPrev)
    {
        if (pstDelItem == pstPrev->pstNext)
        {
            pstPrev->pstNext = pstDelItem->pstNext;
            if (NULL != pfDestroy)
            {
                pfDestroy(pstDelItem);
            }
            ATP_FREE(pstDelItem);
            return;
        }
        pstPrev = pstPrev->pstNext;
    }
}

VOS_VOID ATP_UTIL_ListDeleteItemEx(
                        ATP_UTIL_LIST_ST            **ppstStart,
                        ATP_UTIL_LIST_ST            *pstDelItem)
{
    ATP_UTIL_LIST_ST        *pstPrev;

    if ((NULL == ppstStart) || (NULL == pstDelItem))
    {
        return;
    }

    if (pstDelItem == (*ppstStart))
    {
        (*ppstStart) = pstDelItem->pstNext;
        return;
    }
    pstPrev = (*ppstStart);
    while (NULL != pstPrev)
    {
        if (pstDelItem == pstPrev->pstNext)
        {
            pstPrev->pstNext = pstDelItem->pstNext;
            return;
        }
        pstPrev = pstPrev->pstNext;
    }
}


VOS_VOID ATP_UTIL_ListDeleteAll(
                        ATP_UTIL_LIST_ST            *pstList,
                        PFUtilListItemDestroyProc   pfDestroy)
{
    ATP_UTIL_LIST_ST        *pstNext;

    while (NULL != pstList)
    {
        pstNext = pstList->pstNext;
        if (NULL != pfDestroy)
        {
            pfDestroy(pstList);
        }
        ATP_FREE(pstList);
        pstList = pstNext;
    }
}

VOS_VOID ATP_UTIL_ListAppend(
                        ATP_UTIL_LIST_ST            **ppstList,
                        ATP_UTIL_LIST_ST            *pstItem)
{
    ATP_UTIL_LIST_ST    **ppIterator;

    ppIterator = ppstList;
    while (NULL != (*ppIterator))
    {
    	// If exists, just return
    	if (pstItem == (*ppIterator))
		{
			return;
		}
        ppIterator = &((*ppIterator)->pstNext);
    }
    (*ppIterator) = pstItem;
}

ATP_UTIL_LIST_ST *ATP_UTIL_ListFindItem(const ATP_UTIL_LIST_ST *pstList, const VOS_VOID *pvData,
                                        PFUtilListItemCompareProc pfCompareProc)
{
    ATP_UTIL_LIST_ST    *pstTemp;

    if ((NULL == pfCompareProc) || (NULL == pvData))
    {
        return NULL;
    }

    pstTemp = (ATP_UTIL_LIST_ST *)pstList;
    while (NULL != pstTemp)
    {
        if (VOS_FALSE != pfCompareProc(pstTemp, pvData))
        {
            return pstTemp;
        }
        pstTemp = pstTemp->pstNext;
    }
    return pstTemp;
}

VOS_UINT32 ATP_UTIL_ListIterateItem(const ATP_UTIL_LIST_ST *pstList, const VOS_VOID *pvCookie,
                                      PFUtilListItemIterateProc pfIterateProc)
{
    VOS_UINT32          ulRetVal;
    ATP_UTIL_LIST_ST    *pstTemp;

    if (NULL == pfIterateProc)
    {
        return VOS_OK;
    }

    ulRetVal = VOS_OK;
    pstTemp = (ATP_UTIL_LIST_ST *)pstList;
    while (NULL != pstTemp)
    {
        ulRetVal = pfIterateProc(pstTemp, pvCookie);
        if (VOS_OK != ulRetVal)
        {
            break;
        }
        pstTemp = pstTemp->pstNext;
    }
    return ulRetVal;
}

