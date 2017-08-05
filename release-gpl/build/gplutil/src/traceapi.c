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

#include "tracelog.c"


extern VOS_VOID ATP_TRACE_SetOutput(VOS_UINT32 where);
extern VOS_UINT32 ATP_TRACE_GetOutput(VOS_VOID);
extern VOS_VOID ATP_TRACE_SetFileMaxSize(VOS_UINT64 size);
extern VOS_UINT64 ATP_TRACE_GetFileMaxSize(VOS_VOID);

static const VOS_CHAR *m_apcTraceClOutputMap[] =
{
    "stdout",
    "file",
};

static VOS_VOID TraceDisplayOutPut(VOS_UINT32 ulOutPut)
{
    ATP_Debug_Print("\n trace output to %s \n", ATP_UTIL_GetStrFromIdx(
                        (VOS_INT32)ulOutPut, m_apcTraceClOutputMap,
                        ATP_ARRAY_LEN(m_apcTraceClOutputMap), NULL)
                    );
}

static VOS_VOID TraceDisplayHeader()
{
    ATP_Debug_Print("%-12s %-20s %-8s"ATP_END_OF_LINE_STR_D, "App", "Module", "Level");
}

VOS_VOID TraceDisplayOneItem(const VOS_CHAR *pcAppName, const ATP_TRACE_CBB_LIST_ST *pstModuleList, VOS_BOOL bShowHeader)
{
    const ATP_TRACE_CBB_LIST_ST *pstItem;

    TraceDisplayOutPut(ATP_TRACE_GetOutput());

    if (VOS_FALSE != bShowHeader)
    {
        TraceDisplayHeader();
    }

    pstItem = pstModuleList;
    while (NULL != pstItem)
    {
        ATP_Debug_Print("%-12s %-20s %-8s"ATP_END_OF_LINE_STR_D, pcAppName, pstItem->acName, ATP_TRACE_GetLevelStr(pstItem->ulLevel));
        pcAppName = "";
        pstItem = pstItem->pstNext;
    }
}

VOS_VOID ATP_TRACE_Display()
{
    TraceDisplayOneItem(g_stMsgCtx.aucAppName, m_pstTraceList, VOS_TRUE);
}

typedef struct tagTRACE_MODULE_NAME_LIST_ST
{
    struct tagTRACE_MODULE_NAME_LIST_ST     *pstNext;
    const VOS_CHAR                          *pcName;
} TRACE_MODULE_NAME_LIST_ST;

static TRACE_MODULE_NAME_LIST_ST *m_pstModuleNames = NULL;

//lint -save -e429
VOS_UINT32 ATP_TRACE_RegModule(const VOS_CHAR *pcModuleName)
{
    TRACE_MODULE_NAME_LIST_ST       *pstItem;

    pstItem = (TRACE_MODULE_NAME_LIST_ST *)malloc(sizeof(TRACE_MODULE_NAME_LIST_ST));
    if (NULL == pstItem)
    {
        return ATP_MSG_RET_MEM_ERR;
    }
    memset((void *)pstItem, 
                0, 
     //           0, 
                sizeof(TRACE_MODULE_NAME_LIST_ST));

    pstItem->pcName = strdup(pcModuleName);
    if (NULL == pstItem->pcName)
    {
        ATP_FREE(pstItem);
        return ATP_MSG_RET_MEM_ERR;
    }

    ATP_UTIL_ListAppend((ATP_UTIL_LIST_ST **)(&m_pstModuleNames), (ATP_UTIL_LIST_ST *)pstItem);
    return VOS_OK;
}
//lint restore


/*
 *      For message init response message to recover trace levels
 */
VOS_VOID TraceMsgInitRespProc(const ATP_TRACE_GOLBAL_INFO_ST *pstTraceGlobalInfo, VOS_UINT32 ulLen)
{
    VOS_UINT32              ulIdx;
    VOS_UINT32              ulCnt;
    VOS_UINT32              ulWhere;
    ATP_TRACE_CBB_LIST_ST   *pstItem;  
    
    m_aucAppName = g_stMsgCtx.aucAppName;
    
    if (NULL == pstTraceGlobalInfo  || 0 == ulLen)
    {
        return;
    }
    ulWhere = pstTraceGlobalInfo->ulWhere;
    ATP_TRACE_SetFileMaxSize(pstTraceGlobalInfo->ullSize);
    pstItem = (ATP_TRACE_CBB_LIST_ST*)(&pstTraceGlobalInfo->pvHook);

    ulIdx = 0;
    ulCnt = 0;

    /* 都是unsigned, 最好不要用减法，避免造成死循环*/
    while (ulCnt + sizeof(ATP_TRACE_GOLBAL_INFO_ST) - sizeof(VOS_VOID*) < ulLen)
    {
        ATP_TRACE_SetPackageLevel(pstItem[ulIdx].acName, ATP_MSG_SAFE_ENDIAN_SWAP(pstItem[ulIdx].ulLevel));
        ulCnt += sizeof(ATP_TRACE_CBB_LIST_ST);
        ulIdx += 1;
    }

    ATP_TRACE_SetOutput(ulWhere);
}

