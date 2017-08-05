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
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define __ATP_DEPRECATED_H__
#include "atptypes.h"
#include "atputil.h"
#include "gplrealloc.h"
#define UTIL_WAIT_PID_INTERVAL_D            (40)

static const VOS_CHAR *m_apcBinSearchPath[] =
{
    "/var",
#ifdef SUPPORT_ATP_MUPG
    ATP_INSTALL_BIN_DIR_D"/bin",
#endif
    "/bin",
    "/sbin",
    "/usr/bin",
    NULL
};

VOS_VOID ATP_UTIL_FreeArgs(VOS_CHAR **argv)
{
    VOS_UINT32      ulIdx;

    if (NULL == argv)
    {
        return;
    }

    ulIdx = 0;
    while (NULL != argv[ulIdx])
    {
        free((VOS_VOID *)argv[ulIdx]);
        ulIdx++;
    }

    free((VOS_VOID *)argv);
}

static VOS_UINT32 UtilCopyRawString(VOS_CHAR **ppcDest, VOS_CHAR **ppcSrc)
{
    VOS_CHAR        cChar;

    for (;;)
    {
        if(! (*ppcSrc))
        {
            break;
        }
        cChar = *((*ppcSrc));
        (*ppcSrc)++;

        *(*ppcDest) = cChar;
        (*ppcDest)++;
        switch (cChar)
        {
        case '\0':
            return VOS_NOK;

        case '\'':
            return VOS_OK;

        default:
            break;
        }
    }

    return VOS_NOK;
}

static VOS_UINT32 UtilCopyCookedString(VOS_CHAR **ppcDest, VOS_CHAR **ppcSrc)
{
    VOS_CHAR cChar;

    for (;;)
    {
        if(! (*ppcSrc))
        {
            break;
        }
        cChar = *((*ppcSrc));
        (*ppcSrc)++;
        (*(*ppcDest)) = cChar;
        (*ppcDest)++;
        switch (cChar)
        {
        case '\0':
            return VOS_NOK;
        case '"':
            return VOS_OK;

        case '\\':
            //cChar = UtilEscapeConvt(ppcSrc);
            cChar = *(*ppcSrc);
            (*ppcSrc)++;
            if ('\0' == cChar)
                return VOS_NOK;
            else if (('\\' == cChar) || ('"' == cChar))
                (*ppcDest)--;
            (*(*ppcDest)) = cChar;
            (*ppcDest)++;
            break;

        default:
            break;
        }
    }

    return VOS_NOK;
}

static VOS_CHAR *UtilStripLeadingDir(VOS_CHAR *pcStr)
{
    if (NULL == pcStr)
    {
        return pcStr;
    }

    if (('.' == pcStr[0]) && ('/' == pcStr[1]))
    {
        return pcStr + 2;
    }

    return pcStr;
}

VOS_CHAR *ATP_UTIL_SafeStrDup(const VOS_CHAR *pcStr)
{
    if (NULL == pcStr)
    {
        return strdup("");
    }
    return strdup(pcStr);
}

