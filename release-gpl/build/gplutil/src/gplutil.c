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
#include <ctype.h>
#define __ATP_DEPRECATED_H__
#include "atptypes.h"
#ifdef SUPPORT_ATP_VOICE
#include "voicepub.h"
#endif
#include "gplrealloc.h"
#ifdef SUPPORT_ATP_DHCP6C
#include <dirent.h>
#endif
#include "msgapi.h"

#if 1
VOS_UINT32 ATP_UTIL_GetSysTime(struct timeval* pstTimeVal)
{
    struct timespec ts;

    if (!pstTimeVal)
    {
        return VOS_NOK;
    }

	if (syscall(__NR_clock_gettime, CLOCK_MONOTONIC, &ts))
	{
        pstTimeVal->tv_sec   = 0;
        pstTimeVal->tv_usec  = 0;
	    perror("syscall:__NR_clock_gettime");
        return VOS_NOK;
	}

    pstTimeVal->tv_sec   = ts.tv_sec;
    pstTimeVal->tv_usec  = ts.tv_nsec/1000; 
    return VOS_OK;
}
#else
VOS_UINT32 ATP_UTIL_GetSysTime(struct timeval* pstTimeVal)
{
    struct timespec ts;

    if (!pstTimeVal)
    {
        return VOS_NOK;
    }

    if (gettimeofday(pstTimeVal, NULL) < 0)
    {
        pstTimeVal->tv_sec   = 0;
        pstTimeVal->tv_usec  = 0;
        return VOS_NOK;
    }

    pstTimeVal->tv_sec   = ts.tv_sec;
    pstTimeVal->tv_usec  = ts.tv_nsec/1000; 
    return VOS_OK;
}
#endif

#ifdef SUPPORT_ATP_VOICE
/*****************************************************************************
 �� �� ��: ATP_UTIL_VoiceGetVoipStatus
 ��������: ��ȡVoIP״̬�����л���æ
           VoIP״̬������SIP�ʺ�״̬����ӳ��ֻҪ��һ��SIP�ʺ�Ϊæ�򷵻�æ״̬�Ľ��
 �������: ��
 �������: ��
 �� �� ֵ: VoIP״̬: VOS_FALSEΪ����;VOS_TRUEΪæ
*****************************************************************************/
VOS_BOOL ATP_UTIL_VoiceGetVoipStatus(VOS_VOID)
{
    FILE        *pstFile;
    VOS_UINT32  ulStatus;
    VOS_CHAR    acSrcData[VOICE_STATUS_LEN_MAX];

    memset(acSrcData, 0, VOICE_STATUS_LEN_MAX);
    pstFile = fopen(FILE_PATH_VOIP_STATUS, "rb");
    if (VOS_NULL_PTR == pstFile)
    {
        return VOS_FALSE;
    }

    fread(acSrcData, 1, VOICE_STATUS_LEN_MAX, pstFile);
    fclose(pstFile);
    acSrcData[VOICE_STATUS_LEN_MAX - 1] = '\0';
    ulStatus = (VOS_UINT32)atoi(acSrcData);
    if (ulStatus > 0)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}
#ifdef SUPPORT_ATP_VOICE_DT
VOS_INT32 ATP_UTIL_VoiceGetSipInterval(VOS_VOID)
{
        FILE *      fp = VOS_NULL_PTR;
        VOS_CHAR        acFile[VOICE_STATUS_LEN_MAX];   

        memset(&acFile, 0, sizeof(acFile));
        
        fp = fopen(FILE_PATH_VOIP_INTERVAL, "r");
        if ( VOS_NULL_PTR == fp )
        {
            return 0;
        }
        fread(acFile, 1, VOICE_STATUS_LEN_MAX, fp);
        fclose(fp);
        printf("the number is %d\n",(VOS_UINT32)atoi(acFile));
        return (VOS_UINT32)atoi(acFile);
}
#endif
/*****************************************************************************
 �� �� ��: ATP_UTIL_VoiceGetVoipStatus
 ��������: ��ȡVoIP״̬�����л���æ
           VoIP״̬������SIP�ʺ�״̬����ӳ��ֻҪ��һ��SIP�ʺ�Ϊæ�򷵻�æ״̬�Ľ��
 �������: ��
 �������: ��
 �� �� ֵ: VoIP״̬: VOS_FALSEΪ����;VOS_TRUEΪæ
*****************************************************************************/
VOS_BOOL ATP_UTIL_VoiceHasUrgCall(VOS_VOID)
{
    FILE        *pstFile;
    VOS_UINT32  ulStatus;
    VOS_CHAR    acSrcData[VOICE_STATUS_LEN_MAX];

    memset(acSrcData, 0, VOICE_STATUS_LEN_MAX);
    pstFile = fopen(FILE_PATH_URGCALL_STATUS, "rb");
    if (VOS_NULL_PTR == pstFile)
    {
        return VOS_FALSE;
    }

    fread(acSrcData, 1, VOICE_STATUS_LEN_MAX, pstFile);
    fclose(pstFile);
    acSrcData[VOICE_STATUS_LEN_MAX - 1] = '\0';
    ulStatus = (VOS_UINT32)atoi(acSrcData);
    if (ulStatus > 0)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}
#endif


#ifdef SUPPORT_ATP_DHCP6C

#define ATP_SYS_READ_BUF_SIZE 128
#define ATP_SYS_MEDIUM_LEN 240


