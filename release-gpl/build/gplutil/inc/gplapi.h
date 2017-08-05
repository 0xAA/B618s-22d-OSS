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
 
 
#ifndef __ATP_USBSTORAGECMS_MSGTYPES_H__
#define __ATP_USBSTORAGECMS_MSGTYPES_H__

#define ATP_CBBID_USBSTORAGECMS_NAME "usbstoragecms"
#define ATP_CBBID_BFTPD_NAME                 "bftpd"
#define ATP_CBBID_SMBD_NAME                 "smbd"

enum ATP_USBSTORAGECMS_MSGTYPES_EN
{
    ATP_MSG_USBSTORAGECMS_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_GPLUTIL),

    ATP_MSG_CMS_LOGINCTL_CHECK,
    ATP_MSG_CMS_LOGINCTL_LOGOUT,
    ATP_MSG_CMS_LOGINCTL_ALLOWWAN,
#ifdef SUPPORT_ATP_FTP_ACCESS_CONTROL
    ATP_MSG_CMS_LOGINCTL_ALLOWFTPTYPE,
#endif
    ATP_MSG_CMS_MODIFYBFTPDUSERPID_FILE,
} ;
#endif
