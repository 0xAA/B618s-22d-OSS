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

#ifndef __GLPBASE64_H__
#define __GLPBASE64_H__
#include "atptypes.h"

VOS_INT32 ATP_UTIL_Base64Encode(const VOS_UINT8* pucInput, VOS_INT32 lInputlen, VOS_UINT8** ppucOutput);
VOS_INT32 ATP_UTIL_Base64Decode(const VOS_UINT8* pucInput, VOS_INT32 lInputlen, VOS_UINT8** ppucOutput);

VOS_UINT32 ATP_UTIL_Base64EncodeEx(const VOS_UINT8* pucInput, VOS_UINT32 ulInputlen, VOS_UINT8** ppucOutput, VOS_UINT32 *pulOutputLen);
VOS_UINT32 ATP_UTIL_Base64DecodeEx(const VOS_UINT8* pucInput, VOS_UINT32 ulInputlen, VOS_UINT8** ppucOutput, VOS_UINT32 *pulOutputLen);


#endif

