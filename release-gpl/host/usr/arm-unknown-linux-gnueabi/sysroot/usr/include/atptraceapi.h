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

#ifndef __ATP_TRACE_API_H__
#define __ATP_TRACE_API_H__

#include "atptypes.h"

static inline char *gnu_basename(char *path)    \
{                                               \
    char *base = strrchr(path, '/');            \
    if(NULL != base)                            \
    {                                           \
       return base + 1;                         \
    }                                           \
    else                                        \
    {                                           \
       return path;                             \
    }                                           \
}

#define __FILENAME__    gnu_basename(__FILE__) 

typedef enum _TRACE_LEVEL
{
    TRACE_LV_NONE  = 0,
    TRACE_LV_FATAL = 1,
    TRACE_LV_ERROR = 2,
    TRACE_LV_WARN  = 4,
    TRACE_LV_INFO  = 8,
    TRACE_LV_DEBG  = 16
} TRACE_LEVEL;

typedef enum  tagATP_TRACE_LEVEL_EN
{
    ATP_TRACE_LEVEL_OFF          = TRACE_LV_NONE,
    ATP_TRACE_LEVEL_EMERG        = TRACE_LV_FATAL,
    ATP_TRACE_LEVEL_ALERT        = TRACE_LV_FATAL,
    ATP_TRACE_LEVEL_CRIT         = TRACE_LV_FATAL,
    ATP_TRACE_LEVEL_ERR          = TRACE_LV_ERROR,
    ATP_TRACE_LEVEL_WARNING      = TRACE_LV_WARN,
    ATP_TRACE_LEVEL_NOTICE       = TRACE_LV_INFO,
    ATP_TRACE_LEVEL_INFO         = TRACE_LV_INFO,
    ATP_TRACE_LEVEL_DEBUG        = TRACE_LV_DEBG,
    ATP_TRACE_LEVEL_ALL          = TRACE_LV_DEBG,
} ATP_TRACE_LEVEL_EN;


#define ATP_TRACE_Print(x...)


#define TRACE_Print(ulTraceItemIdx, args...) ATP_TRACE_Print(ATP_MODULE_IDX, ulTraceItemIdx, ##args);


#define ATP_MODULE_NAME_MAX_LEN_D       (12)
typedef struct tagATP_TRACE_CBB_LIST_ST
{
    VOS_VOID            *pstNext;
    VOS_CHAR            acName[ATP_MODULE_NAME_MAX_LEN_D];
    VOS_UINT32          ulLevel;
} ATP_TRACE_CBB_LIST_ST;

typedef struct tagATP_TRACE_GOLBAL_INFO_ST
{
    VOS_UINT32              ulWhere;
    VOS_UINT64              ullSize;
    VOS_VOID*               pvHook;  //不知道具体长度
}ATP_TRACE_GOLBAL_INFO_ST;


VOS_UINT32 ATP_TRACE_SetPackageLevel(const VOS_CHAR *pcName, VOS_UINT32 ulLevel);


VOS_VOID ATP_TRACE_Display();


VOS_BOOL ATP_TRACE_IsModuleEnabled(const VOS_CHAR *pcModule, VOS_UINT32 ulLevel);


VOS_UINT32 ATP_TRACE_RegModule(const VOS_CHAR *pcModuleName);


VOS_INT32 ATP_UTIL_GetCurPid();

// Internal static memory, not thread safe, used only in debug message

VOS_CHAR *ATP_UTIL_GetCurTimeStamp();


VOS_BOOL ATP_TRACE_PrintInfo(const VOS_CHAR *pcFileName, VOS_UINT32 ulLineNo, VOS_BOOL bDbgMode, const VOS_CHAR *pcModule, VOS_UINT32 ulLevel, const VOS_INT8 *fmt, ...) FORMAT_ATTRIBUTE(6, 7);

VOS_BOOL ATP_TRACE_PrintInfoEx(const VOS_CHAR *pcModule, VOS_UINT32 ulLevel, const VOS_INT8 *fmt, ...);

#ifdef SUPPORT_ATP_TRACE_INFO

#ifdef ATP_DEBUG
#define ATP_TRACE(pcModule, ulLevel, args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_TRUE, (pcModule), (ulLevel), ##args)
#define ATP_CMS_TRACE(ulLevel, args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_TRUE, ATP_MACRO_STRINGFY(ATP_MODULE_NAME), (ulLevel), ##args)
#define TRACE_FATAL(module, args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_TRUE, (module), (TRACE_LV_FATAL), ##args)
#define TRACE_ERROR(module, args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_TRUE, (module), (TRACE_LV_ERROR), ##args)
#define TRACE_WARN(module,  args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_TRUE, (module), (TRACE_LV_WARN), ##args)
#define TRACE_INFO(module,  args...)  ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_TRUE, (module), (TRACE_LV_INFO), ##args)
#define TRACE_DEBUG(module,args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_TRUE, (module), (TRACE_LV_DEBG), ##args)

#else
#define ATP_TRACE(pcModule, ulLevel, args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_FALSE, (pcModule), (ulLevel), ##args)
#define ATP_CMS_TRACE(ulLevel, args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_FALSE, ATP_MACRO_STRINGFY(ATP_MODULE_NAME), (ulLevel), ##args)

#define TRACE_FATAL(module, args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_FALSE, (module), (TRACE_LV_FATAL), ##args)
#define TRACE_ERROR(module, args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_FALSE, (module), (TRACE_LV_ERROR), ##args)
#define TRACE_WARN(module,  args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_FALSE, (module), (TRACE_LV_WARN), ##args)
#define TRACE_INFO(module,  args...)  ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_FALSE, (module), (TRACE_LV_INFO), ##args)
#define TRACE_DEBUG(module, args...) ATP_TRACE_PrintInfo(__FILENAME__, __LINE__, VOS_FALSE, (module), (TRACE_LV_DEBG), ##args)
#endif


#else

#define ATP_TRACE(x...)


#define ATP_CMS_TRACE(x...)


#define TRACE_FATAL(module, msg, args...)


#define TRACE_ERROR(module, msg, args...)


#define TRACE_WARN(module, msg,  args...)


#define TRACE_INFO(module, msg,  args...) 


#define TRACE_DEBUG(module, msg, args...)


#define LOG_FATAL(module, msg, args...)    


#define LOG_ERROR(module, msg, args...)  


#define LOG_WARN(module, msg,  args...)  


#define LOG_INFO(module, msg,  args...)   


#define LOG_DEBUG(module, msg, args...) 

#endif


#define ATP_DEBUG_Print_HEADER()    printf("\r\n[%s %s:%d %s:%d]: ", ATP_UTIL_GetCurTimeStamp(), ATP_MACRO_STRINGFY(ATP_MODULE_NAME), ATP_UTIL_GetCurPid(), __FILENAME__, __LINE__);

#ifdef ATP_DEBUG
#define ATP_DEBUG_Print(format, args...) \
        do { \
            ATP_DEBUG_Print_HEADER(); \
            printf(format, ##args); \
            fflush(stdout); \
        } while (0);
#else
#define ATP_DEBUG_Print(x...)
#endif

#endif

