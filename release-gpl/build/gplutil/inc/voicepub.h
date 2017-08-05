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
#ifndef __VOICEPUB_H__
#define __VOICEPUB_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "voice_customer.h"
#include "voicedb.h"

#define VCE_THREAD_STACK_SIZE   1024*1024

/********************    BEGIN: common_define   ********************/
#define VCE_STR_LEN_2               2
#define VCE_STR_LEN_4               4
#define VCE_STR_LEN_8               8
#define VCE_STR_LEN_16              16
#define VCE_STR_LEN_32              32
#define VCE_STR_LEN_64              64
#define VCE_STR_LEN_128             128
#define VCE_STR_LEN_256             256
#define VCE_STR_LEN_512             512
#define VCE_STR_LEN_1K              1024
#define VCE_STR_LEN_2K              (2*1024)
#define VCE_STR_LEN_4K              (4*1024)
#define VCE_STR_LEN_8K              (8*1024)
#define VCE_STR_LEN_16K             (16*1024)
#define VCE_STR_LEN_32K             (32*1024)
#define VCE_STR_LEN_64K             (64*1024)
#define VCE_STR_LEN_128K            (128*1024)
#define VCE_STR_LEN_256K            (256*1024)
#define VCE_STR_LEN_512K            (512*1024)

#define FMC_CLIP_DTMF          1
#define FMC_CLIP_FSKITU        2
#define FMC_CLIP_FSKBELL       3
#define FMC_CLIP_FSKRPAS       4

#define VOIP_FIRST    0
#define CS_FIRST      1
#define VOIP_ONLY     2
#define CS_ONLY       3

#define GSM_2G        3

/********************    END: common_define   ********************/

/*************************  BEGIN: VOICE_LIB  *************************/
#define ATP_VOICE_PID_PATH          "/var/voice"
#define ATP_VOICE_MSGKEY_FLAG       'V'
#define ATP_VOICE_MSG_LEN           256
#define ATP_VOICE_EVENT_LEN         1024  /*�������м�¼ʱ��Ҫ�Ѻ��м�¼�ṹ�巢�͸�dectģ�飬����������չ��Ϣ��Ϊ1024*/

#define FILE_PATH_DIAG_FXS1_TO_FXS2 "/var/voice/fxs1tofxs2"
#define FILE_PATH_DIAG_FXS2_TO_FXS1 "/var/voice/fxs2tofxs1"
#define FILE_PATH_VOIPBOOTUP_STATUS "/var/voice/voipbootupstatus"
#ifdef SUPPORT_ATP_DECT_VOICE
#define VCE_FXS_MAX                 2       /*���֧��FXS�ڵĸ���*/
#define VCE_DECT_HS_MAX             5       /*���֧��DECT�ӻ��ĸ���*/
#define VCE_PORT_MAX (VCE_FXS_MAX + VCE_DECT_HS_MAX)    /*���֧�ֶ˿ڵ���Ŀ*/


/*�˺���������ֵ*/
#define VCE_VOIP_BASE           1                                   /*VOIP�����ʼֵ*/
#define VCE_ISDN_BASE           (VCE_VOIP_BASE + VCE_VOIP_MAX)      /*ISDN�����ʼֵ*/
#define VCE_PSTN_BASE           (VCE_ISDN_BASE + VCE_ISDN_MAX + 1)  /*PSTN�����ʼֵ,�����1�Ǽ�ISDN���ʺ�*/
#define VCE_CS_BASE             (VCE_PSTN_BASE + VCE_PSTN_MAX)      /*CS�����ʼֵ*/
#define VCE_FXS_INCALL_BASE     (VCE_CS_BASE + VCE_CS_MAX)          /*FXS�ڲ������˺������ʼֵ*/
#define VCE_DECT_INCALL_BASE    (VCE_FXS_INCALL_BASE + VCE_FXS_MAX) /*DECT�ڲ������˺������ʼֵ*/

/*ISDN���ʺ�����,���ʺ����ڵ�û��MSN����ʱISDN�����п���*/
#define VCE_ISDN_DFT    (VCE_ISDN_BASE + VCE_ISDN_MAX)              /*ISDNĬ��˳���(��MSN��������)*/

/*����ΪAutoʱDect���ݵ��˺�����*/
#define VCE_OUTGO_AUTO  (VCE_DECT_INCALL_BASE + VCE_DECT_HS_MAX)    /*ȡһ���ϴ�ֵ��Ϊ�Զ�ѡ·����*/
#endif

/*Dect LineSetting�������˺�����*/
#define VCE_ISDN_NAME               "ISDN"
#define VCE_PSTN_NAME               "PSTN"
#define VCE_CS_NAME                 "CS"
#define VCE_INCALL_NAME             "INCALL"
#define VCE_NULL_NAME				"NULL"
#define DSP_TIMESLOT_DTMF4          4    /* Fxs0�˿ڼ���dtmf4 */
#define DSP_TIMESLOT_DTMF5          5    /* Fxs1�˿ڼ���dtmf5 */
#define DSP_TIMESLOT_TEST_UE0       0    /* Fxs0�˿�UE�� */
#define DSP_TIMESLOT_TEST_UE1       1    /* Fxs1�˿�UE�� */
#ifdef SUPPORT_ATP_DECT_VOICE
#define DECT_EEPROM_SUBSDATA_LEN    250   //DECT PCM�л�TDM�����޸�
#define DECT_EEPROM_SUBSDATA_STRLEN DECT_EEPROM_SUBSDATA_LEN * 2

#define DECT_CMO_SUBSDATA_SIGN_LEN  1
#define DECT_CMO_SUBSDATA_TOTAL_LEN DECT_CMO_SUBSDATA_SIGN_LEN + DECT_EEPROM_SUBSDATA_STRLEN + 1
#define DECT_CMO_SUBSDATA_MAX_LEN   512

#define DECT_UPDATA_SIGN_TRUE       '1'

#define DECT_PCM_TEST_DTMF          5
#define DECT_PCM_TEST_UE            2
#define VOICE_DECT_LINE_MAX         28

typedef struct tagVOICE_DECT_VDB_ARG_ST
{
    VOS_UINT32     ulIdx;
    long long      llIndex;
    VOS_CHAR       acArgStr[VCE_STR_LEN_64];
}VOICE_DECT_VDB_ARG_ST;

#endif

/******************************************************************************************/
/*
** msg����: �Ժ�����������Ϣ�շ�������msg�����������Ϣ���Ͷ���������Ҫ��voicecoremsgtypes.h
** ����������VOICE_MSG_TYPE�Ϳ��Բ���������
*/
/******************************************************************************************/

typedef enum VOICE_MSG_TYPE
{
    /*������������Ϣ���Ͷ���*/
    VOICE_MSG_TYPE_TAPI = 8840,   	/*tapi��Ϣ*/
    VOICE_MSG_TYPE_TIMER,         	/*timer��Ϣ*/
    VOICE_MSG_TYPE_TPTD,          	/*tptd��Ϣ*/
    VOICE_MSG_TYPE_SC,				/*SC��Ϣ*/
    VOICE_MSG_TYPE_CS,				/*CS��Ϣ*/
    VOICE_MSG_TYPE_PM,				/*PM��Ϣ*/
    VOICE_MSG_TYPE_MIC,             /*MIC��Ϣ*/
#ifdef SUPPORT_ATP_DIAG_POTS_MNG
    VOICE_MSG_TYPE_DIAG,            /*DIAG��Ϣ*/
#endif
    VOICE_MSG_TYPE_LINEMNG,
    VOICE_MSG_TYPE_ISDN,
    VOICE_MSG_TYPE_SIP,
	VOICE_MSG_TYPE_CMBS,           	/*cmbs target�����Ϣ*/
	VOICE_MSG_TYPE_DIAGLOG,         /* diag log��Ϣ. */

    /*������������Ϣ���Ͷ���*/
    VOICE_MSG_TYPE_CLI = 8900,      /*CLI��Ϣ*/
    VOICE_MSG_TYPE_CMS,           	/*���ù�����Ϣ*/
    VOICE_MSG_TYPE_WEB,           	/*���ù�����Ϣ*/
    VOICE_MSG_TYPE_REBOOT,         	/*web������Ϣ,���޸���ͬ������ATP_VOICE_MSG_REBOOT*/
    VOICE_MSG_TYPE_STOP,            /*web������Ϣ,���޸���ͬ������ATP_VOICE_MSG_STOP*/
    VOICE_MSG_TYPE_WAN,             /*wan������Ϣ*/
    VOICE_MSG_TYPE_RESTORE,         /*�ָ�����������Ϣ*/
    VOICE_MSG_TYPE_ATS,             /*ATS�������ϱ���Voice��Ϣ*/
    VOICE_MSG_TYPE_QUERYSTATUS,     /*�ⲿ���̲�ѯ����״̬*/
    VOICE_MSG_TYPE_OFFHOOKPLAYINBAND, /*ժ��״̬�����Ŵ�������Ϣ*/

    VOICE_MSG_TYPE_GET_PINSTATUS,   /*��ȡ��ǰҳ���PIN״̬*/
    VOICE_MSG_TYPE_SAVE_PININFO,    /*����PIN��Ϣ*/

    VOICE_MSG_TYPE_BUTT
} VOICE_MSG_TYPE_E;

/*����CLI����Ϣ����*/
typedef enum VOICE_CLI_MSG_TYPE_EN_
{
    VOICE_CLI_MSG_START = 1,   	    /*��������*/
    VOICE_CLI_MSG_STOP,	            /*��ֹ����*/
    VOICE_CLI_MSG_SIP_DNSFLUSHLIGHT,    /*�������dns����*/
    VOICE_CLI_MSG_SIP_DNSTTL0,          /*����ttl0��Ϣ�����������������dns��ѯ*/
    VOICE_CLI_MSG_SIP_REG,        	/*ע��sip�˺�*/
    VOICE_CLI_MSG_SIP_UNREG,        /*ע��sip�˺�*/
    VOICE_CLI_MSG_SIP_REG_REPORTOK, /*����SIP�����˺�״̬�����������ע��ɹ�*/
    VOICE_CLI_MSG_VOICE_TAPI,
    VOICE_CLI_MSG_VOICE_LINEMNG,
    VOICE_CLI_MSG_VOICE_SC,
    VOICE_CLI_MSG_VOICE_DPLAN,
    VOICE_CLI_MSG_VOICE_PSTN,
    VOICE_CLI_MSG_VOICE_SIP,
    VOICE_CLI_MSG_VOICE_CUSTOMER,
    VOICE_CLI_MSG_VOICE_DECT,
    VOICE_CLI_MSG_QUERY_CFG,        /*��ѯ����ҵ��������Ϣ*/
    VOICE_CLI_MSG_QUERY_TAPI_CFG,   /*��ѯtapi������Ϣ*/
    VOICE_CLI_MSG_CS_STAT,          /*��ѯCSע��ͺ���״̬*/
    VOICE_CLI_MSG_QUERY_SIPID,      /*��ѯSIP�ʺ���Ϣ*/
    VOICE_CLI_MSG_QUERY_RTP,        /*��ѯRTP��Ϣ*/
    VOICE_CLI_MSG_QUERY_SIPSRV,     /*��ѯSIP��������Ϣ*/
    VOICE_CLI_MSG_QUERY_SIP_STAT, 	/*��ѯsip����״̬��ע��״̬*/
    VOICE_CLI_MSG_DBG_LEVEL,      	/*������־����*/
    VOICE_CLI_MSG_DBG_TELNET,      	/*telnet���������Ϣ*/
    VOICE_CLI_MSG_DBG_BR0,      	/*BR0����*/
    VOICE_CLI_MSG_QUERY_REGINFO,	/*��ѯע����Ϣ*/
    VOICE_CLI_MSG_DBG_CONSOLE,      /*console�����Ϣ*/
    VOICE_CLI_MSG_VOICE_RWSLIC,     /*��дslic�Ĵ�������*/
    VOICE_CLI_MSG_VOICE_TONE,       /*����ָ��Tone��*/
    VOICE_CLI_MSG_VOICE_CHANNEL,    /*����FXS1��FXS2ͨ��*/
    VOICE_CLI_MSG_VOICE_DSP_LOG,    /*����DSP log����*/
    VOICE_CLI_MSG_VOICE_DSP_TRACE,    /*DSP ץ��*/

    /*����CMS���޸��������õ���Ϣ*/
    VOICE_CLI_MSG_CFG_SET_LINEENABLE,    
    VOICE_CLI_MSG_CFG_SET_LINEID,
    VOICE_CLI_MSG_CFG_SET_LINEUSRNAME,
    VOICE_CLI_MSG_CFG_SET_LINEPWD,
    VOICE_CLI_MSG_CFG_SET_LINEPORT,    
	VOICE_CLI_MSG_UNKNOWN,
	
    VOICE_CLI_MSG_BUTT
}VOICE_CLI_MSG_TYPE_E;

