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

/*帐号支持能力*/
#define VCE_VOIP_MAX                16      /*最多支持的VoIP帐号个数*/
#define VCE_ISDN_MAX                10      /*最多支持的ISDN帐号个数*/
#define VCE_PSTN_MAX                1       /*最多支持的PSTN帐号个数*/
#define VCE_CS_MAX                  1       /*最多支持的CS帐号个数*/

#define VCE_LINE_MAX (VCE_VOIP_MAX + VCE_ISDN_MAX + VCE_PSTN_MAX + VCE_CS_MAX) /*最多支持的帐号个数*/

/*端口编号，请勿修改*/
#define VCE_UE_POTS_MIN             0           /* POTS话机编号0 - 1        */
#define VCE_UE_POTS_MAX             1
#define VCE_UE_DECT_MIN             2           /* DECT话机编号2 - 6        */
#define VCE_UE_DECT_MAX             6
#define VCE_UE_ISDN_MIN             7           /* ISDN话机编号7        */
#define VCE_UE_ISDN_MAX             7
#define VCE_UE_SIP_PHONE_MIN        8           /* SIP软Phone话机编号8 - 23 */
#define VCE_UE_SIP_PHONE_MAX        23
#define VCE_UE_MAX_INDEX            23

#define POTS_SET_NUM            ((VCE_UE_POTS_MAX - VCE_UE_POTS_MIN) + 1)           /* 2个  */

#ifdef SUPPORT_ATP_ISDN_VOICE
#define ISDN_SET_NUM            ((VCE_UE_ISDN_MAX - VCE_UE_ISDN_MIN) + 1)           /* 1个  */
#else
#define ISDN_SET_NUM            0
#endif

#ifdef SUPPORT_ATP_DECT_VOICE
#define DECT_SET_NUM            ((VCE_UE_DECT_MAX - VCE_UE_DECT_MIN) + 1)           /* 5个  */
#else
#define DECT_SET_NUM            0
#endif

#ifdef SUPPORT_ATP_SIP_SERVER
#define SIPPHONE_SET_NUM        ((VCE_UE_SIP_PHONE_MAX - VCE_UE_SIP_PHONE_MIN) + 1) /* 16个 */
#else
#define SIPPHONE_SET_NUM        0
#endif

#define VCE_PORT_MAX            (POTS_SET_NUM + DECT_SET_NUM + ISDN_SET_NUM + SIPPHONE_SET_NUM)

#define	MOBILE_BITMAP_ALL	((1<<(DECT_SET_NUM))-1)

/*账号索引基线值*/
enum
{
	VCE_NULL_LINEID		= 0,
	VCE_VOIP_BASE		= 1,                                   /*VOIP序号起始值 1  */
	VCE_ISDN_BASE		= (VCE_VOIP_BASE + VCE_VOIP_MAX),      /*ISDN序号起始值 17 */
	VCE_ISDN_DFT		= (VCE_ISDN_BASE + VCE_ISDN_MAX),      /*ISDN默认顺序号(无MSN号码的情况),27*/
	VCE_PSTN_BASE,     										   /*PSTN序号起始值,28*/
	VCE_CS_BASE,      										   /*CS序号起始值 29 */
	VCE_INCALL_BASE,								           /*FXS内部呼叫账号序号起始值*/
	VCE_OUTGO_AUTO,											   /*取一个较大值作为自动选路索引*/
    VCE_INCOM_ALL,                                             /*取值作为呼入全选*/
	VCE_LINEID_MAX	= VCE_OUTGO_AUTO,
};

