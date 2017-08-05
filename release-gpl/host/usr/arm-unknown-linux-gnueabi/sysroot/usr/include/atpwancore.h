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





#ifndef __ATP_WANCORE_H__
#define __ATP_WANCORE_H__

#include "atputil.h"

typedef enum tagATP_WANCORE_MSGTYPES_EN
{
    ATP_MSG_WANCORE_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_WANCORE), // = 0x11600 = 71168
    ATP_MSG_WANCORE_WANCONN_CHANGE,
    ATP_MSG_WANCORE_WANCONN_RECEIVE_RESPOND,
    ATP_MSG_GET_INTF_TYPE,
    ATP_MSG_WAN_DIAL_FAIL,
    ATP_MSG_WAN_DIAL_CFG_CHANGE,
    ATP_MSG_WAN_3GPP_ONDEMAND_CONNECT,
    ATP_MSG_WAN_3GPP_ONDEMAND_DISCONN,
    ATP_MSG_WAN_GET_WIFI_WAN_INFO,
    ATP_MSG_WAN_3GPP_MANUAL_CONNECT,
    ATP_MSG_WAN_3GPP_MANUAL_DISCONN,
    ATP_MSG_ONDEMAND_READY_ROUTE,
    ATP_MSG_IPV6_ONDEMAND_PREPARED,
    ATP_MSG_WAN_3GPP_STATUS_NOTIFY, /*apn共享*/

    /*软银定制拨上号无服务重定向*/
    ATP_MSG_WAN_NO_SERVICE_REDIRECT_INFO,

    ATP_MSG_WAN_3GPP_DISCONNECT_FINISH,
    /*预检预修MSG 消息ID*/
    ATP_MSG_WAN_ONLINE_CHECK_DIALUP, 
    ATP_MSG_DEVICE_FAST_OFF, /*假关机关机事件*/
    ATP_MSG_DEVICE_FAST_ON,  /*假关机开机事件*/
    ATP_MSG_WAN_CFG_LEARN,   /*从LAN侧学习PPPOE 的mac和用户名密码*/
    ATP_MSG_WAN_MPPE_SWITCH,   /*MPPE协商状态,即server是否期望协商MPPE*/
    ATP_MSG_WAN_CFG_LEARN_TYPE,  /* 从LAN侧学习的探测类型 */
    ATP_MSG_WAN_DISCOVER_LEARN_MAC,  /* 从LAN侧学习的新设备mac地址 */
    ATP_MSG_PPTP_GETUSERINFO, /*PPTP 进程发送请求cms消息*/

} ATP_WANCORE_MSGTYPES_EN;

/*!< 连接触发，需要与DHCP/PPPOE客户保持一致 */
typedef enum
{
    /*!< 等待 */
    WAN_TRIGGER_IDLE = 0,
    /*!< 断线 */
    WAN_TRIGGER_DISCONNECTING = 1,
    /*!< 手动 */
    WAN_TRIGGER_MANUAL = 2,
    /*!< 自动 */
    WAN_TRIGGER_ALWAYSON = 3,
    /*!< 按需拨号 */
    WAN_TRIGGER_ONDEMAND = 4, 
}WAN_TRIGGER_EN;


/*!< WAN连接状态 */
typedef enum
{
    /*!< 未初始化 */
    ATP_WAN_STATUS_UNCONFIGURED,
    /*!< 正在连接 */
    ATP_WAN_STATUS_CONNECTING,
    /*!< 正在认证 */
    ATP_WAN_STATUS_AUTHENTICATING,
    /*!< 已连接 */
    ATP_WAN_STATUS_CONNECTED,
    /*!< 未连接 */
    ATP_WAN_STATUS_PENDING,
    /*!< 正在断开 */
    ATP_WAN_STATUS_DISCONNECTING,
    /*!< 已断开 */
    ATP_WAN_STATUS_DISCONNECTED, 
}ATP_WAN_STATUS_EN;

/* WAN DEV 上行接口类型 */
typedef enum 
{
    ATP_WAN_TYPE_NONE = 0,
    /* XDSL上行 */
    ATP_WAN_TYPE_DSL = 1,
    /* 以太网上行 */
    ATP_WAN_TYPE_ETH = 2,
    /* POTS上行 */
    ATP_WAN_TYPE_POTS = 4,
    /* UMTS上行 */
    ATP_WAN_TYPE_UMTS = 8,
    /* VDSL 上行*/
    ATP_WAN_TYPE_VDSL = 16,
    /* WLAN上行 */
    ATP_WAN_TYPE_WIFI = 32,
    ATP_WAN_TYPE_WLAN = 32,

    ATP_WAN_TYPE_LAN = 64,
	/* G.FAST 上行*/
	ATP_WAN_TYPE_G_FAST = 128,
}ATP_WAN_TYPE_EN;

#define ATP_WAN_TYPE_WIRE (ATP_WAN_TYPE_ETH + ATP_WAN_TYPE_DSL + ATP_WAN_TYPE_VDSL)

/*拨号组件状态变化给WAN发消息的结构体*/
typedef struct tagATP_WAN_STATUS_CHANGE_MSG_ST
{
    /*WAN路径*/
    VOS_CHAR acPath[ATP_BUFFER_128];
    /*接口名称*/
    VOS_CHAR acInterface[ATP_BUFFER_16];
    /*IPv4 status*/
    VOS_UINT32 ulStatus;
    /*IPv6 status*/
    VOS_UINT32 ulStatus6;
}ATP_WAN_STATUS_CHANGE_MSG_ST;


typedef enum 
{
    ATP_WAN_CFG_LEARN_TYPE_LEARNING = 0,
    
    ATP_WAN_CFG_LEARN_TYPE_SUCCESS = 1,
    
    ATP_WAN_CFG_LEARN_TYPE_FAIL = 2
}ATP_WAN_CFG_LEARN_TYPE_EN;


// 返回学习返回类型结果
typedef enum 
{
	ATP_WAN_LEARN_TYPE_TRYING = 0,   // 正在探测状态
    ATP_WAN_LEARN_TYPE_PPP = 1,
    ATP_WAN_LEARN_TYPE_DHCP = 2,
    ATP_WAN_LEARN_TYPE_FAIL = 3		// 没有探测到类型 都失败的场景
}ATP_WAN_LEARN_TYPE_EN;
//!\brief WAN参数从LAN侧设备学习结构
/*!
* @acPAPUser:PPP用户名
* @acPAPPasswd:PPP密码
* @acWanMac:WAN MAC
* @bCfgLearnSucess:学习是否成功
*/
typedef struct tagATP_WAN_CFG_LEARN_MSG_ST
{
	/*PPP 用户名*/
	VOS_CHAR acPAPUser[ATP_STRING_LEN_64];
	/*PPP 密码*/
	VOS_CHAR acPAPPasswd[ATP_STRING_LEN_64];
	/*WAN MAC */
	VOS_CHAR acWanMac[ATP_UTIL_MAC_LENGTH];
	/* 是否学到所需要的信息 */
	ATP_WAN_CFG_LEARN_TYPE_EN ulCfgLearnSucessType;
	ATP_WAN_LEARN_TYPE_EN ulCfgLearnWanType;
}ATP_WAN_CFG_LEARN_MSG_ST;

#endif
