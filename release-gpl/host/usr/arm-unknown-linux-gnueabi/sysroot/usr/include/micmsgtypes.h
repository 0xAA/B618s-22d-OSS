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

#ifndef __ATP_MIC_MSGTYPES_H__
#define __ATP_MIC_MSGTYPES_H__

#define ATP_CBBID_MIC_NAME                  "mic"
#define ATP_CBBID_MIC_MBC_NAME              "mbc"

enum ATP_MIC_MSGTYPES_EN
{
    ATP_MSG_MIC_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_MIC), // = 0x5000 = 20480
    ATP_MSG_UPDATE_DYN_APP_FD, 	//01
    ATP_MSG_CMS_INIT_OK,		//02
    ATP_MSG_TRACE_VOICE,		//03
    ATP_MSG_EXIT_WHEN_IDLE,		//04
    ATP_MSG_CWMP_SESSION_END,	//05
    ATP_MSG_CWMP_CURRENT_IP,	//06
    ATP_MSG_SEND_OPTION43,		//07
    ATP_MSG_IDLE_CTRL,			//08
    ATP_MSG_DBSAVE,				//09
    ATP_MSG_CFM_LOCK,			//0a
    ATP_MSG_CFM_UNLOCK,			//0b
    ATP_MSG_UPG_LOCK,			//0c
    ATP_MSG_UPG_UNLOCK,			//0d
    ATP_MSG_SYS_REBOOT,			//0e
    ATP_MSG_SYS_RESTORE_DEFAULT,//0f
    ATP_MSG_CFM_GETLOCK,		//10
    ATP_MSG_DBSAVE_SYSREBOOT,	//11
    ATP_MSG_SEND_OPTION17,		//12
    ATP_MSG_CFG_LOCK,			//13
    ATP_MSG_CFG_UNLOCK,			//14
    ATP_MSG_LAN_STATUS_DOWN,	//15
    ATP_MSG_LAN_STATUS_UP,		//16
    ATP_MSG_ATPSYNC_NOTIFY,		//17
    ATP_MSG_ATPSYNC_WAIT,		//18
    ATP_MSG_ATPSYNC_POST,		//19
    ATP_MSG_ATPSYNC_DELETE,		//1a
    ATP_MSG_ATPSYNC_DISPLAY,	//1b
    ATP_MSG_MIC_MBC_HEARTBEAT,      // Processed by mic sdk only
    ATP_MSG_MIC_MBC_MASTER_START,   // Send from cms to mic for start MBC master
    ATP_MSG_MIC_MBC_SLAVE_START,    // Send from cms to mic for start MBC slave registration
    ATP_MSG_MIC_MBC_SLAVE_ENDIAN,   // Get slave board if need endian swap
    ATP_MSG_MIC_MBC_REBOOT,         // Send from mic to mbc for restart lte module
    ATP_MSG_MIC_MBC_RESTORE,        // Send from mic to mbc for restore lte module
    ATP_MSG_WLAN_STATUS_DOWN,
    ATP_MSG_DEBUG_HOT_PATCH_GET,
    ATP_MSG_DEBUG_HOT_PATCH_SET,
    ATP_MSG_EXPORT_FLASH_CFG,       // Export configuration file in Flash
    ATP_MSG_EXPORT_CURRENT_CFG,     // Export current configuration file
    ATP_MSG_IMPORT_CFG_FILE,        // Import configuration file
    ATP_MSG_CHECK_CFG_FILE,         // Check configuration file
    ATP_MSG_CLEAN_CFG_FILE,         // Clean configuration file in Flash
    ATP_MSG_APPSAVE,
    ATP_MSG_DBSAVESYNC,             // DBSave Sync
    ATP_MSG_CWMP_CERT_SAVE,         // CWMP Cert to Flash.
    ATP_MSG_SEC_GET_SSL_CERT,       // ����ssl֤����Ϣ
    ATP_MSG_SEC_ENCRYPT_DATA,       // ��������
    ATP_MSG_SEC_DECRYPT_DATA,       // ��������
    ATP_MSG_SEC_GET_PUBKEY,         // ��ȡ��Կ
    ATP_MSG_EUAP_RESTRORE,
    ATP_MSG_MICCMS_SUBDEV_REGED,
    ATP_MSG_DEL_APPDATA,
    ATP_MSG_MEMINFO_GET,
    ATP_MSG_MIC_UPDATE_CFGTOOL,     // Update current config tool
    ATP_MSG_BRCM_CWMP,	//Femto��ͨϵͳ����cwmp �ڵ������Ϣ
    ATP_MSG_MIC_CHECK_WEBAUTH_SIGN, // mic check webauth sign, ��ǰԶ�̹����ȡ������Ҳ���ô���Ϣ
    ATP_MSG_SEC_GET_ENCRYPT_KEY,         // ͨ��domain id ��ȡkey bigģʽ����ͨģʽ����
    ATP_MSG_SEC_GET_DECRYPT_KEY,     // ͨ��domain id ��ȡ��ͨģʽkey
    ATP_MSG_SEC_GET_DECRYPTBIG_KEY,  // ͨ��domain id ��ȡkey bigģʽkey
    ATP_MSG_SEC_ENCRYPT_FILE,         // ��Ϣ��mic�����ļ����м���
    ATP_MSG_SEC_DECRYPT_FILE,         // ��Ϣ��mic�����ļ����н���
    ATP_MSG_SEC_PROTECT,         // ��Ϣ��mic�������ݵ������
    ATP_MSG_SEC_VERIFY_PROTECT,// ��Ϣ��mic�������ݵ������У��
    ATP_MSG_DBSAVE_TOAPP,  // DB���ݱ��浽appdata�ڵ�
    ATP_MSG_DBSAVE_TOAPPSYNC,// DB���ݱ��浽appdata�ڵ� ͬ����Ϣ
    ATP_MSG_MUPG_PATCH_GET, //��ȡͨ��MUPG�����Ȳ�����״̬
    ATP_MSG_MUPG_PATCH_SET, //����ͨ��MUPG�����Ȳ�����״̬
    ATP_MSG_SEC_GEN_NEWPUBKEY,//�����µ�Rsa key
    ATP_MSG_UPLOADLOG_NORMAL, //�ϴ�log��������
    ATP_MSG_UPLOADLOG_TIMER, //��ʱ�ϴ�log��������
    ATP_MSG_INTED_APP_INITED, //�ڲ����������ѳ�ʼ��
    ATP_MSG_MIC_OPEN_TELNET,  //����telnet
    ATP_MSG_CERT_SAVE,          //֤�鱣����Ϣ
};


