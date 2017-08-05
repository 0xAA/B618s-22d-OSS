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
 
#ifndef __VOICE_W723V_H__
#define __VOICE_W723V_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "atptypes.h"

/*�ʺ�֧������*/
#define VCE_VOIP_MAX                16      /*���֧�ֵ�VoIP�ʺŸ���*/
#define VCE_ISDN_MAX                10      /*���֧�ֵ�ISDN�ʺŸ���*/
#define VCE_PSTN_MAX                1       /*���֧�ֵ�PSTN�ʺŸ���*/
#define VCE_CS_MAX                  1       /*���֧�ֵ�CS�ʺŸ���*/

#define VCE_LINE_MAX (VCE_VOIP_MAX + VCE_ISDN_MAX + VCE_PSTN_MAX + VCE_CS_MAX) /*���֧�ֵ��ʺŸ���*/

/*�˿ڱ�ţ������޸�*/
#define VCE_UE_POTS_MIN             0           /* POTS�������0 - 1        */
#define VCE_UE_POTS_MAX             1
#define VCE_UE_DECT_MIN             2           /* DECT�������2 - 6        */
#define VCE_UE_DECT_MAX             6
#define VCE_UE_ISDN_MIN             7           /* ISDN�������7        */
#define VCE_UE_ISDN_MAX             7
#define VCE_UE_SIP_PHONE_MIN        8           /* SIP��Phone�������8 - 23 */
#define VCE_UE_SIP_PHONE_MAX        23
#define VCE_UE_MAX_INDEX            23

#define POTS_SET_NUM            ((VCE_UE_POTS_MAX - VCE_UE_POTS_MIN) + 1)           /* 2��  */

#ifdef SUPPORT_ATP_ISDN_VOICE
#define ISDN_SET_NUM            ((VCE_UE_ISDN_MAX - VCE_UE_ISDN_MIN) + 1)           /* 1��  */
#else
#define ISDN_SET_NUM            0
#endif

#ifdef SUPPORT_ATP_DECT_VOICE
#define DECT_SET_NUM            ((VCE_UE_DECT_MAX - VCE_UE_DECT_MIN) + 1)           /* 5��  */
#else
#define DECT_SET_NUM            0
#endif

#ifdef SUPPORT_ATP_SIP_SERVER
#define SIPPHONE_SET_NUM        ((VCE_UE_SIP_PHONE_MAX - VCE_UE_SIP_PHONE_MIN) + 1) /* 16�� */
#else
#define SIPPHONE_SET_NUM        0
#endif

#define VCE_PORT_MAX            (POTS_SET_NUM + DECT_SET_NUM + ISDN_SET_NUM + SIPPHONE_SET_NUM)

#define	MOBILE_BITMAP_ALL	((1<<(DECT_SET_NUM))-1)

/*�˺���������ֵ*/
enum
{
	VCE_NULL_LINEID		= 0,
	VCE_VOIP_BASE		= 1,                                   /*VOIP�����ʼֵ 1  */
	VCE_ISDN_BASE		= (VCE_VOIP_BASE + VCE_VOIP_MAX),      /*ISDN�����ʼֵ 17 */
	VCE_ISDN_DFT		= (VCE_ISDN_BASE + VCE_ISDN_MAX),      /*ISDNĬ��˳���(��MSN��������),27*/
	VCE_PSTN_BASE,     										   /*PSTN�����ʼֵ,28*/
	VCE_CS_BASE,      										   /*CS�����ʼֵ 29 */
	VCE_INCALL_BASE,								           /*FXS�ڲ������˺������ʼֵ*/
	VCE_OUTGO_AUTO,											   /*ȡһ���ϴ�ֵ��Ϊ�Զ�ѡ·����*/
    VCE_INCOM_ALL,                                             /*ȡֵ��Ϊ����ȫѡ*/
	VCE_LINEID_MAX	= VCE_OUTGO_AUTO,
};

