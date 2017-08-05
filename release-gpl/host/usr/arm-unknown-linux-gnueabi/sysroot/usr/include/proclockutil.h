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


#ifndef __ATP_PROCLOCKUTIL_H__
#define __ATP_PROCLOCKUTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "atptypes.h"

/*!< 需要进行互斥执行命令的lock文件*/
#define IPTABLES_LOCK_FILE "/var/iptables_lock_file"
#define EBTABLES_LOCK_FILE "/var/ebtables_lock_file"

typedef struct TagATP_PROC_LOCK_INFO_ST
{
    pid_t ulProcPid;          /*!< 进程pid*/
    FILE  *pfLockFile;      /*!< 进程lock流*/
}ATP_PROC_LOCK_INFO_ST;

/*!
  \brief  根据指定文件名上文件锁，用于保障进程串行执行
  \param[in]  *psLockFile:进程文件锁名
  \return 
  \retval NULL失败; 非空成功
*/

FILE *ATP_UTIL_LockProc(const char *psLockFile);
/*!
  \brief 文件解锁，用于保障进程串行执行
  \param[in]  fpLockFile:  fpLockFile:文件锁流输入
  \return 
  \retval -1失败; 0 成功
*/

int ATP_UTIL_UnLockProc(FILE * fpLockFile);
/*!
  \brief 注册进程退出前的解锁操作
  \param[in]  fpLockFile: pstProcLockInfo:进程锁信息
  \return 
  \retval 
*/

void ATP_UTIL_RegUnLock(FILE * fpLockFile);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __ATP_PROCLOCKUTIL__ */