#define VCE_PHONE_BOOK_MAX          250     /*最多支持电话本记录条目*/
#define VCE_MISSED_CALL_MAX         100     /*最多支持未接来电记录*/
#define VCE_INACC_CALL_MAX          100     /*最多支持已接来电记录*/
#define VCE_OUT_CALL_MAX			100     /*最多支持呼出来电记录*/
#define VCE_CALLRECORD_MAX			1500    /*最多支持来电记录*/
#define VCE_LINE_SRV_MAX            5       /*一个sip帐号最多支持可配置的注册服务器个数*/
#define VCE_IN_PREFIX_MAX           16      /*最多支持呼入前缀的条目*/
#define VCE_IN_SUFFIX_MAX           16      /*最多支持呼入后缀的条目*/
#define VCE_OUT_PREFIX_MAX          16      /*最多支持呼出前缀的条目*/
#define VCE_OUT_SUFFIX_MAX          16      /*最多支持呼出后缀的条目*/
#define VCE_ROUTE_PREFIX_MAX        16      /*最多支持路由前缀的条目*/
#define VCE_SPEEDDAIL_MAX           16      /*最多支持缩位拨号的条目*/
#define VCE_DIAL_PREFIX_MAX         16      /*最多支持号首条目*/
#define VCE_URG_LINE_MAX            16      /*最多支持紧急号码条目*/
#define VCE_OUTGOLIST_MAX           4       /*最多支持呼出选路的条目*/
#define VCE_SUBEVENT_MAX            3       /*最多支持订阅的种类数*/

#define VCE_WAKEUP_MAX              10       /*最多支持语音闹钟个数*/
#define VCE_RINGSCHEDULE_MAX        4       /*最多支持Ring Schedule个数*/
#define VCE_WAKEUP_NAME_LEN         32+1     /*闹铃名称最大长度*/
#define VCE_WAKEUP_WEEKDAY_MAX      7        /*一周7天*/
#define VCE_DAYTIME_MIN             0        /*时间最小值*/
#define VCE_DAYTIME_HOUR_MIDDLE     12        /*正午小时*/
#define VCE_DAYTIME_HOUR_MAX        24        /*小时最大值*/
#define VCE_DAYTIME_MINUTE_MAX      60        /*分钟最大值*/
#define VCE_DAYTIME_ERRORVALUE      (0xFFFFFFFF)
#define VCE_WAKEUP_EVERYDAY         "Every Day"
#define VCE_WAKEUP_WORKDAY          "Every Workday"
#define VCE_WAKEUP_WEEKEND          "All Weekend"
#define VCE_WEEKDAY_EVERYDAY        "Mon,Tue,Wed,Thu,Fri,Sat,Sun"
#define VCE_WEEKDAY_WORKDAY         "Mon,Tue,Wed,Thu,Fri"
#define VCE_WEEKDAY_WEEKEND         "Sat,Sun"
#define VCE_WEEKDAY_DAYSEC          (24*60*60)
#define VCE_WEEKDAY_WEEKSEC         (7*24*60*60)

/*之所以加1是因为都是一些字符串的长度，需要有结束符'\0'*/
#define VCE_PIN_LEN_MAX             32+1    /*PIN码最大长度*/

#define SIP_MAX_NUM_LEN             32+1    /* 用户号码最大长度                             */
#define SIP_MAX_NAME_LEN            128+1   /* 用户姓名最大长度                             */
#define SIP_MAX_PSW_LEN             128+1   /* 用户密码最大长度                             */
#define SIP_MAX_NAME_64LEN          64+1   /* HG253s V2定制需求:用户姓名最大长度64          */
#define SIP_MAX_PSW_64LEN           64+1   /* HG253s V2定制需求:用户密码最大长度64          */
#define SIP_MAX_URL_LEN             256+1   /* SIP URL最大长度                              */

#define SIP_LINE_STATE_SESS_MAX     2
#define SIP_LINE_STATE_READEAY      0x01020304
#define SIP_LINE_STATE_UNREADY      0x0
#define SIP_QUERY_TIME              10
#define SIP_SESSION_QUERY_TIME      60
#define SIP_RESTE_TIME              2

#define VOICE_FUNCTION_PREFIX_STR            "**09|***91#|**#91#|***92#|**#92#"      /* 功能前缀 */
#define VOICE_FUNPREFIX_LEN                  64

#define VOICE_INCALL_NUM_PREFIX              "**"
#define VOICE_VOXINCALL_NUM_PREFIX           "#"
#define VOICE_DIAL_ROUTER_PREFIX             "##"
#define VOICE_DFT_SIGNAL_PROTOCOL            "SIP/2.0"