/* ���ù����͵�ָʾ */
typedef enum VOICE_CMS_MSG_TYPE
{
    VOICE_CMS_MSG_SIP_REG,        	/*ע��sip�ʺ�*/
    VOICE_CMS_MSG_SIP_UNREG,        /*ע��sip�˺�*/
    VOICE_CMS_MSG_WAN_STAT,       	/*WAN״̬����*/
    VOICE_CMS_MSG_UPDATE_CFG,     	/*����������*/
    VOICE_CMS_MSG_EQUIPMENT_TSET,   /*װ������*/
    VOICE_CMS_MSG_QUERY_SIP_STAT, 	/*���ù�����Ϣ,��ѯsip����״̬��ע��״̬*/
    VOICE_CMS_MSG_DBG_LEVEL,      	/*���ù�����Ϣ,������־����*/
    VOICE_CMS_MSG_DBG_TELNET,      	/*���ù�����Ϣ,�������������Ϣ*/
    VOICE_CMS_MSG_QUERY_REGINFO,	/*��ѯע����Ϣ*/
    VOICE_CMS_MSG_OUTLINE_CHANGED,  /*֪ͨ������������״̬�仯 */
    VOICE_CMS_MSG_FXO_RELAYCTL,     /*FXO�̵�������*/
    VOICE_CMS_MSG_DIAGBUTTON,       /*��ϰ�ť��Ϣ*/
    VOICE_CMS_MSG_LINERESET,        /*SIP�˺�����*/
    VOICE_CMS_MSG_LINE_REREG,       /*SIP�ʺ���RESET������ע��*/
    VOICE_CMS_MSG_STATUSQUERY,      /*����ʺ�����״̬��Ϣ*/
    VOICE_CMS_MSG_CALLSTATUS_QUERY, /*��·����״̬��ѯ*/
    VOICE_CMS_MSG_ANIMSN,           /*��ȡmsn�˺���Ϣ*/
    VOICE_CMS_MSG_WAN_WILLDOWN,     /*֪ͨ��������wan����down*/
    VOICE_CMS_MSG_LAN_IPCHANGE,     /*֪ͨ��������LAN��ά����ַ�ı���*/
    VOICE_CMS_MSG_WAKEUP_TIMECHANGE,/*�������嶨ʱ��ʱ��:���ñ��˻���ϵͳʱ�����*/
    /*HG253s V2��������:�˿�״̬��ʾ*/
    VOICE_CMS_MSG_PORTSTATUS_QUERY, /*�˿�״̬��ѯ*/
    VOICE_CMS_MSG_PROFILERESET,     
    /************** DECT START *****************/
    VOICE_CMS_MSG_DECT_RESTORE = 0x80, /*Dect״̬����(ע��/ע������ı仯)*/
    VOICE_CMS_MSG_DECT_NAME,        /*Dect�ӻ����Ƹ���*/
    VOICE_CMS_MSG_DECT_LINESET,     /*Dect�ӻ�LineSettings����*/ 
    VOICE_CMS_MSG_DECT_PAGE,        /*Dect�ӻ�����*/
    VOICE_CMS_MSG_DECT_REGOPEN,     /*DECT�����ӻ�ע��*/
    VOICE_CMS_MSG_DECT_REGCLOSE,    /*DECT��ֹ�ӻ�ע��*/
    VOICE_CMS_MSG_DECT_HS_REG,      /*DECT�ӻ�ע���¼�*/
    VOICE_CMS_MSG_DECT_HS_UNREG,    /*DECT�ӻ�ע���¼�*/
    VOICE_CMS_MSG_DECT_RFSET,       /*DECT��Ƶ����*/
    /* begin added by xiehuiguang */
    VOICE_CMS_MSG_DECT_ANT0_TXSET,  /*����0�����¼�*/
    VOICE_CMS_MSG_DECT_ANT1_TXSET,  /*����1�����¼�*/
    VOICE_CMS_MSG_DECT_ANT0_TXDISPLAY,
    VOICE_CMS_MSG_DECT_ANT1_TXDISPLAY,
    VOICE_CMS_MSG_DECT_SETRGIQM,
    VOICE_CMS_MSG_DECT_GETRGIQM,
    VOICE_CMS_MSG_DECT_GETREGHS, 	/*DECT ��ȡ�ӻ��б���Ϣ*/
    VOICE_CMS_MSG_DECT_UARTSET,     /*DECT UART����*/
    /* end */
    VOICE_CMS_MSG_DECT_SETNEMO,     /*DECT NEMO ģʽ����*/
    VOICE_CMS_MSG_DECT_SETECO,      /*DECT ECOģʽ,��Ƶ��������*/
    VOICE_CMS_MSG_DECT_SETPCM,      /*PCM����ģʽ*/
    VOICE_CMS_MSG_DECT_PCMTEST,     /* pcm��ͨ�Բ��� */
    VOICE_CMS_MSG_DECT_SETTIME,     /*DECT ʱ��ͬ��*/
    VOICE_CMS_MSG_DECT_SETPIN,      /*DECT PIN����*/
    VOICE_CMS_MSG_DECT_GETPIN,      /*DECT PIN��ȡ*/
    VOICE_CMS_MSG_DECT_SETCALIB,    /*DECT װ����������(RVBG,RVREF,RXTUN,RFPI)*/
    VOICE_CMS_MSG_DECT_GETCALIB,    /*DECT װ��������ȡ(RVBG,RVREF,RXTUN,RFPI)*/
    VICCE_CMS_MSG_DECT_GETVER,      /*DECT �汾�Ż�ȡ*/
    VOICE_CMS_MSG_DECT_TESTMODE,    /*DECT ����ģʽ����*/
    VOICE_CMS_MSG_DECT_EEPROMSET,   /*DECT �ֹ�дEEPROM*/
    VOICE_CMS_MSG_DECT_REBOOT,      /*DECT ����*/
    VOICE_CMS_MSG_DECT_TELBOOK,     /*DECT �绰�����ø���*/
    VOICE_CMS_MSG_DECT_UPDATE,      /*DECT ����*/
    VOICE_CMS_MSG_DECT_RELOCK,      /*DECT RELOCK��Base*/
    VOICE_CMS_MSG_DECT_REINIT,      /*DECT ���³�ʼ��*/
    VOICE_CMS_MSG_DECT_LOG,         /*DECT LOG*/    
    VOICE_CMS_MSG_DECT_EEPROMGET,   /*DECT �ֹ���EEPROM*/
    VOICE_CMS_MSG_DECT_GETSUBINFO,  /*DECT ��ȡע����Ϣ*/
    VOICE_CMS_MSG_DECT_SETSUBINFO,  /*DECT ����ע����Ϣ*/
    VOICE_CMS_MSG_DECT_GETBARCODE,  /*DECT ��ȡװ����Ϣ*/
    VOICE_CMS_MSG_DECT_SETBARCODE,  /*DECT ����װ����Ϣ*/

    VOICE_CMS_MSG_DECT_GETINITSTAT, /*DECT ��ȡ��ʼ��״̬*/
    VOICE_CMS_MSG_DECT_MISSCALLCHANGE,
	VOICE_CMS_MSG_DECT_LIST_CHANGE,
	VOICE_CMS_MSG_DECT_SETMWI,      /*DECT ���Ե�����*/
	VOICE_CMS_MSG_DECT_SETCMBSLINETYPE,    /*����CMBS Line Type,������֤Ҫ��*/
	VOICE_CMS_MSG_DECT_RESETALL,
	VOICE_CMS_MSG_DECT_CMSUPDATEMISS,
	VOICE_WEB_MSG_DECT_WEBUPDATEMISS,
	VOICE_CMS_MSG_DECT_CONTACTSNOTIFY,
	VOICE_CMS_MSG_DECT_NETPHONEBOOK_RESULT,  /*������Net Phone book ���󷵻صĽ��*/
	
	VOICE_CMS_MSG_DECT_GETMAILRES,
	VOICE_CMS_MSG_DECT_NEWMAILNOTIFY,
	VOICE_CMS_MSG_DECT_NEWRSSNOTIFY,
	VOICE_CMS_MSG_DECT_READCHANNELEND,
	VOICE_CMS_MSG_DECT_CHANGELISTRSS,
	VOICE_CMS_MSG_DECT_READCHANNELERR,
	VOICE_CMS_MSG_DECT_GETMAILERR,
	VOICE_CMS_MSG_DECT_MODIFYCHANNELRELATE,
	VOICE_CMS_MSG_DECT_MODIFYACCOUNTRELATE,
	VOICE_CMS_MSG_DECT_RECORD_CALLINFO,
	VOICE_CMS_MSG_DECT_OPERAORSNAME,
	VOICE_CMS_MSG_DECT_SETHALFTRANSMITPOWER,/*DECT���书�ʵ�һ��*/
	VOICE_CMS_MSG_DECT_MOBILE_UPDATE,	   /*�ӻ���Ϣˢ��*/
    /************** DECT END *****************/
    VOICE_CMS_MSG_DECT_CATIQMODE,
    VOICE_CMS_MSG_DECT_ENCRYPTION,
    VOICE_CMS_MSG_UNKNOWN = 0xff,

} VOICE_CMS_MSG_EN;

typedef enum VOICE_ATS_MSG_TYPE
{
	VOICE_ATS_MSG_ATA_RSP            = 1,      /*�·���ATAָ���*/
	VOICE_ATS_MSG_CHUP_RSP           = 2,      /*�·���CHUPָ���*/
    VOICE_ATS_MSG_ATD_RSP            = 3,      /*�·���ATDָ���*/
    VOICE_ATS_MSG_DDSETEX_RSP        = 4,      /*�·���DDSETEXָ���*/ 
	VOICE_ATS_MSG_CHLD_RSP           = 5,      /*�·���CHLDָ���*/
	VOICE_ATS_MSG_CLIP_RSP           = 6,      /*�·���CLIPָ���*/
	VOICE_ATS_MSG_DTMF_RSP           = 7,      /*�·���DTMFָ���*/
	VOICE_ATS_MSG_CW_RSP             = 8,      /*�·���CWָ���*/
	
	VOICE_ATS_MSG_ORIG_REPORT        = 9,      /*ORIGָʾ�ϱ�*/
	VOICE_ATS_MSG_CLIP_REPORT        = 10,     /*CLIPָʾ�ϱ�*/
	VOICE_ATS_MSG_RING_REPORT        = 11,     /*RINGָʾ�ϱ�*/  
	VOICE_ATS_MSG_CONF_REPORT        = 12,     /*CONFָʾ�ϱ�*/  
	VOICE_ATS_MSG_CONN_REPORT        = 13,     /*CONNָʾ�ϱ�*/ 
	VOICE_ATS_MSG_CEND_REPORT        = 14,     /*CENDָʾ�ϱ�*/
	
	VOICE_ATS_MSG_SYSINFO_REPORT     = 15,     /*SYSINFOָʾ�ϱ�*/
	VOICE_ATS_MSG_SIMSTATUS_REPORT   = 16,     /*SIMSTATUSָʾ�ϱ�*/
	VOICE_ATS_MSG_CSSI_REPORT        = 17,     /*CSSIָʾ�ϱ�*/
	VOICE_ATS_MSG_CSSU_REPORT        = 18,     /*CSSUָʾ�ϱ�*/ 
	VOICE_ATS_MSG_CCWA_REPORT        = 19,     /*CCWAָʾ�ϱ�*/

    VOICE_ATS_MSG_USB_STATUS_UPDATE  = 20,
   
    VOICE_ATS_MSG_CCALLSTATE_REPORT  = 21,     /*CCALLSTATEָʾ�ϱ�*/
    
    VOICE_ATS_MSG_CCFC_RSP           = 22,     /*�·���CCFCָ���*/
    VOICE_ATS_MSG_CLVL_RSP           = 23,     /*�·���CLVLָ���*/
    VOICE_ATS_MSG_CLCK_RSP           = 24,     /*�·���CLCKָ���*/
    VOICE_ATS_MSG_CPWD_RSP           = 25,     /*�·���CPWDָ���*/
    VOICE_ATS_MSG_CLIR_RSP           = 26,     /*�·���CLIRָ���*/
    VOICE_ATS_MSG_XLEMA_REPORT       = 27,     /*���������ϱ� */
    VOICE_ATS_MSG_CSCHANINFO_REPORT  = 28,     /* CSCHANNELINFOָʾ�ϱ�.*/

	VOICE_ATS_MSG_UNKNOWN = 0xff,
}VOICE_ATS_MSG_EN;

typedef enum tagVOICE_VOIPDIAG_MSG_TYPE
{
	VOICE_VOIPDIAG_MSG_GETFILE    = 1,      
    VOICE_VOIPDIAG_MSG_FLUSHCACHE = 2,   
    VOICE_VOIPDIAG_MSG_SETHIGH    = 3,
    VOICE_VOIPDIAG_MSG_SETLOW     = 4,
	
	VOICE_VOIPDIAG_MSG_UNKNOWN = 0xff,
}VOICE_VOIPDIAG_MSG_EN;

