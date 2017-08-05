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
 
 #ifndef __ATP_DHCPC_MSGTYPES_H__
#define __ATP_DHCPC_MSGTYPES_H__

#define ATP_CBBID_DHCPC_NAME "dhcpc"

//Don't change these macros unthinkingly
#define DHCPC_STATUS_INIT_SELECTING 0
#define DHCPC_STATUS_REQUESTING 1
#define DHCPC_STATUS_BOUND      2
#define DHCPC_STATUS_RENEWING   3
#define DHCPC_STATUS_REBINDING  4
#define DHCPC_STATUS_INIT_REBOOT    5
#define DHCPC_STATUS_RENEW_REQUESTED 6
#define DHCPC_STATUS_RELEASED   7

#define ATP_DHCPC_MAX_IFC_LEN 32
#define DHCPC_IFC_LEN (64)
#define DHCPC_OPTION_43_LEN 256
#define DHCPC_OPTION_LEN  256
#define DHCPC_SENT_OPTION_NUM_MAX  16
#define DHCPC_REQ_OPTION_NUM_MAX  32
#define DHCPC_OPTION_TAG_MIN      1
#define DHCPC_OPTION_TAG_MAX      254

typedef struct tagATP_DHCPC_STATUSCHG_MSG_ST
{
    VOS_UINT32 ulStatus;
    VOS_CHAR   acIntfName[DHCPC_IFC_LEN];
}ATP_DHCPC_STATUSCHG_MSG_ST;

typedef struct tagATP_DHCPC_OPTION_ST
{
    VOS_BOOL          bEnable;
    VOS_UINT32        ulInstance;
    VOS_UINT32        ulOrder;
    VOS_UINT32        tag;
    VOS_UINT32        len;
    VOS_UINT8         value[DHCPC_OPTION_LEN];
}ATP_DHCPC_OPTION_ST;

enum ATP_DHCPCLIENT_OPTION_TYPE_EN
{
    ATP_DHCPCLIENT_SENTOPTION,
    ATP_DHCPCLIENT_REQOPTION
};

typedef struct tagATP_DHCPC_OPTION_MSG_ST
{
    VOS_CHAR   acIntfName[DHCPC_IFC_LEN];
    ATP_DHCPC_OPTION_ST stOptionList[DHCPC_REQ_OPTION_NUM_MAX]; 
}ATP_DHCPC_OPTION_MSG_ST;

typedef struct tagATP_DHCPC_RENEW_MSG_ST
{
    VOS_CHAR   acIntfName[DHCPC_IFC_LEN];
    VOS_UINT32 leaseTime; 
}ATP_DHCPC_RENEW_MSG_ST;

enum ATP_DHCPC_MSGTYPES_EN
{
    ATP_MSG_DHCPC_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_DHCPC), // = 0x2F00 = 12032
    ATP_MSG_DHCPC_CWMPRENEW,
    ATP_MSG_DHCPC_OPTIONS_COME,
    ATP_MSG_DHCPC_STATUS_CHANGE,
    ATP_MSG_DHCPC_SENTOPTION_UPDATE,
    ATP_MSG_DHCPC_REQOPTION_UPDATE,
    ATP_MSG_DHCPC_RENEW_UPDATE,
    ATP_MSG_DHCPC_STOP,
} ;
typedef struct tagATP_DHCPC_OPTION43_MSG_ST
{
    VOS_CHAR acIfc[ATP_DHCPC_MAX_IFC_LEN];
    VOS_CHAR acUrl[DHCPC_OPTION_43_LEN];
    VOS_UINT32 ulUrlLen;
} ATP_DHCPC_OPTION43_MSG_ST;

typedef struct tagATP_DHCPC_OPTION121_DEFAULT_GW_MSG_ST
{
    VOS_CHAR acGw[ATP_DHCPC_MAX_IFC_LEN];
    VOS_UINT32 ulLen;
} ATP_DHCPC_OPTION121_DFT_GW_MSG_ST;
#endif // End of __ATP_DHCPC_MSGTYPES_H__