#define VOICE_OBJID_NOUSE                      0             /* 数组中的节点对象未使用标记*/
#define VOICE_LINEINDEX_NOUSE                  0             /* 数组中的未使用的线路索引*/
#define VOICE_CMD_LEN                          256
#define VOICE_INTERFACENAME_LEN                32            /* 网关上行接口名长度*/

#define VOICE_SIPSERVER_NUM                    1
#define VOICE_REGION_NAME_LEN                  4             /* 国家或地区缩写长度*/
#define VOICE_DTMF_TYPE_NAME_LEN               32
#define VOICE_FAX_TYPE_NAME_LEN                32
#define VOICE_UMTS_NUMBER_LEN                  32+1          /* UMTS号码长度*/
#define VOICE_PSTN_NUMBER_LEN                  32+1          /* PSTN号码长度*/
#define VOICE_ISDN_NUMBER_LEN                  64+1          /* ISDN号码长度*/
#ifdef SUPPORT_ATP_VCESIP_DIGITMAP_H248
#define VOICE_H248DIGITITDSHORT_MIN            3000          /*H248数图支持定时器最小时长*/
#define VOICE_H248DIGITITDSHORT_MAX            20000         /*H248数图支持定时器最大时长*/
#define VOICE_VOIP_DIGITMAP_LEN                3072+1        /* VOIP DigitMap长度*/
#define VOICE_DIGITMAP_SPECIAL                 "ABCDEFXabcdefx0123456789-[|]*#.TSL"
#define VOICE_DIGITMAP_SPECIAL_MGCP            "*#T"
#define VOICE_DIGITMAP_SPECIAL_H248            "EFSLef"
#else
#define VOICE_VOIP_DIGITMAP_LEN                VOICE_DIGITMAP_MAX_LEN+1         /* VOIP DigitMap长度*/
#define VOICE_DIGITMAP_SPECIAL                 "ABCDXabcdx0123456789-[||]*#.Tt"
#endif
#define VOICE_HOTLINE_NUMBER_LEN               64+1          /* 热线号码号码长度 */
#define VOICE_EMERGENCY_LEN                    42+1          /* 紧急号码长度*/
#define VOICE_CALLPREFIX_LEN                   42+1          /* 呼叫前后缀长度 */
#define VOICE_DIALPREFIX_LEN                   42+1          /* 拨号前缀长度*/
#define VOICE_DIALNUMBER_LEN                   32+1          /* 对应呼出拨号的长度*/
#define VOICE_CALLFIX_ASSOCIATE_NUM_LEN        32+1          /* 呼叫前后缀相关号码的长度*/
#define VOICE_QUICKDIAL_LEN                    40+1          /* 快速拨号的长度*/
#define VOICE_DESCRIPTION_LEN                  32+1          /* 备注长度*/
#define VOICE_PROFILE_NAME_LEN                 64+1          /* Profile名称*/
#define VOICE_SERVER_ADDR_LEN                  256+1         /* 服务器地址长度 */
#define VOICE_PAKPERIOD_LEN                    4             /* 打包时长长度*/
#define VOICE_AREA_LEN                         7+1           /* 区号号码长度*/
#define VOICE_SIP_URI_LEN                      389+1         /* SIP URI长度*/
#define VOICE_MWI_URI_LEN                      128+1
#define VOICE_SUB_EVENT_LEN                    32+1          /*订阅事件名称长度*/
#define VOICE_LINELIST_LEN                     1024+1        /*端口关联账号列表长度*/          
#define VOICE_INCALL_LEN                       32+1          /*内部号码长度*/ 
#define VOICE_INCALL_NAME_LEN                  32+1          /*POTS的Name长度*/
#define VOICE_DECT_PIN_LEN                     32+1          /*DECT PIN码长度*/
#define	VOICE_DECT_NAME_LEN	                   32+1          /*DECT的Name长度*/

