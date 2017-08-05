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

#ifndef __ATP_LOG_MSGTYPES_H__
#define __ATP_LOG_MSGTYPES_H__
#include "atplog.h"

#define ATP_CBBID_LOG_NAME                  "syslog"

#ifdef SUPPORT_ATP_CPE_SBB_AIR3
#define DEVICE_NAME_SBB "SBAir3"
#elif defined(SUPPORT_ATP_CPE_SBB)
#define DEVICE_NAME_SBB "SBAir2"
#endif

enum ATP_LOG_MSGTYPES_EN
{
    ATP_MSG_LOG_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_LOG), // = 0x4B00 = 19200
    ATP_MSG_LOG_ITEM,
    ATP_MSG_LOG_KERNEL_ITEM,
    ATP_MSG_LOG_FILTER,
    ATP_MSG_LOG_RTO,
    ATP_MSG_LOG_TRIGGER,
    ATP_MSG_LOG_FLUSH,
    ATP_MSG_LOG_CLEAR,
    ATP_MSG_LOG_ENABLE,
    ATP_MSG_LOG_CLI_DEBUG,
    ATP_MSG_LOG_CUSTOMIZE_LIMIT,
    ATP_MSG_LOG_UNLIMIT,
    ATP_MSG_LOG_DELETE
} ;
#endif // End of __ATP_LOG_MSGTYPES_H__