typedef struct tagCWMP_SESSION_END_MSG_ST
{
    VOS_UINT32      ulErrCode;
    VOS_CHAR        acLocalAddr[64];
    VOS_CHAR        acRemoteHost[256];
    VOS_CHAR        acRemoteAddr[64];
    VOS_UINT32      ulRemotePort;
} CWMP_SESSION_END_MSG_ST;

//! ATP_MSG_SEC_GET_SSL_CERT
typedef struct tagGET_SSL_CERT_MSG_ST
{
    VOS_UINT32      ulSSLID;
    VOS_UINT32      ulKeyID;
    VOS_CHAR        acCAPath[256];
    VOS_CHAR        acPubCertPath[256];
    VOS_CHAR        acKeyPath[256];
    VOS_UINT32      ulKeyPwdLen;
    VOS_UINT8       aucKeyPwd[64];
} SEC_SSL_CERT_MSG_ST;



#define MAX_HEAETBEAT_TIME      (600)   /* dialup ���������240s */
#define INETD_APP_TIME          (60)    /* ��̬�������̳�ʱʱ�� ������ʱ��Ҫ���ڶ�̬�����˳�ʱ�������̲����˳�*/
#define HEART_INTERVAL          (60)

typedef struct tagATP_MIC_MSGREGISTER
{
    VOS_UINT32 ulSupportHeartbeat;  /* �Ƿ�֧������ */
    VOS_UINT32 ulHeartbeatTimeout;  /* ������ʱʱ�� */
}ATP_MIC_MSGREGISTER;

enum ATP_MICCORE_MSGTYPES_EN
{
    ATP_MSG_MICCORE_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_MICCORE), // = 0x700 = 1792
    ATP_MSG_REGISTER,
    ATP_MSG_SUBSCRIBE_EVT,
    ATP_MSG_UNSUBSCRIBE_EVT,
    ATP_MSG_TIMED_LAUNCH,
    ATP_MSG_GET_NUM_OF_PROC,
    ATP_MSG_SAFE_EXIT_PROCESS,
    ATP_MSG_SYSGUARD_HEARTBEAT_REQUEST,
    ATP_MSG_SYSGUARD_HEARTBEAT_RESPONSE,
    ATP_MSG_SYSGUARD_STOP,
    ATP_MSG_IS_FACTORY_MODE,        // �Ƿ��ǹ���ģʽ
    ATP_MSG_PROCD_START,        // procd start launch process
    ATP_MSG_PROCD_STOP,         // procd stop process
} ;

#define ATP_CBBID_CMS_NAME                  "cms"

enum ATP_CMS_MSGTYPES_EN
{
    ATP_MSG_CMS_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_CMS), // = 0x9800 = 38912
    ATP_MSG_CONFIG_SET,
    ATP_MSG_CONFIG_GET,
    ATP_MSG_CONFIG_ADD,
    ATP_MSG_CONFIG_DEL,
    ATP_MSG_CONFIG_GET_INST,
    ATP_MSG_CMS_GMSG,

    ATP_MSG_CMS_REALTIME_SIGNAL,
    ATP_MSG_CMS_MODULE_LOAD,
    ATP_MSG_CMS_MODULE_UNLOAD,
    ATP_MSG_CMS_MODULE_DISPLAY,
    ATP_MSG_CMS_SECKEY_GET,        /*get ssl private key passwprd*/
    ATP_MSG_CMS_EQUIP_GET,        /*get equip mode */

    ATP_MSG_CMS_GETAPPSCOUNT,//38924
    ATP_MSG_CMS_GETAPPSLIST,
    ATP_MSG_CMS_GETAPPICON,
    ATP_MSG_CMS_GETAPPSTATUS,
    ATP_MSG_CMS_SETAPPACTION,
    ATP_MSG_CMS_GETAPPINSTALLSTATUS,
} ;

typedef struct tagATP_APPSLIST_PARAM_ST
{
    VOS_INT32	lStartIndex;
    VOS_UINT32  ulGetSize;
}ATP_APPSLIST_PARAM_ST;

typedef struct tagATP_APPACTION_PARAM_ST
{
    VOS_CHAR	acAppAction[32];
    VOS_CHAR	acAppPackageName[256];
    VOS_CHAR	acAppUrl[256];
}ATP_APPACTION_PARAM_ST;

#endif // End of __ATP_MIC_MSGTYPES_H__
