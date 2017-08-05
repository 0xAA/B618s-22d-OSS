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
#define ATP_VOICE_EVENT_LEN         1024  /*产生呼叫记录时需要把呼叫记录结构体发送给dect模块，所以这里扩展消息体为1024*/

#define FILE_PATH_DIAG_FXS1_TO_FXS2 "/var/voice/fxs1tofxs2"
#define FILE_PATH_DIAG_FXS2_TO_FXS1 "/var/voice/fxs2tofxs1"
#define FILE_PATH_VOIPBOOTUP_STATUS "/var/voice/voipbootupstatus"
#ifdef SUPPORT_ATP_DECT_VOICE
#define VCE_FXS_MAX                 2       /*最多支持FXS口的个数*/
#define VCE_DECT_HS_MAX             5       /*最多支持DECT子机的个数*/
#define VCE_PORT_MAX (VCE_FXS_MAX + VCE_DECT_HS_MAX)    /*最多支持端口的条目*/


/*账号索引基线值*/
#define VCE_VOIP_BASE           1                                   /*VOIP序号起始值*/
#define VCE_ISDN_BASE           (VCE_VOIP_BASE + VCE_VOIP_MAX)      /*ISDN序号起始值*/
#define VCE_PSTN_BASE           (VCE_ISDN_BASE + VCE_ISDN_MAX + 1)  /*PSTN序号起始值,后面加1是加ISDN空帐号*/
#define VCE_CS_BASE             (VCE_PSTN_BASE + VCE_PSTN_MAX)      /*CS序号起始值*/
#define VCE_FXS_INCALL_BASE     (VCE_CS_BASE + VCE_CS_MAX)          /*FXS内部呼叫账号序号起始值*/
#define VCE_DECT_INCALL_BASE    (VCE_FXS_INCALL_BASE + VCE_FXS_MAX) /*DECT内部呼叫账号序号起始值*/

/*ISDN空帐号索引,该帐号用于当没有MSN号码时ISDN主被叫可用*/
#define VCE_ISDN_DFT    (VCE_ISDN_BASE + VCE_ISDN_MAX)              /*ISDN默认顺序号(无MSN号码的情况)*/

/*呼出为Auto时Dect传递的账号索引*/
#define VCE_OUTGO_AUTO  (VCE_DECT_INCALL_BASE + VCE_DECT_HS_MAX)    /*取一个较大值作为自动选路索引*/
#endif

/*Dect LineSetting中特殊账号名称*/
#define VCE_ISDN_NAME               "ISDN"
#define VCE_PSTN_NAME               "PSTN"
#define VCE_CS_NAME                 "CS"
#define VCE_INCALL_NAME             "INCALL"
#define VCE_NULL_NAME				"NULL"
#define DSP_TIMESLOT_DTMF4          4    /* Fxs0端口检测的dtmf4 */
#define DSP_TIMESLOT_DTMF5          5    /* Fxs1端口检测的dtmf5 */
#define DSP_TIMESLOT_TEST_UE0       0    /* Fxs0端口UE号 */
#define DSP_TIMESLOT_TEST_UE1       1    /* Fxs1端口UE号 */
#ifdef SUPPORT_ATP_DECT_VOICE
#define DECT_EEPROM_SUBSDATA_LEN    250   //DECT PCM切换TDM适配修改
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
** msg整改: 以后语音所有消息收发都是走msg组件，所以消息类型定义这里需要在voicecoremsgtypes.h
** 新增，这里VOICE_MSG_TYPE就可以不用增加了
*/
/******************************************************************************************/

typedef enum VOICE_MSG_TYPE
{
    /*语音进程内消息类型定义*/
    VOICE_MSG_TYPE_TAPI = 8840,   	/*tapi消息*/
    VOICE_MSG_TYPE_TIMER,         	/*timer消息*/
    VOICE_MSG_TYPE_TPTD,          	/*tptd消息*/
    VOICE_MSG_TYPE_SC,				/*SC消息*/
    VOICE_MSG_TYPE_CS,				/*CS消息*/
    VOICE_MSG_TYPE_PM,				/*PM消息*/
    VOICE_MSG_TYPE_MIC,             /*MIC消息*/
#ifdef SUPPORT_ATP_DIAG_POTS_MNG
    VOICE_MSG_TYPE_DIAG,            /*DIAG消息*/
#endif
    VOICE_MSG_TYPE_LINEMNG,
    VOICE_MSG_TYPE_ISDN,
    VOICE_MSG_TYPE_SIP,
	VOICE_MSG_TYPE_CMBS,           	/*cmbs target侧的消息*/
	VOICE_MSG_TYPE_DIAGLOG,         /* diag log消息. */

    /*语音进程外消息类型定义*/
    VOICE_MSG_TYPE_CLI = 8900,      /*CLI消息*/
    VOICE_MSG_TYPE_CMS,           	/*配置管理消息*/
    VOICE_MSG_TYPE_WEB,           	/*配置管理消息*/
    VOICE_MSG_TYPE_REBOOT,         	/*web进程消息,如修改需同步更新ATP_VOICE_MSG_REBOOT*/
    VOICE_MSG_TYPE_STOP,            /*web进程消息,如修改需同步更新ATP_VOICE_MSG_STOP*/
    VOICE_MSG_TYPE_WAN,             /*wan进程消息*/
    VOICE_MSG_TYPE_RESTORE,         /*恢复出厂配置消息*/
    VOICE_MSG_TYPE_ATS,             /*ATS反馈或上报给Voice消息*/
    VOICE_MSG_TYPE_QUERYSTATUS,     /*外部进程查询语音状态*/
    VOICE_MSG_TYPE_OFFHOOKPLAYINBAND, /*摘机状态机播放带内音消息*/

    VOICE_MSG_TYPE_GET_PINSTATUS,   /*获取当前页面解PIN状态*/
    VOICE_MSG_TYPE_SAVE_PININFO,    /*保存PIN信息*/

    VOICE_MSG_TYPE_BUTT
} VOICE_MSG_TYPE_E;

/*来自CLI的消息类型*/
typedef enum VOICE_CLI_MSG_TYPE_EN_
{
    VOICE_CLI_MSG_START = 1,   	    /*启动语音*/
    VOICE_CLI_MSG_STOP,	            /*终止语音*/
    VOICE_CLI_MSG_SIP_DNSFLUSHLIGHT,    /*清除语音dns缓存*/
    VOICE_CLI_MSG_SIP_DNSTTL0,          /*发出ttl0消息，触发语音发起更新dns查询*/
    VOICE_CLI_MSG_SIP_REG,        	/*注册sip账号*/
    VOICE_CLI_MSG_SIP_UNREG,        /*注销sip账号*/
    VOICE_CLI_MSG_SIP_REG_REPORTOK, /*不管SIP上行账号状态，都将其设成注册成功*/
    VOICE_CLI_MSG_VOICE_TAPI,
    VOICE_CLI_MSG_VOICE_LINEMNG,
    VOICE_CLI_MSG_VOICE_SC,
    VOICE_CLI_MSG_VOICE_DPLAN,
    VOICE_CLI_MSG_VOICE_PSTN,
    VOICE_CLI_MSG_VOICE_SIP,
    VOICE_CLI_MSG_VOICE_CUSTOMER,
    VOICE_CLI_MSG_VOICE_DECT,
    VOICE_CLI_MSG_QUERY_CFG,        /*查询语音业务配置信息*/
    VOICE_CLI_MSG_QUERY_TAPI_CFG,   /*查询tapi配置信息*/
    VOICE_CLI_MSG_CS_STAT,          /*查询CS注册和呼叫状态*/
    VOICE_CLI_MSG_QUERY_SIPID,      /*查询SIP帐号信息*/
    VOICE_CLI_MSG_QUERY_RTP,        /*查询RTP信息*/
    VOICE_CLI_MSG_QUERY_SIPSRV,     /*查询SIP服务器信息*/
    VOICE_CLI_MSG_QUERY_SIP_STAT, 	/*查询sip呼叫状态和注册状态*/
    VOICE_CLI_MSG_DBG_LEVEL,      	/*设置日志级别*/
    VOICE_CLI_MSG_DBG_TELNET,      	/*telnet输出调试信息*/
    VOICE_CLI_MSG_DBG_BR0,      	/*BR0上行*/
    VOICE_CLI_MSG_QUERY_REGINFO,	/*查询注册信息*/
    VOICE_CLI_MSG_DBG_CONSOLE,      /*console输出信息*/
    VOICE_CLI_MSG_VOICE_RWSLIC,     /*读写slic寄存器参数*/
    VOICE_CLI_MSG_VOICE_TONE,       /*播放指定Tone音*/
    VOICE_CLI_MSG_VOICE_CHANNEL,    /*测试FXS1和FXS2通话*/
    VOICE_CLI_MSG_VOICE_DSP_LOG,    /*设置DSP log级别*/
    VOICE_CLI_MSG_VOICE_DSP_TRACE,    /*DSP 抓包*/

    /*发给CMS的修改语音配置的消息*/
    VOICE_CLI_MSG_CFG_SET_LINEENABLE,    
    VOICE_CLI_MSG_CFG_SET_LINEID,
    VOICE_CLI_MSG_CFG_SET_LINEUSRNAME,
    VOICE_CLI_MSG_CFG_SET_LINEPWD,
    VOICE_CLI_MSG_CFG_SET_LINEPORT,    
	VOICE_CLI_MSG_UNKNOWN,
	
    VOICE_CLI_MSG_BUTT
}VOICE_CLI_MSG_TYPE_E;