//lint -save -e801
VOS_UINT32 ATP_UTIL_ParseArgs(const VOS_CHAR *pcStr, VOS_CHAR *** pppcArgv,
                VOS_INT32 *plArgc, ATP_PARSE_SH_SYMBOL_ST *pstSymbols)
{
    VOS_INT32   lArgc;
    VOS_INT32   lActualArgs;
    VOS_CHAR    **ppcRes;
    VOS_UINT32  ulResSize = 0;
    VOS_CHAR    **ppcArgv;
    VOS_CHAR    *pcScan;
    VOS_CHAR    *pcDest;
    VOS_CHAR    *pcCopy;
    VOS_CHAR    *pcUnquoteStr;
    VOS_INT32   lLenth = 0;
    VOS_UINT32  ulRetVal;
    VOS_CHAR    cChar;
    VOS_BOOL    bBothRedirect;

    if (NULL != plArgc)
    {
        (*plArgc) = 0;
    }
    if (NULL != pstSymbols)
    {
        memset((VOS_VOID *)pstSymbols, 0, sizeof(ATP_PARSE_SH_SYMBOL_ST));
    }

    if ((NULL == pcStr) || (NULL == pppcArgv))
    {
        return VOS_NOK;
    }

    if (strlen(pcStr) > (4 * 1024))
    {
        return VOS_NOK;
    }

    // Init argvs
    lArgc       = 0;
    lActualArgs = 10;
    ulResSize = sizeof(VOS_CHAR *) * (VOS_UINT32)lActualArgs;
    ppcRes = (VOS_CHAR **)malloc(ulResSize);
    if (NULL == ppcRes)
    {
        return VOS_NOK;
    }
    ppcArgv = ppcRes;

    // Skip white spaces
    while (isspace((VOS_UINT8)(*pcStr)))
    {
        pcStr++;
    }
    pcCopy = strdup(pcStr);
    if(VOS_NULL == pcCopy)
    {
        ATP_FREE(ppcRes);
        return VOS_NOK;
    }
    pcScan = pcCopy;

    for (;;) {
        // Skip white spaces
        while (isspace((VOS_UINT8)(*pcScan)))
        {
            pcScan++;
        }
        if ('\0' == (*pcScan))
        {
            break;
        }

        // Realloc memory if necessary
        lArgc++;
        if (lArgc >= (lActualArgs - 4)) {
            lActualArgs += lActualArgs / 2;
            ppcRes  = (VOS_CHAR **)gpl_realloc(ppcRes, ulResSize,(VOS_UINT32)lActualArgs * sizeof(char *));
            ulResSize = ((VOS_UINT32)lActualArgs * sizeof(char*));
            if (NULL == ppcRes)
            {
                ATP_FREE(pcCopy);
                return VOS_NOK;
            }
            ppcArgv = ppcRes + (lArgc - 1);
        }

        (*ppcArgv) = pcScan;
        pcDest = pcScan;
        ppcArgv++;

        // Loop to copy a token
        for (;;) {
            cChar = *pcScan;
            pcScan++;
            (*pcDest) = cChar;
            pcDest++;
            switch (cChar)
            {
            case '\0':
                goto done;

            case '\\':
                if ('\0' == (*pcScan))
                {
                    (*pcDest) = '\0';
                    goto done;
                }
                if ('\\' == *pcScan)
                {
                    pcDest--;
                }
                (*pcDest) = (*pcScan);
                pcDest++;
                pcScan++;
                break;

            case '\'':
                pcDest--;       // Strip the leading "
                ulRetVal = UtilCopyRawString(&pcDest, &pcScan);
                pcDest--;       // Strip the ending "
                if (VOS_OK != ulRetVal)
                    goto error_leave;
                break;

            case '"':
                pcDest--;       // Strip the leading "
                ulRetVal = UtilCopyCookedString(&pcDest, &pcScan);
                if (VOS_OK != ulRetVal)
                    goto error_leave;
                pcDest--;       // Strip the ending "
                break;

            case ' ':
            case '\t':
            case '\n':
            case '\f':
            case '\r':
            case '\v':
            case '\b':
                pcDest--;
                goto token_done;

            default:
                break;
            }
        }

    token_done:
        *pcDest = '\0';
    }

done:
    *pppcArgv = ppcRes;
    *ppcArgv  = NULL;

    // Check if it is a background command, ie, ending with &
    if ((NULL != pstSymbols) && (lArgc > 0))
    {
        pcUnquoteStr = ppcRes[lArgc - 1];
        if (pcUnquoteStr)
        {
            lLenth = (VOS_INT32)strlen(pcUnquoteStr);
        }
        if ((NULL != pcUnquoteStr) && (lLenth > 0))
        {
            if (0 == strcmp(pcUnquoteStr, "&"))
            {
                pstSymbols->bIsBackground = VOS_TRUE;
                lArgc -= 1;
                ppcRes[lArgc] = NULL;
            }
            else if ('&' == pcUnquoteStr[lLenth - 1])
            {
                pcUnquoteStr[lLenth - 1] = '\0';
                pstSymbols->bIsBackground = VOS_TRUE;
            }
        }
    }

    bBothRedirect = VOS_FALSE;

    // Check if it is redirecting
    if ((NULL != pstSymbols) && (lArgc > 1))
    {
        pcUnquoteStr = ppcRes[lArgc - 1];
        if ((0 == strcmp(pcUnquoteStr, "2>&1")) || (0 == strcmp(pcUnquoteStr, "1>&2")) ||
            (0 == strcmp(pcUnquoteStr, "1>&1")) || (0 == strcmp(pcUnquoteStr, "2>&2"))) // Just ignore
        {
            // Ignored cases
            // ... 2>&1
            // ... 1>&2
            // ... 1>&1
            // ... 2>&2
            lArgc -= 1;
            ppcRes[lArgc] = NULL;
            bBothRedirect = VOS_TRUE;
        }
        else if ((0 == strcmp(ppcRes[lArgc - 2], ">")) ||
                 (0 == strcmp(ppcRes[lArgc - 2], ">>")))
        {
            // ... > /var/test.xml
            // ... >> /var/test.xml

            // Notice: The 1 and 2 in the following cases are not interpreted as stdout or stderr
            // ... 1 > /var/test.xml
            // ... 2 >> /var/test.xml
            pstSymbols->pcStdoutFile = pcUnquoteStr;
            if (0 == strcmp(ppcRes[lArgc - 2], ">>"))
            {
                pstSymbols->bStdoutAppend = VOS_TRUE;
            }
            lArgc -= 2;
            ppcRes[lArgc] = NULL;
        }
        else if ('>' == pcUnquoteStr[0])
        {
            // ... >/var/test.xml
            // ... >>/var/test.xml

            // Ignored cases
            // ... >
            // ... >>
            pcUnquoteStr++;
            if ('>' == pcUnquoteStr[0])
            {
                pcUnquoteStr++;
                if ('\0' != pcUnquoteStr[0])
                {
                    pstSymbols->bStdoutAppend = VOS_TRUE;
                }
            }
            if ('\0' != pcUnquoteStr[0])
            {
                pstSymbols->pcStdoutFile = pcUnquoteStr;
            }
            lArgc -= 1;
            ppcRes[lArgc] = NULL;
        }
        else if ((('1' == pcUnquoteStr[0]) || ('2' == pcUnquoteStr[0])) && ('>' == pcUnquoteStr[1]))
        {
            // Ignored cases
            // ... 1>
            // ... 2>
            // ... 1>>
            // ... 2>>
            if (('>' == pcUnquoteStr[2]) && ('\0' != pcUnquoteStr[3]))  // Append
            {
                if ('1' == pcUnquoteStr[0])
                {
                    //... 1>>/var/test.xml
                    pstSymbols->pcStdoutFile  = pcUnquoteStr + 3;
                    pstSymbols->bStdoutAppend = VOS_TRUE;
                }
                else
                {
                    //... 2>>/var/test.xml
                    pstSymbols->pcStderrFile  = pcUnquoteStr + 3;
                    pstSymbols->bStderrAppend = VOS_TRUE;
                }
            }
            else if ('\0' != pcUnquoteStr[2])    // No append
            {
                if ('1' == pcUnquoteStr[0])
                {
                    //... 1>/var/test.xml
                    pstSymbols->pcStdoutFile  = pcUnquoteStr + 2;
                }
                else
                {
                    //... 2>/var/test.xml
                    pstSymbols->pcStderrFile  = pcUnquoteStr + 2;
                }
            }
            lArgc -= 1;
            ppcRes[lArgc] = NULL;
        }
        else
        {
            pcUnquoteStr = ppcRes[lArgc - 2];
            lLenth = (VOS_INT32)strlen(pcUnquoteStr);
            if ((lLenth > 0) && ('>' == pcUnquoteStr[lLenth - 1]))
            {
                if ((lLenth > 1) && ('>' == pcUnquoteStr[lLenth - 2]))
                {
                    if (0 == strcmp(pcUnquoteStr, "1>>"))
                    {
                        // ... 1>> /var/test.xml
                        pstSymbols->pcStdoutFile  = ppcRes[lArgc - 1];
                        pstSymbols->bStdoutAppend = VOS_TRUE;
                        lArgc -= 1;
                    }
                    else if (0 == strcmp(pcUnquoteStr, "2>>"))
                    {
                        // ... 2>> /var/test.xml
                        pstSymbols->pcStderrFile  = ppcRes[lArgc - 1];
                        pstSymbols->bStderrAppend = VOS_TRUE;
                        lArgc -= 1;
                    }
                    else
                    {
                        // ... cmd>> /var/test.xml
                        pcUnquoteStr[lLenth - 2] = '\0';
                        pstSymbols->pcStdoutFile  = ppcRes[lArgc - 1];
                        pstSymbols->bStdoutAppend = VOS_TRUE;
                        lArgc -= 1;
                    }
                    lArgc -= 1;
                    ppcRes[lArgc] = NULL;
                }
                else
                {
                    if (0 == strcmp(pcUnquoteStr, "1>"))
                    {
                        // ... 1> /var/test.xml
                        pstSymbols->pcStdoutFile  = ppcRes[lArgc - 1];
                        lArgc -= 1;
                    }
                    else if (0 == strcmp(pcUnquoteStr, "2>"))
                    {
                        // ... 2> /var/test.xml
                        pstSymbols->pcStderrFile  = ppcRes[lArgc - 1];
                        lArgc -= 1;
                    }
                    else
                    {
                        // ... cmd> /var/test.xml
                        pcUnquoteStr[lLenth - 1] = '\0';
                        pstSymbols->pcStdoutFile  = ppcRes[lArgc - 1];
                    }
                    lArgc -= 1;
                    ppcRes[lArgc] = NULL;
                }
            }
        }
    }

    // Check redirect again
    if ((NULL != pstSymbols) && (lArgc > 1))
    {
        pcUnquoteStr = ppcRes[lArgc - 1];
        if ((0 == strcmp(pcUnquoteStr, "1>&1")) || (0 == strcmp(pcUnquoteStr, "2>&2"))) // Just ignore
        {
            // Ignored cases
            // ... 1>&1 redirect1
            // ... 2>&2 redirect1
            lArgc -= 1;
            ppcRes[lArgc] = NULL;
            bBothRedirect = VOS_TRUE;
        }
        else if (0 == strcmp(pcUnquoteStr, "2>&1"))
        {
            // ... 2>&1 redirect1
            if (NULL == pstSymbols->pcStderrFile)
            {
                pstSymbols->pcStderrFile  = pstSymbols->pcStdoutFile;
                pstSymbols->bStderrAppend = pstSymbols->bStdoutAppend;
            }
            lArgc -= 1;
            ppcRes[lArgc] = NULL;
        }
        else if (0 == strcmp(pcUnquoteStr, "1>&2"))
        {
            // ... 1>&2 redirect1
            if (NULL == pstSymbols->pcStdoutFile)
            {
                pstSymbols->pcStdoutFile  = pstSymbols->pcStderrFile;
                pstSymbols->bStdoutAppend = pstSymbols->bStderrAppend;
            }
            lArgc -= 1;
            ppcRes[lArgc] = NULL;
        }
        else if ((0 == strcmp(ppcRes[lArgc - 2], ">")) ||
                 (0 == strcmp(ppcRes[lArgc - 2], ">>")))
        {
            // ... > /var/test.xml redirect1
            // ... >> /var/test.xml redirect1

            // Notice: The 1 and 2 in the following cases are not interpreted as stdout or stderr
            // ... 1 > /var/test.xml redirect1
            // ... 2 >> /var/test.xml redirect1
            if (NULL == pstSymbols->pcStdoutFile)
            {
                pstSymbols->pcStdoutFile = pcUnquoteStr;
                if (0 == strcmp(ppcRes[lArgc - 2], ">>"))
                {
                    pstSymbols->bStdoutAppend = VOS_TRUE;
                }
            }
            lArgc -= 2;
            ppcRes[lArgc] = NULL;
        }
        else if ('>' == pcUnquoteStr[0])
        {
            // ... >/var/test.xml redirect1
            // ... >>/var/test.xml redirect1

            // Ignored cases
            // ... > redirect1
            // ... >> redirect1
            pcUnquoteStr++;
            if ('>' == pcUnquoteStr[0])
            {
                pcUnquoteStr++;
                if (('\0' != pcUnquoteStr[0]) && (NULL == pstSymbols->pcStdoutFile))
                {
                    pstSymbols->bStdoutAppend = VOS_TRUE;
                }
            }
            if (('\0' != pcUnquoteStr[0]) && (NULL == pstSymbols->pcStdoutFile))
            {
                pstSymbols->pcStdoutFile = pcUnquoteStr;
            }
            lArgc -= 1;
            ppcRes[lArgc] = NULL;
        }
        else if ((('1' == pcUnquoteStr[0]) || ('2' == pcUnquoteStr[0])) && ('>' == pcUnquoteStr[1]))
        {
            // Ignored cases
            // ... 1> redirect1
            // ... 2> redirect1
            // ... 1>> redirect1
            // ... 2>> redirect1
            if (('>' == pcUnquoteStr[2]) && ('\0' != pcUnquoteStr[3]))  // Append
            {
                if ('1' == pcUnquoteStr[0])
                {
                    if (NULL == pstSymbols->pcStdoutFile)
                    {
                        //... 1>>/var/test.xml redirect1
                        pstSymbols->pcStdoutFile  = pcUnquoteStr + 3;
                        pstSymbols->bStdoutAppend = VOS_TRUE;
                    }
                }
                else
                {
                    if (NULL == pstSymbols->pcStderrFile)
                    {
                        //... 2>>/var/test.xml redirect1
                        pstSymbols->pcStderrFile  = pcUnquoteStr + 3;
                        pstSymbols->bStderrAppend = VOS_TRUE;
                    }
                }
            }
            else if ('\0' != pcUnquoteStr[2])    // No append
            {
                if ('1' == pcUnquoteStr[0])
                {
                    if (NULL == pstSymbols->pcStdoutFile)
                    {
                        //... 1>/var/test.xml redirect1
                        pstSymbols->pcStdoutFile  = pcUnquoteStr + 2;
                    }
                }
                else
                {
                    if (NULL == pstSymbols->pcStderrFile)
                    {
                        //... 2>/var/test.xml redirect1
                        pstSymbols->pcStderrFile  = pcUnquoteStr + 2;
                    }
                }
            }
            lArgc -= 1;
            ppcRes[lArgc] = NULL;
        }
        else
        {
            pcUnquoteStr = ppcRes[lArgc - 2];
            lLenth = (VOS_INT32)strlen(pcUnquoteStr);
            if ((lLenth > 0) && ('>' == pcUnquoteStr[lLenth - 1]))
            {
                if ((lLenth > 1) && ('>' == pcUnquoteStr[lLenth - 2]))
                {
                    if (0 == strcmp(pcUnquoteStr, "1>>"))
                    {
                        // ... 1>> /var/test.xml redirect1
                        if (NULL == pstSymbols->pcStdoutFile)
                        {
                            pstSymbols->pcStdoutFile  = ppcRes[lArgc - 1];
                            pstSymbols->bStdoutAppend = VOS_TRUE;
                        }
                        lArgc -= 1;
                    }
                    else if (0 == strcmp(pcUnquoteStr, "2>>"))
                    {
                        // ... 2>> /var/test.xml redirect1
                        if (NULL == pstSymbols->pcStderrFile)
                        {
                            pstSymbols->pcStderrFile  = ppcRes[lArgc - 1];
                            pstSymbols->bStderrAppend = VOS_TRUE;
                        }
                        lArgc -= 1;
                    }
                    else
                    {
                        // ... cmd>> /var/test.xml redirect1
                        pcUnquoteStr[lLenth - 2] = '\0';
                        if (NULL == pstSymbols->pcStdoutFile)
                        {
                            pstSymbols->pcStdoutFile  = ppcRes[lArgc - 1];
                            pstSymbols->bStdoutAppend = VOS_TRUE;
                        }
                        lArgc -= 1;
                    }
                    lArgc -= 1;
                    ppcRes[lArgc] = NULL;
                }
                else
                {
                    if (0 == strcmp(pcUnquoteStr, "1>"))
                    {
                        // ... 1> /var/test.xml redirect1
                        if (NULL == pstSymbols->pcStdoutFile)
                        {
                            pstSymbols->pcStdoutFile  = ppcRes[lArgc - 1];
                        }
                        lArgc -= 1;
                    }
                    else if (0 == strcmp(pcUnquoteStr, "2>>"))
                    {
                        // ... 2> /var/test.xml redirect1
                        if (NULL == pstSymbols->pcStderrFile)
                        {
                            pstSymbols->pcStderrFile  = ppcRes[lArgc - 1];
                        }
                        lArgc -= 1;
                    }
                    else
                    {
                        // ... cmd> /var/test.xml redirect1
                        pcUnquoteStr[lLenth - 1] = '\0';
                        if (NULL == pstSymbols->pcStdoutFile)
                        {
                            pstSymbols->pcStdoutFile  = ppcRes[lArgc - 1];
                        }
                    }
                    lArgc -= 1;
                    ppcRes[lArgc] = NULL;
                }
            }
        }
    }

    // Make a copy of the string
    for (lActualArgs = 0; lActualArgs < lArgc; lActualArgs++)
    {
        if (0 == lActualArgs)
        {
            ppcRes[0] = strdup(UtilStripLeadingDir(ppcRes[0]));
        }
        else
        {
	        ppcRes[lActualArgs] = ATP_UTIL_SafeStrDup(ppcRes[lActualArgs]);
        }
        
        if (NULL == ppcRes[lActualArgs])
        {
            for (lArgc = 0; lArgc < lActualArgs; lArgc++)
            {
                free((VOS_VOID *)(ppcRes[lArgc]));
            }
            goto error_leave;
        }
    }

    if (NULL != pstSymbols)
    {
        if (NULL != pstSymbols->pcStdoutFile)
        {
            pstSymbols->pcStdoutFile = strdup(pstSymbols->pcStdoutFile);
        }
        if (NULL != pstSymbols->pcStderrFile)
        {
            pstSymbols->pcStderrFile = strdup(pstSymbols->pcStderrFile);
        }
    }

    if (VOS_FALSE != bBothRedirect)
    {
        if ((NULL !=pstSymbols) && (NULL == pstSymbols->pcStdoutFile))
        {
            if (NULL != pstSymbols->pcStderrFile)
            {
                pstSymbols->pcStdoutFile = strdup(pstSymbols->pcStderrFile);
            }
        }
        if ((NULL !=pstSymbols) && (NULL == pstSymbols->pcStderrFile))
        {
            if (NULL != pstSymbols->pcStdoutFile)
            {
                pstSymbols->pcStderrFile = strdup(pstSymbols->pcStdoutFile);
            }
        }
    }

    ppcRes[lActualArgs] = NULL;
    free((void *)pcCopy);
    if (NULL != plArgc)
    {
        (*plArgc) = lActualArgs;
    }
    if (0 == lActualArgs)
    {
        ATP_UTIL_FreeArgs(ppcRes);
        (*pppcArgv) = NULL;
    }
    return VOS_OK;

error_leave:
    printf("Warning: not ended cmd [%s].\n", pcStr);
    free(ppcRes);
     //lint -save -e644
    free((void *)pcCopy);
    //lint -restore
    return VOS_NOK;
}



