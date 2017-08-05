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

/*!< ��Ҫ���л���ִ�������lock�ļ�*/
#define IPTABLES_LOCK_FILE "/var/iptables_lock_file"
#define EBTABLES_LOCK_FILE "/var/ebtables_lock_file"

typedef struct TagATP_PROC_LOCK_INFO_ST
{
    pid_t ulProcPid;          /*!< ����pid*/
    FILE  *pfLockFile;      /*!< ����lock��*/
}ATP_PROC_LOCK_INFO_ST;

/*!
  \brief  ����ָ���ļ������ļ��������ڱ��Ͻ��̴���ִ��
  \param[in]  *psLockFile:�����ļ�����
  \return 
  \retval NULLʧ��; �ǿճɹ�
*/

FILE *ATP_UTIL_LockProc(const char *psLockFile);
/*!
  \brief �ļ����������ڱ��Ͻ��̴���ִ��
  \param[in]  fpLockFile:  fpLockFile:�ļ���������
  \return 
  \retval -1ʧ��; 0 �ɹ�
*/

int ATP_UTIL_UnLockProc(FILE * fpLockFile);
/*!
  \brief ע������˳�ǰ�Ľ�������
  \param[in]  fpLockFile: pstProcLockInfo:��������Ϣ
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