#define VCE_PHONE_BOOK_MAX          250     /*���֧�ֵ绰����¼��Ŀ*/
#define VCE_MISSED_CALL_MAX         100     /*���֧��δ�������¼*/
#define VCE_INACC_CALL_MAX          100     /*���֧���ѽ������¼*/
#define VCE_OUT_CALL_MAX			100     /*���֧�ֺ��������¼*/
#define VCE_CALLRECORD_MAX			1500    /*���֧�������¼*/
#define VCE_LINE_SRV_MAX            5       /*һ��sip�ʺ����֧�ֿ����õ�ע�����������*/
#define VCE_IN_PREFIX_MAX           16      /*���֧�ֺ���ǰ׺����Ŀ*/
#define VCE_IN_SUFFIX_MAX           16      /*���֧�ֺ����׺����Ŀ*/
#define VCE_OUT_PREFIX_MAX          16      /*���֧�ֺ���ǰ׺����Ŀ*/
#define VCE_OUT_SUFFIX_MAX          16      /*���֧�ֺ�����׺����Ŀ*/
#define VCE_ROUTE_PREFIX_MAX        16      /*���֧��·��ǰ׺����Ŀ*/
#define VCE_SPEEDDAIL_MAX           16      /*���֧����λ���ŵ���Ŀ*/
#define VCE_DIAL_PREFIX_MAX         16      /*���֧�ֺ�����Ŀ*/
#define VCE_URG_LINE_MAX            16      /*���֧�ֽ���������Ŀ*/
#define VCE_OUTGOLIST_MAX           4       /*���֧�ֺ���ѡ·����Ŀ*/
#define VCE_SUBEVENT_MAX            3       /*���֧�ֶ��ĵ�������*/

#define VCE_WAKEUP_MAX              10       /*���֧���������Ӹ���*/
#define VCE_RINGSCHEDULE_MAX        4       /*���֧��Ring Schedule����*/
#define VCE_WAKEUP_NAME_LEN         32+1     /*����������󳤶�*/
#define VCE_WAKEUP_WEEKDAY_MAX      7        /*һ��7��*/
#define VCE_DAYTIME_MIN             0        /*ʱ����Сֵ*/
#define VCE_DAYTIME_HOUR_MIDDLE     12        /*����Сʱ*/
#define VCE_DAYTIME_HOUR_MAX        24        /*Сʱ���ֵ*/
#define VCE_DAYTIME_MINUTE_MAX      60        /*�������ֵ*/
#define VCE_DAYTIME_ERRORVALUE      (0xFFFFFFFF)
#define VCE_WAKEUP_EVERYDAY         "Every Day"
#define VCE_WAKEUP_WORKDAY          "Every Workday"
#define VCE_WAKEUP_WEEKEND          "All Weekend"
#define VCE_WEEKDAY_EVERYDAY        "Mon,Tue,Wed,Thu,Fri,Sat,Sun"
#define VCE_WEEKDAY_WORKDAY         "Mon,Tue,Wed,Thu,Fri"
#define VCE_WEEKDAY_WEEKEND         "Sat,Sun"
#define VCE_WEEKDAY_DAYSEC          (24*60*60)
#define VCE_WEEKDAY_WEEKSEC         (7*24*60*60)

/*֮���Լ�1����Ϊ����һЩ�ַ����ĳ��ȣ���Ҫ�н�����'\0'*/
#define VCE_PIN_LEN_MAX             32+1    /*PIN����󳤶�*/

#define SIP_MAX_NUM_LEN             32+1    /* �û�������󳤶�                             */
#define SIP_MAX_NAME_LEN            128+1   /* �û�������󳤶�                             */
#define SIP_MAX_PSW_LEN             128+1   /* �û�������󳤶�                             */
#define SIP_MAX_NAME_64LEN          64+1   /* HG253s V2��������:�û�������󳤶�64          */
#define SIP_MAX_PSW_64LEN           64+1   /* HG253s V2��������:�û�������󳤶�64          */
#define SIP_MAX_URL_LEN             256+1   /* SIP URL��󳤶�                              */

#define SIP_LINE_STATE_SESS_MAX     2
#define SIP_LINE_STATE_READEAY      0x01020304
#define SIP_LINE_STATE_UNREADY      0x0
#define SIP_QUERY_TIME              10
#define SIP_SESSION_QUERY_TIME      60
#define SIP_RESTE_TIME              2

#define VOICE_FUNCTION_PREFIX_STR            "**09|***91#|**#91#|***92#|**#92#"      /* ����ǰ׺ */
#define VOICE_FUNPREFIX_LEN                  64

#define VOICE_INCALL_NUM_PREFIX              "**"
#define VOICE_VOXINCALL_NUM_PREFIX           "#"
#define VOICE_DIAL_ROUTER_PREFIX             "##"
#define VOICE_DFT_SIGNAL_PROTOCOL            "SIP/2.0"