/*
 *      Trace commands
 */
#ifdef SUPPORT_ATP_DEBUG_CMD

static VOS_VOID TracePrintRegisteredModules()
{
    const TRACE_MODULE_NAME_LIST_ST *pstModule;

    pstModule = m_pstModuleNames;
    while (NULL != pstModule)
    {
        ATP_Debug_Print("%s|", pstModule->pcName);
        pstModule = pstModule->pstNext;
    }
}


VOS_UINT32 ATP_TRACE_GetOutputByString(const VOS_CHAR *pcOutput)
{
    VOS_INT32               lIdx;

    lIdx = ATP_UTIL_GetIdxFromStr(pcOutput, m_apcTraceClOutputMap, ATP_ARRAY_LEN(m_apcTraceClOutputMap), NULL);
    return (VOS_UINT32)lIdx;
}

static VOS_VOID TracePrintAvailableOutput()
{
    VOS_UINT32 ulIdx;

    ATP_Debug_Print("{");
    ulIdx = 0;
    while (ulIdx < (ATP_ARRAY_LEN(m_apcTraceClOutputMap) - 1))
    {
        ATP_Debug_Print("%s|", m_apcTraceClOutputMap[ulIdx]);
        ulIdx++;
    }
    if (NULL != m_apcTraceClOutputMap[ulIdx])
    {
        ATP_Debug_Print("%s", m_apcTraceClOutputMap[ulIdx]);
    }
    ulIdx++;
    ATP_Debug_Print("}");
}

static VOS_VOID TracePrintAvailableLevels()
{
    VOS_UINT32 ulIdx;

    ATP_Debug_Print("{");
    ulIdx = 0;
    while (ulIdx < (ATP_ARRAY_LEN(m_apcTraceCliLevelMap) - 1))
    {
        ATP_Debug_Print("%s|", m_apcTraceCliLevelMap[ulIdx]);
        ulIdx++;
    }
    if (NULL != m_apcTraceCliLevelMap[ulIdx])
    {
        ATP_Debug_Print("%s", m_apcTraceCliLevelMap[ulIdx]);
    }
    ulIdx++;
    ATP_Debug_Print("}");
}

#ifdef SUPPORT_ATP_DEBUG_CMD
extern VOS_VOID ModularDebugPrintAvailableModules(VOS_BOOL bWithEnd);
#endif

static VOS_VOID TracePrintAvailableModules()
{
#ifdef SUPPORT_ATP_DEBUG_CMD
    ModularDebugPrintAvailableModules(VOS_FALSE);
#endif
    TracePrintRegisteredModules();
    ATP_Debug_Print("all}");
}

static VOS_VOID TraceSetModuleHelpInfo()
{
    ATP_Debug_Print("Usage:"ATP_END_OF_LINE_STR_D"\ttrace set module level."ATP_END_OF_LINE_STR_D);
    ATP_Debug_Print("\t\tAvailable modules: ");
    TracePrintAvailableModules();
    ATP_Debug_Print(ATP_END_OF_LINE_STR_D);
}

static VOS_VOID TraceLevelHelpInfo()
{
    ATP_Debug_Print("Usage:"ATP_END_OF_LINE_STR_D"\ttrace set module level."ATP_END_OF_LINE_STR_D);
    ATP_Debug_Print("\t\tAvailable levels: ");
    TracePrintAvailableLevels();
    ATP_Debug_Print(ATP_END_OF_LINE_STR_D);
}

static VOS_VOID TraceOutputHelpInfo()
{
    ATP_Debug_Print("Usage:"ATP_END_OF_LINE_STR_D"\ttrace output."ATP_END_OF_LINE_STR_D);
    ATP_Debug_Print("\t\tAvailable output: ");
    TracePrintAvailableOutput();
    ATP_Debug_Print(ATP_END_OF_LINE_STR_D);
}