typedef enum
{
    EPCMD_USER_SLIC_HELP = 0,
    EPCMD_USER_SLIC_WRITE_DIRECT_REG,
    EPCMD_USER_SLIC_READ_DIRECT_REG,
    EPCMD_USER_SLIC_BATCH_READ_DIRECT_REG,    
    EPCMD_USER_SLIC_BATCH_WRITE_DIRECT_REG,
    EPCMD_USER_SLIC_MAX    
}EPCMD_USER_SLIC;   

typedef struct SLICCMDUSERPARM
{
    unsigned long    size;       /* Size of the structure (including the size field) */
    int              cmd;
    int              lineId;
    int              arg[3];   
    unsigned char     regValue[100];   
    unsigned short   retVal;   
    int         epStatus;
} SLIC_CMD_USER_PARM, *PSLIC_CMD_USER_PARM;

typedef struct tagVOICE_DSP_TRACE_INFO_ST
{
    VOS_BOOL        bEnable;             /*�Ƿ�ʹ��*/
    VOS_UINT32      ulChannelId;         /*ͨ��ID*/
    VOS_UINT32      ulSrcIp;             /*ԴIP*/
    VOS_UINT32      ulDesIp;             /*Ŀ��IP*/
    VOS_UINT32      ulSrcPort;           /*Դ�˿�*/
    VOS_UINT32      ulDesPort;           /*Ŀ�Ķ˿�*/
}VOICE_DSP_TRACE_INFO_ST;

/*****************************************************************************
** �����: USB״̬�仯
** �����ʽ: 
** ��Ӧ��ʽ: 
******************************************************************************/
typedef struct tagCS_MSG_USB_STATUS_ST
{
    unsigned char   ucCmdFrom;
    unsigned char   ucResult;
    unsigned char   ucStatus;
}CS_MSG_USB_STATUS_S;

/*****************************************************************************
** �����: ϵͳ����Ϣ��ѯ
** �����ʽ: AT^SYSINFO
** ��Ӧ��ʽ: <CR><LF>^SYSINFO:< srv_status >,< srv_domain >,< roam_status >,
             < sys_mode >,< sim_state >[,<lock_state>,<sys_submode>]<CR><LF><CR>
             <LF>OK<CR><LF> <CR><LF>^SYSINFO:< srv_status >,< srv_domain >,
             < roam_status >,< sys_mode >,< sim_state >[,<lock_state>,
             <sys_submode>]<CR><LF><CR><LF>OK<CR><LF>
******************************************************************************/
typedef struct tagCS_MSG_SYSINFO_ST
{
    unsigned char   ucCmdFrom;
    unsigned char   ucResult;
    unsigned char   ucSrvStatus;    /*ϵͳ����״̬.��CS_SERVER_STATUS_E,ȡֵ����
                                      0:  �޷���
                                      1:  �����Ʒ���
                                      2:  ������Ч 
                                      3:  �����Ƶ��������
                                      4:  ʡ�����˯״̬*/
    unsigned char   ucSrvDomain;    /*ϵͳ������.��CS_ZONE_STATUS_E,ȡֵ����
                                      0�� �޷���
                                      1�� ��CS����
                                      2�� ��PS����
                                      3�� PS+CS����
                                      4�� CS��PS��δע�ᣬ����������״̬
                                      255: CDMA��֧�֡�
                                      250: ��ʾδ��ȡ����ֵ��������*/
    unsigned char   ucRoamStatus;   /*����״̬.��CS_ROAM_STATUS_E,ȡֵ����
                                      0�� ������״̬
                                      1�� ����״̬*/
    unsigned char   ucSysMode;      /*ϵͳģʽ.��CS_SYS_MODE_E,ȡֵ����
                                      0�� �޷���
                                      1�� AMPSģʽ���ݲ�ʹ�ã�
                                      2�� CDMAģʽ���ݲ�ʹ�ã�
                                      3�� GSM/GPRS ģʽ
                                      4�� HDRģʽ
                                      5�� WCDMAģʽ
                                      6�� GPSģʽ*/    
    unsigned char   ucSimState;     /*SIM��״̬.��CS_SIM_STATUS_E,ȡֵ����
                                      0��  USIM��״̬��Ч
                                      1:   USIM��״̬��Ч  
                                      2��  USIM��CS����Ч��EW��
                                      3��  USIM��PS����Ч(EW)
                                      4��  USIM��PS+CS�¾���Ч(EW)
                                      240: ROMSIM�汾
                                      255: USIM��������   
                                      250: ��ʾδ��ȡ����ֵ��������*/
    unsigned char   ucLockState;    /*SIM����LOCK״̬.��CS_SIMLOCK_STATUS_E,ȡֵ����
                                      0�� SIM��δ��SIMLOCK��������
                                      1�� SIM����SIMLOCK��������*/
    unsigned char   ucSysSubMode;   /*��CS_SUBSYS_MODE_E
                                      0���޷���
                                      1�� GSMģʽ
                                      2�� GPRSģʽ
                                      3�� EDGEģʽ
                                      4�� WCDMAģʽ
                                      5�� HSDPAģʽ
                                      6�� HSUPAģʽ
                                      7�� HSDPA&HSUPAģʽ*/
    unsigned char   ucExtern1; //��ʱ 1����LTE ONLY
    unsigned char   ucExtern2; //��ʱ 1����VOLTEע������
    unsigned char   ucExtern3;
}CS_MSG_SYSINFO_S;

typedef enum
{
    DIAGNOSIS_SLIC_CHECKRESULT_INIT = 0,
    DIAGNOSIS_SLIC_CHECKRESULT_SUCCESS,
    DIAGNOSIS_SLIC_CHECKRESULT_FAIL,
    DIAGNOSIS_MAX    
}VOICE_DIAGNOSIS_EN;  

typedef enum tagVOICE_LED_STATUS_EN
{
    VOICE_LED_STATUS_NONE = 0,
    VOICE_LED_STATUS_REBOOT,
}VOICE_LED_STATUS_EN;  

/* WEB����Ϣ*/
typedef enum VOICE_WEB_MSG_TYPE
{
    VOICE_WEB_MSG_PUK_REQUIRED       = 1,       /*ҳ���Ͻ�pin����ò��ɹ�3�κ���Ҫ����PUK��*/
    VOICE_WEB_MSG_UNKNOWN = 0xff,
}VOICE_WEB_MSG_EN;

/* WAN����Ϣ */
typedef enum VOICE_WAN_MSG_TYPE
{
    ATP_UTIL_PPP_UP_MANUAL = 0,   // �ֶ��������ӳɹ�
    ATP_UTIL_PPP_UP_AUTO = 1,      // �Զ��������ӳɹ�
    ATP_UTIL_PPP_UP_DEMAND = 2,   // ���貦�Ž������ӳɹ�
    ATP_UTIL_PPP_UP_VOICE = 3,     // VOIPժ�������������ӳɹ�
    ATP_UTIL_PPP_DOWN_DSL = 4,   // DSL��·ʧ�ܵ������ӶϿ�
    ATP_UTIL_PPP_DOWN_ECHO = 5,   // PPP ECHO������Ӧ�������ӶϿ�
    ATP_UTIL_PPP_DOWN_TIMEOUT = 6,  // ���貦�ų�ʱ�������������ӶϿ�
    ATP_UTIL_PPP_FAIL_SVR = 7,  // BAS����Ӧ���²���ʧ��
    ATP_UTIL_PPP_FAIL_SVR_VOICE = 8, // BAS����Ӧ����VOICEժ�������Ĳ���ʧ��
    ATP_UTIL_PPP_FAIL_AUTH = 9,  // ��֤�����²���ʧ��
    ATP_UTIL_PPP_FAIL_AUTH_VOICE = 10,  // ��֤������VOICEժ�������Ĳ���ʧ��
    ATP_UTIL_PPP_FAIL_NO_NAS = 11,  // û��nas�ӿڣ���WAN PPP�ϵ�ʱ��ժ������ʧ�ܣ�
    ATP_UTIL_DNS_TTL_EXPIRE_NOTIFY = 12, //dns srv ttl ��ʱ֪ͨ
}VOICE_WAN_MSG_EN;

/*���е�·������ö�ٶ���*/
typedef enum tagLINE_TYPE_EN
{
    LINE_TYPE_NULL      = 0x0,
    LINE_TYPE_PSTN      = (0x1 << 0),
    LINE_TYPE_SIP       = (0x1 << 1),
    LINE_TYPE_CS        = (0x1 << 2),
    LINE_TYPE_ISDN      = (0x1 << 3),
    LINE_TYPE_INCALL    = (0x1 << 4),   
    LINE_TYPE_MIX       = (0x1 << 5),       /* ��Ϻ��� */
    LINE_TYPE_LCL       = (0x1 << 6),       /* ���ط��� */
	LINE_TYPE_AUTO		= (0x1 << 7),		/*  */
    
    LINE_TYPE_BUT,
}LINE_TYPE_EN;

/*ģʽѡ��:VOIP/PSTNģʽ��,ISDN������Ч������*/
typedef enum LINE_MODE_E_
{
    LINE_MODE_VOIP      = LINE_TYPE_SIP,
    LINE_MODE_PSTN      = (LINE_TYPE_PSTN | LINE_TYPE_SIP),
    LINE_MODE_ISDN      = (LINE_TYPE_ISDN | LINE_TYPE_SIP),
    LINE_MODE_AUTO      = (LINE_TYPE_PSTN | LINE_TYPE_ISDN | LINE_TYPE_SIP | LINE_TYPE_CS),
    LINE_MODE_CS        = (LINE_TYPE_CS),
    LINE_MODE_BUTT
}LINE_MODE_E;

/*�˿�����ö�ٶ���*/
typedef enum tagPORT_TYPE_E_
{
    PORT_TYPE_NULL_ = 0,
    PORT_TYPE_FXS,                      /*FXS��*/
    PORT_TYPE_HS,                       /*DECT�ӻ�,HandleSet(HS)*/
    PORT_TYPE_ISDN,                       /*ISDN����,����ISDN*/
	PORT_TYPE_SIP,

    PORT_TYPE_BUTT,
}PORT_TYPE_E;


/*FXO��״̬ö�ٶ���*/
typedef enum tagFXO_STATUS_E_
{
    FXO_STATUS_NULL = 0,
    FXO_STATUS_ISDN,                      /*ISDN up*/
    FXO_STATUS_PSTN,                      /*PSTN up*/

    FXO_STATUS_BUTT,
}FXO_STATUS_E;

typedef enum tagCS_LINKSTATUS_E_
{
    CS_LINKSTATUS_NULL = 0,
    CS_LINKSTATUS_FAULT,
    CS_LINKSTATUS_UNREG,
    CS_LINKSTATUS_REG,
    CS_LINKSTATUS_INCALL,
    CS_LINKSTATUS_BUTT,
}CS_LINKSTATUS_E;

typedef enum tagFAX_TYPE_E
{
    FAX_TYPE_G711A     = 0,
    FAX_TYPE_G711U     = 1,   
    FAX_TYPE_T38_FAX   = 2,
    FAX_TYPE_G711A_VBD = 3,
    FAX_TYPE_G711U_VBD = 4,
    FAX_TYPE_NULL,
}FAX_TYPE_E;

typedef enum tagSIPOPTIONS_TYPE_EN
{
    VOICE_OPTIONS_DISABLE_EN    = 0,          /*������Options���/����*/        
    VOICE_OPTIONS_SEND_EN       = 1,          /*��������*/
    VOICE_OPTIONS_DETECT_EN     = 2,          /*�������*/
    VOICE_OPTIONS_MAX_EN
}VOICE_SIPOPTIONS_TYPE_EN;

typedef enum tagPORTBINDING_MODE_EN
{
    PORTBINDING_MODE_AUTO    =   0,          /*Auto*/
    PORTBINDING_MODE_SINGLE,                 /*һ���˿�ֻ�ܰ�һ���˺�,��������Ҫҳ��Ҳ����Ӧ�޸�*/
    PORTBINDING_MODE_CUSTOMER,               /*�󶨶˿ڶ���*/
    //PORTBINDING_MODE,                      /*������չ��ʽ*/
}PORTBINDING_MODE_EN;

/*2_10	SIP.SupportSIPLocalPortģʽ*/
typedef enum tagVOICE_SIP_LOCAL_PORT_MODE_EN
{
    VOICE_SIP_LOCAL_PORT_DISABLE = 0,    /*ƽ̨ͨ�÷�ʽ:��ʹ��X_SIPLocalPort*/
    VOICE_SIP_LOCAL_PORT_RELATED,        /*HG659����������:ͬһ��profile�µ�SIP �ʺ�����ͬ��X_SIPLocalPort,��UserAgentPortһ��.*/
    VOICE_SIP_LOCAL_PORT_SEPARATE,       /*HG658V2-20�޵綨��:��ͬ��SIP �ʺſ����ò�ͬ��X_SIPLocalPort.*/
}VOICE_SIP_LOCAL_PORT_MODE_EN;

