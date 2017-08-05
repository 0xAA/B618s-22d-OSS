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
 
/*include 头文件*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/file.h>
#include <errno.h>
#include <mntent.h>
#define __ATP_DEPRECATED_H__
#include "atputil.h"
#include "loginctl.h"
#include "msgapi.h"
#include "gplapi.h"

#ifdef SUPPORT_ATP_USBSTORAGE


VOS_UINT32 ATP_LoginCtlInit(VOS_UINT32 ulLogType)
{
    VOS_UINT32 ulRet = VOS_OK;

    if(ATP_LOGINTYPE_FTP == ulLogType)
    {
        ulRet = ATP_MSG_Init(ATP_CBBID_BFTPD_NAME);
    }
    else
    {
        if(ATP_LOGINTYPE_SAMBA == ulLogType)
        {
            ulRet = ATP_MSG_Init(ATP_CBBID_SMBD_NAME);
        }
    }

    return ulRet;
}


ATP_SCTRL_LOGIN_RET_EN ATP_LoginCtlCheck(const VOS_CHAR *pszUsername ,const VOS_CHAR *pszIpAddr ,VOS_UINT32 ulLogType , 
                                                                VOS_UINT ulLogStatus)
{
    ATP_MSG_HEADER_ST   * pstMsg = VOS_NULL;
    ATP_MSG_HEADER_ST   * pstResp = VOS_NULL;
    VOS_UINT8   aucBuf[sizeof(ATP_MSG_HEADER_ST) + ATP_ACTUAL_LEN_512] = {0};
    VOS_CHAR    *pszTmp =  VOS_NULL;
    VOS_UINT32  ulRet = VOS_OK;

    LoginDebugPrint("Begin check login status...\n");

    if((VOS_NULL_PTR == pszUsername) && (VOS_NULL_PTR == pszIpAddr))
    {
        LoginDebugPrint("The pointer parameter is NULL\n");
        return ATP_LOGINRET_INNORMAL;
    }
    
    pszTmp = (VOS_CHAR *)(aucBuf + sizeof(ATP_MSG_HEADER_ST));
    /* 开启连接跟踪即时生效后,需要在cms杀掉指定的FTP/SAMBA进程,因此这里传入PID */
#ifdef SUPPORT_ATP_COMMON_CT_CLEAN
    snprintf(pszTmp , ATP_ACTUAL_LEN_512 - 1 , "%s %s %u %u %d" , pszUsername , pszIpAddr , ulLogType , ulLogStatus, getpid());
#else
    snprintf(pszTmp , ATP_ACTUAL_LEN_512 - 1 , "%s %s %u %u" , pszUsername , pszIpAddr , ulLogType , ulLogStatus);
#endif
    LoginDebugPrint("pszTmp=%s\n",pszTmp);
    pstMsg = (ATP_MSG_HEADER_ST *)aucBuf;
    ATP_MSG_SimpleBuilder(pstMsg , ATP_CBBID_CMS_NAME, ATP_MSG_CMS_LOGINCTL_CHECK , 0);
    pstResp = NULL;
    pstMsg->ulDataLen = strlen(pszTmp)+1;
    ulRet = ATP_MSG_SendAndRecv(pstMsg , &pstResp , 2*1000);
    memset(aucBuf, 0, sizeof(aucBuf));
    if(VOS_OK != ulRet)
    {
        LoginDebugPrint("ATP_MSG_SendAndRecv failed, ulRet:%x\n", ulRet);
        return ATP_LOGINRET_INNORMAL;
    }
    LoginDebugPrint("Ret=%u\n",pstResp->ulMsgData);
    ulRet = (ATP_SCTRL_LOGIN_RET_EN)(pstResp->ulMsgData);
    free((VOS_VOID *)pstResp);

    return (ATP_SCTRL_LOGIN_RET_EN)ulRet;
}