static VOS_UINT32 TraceDebugSetOutput(VOS_UINT32 ulArgc, VOS_CHAR  *acLastPara[])
{
    int  offIndex = 0;

    if (ulArgc < 1)
    {
        TraceOutputHelpInfo();
        return VOS_OK;
    }

    offIndex = ATP_TRACE_GetOutputByString(acLastPara[0]);
    if (-1 == offIndex)
    {
        return VOS_OK;
    }
    ATP_TRACE_SetOutput(offIndex);
    return VOS_OK;
}

static VOS_UINT32 TraceDebugSetLevel(VOS_UINT32 ulArgc, VOS_CHAR  *acLastPara[])
{
    if (ulArgc < 1)
    {
        TraceSetModuleHelpInfo();
        return VOS_OK;
    }
    if (ulArgc < 2)
    {
        TraceLevelHelpInfo();
        return VOS_OK;
    }

    ATP_TRACE_SetPackageLevel(acLastPara[0], ATP_TRACE_GetLevelByString(acLastPara[1]));
    return VOS_OK;
}

static VOS_UINT32 TraceDebugDisplayInfo(VOS_UINT32 ulArgc, VOS_CHAR  *acLastPara[])
{
    TraceDisplayOneItem(g_stMsgCtx.aucAppName, m_pstTraceList, VOS_TRUE);
    return VOS_OK;
}

static VOS_UINT32 TraceDebugHelp(VOS_UINT32 ulArgc, VOS_CHAR  *acLastPara[])
{
    ATP_Debug_Print("help:"ATP_END_OF_LINE_STR_D);

    // For set trace levels
    ATP_Debug_Print("\tset ");
    TracePrintAvailableModules();
    ATP_Debug_Print(" ");
    TracePrintAvailableLevels();
    ATP_Debug_Print(": change trace level of sub modules"ATP_END_OF_LINE_STR_D);

    // For displaying trace level info
    ATP_Debug_Print("\tinfo : display trace levels"ATP_END_OF_LINE_STR_D);
    ATP_Debug_Print("\toutput : set trace ouput target"ATP_END_OF_LINE_STR_D);
    return VOS_OK;
}

#ifdef SUPPORT_ATP_DEBUG_CMD
const ATP_UTIL_Debug_CMD_ST m_astTraceDebugCmds[] = 
{
    {ATP_DEBUG_HELP,        TraceDebugHelp},
    {ATP_DEBUG_INFO,        TraceDebugDisplayInfo},
    {"set",                 TraceDebugSetLevel},
    {"output",              TraceDebugSetOutput},
};
VOS_VOID TraceDebugCmdRegister()
{
    ATP_Debug_RegModCmds("trace", m_astTraceDebugCmds, ATP_ARRAY_LEN(m_astTraceDebugCmds));
}
#endif

#endif

/*
 *  These functions are added for both GPL apps and ATP private apps
 */
#ifdef __BIONIC__
struct mntent *getmntent_r(FILE *fp, struct mntent *mnt, char *buf, int buflen)
{
    char *tokp = NULL, *s;

    do {
        if (!fgets(buf, buflen, fp))
            return NULL;
        tokp = 0;
        s = strtok_r(buf, " \t\n", &tokp);
    } while (!s || *s == '#');

    mnt->mnt_fsname = s;
    mnt->mnt_freq = mnt->mnt_passno = 0;
    if (!(mnt->mnt_dir = strtok_r(NULL, " \t\n", &tokp)))
        return NULL;
    if (!(mnt->mnt_type = strtok_r(NULL, " \t\n", &tokp)))
        return NULL;
    if (!(mnt->mnt_opts = strtok_r(NULL, " \t\n", &tokp)))
        mnt->mnt_opts = "";
    else if ((s = strtok_r(NULL, " \t\n", &tokp)))
    {
        mnt->mnt_freq = atoi(s);
        if ((s = strtok_r(NULL, " \t\n", &tokp)))
            mnt->mnt_passno = atoi(s);
    }

    return mnt;
}

/* override definition in bionic/stubs.c */
struct mntent *getmntent(FILE *fp)
{
    static struct mntent mnt;
    static char buf[256];
    return getmntent_r(fp, &mnt, buf, 256);
}
FILE *setmntent(const char *filename, const char *type)
{
    FILE * fp = NULL;
    fp = fopen(filename,type);
    if(fp != NULL)
    {
        return fp;
    }
    return NULL;
}

int endmntent(FILE *fp)
{
    if(fp != NULL)
    {
        fclose( fp);
    }
    return 0;
}
#endif