#define VOICE_STATUS_LEN                       32            /*号码状态长度*/
#define VOICE_CALL_ALL_PORTS_LEN               32+1          /*端口群呼号码的长度*/

#define VOICE_DFT_LOCALPORT                    0
#define VOICE_PORTLIST_LEN                     33            /*帐号关联端口列表长度*/
#define VOICE_ADR_LEN                          257           /*Server名称的长度*/
#define VOICE_NUMBER_SPECIAL                   "0123456789"
#define VOICE_SIPID_SPECIAL                    "0123456789*#"
#define VOICE_DPLAN_SPECIAL                    "0123456789*#ABCDabcd"
#define VOICE_AUTHNAMEORPWD_SPECIAL            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%^&*()_+-@."
#define VOICE_PORT_MAXNUM                      2             /*最多支持端口记录数目*/
#define VOICE_DECT_MAXNUM                      5             /*最多支持DECT的数目*/
#define VOICE_PORTROUTE_LEN                    33            /*端口路由类型长度*/

#define VOICE_TAPI_REGIONRMAX                  28            /*国家的个数*/    // Modify by 2013/5/4

#define VOICE_PROFILE_MAX                      16            /*最多支持16个Profile*/
#define VOICE_LINE_MAX                         16            /*最多支持每个Profile下Line的记录数目*/

#define VOICE_CODEC_PRIORITY_MIN               1             /*定义编解码器的最高优先级*/
#define VOICE_CODEC_PRIORITY_MAX               6             /*定义编解码器的最低优先级*/
#define VOICE_CODEC_PRIORITY_NULL              7             /*定义编解码为空时的优先级*/
#define VOICE_CODE_LIST_SET_LEN                256           /* 定义编解码优先级和使能情况的字符串长度 */ // 2013/5/14

#define VOICE_TAPI_DTMFTYPEMAX                 3             /*DTMF数据传输方法个数*/
#define VOICE_TAPI_FAXTYPEMAX                  5             /*传真的类型个数*/
#define VOICE_UMTS_DTMFTYPEMAX                 2             /* CS DTMF方法个数 */

#define VOICE_STRING_MIN                       0
#define VOICE_SIPEVENTEXP_MIN                  20            /* MWI刷新时间最小值*/
#define VOICE_SIPEVENTEXP_MAX                  65535         /* MWI刷新时间最大值*/
#define VOICE_OPTIONINTE_MIN                   30            /* Options检测服务最小时间间隔 */
#define VOICE_OPTIONINTE_MAX                   3600          /* Options检测服务最大时间间隔 */

#ifdef HISI_CHIP
/*芯片特性:HISI芯片 JitterBuffer取值范围[6,200], 建议默认值6*/
#define VOICE_JBLENGTH_MIN                     6            /* JB 长度的最小值*/
#define VOICE_JBLENGTH_MAX                     200          /* JB 长度的最大值*/
#else
#define VOICE_JBLENGTH_MIN                     20            /* JB 长度的最小值*/
#define VOICE_JBLENGTH_MAX                     1000          /* JB 长度的最大值*/
#endif