/* 配置管理发送的指示 */
typedef enum VOICE_CMS_MSG_TYPE
{
    VOICE_CMS_MSG_SIP_REG,        	/*注册sip帐号*/
    VOICE_CMS_MSG_SIP_UNREG,        /*注销sip账号*/
    VOICE_CMS_MSG_WAN_STAT,       	/*WAN状态报告*/
    VOICE_CMS_MSG_UPDATE_CFG,     	/*更新了配置*/
    VOICE_CMS_MSG_EQUIPMENT_TSET,   /*装备测试*/
    VOICE_CMS_MSG_QUERY_SIP_STAT, 	/*配置管理消息,查询sip呼叫状态和注册状态*/
    VOICE_CMS_MSG_DBG_LEVEL,      	/*配置管理消息,设置日志级别*/
    VOICE_CMS_MSG_DBG_TELNET,      	/*配置管理消息,串口输出调试信息*/
    VOICE_CMS_MSG_QUERY_REGINFO,	/*查询注册信息*/
    VOICE_CMS_MSG_OUTLINE_CHANGED,  /*通知语音进程外线状态变化 */
    VOICE_CMS_MSG_FXO_RELAYCTL,     /*FXO继电器控制*/
    VOICE_CMS_MSG_DIAGBUTTON,       /*诊断按钮消息*/
    VOICE_CMS_MSG_LINERESET,        /*SIP账号重启*/
    VOICE_CMS_MSG_LINE_REREG,       /*SIP帐号先RESET再重启注册*/
    VOICE_CMS_MSG_STATUSQUERY,      /*清空帐号配置状态信息*/
    VOICE_CMS_MSG_CALLSTATUS_QUERY, /*线路呼叫状态查询*/
    VOICE_CMS_MSG_ANIMSN,           /*获取msn账号消息*/
    VOICE_CMS_MSG_WAN_WILLDOWN,     /*通知语音进程wan即将down*/
    VOICE_CMS_MSG_LAN_IPCHANGE,     /*通知语音进程LAN口维护地址改变了*/
    VOICE_CMS_MSG_WAKEUP_TIMECHANGE,/*更新闹铃定时器时间:配置变了或者系统时间变了*/
    /*HG253s V2语音定制:端口状态显示*/
    VOICE_CMS_MSG_PORTSTATUS_QUERY, /*端口状态查询*/
    VOICE_CMS_MSG_PROFILERESET,     
    /************** DECT START *****************/
    VOICE_CMS_MSG_DECT_RESTORE = 0x80, /*Dect状态更新(注册/注销引起的变化)*/
    VOICE_CMS_MSG_DECT_NAME,        /*Dect子机名称更新*/
    VOICE_CMS_MSG_DECT_LINESET,     /*Dect子机LineSettings更新*/ 
    VOICE_CMS_MSG_DECT_PAGE,        /*Dect子机查找*/
    VOICE_CMS_MSG_DECT_REGOPEN,     /*DECT允许子机注册*/
    VOICE_CMS_MSG_DECT_REGCLOSE,    /*DECT禁止子机注册*/
    VOICE_CMS_MSG_DECT_HS_REG,      /*DECT子机注册事件*/
    VOICE_CMS_MSG_DECT_HS_UNREG,    /*DECT子机注销事件*/
    VOICE_CMS_MSG_DECT_RFSET,       /*DECT射频开关*/
    /* begin added by xiehuiguang */
    VOICE_CMS_MSG_DECT_ANT0_TXSET,  /*天线0设置事件*/
    VOICE_CMS_MSG_DECT_ANT1_TXSET,  /*天线1设置事件*/
    VOICE_CMS_MSG_DECT_ANT0_TXDISPLAY,
    VOICE_CMS_MSG_DECT_ANT1_TXDISPLAY,
    VOICE_CMS_MSG_DECT_SETRGIQM,
    VOICE_CMS_MSG_DECT_GETRGIQM,
    VOICE_CMS_MSG_DECT_GETREGHS, 	/*DECT 获取子机列表信息*/
    VOICE_CMS_MSG_DECT_UARTSET,     /*DECT UART开关*/
    /* end */
    VOICE_CMS_MSG_DECT_SETNEMO,     /*DECT NEMO 模式设置*/
    VOICE_CMS_MSG_DECT_SETECO,      /*DECT ECO模式,射频调节设置*/
    VOICE_CMS_MSG_DECT_SETPCM,      /*PCM测试模式*/
    VOICE_CMS_MSG_DECT_PCMTEST,     /* pcm连通性测试 */
    VOICE_CMS_MSG_DECT_SETTIME,     /*DECT 时间同步*/
    VOICE_CMS_MSG_DECT_SETPIN,      /*DECT PIN设置*/
    VOICE_CMS_MSG_DECT_GETPIN,      /*DECT PIN获取*/
    VOICE_CMS_MSG_DECT_SETCALIB,    /*DECT 装备参数设置(RVBG,RVREF,RXTUN,RFPI)*/
    VOICE_CMS_MSG_DECT_GETCALIB,    /*DECT 装备参数获取(RVBG,RVREF,RXTUN,RFPI)*/
    VICCE_CMS_MSG_DECT_GETVER,      /*DECT 版本号获取*/
    VOICE_CMS_MSG_DECT_TESTMODE,    /*DECT 测试模式设置*/
    VOICE_CMS_MSG_DECT_EEPROMSET,   /*DECT 手工写EEPROM*/
    VOICE_CMS_MSG_DECT_REBOOT,      /*DECT 重启*/
    VOICE_CMS_MSG_DECT_TELBOOK,     /*DECT 电话本配置更新*/
    VOICE_CMS_MSG_DECT_UPDATE,      /*DECT 升级*/
    VOICE_CMS_MSG_DECT_RELOCK,      /*DECT RELOCK到Base*/
    VOICE_CMS_MSG_DECT_REINIT,      /*DECT 重新初始化*/
    VOICE_CMS_MSG_DECT_LOG,         /*DECT LOG*/    
    VOICE_CMS_MSG_DECT_EEPROMGET,   /*DECT 手工读EEPROM*/
    VOICE_CMS_MSG_DECT_GETSUBINFO,  /*DECT 获取注册信息*/
    VOICE_CMS_MSG_DECT_SETSUBINFO,  /*DECT 设置注册信息*/
    VOICE_CMS_MSG_DECT_GETBARCODE,  /*DECT 获取装备信息*/
    VOICE_CMS_MSG_DECT_SETBARCODE,  /*DECT 设置装备信息*/

    VOICE_CMS_MSG_DECT_GETINITSTAT, /*DECT 获取初始化状态*/
    VOICE_CMS_MSG_DECT_MISSCALLCHANGE,
	VOICE_CMS_MSG_DECT_LIST_CHANGE,
	VOICE_CMS_MSG_DECT_SETMWI,      /*DECT 留言灯设置*/
	VOICE_CMS_MSG_DECT_SETCMBSLINETYPE,    /*设置CMBS Line Type,满足认证要求*/
	VOICE_CMS_MSG_DECT_RESETALL,
	VOICE_CMS_MSG_DECT_CMSUPDATEMISS,
	VOICE_WEB_MSG_DECT_WEBUPDATEMISS,
	VOICE_CMS_MSG_DECT_CONTACTSNOTIFY,
	VOICE_CMS_MSG_DECT_NETPHONEBOOK_RESULT,  /*网络侧对Net Phone book 请求返回的结果*/
	
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
	VOICE_CMS_MSG_DECT_SETHALFTRANSMITPOWER,/*DECT发射功率的一半*/
	VOICE_CMS_MSG_DECT_MOBILE_UPDATE,	   /*子机信息刷新*/
    /************** DECT END *****************/
    VOICE_CMS_MSG_DECT_CATIQMODE,
    VOICE_CMS_MSG_DECT_ENCRYPTION,
    VOICE_CMS_MSG_UNKNOWN = 0xff,

} VOICE_CMS_MSG_EN;