/*��ͼ��ʽö��*/
//#ifdef SUPPORT_ATP_VCESIP_DIGITMAP_H248
typedef enum tagVOICE_DIGITMAP_FORMAT_EN
{
    VOICE_DIGITMAP_FORMAT_EXT        = 0x0,
    VOICE_DIGITMAP_FORMAT_MGCP       = 0x1 << 1,   /* MGCP��ʽ��ͼ */
    VOICE_DIGITMAP_FORMAT_H248       = 0x1 << 2,   /* H248��ʽ��ͼ */
    VOICE_DIGITMAP_FORMAT_BUTT       = 0x1 << 3,
}VOICE_DIGITMAP_FORMAT_EN;
//#endif

typedef enum tagVOICE_WAKEUP_WEEKDAY_EN
{    
    VOICE_WAKEUP_SUNDAY     = 0,
    VOICE_WAKEUP_MONDAY     = 1,
    VOICE_WAKEUP_TUESDAY    = 2,
    VOICE_WAKEUP_WEDNESDAY  = 3,
    VOICE_WAKEUP_THURSDAY   = 4,
    VOICE_WAKEUP_FRIDAY     = 5,
    VOICE_WAKEUP_SATURDAY   = 6,
    VOICE_WAKEUP_WEEKDAY_NULL,
        
}VOICE_WAKEUP_WEEKDAY_EN;

typedef struct tagVOICE_FUNOPCMS_MSG
{
    VOS_CHAR    szId[SIP_MAX_NUM_LEN];
    VOS_UINT32  ulFunOpType;                                  
}VOICE_FUNOPCMS_MSG;

typedef struct tagVOICE_WEEKDAY_INFO_OBJ
{
    VOS_CHAR    szWeekDayStr[VCE_STR_LEN_16];
    VOS_UINT32  ulWeekDayNum;                                  
}VOICE_WEEKDAY_INFO_ST;

typedef struct tagVOICE_WAN_ST
{
    VOS_CHAR      acInfName[VOICE_INTERFACENAME_LEN];  /* ��������ʹ�õ�Wan�ӿ��� */
    VOS_BOOL      bInternetWan;                         /* ��Wan�Ƿ�ΪInternet Wan */
    VOS_BOOL      bInternetToVoice;                     /* �Ƿ��Internet Wan�е�����wan */
}VOICE_WAN_ST;

/*��Ϣ���¼�*/
typedef struct tagATP_VOICE_MSG_ST_
{
    VOS_UINT32  ulEventType;                    /*�¼�����,����ͬ��Ϣ�µ��¼�����*/
    VOS_UINT32  ulPara;                         /*�¼�����*/
    VOS_CHAR    szBoby[ATP_VOICE_EVENT_LEN];    /*�¼�����*/
}ATP_VOICE_MSG_S;

/*������Ϣ�ṹ��*/
typedef struct tagATP_VOICE_MSG_BUF_ST_
{
    VOS_INT32  lMsgType;                        /*��Ϣ����. ��VOICE_MSG_TYPE_E*/
    VOS_CHAR   szMsgBody[ATP_VOICE_MSG_LEN];    /*��Ϣ����*/
}ATP_VOICE_MSG_BUF_S;

typedef struct tagGLOBAL_CFG_FROM_WEB_ST_
{
    VOS_UINT32  ulPrimaryCheckExpires;                  /* ̽�����ʱ�� */
    VOS_UINT32  ulMaxRetryTime;                         /* Э��ջ����ʱ�� */
    VOS_UINT32  ulRegExpire;                            /* ע��Expireʱ��,��λs                 */
    VOS_CHAR    acIsdnAreaCode[VOICE_AREA_LEN];         /* ISDN��������                         */
    VOS_CHAR    szIfName[VOICE_INTERFACENAME_LEN];      /* ���нӿ���                           */
    VOS_CHAR    acPSTNNumber[VOICE_PSTN_NUMBER_LEN];    /* PSTN����                             */
    VOS_CHAR    acUMTSNumber[VOICE_UMTS_NUMBER_LEN];    /* UMTS����                             */
    VOS_BOOL    bUmts;                                  /* �Ƿ�����UMTS����                     */
    VOS_BOOL    bPstnEnable;                            /* �Ƿ�����pstn                         */
    VOS_BOOL    bPstnClipEnable;                        /* PSTN��·�Ƿ�����CLIP                 */
    VOS_BOOL    bUmtsClipEnable;                        /* UMTS��·�Ƿ�����CLIP                 */
    VOS_UINT32  ulUmtsDTMFMethod;                       /* 0ΪCS����DTMF��1ΪCS����DTMF         */
    VOS_CHAR    acCallAllPortsPrefix[SIP_MAX_NUM_LEN];  
    VOS_UINT8   ucUrgenceRouteType;                     /* �������������·����,��LINE_TYPE_EN  */
    VOS_CHAR    acUrgenceRouteAccount[SIP_MAX_NUM_LEN]; /* �������������������                 */   


    VOS_CHAR    acVoipDigitMap[VOICE_VOIP_DIGITMAP_LEN];     /* VOIP��ͼ */
    VOS_BOOL    bHEnable;                                    /* �Ƿ�֧��#����*/
    VOS_BOOL    bEnableHotLine;                              /* �Ƿ�֧�����ߺ���*/
    VOS_UINT32  ulHotLineInterval;                           /* ���ߺ�������ʱ����*/
    VOS_CHAR    acHotLineNumber[VOICE_HOTLINE_NUMBER_LEN];   /* ���ߺ���*/
    VOS_UINT32  ulOffHookTime;
    VOS_UINT32  ulOnHookTime;
    VOS_UINT32  ulMinHookFlash;
    VOS_UINT32  ulMaxHookFlash;
    VOS_BOOL    bRegDetect;                          /*�Ƿ�����̽������*/
    VOS_UINT32  ulRegRetry;                          /* ע���ط�ʱ��,��λ��,����һ�ַ�����������ɺ�ĵȴ����*/
    VOS_UINT32  ulRegTimeoutRetry;                    /* ע�ᳬʱ�ط�ʱ��,��λ��,����һ�ַ�����������ɺ�ĵȴ����*/
    
    VOS_BOOL    bNeedPrack;                          /* �Ƿ���Ҫ֧��Prack����*/    
    VOS_BOOL    bUrgCallHead;                        /* ���������Ƿ�ӽ�������ͷ��*/
    VOS_UINT32  ulSessExpire;                        /* Session��Updateʱ��,��λs*/
    VOS_UINT32  ulMinSE;                             /* Min-SEʱ��,��λs*/
    VOS_UINT32  ulHoldMethod;                        /* ���б��ֵķ���,��SIP_HOLD_METHOD_E*/
    VOS_UINT32  ulMwiExpire;                         /* MWI��Expireʱ��,��λs*/
    VOS_UINT32  ulUaProfileExpire;                   /* UA Profile��Expireʱ��,��λs*/
    VOS_UINT32  ulReginfoExpire;                     /* Reg����Expireʱ�䣬��λs*/
    VOS_UINT32  ulOptionChkType;                     /* Option��ⷽ��,0--�����;1--�Զ˷�;2--���˷�*/
    VOS_UINT32  ulOptionChkTimeLen;                  /* Option�����ʱ��,��λs*/ 
    VOS_UINT32  ulOptDetInterval;                    /*  */
    VOS_UINT32  ulOptDetRetryInterval;               /*  */
    VOS_UINT32  ulOptDetRegRetryInterval;            /*  */
    VOS_UINT32  ulDigitShortTime;                    /* ���źż����̶�ʱ��ʱ��,��λms*/
    VOS_UINT32  ulDigitLongTime;                     /* ���źż�������ʱ��ʱ��,��λms */
    VOS_UINT32  ulDialToneTime;                      /* ������ʱ��,��λms*/
    VOS_UINT32  ulRingTime;                          /* ����ʱ��,��λms*/
    VOS_UINT32  ulHowlToneTime;                      /* ������ʱ��,��λms*/
    VOS_UINT32  ulBusyToneTime;                      /* æ��ʱ��,��λms*/
    VOS_UINT32  ulCFNRTime;                          /* ������Ӧ��ǰת����ʱ��:�������ʱ�������ǰת,��λs*/

#ifdef SUPPORT_ATP_VCESIP_DIGITMAP_H248
    VOS_UINT32  ulH248DigitShortTimer;                /*H248��ͼ�̳�ʱʱ��*/
    VOS_UINT32  ulH248DigitLongTimer;                 /*H248��ͼ����ʱʱ��*/
    VOS_UINT32  ulDigitMapFormat;                     /*��ͼ��ʽ��:H248��ͼ��,��VOICE_DIGITMAP_FORMAT_EN*/  
#endif   
    VOS_BOOL    bVoiceDiag;                          /* �Ƿ���װ������ */
    VOS_CHAR    szProfileBody[VCE_STR_LEN_2K];       /* ��¼�������profile body */

    /*HG253s V2��������Ҫ��ʵ��:SIP��DSCPmark*/
    VOS_UINT32  ulSIPDSCPMark;
    VOS_BOOL    bRingScheduleEnable;

    VOS_UINT32  ulVoipDiagLogLevel;                 /* Voip Diagnostics Log Level */
	
    VOS_UINT8   szFmcClipOption;                 /* fmc clip option,1-DTMF,2-FSK_ITU,3-FSK_BELL,4-FSK_RPAS */
    VOS_BOOL    bFmcUmtsClipEnable;              /* fmc umts clip enable, 1-enable, 0-disable */
    
    VOS_BOOL    bProfileCallWaitingEnable;      /* Profile�µ�CallWaitingEnable����*/ 

    VOS_UINT32  ulCIDSig;                       /*CID�ź���ѭЭ��: DTMF����FSK*/    
    VOS_BOOL    bVMIndTone;                     /* VoiceMail��ʾ�� */
#ifdef SUPPORT_ATP_LMT_CFU_TONE
    VOS_BOOL    bCfuIndTone;                     /* call forwarding��ʾ�� */
#endif
   VOS_BOOL    bUtEnable;                            /* �Ƿ�����ut                         */	
}GLOBAL_CFG_FROM_WEB_S, *GLOBAL_CFG_FROM_WEB_PS;

typedef struct tagLINE_CFG_FROM_WEB_ST_
{
    VOS_BOOL    bEnable;                        /*�ʺ�ʹ��*/
    VOS_BOOL    bReset;                         /* �Ƿ����ø�SIP�ʺ�*/
    VOS_BOOL    bPortEnable;                    /*�˺ŵĶ˿�ʹ��,HG253sV2�˿ڹ��ܶ���ʵ��*/
    VOS_UINT32  ulLineIndex;                    /*�����ʺ�����,Id*/    
    VOS_CHAR    szId[SIP_MAX_NUM_LEN];          /*SIP�ʺ�*/
    VOS_CHAR    szUserName[SIP_MAX_NAME_LEN];   /*�û���*/
    VOS_CHAR    szPassword[SIP_MAX_PSW_LEN];    /*����*/
    VOS_CHAR    szDisplayName[SIP_MAX_NAME_LEN]; /*������ʾ*/
    VOS_CHAR    szCode[SIP_MAX_NUM_LEN];        /*����*/
    VOS_BOOL    bEnableCode;                    /*�����Ƿ�ʹ��*/
    VOS_BOOL    bCallerIDRestrictionEnable;      /*CallerIDRestrictin�Ƿ�ʹ��*/       
    VOS_BOOL    bBusyOnBusy;                    /*Busy On Busy�Ƿ���*/
    VOS_BOOL    bMultiLine;                     /* ������·MultiLine����*/
    VOS_UINT8   ucProtocolType;                 /*Э������:1.UDP 2.TCP 3.TLS 4.SCTP*/
    VOS_UINT16  uwLocalPort;                    /*local port*/
    VOS_CHAR    szRegServer[VCE_LINE_SRV_MAX][SIP_MAX_URL_LEN];   /*ע�������*/
    VOS_CHAR    szSipDomain[VCE_LINE_SRV_MAX][SIP_MAX_URL_LEN];   /*ע��SIPDomain */
    VOS_CHAR    szOutProxy[SIP_MAX_URL_LEN];    /*outbound proxy server*/
    VOS_CHAR    szProxyServer[VCE_LINE_SRV_MAX][SIP_MAX_URL_LEN]; /*���������*/
    VOS_CHAR    szStunServer[SIP_MAX_URL_LEN];  /*stun������*/
    VOS_UINT16  uwRegPort[VCE_LINE_SRV_MAX];    /*ע��������˿ں�*/
    VOS_UINT16  uwOutProxyPort;                 /*outbound proxy port*/
    VOS_UINT16  uwProxyPort[VCE_LINE_SRV_MAX]; /*����������˿ں�*/
    VOS_UINT16  uwStunPort;                     /*stun�������˿ں�*/
    VOS_BOOL    bCLIPEnable;                    /*CLIP����*/
    VOS_BOOL    bMwiEnable;                     /*MWI�Ƿ�ʹ��*/
    VOS_BOOL    bUaProfileEnable;               /*UA_PROFILE�����Ƿ�ʹ��*/
    VOS_BOOL    bReginfoEnable;                 /*REG�����Ƿ�ʹ��*/
    VOS_BOOL    bCHEnable;                      /*CallHold�Ƿ�ʹ��*/
    VOS_BOOL    bCWEnable;                      /*CallWaiting�Ƿ�ʹ��*/
    VOS_BOOL    bCTREnable;                     /*CallTransfer�Ƿ�ʹ��*/
    VOS_UINT32  ulMaxSessions;                  /*����ͨ���Ƿ���*/

	VOS_CHAR	szHotLineNumber[VOICE_HOTLINE_NUMBER_LEN];
	VOS_UINT32  ulHotLineTimeout;
    VOS_BOOL    bHotLineEnable;
    VOS_UINT32  ulNumberDisplayType;
    VOS_UINT32  ulPrivacyLevel;
}LINE_CFG_FROM_WEB_S, *LINE_CFG_FROM_WEB_PS;

