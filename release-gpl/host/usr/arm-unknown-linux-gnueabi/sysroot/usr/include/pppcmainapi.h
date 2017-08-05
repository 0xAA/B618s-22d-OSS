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


/* ������ */
typedef enum
{
    ATP_PPPC_OK = 0,
    /* ����PPPC��������ʼֵ */
    ATP_ERR_PPPC_START = 0x0820,
    /* ����У����� */
    ATP_ERR_PPPC_CHECK_FAILED,
    /* �����ļ����� */
    ATP_ERR_PPPC_CONFIG_FAILED,
    /* ���������� */
    ATP_ERR_PPPC_ALREADY_EXIST,
    /* ���̲����� */
    ATP_ERR_PPPC_NO_EXIST,
}ATP_ERR_PPPC_EN;

/* ���Ӵ�������Ҫ��WANģ�鱣��һ�� */
typedef enum
{
    /* �ȴ� */
    ATP_PPPC_TRIGGER_IDLE = 0,
    /* ���� */
    ATP_PPPC_TRIGGER_DISCONNECTING = 1,
    /* �ֶ� */
    ATP_PPPC_TRIGGER_MANUAL = 2,
    /* �Զ� */
    ATP_PPPC_TRIGGER_ALWAYSON = 3,
    /* ���貦�� */
    ATP_PPPC_TRIGGER_ONDEMAND = 4,
    /* ���ֵ */
    ATP_PPPC_TRIGGER_MAX
}ATP_PPPC_TRIGGER_EN;

/* PPPC����״̬ */
typedef enum
{
    /* δ��ʼ�� */
    ATP_PPPC_STATUS_UNCONFIGURED,
    /* �������� */
    ATP_PPPC_STATUS_CONNECTING,
    /* ������֤ */
    ATP_PPPC_STATUS_AUTHENTICATING,
    /* ������ */
    ATP_PPPC_STATUS_CONNECTED,
    /* δ���� */
    ATP_PPPC_STATUS_PENDING,
    /* ���ڶϿ� */
    ATP_PPPC_STATUS_DISCONNECTING,
    /* �ѶϿ� */
    ATP_PPPC_STATUS_DISCONNECTED 
}ATP_PPPC_STATUS_EN;


#ifdef SUPPORT_ATP_IPV6
/* IPV6��ַ���÷�ʽ */
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

/* IPV6��ַ����ѡ�� */
typedef enum
{
    /* IANA + IAPD */
    ATP_PPPC_IPV6_ADDR_OPTION_BOTH,
    /* IANA */
    ATP_PPPC_IPV6_ADDR_OPTION_IANA,
    /* IAPD */
    ATP_PPPC_IPV6_ADDR_OPTION_IAPD,
    /* ����Ӧ���ݲ�֧�� */
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
    /*PPTPģʽpppc���̷�����Ϣ*/
    ATP_MSG_PPTP_ESTABLISED,
#endif
} ;

#endif // End of __ATP__MSGTYPES_H__