typedef enum VOICE_ATS_MSG_TYPE
{
	VOICE_ATS_MSG_ATA_RSP            = 1,      /*下发的ATA指令反馈*/
	VOICE_ATS_MSG_CHUP_RSP           = 2,      /*下发的CHUP指令反馈*/
    VOICE_ATS_MSG_ATD_RSP            = 3,      /*下发的ATD指令反馈*/
    VOICE_ATS_MSG_DDSETEX_RSP        = 4,      /*下发的DDSETEX指令反馈*/ 
	VOICE_ATS_MSG_CHLD_RSP           = 5,      /*下发的CHLD指令反馈*/
	VOICE_ATS_MSG_CLIP_RSP           = 6,      /*下发的CLIP指令反馈*/
	VOICE_ATS_MSG_DTMF_RSP           = 7,      /*下发的DTMF指令反馈*/
	VOICE_ATS_MSG_CW_RSP             = 8,      /*下发的CW指令反馈*/
	
	VOICE_ATS_MSG_ORIG_REPORT        = 9,      /*ORIG指示上报*/
	VOICE_ATS_MSG_CLIP_REPORT        = 10,     /*CLIP指示上报*/
	VOICE_ATS_MSG_RING_REPORT        = 11,     /*RING指示上报*/  
	VOICE_ATS_MSG_CONF_REPORT        = 12,     /*CONF指示上报*/  
	VOICE_ATS_MSG_CONN_REPORT        = 13,     /*CONN指示上报*/ 
	VOICE_ATS_MSG_CEND_REPORT        = 14,     /*CEND指示上报*/
	
	VOICE_ATS_MSG_SYSINFO_REPORT     = 15,     /*SYSINFO指示上报*/
	VOICE_ATS_MSG_SIMSTATUS_REPORT   = 16,     /*SIMSTATUS指示上报*/
	VOICE_ATS_MSG_CSSI_REPORT        = 17,     /*CSSI指示上报*/
	VOICE_ATS_MSG_CSSU_REPORT        = 18,     /*CSSU指示上报*/ 
	VOICE_ATS_MSG_CCWA_REPORT        = 19,     /*CCWA指示上报*/

    VOICE_ATS_MSG_USB_STATUS_UPDATE  = 20,
   
    VOICE_ATS_MSG_CCALLSTATE_REPORT  = 21,     /*CCALLSTATE指示上报*/
    
    VOICE_ATS_MSG_CCFC_RSP           = 22,     /*下发的CCFC指令反馈*/
    VOICE_ATS_MSG_CLVL_RSP           = 23,     /*下发的CLVL指令反馈*/
    VOICE_ATS_MSG_CLCK_RSP           = 24,     /*下发的CLCK指令反馈*/
    VOICE_ATS_MSG_CPWD_RSP           = 25,     /*下发的CPWD指令反馈*/
    VOICE_ATS_MSG_CLIR_RSP           = 26,     /*下发的CLIR指令反馈*/
    VOICE_ATS_MSG_XLEMA_REPORT       = 27,     /*紧急号码上报 */
    VOICE_ATS_MSG_CSCHANINFO_REPORT  = 28,     /* CSCHANNELINFO指示上报.*/

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
    VOS_BOOL        bEnable;             /*是否使能*/
    VOS_UINT32      ulChannelId;         /*通道ID*/
    VOS_UINT32      ulSrcIp;             /*源IP*/
    VOS_UINT32      ulDesIp;             /*目的IP*/
    VOS_UINT32      ulSrcPort;           /*源端口*/
    VOS_UINT32      ulDesPort;           /*目的端口*/
}VOICE_DSP_TRACE_INFO_ST;

/*****************************************************************************
** 命令功能: USB状态变化
** 命令格式: 
** 响应格式: 
******************************************************************************/
typedef struct tagCS_MSG_USB_STATUS_ST
{
    unsigned char   ucCmdFrom;
    unsigned char   ucResult;
    unsigned char   ucStatus;
}CS_MSG_USB_STATUS_S;

/*****************************************************************************
** 命令功能: 系统的信息查询
** 命令格式: AT^SYSINFO
** 响应格式: <CR><LF>^SYSINFO:< srv_status >,< srv_domain >,< roam_status >,
             < sys_mode >,< sim_state >[,<lock_state>,<sys_submode>]<CR><LF><CR>
             <LF>OK<CR><LF> <CR><LF>^SYSINFO:< srv_status >,< srv_domain >,
             < roam_status >,< sys_mode >,< sim_state >[,<lock_state>,
             <sys_submode>]<CR><LF><CR><LF>OK<CR><LF>
******************************************************************************/
typedef struct tagCS_MSG_SYSINFO_ST
{
    unsigned char   ucCmdFrom;
    unsigned char   ucResult;
    unsigned char   ucSrvStatus;    /*系统服务状态.见CS_SERVER_STATUS_E,取值如下
                                      0:  无服务
                                      1:  有限制服务
                                      2:  服务有效 
                                      3:  有限制的区域服务
                                      4:  省电和深睡状态*/
    unsigned char   ucSrvDomain;    /*系统服务域.见CS_ZONE_STATUS_E,取值如下
                                      0： 无服务
                                      1： 仅CS服务
                                      2： 仅PS服务
                                      3： PS+CS服务
                                      4： CS、PS均未注册，并处于搜索状态
                                      255: CDMA不支持。
                                      250: 表示未获取到数值，无意义*/
    unsigned char   ucRoamStatus;   /*漫游状态.见CS_ROAM_STATUS_E,取值如下
                                      0： 非漫游状态
                                      1： 漫游状态*/
    unsigned char   ucSysMode;      /*系统模式.见CS_SYS_MODE_E,取值如下
                                      0： 无服务
                                      1： AMPS模式（暂不使用）
                                      2： CDMA模式（暂不使用）
                                      3： GSM/GPRS 模式
                                      4： HDR模式
                                      5： WCDMA模式
                                      6： GPS模式*/    
    unsigned char   ucSimState;     /*SIM卡状态.见CS_SIM_STATUS_E,取值如下
                                      0：  USIM卡状态无效
                                      1:   USIM卡状态有效  
                                      2：  USIM在CS下无效（EW）
                                      3：  USIM在PS下无效(EW)
                                      4：  USIM在PS+CS下均无效(EW)
                                      240: ROMSIM版本
                                      255: USIM卡不存在   
                                      250: 表示未获取到数值，无意义*/
    unsigned char   ucLockState;    /*SIM卡的LOCK状态.见CS_SIMLOCK_STATUS_E,取值如下
                                      0： SIM卡未被SIMLOCK功能锁定
                                      1： SIM卡被SIMLOCK功能锁定*/
    unsigned char   ucSysSubMode;   /*见CS_SUBSYS_MODE_E
                                      0：无服务
                                      1： GSM模式
                                      2： GPRS模式
                                      3： EDGE模式
                                      4： WCDMA模式
                                      5： HSDPA模式
                                      6： HSUPA模式
                                      7： HSDPA&HSUPA模式*/
    unsigned char   ucExtern1; //暂时 1代表LTE ONLY
    unsigned char   ucExtern2; //暂时 1代表VOLTE注册上了
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

/* WEB子消息*/
typedef enum VOICE_WEB_MSG_TYPE
{
    VOICE_WEB_MSG_PUK_REQUIRED       = 1,       /*页面上将pin码禁用不成功3次后需要输入PUK码*/
    VOICE_WEB_MSG_UNKNOWN = 0xff,
}VOICE_WEB_MSG_EN;

/* WAN子消息 */
typedef enum VOICE_WAN_MSG_TYPE
{
    ATP_UTIL_PPP_UP_MANUAL = 0,   // 手动建立连接成功
    ATP_UTIL_PPP_UP_AUTO = 1,      // 自动建立连接成功
    ATP_UTIL_PPP_UP_DEMAND = 2,   // 按需拨号建立连接成功
    ATP_UTIL_PPP_UP_VOICE = 3,     // VOIP摘机触发建立连接成功
    ATP_UTIL_PPP_DOWN_DSL = 4,   // DSL链路失败导致连接断开
    ATP_UTIL_PPP_DOWN_ECHO = 5,   // PPP ECHO请求无应答导致连接断开
    ATP_UTIL_PPP_DOWN_TIMEOUT = 6,  // 按需拨号超时无流量导致连接断开
    ATP_UTIL_PPP_FAIL_SVR = 7,  // BAS无响应导致拨号失败
    ATP_UTIL_PPP_FAIL_SVR_VOICE = 8, // BAS无响应导致VOICE摘机触发的拨号失败
    ATP_UTIL_PPP_FAIL_AUTH = 9,  // 认证错误导致拨号失败
    ATP_UTIL_PPP_FAIL_AUTH_VOICE = 10,  // 认证错误导致VOICE摘机触发的拨号失败
    ATP_UTIL_PPP_FAIL_NO_NAS = 11,  // 没有nas接口（当WAN PPP断掉时，摘机拨号失败）
    ATP_UTIL_DNS_TTL_EXPIRE_NOTIFY = 12, //dns srv ttl 超时通知
}VOICE_WAN_MSG_EN;

/*呼叫的路由类型枚举定义*/
typedef enum tagLINE_TYPE_EN
{
    LINE_TYPE_NULL      = 0x0,
    LINE_TYPE_PSTN      = (0x1 << 0),
    LINE_TYPE_SIP       = (0x1 << 1),
    LINE_TYPE_CS        = (0x1 << 2),
    LINE_TYPE_ISDN      = (0x1 << 3),
    LINE_TYPE_INCALL    = (0x1 << 4),   
    LINE_TYPE_MIX       = (0x1 << 5),       /* 混合呼叫 */
    LINE_TYPE_LCL       = (0x1 << 6),       /* 本地服务 */
	LINE_TYPE_AUTO		= (0x1 << 7),		/*  */
    
    LINE_TYPE_BUT,
}LINE_TYPE_EN;

/*模式选择:VOIP/PSTN模式下,ISDN号码无效不可配*/
typedef enum LINE_MODE_E_
{
    LINE_MODE_VOIP      = LINE_TYPE_SIP,
    LINE_MODE_PSTN      = (LINE_TYPE_PSTN | LINE_TYPE_SIP),
    LINE_MODE_ISDN      = (LINE_TYPE_ISDN | LINE_TYPE_SIP),
    LINE_MODE_AUTO      = (LINE_TYPE_PSTN | LINE_TYPE_ISDN | LINE_TYPE_SIP | LINE_TYPE_CS),
    LINE_MODE_CS        = (LINE_TYPE_CS),
    LINE_MODE_BUTT
}LINE_MODE_E;

/*端口类型枚举定义*/
typedef enum tagPORT_TYPE_E_
{
    PORT_TYPE_NULL_ = 0,
    PORT_TYPE_FXS,                      /*FXS口*/
    PORT_TYPE_HS,                       /*DECT子机,HandleSet(HS)*/
    PORT_TYPE_ISDN,                       /*ISDN话机,下行ISDN*/
	PORT_TYPE_SIP,

    PORT_TYPE_BUTT,
}PORT_TYPE_E;


/*FXO口状态枚举定义*/
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
    VOICE_OPTIONS_DISABLE_EN    = 0,          /*不进行Options检测/发送*/        
    VOICE_OPTIONS_SEND_EN       = 1,          /*主动发送*/
    VOICE_OPTIONS_DETECT_EN     = 2,          /*主动检测*/
    VOICE_OPTIONS_MAX_EN
}VOICE_SIPOPTIONS_TYPE_EN;