#define VOICE_OBJID_NOUSE                      0             /* �����еĽڵ����δʹ�ñ��*/
#define VOICE_LINEINDEX_NOUSE                  0             /* �����е�δʹ�õ���·����*/
#define VOICE_CMD_LEN                          256
#define VOICE_INTERFACENAME_LEN                32            /* �������нӿ�������*/

#define VOICE_SIPSERVER_NUM                    1
#define VOICE_REGION_NAME_LEN                  4             /* ���һ������д����*/
#define VOICE_DTMF_TYPE_NAME_LEN               32
#define VOICE_FAX_TYPE_NAME_LEN                32
#define VOICE_UMTS_NUMBER_LEN                  32+1          /* UMTS���볤��*/
#define VOICE_PSTN_NUMBER_LEN                  32+1          /* PSTN���볤��*/
#define VOICE_ISDN_NUMBER_LEN                  64+1          /* ISDN���볤��*/
#ifdef SUPPORT_ATP_VCESIP_DIGITMAP_H248
#define VOICE_H248DIGITITDSHORT_MIN            3000          /*H248��ͼ֧�ֶ�ʱ����Сʱ��*/
#define VOICE_H248DIGITITDSHORT_MAX            20000         /*H248��ͼ֧�ֶ�ʱ�����ʱ��*/
#define VOICE_VOIP_DIGITMAP_LEN                3072+1        /* VOIP DigitMap����*/
#define VOICE_DIGITMAP_SPECIAL                 "ABCDEFXabcdefx0123456789-[|]*#.TSL"
#define VOICE_DIGITMAP_SPECIAL_MGCP            "*#T"
#define VOICE_DIGITMAP_SPECIAL_H248            "EFSLef"
#else
#define VOICE_VOIP_DIGITMAP_LEN                VOICE_DIGITMAP_MAX_LEN+1         /* VOIP DigitMap����*/
#define VOICE_DIGITMAP_SPECIAL                 "ABCDXabcdx0123456789-[||]*#.Tt"
#endif
#define VOICE_HOTLINE_NUMBER_LEN               64+1          /* ���ߺ�����볤�� */
#define VOICE_EMERGENCY_LEN                    42+1          /* �������볤��*/
#define VOICE_CALLPREFIX_LEN                   42+1          /* ����ǰ��׺���� */
#define VOICE_DIALPREFIX_LEN                   42+1          /* ����ǰ׺����*/
#define VOICE_DIALNUMBER_LEN                   32+1          /* ��Ӧ�������ŵĳ���*/
#define VOICE_CALLFIX_ASSOCIATE_NUM_LEN        32+1          /* ����ǰ��׺��غ���ĳ���*/
#define VOICE_QUICKDIAL_LEN                    40+1          /* ���ٲ��ŵĳ���*/
#define VOICE_DESCRIPTION_LEN                  32+1          /* ��ע����*/
#define VOICE_PROFILE_NAME_LEN                 64+1          /* Profile����*/
#define VOICE_SERVER_ADDR_LEN                  256+1         /* ��������ַ���� */
#define VOICE_PAKPERIOD_LEN                    4             /* ���ʱ������*/
#define VOICE_AREA_LEN                         7+1           /* ���ź��볤��*/
#define VOICE_SIP_URI_LEN                      389+1         /* SIP URI����*/
#define VOICE_MWI_URI_LEN                      128+1
#define VOICE_SUB_EVENT_LEN                    32+1          /*�����¼����Ƴ���*/
#define VOICE_LINELIST_LEN                     1024+1        /*�˿ڹ����˺��б���*/          
#define VOICE_INCALL_LEN                       32+1          /*�ڲ����볤��*/ 
#define VOICE_INCALL_NAME_LEN                  32+1          /*POTS��Name����*/
#define VOICE_DECT_PIN_LEN                     32+1          /*DECT PIN�볤��*/
#define	VOICE_DECT_NAME_LEN	                   32+1          /*DECT��Name����*/

#define VOICE_STATUS_LEN                       32            /*����״̬����*/
#define VOICE_CALL_ALL_PORTS_LEN               32+1          /*�˿�Ⱥ������ĳ���*/