#define VOICE_RTP_PORT_MIN                     50000         /* RTP端口号的最小值 */                 
#define VOICE_RTP_PORT_MAX                     50050         /* RTP端口号的最大值 */ 
#define VOICE_DIGITITDSHORT_MIN                0             /* 短位间拨号最小时间间隔,单位毫秒 */
#define VOICE_DIGITITDSHORT_MAX                10000         /* 短位间拨号最大时间间隔,单位毫秒 */
#define VOICE_DIGITITDLONG_MIN                 0             /* 长位间拨号最小时间间隔,单位毫秒 */
#define VOICE_DIGITITDLONG_MAX                 20000         /* 长位间拨号最大时间间隔,单位毫秒 */
#define VOICE_DIALITD_MIN                      10000         /* 摘机不拨号最短放音时长,单位毫秒 */
#define VOICE_DIALITD_MAX                      20000         /* 摘机不拨号最长放音时长,单位毫秒 */
#define VOICE_RINGITD_MIN                      50000         /* 久叫不应最短放音时长,单位毫秒 */
#define VOICE_RINGITD_MIN_CUSTOMIZE            40000         /* 久叫不应最短放音时长,单位毫秒 */
#define VOICE_RINGITD_MAX                      80000         /* 久叫不应最长放音时长,单位毫秒 */
#define VOICE_RINGITD_DEFAULT                  60000         /* 久叫不应默认放音时长,单位毫秒 */
#define VOICE_HOWLITD_MIN                      40000         /* 催挂音最短放音时长,单位毫秒 */
#define VOICE_HOWLITD_MAX                      60000         /* 催挂音最长放音时长,单位毫秒 */
#define VOICE_BUSYITD_MIN                      40000         /* 忙音最短放音时长,单位毫秒 */
#define VOICE_BUSYITD_MAX                      60000         /* 忙音最长放音时长,单位毫秒 */
#define VOICE_CFNRTIME_MIN                     11            /* 呼叫前转最短放音时长,单位秒 */
#define VOICE_CFNRTIME_MAX                     60            /* 呼叫前转最长放音时长,单位秒 */
#define VOICE_REGRETRY_MIN                     1
#define VOICE_REGRETRY_MAX                     65535
#define VOICE_REGEXPIRES_MIN                   20
#define VOICE_REGEXPIRES_MAX                   65535
#define VOICE_SESSIONEXP_MIN                   90             
#define VOICE_SESSIONEXP_MAX                   3600
#define VOICE_MINSE_MIN                        90
#define VOICE_MINSE_MAX                        1800
#define VOICE_GAIN_MIN                         (-12)         /* 增益的最小值 */ 
#define VOICE_GAIN_MAX                         12            /* 增益的最大值 */ 
#define VOICE_SESSIONPERLINE_MAX               2             /* 每条线路所支持的同步会话的数目的上限,2表示支持三方通话，1表示不支持三方通话*/
#define VOICE_OFFHOOKTIME_MIN                  250           /* 单位毫秒*/
#define VOICE_OFFHOOKTIME_MAX                  1000          /* 单位毫秒*/
#define VOICE_ONHOOKTIME_MIN                   250           /* 单位毫秒*/
#define VOICE_ONHOOKTIME_MAX                   1000          /* 单位毫秒*/
#define VOICE_MINHOOKFLASH_MIN                 80            /* 单位毫秒*/
#define VOICE_MINHOOKFLASH_MIN_CUSTOMIZE       50            /* 单位毫秒*/   // 2013/9/3
#define VOICE_MINHOOKFLASH_MAX                 240           /* 单位毫秒*/
#define VOICE_MAXHOOKFLASH_MIN                 90            /* 单位毫秒*/
#define VOICE_MAXHOOKFLASH_MIN_CUSTOMIZE       80           /* 单位毫秒*/    // 2013/9/3
#define VOICE_MAXHOOKFLASH_MAX_CUSTOMIZE       1100          /* 单位毫秒 */  // 2013/9/3
#define VOICE_MAXHOOKFLASH_MAX                 250           /* 单位毫秒*/
#define VOICE_RTP_PORT_RESERVE                 20            /* RTP最小端口与最大端口值差值 */  
#define VOICE_RTCP_INTERVAL_MIN                1000          /* RTCP包tx的最小值单位毫秒*/
#define VOICE_RTCP_INTERVAL_MAX                16000         /* RTCP包tx的最大值单位毫秒*/
#define VOICE_PORT_MIN                         1             /* 端口最小值*/
#define VOICE_PORT_MAX                         65535         /* 端口最小值*/
#define VOICE_HOTLINE_INTERVAL_MIN0            0             /* 立即热线时间间隔*/
#define VOICE_HOTLINE_INTERVAL_MIN             3             /* 热线号码的启用时间间隔最小值*/
#define VOICE_HOTLINE_INTERVAL_MAX0            10            /* 热线号码的启用时间间隔最大值*/
#define VOICE_HOTLINE_INTERVAL_MAX             20            /* 热线号码的启用时间间隔最大值*/
#define VOICE_HOTLINE_INTERVAL_DEFAULT         7
#define VOICE_COMMON_LENGTH_MAX                32            /* CallPrefix,DialPrefix等一些字符串长度最大值*/
#define VOICE_URI_LEN_MAX                      389           /* SIP URI字符串长度最大值*/
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
#define VOICE_ENABLED_STR                      "Enabled"      /* 启用line */
#define VOICE_DISABLED_STR                     "Disabled"     /* 禁用line */
#define VOICE_QUIESCENT_STR                    "Quiescent"
#define VOICE_CODEC_PERIOD_MIN                 "10"           /*打包时长最小值*/
#define VOICE_CODEC_PERIOD_MIDDLE              "20"             
#define VOICE_CODEC_PERIOD_MAX                 "30"           /*打包时长最大值*/
#define VOICE_INCOM_ALL_STR                    "all"          /* 呼入全部关联*/
#define VOICE_OUTGO_AUTO_STR                   "auto"         /* 呼出关联自动*/
#define VOICE_LINESTAT_UNREG                   "Unregistered"
#define VOICE_LINESTAT_REGING                  "Registering"
#define VOICE_LINESTAT_REG                     "Up"
#define VOICE_LINECALLSTAT_IDLE                "Idle"