typedef struct tagISDN_LINE_CFG_FROM_WEB_ST_
{
    VOS_CHAR    szNumber[VOICE_ISDN_NUMBER_LEN];/*ISDN����*/
    VOS_BOOL    bBusyOnBusy;                    /*Busy On Busy�Ƿ���*/
    VOS_BOOL    bCLIPEnable;                    /*CLIP�Ƿ���*/
}ISDN_LINE_CFG_FROM_WEB_S, *ISDN_LINE_CFG_FROM_WEB_PS;

#ifdef SUPPORT_ATP_DECT_VOICE
typedef struct tagVOICE_DECT_LINE_NOTIFY_OBJ
{
    VOS_UINT32  ulNumber;
    VOS_UINT32  auLineId[VOICE_DECT_LINE_MAX];
}DECT_VOICE_LINE_NOTIFY_ST;

typedef struct
{
    VOS_UINT8       u8_IPUI[VCE_STR_LEN_64];    /*!< Handset identity >suota����ʱ��*/
}DECT_HS_IPUI_ST;
typedef struct tagMOBILE_CFG_ST_
{
    VOS_BOOL    bEnable;                /*�˿��Ƿ�ʹ��.Dectûע����ΪDisable;ע����ΪEnable*/
    VOS_UINT8   ucPortID;               /*�˿�ID*/
    VOS_UINT8   ucLineID;               /*�ڲ��������кţ���ʼ�����VCE_INCALL_BASE*/
    VOS_UINT8   ucDectType;             /*Dect�ӻ�����:0��ʾGAP��1��ʾCATIQ1��2��ʾCATIQ2����DECT_TYPE_E */
    VOS_UINT8   ucInLineNum;            /*��������ʺ���Ŀ*/
    VOS_UINT8   ucOutLineNum;           /*���������ʺ���Ŀ*/
    VOS_UINT8   ucReserve;
    VOS_BOOL    bInRelateAll;           /*�����������*/
    VOS_BOOL    bOutRelateAuto;         /*�����Զ�ѡ�ʺ�*/
    VOS_UINT8   aucIncomingLine[VCE_LINE_MAX];  /*��������ʺ�. ��Ź����ʺ�����*/
    VOS_UINT8   aucOutgoingLine[VCE_LINE_MAX];  /*���������ʺ�. ��Ź����ʺ�����*/
    VOS_CHAR    szName[VOICE_DECT_NAME_LEN];       /*�˿���*/
    VOS_CHAR    acIncallNumber[VOICE_INCALL_LEN];/*�ڲ��̺�*/
    VOS_INT     iCFUDestPortId;         /*������ǰתĿ�Ķ˿ںţ���Χ0~6����ҵ��ʱΪ-1*/
    VOS_INT     iCFBDestPortId;         /*��æĿ�Ķ˿ںţ���Χ0~6����ҵ��ʱΪ-1*/
    VOS_INT     iCFNRDestPortId;        /*��Ӧ��Ŀ�Ķ˿ںţ���Χ0~6����ҵ��ʱΪ-1*/
}MOBILE_CFG_S;
typedef struct tagDECT_CFG_FROM_WEB_ST_
{
    VOS_BOOL    	bEnable;                        /*dectʹ��*/
	VOS_BOOL        bEnableNemo;               /*ʹ��dect���书�ʵ�һ��*/
	VOS_BOOL	    bEnableEco;           /*ʹ��dect��̬ģʽʹ��*/
    VOS_CHAR    szPin[VCE_PIN_LEN_MAX];         /*dect�ӻ�PIN��*/
	VOS_BOOL   bEnableEcologicalModel;          /*ʹ��dect��̬ģʽʹ��*/
	VOS_BOOL   bEnableHalfTransmitPower;        /*ʹ��dect���书�ʵ�һ��*/
	VOS_CHAR   szSubsData[DECT_CMO_SUBSDATA_MAX_LEN]; /*�����ӻ�ע����Ϣ*/
    VOS_UINT32 ulNewMobilId;                    /*��¼�ո�ע���ϵ��ӻ�id����cgi���ظ�ҳ��*/
    DECT_HS_IPUI_ST stHsIpui[VCE_DECT_HS_MAX];
	MOBILE_CFG_S	stMobile[DECT_SET_NUM];
}DECT_CFG_FROM_WEB_S, *DECT_CFG_FROM_WEB_PS;
/*Dect�ӻ�����*/
typedef enum tagDECT_TYPE_E_
{
    DECT_TYPE_GAP	= 0,
    DECT_TYPE_CATIQ1,
    DECT_TYPE_CATIQ2,
    DECT_TYPE_DSPG,
	DECT_TYPE_UNKNOW,
}DECT_TYPE_E;
/* ��������*/
typedef enum tagDECT_CFG_TYPE_E_
{
    DECT_CFG_NORMAL   = 0,       /* ������� */
    DECT_CFG_EQUIP,              /* װ����������DECT���� */
    DECT_CFG_PP,                 /* �ӻ����������ע�� */
    DECT_CFG_OTHER,
}DECT_CFG_TYPE_E;
typedef struct tagDECT_HS_TYPE_ST
{
    VOS_UINT32      ulHsId;     /*ȡֵ��Χ1~5*/
    DECT_TYPE_E     enHsType;
    DECT_CFG_TYPE_E enConfigType;
    VOS_CHAR    acIPUI[VCE_STR_LEN_64];                       /*InternationalPortableUserIdentity*/
    VOS_CHAR    acIPEI[VCE_STR_LEN_64];                       /*InternationalPortableEquipementIdentity*/
    VOS_CHAR    acRFPIAttachTo[VCE_STR_LEN_32];
    VOS_CHAR    acSubscripTime[VCE_STR_LEN_32];
}DECT_HS_TYPE_ST;
/*LineSettings*/
typedef struct tagDECT_LINE_SET_ST
{
    long long           llEntryId;
    VOS_UINT32          ulChangeList[32];
    ATP_TAB_VOICE_LINESETTING_ST          stInfo;
}DECT_LINE_SET_ST;

/*Dect���÷������ĵ�����*/
typedef enum tagDECT_COMMONCFG_SETTYPE_E_
{
    DECT_SETTYPE_ADD   = 0,       /* ���� */
    DECT_SETTYPE_DEL,             /* ɾ�� */
    DECT_SETTYPE_SET,             /* �޸� */
    DECT_SETTYPE_OTHER,
}DECT_COMMONCFG_SETTYPE_E;

typedef struct tagATP_VOICE_DECTINFO_ST
{
    int          lEntryId;
    int          lListId;
    DECT_COMMONCFG_SETTYPE_E enSetType;    
}ATP_VOICE_DECTINFO_ST;
#endif /* SUPPORT_ATP_DECT_VOICE */

typedef struct tagPHY_CFG_FROM_WEB_ST_
{
    VOS_BOOL    bEnable;                /*�˿��Ƿ�ʹ��*/
    VOS_UINT8   ucPortID;               /*�˿�ID*/
    VOS_UINT8   ucLineID;               /*�ڲ��������кţ���ʼ�����VCE_INCALL_BASE*/
//    VOS_UINT8   ucPortType;             /*�˿�����:FXS��,dect�ӻ�,ISDN���л���,��PORT_TYPE_E*/
    VOS_UINT8   ucDectType;             /*Dect�ӻ�����:0��ʾGAP��1��ʾCATIQ1��2��ʾCATIQ2����DECT_TYPE_E */
    VOS_UINT8   ucInLineNum;            /*��������ʺ���Ŀ*/
    VOS_UINT8   ucOutLineNum;           /*���������ʺ���Ŀ*/
//    VOS_UINT8   ucReserve;
    VOS_BOOL    bInRelateAll;           /*�����������*/
    VOS_BOOL    bOutRelateAuto;         /*�����Զ�ѡ�ʺ�*/
    VOS_UINT8   aucIncomingLine[VCE_LINE_MAX];  /*��������ʺ�. ��Ź����ʺ�����*/
    VOS_UINT8   aucOutgoingLine[VCE_LINE_MAX];  /*���������ʺ�. ��Ź����ʺ�����*/
    VOS_CHAR    szName[VOICE_INCALL_NAME_LEN];       /*�˿���*/
    VOS_CHAR    acIncallNumber[VOICE_INCALL_LEN];/*�ڲ��̺�*/
    VOS_BOOL    bCFUEnable;             /*�˿�������ǰתʹ������*/
    VOS_BOOL    bCFBEnable;             /*�˿���æǰתʹ������*/
    VOS_BOOL    bCFNREnable;            /*�˿���Ӧ��ǰתʹ������*/
    VOS_INT     iCFUDestPortId;         /*������ǰתĿ�Ķ˿ںţ���Χ0~6����ҵ��ʱΪ-1*/
    VOS_INT     iCFBDestPortId;         /*��æĿ�Ķ˿ںţ���Χ0~6����ҵ��ʱΪ-1*/
    VOS_INT     iCFNRDestPortId;        /*��Ӧ��Ŀ�Ķ˿ںţ���Χ0~6����ҵ��ʱΪ-1*/
}PHY_CFG_FROM_WEB_S, *PHY_CFG_FROM_WEB_PS;

typedef struct tagPHONE_BOOK_CFG_FROM_WEB_ST_
{
    VOS_CHAR    szName[SIP_MAX_NAME_LEN];       /*����*/
    VOS_CHAR    szPrivateNum[SIP_MAX_NUM_LEN];  /*˽�˵绰*/
    VOS_CHAR    szFamilyNum[SIP_MAX_NUM_LEN];   /*��ͥ�绰*/
    VOS_CHAR    szMobileNum[SIP_MAX_NUM_LEN];   /*�ƶ��绰*/
}PHONE_BOOK_CFG_FROM_WEB_S, *PHONE_BOOK_CFG_FROM_WEB_PS;

typedef struct tagSIPSERVER_LINE_CFG_ST_
{
    VOS_CHAR    szId[SIP_MAX_NUM_LEN];          /* SIP�ʺ�*/
    VOS_BOOL    bAuth;                          /* �Ƿ���Ҫ��Ȩ*/
    VOS_CHAR    szUserName[SIP_MAX_NAME_LEN];   /* �û���*/
    VOS_CHAR    szPassword[SIP_MAX_PSW_LEN];    /* ����*/
    
    VOS_UINT8   ucInLineNum;                    /* ��������ʺ���Ŀ*/
    VOS_UINT8   ucOutLineNum;                   /* ���������ʺ���Ŀ*/
    VOS_UINT8   ucReserve;
    VOS_BOOL    bInRelateAll;                   /* �����������*/
    VOS_BOOL    bOutRelateAuto;                 /* �����Զ�ѡ�ʺ�*/
    VOS_UINT8   aucIncomingLine[VCE_LINE_MAX];  /* ��������ʺ�. ��Ź����ʺ�����*/
    VOS_UINT8   aucOutgoingLine[VCE_LINE_MAX];  /* ���������ʺ�. ��Ź����ʺ�����*/
    VOS_INT32   iCFUDestPortId;
    VOS_INT32   iCFBDestPortId;
    VOS_INT32   iCFNRDestPortId;
}SIPSERVER_LINE_CFG_S, *SIPSERVER_LINE_CFG_PS;

typedef struct tagSIPSERVER_CFG_FROM_WEB_ST_
{
    VOS_UINT32  ulServerPort;
    VOS_UINT32  ulMinRegExpire;                         /* ע��Expireʱ��,��λs*/
    VOS_UINT32  ulSessExpire;                        /* Session��Updateʱ��,��λs*/
    VOS_UINT32  ulMinSE;                             /* Min-SEʱ��,��λs*/
    SIPSERVER_LINE_CFG_S   stSipServerLine[SIPPHONE_SET_NUM];/*Sip Server֧�ֵ��˺�*/
}SIPSERVER_CFG_FROM_WEB_S, *SIPSERVER_CFG_FROM_WEB_PS;