static VOS_BOOL GPL_UTIL_RmDelimitor( VOS_CHAR *pcBuf)
{
    VOS_BOOL  bRet = VOS_TRUE;    
    VOS_INT   i = 0;
    VOS_INT   j = 0;


    if ( pcBuf == VOS_NULL ) 
    {
        return VOS_FALSE;
    }

    while((*(pcBuf + i) != '\0') || (*(pcBuf + i + 1) != '\0'))
    {
        if(*(pcBuf + i) == '\0')
        {
            i++;
            continue;
        }
        *(pcBuf + j) = *(pcBuf + i);
        j++;
        i++;
    }
    *(pcBuf + j) = '\0';

    return bRet;

}



static VOS_INT32* GPL_UTIL_FindPidByName( VOS_CHAR* pszPidName)
{
    DIR    *pDir;
    struct dirent *pNext = VOS_NULL;
    VOS_INT32*   pPidList = VOS_NULL;
    VOS_UINT32    i = 0;

    FILE *pCmdline = VOS_NULL;
    VOS_CHAR    acFilename[ATP_SYS_READ_BUF_SIZE];
    VOS_CHAR    acBuffer[ATP_SYS_READ_BUF_SIZE];
    size_t szPidList = 0;

    if ( pszPidName == VOS_NULL ) 
    {
        return VOS_NULL;
    }

#ifdef ATP_PCLINT
    pszPidName = pszPidName;
#endif

    pDir = opendir("/proc");
    if (!pDir) 
    {
        printf("cms:Cannot open /proc");
        return VOS_NULL;
    }

    while ((pNext = readdir(pDir)) != VOS_NULL) 
    {
        /* ���³�ʼ�� */
        memset(acFilename, 0, sizeof(acFilename));
        memset(acBuffer, 0, sizeof(acBuffer));  

        /* ��/proc�й��˵�".."*/
        if (strcmp(pNext->d_name, "..") == 0)
        {
            continue;
        }

        /* �������ֱ��������� */
        if (!isdigit(*pNext->d_name))
        {
            continue;
        }

        snprintf(acFilename, sizeof(acFilename), "/proc/%s/cmdline", pNext->d_name);
        if (VOS_NULL == (pCmdline = fopen(acFilename, "r")) ) 
        {
            continue;
        }
        if (fgets(acBuffer, ATP_SYS_READ_BUF_SIZE-1, pCmdline) == VOS_NULL) 
        {
            fclose(pCmdline);
            continue;
        }
        fclose(pCmdline);

        /* acBuffer������������ "Name:   binary_name" */
        /*��'\0'ȥ��*/
        GPL_UTIL_RmDelimitor(acBuffer);
        if (strstr(acBuffer, pszPidName) != VOS_NULL) 
        {
            if(0 == i)
            {
                pPidList = (VOS_INT32*)malloc(sizeof(VOS_INT32) * (i + 2));
            }
            else
            {
                pPidList = (VOS_INT32*)gpl_realloc( pPidList, szPidList,sizeof(VOS_INT32) * (i + 2));
            }
            szPidList = sizeof(VOS_INT32) * (i + 2);
            if (!pPidList) 
            {
                printf("cms: Out of memeory!\n");
				closedir(pDir);
                return VOS_NULL;
            }
                pPidList[i++] = strtol(pNext->d_name, VOS_NULL, 0);
        }
    }
    closedir(pDir);

    if (pPidList)
    {
        pPidList[i] = 0;
    }
    else if ( strcmp(pszPidName, "init") == 0) 
    {
        /* init������Ϊ����ID:1 */
        pPidList = (VOS_INT32*)gpl_realloc( pPidList,  sizeof(VOS_INT32) * (i + 1),sizeof(VOS_INT32));
        if (!pPidList) 
        {
            printf("cms: Out of memeory!\n");
            return VOS_NULL;
        }
        pPidList[0] = 1;
    } 
    else 
    {
        pPidList = (VOS_INT32*)gpl_realloc( pPidList,  sizeof(VOS_INT32) * (i + 1),sizeof(VOS_INT32));
        if (!pPidList) 
        {
            printf("cms: Out of memeory!\n");
            return VOS_NULL;
        }
        pPidList[0] = -1;
    }
    return pPidList;
}



VOS_INT GPL_UTIL_GetPid(VOS_CHAR * pcCommand)
{
    VOS_CHAR   acCmdline[ATP_SYS_MEDIUM_LEN];
    VOS_CHAR   *pcTmp1 = VOS_NULL;
    VOS_CHAR   *pcTmp2 = VOS_NULL;
    pid_t *pPid = VOS_NULL;
    VOS_INT    lRet = 0;

    if ( pcCommand == VOS_NULL )
    {
        return lRet;
    }
    
    pcTmp1 = pcCommand;
    pcTmp2 = acCmdline;
    while ( *pcTmp1 != '\0') 
    {
        if (*pcTmp1 != ' ') 
        {
            *pcTmp2 = *pcTmp1;
            pcTmp2++;
        }
        pcTmp1++;
    }
    *pcTmp2='\0';

    /* pPid�ڴ������ATP_UTIL_FindPidByName���� */
    pPid = GPL_UTIL_FindPidByName(acCmdline);
    if ( pPid != VOS_NULL ) 
    {
       lRet = (VOS_INT)(*pPid);
       free(pPid);
       pPid = VOS_NULL;
    }

    return lRet;
}

#endif