#define VOICE_DFT_LOCALPORT                    0
#define VOICE_PORTLIST_LEN                     33            /*�ʺŹ����˿��б���*/
#define VOICE_ADR_LEN                          257           /*Server���Ƶĳ���*/
#define VOICE_NUMBER_SPECIAL                   "0123456789"
#define VOICE_SIPID_SPECIAL                    "0123456789*#"
#define VOICE_DPLAN_SPECIAL                    "0123456789*#ABCDabcd"
#define VOICE_AUTHNAMEORPWD_SPECIAL            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%^&*()_+-@."
#define VOICE_PORT_MAXNUM                      2             /*���֧�ֶ˿ڼ�¼��Ŀ*/
#define VOICE_DECT_MAXNUM                      5             /*���֧��DECT����Ŀ*/
#define VOICE_PORTROUTE_LEN                    33            /*�˿�·�����ͳ���*/

#define VOICE_TAPI_REGIONRMAX                  28            /*���ҵĸ���*/    // Modify by 2013/5/4

#define VOICE_PROFILE_MAX                      16            /*���֧��16��Profile*/
#define VOICE_LINE_MAX                         16            /*���֧��ÿ��Profile��Line�ļ�¼��Ŀ*/

#define VOICE_CODEC_PRIORITY_MIN               1             /*������������������ȼ�*/
#define VOICE_CODEC_PRIORITY_MAX               6             /*������������������ȼ�*/
#define VOICE_CODEC_PRIORITY_NULL              7             /*��������Ϊ��ʱ�����ȼ�*/
#define VOICE_CODE_LIST_SET_LEN                256           /* �����������ȼ���ʹ��������ַ������� */ // 2013/5/14

#define VOICE_TAPI_DTMFTYPEMAX                 3             /*DTMF���ݴ��䷽������*/
#define VOICE_TAPI_FAXTYPEMAX                  5             /*��������͸���*/
#define VOICE_UMTS_DTMFTYPEMAX                 2             /* CS DTMF�������� */

#define VOICE_STRING_MIN                       0
#define VOICE_SIPEVENTEXP_MIN                  20            /* MWIˢ��ʱ����Сֵ*/
#define VOICE_SIPEVENTEXP_MAX                  65535         /* MWIˢ��ʱ�����ֵ*/
#define VOICE_OPTIONINTE_MIN                   30            /* Options��������Сʱ���� */
#define VOICE_OPTIONINTE_MAX                   3600          /* Options���������ʱ���� */

#ifdef HISI_CHIP
/*оƬ����:HISIоƬ JitterBufferȡֵ��Χ[6,200], ����Ĭ��ֵ6*/
#define VOICE_JBLENGTH_MIN                     6            /* JB ���ȵ���Сֵ*/
#define VOICE_JBLENGTH_MAX                     200          /* JB ���ȵ����ֵ*/
#else
#define VOICE_JBLENGTH_MIN                     20            /* JB ���ȵ���Сֵ*/
#define VOICE_JBLENGTH_MAX                     1000          /* JB ���ȵ����ֵ*/
#endif

