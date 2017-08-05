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
 
 #ifndef __ATP__PPPCMSGTYPES_H__
#define __ATP__PPPCMSGTYPES_H__

#define ATP_CBBID_PPPC_NAME "pppc"

#define ATP_PPP_FIRST_DIAL_FILE "var/wan/%s/firstdial"


/* 错误码 */
typedef enum
{
    ATP_PPPC_OK = 0,
    /* 定义PPPC错误码起始值 */
    ATP_ERR_PPPC_START = 0x0820,
    /* 参数校验错误 */
    ATP_ERR_PPPC_CHECK_FAILED,
    /* 配置文件错误 */
    ATP_ERR_PPPC_CONFIG_FAILED,
    /* 进程已启动 */
    ATP_ERR_PPPC_ALREADY_EXIST,
    /* 进程不存在 */
    ATP_ERR_PPPC_NO_EXIST,
}ATP_ERR_PPPC_EN;

/* 连接触发，需要与WAN模块保持一致 */
typedef enum
{
    /* 等待 */
    ATP_PPPC_TRIGGER_IDLE = 0,
    /* 断线 */
    ATP_PPPC_TRIGGER_DISCONNECTING = 1,
    /* 手动 */
    ATP_PPPC_TRIGGER_MANUAL = 2,
    /* 自动 */
    ATP_PPPC_TRIGGER_ALWAYSON = 3,
    /* 按需拨号 */
    ATP_PPPC_TRIGGER_ONDEMAND = 4,
    /* 最大值 */
    ATP_PPPC_TRIGGER_MAX
}ATP_PPPC_TRIGGER_EN;

/* PPPC连接状态 */
typedef enum
{
    /* 未初始化 */
    ATP_PPPC_STATUS_UNCONFIGURED,
    /* 正在连接 */
    ATP_PPPC_STATUS_CONNECTING,
    /* 正在认证 */
    ATP_PPPC_STATUS_AUTHENTICATING,
    /* 已连接 */
    ATP_PPPC_STATUS_CONNECTED,
    /* 未连接 */
    ATP_PPPC_STATUS_PENDING,
    /* 正在断开 */
    ATP_PPPC_STATUS_DISCONNECTING,
    /* 已断开 */
    ATP_PPPC_STATUS_DISCONNECTED 
}ATP_PPPC_STATUS_EN;


#ifdef SUPPORT_ATP_IPV6
/* IPV6地址配置方式 */
typedef enum
{
    /* Disable */
    ATP_PPPC_IPV6_ADDR_TYPE_DISABLE,
    /* SLAAC */
    ATP_PPPC_IPV6_ADDR_TYPE_SLAAC,
    /* DHCP */
    ATP_PPPC_IPV6_ADDR_TYPE_DHCP,
    /* Static */
    ATP_PPPC_IPV6_ADDR_TYPE_STATIC,
}ATP_PPPC_IPV6_ADDR_TYPE_EN;

/* IPV6地址请求选项 */
typedef enum
{
    /* IANA + IAPD */
    ATP_PPPC_IPV6_ADDR_OPTION_BOTH,
    /* IANA */
    ATP_PPPC_IPV6_ADDR_OPTION_IANA,
    /* IAPD */
    ATP_PPPC_IPV6_ADDR_OPTION_IAPD,
    /* 自适应，暂不支持 */
    ATP_PPPC_IPV6_ADDR_OPTION_AUTO,
}ATP_PPPC_IPV6_ADDR_OPTION_EN;
#endif

#define PPPC_IFC_LEN (64)
typedef struct tagATP_PPPC_STATUSCHG_MSG_ST
{
    VOS_UINT32 ulStatus;
    VOS_CHAR   acIntfName[PPPC_IFC_LEN];
}ATP_PPPC_STATUSCHG_MSG_ST;

enum ATP_MSGTYPES_EN
{
    ATP_MSG_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_PPPC),
    ATP_MSG_START_DHCP6C_PRO,
    ATP_MSG_PPPC_STATUS_CHANGE,
    ATP_MSG_CMS_CONFIRM_VLAN_INF,
    ATP_MSG_PPPC_VLAN_FORCE_CHANGE,
    ATP_MSG_PPPC_UMTS_DIAL_FAIL,
#ifdef SUPPORT_ATP_QMI6
	ATP_MSG_ONDEMAND_IPV6_DNS_TRIGGER,
#endif
    ATP_MSG_PPPC_IPV6CP_CHANGE,
#ifdef SUPPORT_ATP_PPTP_VPN
    /*PPTP模式pppc进程发送消息*/
    ATP_MSG_PPTP_ESTABLISED,
#endif
} ;

#endif // End of __ATP__MSGTYPES_H__