// ulWaitMiliSecs: 0 means no wait, -1 means wait for ever
VOS_INT32 ATP_UTIL_WaitForPid(VOS_INT32 lPid, VOS_INT32 lWaitMiliSecs,
                                            VOS_INT32 *plExitSignal, VOS_INT32 *plExitCode)
{
    VOS_INT32       lRet;
    VOS_INT32       lStatus;
    VOS_INT32       lWaitFlag;
    VOS_INT32       lWaitTime;

    lWaitFlag = 0;
    if (lWaitMiliSecs >= 0)
    {
        lWaitFlag = WNOHANG;
    }

    do 
    {
        lRet = waitpid(lPid, &lStatus, lWaitFlag);
        if (-1 == lRet)     // Error
        {
            if (EINTR == errno)
            {
                continue;
            }
            if (ECHILD != errno)
            {
                //printf("Wait pid for %d return error %d.\n", lRet, errno);
                return -1;
            }
            else
            {
                return lPid;
            }
        }
        else if (0 == lRet)     // None
        {
            if (lWaitMiliSecs <= 0)
            {
                if (0 == lWaitMiliSecs)
                {
                    return lPid;
                }
                return -1;
            }
            lWaitTime = UTIL_WAIT_PID_INTERVAL_D;
            if (lWaitMiliSecs < UTIL_WAIT_PID_INTERVAL_D)
            {
                lWaitTime = lWaitMiliSecs;
            }
            usleep((VOS_UINT32)lWaitTime * 1000);
            if (lWaitTime < UTIL_WAIT_PID_INTERVAL_D)
            {
               lWaitMiliSecs = 0;
            }
            else
            {
                lWaitMiliSecs -= UTIL_WAIT_PID_INTERVAL_D;
            }
        }
        else
        {
            if (NULL != plExitSignal)
            {
                (*plExitSignal) = (VOS_INT32)(WIFSIGNALED(lStatus) ? WTERMSIG(lStatus) : 0);
            }
            if (NULL != plExitCode)
            {
                (*plExitCode) = (VOS_INT32)(WEXITSTATUS(lStatus));
            }
            return lRet;
        }
    } while (1);
}

