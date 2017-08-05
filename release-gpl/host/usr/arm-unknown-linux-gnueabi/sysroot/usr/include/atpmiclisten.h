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
 

#ifndef __ATP_MIC_LISTEN_H__
#define __ATP_MIC_LISTEN_H__

/********************** Include Files ***************************************/
#include "atptypes.h"



/*function macro*/
#if defined(__cplusplus)
extern "C" {
#endif



VOS_UINT32 ATP_UTIL_MIC_ResetBackupAppFds( VOS_UINT32 * pulFdsArray, const VOS_UINT32 ulFdsArrSize );



VOS_UINT32 ATP_UTIL_MIC_AddBackupAppFds( VOS_UINT32 * pulFdsArray, const VOS_UINT32 ulFdsArrSize, const VOS_UINT32 ulAddFd );



VOS_UINT32 ATP_UTIL_MIC_CloseBackupAppFdsReadableConnection( const VOS_UINT32 * pulFdsArray, const VOS_UINT32 ulFdsArrSize );



#if defined(__cplusplus)
}
#endif

#endif