typedef enum tagPORTBINDING_MODE_EN
{
    PORTBINDING_MODE_AUTO    =   0,          /*Auto*/
    PORTBINDING_MODE_SINGLE,                 /*一个端口只能绑定一个账号,该特性需要页面也做相应修改*/
    PORTBINDING_MODE_CUSTOMER,               /*绑定端口定制*/
    //PORTBINDING_MODE,                      /*其他扩展方式*/
}PORTBINDING_MODE_EN;

/*2_10	SIP.SupportSIPLocalPort模式*/
typedef enum tagVOICE_SIP_LOCAL_PORT_MODE_EN
{
    VOICE_SIP_LOCAL_PORT_DISABLE = 0,    /*平台通用方式:不使用X_SIPLocalPort*/
    VOICE_SIP_LOCAL_PORT_RELATED,        /*HG659卡塔尔定制:同一个profile下的SIP 帐号用相同的X_SIPLocalPort,与UserAgentPort一致.*/
    VOICE_SIP_LOCAL_PORT_SEPARATE,       /*HG658V2-20罗电定制:不同的SIP 帐号可配置不同的X_SIPLocalPort.*/
}VOICE_SIP_LOCAL_PORT_MODE_EN;

/*数图格式枚举*/
//#ifdef SUPPORT_ATP_VCESIP_DIGITMAP_H248
typedef enum tagVOICE_DIGITMAP_FORMAT_EN
{
    VOICE_DIGITMAP_FORMAT_EXT        = 0x0,
    VOICE_DIGITMAP_FORMAT_MGCP       = 0x1 << 1,   /* MGCP格式数图 */
    VOICE_DIGITMAP_FORMAT_H248       = 0x1 << 2,   /* H248格式数图 */
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
    VOS_CHAR      acInfName[VOICE_INTERFACENAME_LEN];  /* 语音现在使用的Wan接口名 */
    VOS_BOOL      bInternetWan;                         /* 此Wan是否为Internet Wan */
    VOS_BOOL      bInternetToVoice;                     /* 是否从Internet Wan切到语音wan */
}VOICE_WAN_ST;

/*消息子事件*/
typedef struct tagATP_VOICE_MSG_ST_
{
    VOS_UINT32  ulEventType;                    /*事件类型,见不同消息下的事件类型*/
    VOS_UINT32  ulPara;                         /*事件参数*/
    VOS_CHAR    szBoby[ATP_VOICE_EVENT_LEN];    /*事件数据*/
}ATP_VOICE_MSG_S;

/*语音消息结构体*/
typedef struct tagATP_VOICE_MSG_BUF_ST_
{
    VOS_INT32  lMsgType;                        /*消息类型. 见VOICE_MSG_TYPE_E*/
    VOS_CHAR   szMsgBody[ATP_VOICE_MSG_LEN];    /*消息内容*/
}ATP_VOICE_MSG_BUF_S;

typedef struct tagGLOBAL_CFG_FROM_WEB_ST_
{
    VOS_UINT32  ulPrimaryCheckExpires;                  /* 探测回切时间 */
    VOS_UINT32  ulMaxRetryTime;                         /* 协议栈重试时间 */
    VOS_UINT32  ulRegExpire;                            /* 注册Expire时间,单位s                 */
    VOS_CHAR    acIsdnAreaCode[VOICE_AREA_LEN];         /* ISDN号码区号                         */
    VOS_CHAR    szIfName[VOICE_INTERFACENAME_LEN];      /* 上行接口名                           */
    VOS_CHAR    acPSTNNumber[VOICE_PSTN_NUMBER_LEN];    /* PSTN号码                             */
    VOS_CHAR    acUMTSNumber[VOICE_UMTS_NUMBER_LEN];    /* UMTS号码                             */
    VOS_BOOL    bUmts;                                  /* 是否启用UMTS语音                     */
    VOS_BOOL    bPstnEnable;                            /* 是否启用pstn                         */
    VOS_BOOL    bPstnClipEnable;                        /* PSTN线路是否启用CLIP                 */
    VOS_BOOL    bUmtsClipEnable;                        /* UMTS线路是否启用CLIP                 */
    VOS_UINT32  ulUmtsDTMFMethod;                       /* 0为CS带外DTMF，1为CS带内DTMF         */
    VOS_CHAR    acCallAllPortsPrefix[SIP_MAX_NUM_LEN];  
    VOS_UINT8   ucUrgenceRouteType;                     /* 紧急号码呼出线路类型,见LINE_TYPE_EN  */
    VOS_CHAR    acUrgenceRouteAccount[SIP_MAX_NUM_LEN]; /* 紧急号码呼出关联号码                 */   


    VOS_CHAR    acVoipDigitMap[VOICE_VOIP_DIGITMAP_LEN];     /* VOIP数图 */
    VOS_BOOL    bHEnable;                                    /* 是否支持#加速*/
    VOS_BOOL    bEnableHotLine;                              /* 是否支持热线号码*/
    VOS_UINT32  ulHotLineInterval;                           /* 热线号码启动时间间隔*/
    VOS_CHAR    acHotLineNumber[VOICE_HOTLINE_NUMBER_LEN];   /* 热线号码*/
    VOS_UINT32  ulOffHookTime;
    VOS_UINT32  ulOnHookTime;
    VOS_UINT32  ulMinHookFlash;
    VOS_UINT32  ulMaxHookFlash;
    VOS_BOOL    bRegDetect;                          /*是否启动探测流程*/
    VOS_UINT32  ulRegRetry;                          /* 注册重发时间,单位秒,用作一轮服务器尝试完成后的等待间隔*/
    VOS_UINT32  ulRegTimeoutRetry;                    /* 注册超时重发时间,单位秒,用作一轮服务器尝试完成后的等待间隔*/
    
    VOS_BOOL    bNeedPrack;                          /* 是否需要支持Prack方法*/    
    VOS_BOOL    bUrgCallHead;                        /* 紧急呼叫是否加紧急呼叫头域*/
    VOS_UINT32  ulSessExpire;                        /* Session的Update时间,单位s*/
    VOS_UINT32  ulMinSE;                             /* Min-SE时间,单位s*/
    VOS_UINT32  ulHoldMethod;                        /* 呼叫保持的方法,见SIP_HOLD_METHOD_E*/
    VOS_UINT32  ulMwiExpire;                         /* MWI的Expire时间,单位s*/
    VOS_UINT32  ulUaProfileExpire;                   /* UA Profile的Expire时间,单位s*/
    VOS_UINT32  ulReginfoExpire;                     /* Reg订阅Expire时间，单位s*/
    VOS_UINT32  ulOptionChkType;                     /* Option检测方法,0--不检测;1--对端发;2--本端发*/
    VOS_UINT32  ulOptionChkTimeLen;                  /* Option检测间隔时长,单位s*/ 
    VOS_UINT32  ulOptDetInterval;                    /*  */
    VOS_UINT32  ulOptDetRetryInterval;               /*  */
    VOS_UINT32  ulOptDetRegRetryInterval;            /*  */
    VOS_UINT32  ulDigitShortTime;                    /* 拨号号间间隔短定时器时长,单位ms*/
    VOS_UINT32  ulDigitLongTime;                     /* 拨号号间间隔长定时器时长,单位ms */
    VOS_UINT32  ulDialToneTime;                      /* 拨号音时长,单位ms*/
    VOS_UINT32  ulRingTime;                          /* 振铃时长,单位ms*/
    VOS_UINT32  ulHowlToneTime;                      /* 嚎鸣音时长,单位ms*/
    VOS_UINT32  ulBusyToneTime;                      /* 忙音时长,单位ms*/
    VOS_UINT32  ulCFNRTime;                          /* 呼叫无应答前转振铃时长:超过这个时间则进行前转,单位s*/

#ifdef SUPPORT_ATP_VCESIP_DIGITMAP_H248
    VOS_UINT32  ulH248DigitShortTimer;                /*H248数图短超时时间*/
    VOS_UINT32  ulH248DigitLongTimer;                 /*H248数图长超时时间*/
    VOS_UINT32  ulDigitMapFormat;                     /*数图格式如:H248数图等,见VOICE_DIGITMAP_FORMAT_EN*/  
#endif   
    VOS_BOOL    bVoiceDiag;                          /* 是否在装备测试 */
    VOS_CHAR    szProfileBody[VCE_STR_LEN_2K];       /* 记录定制项的profile body */

    /*HG253s V2语音定制要求实现:SIP打DSCPmark*/
    VOS_UINT32  ulSIPDSCPMark;
    VOS_BOOL    bRingScheduleEnable;

    VOS_UINT32  ulVoipDiagLogLevel;                 /* Voip Diagnostics Log Level */
	
    VOS_UINT8   szFmcClipOption;                 /* fmc clip option,1-DTMF,2-FSK_ITU,3-FSK_BELL,4-FSK_RPAS */
    VOS_BOOL    bFmcUmtsClipEnable;              /* fmc umts clip enable, 1-enable, 0-disable */
    
    VOS_BOOL    bProfileCallWaitingEnable;      /* Profile下的CallWaitingEnable控制*/ 

    VOS_UINT32  ulCIDSig;                       /*CID信号遵循协议: DTMF还是FSK*/    
    VOS_BOOL    bVMIndTone;                     /* VoiceMail提示音 */
#ifdef SUPPORT_ATP_LMT_CFU_TONE
    VOS_BOOL    bCfuIndTone;                     /* call forwarding提示音 */
#endif
   VOS_BOOL    bUtEnable;                            /* 是否启用ut                         */	
}GLOBAL_CFG_FROM_WEB_S, *GLOBAL_CFG_FROM_WEB_PS;