typedef struct tagROUTE_FIX_CFG_FROM_WEB_ST_
{
    VOS_CHAR    acRouteFix[SIP_MAX_NUM_LEN];        /*·��ǰ��׺*/
    VOS_CHAR    acAccount[SIP_MAX_NUM_LEN];         /*��������*/
    VOS_UINT8   ucType;                             /*��·����,��LINE_TYPE_EN*/
    VOS_UINT8   ucReserve[3];                       /*�����ֽ�*/
}ROUTE_FIX_CFG_FROM_WEB_S, *ROUTE_FIX_CFG_FROM_WEB_PS;

typedef struct tagIN_FIX_CFG_FROM_WEB_ST_
{
    VOS_CHAR    acInFix[SIP_MAX_NUM_LEN];           /*����ǰ��׺*/
}IN_FIX_CFG_FROM_WEB_S, *IN_FIX_CFG_FROM_WEB_PS;

typedef struct tagOUT_FIX_CFG_FROM_WEB_ST_
{
    VOS_CHAR    acOutFix[SIP_MAX_NUM_LEN];          /*����ǰ��׺*/
    VOS_CHAR    acNumber[SIP_MAX_NUM_LEN];          /*��������*/
}OUT_FIX_CFG_FROM_WEB_S, *OUT_FIX_CFG_FROM_WEB_PS;

typedef struct tagSPEEDDIAL_CFG_FROM_WEB_ST_
{
    VOS_CHAR    acSrcNumber[SIP_MAX_NUM_LEN];       /*��λ����*/
    VOS_CHAR    acDstNumber[SIP_MAX_NUM_LEN];       /*ʵ�ʺ���*/
}SPEEDDIAL_CFG_FROM_WEB_S, *SPEEDDIAL_CFG_FROM_WEB_PS;

typedef struct tagWAKEUP_CFG_FROM_WEB_ST_
{   
    VOS_BOOL     bEnable;                          /*����ʹ��*/
    VOS_UINT32   ulTime;                          /*����ʱ��*/
    VOS_CHAR     szWeekDay[VCE_STR_LEN_64];          /*��������*/
    VOS_CHAR     szName[VCE_WAKEUP_NAME_LEN];          /*�������� */
}WAKEUP_CFG_FROM_WEB_S, *WAKEUP_CFG_FROM_WEB_PS;

typedef struct tagRINGSCHEDULE_CFG_FROM_WEB_ST_
{   
    VOS_UINT32     ulStartTime;          /*RingSchedule��ʼʱ��*/
    VOS_UINT32     ulEndTime;          /*RingSchedule����ʱ��*/
}RINGSCHEDULE_CFG_FROM_WEB_S, *RINGSCHEDULE_CFG_FROM_WEB_PS;

typedef struct tagVOICE_SVC_CFG_FROM_WEB_ST_
{
    GLOBAL_CFG_FROM_WEB_S       stGlobal;                   /*����ҵ��ȫ������*/
    LINE_CFG_FROM_WEB_S         stLine[VCE_VOIP_MAX];       /*SIP�ʺ�����*/
    ISDN_LINE_CFG_FROM_WEB_S    stIsdnLine[VCE_ISDN_MAX]; /*ISDN�ʺ�����,*/
    ISDN_LINE_CFG_FROM_WEB_S    stIsdnDft; 					/*Ĭ��ISDN�ʺ�����,*/
#ifdef SUPPORT_ATP_DECT_VOICE
    DECT_CFG_FROM_WEB_S         stDect;                     /*DECTȫ������*/
    PHY_CFG_FROM_WEB_S          stPhy[VCE_PORT_MAX];        /*FXS������*/
#else
    PHY_CFG_FROM_WEB_S          stPhy[POTS_SET_NUM];        /*FXS������*/
#endif
#ifdef SUPPORT_ATP_SIP_SERVER
    SIPSERVER_CFG_FROM_WEB_S    stSipServer;                /*SipServer����*/
#endif
    ROUTE_FIX_CFG_FROM_WEB_S    stRouteFix[VCE_ROUTE_PREFIX_MAX];
    ROUTE_FIX_CFG_FROM_WEB_S    stDialPreFix[VCE_DIAL_PREFIX_MAX];
    IN_FIX_CFG_FROM_WEB_S       stUrgeLine[VCE_URG_LINE_MAX];
    IN_FIX_CFG_FROM_WEB_S       stInPrefix[VCE_IN_PREFIX_MAX];
    IN_FIX_CFG_FROM_WEB_S       stInSuffix[VCE_IN_SUFFIX_MAX];
    OUT_FIX_CFG_FROM_WEB_S      stOutPrefix[VCE_OUT_PREFIX_MAX];
    OUT_FIX_CFG_FROM_WEB_S      stOutSuffix[VCE_OUT_SUFFIX_MAX];
    SPEEDDIAL_CFG_FROM_WEB_S    stSpeedDial[VCE_SPEEDDAIL_MAX];
    WAKEUP_CFG_FROM_WEB_S       stWakeUp[VCE_WAKEUP_MAX];
    RINGSCHEDULE_CFG_FROM_WEB_S stRingSchedule[VCE_RINGSCHEDULE_MAX];
}VOICE_SVC_CFG_S, *VOICE_SVC_CFG_PS;

#ifdef SUPPORT_ATP_DECT_VOICE
typedef struct tagDECT_EEPROM_ST
{
    VOS_UINT32  ulOffset;
    VOS_UINT32  ulLen;
    VOS_CHAR    acValue[128];
}DECT_EEPROM_ST;

typedef struct tagDECT_MWI_ST
{
    VOS_UINT32  ulLineID;
    VOS_UINT32  ulMsgNum;
}DECT_MWI_ST;

typedef struct tagDECT_CMBS_LINE_TYPE_ST
{
    VOS_UINT32  ulLineID;
    VOS_UINT32  ulType;
}DECT_CMBS_LINE_TYPE_ST;

typedef struct tagDECT_EEPSUB_ST
{
    VOS_CHAR    acRFPI[12];
    VOS_CHAR    ucHsNr[4];
    VOS_CHAR    acSubInfo[84];
}DECT_EEPSUB_ST;

typedef struct tagDECT_EQUIP_ST
{
    VOS_CHAR    acValue[100];
}DECT_EQUIP_ST;

typedef enum
{
    DECT_LOCATE_UNKNOW = 0,
    DECT_LOCATE_WEB_EN,
    DECT_LOCATE_BUTTON_EN,
}DECT_LOCATE_METHOD_EN;

/*�ӻ�������Ϣ�ṹ��*/
typedef struct tagDECT_LOCATE_ST
{
    VOS_UINT32	ulHsMask;
    VOS_UINT32	ulStatus;
	VOS_UINT32	ulMethod;
    VOS_CHAR   acReserved[VCE_STR_LEN_16];
}DECT_LOCATE_ST;

typedef struct tagDECT_CMBS_LINE_CF_ST
{
    VOS_UINT32  ulLineID;
    VOS_UINT32  ulType;                   /*0:CFU;1:CFB;2:CFNR*/
    char acActiveCode[VCE_STR_LEN_32];    /*Activation code number*/
    char acDeactiveCode[VCE_STR_LEN_32];  /*Deactivation code number*/
}DECT_CMBS_LINE_CF_ST;


#define CMBS_MAX_VERSION_LENGTH 20

typedef struct tagDECT_INFO_ST
{
     VOS_UINT32 ulHandsetFlag;
     VOS_CHAR acHandsetHardwareVer[CMBS_MAX_VERSION_LENGTH]; 
     VOS_CHAR acHandsetSoftwareVer[CMBS_MAX_VERSION_LENGTH]; 
     VOS_CHAR acLastUPTime[VCE_STR_LEN_64]; 
}DECT_INFO_ST;
typedef struct tagDECT_JUDGELEVEL_LISTID
{
	VOS_UINT32	ulLevelListId;

}DECT_JUDGELEVEL_LISTID;
#endif

extern VOICE_SVC_CFG_PS g_pstVoiceServiceCfg;
/*************************  END: VOICE_LIB  *************************/




/*************************  BEGIN: VOICE_STATE  *************************/
#define VOICE_STATUS_DIR            "/var/voice"
#define VOICE_STATUS_FILENAME       "status"
#define FILE_PATH_PORT_STATUS       "/var/voice/portstatus"
#define FILE_PATH_VOIP_STATUS       "/var/voice/voipstatus"
#define FILE_PATH_URGCALL_STATUS    "/var/voice/urgcallstatus"
#define FILE_PATH_DECT_UPGIMAGE     "/var/voice/dectimage"
#define FILE_PATH_DECT_CMBS_LOG     "/var/voice/dectLog"
#define FILE_PATH_DECT_CMBS_TRACE   "/var/voice/dectTrace"
#define FILE_PATH_DECT_TMPVALUE     "/var/voice/decttmpvalue"
#define FILE_PATH_DECT_UPDATE     "/var/voice/dectupdate"
#define FILE_PATH_DECT_SUBINFO      "/var/voice/dectsubinfo"
#define FILE_PATH_DECT_SUBINFOSTAT  "/var/voice/dectsubinfostat"
#define FILE_PATH_DECT_BASE_VER     "/var/voice/dectbaseversion"
#define FILE_PATH_DECT_PCM_RESULT   "/var/voice/pcmresult"
#define FILE_PATH_DECT_BARCODE      "/var/voice/dectbarcode"
#define FILE_PATH_DECT_EFPI         "/var/voice/dectrfpi"

#define VOICE_STATUS_LEN_MAX        (16)

/* rfpi code (10) + hs Nr (2) + subscribe info (80) */

#define VOICE_DECT_RFPI_LEN         (10)
#define VOICE_DECT_HSNR_LEN         (2)
#define VOICE_DECT_SUBINFO_LEN      (80)

#define VOICE_DECT_SUBINFO_LEN_ALL  (400)
#define VOICE_DECT_SUBINFO_TOTAL_LEN  (VOICE_DECT_RFPI_LEN + VOICE_DECT_SUBINFO_LEN)
#define VOICE_DECT_BARCODE_LEN      (16)

#define LINE_CALL_STATUS_STR_IDLE               "Idle"
#define LINE_CALL_STATUS_STR_CALLING            "Calling"
#define LINE_CALL_STATUS_STR_RINGING            "Ringing"
#define LINE_CALL_STATUS_STR_CONNECTING         "Connecting"
#define LINE_CALL_STATUS_STR_INCALL             "InCall"
#define LINE_CALL_STATUS_STR_HOLD               "Hold"
#define LINE_CALL_STATUS_STR_DISCONNECTING      "Disconnecting"
#define LINE_CALL_STATUS_STR_BUSY				"Busy"

/*HG253s V2��������:�˿�״̬��ʾ*/
#define PORT_STATUS_STR_DISABLED                "Disabled"
#define PORT_STATUS_STR_ENABLED                 "Enabled"
#define PORT_STATUS_STR_ONHOOK                  "On Hook"
#define PORT_STATUS_STR_OFFHOOK                 "Off Hook"
#define PORT_STATUS_STR_WAITONHOOK              "WaitonHook"
#define PORT_STATUS_STR_CALLING                 "Calling"
#define PORT_STATUS_STR_RINGING                 "Ringing"
#define PORT_STATUS_STR_TALKING                 "Talking"

#define CALL_CALLFEATURES_STATUS_STR_DISABLE    "Disabled"
#define CALL_CALLFEATURES_STATUS_STR_IDLE       "Idle"
#define CALL_CALLFEATURES_STATUS_STR_RINGING    "SecondaryRinging"
#define CALL_CALLFEATURES_STATUS_STR_CALLING    "SecondaryCalling"
#define CALL_CALLFEATURES_STATUS_STR_CONNECTING "SecondaryConnecting"
#define CALL_CALLFEATURES_STATUS_STR_CONNECTED  "SecondaryConnected"              
#define CALL_CALLFEATURES_STATUS_STR_CALL       "InConferenceCall"              

/*ǰת����*/
typedef enum tagVOICE_CF_TYPE_EN
{
    VOICE_CF_CFU          = 0,
    VOICE_CF_CFB          = 1,
    VOICE_CF_CFNR         = 2,
}VOICE_CF_TYPE_EN;

typedef enum tagVOICE_CALLFEATURES_TYPE_EN
{
    VOICE_CALLFEATURES_CW        = 0,
    VOICE_CALLFEATURES_CONF      = 1,
}VOICE_CALLFEATURES_TYPE_EN;

typedef enum tagVOICE_CALLFEATURE_STATUS_TYPE_EN
{
	VOICE_CALLFEATURES_STATE_DISABLE  = 1,					/*Disabled*/
	VOICE_CALLFEATURES_STATE_IDLE,						    /*Idle*/
    VOICE_CALLFEATURES_SECONDARY_RINGING,                   /*SecondaryRinging*/
    VOICE_CALLFEATURES_SECONDARY_CALLING,				    /*SecondaryCalling*/
	VOICE_CALLFEATURES_SECONDARY_CONNECTING,              	/*SecondaryConnecting*/
	VOICE_CALLFEATURES_SECONDARY_CONNECTED,                 /*SecondaryConnected*/
	VOICE_CALLFEATURES_CONFERENCE_CALL,                     /*InConferenceCall*/
}VOICE_CALLFEATURE_STATUS_TYPE_EN;