#define VOICE_STUN_DFT_PORT                    3478          /* 默认STUN服务器的端口值*/

#define VOICE_PROFILE_PARANUM                  21             /* Profile节点参数个数*/
#define VOICE_PROFILESIP_PARANUM               24             /*Profile.SIP节点参数个数*/
#define VOICE_LINEPROCESS_PARANUM              4              /*Line.VoiceProcessing节点参数个数*/

#ifdef SUPPORT_ATP_DECT_VOICE
/* 记录Dect对码状态文件*/
#define FILE_PATH_DECT_STATUS               "/var/voice/dectstatus"
#define	VOICE_GET_MOBILE_INFO(_idx)		(((_idx)<DECT_SET_NUM) ? \
										&(g_stVoiceService.stDect.stDectMobile[(_idx)]) : VOS_NULL_PTR)
#endif

#define	VOICE_LOGICAL_INVERSE(_flag)	((VOS_FALSE == (_flag)) ? VOS_TRUE : VOS_FALSE)

										
/*按照TR104数据模型，codec的Enum统一成以下格式
  G.711MuLaw G.711ALaw G.726 G.729 G.729a G.729e G.728
  G.723.1 G.722 G.722.1 G.722.2 GSM-FR GSM-HR GSM-EFR iLBC
*/
#define VCE_CODEC_MAX                   6             /*最多支持每个账号下编码方式个数*/
#define VOICE_CODEC_NAME_LEN            32
#define VOICE_CODECLIST_LEN             (VCE_CODEC_MAX)*(VOICE_CODEC_NAME_LEN)
#define VOICE_CODEC_LIST                "G.711ALaw,G.711MuLaw,G.726-32,G.726-24,G.729,G.722"

/*添加线路时，线路的默认配置*/
#define VOICE_FAX_TYPE_LIST_DEFAULT     "G711A,G711A_VBD,G711U,G711U_VBD,T38"
/*CLIP 使能默认值*/ 
#define VOICE_CLIP_VALUE_DEFAULT        VOS_TRUE
/*Call Waiting 使能默认值*/ 
#define VOICE_CW_VALUE_DEFAULT          VOS_TRUE
/*Call Transfer 使能默认值*/
#define VOICE_MAXSESSIONS_VALUE_DEFAULT 2
/*三方通话 使能默认值*/
#define VOICE_CT_VALUE_DEFAULT          VOS_TRUE
/*Silence Suppression使能默认值*/
#define VOICE_SS_VALUE_DEFAULT          VOS_TRUE   

#define VOICE_NUMBER_DISPLAY_TYPE_VALUE_DEFAULT        0
#define VOICE_PRIVACY_LEVEL_VALUE_DEFAULT              6

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __VOICE_HGW723V_H__ */

