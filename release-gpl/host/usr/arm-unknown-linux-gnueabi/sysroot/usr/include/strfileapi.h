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

#ifndef __ATP_STRFILE_API_H__
#define __ATP_STRFILE_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

/*
 *  FreeList结构声明，结构的具体信息隐藏在C文件中，只能通过接口访问FreeList
 */
struct tagATP_UTIL_STRFILE_ST;
typedef struct tagATP_UTIL_STRFILE_ST ATP_UTIL_STRFILE_ST;


ATP_UTIL_STRFILE_ST *ATP_UTIL_StrFileOpen(VOS_INT32 lInitSize);


ATP_UTIL_STRFILE_ST *ATP_UTIL_StrFileOpenEx(VOS_CHAR *pcInitBuf);


ATP_UTIL_STRFILE_ST *ATP_UTIL_StrFileFOpen(const VOS_CHAR *pcFileName);

ATP_UTIL_STRFILE_ST *ATP_UTIL_StrFileFMmapOpen(const VOS_CHAR *pcFileName);


VOS_VOID ATP_UTIL_StrFileClose(ATP_UTIL_STRFILE_ST *pstFile);


VOS_BOOL ATP_UTIL_StrFileReSize(ATP_UTIL_STRFILE_ST *pstFile,
                                      VOS_INT32           lNewSize);


VOS_BOOL ATP_UTIL_StrFileWriteBin(ATP_UTIL_STRFILE_ST       *pstFile,
                                       const VOS_CHAR       *pcSrc,
                                       VOS_INT32            lLen);


VOS_INT32 ATP_UTIL_StrFileVPrintf(ATP_UTIL_STRFILE_ST *pstFile,
                                     VOS_CHAR *fmt, va_list ap);


VOS_INT32 ATP_UTIL_StrFilePrintf(ATP_UTIL_STRFILE_ST *pstFile,
                                     VOS_CHAR *fmt, ...);


VOS_INT32 ATP_UTIL_StrFileTell(const ATP_UTIL_STRFILE_ST *pstFile);


VOS_CHAR* ATP_UTIL_StrFileBuffer(const ATP_UTIL_STRFILE_ST *pstFile);


VOS_BOOL ATP_UTIL_StrFileSetLen(ATP_UTIL_STRFILE_ST         *pstFile,
                                      VOS_INT32             lNewLen);


VOS_VOID ATP_UTIL_StrFileFlush(ATP_UTIL_STRFILE_ST *pstFile);


VOS_UINT32 ATP_UTIL_StrFileToBuf(const VOS_CHAR *pcFileName,
                                       VOS_CHAR** ppcBuf);

#ifdef __cplusplus
}
#endif

#endif