/*����ǰת��Ϣ�ṹ*/
typedef struct tagATP_VOICE_CFINFO_ST
{
    VOS_INT    iSrcPortId;
    VOS_INT    iDstPortId;
    VOICE_CF_TYPE_EN enCFType;
} ATP_VOICE_CFINFO_ST;


typedef struct tagVOICE_CFG_FROM_CLI_ST_
{
    VOS_UINT32  ulEventType;          /*�¼����ͣ���Ҫ���õĲ�������*/
    VOS_UINT32  ulProfileInst;        /*��profileʵ����*/
    VOS_UINT32  ulLineInst;           /*lineʵ����*/
    VOS_UINT32  ulPara;                                         
    VOS_CHAR    szMsgData[VCE_STR_LEN_256];             
}VOICE_CFG_FROM_CLI_S;

/*�Ự��Ϣ*/
typedef struct tagSESSION_STATE_ST_
{   
    VOS_UINT32      ulStartYear;
    VOS_UINT32      ulStartMonth;
    VOS_UINT32      ulStartDay;
    VOS_UINT32      ulStartHour;
    VOS_UINT32      ulStartMinute;
    VOS_UINT32      ulStartSecond;
    VOS_UINT32      ulStartTime;                            /*��ʼʱ��*/
    VOS_UINT32      ulEndTime;                              /*����ʱ��,���Ϊ0,��ʾ��δ����*/

    VOS_UINT32      ulDuration;                             /*ͨ��ʱ��*/
    VOS_UINT32      ulFarEndIP;                             /*Զ�˵�ַ*/
    VOS_UINT16      uwFarEndUDPPort;                        /*Զ��RTP�˿�*/
    VOS_UINT16      uwLocalUDPPort;                         /*����RTP�˿�*/
}SESSION_STATE_S, *SESSION_STATE_PS;


/*RTCP��Ϣͳ��*/
typedef struct tagRTCP_INFO_ST_
{
    VOS_UINT32  ulPacketsSent;                          /*�ѷ��ͱ��ĸ���*/
    VOS_UINT32  ulPacketsReceived;                      /*�ѽ��ձ��ĸ���*/
    VOS_UINT32  ulBytesSent;                            /*�ѷ��ͱ����ֽ���*/
    VOS_UINT32  ulBytesReceived;                        /*�ѽ��ձ����ֽ���*/
    VOS_UINT32  ulPacketsLost;                          /*�Ѷ�ʧ���ĸ���*/

    /*Total number of times the receive jitter buffer has overrun for this line*/
    VOS_UINT32  ulOverruns;                             /*����������Χ��ı��ĸ���*/

    /*Total number of times the receive jitter buffer has underrun for this line*/
    VOS_UINT32  ulUnderruns;                            /*������Χ�ڵı��ĸ���*/

    /*Current receive packet loss rate in percent*/
    VOS_UINT32  ulReceivePacketLossRate;                /*���˶�����*/

    /*Current far end receive packet lost rate in percent*/
    VOS_UINT32  ulFarEndPacketLossRate;                 /*Զ�˶�����*/

    /*Current receive interarrival jitter in microseconds*/
    VOS_UINT32  ulReceiveInterarrivalJitter;            /*���˶���ʱ����*/

    /*Current Interarrival jitter in microseconds as reported from the far-end device via RTCP*/
    VOS_UINT32  ulFarEndInterarrivalJitter;             /*Զ�˶���ʱ����*/

    /*Current round trip delay in microseconds*/
    VOS_UINT32  ulRoundTripDelay;                       /*�����ӳ�[RFC3550 6.4]*/

    /*Average receive interarrival jitter in microseconds since the beginning of the current call*/
    VOS_UINT32  ulAverageReceiveInterarrivalJitter;     /*����ƽ������ʱ����*/

    /*Average far-end interarrival jitter in microseconds since the beginning of the current call*/
    VOS_UINT32  ulAverageFarEndInterarrivalJitter;      /*Զ��ƽ������ʱ����*/

    /*Average round trip delay in microseconds since the beginning of the current call*/
    VOS_UINT32  ulAverageRoundTripDelay;                /*ƽ�������ӳ�*/
}RTCP_INFO_ST;

/*IMS����ҵ����ʾ*/
typedef struct tagSIP_MSG_SIMSERVS_ST_
{
    VOS_UINT8   ucMcidFlag;  				/* mcid-service */
    VOS_UINT8   ucHoldFlag;  				/* hold-service */
    VOS_UINT8   ucConferenceFlag;  		    /* three-party-service */
    VOS_UINT8   ucCwFlag;  				    /* cw-service */
    VOS_UINT8   ucDialTonePattern;  		/* dial-tone-pattern DIAL_TONE_PATTERN_E */
    VOS_UINT8   ucNoDialingBehaviour;  		/* no-dialing-behaviour NO_DIALING_BEHAVIOUR_E */
    VOS_UINT8   szConferenceUri[128];  		/* conference-uri */
}SIP_MSG_SIMSERVS_ST;


/*�ʺ�״̬*/
typedef struct tagLINE_STATE_ST_
{
    VOS_CHAR        szId[SIP_MAX_NUM_LEN];                  /*Line�ʺ�*/
    VOS_CHAR        szCallStatus[VCE_STR_LEN_16];   
    VOS_UINT8       ucRegStatus;                            /*����ע��״̬*/
    VOS_UINT8       ucRegFailReason;                        /*ע��ʧ��ԭ��*/

    VOS_UINT32      ulCallDir;

    VOS_UINT32      ulReadyFlag;                            /*��Ϣ�Ƿ�Ready�ı�־λ*/
    VOS_BOOL        bResetStatistics;                       /*�Ƿ����ͳ��*/
    VOS_UINT32      ulIncomingReceived;                     /*����绰����*/
    VOS_UINT32      ulIncomingAnswered;                     /*�����ѽӵ绰����*/
    VOS_UINT32      ulIncomingConnected;                    /*����ɹ��绰����*/
    VOS_UINT32      ulIncomingFailed;                       /*����ʧ�ܵ绰����*/
    VOS_UINT32      ulOutgoingAttempted;                    /*�����绰����*/
    VOS_UINT32      ulOutgoingAnswered;                     /*�����ѽӵ绰����*/
    VOS_UINT32      ulOutgoingConnected;                    /*�����ɹ��绰����*/
    VOS_UINT32      ulOutgoingFailed;                       /*����ʧ�ܵ绰����*/
    VOS_UINT32      ulCallsDropped;                         /*ͨ���������жϸ���*/
    VOS_UINT32      ulTotalCallTime;
	VOS_UINT32      ulMWINum;                               /*MWI��Ŀ*/

    VOS_UINT32      ulSrvDownStartTime;                      /*һ�η�����DOWN�Ŀ�ʼʱ�䣬���Ϊע�᲻�ϵ�ʱ��*/
    VOS_UINT32      ulAccumSrvDownTime;                     /*��һ�λָ�ע��ʱ�ۻ���DOWNʱ��*/
    VOS_UINT32      ulSeverDownTime;                        /*�˺�ע�᲻�ϵ��ۻ�ʱ��*/

    /*HG253s V2�����Ự�����б����ڵ���ʾ����*/
    VOS_UINT32      ulTransmitCodec;                        /*��������ͨ��ʱ�ı����*/
    VOS_UINT32      ulReceiveCodec;                         /*���뽨��ͨ��ʱ�ı����*/

    SESSION_STATE_S stSession[SIP_LINE_STATE_SESS_MAX];     /*�ʺ�����ĺ�����Ϣ*/
    
    RTCP_INFO_ST    stRtcp;                                 /*RTCPͳ����Ϣ*/
    SIP_MSG_SIMSERVS_ST  stSimServs;                        /*IMS������Ϣ*/

    VOS_UINT8       ucCWState;                              /*����ҵ�����״̬*/      
    VOS_UINT8       ucConfState;                            /*����ҵ������ͨ��״̬*/ 
}LINE_STATE_S, *LINE_STATE_PS;

typedef struct tagSIPSERVER_LINE_STATE_ST_
{
    VOS_UINT8       ucRegStatus;                            /*����ע��״̬*/
}SIPSERVER_LINE_STATE_S, *SIPSERVER_LINE_STATE_PS;

typedef struct tagVOICE_DIAGNOSIS_OBJ
{
    VOS_UINT32  ulDiagnosisResult;                                  /* ��Ͻ�� */
}VOICE_DIAGNOSIS_INFO_ST;



/*PhyInterface state*/
typedef struct tagPHY_STATE_ST_
{
    VOS_BOOL    bBusy;                                  /*�˿��Ƿ�����ʹ��*/
    VOS_BOOL    bCFType;                                /*ǰת����*/
    VOS_CHAR    szCFNum[SIP_MAX_NUM_LEN];               /*ǰת����*/    
    /*HG253s V2��������:�˿�״̬��ʾ*/
    VOS_CHAR    szPortStatus[VCE_STR_LEN_16];           /*�˿�״̬*/
    VOS_UINT32  ulReadyFlag;                            /*��Ϣ�Ƿ�Ready�ı�־λ*/    
}PHY_STATE_S, *PHY_STATE_PS;

typedef struct tagSIP_INFO_ST_
{
    VOS_CHAR    szId[SIP_MAX_NUM_LEN];                  /*VoIP�ʺ�*/
}SIP_INFO_S, *SIP_INFO_PS;

typedef struct tagGLOBAL_STATE_ST_
{
    VOS_BOOL    bPortBusy;                              /*�Ƿ��ж˿�����ʹ��*/
    VOS_BOOL    bLineCallBusy;                          /*�Ƿ�����·���ڽ�������ͨ��*/
    VOS_BOOL    bHasUrgCall;                            /*�Ƿ���ڽ�������*/
    VOS_BOOL    bHasUseableLine;                        /*�Ƿ���ڿ����ʺ�*/
    VOS_UINT32  ulFxoStatus;                            /*FXO��״̬:ISDN UP;PSTN UP;fail*/
    VOS_UINT32  ulDectStatus;                            /*FXO��״̬:ISDN UP;PSTN UP;fail*/
    VOS_UINT32  ulRegExpire;                            /*ע��ˢ��ʱ��*/
	VOS_UINT32  ulCsLinkStatus;                         /*CS status*/
    VOS_UINT32  ulCsCallStatus;                         /*CS Call status*/
    VOS_UINT32  ulLclIpAddr;                            /*0��ʾδ���Ϻ�*/
}GLOBAL_STATE_S, *GLOBAL_STATE_PS;

typedef struct tagISDN_AUTO_ST_
{
    VOS_CHAR    szNumber[SIP_MAX_NUM_LEN];              /*ISDN����*/
    
}ISDN_AUTO_S, *ISDN_AUTO_PS;

typedef struct tagVOICE_STATE_ST_
{
    GLOBAL_STATE_S  stGlobal;                           /*ȫ��״̬��Ϣ*/
    LINE_STATE_S    stLine[VCE_LINE_MAX];               /*�ʺ�״̬��Ϣ*/
    PHY_STATE_S     stPort[VCE_PORT_MAX];               /*�˿�״̬��Ϣ*/
    ISDN_AUTO_S     stAutoIsdn[VCE_ISDN_MAX];           /*�Զ���ȡISDN����*/
    SIPSERVER_LINE_STATE_S stServerLine[SIPPHONE_SET_NUM];/*Sip�����˺�״̬*/
    VOICE_DIAGNOSIS_INFO_ST     stDiagnosis;            /* slic �����Ϣ */
#ifdef SUPPORT_ATP_DECT_VOICE
    VOS_BOOL        bAnt0IsOn;                           /* ��¼����0��״̬*/
    VOS_BOOL        bAnt1IsOn;                           /* ��¼����1��״̬*/
#endif	
}VOICE_STATE_S, *VOICE_STATE_PS;

extern VOICE_STATE_PS g_pstVoiceState;

/*************************  END: VOICE_STATE  *************************/




/*************************  BEGIN: TAPI_CMS  *************************/
/* ��Ϣ����дȨ�� */
#define VHG_VOICE_MSG_W             01
#define VHG_VOICE_CMD_MSG_TYPE      8849
#define VHG_VOICE_CMS_MSGKEY        'V'
#define VHG_VOICE_PID_PATH          "/var/vhgvpid"

/*��Ϣ������*/
typedef enum tagVHG_VOICE_MSG_TYPE_E
{
    VHG_MSG_TYPE_CMS,                       /*��Ʒ����ҵ��������Ϣ*/
    VHG_MSG_TYPE_TIMER,                     /*timer��Ϣ*/
    VHG_MSG_TYPE_BUTT
}VHG_VOICE_MSG_TYPE_E;