VOS_INT32 ATP_UTIL_GetExeFullPath(const VOS_CHAR *pcExeName, VOS_CHAR *pcFullPath, VOS_UINT32 ulLength)
{
    VOS_INT32               lIdx;
    struct stat64           info;

    if ((NULL == pcExeName) || ('\0' == pcExeName[0]) || (NULL == pcFullPath))
    {
        return -1;
    }

    // Try /var directory for debugging
    if ('/' != pcExeName[0])
    {
        lIdx = 0;
        while (NULL != m_apcBinSearchPath[lIdx])
        {
            snprintf(pcFullPath, ulLength, "%s/%s", m_apcBinSearchPath[lIdx], pcExeName);
            if ((stat64(pcFullPath, &info) < 0) || (0 == (S_IXUSR & info.st_mode)) || (0 == (S_IFREG & info.st_mode)))
            {
                lIdx++;
                continue;
            }
            return 0;
        }
        return -1;
    }

    snprintf(pcFullPath, ulLength, "%s", pcExeName);
    return 0;
}

VOS_INT32 ATP_UTIL_ForkProcessFull(const VOS_CHAR *argv[], VOS_INT32 lWaitMiliSecs,
                                            VOS_INT32 *plExitSignal, VOS_INT32 *plExitCode,
                                            ATP_PARSE_SH_SYMBOL_ST *pstSymbols)
{
    VOS_INT32               lPid;
    VOS_CHAR                acPath[256];
    VOS_INT32               lRedirectStdout;
    VOS_INT32               lRedirectStderr;
    VOS_INT32               lSaveSigChld;
    struct sigaction        stOldAct;
    struct sigaction        stNewAct;

    memset(&stOldAct, 0, sizeof(stOldAct));
    memset(&stNewAct, 0, sizeof(stNewAct));

#ifdef ATP_PCLINT
    argv = argv;
    pstSymbols = pstSymbols;
#endif

    if (0 != ATP_UTIL_GetExeFullPath(argv[0], acPath, sizeof(acPath)))
    {
        return -1;
    }

    lRedirectStdout = -1;
    lRedirectStderr = -1;
    if ((NULL != pstSymbols) && (NULL != pstSymbols->pcStdoutFile))
    {
        if (VOS_FALSE != pstSymbols->bStdoutAppend)
        {
            lRedirectStdout = open(pstSymbols->pcStdoutFile, O_RDWR | O_CREAT | O_APPEND, S_IRUSR  | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        }
        else
        {
            lRedirectStdout = open(pstSymbols->pcStdoutFile, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR  | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        }
    }
    if ((NULL != pstSymbols) && (NULL != pstSymbols->pcStderrFile))
    {
        if ((NULL != pstSymbols->pcStdoutFile) &&
            (0 == strcmp(pstSymbols->pcStdoutFile, pstSymbols->pcStderrFile)))
        {
            lRedirectStderr = lRedirectStdout;
        }
        else
        {
            if (VOS_FALSE != pstSymbols->bStderrAppend)
            {
                lRedirectStderr = open(pstSymbols->pcStderrFile, O_RDWR | O_CREAT | O_APPEND, S_IRUSR  | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            }
            else
            {
                lRedirectStderr = open(pstSymbols->pcStderrFile, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR  | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            }
        }
    }

    stNewAct.sa_flags |= SA_RESTART;
    stNewAct.sa_handler = SIG_DFL;
    lSaveSigChld = sigaction(SIGCHLD, &stNewAct, &stOldAct);
    if (0 != lSaveSigChld)
    {
        perror("sigaction error\r\n");
    }
    lPid = fork();
    if (lPid > 0)
    {
        //printf("Child process [%d].\n", lPid);
        if (-1 != lRedirectStdout)
        {
            close(lRedirectStdout);
        }
        if (lRedirectStdout != lRedirectStderr)
        {
            if(-1 != lRedirectStderr)
            {   
                close(lRedirectStderr);
            }
        }
        if ((NULL != pstSymbols) && (VOS_FALSE != pstSymbols->bIsBackground))
        {
            lWaitMiliSecs = -1;
        }
        lPid = ATP_UTIL_WaitForPid(lPid, lWaitMiliSecs, plExitSignal, plExitCode);
        if (0 == lSaveSigChld)
        {
            sigaction(SIGCHLD, &stOldAct, NULL);        
        }
        return lPid;
    }
    else if (lPid < 0)
    {
        //printf("Fork process failed with errno %d.\n", errno);
        if (-1 != lRedirectStdout)
        {
            close(lRedirectStdout);
        }
        if (lRedirectStdout != lRedirectStderr)
        {
            if(-1 != lRedirectStderr)
            {   
                close(lRedirectStderr);
            }
        }
        return lPid;
    }

    // Child process
    //setsid();

    // Close unnecessary fds in the child process
    for (lPid = 3; lPid < 50; lPid++)
    {
        if ((lRedirectStdout != lPid) && (lRedirectStderr != lPid))
        {
            close(lPid);
        }
    }
    if (-1 != lRedirectStdout)
    {
        // Redirect stderr and stdout
        close(1);   // stdout
        dup2(lRedirectStdout, 1);
    }
    if (-1 != lRedirectStderr)
    {
        // Redirect stderr and stdout
        close(2);   // stderr
        dup2(lRedirectStderr, 2);
    }
    if (-1 != lRedirectStdout)
    {
        close(lRedirectStdout);
    }
    if ((-1 != lRedirectStderr) && (lRedirectStdout != lRedirectStderr))
    {
        close(lRedirectStderr);
    }

    if ((NULL != pstSymbols) && (VOS_FALSE != pstSymbols->bIsBackground))
    {
            lRedirectStderr = open("/dev/null", O_RDWR);
            if (lRedirectStderr > 0)
            {
                close(0);
                dup2(lRedirectStderr, 0);
                close(lRedirectStderr);
            }
        // Double fork to be deamon
        lPid = fork();
        if (lPid < 0)
        {
            exit(-1);
        }
        if (0 < lPid)
        {
            exit(0);
        }
        setsid();
    }

    // Restore all signal processing to default for the child process
    if ((0 == lWaitMiliSecs) && (NULL != pstSymbols) && (VOS_FALSE != pstSymbols->bIsBackground))
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
    }
    else
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
    }
    signal(SIGHUP, SIG_DFL);
    signal(SIGILL, SIG_DFL);
    signal(SIGTRAP, SIG_DFL);
#ifdef SIGEMT
    //lint -save -e40
    signal(SIGEMT, SIG_DFL);
    //lint -restore
#endif
    signal(SIGABRT, SIG_DFL);  // same as SIGIOT
    signal(SIGFPE, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);
    signal(SIGBUS, SIG_DFL);
    signal(SIGSYS, SIG_DFL);
    signal(SIGALRM, SIG_DFL);
    signal(SIGPIPE, SIG_DFL);
    signal(SIGTERM, SIG_DFL);
    signal(SIGUSR2, SIG_DFL);
    signal(SIGUSR1, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);  // same as SIGCLD
    signal(SIGPWR, SIG_DFL);
    signal(SIGURG, SIG_DFL);
    signal(SIGWINCH, SIG_DFL);
    signal(SIGIO, SIG_DFL);    // same as SIGPOLL
    signal(SIGTSTP, SIG_DFL);
    signal(SIGSTOP, SIG_DFL);
    signal(SIGCONT, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGPROF, SIG_DFL);
    signal(SIGVTALRM, SIG_DFL);
    signal(SIGXFSZ, SIG_DFL);
    signal(SIGXCPU, SIG_DFL);

    execv(acPath, (char* const*)argv);

    exit(-1);
}

VOS_INT32 ATP_UTIL_ForkProcessEx(const VOS_CHAR *argv[], VOS_INT32 lWaitMiliSecs,
                                            VOS_INT32 *plExitSignal, VOS_INT32 *plExitCode)
{
    ATP_PARSE_SH_SYMBOL_ST      stSymbol;

    if (0 == lWaitMiliSecs)
    {
        memset((VOS_VOID *)(&stSymbol), 0, sizeof(stSymbol));
        stSymbol.bIsBackground = VOS_TRUE;
        return ATP_UTIL_ForkProcessFull(argv, lWaitMiliSecs, plExitSignal, plExitCode, &stSymbol);
    }

    return ATP_UTIL_ForkProcessFull(argv, lWaitMiliSecs, plExitSignal, plExitCode, NULL);
}

static void UtilFreeSymbols(ATP_PARSE_SH_SYMBOL_ST *pstSymbols)
{
#ifdef ATP_PCLINT
    pstSymbols = pstSymbols;
#endif
	if (NULL != pstSymbols->pcStdoutFile)
	{
		free((void *)pstSymbols->pcStdoutFile);
	}
	if (NULL != pstSymbols->pcStderrFile)
	{
		free((void *)pstSymbols->pcStderrFile);
	}
}

VOS_INT32 ATP_UTIL_ForkProcess(const VOS_CHAR *pcCmd, VOS_INT32 lWaitMiliSecs,
                                            VOS_INT32 *plExitSignal, VOS_INT32 *plExitCode)
{
    VOS_INT32               lPid;
    VOS_INT32               lArgc;
    VOS_UINT32              ulRetVal;
    VOS_CHAR                **ppcArgv = NULL;
    ATP_PARSE_SH_SYMBOL_ST  stSymbols;

    ulRetVal = ATP_UTIL_ParseArgs(pcCmd, &ppcArgv, &lArgc, &stSymbols);
    if ((VOS_OK != ulRetVal) || (0 == lArgc))
    {
        ATP_UTIL_FreeArgs(ppcArgv);
        UtilFreeSymbols(&stSymbols);
        return -1;
    }

    if (VOS_FALSE != stSymbols.bIsBackground)
    {
        lWaitMiliSecs = 0;
    }

    lPid = ATP_UTIL_ForkProcessFull((const VOS_CHAR **)ppcArgv, lWaitMiliSecs, plExitSignal, plExitCode, &stSymbols);
    ATP_UTIL_FreeArgs(ppcArgv);
	UtilFreeSymbols(&stSymbols);
    return lPid;
}