#define VOICE_RTP_PORT_MIN                     50000         /* RTP�˿ںŵ���Сֵ */                 
#define VOICE_RTP_PORT_MAX                     50050         /* RTP�˿ںŵ����ֵ */ 
#define VOICE_DIGITITDSHORT_MIN                0             /* ��λ�䲦����Сʱ����,��λ���� */
#define VOICE_DIGITITDSHORT_MAX                10000         /* ��λ�䲦�����ʱ����,��λ���� */
#define VOICE_DIGITITDLONG_MIN                 0             /* ��λ�䲦����Сʱ����,��λ���� */
#define VOICE_DIGITITDLONG_MAX                 20000         /* ��λ�䲦�����ʱ����,��λ���� */
#define VOICE_DIALITD_MIN                      10000         /* ժ����������̷���ʱ��,��λ���� */
#define VOICE_DIALITD_MAX                      20000         /* ժ�������������ʱ��,��λ���� */
#define VOICE_RINGITD_MIN                      50000         /* �ýв�Ӧ��̷���ʱ��,��λ���� */
#define VOICE_RINGITD_MIN_CUSTOMIZE            40000         /* �ýв�Ӧ��̷���ʱ��,��λ���� */
#define VOICE_RINGITD_MAX                      80000         /* �ýв�Ӧ�����ʱ��,��λ���� */
#define VOICE_RINGITD_DEFAULT                  60000         /* �ýв�ӦĬ�Ϸ���ʱ��,��λ���� */
#define VOICE_HOWLITD_MIN                      40000         /* �߹�����̷���ʱ��,��λ���� */
#define VOICE_HOWLITD_MAX                      60000         /* �߹��������ʱ��,��λ���� */
#define VOICE_BUSYITD_MIN                      40000         /* æ����̷���ʱ��,��λ���� */
#define VOICE_BUSYITD_MAX                      60000         /* æ�������ʱ��,��λ���� */
#define VOICE_CFNRTIME_MIN                     11            /* ����ǰת��̷���ʱ��,��λ�� */
#define VOICE_CFNRTIME_MAX                     60            /* ����ǰת�����ʱ��,��λ�� */
#define VOICE_REGRETRY_MIN                     1
#define VOICE_REGRETRY_MAX                     65535
#define VOICE_REGEXPIRES_MIN                   20
#define VOICE_REGEXPIRES_MAX                   65535
#define VOICE_SESSIONEXP_MIN                   90             
#define VOICE_SESSIONEXP_MAX                   3600
#define VOICE_MINSE_MIN                        90
#define VOICE_MINSE_MAX                        1800
#define VOICE_GAIN_MIN                         (-12)         /* �������Сֵ */ 
#define VOICE_GAIN_MAX                         12            /* ��������ֵ */ 
#define VOICE_SESSIONPERLINE_MAX               2             /* ÿ����·��֧�ֵ�ͬ���Ự����Ŀ������,2��ʾ֧������ͨ����1��ʾ��֧������ͨ��*/
#define VOICE_OFFHOOKTIME_MIN                  250           /* ��λ����*/
#define VOICE_OFFHOOKTIME_MAX                  1000          /* ��λ����*/
#define VOICE_ONHOOKTIME_MIN                   250           /* ��λ����*/
#define VOICE_ONHOOKTIME_MAX                   1000          /* ��λ����*/
#define VOICE_MINHOOKFLASH_MIN                 80            /* ��λ����*/
#define VOICE_MINHOOKFLASH_MIN_CUSTOMIZE       50            /* ��λ����*/   // 2013/9/3
#define VOICE_MINHOOKFLASH_MAX                 240           /* ��λ����*/
#define VOICE_MAXHOOKFLASH_MIN                 90            /* ��λ����*/
#define VOICE_MAXHOOKFLASH_MIN_CUSTOMIZE       80           /* ��λ����*/    // 2013/9/3
#define VOICE_MAXHOOKFLASH_MAX_CUSTOMIZE       1100          /* ��λ���� */  // 2013/9/3
#define VOICE_MAXHOOKFLASH_MAX                 250           /* ��λ����*/
#define VOICE_RTP_PORT_RESERVE                 20            /* RTP��С�˿������˿�ֵ��ֵ */  
#define VOICE_RTCP_INTERVAL_MIN                1000          /* RTCP��tx����Сֵ��λ����*/
#define VOICE_RTCP_INTERVAL_MAX                16000         /* RTCP��tx�����ֵ��λ����*/
#define VOICE_PORT_MIN                         1             /* �˿���Сֵ*/
#define VOICE_PORT_MAX                         65535         /* �˿���Сֵ*/
#define VOICE_HOTLINE_INTERVAL_MIN0            0             /* ��������ʱ����*/
#define VOICE_HOTLINE_INTERVAL_MIN             3             /* ���ߺ��������ʱ������Сֵ*/
#define VOICE_HOTLINE_INTERVAL_MAX0            10            /* ���ߺ��������ʱ�������ֵ*/
#define VOICE_HOTLINE_INTERVAL_MAX             20            /* ���ߺ��������ʱ�������ֵ*/
#define VOICE_HOTLINE_INTERVAL_DEFAULT         7
#define VOICE_COMMON_LENGTH_MAX                32            /* CallPrefix,DialPrefix��һЩ�ַ����������ֵ*/
#define VOICE_URI_LEN_MAX                      389           /* SIP URI�ַ����������ֵ*/
#define VOICE_NUMBER_DISPLAY_TYPE_MIN          0
#define VOICE_NUMBER_DISPLAY_TYPE_MAX          2
#define VOICE_PRIVACY_LEVEL_MIN                1
#define VOICE_PRIVACY_LEVEL_MAX                6
#define VOICE_DECT_PIN_MIN                     4
#define VOICE_DECT_PIN_MAX                     8
#define VOICE_DECTPIN_SPECIAL                  "0123456789"

#define VOICE_DIAG_LOG_LEVEL_MIN               1
#define VOICE_DIAG_LOG_LEVEL_MAX               2

