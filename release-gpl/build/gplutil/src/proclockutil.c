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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>
#define __ATP_DEPRECATED_H__
#include "proclockutil.h"


#ifdef __BIONIC__
ATP_PROC_LOCK_INFO_ST gstProcLockInfo ;
#endif
static int proc_create_file(const char *psLockFile)
{
    int iLockFd = -1;

    if (NULL == psLockFile)
    {
        return -1;
    }
    
    iLockFd = open(psLockFile, O_RDWR|O_CREAT, 0777);
    if (iLockFd < 0)
    {
        return -1;
    }

    close(iLockFd);
    return 0;
}




FILE *ATP_UTIL_LockProc(const char *psLockFile)
{
    FILE    *fp = NULL;
    int     lfd = 0;

    if (NULL == psLockFile)
    {
        return NULL;
    }

    if (access(psLockFile, F_OK) != 0)
    {
        if (proc_create_file(psLockFile) < 0)
        {
            return NULL;
        }
    }

    fp = fopen(psLockFile, "r");
    if (NULL == fp)
    {
        return NULL;
    }

    lfd = fileno(fp);
    if (lfd < 0)
    {
        fclose(fp);
        return NULL;
    }

    if (flock(lfd, LOCK_EX) < 0)
    {
        printf("lock %d failed\n", lfd);
    }

    return fp;
}




int ATP_UTIL_UnLockProc(FILE * fpLockFile)
{
    int    lfd = 0;

    if (NULL == fpLockFile)
    {
        return -1;
    }

    lfd = fileno(fpLockFile);
    if (lfd < 0)
    {
        return -1;
    }
    
    if (flock(lfd, LOCK_UN) < 0 )
    {
        printf("unlock %d failed\n", lfd);
    }

    fclose(fpLockFile);
    return 0;
}

#ifndef __BIONIC__
static void proc_exit_unlock(int lstatus, void *pvProcLockInfo)
{
    ATP_PROC_LOCK_INFO_ST *pstProcLockInfo = NULL;
    lstatus = lstatus;

    if (NULL == pvProcLockInfo) {
        return;
    }

    pstProcLockInfo = (ATP_PROC_LOCK_INFO_ST *)pvProcLockInfo;

    /*只对父进程进行解锁*/
    if (getpid() != pstProcLockInfo->ulProcPid) {
        return;
    }

    ATP_UTIL_UnLockProc(pstProcLockInfo->pfLockFile);

    ATP_FREE(pvProcLockInfo);
    return;
}
#else
static void proc_exit_unlock(void)
{    
    /*只对父进程进行解锁*/
    if (getpid() != gstProcLockInfo.ulProcPid) {
        return;
    }
    ATP_UTIL_UnLockProc(gstProcLockInfo.pfLockFile);
    return;
}
#endif



void ATP_UTIL_RegUnLock(FILE *pfLockFile)
{
#ifndef __BIONIC__
    ATP_PROC_LOCK_INFO_ST *pstProcLockInfo = NULL;

    if (NULL == pfLockFile)
    {
        return;
    }

    pstProcLockInfo = (ATP_PROC_LOCK_INFO_ST *)malloc(sizeof(ATP_PROC_LOCK_INFO_ST));
    if (NULL == pstProcLockInfo)
    {
        return;
    }

    memset(pstProcLockInfo, 0, sizeof(ATP_PROC_LOCK_INFO_ST));
    pstProcLockInfo->pfLockFile = pfLockFile;
    pstProcLockInfo->ulProcPid = getpid();
    on_exit(proc_exit_unlock, (void *)pstProcLockInfo);
#else  

    if (NULL == pfLockFile)
    {
        return;
    }

    memset(&gstProcLockInfo, 0, sizeof(ATP_PROC_LOCK_INFO_ST));
    gstProcLockInfo.pfLockFile = pfLockFile;
    gstProcLockInfo.ulProcPid = getpid();
    atexit(proc_exit_unlock);
#endif
    return;
}