VOS_INT32 ATP_LoginCtlLogout(const VOS_CHAR *pszUsername , const VOS_CHAR *pszAddrInfo,VOS_UINT32 ulLogintype)
{
    ATP_MSG_HEADER_ST   * pstMsg = VOS_NULL;
    ATP_MSG_HEADER_ST   * pstResp = VOS_NULL;
    VOS_UINT8   aucBuf[sizeof(ATP_MSG_HEADER_ST) + ATP_ACTUAL_LEN_512] = {0};
    VOS_CHAR    *pszTmp =  VOS_NULL;
    VOS_UINT32   ulRet = VOS_OK;
    VOS_INT32   lRet = VOS_OK;

    LoginDebugPrint("Begin check login status...\n");

    if(VOS_NULL_PTR == pszUsername) 
    {
        LoginDebugPrint("The pointer parameter is NULL\n");
        return VOS_ERROR;
    }
    
    pszTmp = (VOS_CHAR *)(aucBuf + sizeof(ATP_MSG_HEADER_ST));
#ifdef SUPPORT_ATP_COMMON_CT_CLEAN
    snprintf(pszTmp , ATP_ACTUAL_LEN_512 - 1 , "%s %s %u %d" , pszUsername, pszAddrInfo, ulLogintype, getpid());
#else
    snprintf(pszTmp , ATP_ACTUAL_LEN_512 - 1 , "%s %s %u" , pszUsername, pszAddrInfo, ulLogintype);
#endif
    LoginDebugPrint("pszTmp=%s\n",pszTmp);
    pstMsg = (ATP_MSG_HEADER_ST *)aucBuf;
    ATP_MSG_SimpleBuilder(pstMsg , ATP_CBBID_CMS_NAME, ATP_MSG_CMS_LOGINCTL_LOGOUT , 0);
    pstResp = NULL;
    pstMsg->ulDataLen = strlen(pszTmp)+1;
    ulRet = ATP_MSG_SendAndRecv(pstMsg , &pstResp , 2*1000);
    memset(aucBuf, 0, sizeof(aucBuf));
    if(VOS_OK != ulRet)
    {
        LoginDebugPrint("ATP_MSG_SendAndRecv failed, ulRet:%x\n", ulRet);
        return VOS_ERROR;
    }
    LoginDebugPrint("Ret=%u\n",pstResp->ulMsgData);
    lRet = (VOS_INT32)(pstResp->ulMsgData);
    free((VOS_VOID *)pstResp);

    return lRet;
}


VOS_INT32 ATP_LoginCtlAllowWanAcc(const VOS_CHAR *pszUsername , VOS_UINT32 ulLogintype)
{
    ATP_MSG_HEADER_ST   * pstMsg = VOS_NULL;
    ATP_MSG_HEADER_ST   * pstResp = VOS_NULL;
    VOS_UINT8   aucBuf[sizeof(ATP_MSG_HEADER_ST) + ATP_ACTUAL_LEN_512] = {0};
    VOS_CHAR    *pszTmp =  VOS_NULL;
    VOS_UINT32  ulRet = VOS_OK;
    VOS_INT32   lRet = VOS_OK;

    LoginDebugPrint("Begin check login status...\n");

    if(VOS_NULL_PTR == pszUsername) 
    {
        LoginDebugPrint("The pointer parameter is NULL\n");
        return VOS_ERROR;
    }
    
    pszTmp = (VOS_CHAR *)(aucBuf + sizeof(ATP_MSG_HEADER_ST));
    snprintf(pszTmp , ATP_ACTUAL_LEN_512 - 1 , "%s %u" , pszUsername , ulLogintype);
    LoginDebugPrint("pszTmp=%s\n",pszTmp);
    pstMsg = (ATP_MSG_HEADER_ST *)aucBuf;
    ATP_MSG_SimpleBuilder(pstMsg , ATP_CBBID_CMS_NAME, ATP_MSG_CMS_LOGINCTL_ALLOWWAN , 0);
    pstResp = NULL;
    pstMsg->ulDataLen = strlen(pszTmp)+1;
    ulRet = ATP_MSG_SendAndRecv(pstMsg , &pstResp , 2*1000);
    memset(aucBuf, 0, sizeof(aucBuf));
    if(VOS_OK != ulRet)
    {
        LoginDebugPrint("ATP_MSG_SendAndRecv failed, ulRet:%x\n", ulRet);
        return VOS_ERROR;
    }
    LoginDebugPrint("Ret=%u\n",pstResp->ulMsgData);
    lRet = (VOS_INT32)(pstResp->ulMsgData);
    free((VOS_VOID *)pstResp);

    return lRet;
}
#ifdef SUPPORT_ATP_FTP_ACCESS_CONTROL

