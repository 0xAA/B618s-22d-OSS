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
    ATP_MSG_WAN_3GPP_STATUS_NOTIFY, /*apn����*/

    /*�������Ʋ��Ϻ��޷����ض���*/
    ATP_MSG_WAN_NO_SERVICE_REDIRECT_INFO,

    ATP_MSG_WAN_3GPP_DISCONNECT_FINISH,
    /*Ԥ��Ԥ��MSG ��ϢID*/
    ATP_MSG_WAN_ONLINE_CHECK_DIALUP, 
    ATP_MSG_DEVICE_FAST_OFF, /*�ٹػ��ػ��¼�*/
    ATP_MSG_DEVICE_FAST_ON,  /*�ٹػ������¼�*/
    ATP_MSG_WAN_CFG_LEARN,   /*��LAN��ѧϰPPPOE ��mac���û�������*/
    ATP_MSG_WAN_MPPE_SWITCH,   /*MPPEЭ��״̬,��server�Ƿ�����Э��MPPE*/
    ATP_MSG_WAN_CFG_LEARN_TYPE,  /* ��LAN��ѧϰ��̽������ */
    ATP_MSG_WAN_DISCOVER_LEARN_MAC,  /* ��LAN��ѧϰ�����豸mac��ַ */
    ATP_MSG_PPTP_GETUSERINFO, /*PPTP ���̷�������cms��Ϣ*/

} ATP_WANCORE_MSGTYPES_EN;

/*!< ���Ӵ�������Ҫ��DHCP/PPPOE�ͻ�����һ�� */
typedef enum
{
    /*!< �ȴ� */
    WAN_TRIGGER_IDLE = 0,
    /*!< ���� */
    WAN_TRIGGER_DISCONNECTING = 1,
    /*!< �ֶ� */
    WAN_TRIGGER_MANUAL = 2,
    /*!< �Զ� */
    WAN_TRIGGER_ALWAYSON = 3,
    /*!< ���貦�� */
    WAN_TRIGGER_ONDEMAND = 4, 
}WAN_TRIGGER_EN;


/*!< WAN����״̬ */
typedef enum
{
    /*!< δ��ʼ�� */
    ATP_WAN_STATUS_UNCONFIGURED,
    /*!< �������� */
    ATP_WAN_STATUS_CONNECTING,
    /*!< ������֤ */
    ATP_WAN_STATUS_AUTHENTICATING,
    /*!< ������ */
    ATP_WAN_STATUS_CONNECTED,
    /*!< δ���� */
    ATP_WAN_STATUS_PENDING,
    /*!< ���ڶϿ� */
    ATP_WAN_STATUS_DISCONNECTING,
    /*!< �ѶϿ� */
    ATP_WAN_STATUS_DISCONNECTED, 
}ATP_WAN_STATUS_EN;

/* WAN DEV ���нӿ����� */
typedef enum 
{
    ATP_WAN_TYPE_NONE = 0,
    /* XDSL���� */
    ATP_WAN_TYPE_DSL = 1,
    /* ��̫������ */
    ATP_WAN_TYPE_ETH = 2,
    /* POTS���� */
    ATP_WAN_TYPE_POTS = 4,
    /* UMTS���� */
    ATP_WAN_TYPE_UMTS = 8,
    /* VDSL ����*/
    ATP_WAN_TYPE_VDSL = 16,
    /* WLAN���� */
    ATP_WAN_TYPE_WIFI = 32,
    ATP_WAN_TYPE_WLAN = 32,

    ATP_WAN_TYPE_LAN = 64,
	/* G.FAST ����*/
	ATP_WAN_TYPE_G_FAST = 128,
}ATP_WAN_TYPE_EN;

#define ATP_WAN_TYPE_WIRE (ATP_WAN_TYPE_ETH + ATP_WAN_TYPE_DSL + ATP_WAN_TYPE_VDSL)

/*�������״̬�仯��WAN����Ϣ�Ľṹ��*/
typedef struct tagATP_WAN_STATUS_CHANGE_MSG_ST
{
    /*WAN·��*/
    VOS_CHAR acPath[ATP_BUFFER_128];
    /*�ӿ�����*/
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


// ����ѧϰ�������ͽ��
typedef enum 
{
	ATP_WAN_LEARN_TYPE_TRYING = 0,   // ����̽��״̬
    ATP_WAN_LEARN_TYPE_PPP = 1,
    ATP_WAN_LEARN_TYPE_DHCP = 2,
    ATP_WAN_LEARN_TYPE_FAIL = 3		// û��̽�⵽���� ��ʧ�ܵĳ���
}ATP_WAN_LEARN_TYPE_EN;
//!\brief WAN������LAN���豸ѧϰ�ṹ
/*!
* @acPAPUser:PPP�û���
* @acPAPPasswd:PPP����
* @acWanMac:WAN MAC
* @bCfgLearnSucess:ѧϰ�Ƿ�ɹ�
*/
typedef struct tagATP_WAN_CFG_LEARN_MSG_ST
{
	/*PPP �û���*/
	VOS_CHAR acPAPUser[ATP_STRING_LEN_64];
	/*PPP ����*/
	VOS_CHAR acPAPPasswd[ATP_STRING_LEN_64];
	/*WAN MAC */
	VOS_CHAR acWanMac[ATP_UTIL_MAC_LENGTH];
	/* �Ƿ�ѧ������Ҫ����Ϣ */
	ATP_WAN_CFG_LEARN_TYPE_EN ulCfgLearnSucessType;
	ATP_WAN_LEARN_TYPE_EN ulCfgLearnWanType;
}ATP_WAN_CFG_LEARN_MSG_ST;

#endif