typedef struct tagLINE_CFG_FROM_WEB_ST_
{
    VOS_BOOL    bEnable;                        /*帐号使能*/
    VOS_BOOL    bReset;                         /* 是否重置该SIP帐号*/
    VOS_BOOL    bPortEnable;                    /*账号的端口使能,HG253sV2端口功能定制实现*/
    VOS_UINT32  ulLineIndex;                    /*本地帐号索引,Id*/    
    VOS_CHAR    szId[SIP_MAX_NUM_LEN];          /*SIP帐号*/
    VOS_CHAR    szUserName[SIP_MAX_NAME_LEN];   /*用户名*/
    VOS_CHAR    szPassword[SIP_MAX_PSW_LEN];    /*密码*/
    VOS_CHAR    szDisplayName[SIP_MAX_NAME_LEN]; /*姓名显示*/
    VOS_CHAR    szCode[SIP_MAX_NUM_LEN];        /*区号*/
    VOS_BOOL    bEnableCode;                    /*区号是否使能*/
    VOS_BOOL    bCallerIDRestrictionEnable;      /*CallerIDRestrictin是否使能*/       
    VOS_BOOL    bBusyOnBusy;                    /*Busy On Busy是否开启*/
    VOS_BOOL    bMultiLine;                     /* 新增线路MultiLine属性*/
    VOS_UINT8   ucProtocolType;                 /*协议类型:1.UDP 2.TCP 3.TLS 4.SCTP*/
    VOS_UINT16  uwLocalPort;                    /*local port*/
    VOS_CHAR    szRegServer[VCE_LINE_SRV_MAX][SIP_MAX_URL_LEN];   /*注册服务器*/
    VOS_CHAR    szSipDomain[VCE_LINE_SRV_MAX][SIP_MAX_URL_LEN];   /*注册SIPDomain */
    VOS_CHAR    szOutProxy[SIP_MAX_URL_LEN];    /*outbound proxy server*/
    VOS_CHAR    szProxyServer[VCE_LINE_SRV_MAX][SIP_MAX_URL_LEN]; /*代理服务器*/
    VOS_CHAR    szStunServer[SIP_MAX_URL_LEN];  /*stun服务器*/
    VOS_UINT16  uwRegPort[VCE_LINE_SRV_MAX];    /*注册服务器端口号*/
    VOS_UINT16  uwOutProxyPort;                 /*outbound proxy port*/
    VOS_UINT16  uwProxyPort[VCE_LINE_SRV_MAX]; /*代理服务器端口号*/
    VOS_UINT16  uwStunPort;                     /*stun服务器端口号*/
    VOS_BOOL    bCLIPEnable;                    /*CLIP启动*/
    VOS_BOOL    bMwiEnable;                     /*MWI是否使能*/
    VOS_BOOL    bUaProfileEnable;               /*UA_PROFILE订阅是否使能*/
    VOS_BOOL    bReginfoEnable;                 /*REG订阅是否使能*/
    VOS_BOOL    bCHEnable;                      /*CallHold是否使能*/
    VOS_BOOL    bCWEnable;                      /*CallWaiting是否使能*/
    VOS_BOOL    bCTREnable;                     /*CallTransfer是否使能*/
    VOS_UINT32  ulMaxSessions;                  /*三方通话是否开启*/

	VOS_CHAR	szHotLineNumber[VOICE_HOTLINE_NUMBER_LEN];
	VOS_UINT32  ulHotLineTimeout;
    VOS_BOOL    bHotLineEnable;
    VOS_UINT32  ulNumberDisplayType;
    VOS_UINT32  ulPrivacyLevel;
}LINE_CFG_FROM_WEB_S, *LINE_CFG_FROM_WEB_PS;

typedef struct tagISDN_LINE_CFG_FROM_WEB_ST_
{
    VOS_CHAR    szNumber[VOICE_ISDN_NUMBER_LEN];/*ISDN号码*/
    VOS_BOOL    bBusyOnBusy;                    /*Busy On Busy是否开启*/
    VOS_BOOL    bCLIPEnable;                    /*CLIP是否开启*/
}ISDN_LINE_CFG_FROM_WEB_S, *ISDN_LINE_CFG_FROM_WEB_PS;

#ifdef SUPPORT_ATP_DECT_VOICE
typedef struct tagVOICE_DECT_LINE_NOTIFY_OBJ
{
    VOS_UINT32  ulNumber;
    VOS_UINT32  auLineId[VOICE_DECT_LINE_MAX];
}DECT_VOICE_LINE_NOTIFY_ST;