VOS_INT32 ATP_LoginCtlCheckFtpAcc(const VOS_CHAR *pszUsername, VOS_UINT32 ulFtpType,VOS_UINT32 ulFromType)
{
    ATP_MSG_HEADER_ST   * pstMsg = VOS_NULL;
    ATP_MSG_HEADER_ST   * pstResp = VOS_NULL;
    VOS_UINT8   aucBuf[sizeof(ATP_MSG_HEADER_ST) + ATP_ACTUAL_LEN_512] = {0};
    VOS_CHAR    *pszTmp =  VOS_NULL;
    VOS_UINT32  ulRet = VOS_OK;
    VOS_INT32   lRet = VOS_OK;

    pszTmp = (VOS_CHAR *)(aucBuf + sizeof(ATP_MSG_HEADER_ST));
    snprintf(pszTmp , ATP_ACTUAL_LEN_512 - 1 , "%s %u %u" , pszUsername, ulFtpType,ulFromType);
    LoginDebugPrint("pszTmp=%s\n",pszTmp);
    pstMsg = (ATP_MSG_HEADER_ST *)aucBuf;
    ATP_MSG_SimpleBuilder(pstMsg , ATP_CBBID_CMS_NAME, ATP_MSG_CMS_LOGINCTL_ALLOWFTPTYPE , 0);
    pstResp = NULL;
    pstMsg->ulDataLen = strlen(pszTmp)+1;
    LoginDebugPrint("ulDataLen=%d\n",pstMsg->ulDataLen);
    ulRet = ATP_MSG_SendAndRecv(pstMsg , &pstResp , 2*1000);
	memset(aucBuf, 0, sizeof(aucBuf));
    if(VOS_OK != ulRet)
    {
        LoginDebugPrint("ATP_MSG_SendAndRecv failed, ulRet:%x\n", ulRet);
        return VOS_ERROR;
    }
    LoginDebugPrint("Ret=%u\n",pstResp->ulMsgData);
    lRet = (VOS_INT32)(pstResp->ulMsgData);
    free((VOS_VOID *)pstResp);
    printf("---------------->%d\r\n",ulRet);
    return lRet;
}
#endif
#endif


#ifdef __BIONIC__
extern FILE *setmntent(const char *filename, const char *type);
extern struct mntent *getmntent_r(FILE *fp, struct mntent *mnt, char *buf, int buflen);
extern int endmntent(FILE *fp);
#endif
VOS_INT32   ATP_UTIL_IsPathVfat(const char *pcPath)
{
    FILE                *fstab;
    struct mntent       mtEnt;
    VOS_CHAR        acBuf[1024];

    if (NULL == pcPath)
    {
        return 0;
    }

    fstab = setmntent("/proc/mounts", "r");
    if (NULL == fstab)
    {
        return 0;
    }

    memset((void *)(&(mtEnt)), 0, sizeof(mtEnt));
    memset((void *)acBuf, 0, sizeof(acBuf));
    while (NULL != getmntent_r(fstab, &mtEnt, acBuf, sizeof(acBuf)))
    {
        if ((NULL != mtEnt.mnt_type) && (0 != strcmp(mtEnt.mnt_type, "vfat")))
        {
            continue;
        }

        if ((NULL != mtEnt.mnt_dir) &&
            (0 == memcmp((void *)(mtEnt.mnt_dir), (void *)pcPath, strlen(mtEnt.mnt_dir))) &&
            (('/' == pcPath[strlen(mtEnt.mnt_dir)]) || ('\0' == pcPath[strlen(mtEnt.mnt_dir)])))
        {
            endmntent(fstab);
            return 1;
        }

        memset((void *)(&(mtEnt)), 0, sizeof(mtEnt));
        memset((void *)acBuf, 0, sizeof(acBuf));
    }
    endmntent(fstab);

    return 0;
}