/* �����л����ù����͵�ָʾ */
typedef enum tagVHG_VOICE_CMS_MSG_TYPE_E
{
	VHG_VOICE_CMS_MSG_UPDATA_CONFIG,
    VHG_VOICE_CMS_MSG_UNKNOWN
}VHG_VOICE_CMS_MSG_TYPE_E;

/* ���ò������� (���ù������) */
typedef enum tagVHG_VOICE_CMS_MSG_CMO_E
{
	VHG_VOICE_CMS_MSG_VOICEPROFILE,
    VHG_VOICE_CMS_MSG_RTP,
    VHG_VOICE_CMS_MSG_VOICEPROCESSING,
    VHG_VOICE_CMS_MSG_CODEC,
    VHG_VOICE_CMS_MSG_CODECLIST
}VHG_VOICE_CMS_MSG_CMO_E;

/*ȫ�ֲ���*/
typedef struct
{
    /*voice profile����Ĳ���*/
    VOS_UINT32  ulRegion;	                /*����REGION_CODING_E*/

    /*RTP����Ĳ���*/
    VOS_UINT32  ulLclRTPPortMin;            /*��СRTP�˿�*/
    VOS_UINT32  ulLclRTPPortMax;            /*���RTP�˿�*/
    VOS_BOOL    bJitterBuffer;              /*�Ƿ����ö�������*/
    VOS_UINT32  ulJBLength;                 /*JitterBuffer����*/
    VOS_BOOL    bPackLostCompensate;        /*�Ƿ����ö�������*/
    VOS_UINT32  ulJBType;                   /*JitterBuffer����JB_TYPE_E*/

    /*VoiceProcessing����Ĳ���*/
    VOS_INT32	lTransmitGain;              /*��Ͳ����*/
    VOS_INT32	lReceiveGain;               /*��Ͳ����*/

    /*RTCP����Ĳ���*/
    VOS_UINT32  ulRtcpTxRepeatInterval;         /*RTCP������ʱ����*/

    /*HG253s V2��������Ҫ��ʵ��:RTP��DSCPmark*/
    VOS_UINT32  ulRTPDSCPMark;                 /*DSCPMarkֵ*/  
    
    /*HG253s V2��������Ҫ��ʵ��:RFC2833Payloadֵ��������*/
    VOS_UINT32  ulDTMF2833PayloadType;         /*RFC2833Payloadֵ*/

     VOS_UINT32  ulxrinterval;
     VOS_UINT32  ulxropt;    
}TAPI_GLOBAL_S;

/*Codec����*/
typedef struct
{
    VOS_UINT32  ulCodecName;                     /*��������ͣ���ATP_CODEC_NAME_E*/
    VOS_BOOL    bSilence;                   /*�Ƿ�������������*/
    VOS_UINT32  ulPacketPeriod;             /*���ʱ��10/20/30ms,��PACK_TIME_E*/
}TAPI_CODEC_S;

/*�ʺŲ���*/
typedef struct
{
    VOS_BOOL        bECEnable;              /*�Ƿ����ûز�����*/
    VOS_UINT32      ulDTMFMethod;           /* DTMF���ݵĴ��䷽��DTMF_TYPE_E
                                             0:Inband
                                             1:RFC 2833
                                             2:SIP Info*/
    VOS_UINT32      ulFaxOption;            /*For Test, Will remove Later*/
    VOS_UINT32      ulFaxOptionArray[VOICE_TAPI_FAXTYPEMAX];
                                            /*�������ͣ��弶����*/
	VOS_UINT32		ulFaxDetectType;		/* 0: Disable; 
											   1: Terminating
											   2: Originating
											   3: Both*/
    /*HG253s V2�޸��������:CNG�����޸�*/
    VOS_BOOL        bCNGEnable;             /*�Ƿ�����������������,Ŀǰֻ��bcm96362оƬ֧������*/											   
    TAPI_CODEC_S    stCodec[VCE_CODEC_MAX]; /*������б�*/
    VOS_BOOL        bT38Enable;             /*HG253s V2����T38ʹ�ܽڵ㹦��ʵ��*/
}TAPI_LINE_S;

/*��������*/
typedef struct
{
    TAPI_GLOBAL_S   stGlobal;               /*ȫ�ֲ���*/
    TAPI_LINE_S     stLine[VCE_VOIP_MAX];   /*VoIP�ʺŲ���*/
}TAPI_CMS_S, *TAPI_CMS_PS;

/* CMS message */
typedef struct VHG_VOICE_CMS_MSG
{
    VHG_VOICE_CMS_MSG_TYPE_E  lEventType;   /*���ò�������,��VHG_VOICE_CMS_MSG_TYPE_E*/
    VOS_UINT32                ulCMDHead;    /*���ò�������*/
    VHG_VOICE_CMS_MSG_CMO_E   lCMDBody;     /*���ò�������*/
}VHG_VCMS_MSG_ST;

typedef struct VHG_VCMS_MSG
{
    VHG_VOICE_MSG_TYPE_E eMsgType;          /*��Ϣ���ͣ��������������Ƿ���������Ϣ,��VHG_VOICE_MSG_TYPE_E*/
    VHG_VCMS_MSG_ST      CMSMsg;            /*�����������Ϣʱ������������Ϣ������*/
} VHG_VOICE_MSG_ST;

typedef struct VHG_VCMS_MSG_BUFF
{
    VOS_INT32         mtype;                /* ��Ϣ���� ,�����ж��Ƿ��ǲ�Ʒ����ҵ����Ϣ*/
    VHG_VOICE_MSG_ST  stVoiceMsg;           /* ��Ϣ���� */
}VHG_VOICE_MSG_BUFF_ST;

#ifdef SUPPORT_ATP_DECT_VOICE
#define	DECT_NAME_MAX_LEN			64
typedef struct tagDECT_NAME_UPDATE
{
	VOS_UINT32	ulDectIndex;
	VOS_CHAR	acDectName[DECT_NAME_MAX_LEN];
}DECT_NAME_UPDATE;

/*RSS RESPONSE*/
typedef struct tagATP_VOICE_RSSRESPONSE_ST
{
    VOS_UINT32  ulIdx;
	VOS_CHAR    acSessinList[VCE_STR_LEN_256];
} ATP_VOICE_RSSRESPONSE_ST;

/*RSS MSG*/
typedef struct tagATP_RSSRead_MSG_ST
{
    VOS_UINT32  ulStartId;
	VOS_UINT32  ulCount;
	VOS_UINT32  ulSessionId;
}ATP_RSSRead_MSG_ST;
#endif

typedef enum	tagATP_CODEC_NAME_E
{
	/* AUDIO */
	ATP_CODEC_NAME_NULL			= (0),		  /* NULL */
	ATP_CODEC_NAME_PCMU,	 /* G.711 ulaw */
	ATP_CODEC_NAME_PCMA,	 /* G.711 alaw */
	ATP_CODEC_NAME_G726_16,	/* G.726 - 16 kbps */
	ATP_CODEC_NAME_G726_24,	/* G.726 - 24 kbps */
	ATP_CODEC_NAME_G726_32,	/* G.726 - 32 kbps */
	ATP_CODEC_NAME_G726_40,	/* G.726 - 40 kbps */
	ATP_CODEC_NAME_G723,
	ATP_CODEC_NAME_G7231_53 = ATP_CODEC_NAME_G723,	 /* G.723.1 - 5.3 kbps */
	ATP_CODEC_NAME_G7231_63,	 /* G.723.1 - 6.3 kbps */
	ATP_CODEC_NAME_G7231A_53,   /* G.723.1A - 5.3 kbps */
	ATP_CODEC_NAME_G7231A_63,   /* G.723.1A - 6.3 kbps */
	ATP_CODEC_NAME_G729A,  /* G.729A */
	ATP_CODEC_NAME_G729B,  /* G.729B */
	ATP_CODEC_NAME_G711_LINEAR,  /* Linear media queue data */
	ATP_CODEC_NAME_G728,	/* G.728 */
	ATP_CODEC_NAME_G729,	/* G.729 */
	ATP_CODEC_NAME_G729D,
	ATP_CODEC_NAME_G729E,  /* G.729E */
	ATP_CODEC_NAME_BV16,	/* BRCM Broadvoice - 16 kbps */
	ATP_CODEC_NAME_BV32,	/* BRCM Broadvoice - 32 kbps */
	ATP_CODEC_NAME_NTE,  /* Named telephone events */
	ATP_CODEC_NAME_ILBC_20,  /* iLBC speech coder - 20 ms frame / 15.2 kbps */
	ATP_CODEC_NAME_ILBC_30,  /* iLBC speech coder - 30 ms frame / 13.3 kbps */
	ATP_CODEC_NAME_G7231_53_VAR, /* G723.1 variable rates (preferred=5.3) */
	ATP_CODEC_NAME_G7231_63_VAR, /* G723.1 variable rates (preferred=6.3) */
	ATP_CODEC_NAME_G7231_VAR, /* G723.1 variable rates */
	ATP_CODEC_NAME_T38,  /* T.38 fax relay */
	ATP_CODEC_NAME_T38_MUTE,	/* Mute before switching to T.38 fax relay */
	ATP_CODEC_NAME_RED,  /* Redundancy - RFC 2198 */
	ATP_CODEC_NAME_G722,  /* G.722 Mode 1 64 kbps */
	ATP_CODEC_NAME_LINPCM128,  /* Narrowband linear PCM @ 128 Kbps */
	ATP_CODEC_NAME_LINPCM256,  /* Wideband linear PCM @ 256 Kbps */
	
	ATP_CODEC_NAME_GSMAMR_12K,  /* GSM AMR codec @ 12.2 kbps */
	ATP_CODEC_NAME_GSMAMR_10K,  /* GSM AMR codec @ 10.2 kbps */
	ATP_CODEC_NAME_GSMAMR_795,  /* GSM AMR codec @ 7.95 kbps */
	ATP_CODEC_NAME_GSMAMR_740,  /* GSM AMR codec @ 7.4 kbps */
	ATP_CODEC_NAME_GSMAMR_670,  /* GSM AMR codec @ 6.7 kbps */
	ATP_CODEC_NAME_GSMAMR_590,  /* GSM AMR codec @ 5.9 kbps */
	ATP_CODEC_NAME_GSMAMR_515,  /* GSM AMR codec @ 5.15 kbps */
	ATP_CODEC_NAME_GSMAMR_475,  /* GSM AMR codec @ 4.75 kbps */

	ATP_CODEC_NAME_AMRWB_660,	  /* AMR WB codec @ 6.6 kbps */
	ATP_CODEC_NAME_AMRWB_885,   /* AMR WB codec @ 8.85 kbps */
	ATP_CODEC_NAME_AMRWB_1265,  /* AMR WB codec @ 12.65 kbps */
	ATP_CODEC_NAME_AMRWB_1425,  /* AMR WB codec @ 14.25 kbps */
	ATP_CODEC_NAME_AMRWB_1585,  /* AMR WB codec @ 15.85 kbps */
	ATP_CODEC_NAME_AMRWB_1825,  /* AMR WB codec @ 18.25 kbps */
	ATP_CODEC_NAME_AMRWB_1985,  /* AMR WB codec @ 19.85 kbps */
	ATP_CODEC_NAME_AMRWB_2305,  /* AMR WB codec @ 23.05 kbps */
	ATP_CODEC_NAME_AMRWB_2385,  /* AMR WB codec @ 23.85 kbps */

	ATP_CODEC_NAME_PCMA_VBD,
	ATP_CODEC_NAME_PCMU_VBD,

	ATP_CODEC_NAME_GSM,
	ATP_CODEC_NAME_GSM_EFR,
	ATP_CODEC_NAME_DVI4,
	ATP_CODEC_NAME_LPC,
	ATP_CODEC_NAME_L8,
	ATP_CODEC_NAME_L16,
	ATP_CODEC_NAME_QCELP,
	ATP_CODEC_NAME_CN,
	ATP_CODEC_NAME_MPA,
	ATP_CODEC_NAME_VDVI,

	/*VIDEO*/
	ATP_CODEC_NAME_CELB,
	ATP_CODEC_NAME_JPEG,
	ATP_CODEC_NAME_NV,
	ATP_CODEC_NAME_H261,
	ATP_CODEC_NAME_MPV,
	ATP_CODEC_NAME_MP2T,
	ATP_CODEC_NAME_H263,
	ATP_CODEC_NAME_H263_1998,
	
	
	/* Maximum number of codec types. */
	ATP_CODEC_NAME_MAX_TYPES,

	/* Place-holder for dynamic codec types that haven't been mapped yet */
	ATP_CODEC_NAME_DYNAMIC		= (0xffff),

	/* Place-holder for unknown codec types that should be ignored/removed from list */
	ATP_CODEC_NAME_UNKNOWN		= (0xfffe)
}ATP_CODEC_NAME_E;

extern TAPI_CMS_PS g_pstVoiceTapiCfg;
/*************************  END: TAPI_CMS  *************************/



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __VOICEPUB_H__ */