typedef struct
{
    VOS_UINT8       u8_IPUI[VCE_STR_LEN_64];    /*!< Handset identity >suota升级时用*/
}DECT_HS_IPUI_ST;
typedef struct tagMOBILE_CFG_ST_
{
    VOS_BOOL    bEnable;                /*端口是否使能.Dect没注册上为Disable;注册上为Enable*/
    VOS_UINT8   ucPortID;               /*端口ID*/
    VOS_UINT8   ucLineID;               /*内部号码序列号，起始号码见VCE_INCALL_BASE*/
    VOS_UINT8   ucDectType;             /*Dect子机类型:0表示GAP，1表示CATIQ1，2表示CATIQ2，见DECT_TYPE_E */
    VOS_UINT8   ucInLineNum;            /*呼入关联帐号数目*/
    VOS_UINT8   ucOutLineNum;           /*呼出关联帐号数目*/
    VOS_UINT8   ucReserve;
    VOS_BOOL    bInRelateAll;           /*呼入关联所有*/
    VOS_BOOL    bOutRelateAuto;         /*呼出自动选帐号*/
    VOS_UINT8   aucIncomingLine[VCE_LINE_MAX];  /*呼入关联帐号. 存放关联帐号索引*/
    VOS_UINT8   aucOutgoingLine[VCE_LINE_MAX];  /*呼出关联帐号. 存放关联帐号索引*/
    VOS_CHAR    szName[VOICE_DECT_NAME_LEN];       /*端口名*/
    VOS_CHAR    acIncallNumber[VOICE_INCALL_LEN];/*内部短号*/
    VOS_INT     iCFUDestPortId;         /*无条件前转目的端口号，范围0~6，无业务时为-1*/
    VOS_INT     iCFBDestPortId;         /*遇忙目的端口号，范围0~6，无业务时为-1*/
    VOS_INT     iCFNRDestPortId;        /*无应答目的端口号，范围0~6，无业务时为-1*/
}MOBILE_CFG_S;
typedef struct tagDECT_CFG_FROM_WEB_ST_
{
    VOS_BOOL    	bEnable;                        /*dect使能*/
	VOS_BOOL        bEnableNemo;               /*使能dect发射功率的一半*/
	VOS_BOOL	    bEnableEco;           /*使能dect生态模式使能*/
    VOS_CHAR    szPin[VCE_PIN_LEN_MAX];         /*dect子机PIN码*/
	VOS_BOOL   bEnableEcologicalModel;          /*使能dect生态模式使能*/
	VOS_BOOL   bEnableHalfTransmitPower;        /*使能dect发射功率的一半*/
	VOS_CHAR   szSubsData[DECT_CMO_SUBSDATA_MAX_LEN]; /*备份子机注册信息*/
    VOS_UINT32 ulNewMobilId;                    /*记录刚刚注册上的子机id，供cgi返回给页面*/
    DECT_HS_IPUI_ST stHsIpui[VCE_DECT_HS_MAX];
	MOBILE_CFG_S	stMobile[DECT_SET_NUM];
}DECT_CFG_FROM_WEB_S, *DECT_CFG_FROM_WEB_PS;
/*Dect子机类型*/
typedef enum tagDECT_TYPE_E_
{
    DECT_TYPE_GAP	= 0,
    DECT_TYPE_CATIQ1,
    DECT_TYPE_CATIQ2,
    DECT_TYPE_DSPG,
	DECT_TYPE_UNKNOW,
}DECT_TYPE_E;
/* 配置类型*/
typedef enum tagDECT_CFG_TYPE_E_
{
    DECT_CFG_NORMAL   = 0,       /* 正常情况 */
    DECT_CFG_EQUIP,              /* 装备命令配置DECT对码 */
    DECT_CFG_PP,                 /* 子机动作引起的注销 */
    DECT_CFG_OTHER,
}DECT_CFG_TYPE_E;
typedef struct tagDECT_HS_TYPE_ST
{
    VOS_UINT32      ulHsId;     /*取值范围1~5*/
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

/*Dect配置发生更改的类型*/
typedef enum tagDECT_COMMONCFG_SETTYPE_E_
{
    DECT_SETTYPE_ADD   = 0,       /* 增加 */
    DECT_SETTYPE_DEL,             /* 删除 */
    DECT_SETTYPE_SET,             /* 修改 */
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
    VOS_BOOL    bEnable;                /*端口是否使能*/
    VOS_UINT8   ucPortID;               /*端口ID*/
    VOS_UINT8   ucLineID;               /*内部号码序列号，起始号码见VCE_INCALL_BASE*/
//    VOS_UINT8   ucPortType;             /*端口类型:FXS口,dect子机,ISDN下行话机,见PORT_TYPE_E*/
    VOS_UINT8   ucDectType;             /*Dect子机类型:0表示GAP，1表示CATIQ1，2表示CATIQ2，见DECT_TYPE_E */
    VOS_UINT8   ucInLineNum;            /*呼入关联帐号数目*/
    VOS_UINT8   ucOutLineNum;           /*呼出关联帐号数目*/
//    VOS_UINT8   ucReserve;
    VOS_BOOL    bInRelateAll;           /*呼入关联所有*/
    VOS_BOOL    bOutRelateAuto;         /*呼出自动选帐号*/
    VOS_UINT8   aucIncomingLine[VCE_LINE_MAX];  /*呼入关联帐号. 存放关联帐号索引*/
    VOS_UINT8   aucOutgoingLine[VCE_LINE_MAX];  /*呼出关联帐号. 存放关联帐号索引*/
    VOS_CHAR    szName[VOICE_INCALL_NAME_LEN];       /*端口名*/
    VOS_CHAR    acIncallNumber[VOICE_INCALL_LEN];/*内部短号*/
    VOS_BOOL    bCFUEnable;             /*端口无条件前转使能配置*/
    VOS_BOOL    bCFBEnable;             /*端口遇忙前转使能配置*/
    VOS_BOOL    bCFNREnable;            /*端口无应答前转使能配置*/
    VOS_INT     iCFUDestPortId;         /*无条件前转目的端口号，范围0~6，无业务时为-1*/
    VOS_INT     iCFBDestPortId;         /*遇忙目的端口号，范围0~6，无业务时为-1*/
    VOS_INT     iCFNRDestPortId;        /*无应答目的端口号，范围0~6，无业务时为-1*/
}PHY_CFG_FROM_WEB_S, *PHY_CFG_FROM_WEB_PS;

typedef struct tagPHONE_BOOK_CFG_FROM_WEB_ST_
{
    VOS_CHAR    szName[SIP_MAX_NAME_LEN];       /*姓名*/
    VOS_CHAR    szPrivateNum[SIP_MAX_NUM_LEN];  /*私人电话*/
    VOS_CHAR    szFamilyNum[SIP_MAX_NUM_LEN];   /*家庭电话*/
    VOS_CHAR    szMobileNum[SIP_MAX_NUM_LEN];   /*移动电话*/
}PHONE_BOOK_CFG_FROM_WEB_S, *PHONE_BOOK_CFG_FROM_WEB_PS;

typedef struct tagSIPSERVER_LINE_CFG_ST_
{
    VOS_CHAR    szId[SIP_MAX_NUM_LEN];          /* SIP帐号*/
    VOS_BOOL    bAuth;                          /* 是否需要鉴权*/
    VOS_CHAR    szUserName[SIP_MAX_NAME_LEN];   /* 用户名*/
    VOS_CHAR    szPassword[SIP_MAX_PSW_LEN];    /* 密码*/
    
    VOS_UINT8   ucInLineNum;                    /* 呼入关联帐号数目*/
    VOS_UINT8   ucOutLineNum;                   /* 呼出关联帐号数目*/
    VOS_UINT8   ucReserve;
    VOS_BOOL    bInRelateAll;                   /* 呼入关联所有*/
    VOS_BOOL    bOutRelateAuto;                 /* 呼出自动选帐号*/
    VOS_UINT8   aucIncomingLine[VCE_LINE_MAX];  /* 呼入关联帐号. 存放关联帐号索引*/
    VOS_UINT8   aucOutgoingLine[VCE_LINE_MAX];  /* 呼出关联帐号. 存放关联帐号索引*/
    VOS_INT32   iCFUDestPortId;
    VOS_INT32   iCFBDestPortId;
    VOS_INT32   iCFNRDestPortId;
}SIPSERVER_LINE_CFG_S, *SIPSERVER_LINE_CFG_PS;

typedef struct tagSIPSERVER_CFG_FROM_WEB_ST_
{
    VOS_UINT32  ulServerPort;
    VOS_UINT32  ulMinRegExpire;                         /* 注册Expire时间,单位s*/
    VOS_UINT32  ulSessExpire;                        /* Session的Update时间,单位s*/
    VOS_UINT32  ulMinSE;                             /* Min-SE时间,单位s*/
    SIPSERVER_LINE_CFG_S   stSipServerLine[SIPPHONE_SET_NUM];/*Sip Server支持的账号*/
}SIPSERVER_CFG_FROM_WEB_S, *SIPSERVER_CFG_FROM_WEB_PS;

typedef struct tagROUTE_FIX_CFG_FROM_WEB_ST_
{
    VOS_CHAR    acRouteFix[SIP_MAX_NUM_LEN];        /*路由前后缀*/
    VOS_CHAR    acAccount[SIP_MAX_NUM_LEN];         /*关联号码*/
    VOS_UINT8   ucType;                             /*线路类型,见LINE_TYPE_EN*/
    VOS_UINT8   ucReserve[3];                       /*保留字节*/
}ROUTE_FIX_CFG_FROM_WEB_S, *ROUTE_FIX_CFG_FROM_WEB_PS;

typedef struct tagIN_FIX_CFG_FROM_WEB_ST_
{
    VOS_CHAR    acInFix[SIP_MAX_NUM_LEN];           /*呼入前后缀*/
}IN_FIX_CFG_FROM_WEB_S, *IN_FIX_CFG_FROM_WEB_PS;

typedef struct tagOUT_FIX_CFG_FROM_WEB_ST_
{
    VOS_CHAR    acOutFix[SIP_MAX_NUM_LEN];          /*呼出前后缀*/
    VOS_CHAR    acNumber[SIP_MAX_NUM_LEN];          /*关联号码*/
}OUT_FIX_CFG_FROM_WEB_S, *OUT_FIX_CFG_FROM_WEB_PS;

typedef struct tagSPEEDDIAL_CFG_FROM_WEB_ST_
{
    VOS_CHAR    acSrcNumber[SIP_MAX_NUM_LEN];       /*缩位号码*/
    VOS_CHAR    acDstNumber[SIP_MAX_NUM_LEN];       /*实际号码*/
}SPEEDDIAL_CFG_FROM_WEB_S, *SPEEDDIAL_CFG_FROM_WEB_PS;

typedef struct tagWAKEUP_CFG_FROM_WEB_ST_
{   
    VOS_BOOL     bEnable;                          /*闹铃使能*/
    VOS_UINT32   ulTime;                          /*闹铃时间*/
    VOS_CHAR     szWeekDay[VCE_STR_LEN_64];          /*闹铃日期*/
    VOS_CHAR     szName[VCE_WAKEUP_NAME_LEN];          /*闹铃名称 */
}WAKEUP_CFG_FROM_WEB_S, *WAKEUP_CFG_FROM_WEB_PS;

typedef struct tagRINGSCHEDULE_CFG_FROM_WEB_ST_
{   
    VOS_UINT32     ulStartTime;          /*RingSchedule起始时间*/
    VOS_UINT32     ulEndTime;          /*RingSchedule结束时间*/
}RINGSCHEDULE_CFG_FROM_WEB_S, *RINGSCHEDULE_CFG_FROM_WEB_PS;

typedef struct tagVOICE_SVC_CFG_FROM_WEB_ST_
{
    GLOBAL_CFG_FROM_WEB_S       stGlobal;                   /*语音业务全局配置*/
    LINE_CFG_FROM_WEB_S         stLine[VCE_VOIP_MAX];       /*SIP帐号配置*/
    ISDN_LINE_CFG_FROM_WEB_S    stIsdnLine[VCE_ISDN_MAX]; /*ISDN帐号配置,*/
    ISDN_LINE_CFG_FROM_WEB_S    stIsdnDft; 					/*默认ISDN帐号配置,*/
#ifdef SUPPORT_ATP_DECT_VOICE
    DECT_CFG_FROM_WEB_S         stDect;                     /*DECT全局配置*/
    PHY_CFG_FROM_WEB_S          stPhy[VCE_PORT_MAX];        /*FXS口配置*/
#else
    PHY_CFG_FROM_WEB_S          stPhy[POTS_SET_NUM];        /*FXS口配置*/
#endif
#ifdef SUPPORT_ATP_SIP_SERVER
    SIPSERVER_CFG_FROM_WEB_S    stSipServer;                /*SipServer配置*/
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

/*子机呼叫消息结构体*/
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

/*HG253s V2语音定制:端口状态显示*/
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

/*前转类型*/
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

/*更新前转消息结构*/
typedef struct tagATP_VOICE_CFINFO_ST
{
    VOS_INT    iSrcPortId;
    VOS_INT    iDstPortId;
    VOICE_CF_TYPE_EN enCFType;
} ATP_VOICE_CFINFO_ST;


typedef struct tagVOICE_CFG_FROM_CLI_ST_
{
    VOS_UINT32  ulEventType;          /*事件类型，即要配置的参数类型*/
    VOS_UINT32  ulProfileInst;        /*该profile实例号*/
    VOS_UINT32  ulLineInst;           /*line实例号*/
    VOS_UINT32  ulPara;                                         
    VOS_CHAR    szMsgData[VCE_STR_LEN_256];             
}VOICE_CFG_FROM_CLI_S;

/*会话信息*/
typedef struct tagSESSION_STATE_ST_
{   
    VOS_UINT32      ulStartYear;
    VOS_UINT32      ulStartMonth;
    VOS_UINT32      ulStartDay;
    VOS_UINT32      ulStartHour;
    VOS_UINT32      ulStartMinute;
    VOS_UINT32      ulStartSecond;
    VOS_UINT32      ulStartTime;                            /*开始时刻*/
    VOS_UINT32      ulEndTime;                              /*结束时刻,如果为0,表示还未结束*/

    VOS_UINT32      ulDuration;                             /*通话时长*/
    VOS_UINT32      ulFarEndIP;                             /*远端地址*/
    VOS_UINT16      uwFarEndUDPPort;                        /*远端RTP端口*/
    VOS_UINT16      uwLocalUDPPort;                         /*本端RTP端口*/
}SESSION_STATE_S, *SESSION_STATE_PS;


/*RTCP信息统计*/
typedef struct tagRTCP_INFO_ST_
{
    VOS_UINT32  ulPacketsSent;                          /*已发送报文个数*/
    VOS_UINT32  ulPacketsReceived;                      /*已接收报文个数*/
    VOS_UINT32  ulBytesSent;                            /*已发送报文字节数*/
    VOS_UINT32  ulBytesReceived;                        /*已接收报文字节数*/
    VOS_UINT32  ulPacketsLost;                          /*已丢失报文个数*/

    /*Total number of times the receive jitter buffer has overrun for this line*/
    VOS_UINT32  ulOverruns;                             /*超出抖动范围外的报文个数*/

    /*Total number of times the receive jitter buffer has underrun for this line*/
    VOS_UINT32  ulUnderruns;                            /*抖动范围内的报文个数*/

    /*Current receive packet loss rate in percent*/
    VOS_UINT32  ulReceivePacketLossRate;                /*本端丢包率*/

    /*Current far end receive packet lost rate in percent*/
    VOS_UINT32  ulFarEndPacketLossRate;                 /*远端丢包率*/

    /*Current receive interarrival jitter in microseconds*/
    VOS_UINT32  ulReceiveInterarrivalJitter;            /*本端抖动时间间隔*/

    /*Current Interarrival jitter in microseconds as reported from the far-end device via RTCP*/
    VOS_UINT32  ulFarEndInterarrivalJitter;             /*远端抖动时间间隔*/

    /*Current round trip delay in microseconds*/
    VOS_UINT32  ulRoundTripDelay;                       /*往返延迟[RFC3550 6.4]*/

    /*Average receive interarrival jitter in microseconds since the beginning of the current call*/
    VOS_UINT32  ulAverageReceiveInterarrivalJitter;     /*本端平均抖动时间间隔*/

    /*Average far-end interarrival jitter in microseconds since the beginning of the current call*/
    VOS_UINT32  ulAverageFarEndInterarrivalJitter;      /*远端平均抖动时间间隔*/

    /*Average round trip delay in microseconds since the beginning of the current call*/
    VOS_UINT32  ulAverageRoundTripDelay;                /*平均往返延迟*/
}RTCP_INFO_ST;

/*IMS订阅业务显示*/
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


/*帐号状态*/
typedef struct tagLINE_STATE_ST_
{
    VOS_CHAR        szId[SIP_MAX_NUM_LEN];                  /*Line帐号*/
    VOS_CHAR        szCallStatus[VCE_STR_LEN_16];   
    VOS_UINT8       ucRegStatus;                            /*号码注册状态*/
    VOS_UINT8       ucRegFailReason;                        /*注册失败原因*/

    VOS_UINT32      ulCallDir;

    VOS_UINT32      ulReadyFlag;                            /*信息是否Ready的标志位*/
    VOS_BOOL        bResetStatistics;                       /*是否清空统计*/
    VOS_UINT32      ulIncomingReceived;                     /*呼入电话个数*/
    VOS_UINT32      ulIncomingAnswered;                     /*呼入已接电话个数*/
    VOS_UINT32      ulIncomingConnected;                    /*呼入成功电话个数*/
    VOS_UINT32      ulIncomingFailed;                       /*呼入失败电话个数*/
    VOS_UINT32      ulOutgoingAttempted;                    /*呼出电话个数*/
    VOS_UINT32      ulOutgoingAnswered;                     /*呼出已接电话个数*/
    VOS_UINT32      ulOutgoingConnected;                    /*呼出成功电话个数*/
    VOS_UINT32      ulOutgoingFailed;                       /*呼出失败电话个数*/
    VOS_UINT32      ulCallsDropped;                         /*通话不正常中断个数*/
    VOS_UINT32      ulTotalCallTime;
	VOS_UINT32      ulMWINum;                               /*MWI数目*/

    VOS_UINT32      ulSrvDownStartTime;                      /*一次服务器DOWN的开始时间，理解为注册不上的时间*/
    VOS_UINT32      ulAccumSrvDownTime;                     /*上一次恢复注册时累积的DOWN时间*/
    VOS_UINT32      ulSeverDownTime;                        /*账号注册不上的累积时间*/

    /*HG253s V2语音会话过程中编解码节点显示功能*/
    VOS_UINT32      ulTransmitCodec;                        /*呼出建立通话时的编解码*/
    VOS_UINT32      ulReceiveCodec;                         /*呼入建立通话时的编解码*/

    SESSION_STATE_S stSession[SIP_LINE_STATE_SESS_MAX];     /*帐号上面的呼叫信息*/
    
    RTCP_INFO_ST    stRtcp;                                 /*RTCP统计信息*/
    SIP_MSG_SIMSERVS_ST  stSimServs;                        /*IMS订阅信息*/

    VOS_UINT8       ucCWState;                              /*补充业务呼等状态*/      
    VOS_UINT8       ucConfState;                            /*补充业务三方通话状态*/ 
}LINE_STATE_S, *LINE_STATE_PS;

typedef struct tagSIPSERVER_LINE_STATE_ST_
{
    VOS_UINT8       ucRegStatus;                            /*号码注册状态*/
}SIPSERVER_LINE_STATE_S, *SIPSERVER_LINE_STATE_PS;

typedef struct tagVOICE_DIAGNOSIS_OBJ
{
    VOS_UINT32  ulDiagnosisResult;                                  /* 诊断结果 */
}VOICE_DIAGNOSIS_INFO_ST;



/*PhyInterface state*/
typedef struct tagPHY_STATE_ST_
{
    VOS_BOOL    bBusy;                                  /*端口是否正在使用*/
    VOS_BOOL    bCFType;                                /*前转类型*/
    VOS_CHAR    szCFNum[SIP_MAX_NUM_LEN];               /*前转号码*/    
    /*HG253s V2语音定制:端口状态显示*/
    VOS_CHAR    szPortStatus[VCE_STR_LEN_16];           /*端口状态*/
    VOS_UINT32  ulReadyFlag;                            /*信息是否Ready的标志位*/    
}PHY_STATE_S, *PHY_STATE_PS;

typedef struct tagSIP_INFO_ST_
{
    VOS_CHAR    szId[SIP_MAX_NUM_LEN];                  /*VoIP帐号*/
}SIP_INFO_S, *SIP_INFO_PS;

typedef struct tagGLOBAL_STATE_ST_
{
    VOS_BOOL    bPortBusy;                              /*是否有端口正在使用*/
    VOS_BOOL    bLineCallBusy;                          /*是否有线路正在进行语音通话*/
    VOS_BOOL    bHasUrgCall;                            /*是否存在紧急呼叫*/
    VOS_BOOL    bHasUseableLine;                        /*是否存在可用帐号*/
    VOS_UINT32  ulFxoStatus;                            /*FXO口状态:ISDN UP;PSTN UP;fail*/
    VOS_UINT32  ulDectStatus;                            /*FXO口状态:ISDN UP;PSTN UP;fail*/
    VOS_UINT32  ulRegExpire;                            /*注册刷新时间*/
	VOS_UINT32  ulCsLinkStatus;                         /*CS status*/
    VOS_UINT32  ulCsCallStatus;                         /*CS Call status*/
    VOS_UINT32  ulLclIpAddr;                            /*0表示未拨上号*/
}GLOBAL_STATE_S, *GLOBAL_STATE_PS;

typedef struct tagISDN_AUTO_ST_
{
    VOS_CHAR    szNumber[SIP_MAX_NUM_LEN];              /*ISDN号码*/
    
}ISDN_AUTO_S, *ISDN_AUTO_PS;

typedef struct tagVOICE_STATE_ST_
{
    GLOBAL_STATE_S  stGlobal;                           /*全局状态信息*/
    LINE_STATE_S    stLine[VCE_LINE_MAX];               /*帐号状态信息*/
    PHY_STATE_S     stPort[VCE_PORT_MAX];               /*端口状态信息*/
    ISDN_AUTO_S     stAutoIsdn[VCE_ISDN_MAX];           /*自动获取ISDN号码*/
    SIPSERVER_LINE_STATE_S stServerLine[SIPPHONE_SET_NUM];/*Sip下行账号状态*/
    VOICE_DIAGNOSIS_INFO_ST     stDiagnosis;            /* slic 诊断信息 */
#ifdef SUPPORT_ATP_DECT_VOICE
    VOS_BOOL        bAnt0IsOn;                           /* 记录天线0打开状态*/
    VOS_BOOL        bAnt1IsOn;                           /* 记录天线1打开状态*/
#endif	
}VOICE_STATE_S, *VOICE_STATE_PS;

extern VOICE_STATE_PS g_pstVoiceState;

/*************************  END: VOICE_STATE  *************************/




/*************************  BEGIN: TAPI_CMS  *************************/
/* 消息队列写权限 */
#define VHG_VOICE_MSG_W             01
#define VHG_VOICE_CMD_MSG_TYPE      8849
#define VHG_VOICE_CMS_MSGKEY        'V'
#define VHG_VOICE_PID_PATH          "/var/vhgvpid"

/*消息的类型*/
typedef enum tagVHG_VOICE_MSG_TYPE_E
{
    VHG_MSG_TYPE_CMS,                       /*产品语音业务配置消息*/
    VHG_MSG_TYPE_TIMER,                     /*timer消息*/
    VHG_MSG_TYPE_BUTT
}VHG_VOICE_MSG_TYPE_E;

/* 命令行或配置管理发送的指示 */
typedef enum tagVHG_VOICE_CMS_MSG_TYPE_E
{
	VHG_VOICE_CMS_MSG_UPDATA_CONFIG,
    VHG_VOICE_CMS_MSG_UNKNOWN
}VHG_VOICE_CMS_MSG_TYPE_E;

/* 配置操作数据 (配置管理对象) */
typedef enum tagVHG_VOICE_CMS_MSG_CMO_E
{
	VHG_VOICE_CMS_MSG_VOICEPROFILE,
    VHG_VOICE_CMS_MSG_RTP,
    VHG_VOICE_CMS_MSG_VOICEPROCESSING,
    VHG_VOICE_CMS_MSG_CODEC,
    VHG_VOICE_CMS_MSG_CODECLIST
}VHG_VOICE_CMS_MSG_CMO_E;

/*全局参数*/
typedef struct
{
    /*voice profile对象的参数*/
    VOS_UINT32  ulRegion;	                /*国别REGION_CODING_E*/

    /*RTP对象的参数*/
    VOS_UINT32  ulLclRTPPortMin;            /*最小RTP端口*/
    VOS_UINT32  ulLclRTPPortMax;            /*最大RTP端口*/
    VOS_BOOL    bJitterBuffer;              /*是否启用抖动缓冲*/
    VOS_UINT32  ulJBLength;                 /*JitterBuffer长度*/
    VOS_BOOL    bPackLostCompensate;        /*是否启用丢包补偿*/
    VOS_UINT32  ulJBType;                   /*JitterBuffer类型JB_TYPE_E*/

    /*VoiceProcessing对象的参数*/
    VOS_INT32	lTransmitGain;              /*话筒音量*/
    VOS_INT32	lReceiveGain;               /*听筒音量*/

    /*RTCP对象的参数*/
    VOS_UINT32  ulRtcpTxRepeatInterval;         /*RTCP发包的时间间隔*/

    /*HG253s V2语音定制要求实现:RTP打DSCPmark*/
    VOS_UINT32  ulRTPDSCPMark;                 /*DSCPMark值*/  
    
    /*HG253s V2语音定制要求实现:RFC2833Payload值可以配置*/
    VOS_UINT32  ulDTMF2833PayloadType;         /*RFC2833Payload值*/

     VOS_UINT32  ulxrinterval;
     VOS_UINT32  ulxropt;    
}TAPI_GLOBAL_S;

/*Codec参数*/
typedef struct
{
    VOS_UINT32  ulCodecName;                     /*编解码类型，见ATP_CODEC_NAME_E*/
    VOS_BOOL    bSilence;                   /*是否启用语音活动检测*/
    VOS_UINT32  ulPacketPeriod;             /*打包时长10/20/30ms,见PACK_TIME_E*/
}TAPI_CODEC_S;

/*帐号参数*/
typedef struct
{
    VOS_BOOL        bECEnable;              /*是否启用回波抵消*/
    VOS_UINT32      ulDTMFMethod;           /* DTMF数据的传输方法DTMF_TYPE_E
                                             0:Inband
                                             1:RFC 2833
                                             2:SIP Info*/
    VOS_UINT32      ulFaxOption;            /*For Test, Will remove Later*/
    VOS_UINT32      ulFaxOptionArray[VOICE_TAPI_FAXTYPEMAX];
                                            /*传真类型，五级备份*/
	VOS_UINT32		ulFaxDetectType;		/* 0: Disable; 
											   1: Terminating
											   2: Originating
											   3: Both*/
    /*HG253s V2修改问题合入:CNG问题修改*/
    VOS_BOOL        bCNGEnable;             /*是否启用舒适噪音生成,目前只有bcm96362芯片支持配置*/											   
    TAPI_CODEC_S    stCodec[VCE_CODEC_MAX]; /*编解码列表*/
    VOS_BOOL        bT38Enable;             /*HG253s V2语音T38使能节点功能实现*/
}TAPI_LINE_S;

/*语音参数*/
typedef struct
{
    TAPI_GLOBAL_S   stGlobal;               /*全局参数*/
    TAPI_LINE_S     stLine[VCE_VOIP_MAX];   /*VoIP帐号参数*/
}TAPI_CMS_S, *TAPI_CMS_PS;

/* CMS message */
typedef struct VHG_VOICE_CMS_MSG
{
    VHG_VOICE_CMS_MSG_TYPE_E  lEventType;   /*配置操作类型,见VHG_VOICE_CMS_MSG_TYPE_E*/
    VOS_UINT32                ulCMDHead;    /*配置操作内容*/
    VHG_VOICE_CMS_MSG_CMO_E   lCMDBody;     /*配置操作数据*/
}VHG_VCMS_MSG_ST;

typedef struct VHG_VCMS_MSG
{
    VHG_VOICE_MSG_TYPE_E eMsgType;          /*消息类型，可以用来区分是否是配置消息,见VHG_VOICE_MSG_TYPE_E*/
    VHG_VCMS_MSG_ST      CMSMsg;            /*如果是配置消息时，则是配置消息的内容*/
} VHG_VOICE_MSG_ST;

typedef struct VHG_VCMS_MSG_BUFF
{
    VOS_INT32         mtype;                /* 消息区分 ,用来判断是否是产品语音业务消息*/
    VHG_VOICE_MSG_ST  stVoiceMsg;           /* 消息内容 */
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