#define VOICE_DECT_INNER_ID_BASE               61

#define VOICE_DEFAULT_IFNAME                   ""
#define VOICE_IFNAME_BR0                       "br0"
#define VOICE_SUBEVENT_MWI                     "MWI"//"message-summary"
#define VOICE_SUBEVENT_UA                      "UA_PROFILE"//"ua-profile"
#define VOICE_SUBEVENT_REG                     "REG"//"reg"
#define VOICE_ENABLED_STR                      "Enabled"      /* ����line */
#define VOICE_DISABLED_STR                     "Disabled"     /* ����line */
#define VOICE_QUIESCENT_STR                    "Quiescent"
#define VOICE_CODEC_PERIOD_MIN                 "10"           /*���ʱ����Сֵ*/
#define VOICE_CODEC_PERIOD_MIDDLE              "20"             
#define VOICE_CODEC_PERIOD_MAX                 "30"           /*���ʱ�����ֵ*/
#define VOICE_INCOM_ALL_STR                    "all"          /* ����ȫ������*/
#define VOICE_OUTGO_AUTO_STR                   "auto"         /* ���������Զ�*/
#define VOICE_LINESTAT_UNREG                   "Unregistered"
#define VOICE_LINESTAT_REGING                  "Registering"
#define VOICE_LINESTAT_REG                     "Up"
#define VOICE_LINECALLSTAT_IDLE                "Idle"

#define VOICE_STUN_DFT_PORT                    3478          /* Ĭ��STUN�������Ķ˿�ֵ*/

#define VOICE_PROFILE_PARANUM                  21             /* Profile�ڵ��������*/
#define VOICE_PROFILESIP_PARANUM               24             /*Profile.SIP�ڵ��������*/
#define VOICE_LINEPROCESS_PARANUM              4              /*Line.VoiceProcessing�ڵ��������*/

#ifdef SUPPORT_ATP_DECT_VOICE
/* ��¼Dect����״̬�ļ�*/
#define FILE_PATH_DECT_STATUS               "/var/voice/dectstatus"
#define	VOICE_GET_MOBILE_INFO(_idx)		(((_idx)<DECT_SET_NUM) ? \
										&(g_stVoiceService.stDect.stDectMobile[(_idx)]) : VOS_NULL_PTR)
#endif

#define	VOICE_LOGICAL_INVERSE(_flag)	((VOS_FALSE == (_flag)) ? VOS_TRUE : VOS_FALSE)

										
/*����TR104����ģ�ͣ�codec��Enumͳһ�����¸�ʽ
  G.711MuLaw G.711ALaw G.726 G.729 G.729a G.729e G.728
  G.723.1 G.722 G.722.1 G.722.2 GSM-FR GSM-HR GSM-EFR iLBC
*/
#define VCE_CODEC_MAX                   6             /*���֧��ÿ���˺��±��뷽ʽ����*/
#define VOICE_CODEC_NAME_LEN            32
#define VOICE_CODECLIST_LEN             (VCE_CODEC_MAX)*(VOICE_CODEC_NAME_LEN)
#define VOICE_CODEC_LIST                "G.711ALaw,G.711MuLaw,G.726-32,G.726-24,G.729,G.722"

/*�����·ʱ����·��Ĭ������*/
#define VOICE_FAX_TYPE_LIST_DEFAULT     "G711A,G711A_VBD,G711U,G711U_VBD,T38"
/*CLIP ʹ��Ĭ��ֵ*/ 
#define VOICE_CLIP_VALUE_DEFAULT        VOS_TRUE
/*Call Waiting ʹ��Ĭ��ֵ*/ 
#define VOICE_CW_VALUE_DEFAULT          VOS_TRUE
/*Call Transfer ʹ��Ĭ��ֵ*/
#define VOICE_MAXSESSIONS_VALUE_DEFAULT 2
/*����ͨ�� ʹ��Ĭ��ֵ*/
#define VOICE_CT_VALUE_DEFAULT          VOS_TRUE
/*Silence Suppressionʹ��Ĭ��ֵ*/
#define VOICE_SS_VALUE_DEFAULT          VOS_TRUE   

#define VOICE_NUMBER_DISPLAY_TYPE_VALUE_DEFAULT        0
#define VOICE_PRIVACY_LEVEL_VALUE_DEFAULT              6

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __VOICE_HGW723V_H__ */

