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


#ifndef __ATP_LOG_DEF_H__
#define __ATP_LOG_DEF_H__

#define ATP_LOG_LENGTH_128 (128)

#define LOG_FLUSH_MASK 0x80000
#define LOG_NEED_FLUSH(id) (id & LOG_FLUSH_MASK)

/*
 *  RFC3164: Section 4.1.1
 *      Only 24 log types are allowed, user can define 8 types more
 *
 */
typedef enum tagATP_LOG_TYPE_EN
{
    ATP_LOG_TYPE_KERNEL         = 1 << 0,
    ATP_LOG_TYPE_USER_LEVEL     = 1 << 1,    // This can be used by user
    //ATP_LOG_TYPE_MAIL_SYS       = 1 << 2,
    ATP_LOG_TYPE_SYS_DEAMON     = 1 << 3,
    ATP_LOG_TYPE_SECURITY       = 1 << 4,
    ATP_LOG_TYPE_SYSLOGD        = 1 << 5,
    //ATP_LOG_TYPE_LINE_PRINTER   = 1 << 6,
    ATP_LOG_TYPE_HILINK_MESSAGE  = 1 << 6, //for hilink message
    ATP_LOG_TYPE_WIFI            = 1 << 7, //wifi log
    //ATP_LOG_TYPE_UUCP           = 1 << 8,
    //ATP_LOG_TYPE_CLOCK          = 1 << 9,
    //ATP_LOG_TYPE_SECURITY2      = 1 << 10,
    //ATP_LOG_TYPE_FTP            = 1 << 11,
    ATP_LOG_TYPE_LAN            = 1 << 8,
    ATP_LOG_TYPE_DATA           = 1 << 9,
    ATP_LOG_TYPE_UMTS           = 1 << 10,
    ATP_LOG_TYPE_USB            = 1 << 11,
    ATP_LOG_TYPE_NTP            = 1 << 12,
    ATP_LOG_TYPE_MISSCALL          = 1 << 13,
    ATP_LOG_TYPE_ALERT          = 1 << 14,
    //ATP_LOG_TYPE_CLOCK2         = 1 << 15,
    ATP_LOG_TYPE_INCALL         = 1 << 15,
    ATP_LOG_TYPE_OUTCALL        = 1 << 16,

    // User defined log type come here (value: 16~ 23)
    // Warning: Do not add new types unless you know what you are doing
    ATP_LOG_TYPE_WAN            = 1 << 17,
    ATP_LOG_TYPE_PORTFORWARDING = 1 << 18,
    ATP_LOG_TYPE_DAD            = ATP_LOG_TYPE_SYS_DEAMON,
    ATP_LOG_TYPE_TR069          = 1 << 20,
    ATP_LOG_TYPE_DDNS           = 1 << 21,
    ATP_LOG_TYPE_FIREWALL       = 1 << 22,
    ATP_LOG_TYPE_VOICE          = 1 << 23,
    ATP_LOG_TYPE_BUTT           = 1 << 23   // !!DO NOT MODIFY
}ATP_LOG_TYPE_EN;

/*
 *  No more log level allowed
 */
typedef enum tagATP_LOG_LEVEL_EN
{
    ATP_LOG_LEVEL_EMERGENCY     = 1 << 0,
    ATP_LOG_LEVEL_ALERT         = 1 << 1,
    ATP_LOG_LEVEL_CRITICAL      = 1 << 2,
    ATP_LOG_LEVEL_ERROR         = 1 << 3,
    ATP_LOG_LEVEL_WARNING       = 1 << 4,
    ATP_LOG_LEVEL_NOTICE        = 1 << 5,
    ATP_LOG_LEVEL_INFO          = 1 << 6,
    ATP_LOG_LEVEL_DEBUG         = 1 << 7,

    ATP_LOG_LEVEL_BUTT          = 1 << 7   // !!DO NOT MODIFY
} ATP_LOG_LEVEL_EN;

/*
 * Log Items for UPG
 */
#define ATP_SYS_LOG_UPG_BEGIN                         0x1a000000
#define ATP_SYS_LOG_UPG_FAIL                          0x1a000001
#define ATP_SYS_LOG_UPG_FAIL_FILE_LARGE               0x1a000002
#define ATP_SYS_LOG_UPG_FAIL_VOICE_BUSY               0x1a000003
#define ATP_SYS_LOG_UPG_FAIL_SERV_CONFLICT            0x1a000004
#define ATP_SYS_LOG_UPG_FAIL_DL_ERR                   0x1a000005
#define ATP_SYS_LOG_UPG_FAIL_FMT_ERR                  0x1a000006
#define ATP_SYS_LOG_UPG_FAIL_OTHER_ERR                0x1a000007
#define ATP_SYS_LOG_UPG_IMG_OK                        0x1a000008
#define ATP_SYS_LOG_UPG_END                           0x1a000009
#define ATP_SYS_LOG_UPG_MODULE_NAME                   0x1a00000a
#define ATP_SYS_LOG_UPG_MODULE_DATE                   0x1a00000b
#define ATP_SYS_LOG_UPG_MODULE_VER                    0x1a00000c
#define ATP_SYS_LOG_UPG_CFG_BEGIN                     0x1a00000d
#define ATP_SYS_LOG_UPG_CFG_DL_FAIL                   0x1a00000e
#define ATP_SYS_LOG_UPG_CFGFILE_FMT_FAIL              0x1a00000f
#define ATP_SYS_LOG_UPG_CFG_SUC                       0x1a000010
#define ATP_SYS_LOG_UPG_UL_CFGFILE_BEGIN              0x1a000011
#define ATP_SYS_LOG_UPG_UL_CFGFILE_FAIL               0x1a000012
#define ATP_SYS_LOG_UPG_UL_CFGFILE_SUC                0x1a000013
#define ATP_SYS_LOG_UPG_UL_LOGFILE_BEGIN              0x1a000014
#define ATP_SYS_LOG_UPG_UL_LOGFILE_FAIL               0x1a000015
#define ATP_SYS_LOG_UPG_UL_LOGFILE_SUC                0x1a000016
#define ATP_SYS_LOG_UPG_SIGNATURE_ERR                 0x1a000017
#define ATP_SYS_LOG_UPG_VERIMG_OK                     0x1a000018
#define ATP_SYS_LOG_UPG_VERIMG_ERROR_FORMAT           0x1a000019
#define ATP_SYS_LOG_UPG_VERIMG_ERROR_TIMEOUT          0x1a00001a
#define ATP_SYS_LOG_UPG_VERIMG_ERROR_INTERNAL         0x1a00001b
#define ATP_SYS_LOG_UPG_VERIMG_ERROR_TRANS            0x1a00001c
#define ATP_SYS_LOG_UPG_VERIMG_ERROR_CHECK            0x1a00001d
#define ATP_SYS_LOG_UPG_VERIMG_ERROR_BROKEN           0x1a00001e
#define ATP_SYS_LOG_UPG_SERVER_NOFILE                 0x1a00001f
#define ATP_SYS_LOG_UPG_SERVER_UNREACHABLE            0x1a000020
#define ATP_SYS_LOG_UPG_SERVER_AUTH_FAIL              0x1a000021
#define ATP_SYS_LOG_UPG_MULTIBOARD_INFO               0x1a000022
#define ATP_SYS_LOG_UPG_CHECK_NEW                     0x1a000023
#define ATP_SYS_LOG_UPG_ANDROID_OTA_START             0x1a000022
#define ATP_SYS_LOG_UPG_ANDROID_OTA_ERROR             0x1a000023
#define ATP_SYS_LOG_UPG_ANDROID_OTA_SUCCESS           0x1a000024
#define ATP_SYS_LOG_UPG_HOTA_DOWNLOAD_END             0x1a000025
#define ATP_SYS_LOG_UPG_HOTA_DOWNLOAD_FAILED          0x1a000026
#define ATP_SYS_LOG_UPG_HOTA_CHECKHEAD_FAILED         0x1a000027
#define ATP_SYS_LOG_UPG_FAIL_EUAP                     0x1a000028
#define ATP_SYS_LOG_UPG_FAIL_CRC_ERR                  0x1a000029
#define ATP_SYS_LOG_UPG_END_EUAP                      0x1a000030
#define ATP_SYS_LOG_UPG_BEGIN_EUAP                    0x1a000031
#define ATP_SYS_LOG_UPG_FAIL_MD5_ERR                  0x1a000032
#define ATP_SYS_LOG_UPG_ENABLE_AUTO_UPDATE            0x1a000033
#define ATP_SYS_LOG_UPG_DISABLE_AUTO_UPDATE           0x1a000034
#define ATP_SYS_LOG_UPG_MODIFY_AUTO_UPDATETIME        0x1a000035
#define ATP_SYS_LOG_UPG_OPEN_NOT_NEED_LOGIN           0x1a000036
#define ATP_SYS_LOG_UPG_CLOSE_NOT_NEED_LOGIN          0x1a000037
#define ATP_SYS_LOG_UPG_ENABLE_FORCE_UPDATE           0x1a000038
#define ATP_SYS_LOG_UPG_DISABLE_FORCE_UPDATE          0x1a000039


/*
 * Log Items for WEB
 */
#define ATP_SYS_LOG_WEB_LOGIN_OK                      0x5000000
#define ATP_SYS_LOG_WEB_LOGIN_FAIL                    0x5000001
#define ATP_SYS_LOG_WEB_LOGOUT                        0x5000002
#define ATP_SYS_LOG_WEB_UL_CFGFILE_OK                 0x5000003
#define ATP_SYS_LOG_WEB_UL_CFGFILE_ERR                0x5000004
#define ATP_SYS_LOG_WEB_UL_CFGFILE_FILESIZE_ERR       0x5000005
#define ATP_SYS_LOG_WEB_UL_CFGFILE_UNFMT_FILE_ERR     0x5000006
#define ATP_SYS_LOG_WEB_LOGIN_FAIL_USERNAME_ERR       0x5000007
#define ATP_SYS_LOG_WEB_LOGIN_FAIL_PASSWORD_ERR       0x5000008
#define ATP_SYS_LOG_WEB_LOGIN_FAIL_OVER_MAX_TIME      0x5000009
#define ATP_SYS_LOG_WEB_UPDATE_PASSWORD               0x500000a
#define ATP_SYS_LOG_WEB_LOGIN_FAIL_UNLOCK             0x500000b
#define ATP_SYS_LOG_WEB_SESSION_TIMEOUT               0x500000c
#define ATP_SYS_LOG_WEB_REBOOT                        0x500000d
#define ATP_SYS_LOG_HARD_REBOOT                       0x500000e
#define ATP_SYS_LOG_WEB_PING_SUC                      0x500000f
#define ATP_SYS_LOG_WEB_PING_FAIL                     0x5000010
#define ATP_SYS_LOG_WEB_MIRROR_START                  0x5000011
#define ATP_SYS_LOG_WEB_MIRROR_STOP                   0x5000012
#define ATP_SYS_LOG_WEB_SET_VERIFYCODE                0x5000013
#define ATP_SYS_LOG_WEB_URL_PERMISSION_ERROR          0x5000014

/*
 * Log Items for CFM
 */
#ifdef SUPPORT_ATP_EUAP
#define ATP_SYS_LOG_FACTORY_RESET_EUAP                0x1e000000
#define ATP_SYS_LOG_REBOOT_LAN_EUAP                   0x1e000001
#endif
#define ATP_SYS_LOG_FACTORY_RESET                     0x1e000000 | LOG_FLUSH_MASK
#define ATP_SYS_LOG_REBOOT_LAN                        0x1e000001 | LOG_FLUSH_MASK
#define ATP_SYS_LOG_REBOOT_WAN                        0x1e000002 | LOG_FLUSH_MASK
#define ATP_SYS_LOG_CFM_BACKUP_CFGFILE_SUC            0x1e000003
#define ATP_SYS_LOG_CFM_BACKUP_CFGFILE_FAIL           0x1e000004
#define ATP_SYS_LOG_CFM_RECOVER_CFGFILE_SUC           0x1e000005 | LOG_FLUSH_MASK
#define ATP_SYS_LOG_CFM_RECOVER_CFGFILE_FAIL          0x1e000006 | LOG_FLUSH_MASK
#define ATP_SYS_LOG_CFM_CFGFILE_ERR                   0x1e000007
#define ATP_SYS_LOG_CFM_EXPORT_SUC                    0x1e000008
#define ATP_SYS_LOG_CFM_IMPORT_SUC                    0x1e000009
#define ATP_SYS_LOG_APP_INIT_ERR                      0x1e00000a
#define ATP_SYS_LOG_APP_RUN_EXCEPTION                 0x1e00000b
#define ATP_SYS_LOG_CFM_IMPORT_ERREXPORTPASSWORD      0x1e000010
#define ATP_SYS_LOG_CFM_IMPORT_ERRFILESTRUCT          0x1e000011
#define ATP_SYS_LOG_CFM_IMPORT_TOOBIGFILE             0x1e000012
#define ATP_SYS_LOG_CFM_IMPORT_ERRCOUNTRY             0x1e000013
#define ATP_SYS_LOG_CFM_IMPORT_TOOSMALL               0x1e000014
#define ATP_SYS_LOG_CFM_IMPORT_AREARUNNING            0x1e000015
#define ATP_SYS_LOG_CFM_IMPORT_ERRDEVTYPE             0x1e000016
#define ATP_SYS_LOG_CFM_IMPORT_ERRDEVMODEL            0x1e000017
#define ATP_SYS_LOG_CFM_INNER_ERROR                   0x1e000018
#define ATP_SYS_LOG_CFM_APPLY_ERR_FAC_DEF             0x1e000019
#define ATP_SYS_LOG_CFM_CONFIGURE                     0x1e00001a
#define ATP_SYS_LOG_FACTORY_RESET_BUTTON              0x1e00001b | LOG_FLUSH_MASK
#define ATP_SYS_LOG_USER_POWEROFF                     0x1e00001c | LOG_FLUSH_MASK
#define ATP_SYS_LOG_USERKEY_POWEROFF                  0x1e00001d | LOG_FLUSH_MASK

/*
 * Log Items for VOICE
 */
#define ATP_VOICE_LOG_REG_FAIL_DNS                    0xd5000000
#define ATP_VOICE_LOG_REG_FAIL_TIMEOUT                0xd5000001
#define ATP_VOICE_LOG_REG_FAIL_AUTH                   0xd5000002
#define ATP_VOICE_LOG_REG_FAIL_OTHER                  0xd5000003
#define ATP_VOICE_LOG_REG_SUC                         0xd5000004
#define ATP_VOICE_LOG_UNREG_FAIL                      0xd5000005
#define ATP_VOICE_LOG_UNREG_SUC                       0xd5000006
#define ATP_VOICE_LOG_OUTGOING_CALL                   0xd5000007
#define ATP_VOICE_LOG_INCOMING_CALL                   0xd5000008
#define ATP_VOICE_LOG_ADD_NEW_SIP_LINE_INFO           0xd5000009
#define ATP_VOICE_LOG_ADD_NEW_SIP_PROF_INFO           0xd500000a
#define ATP_VOICE_LOG_UPDATE_SIP_LINE_INFO            0xd500000b
#define ATP_VOICE_LOG_UPDATE_SIP_PROF_INFO            0xd500000c
#define ATP_VOICE_LOG_DEL_SIP_LINE_INFO               0xd500000d
#define ATP_VOICE_LOG_DEL_SIP_PROF_INFO               0xd500000e
#define ATP_VOICE_LOG_MSG_RCV                         0xd500000f
#define ATP_VOICE_LOG_RCV_ACS_CFG_DATA                0xd5000010
#define ATP_VOICE_LOG_SUOTA_CHECK_UPDATE              0xd5000011
#define ATP_VOICE_LOG_SUOTA_NEW_FIRM_VALID            0xd5000012
#define ATP_VOICE_LOG_SUOTA_NONE_FIRM_VALID           0xd5000013
#define ATP_VOICE_LOG_REG_FAIL_SVR_RESP_ERR           0xd5000014
#define ATP_VOICE_LOG_REG_FAIL_FORBIDDEN              0xd5000015
#define ATP_VOICE_LOG_REG_FAIL_NOT_FOUND              0xd5000016
#define ATP_VOICE_LOG_REG_FAIL_METHOD_NOT_ALLOWED     0xd5000017
#define ATP_VOICE_LOG_REG_FAIL_ADDR_INCOMPLETE        0xd5000018
#define ATP_VOICE_LOG_REG_FAIL_NOT_ACCEPTABLE_HERE    0xd5000019
#define ATP_VOICE_LOG_REG_FAIL_REQ_PENDING            0xd500001a
#define ATP_VOICE_LOG_REG_FAIL_INTERNEL_SVR_ERR       0xd500001b
#define ATP_VOICE_LOG_REG_FAIL_SERVICE_UNAVAILABLE    0xd500001c
#define ATP_VOICE_LOG_PPP_DOWN_TIMEOUT                0xd500001d
#define ATP_VOICE_LOG_PPP_DOWN_ECHO                   0xd500001e
#define ATP_VOICE_LOG_PPP_UP                          0xd500001f
#define ATP_VOICE_LOG_PPP_DOWN_DSL                    0xd5000020
#define ATP_VOICE_LOG_PPP_FAIL_AUTH                   0xd5000021
#define ATP_VOICE_LOG_PPP_FAIL_SVR                    0xd5000022
#define ATP_VOICE_LOG_PPP_NO_NAS                      0xd5000023
#define ATP_VOICE_LOG_PPP_FAIL_SVR_VOICE              0xd5000024
#define ATP_VOICE_LOG_MISS_CALL                       0xd5000025
#define ATP_VOICE_LOG_SUOTA_DOWNLOAD_UPDATE           0xd5000026
#define ATP_VOICE_LOG_SUOTA_INSTALL_SUCC              0xd5000027
#define ATP_VOICE_LOG_SUOTA_INSTALL_FAIL              0xd5000028
#define ATP_VOICE_LOG_PP_PAIRED_SUCC                  0xd5000029
#define ATP_VOICE_LOG_PP_PAIRED_FAIL                  0xd500002a
#define ATP_VOICE_LOG_PP_LOST_CONNECTION              0xd500002b
#define ATP_VOICE_LOG_PP_CONNECT                      0xd500002c
#define ATP_VOICE_LOG_DETLETE_CALLLIST                0xd500002d
#define ATP_VOICE_LOG_SIP_MSG_RECEIVE                 0xd500002e
#define ATP_VOICE_LOG_SIP_MSG_SEND                    0xd500002f
#define ATP_VOICE_LOG_TAPI_OFFHOOK                    0xd5000030
#define ATP_VOICE_LOG_TAPI_ONHOOK                     0xd5000031
#define ATP_VOICE_LOG_DNS_PARSE_SUCC                  0xd5000032
#define ATP_VOICE_LOG_DNS_PARSE_FAIL                  0xd5000033
#define ATP_VOICE_LOG_DECT_HS_REG                     0xd5000034
#define ATP_VOICE_LOG_DECT_HS_UNREG                   0xd5000035

/*
 * Log Items for IPSECTOOLS
 */
#define ATP_SYS_LOG_IPSECTOOLS_OPENWIFI_TUNNEL_UP     0xc2000000
#define ATP_SYS_LOG_IPSECTOOLS_OPENWIFI_TUNNEL_DOWN   0xc2000001

/*
 * Log Items for UPNP
 */
#define ATP_SYS_LOG_UPNP_ACTIVED                      0x31000000
#define ATP_SYS_LOG_UPNP_DEACTIVED                    0x31000001
#define ATP_SYS_LOG_UPNP_EX_UPNP_SEC_ENABLED          0x31000002
#define ATP_SYS_LOG_UPNP_EX_UPNP_SEC_DISABLED         0x31000003
#define ATP_SYS_LOG_UPNP_PMAPPING_ADD_PARA_ERR        0x31000004
#define ATP_SYS_LOG_UPNP_PMAPPING_ADD_SUC             0x31000005
#define ATP_SYS_LOG_UPNP_PMAPPING_ADD_ERR             0x31000006
#define ATP_SYS_LOG_UPNP_PMAPPING_DEL_PARA_ERR        0x31000007
#define ATP_SYS_LOG_UPNP_PMAPPING_DEL_SUC             0x31000008
#define ATP_SYS_LOG_UPNP_PMAPPING_DEL_ERR             0x31000009
#define ATP_SYS_LOG_UPNP_LEGACY_PMAPPING_SUC          0x3100000a
#define ATP_SYS_LOG_UPNP_LEGACY_PMAPPING_FAIL         0x3100000b
#define ATP_SYS_LOG_UPNP_TR064_AUTH_FAIL              0x3100000c
#define ATP_SYS_LOG_UPNP_TR064_AUTH_SUC               0x3100000d
#define ATP_SYS_LOG_UPNP_TR064_START                  0x3100000e
#define ATP_SYS_LOG_UPNP_TR064_CLOSE                  0x3100000f
#define ATP_SYS_LOG_UPNP_TR064_ACTION_SUC             0x31000010
#define ATP_SYS_LOG_UPNP_TR064_ACTION_FAIL            0x31000011
#define ATP_SYS_LOG_UPNP_LOGIN_UNLOCKED                 0x31000012
#define ATP_SYS_LOG_UPNP_LOGIN_LOCKED                   0x31000013

/*
 * Log Items for PPPC
 */
#define ATP_SYS_LOG_PPP_IPCP_SEND_TERM_REQ            0xb000000
#define ATP_SYS_LOG_PPP_LCP_SEND_TERM_REQ             0xb000001
#define ATP_SYS_LOG_PPP_IPCP_RCV_CFG_REQ              0xb000002
#define ATP_SYS_LOG_PPP_LCP_RCV_CFG_REQ               0xb000003
#define ATP_SYS_LOG_PPP_IPCP_RCV_CFG_ACK              0xb000004
#define ATP_SYS_LOG_PPP_LCP_RCV_CFG_ACK               0xb000005
#define ATP_SYS_LOG_PPP_IPCP_RCV_CFG_NAK              0xb000006
#define ATP_SYS_LOG_PPP_LCP_RCV_CFG_NAK               0xb000007
#define ATP_SYS_LOG_PPP_IPCP_RCV_CFG_REJECT           0xb000008
#define ATP_SYS_LOG_PPP_LCP_RCV_CFG_REJECT            0xb000009
#define ATP_SYS_LOG_PPP_IPCP_RCV_TERM_REQ             0xb00000a
#define ATP_SYS_LOG_PPP_LCP_RCV_TERM_REQ              0xb00000b
#define ATP_SYS_LOG_PPP_IPCP_RCV_TERM_ACK             0xb00000c
#define ATP_SYS_LOG_PPP_LCP_RCV_TERM_ACK              0xb00000d
#define ATP_SYS_LOG_PPP_IPCP_RCV_CODE_REJECT          0xb00000e
#define ATP_SYS_LOG_PPP_LCP_RCV_CODE_REJECT           0xb00000f
#define ATP_SYS_LOG_PPP_IPCP_SEND_TERM_ACK            0xb000010
#define ATP_SYS_LOG_PPP_LCP_SEND_TERM_ACK             0xb000011
#define ATP_SYS_LOG_PPP_IPCP_SEND_CFG_REQ             0xb000012
#define ATP_SYS_LOG_PPP_LCP_SEND_CFG_REQ              0xb000013
#define ATP_SYS_LOG_PPP_IPCP_SEND_CFG_ACK             0xb000014
#define ATP_SYS_LOG_PPP_LCP_SEND_CFG_ACK              0xb000015
#define ATP_SYS_LOG_PPP_IPCP_SEND_CFG_NAK             0xb000016
#define ATP_SYS_LOG_PPP_LCP_SEND_CFG_NAK              0xb000017
#define ATP_SYS_LOG_PPP_IPCP_SEND_CFG_REJECT          0xb000018
#define ATP_SYS_LOG_PPP_LCP_SEND_CFG_REJECT           0xb000019
#define ATP_SYS_LOG_PPP_IPCP_SEND_CODE_REJECT         0xb00001a
#define ATP_SYS_LOG_PPP_LCP_SEND_CODE_REJECT          0xb00001b
#define ATP_SYS_LOG_PPP_CHAP_RCV_CHALLENGE            0xb00001c
#define ATP_SYS_LOG_PPP_CHAP_PEER_AUTH_SUC            0xb00001d
#define ATP_SYS_LOG_PPP_CHAP_PEER_AUTH_FAIL           0xb00001e
#define ATP_SYS_LOG_PPP_CHAP_RCV_SUC_AUTH_OK          0xb00001f
#define ATP_SYS_LOG_PPP_CHAP_RCV_FAIL                 0xb000020
#define ATP_SYS_LOG_PPP_PAP_RCV_SUC_AUTH_OK           0xb000021
#define ATP_SYS_LOG_PPP_PAP_RCV_FAIL                  0xb000022
#define ATP_SYS_LOG_PPP_LOG_FAIL_WITH_INFO            0xb000023
#define ATP_SYS_LOG_PPP_LOG_FAIL_WITHOUT_INFO         0xb000024
#define ATP_PPPC_LOG_R001                             0xb000025
#define ATP_PPPC_LOG_R001_56_0000                     0xb000026
#define ATP_PPPC_LOG_R001_56_0001                     0xb000027
#define ATP_PPPC_LOG_R001_56_0022                     0xb000028
#define ATP_PPPC_LOG_R001_56_0023                     0xb000029
#define ATP_PPPC_LOG_R001_56_0025                     0xb00002a
#define ATP_PPPC_LOG_R001_56_0026                     0xb00002b
#define ATP_PPPC_LOG_R001_56_0028                     0xb00002c
#define ATP_PPPC_LOG_R001_56_0030                     0xb00002d
#define ATP_PPPC_LOG_R001_56_0034                     0xb00002e
#define ATP_PPPC_LOG_R001_56_0002                     0xb00002f
#define ATP_PPPC_LOG_R001_56_0003                     0xb000030
#define ATP_PPPC_LOG_R001_56_0004                     0xb000031
#define ATP_PPPC_LOG_R001_56_0005                     0xb000032
#define ATP_PPPC_LOG_R001_56_0006                     0xb000033
#define ATP_PPPC_LOG_R001_56_0007                     0xb000034
#define ATP_PPPC_LOG_R001_56_0008                     0xb000035
#define ATP_PPPC_LOG_R001_56_0009                     0xb000036
#define ATP_PPPC_LOG_R001_56_0012                     0xb000037
#define ATP_PPPC_LOG_R001_56_0013                     0xb000038
#define ATP_PPPC_LOG_R001_56_0014                     0xb000039
#define ATP_PPPC_LOG_R001_56_0015                     0xb00003a
#define ATP_PPPC_LOG_R001_56_0016                     0xb00003b
#define ATP_PPPC_LOG_R001_56_0017                     0xb00003c
#define ATP_PPPC_LOG_R001_56_0018                     0xb00003d
#define ATP_PPPC_LOG_R001_56_0019                     0xb00003e
#define ATP_PPPC_LOG_R001_56_0020                     0xb00003f
#define ATP_PPPC_LOG_R001_56_0021                     0xb000040
#define ATP_PPPC_LOG_R001_56_0024                     0xb000041
#define ATP_PPPC_LOG_R001_56_0027                     0xb000042
#define ATP_PPPC_LOG_R001_56_0029                     0xb000043
#define ATP_PPPC_LOG_R001_56_0031                     0xb000044
#define ATP_PPPC_LOG_R001_56_0032                     0xb000045
#define ATP_PPPC_LOG_R001_56_0033                     0xb000046
#define ATP_PPPC_LOG_R001_56_0035                     0xb000047
#define ATP_PPPC_LOG_R011                             0xb000048
#define ATP_PPPC_LOG_R012                             0xb000049
#define ATP_PPPC_LOG_R013                             0xb00004a
#define ATP_PPPC_LOG_R014                             0xb00004b
#define ATP_PPPC_LOG_R015                             0xb00004c
#define ATP_PPPC_LOG_R016                             0xb00004d
#define ATP_PPPC_LOG_R017                             0xb00004e
#define ATP_PPPC_LOG_R018                             0xb00004f
#define ATP_PPPC_LOG_R019                             0xb000050
#define ATP_PPPC_LOG_R020                             0xb000051
#define ATP_PPPC_LOG_R021                             0xb000052
#define ATP_PPPC_LOG_R023                             0xb000053
#define ATP_PPPC_LOG_CONNECTING                       0xb000054
#define ATP_PPPC_LOG_PADI_NORELAY                     0xb000055
#define ATP_PPPC_LCP_IPCP_CONFIG_NOREPLY              0xb000056

/*
 * Log Items for CWMP
 */
#define ATP_SYS_LOG_CWMP_GET_PARAVALUE_ERR            0x18000000
#define ATP_SYS_LOG_CWMP_GET_INVALID_PARA             0x18000001
#define ATP_SYS_LOG_CWMP_GPV_SUC                      0x18000002
#define ATP_SYS_LOG_CWMP_GET_VALUE_TR069_ERR          0x18000003
#define ATP_SYS_LOG_CWMP_SET_PARA_ERR                 0x18000004
#define ATP_SYS_LOG_CWMP_SET_PARA_RDO_ERR             0x18000005
#define ATP_SYS_LOG_CWMP_SET_PARA_VALUE_ERR           0x18000006
#define ATP_SYS_LOG_CWMP_SET_BY_TR069_ERR             0x18000007
#define ATP_SYS_LOG_CWMP_SET_BY_TR069_OK              0x18000008
#define ATP_SYS_LOG_CWMP_GET_PARA_ATTR_ERR            0x18000009
#define ATP_SYS_LOG_CWMP_SET_PARA_ATTR_ERR            0x1800000a
#define ATP_SYS_LOG_CWMP_TRANSFER_ST_SUCC             0x1800000b
#define ATP_SYS_LOG_CWMP_TRANSFER_ST                  0x1800000c
#define ATP_SYS_LOG_CWMP_DLD_FILE_URL                 0x1800000d
#define ATP_SYS_LOG_CWMP_DLD_FILE_NAME                0x1800000e
#define ATP_SYS_LOG_CWMP_DLD_FILE_START               0x1800000f
#define ATP_SYS_LOG_CWMP_DLD_FILE_OK                  0x18000010
#define ATP_SYS_LOG_CWMP_DLD_FILE_ERR                 0x18000011
#define ATP_SYS_LOG_CWMP_ULD_FILE_TYPE                0x18000012
#define ATP_SYS_LOG_CWMP_ULD_FILE_START               0x18000013
#define ATP_SYS_LOG_CWMP_ULD_FILE_OK                  0x18000014
#define ATP_SYS_LOG_CWMP_ULD_FILE_ERR                 0x18000015
#define ATP_SYS_LOG_CWMP_REBOOT                       0x18000016
#define ATP_SYS_LOG_CWMP_REBOOT_ERR                   0x18000017
#define ATP_SYS_LOG_CWMP_REBOOT_OK                    0x18000018
#define ATP_SYS_LOG_CWMP_FACTORY_RST                  0x18000019
#define ATP_SYS_LOG_CWMP_FACTORY_RST_ERR              0x1800001a
#define ATP_SYS_LOG_CWMP_FACTORY_RST_OK               0x1800001b
#define ATP_SYS_LOG_CWMP_ADD_OBJ_BY_TR069             0x1800001c
#define ATP_SYS_LOG_CWMP_ADD_OBJ_BY_TR069_FAIL        0x1800001d
#define ATP_SYS_LOG_CWMP_DEL_OBJ_BY_TR069             0x1800001e
#define ATP_SYS_LOG_CWMP_DEL_OBJ_BY_TR069_FAIL        0x1800001f
#define ATP_SYS_LOG_CWMP_SESS_START                   0x18000020
#define ATP_SYS_LOG_CWMP_SESS_START_FAIL              0x18000021
#define ATP_SYS_LOG_CWMP_SESS_CONN_FAIL               0x18000022
#define ATP_SYS_LOG_CWMP_SESS_INFO_MSG                0x18000023
#define ATP_SYS_LOG_CWMP_SESS_SUC                     0x18000024
#define ATP_SYS_LOG_CWMP_RCV_FLT                      0x18000025
#define ATP_SYS_LOG_CWMP_RCV_EMPTY_PKT_FROM_HDM       0x18000026
#define ATP_SYS_LOG_CWMP_RCV_FLT_FROM_HDM             0x18000027
#define ATP_SYS_LOG_CWMP_HTTPVERSION_UNSUPPORT        0x18000028
#define ATP_SYS_LOG_CWMP_DNS_RESOLVE_ERR              0x18000029
#define ATP_SYS_LOG_CWMP_HTTP_SOCK_ERR                0x1800002a
#define ATP_SYS_LOG_CWMP_HDM_CLOSE_THE_SOCK           0x1800002b
#define ATP_SYS_LOG_CWMP_HTTPSOCK_RCV_DATA_ERR        0x1800002c
#define ATP_SYS_LOG_CWMP_HTTPSOCK_SEND_DATA_ERR       0x1800002d
#define ATP_SYS_LOG_CWMP_HTTP_SOCK_TIMEOUT            0x1800002e
#define ATP_SYS_LOG_CWMP_SSL_CERT_ERR                 0x1800002f
#define ATP_SYS_LOG_CWMP_RETCODE_NOT_SUPPORT          0x18000030
#define ATP_SYS_LOG_CWMP_AUTH_ERR                     0x18000031
#define ATP_SYS_LOG_CWMP_INTERNAL_ERR                 0x18000032
#define ATP_SYS_LOG_CWMP_SOAPID_ERR                   0x18000033
#define ATP_SYS_LOG_CWMP_RCV_ERR_PKTS_FROM_HDM        0x18000034
#define ATP_SYS_LOG_CWMP_ACS_CONN_TO_CPE_FAIL         0x18000035
#define ATP_SYS_LOG_CWMP_ACS_CONN_TO_CPE_SUC          0x18000036
#define ATP_SYS_LOG_CWMP_INFROM_EVENT                 0x18000037
#define ATP_SYS_LOG_CWMP_INFROM_GET_ACTIONS           0x18000038
#define ATP_SYS_LOG_CWMP_INFROM_SET_ACTIONS           0x18000039
#define ATP_SYS_LOG_CWMP_UPDATE_CERT_FILE             0x1800003a
#define ATP_SYS_LOG_CWMP_PERIOD_REPORT                0x1800003b
#define ATP_SYS_LOG_CWMP_UPDATE_URL                   0x1800003c
#define ATP_SYS_LOG_CWMP_INFROM_ACS_CONN_OK           0x1800003d
#define ATP_SYS_LOG_CWMP_INFORM_SET_PARA_DONE         0x1800003e
#define ATP_SYS_LOG_CWMP_POST_INFORM_SUC              0x1800003f
#define ATP_SYS_LOG_CWMP_POST_INFORM_FAIL             0x18000040

#define ATP_SYS_LOG_CWMP_EASYSUPPORT_ACTIVATED        0x18000041
#define ATP_SYS_LOG_CWMP_EASYSUPPORT_DEACTIVATED      0x18000042
#define ATP_SYS_LOG_CWMP_CONTACT_ACS                  0x18000043
#define ATP_SYS_LOG_CWMP_RECEVIDED_ACCESS_DATA        0x18000044
#define ATP_SYS_LOG_CWMP_RECEVIDED_VOIP_DATA          0x18000045
#define ATP_SYS_LOG_CWMP_FLASHED_IMG_SUC              0x18000046
#define ATP_SYS_LOG_CWMP_CANT_CONFIG                  0x18000047
#define ATP_SYS_LOG_CWMP_CPE_CANT_REACHED_ACS         0x18000048
#define ATP_SYS_LOG_CWMP_SSL_ACS_DENY                 0x18000049
#define ATP_SYS_LOG_CWMP_SSL_CPE_DENY                 0x1800004a
#define ATP_SYS_LOG_CWMP_SOAP_FAULT_FROM_ACS          0x1800004b
#define ATP_SYS_LOG_CWMP_INVALID_REQ_REP_FROM_ACS     0x1800004c
#define ATP_SYS_LOG_CWMP_CONNECTION_BREAKDOWN         0x1800004d
#define ATP_SYS_LOG_CWMP_SSL_COM_TIMEOUT              0x1800004e
#define ATP_SYS_LOG_CWMP_VOIP_DATA_ERR                0x1800004f
#define ATP_SYS_LOG_CWMP_VOIP_NOT_BOOKED              0x18000050
#define ATP_SYS_LOG_CWMP_CANT_RECV_FIRM               0x18000051
#define ATP_SYS_LOG_CWMP_FIRM_CHECK_FAILED            0x18000052
#define ATP_SYS_LOG_CWMP_ACCESS_DATA_ERR              0x18000053
#define ATP_SYS_LOG_CWMP_CFG_CHANGE                   0x18000054
#define ATP_SYS_LOG_CWMP_ACS_PRAMA_CHANGE             0x18000055
#define ATP_SYS_LOG_CWMP_DIAGNOSE_COMPLETE_OK         0x18000056
#define ATP_SYS_LOG_CWMP_LOGIN_FAIL_UNLOCK            0x18000057
#define ATP_SYS_LOG_CWMP_LOGIN_FAIL_OVER_MAX_TIME     0x18000058
#define ATP_SYS_LOG_CWMP_SCHEDULE_REPORT              0x18000059
/*
 * Log Items for DDNS
 */
#define ATP_SYS_LOG_DDNS_USER_INFO_ERR                0x9000000
#define ATP_SYS_LOG_DDNS_SERVICE_INFO                 0x9000001
#define ATP_SYS_LOG_DDNS_STATUS                       0x9000002
#define ATP_SYS_LOG_DDNS_CLIENT_CONNECT_ERR           0x9000003
#define ATP_SYS_LOG_DDNS_REPLY_SUC                    0x9000004
#define ATP_SYS_LOG_DDNS_REPLY_FAIL                   0x9000005
#define ATP_SYS_LOG_DDNS_NOREPLY                   	  0x9000006
#define ATP_SYS_LOG_DDNS_REPLY_GOOD                   0x9000007
#define ATP_SYS_LOG_DDNS_REPLY_NOHOST                 0x9000008
#define ATP_SYS_LOG_DDNS_REPLY_NOTFQDN                0x9000009
#define ATP_SYS_LOG_DDNS_REPLY_NOTYOURS               0x900000a
#define ATP_SYS_LOG_DDNS_REPLY_ABUSE                  0x900000b
#define ATP_SYS_LOG_DDNS_REPLY_NOCHG                  0x900000c
#define ATP_SYS_LOG_DDNS_REPLY_BADAUTH                0x900000d
#define ATP_SYS_LOG_DDNS_REPLY_BADSYS                 0x900000e
#define ATP_SYS_LOG_DDNS_REPLY_BADAGENT               0x9000010
#define ATP_SYS_LOG_DDNS_REPLY_NUMHOST                0x9000011
#define ATP_SYS_LOG_DDNS_REPLY_DNSERR                 0x9000012
#define ATP_SYS_LOG_DDNS_REPLY_911ERR                 0x9000013
#define ATP_SYS_LOG_DDNS_REPLY_999ERR                 0x9000014
#define ATP_SYS_LOG_DDNS_REPLY_NOTDONATOR             0x9000015
#define ATP_SYS_LOG_DDNS_REPLY_401ERR                 0x9000016
#define ATP_SYS_LOG_DDNS_REPLY_UNKNOWCODE             0x9000017
#define ATP_SYS_LOG_DDNS_REPLY_204ERR	              0x9000018






































/*
 * Log Items for POWERMNGT
 */
#define ATP_SYS_LOG_POWERMNGT_NORMAL_MODE             0xbe000000
#define ATP_SYS_LOG_POWERMNGT_SLEEP_MODE              0xbe000001

/*
 * Log Items for THERMOSTAT
 */
#define ATP_SYS_LOG_THERMOSTAT_CHANGE                 0xbf000000

/*
 * Log Items for SNTP
 */
#define ATP_SYS_LOG_SNTP_SYNC_FAIL                    0xa000000
#define ATP_SYS_LOG_SNTP_SYNC_START                   0xa000001
#define ATP_SYS_LOG_SNTP_SYNC_SUC                     0xa000002
#define ATP_SYS_LOG_SNTP_SERVER_UNREACHABLE           0xa000003
#define ATP_SYS_LOG_SNTPv6_SYNC_FAIL                  0xa000004
#define ATP_SYS_LOG_SNTPv6_SYNC_SUC                   0xa000005
#define ATP_SYS_LOG_SNTPv6_SERVER_UNREACHABLE         0xa000006
#define ATP_SYS_LOG_SNTP_SERVER_CHANGE                0xa000007
#define ATP_SYS_LOG_SNTP_TIMEZONE_CHANGE              0xa000008
#define ATP_SYS_LOG_SNTP_MANUALSET_ENABLE             0xa000009
#define ATP_SYS_LOG_SNTP_MANUALSET_DISABLE            0xa00000a
#define ATP_SYS_LOG_SNTP_DST_ENABLE                   0xa00000b
#define ATP_SYS_LOG_SNTP_DST_DISABLE                  0xa00000c
#define ATP_SYS_LOG_SNTP_ENABLE                       0xa00000d
#define ATP_SYS_LOG_SNTP_DISABLE                      0xa00000e
#define ATP_SYS_LOG_SNTP_HOTASYNC_SUC                 0xa00000f
#define ATP_SYS_LOG_SNTP_HOTASYNC_FAIL                0xa000010
#define ATP_SYS_LOG_SNTP_BBOU_SUC                 0xa000011
#define ATP_SYS_LOG_SNTP_BBOU_FAIL                 0xa000012

/*
 * Log Items for DHCP
 */
#define ATP_SYS_LOG_DHCP_ACTIVE                     0x3000000
#define ATP_SYS_LOG_DHCP_DEACTIVE                   0x3000001
#define ATP_SYS_LOG_DHCP_FAIL                       0x3000002
#define ATP_SYS_LOG_DHCP_LAN_WAN_CONFLICT           0x3000003
#define ATP_SYS_LOG_DHCP_DISCOVER_FAIL              0x3000004
#define ATP_SYS_LOG_DHCP_REQUEST_INFO               0x3000005
#define ATP_SYS_LOG_DHCP_ACKINFO                    0x3000006
#define ATP_SYS_LOG_DHCPS_IPINTERFACE_CHANGE        0x3000007
#define ATP_SYS_LOG_DHCPS_SERVER_STATUS_ENABLE      0x3000008
#define ATP_SYS_LOG_DHCPS_SERVER_STATUS_DISABLE     0x3000009
#define ATP_SYS_LOG_DHCPS_SERVER_POOL_CHANGE        0x300000a
#define ATP_SYS_LOG_DHCPS_LHCM_IPADDRESS_CHANGE     0x300000b
#define ATP_SYS_LOG_DHCPC_SENDDISCOVER              0x300000c
#define ATP_SYS_LOG_DHCPC_REQUESTED                 0x300000d
#define ATP_SYS_LOG_DHCPC_SENDRELEASE               0x300000e
#define ATP_SYS_LOG_DHCPC_RECOFFER                  0x300000f
#define ATP_SYS_LOG_DHCPC_RECACK                    0x3000010
#define ATP_SYS_LOG_DHCPC_RECNAK                    0x3000011
#define ATP_SYS_LOG_DHCPC_RECFORCERENEW             0x3000012
#define ATP_SYS_LOG_DHCPC_DISCOVER_NORELAY          0x3000013
#define ATP_SYS_LOG_DHCPC_REQUEST_NORELAY           0x3000014
#define ATP_SYS_LOG_DHCPS_LEASETIME_CHANGE          0x3000015

/*
 *  Log Items for ipcheck
 */
#define ATP_SYS_LOG_IPCHECK_IPV4_CONFLICT             0x70000000
#define ATP_SYS_LOG_IPCHECK_ADD_HOST                  0x70000001

/*
 * Log Items for WAN
 */
#ifdef SUPPORT_ATP_CPE_SBB
#define ATP_SYS_LOG_WAN_CONNECTED                     (0x8f000000 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_WAN_DISCONNETED                   (0x8f000001 | LOG_FLUSH_MASK)
#else
#define ATP_SYS_LOG_WAN_CONNECTED                     0x8f000000
#define ATP_SYS_LOG_WAN_DISCONNETED                   0x8f000001
#endif
#define ATP_SYS_LOG_WAN_IPV6_CONNECTED                0x8f000002
#define ATP_SYS_LOG_WAN_IPV6_DISCONNECTED             0x8f000003
#define ATP_SYS_LOG_WAN_AUTO_SENSING_LAST_CONN_PORT   0x8f000004
#define ATP_SYS_LOG_WAN_AUTO_SENSING_DETECTED_PORT    0x8f000005
#define ATP_SYS_LOG_WAN_CONFIG_IP_CONN_DEL            0x8f000006
#define ATP_SYS_LOG_WAN_CONFIG_IP_CONN_ADD            0x8f000007
#define ATP_SYS_LOG_WAN_CONFIG_IP_CONN_SET            0x8f000008
#define ATP_SYS_LOG_WAN_CONFIG_PPP_CONN_DEL           0x8f000009
#define ATP_SYS_LOG_WAN_CONFIG_PPP_CONN_ADD           0x8f00000a
#define ATP_SYS_LOG_WAN_CONFIG_PPP_CONN_SET           0x8f00000b
#define ATP_SYS_LOG_WAN_UMTS_DIAL_SUCCESS             0x8f00000c
#define ATP_SYS_LOG_WAN_UMTS_DIAL_FAIL                0x8f00000d
#define ATP_SYS_LOG_WAN_ROUTED_DETAIL_INFO            0x8f00000e
#define ATP_SYS_LOG_WAN_PPP_ENABLE                    0x8f00000f
#define ATP_SYS_LOG_WAN_PPP_CONNECTIONTYPE            0x8f000010
#define ATP_SYS_LOG_WAN_PPP_NATENABLED                0x8f000011
#define ATP_SYS_LOG_WAN_PPP_USERNAME                  0x8f000012
#define ATP_SYS_LOG_WAN_PPP_PASSWORD                  0x8f000013
#define ATP_SYS_LOG_WAN_IP_ENABLE                     0x8f000014
#define ATP_SYS_LOG_WAN_IP_CONNECTIONTYPE             0x8f000015
#define ATP_SYS_LOG_WAN_IP_NATENABLED                 0x8f000016
#define ATP_SYS_LOG_WAN_PVC_CHANGE                    0x8f000017
#define ATP_SYS_LOG_WAN_VLAN_CHANGE                   0x8f000018
#define ATP_SYS_LOG_WAN_DUPLEX                        0x8f000019
#define ATP_SYS_LOG_WAN_LEARN_PPPINFO                 0x8f00001a
#define ATP_SYS_LOG_WAN_CONNFAIL           0x8f00001b



/*
 * Log Items for WLAN
 */
#define ATP_SYS_LOG_WLAN_WPS_STARTED                  0x14000000
#define ATP_SYS_LOG_WLAN_WPS_FINISHED                 0x14000001
#define ATP_SYS_LOG_WLAN_ACTIVED                      0x14000002
#define ATP_SYS_LOG_WLAN_DEACTIVED                    0x14000003
#define ATP_SYS_LOG_WLAN_SSID_CHANGED                 0x14000004
#define ATP_SYS_LOG_WLAN_PASSWD_CHANGED               0x14000005
#define ATP_SYS_LOG_WLAN_SEC_MODE_CHANGED             0x14000006
#define ATP_SYS_LOG_WLAN_CHANNEL_CHANGED              0x14000007
#define ATP_SYS_LOG_WLAN_STANDARD_CHANGED             0x14000008
#define ATP_SYS_LOG_WLAN_SECURITY_RESTORE             0x14000009
#define ATP_SYS_LOG_WLAN_STA_BREAK                    0x1400000a
#define ATP_SYS_LOG_WLAN_AUTH_FAIL                    0x1400000b
#define ATP_SYS_LOG_WLAN_TIMERULE_ACT                 0x1400000c
#define ATP_SYS_LOG_WLAN_TIMERULE_DEACT               0x1400000d
#define ATP_SYS_LOG_WLAN_ACT                          0x1400000e
#define ATP_SYS_LOG_WLAN_DEACT                        0x1400000f
#define ATP_SYS_LOG_WLAN_STA_BREAK_NOCOMPILE          0x14000010
#define ATP_SYS_LOG_WLAN_STA_BREAK_BLACKLIST          0x14000011
#define ATP_SYS_LOG_WLAN_STA_2G_SUCCESS               0x14000012
#define ATP_SYS_LOG_WLAN_STA_5G_SUCCESS               0x14000013
#define ATP_SYS_LOG_WLAN_CHANNEL_SWITCH_FROM          0x14000014
#define ATP_SYS_LOG_WLAN_CHANNEL_SWITCH_TO            0x14000015
#define ATP_SYS_LOG_WLAN_SECURITY_SAVE                0x14000016
#define ATP_SYS_LOG_WLAN_CLIENT_ACTIVED               0x14000017
#define ATP_SYS_LOG_WLAN_CLIENT_DEACTIVED             0x14000018
#define ATP_SYS_LOG_WLAN_STA_ACTIVED                  0x14000019
#define ATP_SYS_LOG_WLAN_STA_DEACTIVED                0x1400001a
#define ATP_SYS_LOG_WLAN_ERR                          0x1400001b
#define ATP_SYS_LOG_WLAN_DEAUTH_LEAVING               0x1400001c
#define ATP_SYS_LOG_WLAN_INVAL_CLASS_2                0x1400001d
#define ATP_SYS_LOG_WLAN_INVAL_CLASS_3                0x1400001e
#define ATP_SYS_LOG_WLAN_DISASSOC_LEAVING             0x1400001f
#define ATP_SYS_LOG_WLAN_AUTH_CHALLENGE_FAIL          0x14000020
#define ATP_SYS_LOG_WLAN_AUTH_TIMEOUT                 0x14000021
#define ATP_SYS_LOG_WLAN_UNSPECIFIED                  0x14000022
#define ATP_SYS_LOG_WLAN_STA_BREAK_WHITELIST          0x14000023
#define ATP_SYS_LOG_WLAN_RATE_CHANGED                 0x14000024
#define ATP_SYS_LOG_WLAN_POWER_CHANGED                0x14000025
#define ATP_SYS_LOG_WLAN_MACFILT_CTR_CHANGED          0x14000026
#define ATP_SYS_LOG_WLAN_MACFILT_PPLICY_CHANGED       0x14000027
#define ATP_SYS_LOG_WLAN_WMM_CHANGED                  0x14000028
#define ATP_SYS_LOG_WLAN_BEACONTYPE_CHANGED           0x14000029
#define ATP_SYS_LOG_WLAN_ENCRYPTIONMODE_CHANGED       0x1400002a
#define ATP_SYS_LOG_WLAN_BASICAUTHENTICATIONMODE_CHANGED           0x1400002b
#define ATP_SYS_LOG_WLAN_WEPKEY_CHANGED               0x1400002c
#define ATP_SYS_LOG_WLAN_PRESHAREDKEY_CHANGED         0x1400002d
#define ATP_SYS_LOG_WLAN_MCS_CHANGED                  0x1400002e
#define ATP_SYS_LOG_WLAN_AUTOCHANNEL_CHANGED          0x1400002f
#define ATP_SYS_LOG_WLAN_COUNTRY_CHANGED              0x14000030
#define ATP_SYS_LOG_WLAN_SSID_STATUS_OPEN           0x14000031
#define ATP_SYS_LOG_WLAN_SSID_STATUS_CLOSE          0x14000032
#define ATP_SYS_LOG_WLAN_STATUS_CHANGED             0x14000033

/*
 * Log Items for WLAN_FORCOVER
 */
#define ATP_SYS_LOG_WLAN_SYNC_EXTAP_ALIVE             0x14000034
#define ATP_SYS_LOG_WLAN_SYNC_EXTAP_BYEBYE            0x14000035
#define ATP_SYS_LOG_WLAN_SYNC_EXTAP_SYNC_START        0x14000036
#define ATP_SYS_LOG_WLAN_SYNC_EXTAP_SYNC_SUCCESS      0x14000037
#define ATP_SYS_LOG_WLAN_SYNC_EXTAP_SYNC_FAILURE      0x14000038
#define ATP_SYS_LOG_WLAN_SYNC_EXTAP_STA_ALIVE         0x14000039
#define ATP_SYS_LOG_WLAN_SYNC_EXTAP_STA_BYEBYE        0x1400003a

/*
 * Log Items for WLAN_FBT
 */
#define ATP_SYS_LOG_WLAN_FBT_STA_RSSI_WEAK            0x1400003b
#define ATP_SYS_LOG_WLAN_FBT_STA_RSSI_STRONG          0x1400003c
#define ATP_SYS_LOG_WLAN_FBT_EXTSTA_FOUND             0x1400003d
#define ATP_SYS_LOG_WLAN_FBT_EXTSTA_KICKOUT           0x1400003e
#define ATP_SYS_LOG_WLAN_FBT_EXTSTA_SUCCESS           0x1400003f
#define ATP_SYS_LOG_WLAN_FBT_EXTSTA_FAILURE           0x14000040

#define ATP_SYS_LOG_WLAN_ASSOC                        0x14000041
#define ATP_SYS_LOG_WLAN_SSID_BROADCAST_OPEN          0x14000042
#define ATP_SYS_LOG_WLAN_SSID_BROADCAST_CLOSE         0x14000043
#define ATP_SYS_LOG_WLAN_SSID_ISOLATE_OPEN            0x14000044
#define ATP_SYS_LOG_WLAN_SSID_ISOLATE_CLOSE           0x14000045
#define ATP_SYS_LOG_WLAN_OFFTIME_CHANGE               0x14000046
#define ATP_SYS_LOG_WLAN_MAXASSOCNUM_CHANGE           0x14000047
#define ATP_SYS_LOG_WLAN_AUTHTYPE_CHANGED             0x14000048
#define ATP_SYS_LOG_WLAN_COUNTRY_ADAPTER_OPEN         0x14000049 
#define ATP_SYS_LOG_WLAN_COUNTRY_ADAPTER_CLOSE        0x1400004a
#define ATP_SYS_LOG_WLAN_FREQUENCYBAND_STATUS_CHANGE  0x1400004b
#define ATP_SYS_LOG_WLAN_COUNTRYCODE_CHANGE           0x1400004c
#define ATP_SYS_LOG_WLAN_CHANNEL_CHANGE               0x1400004d
#define ATP_SYS_LOG_WLAN_BANDWIDTH_CHANGE             0x1400004e
#define ATP_SYS_LOG_WLAN_MAC_SWITCH_CHANGED           0x1400004f
#define ATP_SYS_LOG_WLAN_MAC_CHANGED                  0x14000050
#define ATP_SYS_LOG_WLAN_WPS_FAIL                     0x14000051
#define ATP_SYS_LOG_WLAN_WPS_OVERLAP                  0x14000052
#define ATP_SYS_LOG_WLAN_WPS_CLOSE                    0x14000053
#define ATP_SYS_LOG_WLAN_WPS_CANCEL                   0x14000054
#define ATP_SYS_LOG_WLAN_WPS_TIMEOUT                  0x14000055
#define ATP_SYS_LOG_WLAN_WPS_OPEN                     0x14000056
#define ATP_SYS_LOG_WLAN_HILINK_PRESSED               0x14000057
#define ATP_SYS_LOG_WLAN_WPS_PRESSED                  0x14000058
#define ATP_SYS_LOG_WLAN_ONLINE                       0x14000059
#define ATP_SYS_LOG_WLAN_OFFLINE                      0x1400005a
#define ATP_SYS_LOG_WLAN_CLOSE_MACFILTER              0x1400005b
#define ATP_SYS_LOG_WLAN_SET_MACFILTER_BLACK          0x1400005c
#define ATP_SYS_LOG_WLAN_SET_MACFILTER_WHITE          0x1400005d
#define ATP_SYS_LOG_WLAN_HILINK_NEWDEVIN              0x1400005e
#define ATP_SYS_LOG_WLAN_HILINK_NEWDEVREMOVE          0x1400005f
#define ATP_SYS_LOG_WLAN_HILINK_NEWDEVADDEDOK         0x14000060
#define ATP_SYS_LOG_WLAN_HILINK_NEWDEVADDEDNOK        0x14000061
#define ATP_SYS_LOG_WLAN_HILINK_NEWDEVINBYAPP         0x14000062
#define ATP_SYS_LOG_WLAN_HILINK_NEWDEVINBYKEY         0x14000063

/*
 * Log Items for IGMP
 */
#define ATP_SYS_LOG_IGMP_LEAVE_INFO                   0x4000000
#define ATP_SYS_LOG_IGMP_REPORT_INFO_MODE             0x4000001
#define ATP_SYS_LOG_IGMP_REPORT_INFO                  0x4000002
#define ATP_SYS_LOG_IGMP_QUERY_INFO                   0x4000003

/*
 * Log Items for L2TP
 */
#define ATP_SYS_LOG_L2TP_CONNECTING                   0x4100000
#define ATP_SYS_LOG_L2TP_CONNECTING_SUCCESS           0x4100001
#define ATP_SYS_LOG_L2TP_DISCONNECTED                 0x4100002
#define ATP_SYS_LOG_L2TP_GET_FROM_INVALID_SERVER      0x4100003

/*
 * Log Items for FIREWALL
 */
#define ATP_SYS_LOG_FW_CHANGE_TO_LEVEL                0xac000000
#define ATP_SYS_LOG_FW_FITER_LEVEL_ADD                0xac000001
#define ATP_SYS_LOG_FW_FILTER_LEVEL_MOD               0xac000002
#define ATP_SYS_LOG_FW_NEW_ACC_CTRL_ENTRY_ADD         0xac000003
#define ATP_SYS_LOG_FW_ACC_CTRL_ENTRY_MOD             0xac000004
#define ATP_SYS_LOG_FW_ACC_CTRL_ENTRY_DEL             0xac000005
#define ATP_SYS_LOG_FW_NEW_IP_FILTER_ENTRY_ADD        0xac000006
#define ATP_SYS_LOG_FW_IP_FILTER_ENTRY_MOD            0xac000007
#define ATP_SYS_LOG_FW_NEW_URL_FILTER_BLIST_ADD       0xac000008
#define ATP_SYS_LOG_FW_NEW_URL_FILTER_BLIST_MOD       0xac000009
#define ATP_SYS_LOG_FW_DOS_ENTRY_MOD                  0xac00000a
#define ATP_SYS_LOG_FW_FILTER_LEVEL_DEL               0xac00000b
#define ATP_SYS_LOG_FW_IP_FILTER_ENTRY_DEL            0xac00000c
#define ATP_SYS_LOG_FW_KEYWORD_ADD                    0xac00000d
#define ATP_SYS_LOG_FW_KEYWORD_MOD                    0xac00000e
#define ATP_SYS_LOG_FW_KEYWORD_DEL                    0xac00000f
#define ATP_SYS_LOG_FW_URL_FILTER_BLIST_DEL           0xac000010
#define ATP_SYS_LOG_FW_URL_FILTER_WLIST_DEL           0xac000011
#define ATP_SYS_LOG_FW_NEW_URL_FILTER_WLIST_ADD       0xac000012
#define ATP_SYS_LOG_FW_URL_FILTER_WLIST_MOD           0xac000013
#define ATP_SYS_LOG_FW_ACL_ADD                        0xac000014
#define ATP_SYS_LOG_FW_ACL_DELETE                     0xac000015
#define ATP_SYS_LOG_FW_ACL_MODIFY                     0xac000016
#define ATP_SYS_LOG_FW_DOS_ATTACK                     0xac000023
#define ATP_SYS_LOG_FW_LEVEL_TOO_LONG                 0xac000024
#define ATP_SYS_LOG_FW_LEVEL_NOT_FOUND                0xac000025
#define ATP_SYS_LOG_FW_DOS_ATTACK_DISABLE             0xac000026
#define ATP_SYS_LOG_FW_DOS_ATTACK_ENABLE              0xac000027
#define ATP_SYS_LOG_FW_ICMP_SMURF                     0xac000028
#define ATP_SYS_LOG_FW_UDP_PORT_SCAN                  0xac000029
#define ATP_SYS_LOG_FW_MACFILTER_ADD                  0xac000030
#define ATP_SYS_LOG_FW_MACFILTER_MOD                  0xac000031
#define ATP_SYS_LOG_FW_MACFILTER_DEL                  0xac000032
#define ATP_SYS_LOG_FW_MAIN_SWITCH                    0xac000033
#define ATP_SYS_LOG_FW_IPFLT_SWITCH                   0xac000034
#define ATP_SYS_LOG_FW_WANPING_SWITCH                 0xac000035
#define ATP_SYS_LOG_FW_MACFLT_SWITCH                  0xac000036
#define ATP_SYS_LOG_FW_URLFLT_SWITCH                  0xac000037
#define ATP_SYS_LOG_FW_URL_FILTER_MOD                 0xac000038
#define ATP_SYS_LOG_FW_URLSAVE_FILTER_ADD             0xac000039
#define ATP_SYS_LOG_FW_URLSAVE_FILTER_MOD             0xac00003a
#define ATP_SYS_LOG_FW_URLSAVE_FILTER_DEL             0xac00003b
#define ATP_SYS_LOG_FW_URLSAVE_FILTER_ENABLE          0xac00003c
#define ATP_SYS_LOG_FW_URLSAVE_FILTER_DISABLE         0xac00003d  
#define ATP_SYS_LOG_FW_IP_FILTER_CHANGEMODE           0xac00003e
#define ATP_SYS_LOG_FW_URLFILTER_CHANGEMODE           0xac00003f
#define ATP_SYS_LOG_FW_URL_FILTER_ADD                 0xac000040
#define ATP_SYS_LOG_FW_URL_FILTER_DEL                 0xac000041



/*
 * Log Items for QOS
 */
#define ATP_SYS_LOG_QOS_RATE_CAP_SET                  0x4d000000

/*
 * Log Items for USBMOUNT
 */
#define ATP_SYS_LOG_UMOUNT_MANUAL_UMOUNT                0x15000000
#define ATP_SYS_LOG_UMOUNT_DEV_BUSY                     0x15000001
#define ATP_SYS_LOG_UMOUNT_PRT_CONN                     0x15000002
#define ATP_SYS_LOG_UMOUNT_PRT_DISCONN                  0x15000003
#define ATP_SYS_LOG_UMOUNT_MOUNT                        0x15000004
#define ATP_SYS_LOG_UMOUNT_AUTO_MOUNT                   0x15000005
#define ATP_SYS_LOG_UMOUNT_UNKNOWN_DEV_CONN             0x15000006
#define ATP_SYS_LOG_UMOUNT_DISCONN_HUB                  0x15000007
#define ATP_SYS_LOG_UMOUNT_CONN_HUB                     0x15000008
#define ATP_SYS_LOG_UMOUNT_CREATE_USER                  0x15000009
#define ATP_SYS_LOG_UMOUNT_CHANGE_USER_INFO             0x1500000a
#define ATP_SYS_LOG_UMOUNT_60MINUTES_BLOCKING_EXPIRED   0x1500000b
#define ATP_SYS_LOG_UMOUNT_USER_LOGIN_INFO              0x1500000c
#define ATP_SYS_LOG_UMOUNT_USER_LOGOUT_INFO             0x1500000d
#define ATP_SYS_LOG_UMOUNT_DELETE_USER                  0x1500000e
#define ATP_SYS_LOG_UMOUNT_STORAGE_95_FULL              0x1500000f
#define ATP_SYS_LOG_UMOUNT_STORAGE_100_FULL             0x15000010
#define ATP_SYS_LOG_UMOUNT_NAS_SYNCBACKUP_START               0x15000011
#define ATP_SYS_LOG_UMOUNT_NAS_SYNCBACKUP_FINISH              0x15000012
#define ATP_SYS_LOG_UMOUNT_NAS_SYNCBACKUP_FAIL                0x15000013
#define ATP_SYS_LOG_UMOUNT_LOCAL_USER_FAIL_LOGIN_5_TIMES     0x15000014
#define ATP_SYS_LOG_UMOUNT_REMOTE_USER_FAIL_LOGIN_5_TIMES    0x15000015
#define ATP_SYS_LOG_UMOUNT_USER_LOGIN_FAIL_INFO         0x15000016
#define ATP_SYS_LOG_UMOUNT_STORAGE_NOT_WORKING          0x15000017
#define ATP_SYS_LOG_UMOUNT_TOP_LEVEL_FLODER_CREATE      0x15000018
#define ATP_SYS_LOG_UMOUNT_TOP_LEVEL_FLODER_DELETE      0x15000019
#define ATP_SYS_LOG_UMOUNT_TOP_LEVEL_FLODER_RENAME      0x1500001a
#define ATP_SYS_LOG_UMOUNT_FTP_START                    0x1500001b
#define ATP_SYS_LOG_UMOUNT_FTP_STOP                     0x1500001c
#define ATP_SYS_LOG_UMOUNT_FTP_LOGIN_ERROR_PASSWORD     0x1500001d
#define ATP_SYS_LOG_UMOUNT_SMB_START                    0x1500001e
#define ATP_SYS_LOG_UMOUNT_SMB_STOP                     0x1500001f
#define ATP_SYS_LOG_UMOUNT_CHANGE_USER_USERNAME         0x15000020
#define ATP_SYS_LOG_UMOUNT_CHANGE_USER_PASSWORD         0x15000021
#define ATP_SYS_LOG_UMOUNT_CHANGE_USER_PATH             0x15000022
#define ATP_SYS_LOG_UMOUNT_CHANGE_USER_ACCESS_READONLY  0x15000023
#define ATP_SYS_LOG_UMOUNT_CHANGE_USER_ACCESS_READWRITE 0x15000024
#define ATP_SYS_LOG_UMOUNT_CHANGE_USER_ENABLE_ENABLE    0x15000025
#define ATP_SYS_LOG_UMOUNT_CHANGE_USER_ENABLE_DISABLE   0x15000026
#define ATP_SYS_LOG_UMOUNT_FTP_LONGIN_SUCCESS           0x15000027
#define ATP_SYS_LOG_UMOUNT_FTP_LONGIN_FAILED            0x15000028
#define ATP_SYS_LOG_UMOUNT_SAMBA_LONGIN_SUCCESS         0x15000029
#define ATP_SYS_LOG_UMOUNT_SAMBA_LONGIN_FAILED          0x1500002a
#define ATP_SYS_LOG_UMOUNT_SAMBA_LONGOUT_SUCCESS        0x1500002b
#define ATP_SYS_LOG_UMOUNT_FTP_LONGOUT_SUCCESS          0x1500002c
#define ATP_SYS_LOG_UMOUNT_ACCOUNT_FORBBIDEN            0x1500002d
#define ATP_SYS_LOG_UMOUNT_ACCOUNT_RELEASE              0x1500002e
#define ATP_SYS_LOG_SAMBA_STATUS_ENABLE                 0x1500002f
#define ATP_SYS_LOG_SAMBA_STATUS_DISABLE                0x15000030

/*
 * Log Items for CLI
 */
#define ATP_SYS_LOG_CLI_LOGIN_OK                      0x84000000
#define ATP_SYS_LOG_CLI_LOGOUT                        0x84000001
#define ATP_SYS_LOG_CLI_LOGIN_ERR                     0x84000002
#define ATP_SYS_LOG_CLI_LOGIN_LOCKED                  0x84000003
#define ATP_SYS_LOG_CLI_LOGIN_UNLOCKED                0x84000004

/*
 * Log Items for BHAL
 */
#define ATP_SYS_LOG_BHAL_FLASH_READ_ERR               0x85000000
#define ATP_SYS_LOG_BHAL_FLASH_WRITE_ERR              0x85000001
#define ATP_SYS_LOG_BHAL_ASSEMBLE_ERR                 0x85000002
#define ATP_SYS_LOG_BHAL_AUTOREBOOT_ERR               0x85000003

/*
 * Log Items for XDSL
 */
#define ATP_SYS_LOG_XDSL_DSL_CONN                     0xbd000000
#define ATP_SYS_LOG_XDSL_DSL_DISCONN                  0xbd000001
#define ATP_SYS_LOG_XDSL_DSL_TRAINING                 0xbd000002

/*
 * Log Items for NAT
 */
#define ATP_SYS_LOG_NAT_DMZ_HOST_IP_ADD               0x4f000000
#define ATP_SYS_LOG_NAT_DMZ_HOST_IP_DEL               0x4f000001
#define ATP_SYS_LOG_NAT_DMZ_HOST_IP_MOD               0x4f000002
#define ATP_SYS_LOG_NAT_PORT_MAP_ENTRY                0x4f000003
#define ATP_SYS_LOG_NAT_PORT_TRIGGER_ENTRY            0x4f000004
#define ATP_SYS_LOG_NAT_DMZ_ENABLE                    0x4f000005
#define ATP_SYS_LOG_NAT_DMZ_DISABLE                   0x4f000006
#define ATP_SYS_LOG_NAT_DMZ_NOWAN_HOST_MOD            0x4f000007
#define ATP_SYS_LOG_NAT_APPPORT_MAP_SET               0x4f000008
#define ATP_SYS_LOG_NAT_APPPORT_MAP_ENABLE            0x4f000009
#define ATP_SYS_LOG_NAT_APPPORT_MAP_DISABLE           0x4f00000A
#define ATP_SYS_LOG_NAT_APPPORT_MAP_DEL               0x4f00000B
#define ATP_SYS_LOG_NAT_NATTYPE_SYMMETRY              0x4f00000C
#define ATP_SYS_LOG_NAT_NATTYPE_PORT_RESTRICT         0x4f00000D
#define ATP_SYS_LOG_NAT_PORT_MAP_RULE_ADD             0x4f00000E
#define ATP_SYS_LOG_NAT_PORT_MAP_RULE_DELETE          0x4f00000F
#define ATP_SYS_LOG_NAT_PORT_TRIGGER_RULE_ADD         0x4f000010
#define ATP_SYS_LOG_NAT_PORT_TRIGGER_RULE_DELETE      0x4f000011



/*
 * Log Items for DNS
 */
#define ATP_SYS_LOG_DNS_QUERY_FAIL                    0x76000000
#define ATP_SYS_LOG_DNS_DNSV6_NOREPLY                 0x76000001

/*
 * Log Items for LOG
 */
#define ATP_SYS_LOG_LOG_CONFIG_SERVER                 0x1b000000
#ifdef SUPPORT_ATP_EUAP
#define ATP_SYS_LOG_LOG_CLEAR_EUAP                    0x1b000001
#endif
#define ATP_SYS_LOG_LOG_CLEAR                        (0x1b000001 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_LOG_DNSREADY                      0x1b000002
#define ATP_SYS_LOG_LOG_CLEAR_BY_BUTTON_RESET  (0x1b000006 | LOG_FLUSH_MASK)

/*
 * Log Items for PPPINTF
 */
#define ATP_SYS_LOG_INTERNET_TERMINATED               0x11f00001
#define ATP_SYS_LOG_INTERNET_ESTABLISHED              0x11f00002
#define ATP_SYS_LOG_INTERNET_ESTABLISHED_DEFAULT      0x11f00003
#define ATP_SYS_LOG_INTERNET_ESTABLISHED_SETUP        0x11f00004
#define ATP_SYS_LOG_INTERNET_GATEWAY_IP_ADDR          0x11f00005

/*
 * Log Items for DLNA
 */
#define ATP_SYS_LOG_UPNP_AV_START                     0x1d000001
#define ATP_SYS_LOG_UPNP_AV_STOP                      0x1d000002
#define ATP_SYS_LOG_DMS_UPLOAD_OBJ                    0x1d000003
#define ATP_SYS_LOG_DMS_DESTROY_OBJ                   0x1d000004

/*
 * Log Items for ETHLINK
 */
#define ATP_SYS_LOG_EXTERNALMODEM_DOWN                0x11900001
#define ATP_SYS_LOG_EXTERNALMODEM_UP                  0x11900002

/*
 * Log Items for DHCP6C
 */
#define ATP_SYS_LOG_DHCP6C_WAN_ADDR                     0x09d00001
#define ATP_SYS_LOG_DHCP6C_GATEWAY_ADDR                 0x09d00002
#define ATP_SYS_LOG_DHCP6C_ESTABLISHED_WITH_PREFIX      0x09d00003
#define ATP_SYS_LOG_DHCP6C_ESTABLISHED_WITHOUT_PREFIX   0x09d00004
#define ATP_SYS_LOG_DHCP6C_DNS                          0x09d00005


/*
 * Log Items for DHCP6S
 */
#define ATP_SYS_LOG_DHCP6S_ACTIVE                           0x3400000
#define ATP_SYS_LOG_DHCP6S_DEACTIVE                       0x3400001

/*
 * Log Items for RA
 */
#define ATP_SYS_LOG_RA_IPv6_PREFIX_CHANGE           0x6e00000


/*
 * Log Items for DIALUP
 */
#define ATP_SYS_LOG_DIALUP_PIN_FAIL         0x28700001
#define ATP_SYS_LOG_DIALUP_PUK_FAIL         0x28700002
#define ATP_SYS_LOG_DIALUP_SIMLOCK_FAIL     0x28700003

#define ATP_SYS_LOG_SMS_USESREPORT_ON                0x28700006
#define ATP_SYS_LOG_SMS_VALIDITY_CHANGE              0x28700007
#define ATP_SYS_LOG_SMS_CENTER_CHANGE                0x28700008
#define ATP_SYS_LOG_SMS_USESREPORT_OFF               0x28700009
#define ATP_SYS_LOG_SMS_BACKUP_SIM                   0x2870000a
#define ATP_SYS_LOG_SMS_DELET                        0x2870000b
#define ATP_SYS_LOG_SMS_BACKUP_SIM_FAIL              0x2870000c
#define ATP_SYS_LOG_SMS_DELET_FAIL                   0x2870000d






/*
 * Log Items for FON
 */
#define ATP_SYS_LOG_FON_HB_VALID_RESPONSE             0xdb000000
#define ATP_SYS_LOG_FON_HB_NO_RESPONSE                0xdb000001
#define ATP_SYS_LOG_FON_SSID_ACTIVE                   0xdb000002
#define ATP_SYS_LOG_FON_SSID_DEACTIVE                 0xdb000003

/*
 * Log Items for SHOPASSIST
 */
#define ATP_SYS_LOG_SHOPASSIST_GWD_ENABLE             0xdc000000
#define ATP_SYS_LOG_SHOPASSIST_GWD_DISABLE            0xdc000001
/*
 * Log Items for XUNLEIDOWNLOAD
 */
#define ATP_SYS_LOG_XUNLEIDOWNLOAD_DISABLE           0xdd000000
#define ATP_SYS_LOG_XUNLEIDOWNLOAD_ENABLE            0xdd000001
#define ATP_SYS_LOG_XUNLEIDOWNLOAD_UNBIND            0xdd000002
#define ATP_SYS_LOG_HA_HAAP_SERVER_ADDR 0x2d400000
#define ATP_SYS_LOG_HA_DSL_TUNNEL_UP 0x2d400001
#define ATP_SYS_LOG_HA_LTE_TUNNEL_UP 0x2d400002
#define ATP_SYS_LOG_HA_TUNNEL_IPV4_ADDR 0x2d400003
#define ATP_SYS_LOG_HA_TUNNEL_IPV6_PREFIX 0x2d400004
#define ATP_SYS_LOG_HA_TELEKOM_LIST_RECEIVED 0x2d400005
#define ATP_SYS_LOG_HA_BONDING_STARTED 0x2d400006
#define ATP_SYS_LOG_HA_LTE_TUNNEL_REQUEST_TIMEOUT 0x2d400007
#define ATP_SYS_LOG_HA_DSL_TUNNEL_REQUEST_TIMEOUT 0x2d400008
#define ATP_SYS_LOG_HA_LTE_TUNNEL_DOWN 0x2d400009
#define ATP_SYS_LOG_HA_DSL_TUNNEL_DOWN 0x2d40000a
#define ATP_SYS_LOG_HA_DSL_TOID_UNAUTHORIZED 0x2d40000b
#define ATP_SYS_LOG_HA_LTE_MSISDN_UNAUTHORIZED 0x2d40000c
#define ATP_SYS_LOG_HA_LTEDSL_ID_MISMATCH 0x2d40000d
#define ATP_SYS_LOG_HA_SESSION_ID_ERROR 0x2d40000e
#define ATP_SYS_LOG_HA_CIN_ERROR 0x2d40000f
#define ATP_SYS_LOG_HA_TERMINATE_TUNNEL_DOWN 0x2d400010
#define ATP_SYS_LOG_HA_WEB_REBOOT 0x2d400011

#define ATP_SYS_LOG_CLOUD_VISIT 0x26c00000
#define ATP_SYS_LOG_CLOUD_MODIFY 0x26c00001
#define ATP_SYS_LOG_CLOUD_BIND 0x26c00002 
#define ATP_SYS_LOG_CLOUD_UNBIND 0x26c00003


/*Log Items for Diagnose*/
#define ATP_SYS_LOG_DIAGNOSE_PING  0x27000000
/*
 * Log Items for device
 */
#define ATP_SYS_LOG_DEVICE_SET_ANTENNA         0x29700001
#define ATP_SYS_LOG_DEVICE_SET_LED_CIRCLE      0x29700002
#define ATP_SYS_LOG_USER_KEY                   (0x29700003 | LOG_FLUSH_MASK)
/*
 * Log Items for statistic
 */
#define ATP_SYS_LOG_STATISTIC_CLEAR_RECORED         0x30700001
#define ATP_SYS_LOG_STATISTIC_SET_MONTHSTATISTIC         0x30700002

#define ATP_SYS_LOG_VERIFY_PIN_FAIL      0x31d00000
#define ATP_SYS_LOG_VERIFY_PIN_SUCCESS   0x31d00001
#define ATP_SYS_LOG_VERIFY_PUK_FAIL      0x31d00002
#define ATP_SYS_LOG_VERIFY_PUK_SUCCESS   0x31d00003
#define ATP_SYS_LOG_ENABLE_PIN_FAIL      0x31d00004
#define ATP_SYS_LOG_ENABLE_PIN_SUCCESS   0x31d00005
#define ATP_SYS_LOG_DISABLE_PIN_FAIL     0x31d00006
#define ATP_SYS_LOG_DISABLE_PIN_SUCCESS  0x31d00007
#define ATP_SYS_LOG_MODIFY_PIN_FAIL      0x31d00008
#define ATP_SYS_LOG_MODIFY_PIN_SUCCESS   0x31d00009

#define ATP_SYS_LOG_ENABLE_DATASWITCH    0x31c00000
#define ATP_SYS_LOG_DISABLE_DATASWITCH   0x31c00001
#define ATP_SYS_LOG_SET_CONNECTIONPARAM  0x31c00002
#define ATP_SYS_LOG_MANUAL_CONNECT       0x31c00003
#define ATP_SYS_LOG_MANUAL_DISCONNECT    0x31c00004
#define ATP_SYS_LOG_PROFILE_DELETE       0x31c00005
#define ATP_SYS_LOG_PROFILE_ADD          0x31c00006
#define ATP_SYS_LOG_PROFILE_MODIFY       0x31c00007
#define ATP_SYS_LOG_PROFILE_SETDEFAULT   0x31c00008
#define ATP_SYS_LOG_NET_REGISTER         0x31c00009
#define ATP_SYS_LOG_NET_SETMODE          0x31c0000a
#define ATP_SYS_LOG_NET_SEARCH           0x31c0000b
#ifdef SUPPORT_ATP_CPE_SBB
/*reboot and reset event need | LOG_FLUSH_MASK to make the sequence correct*/
#define ATP_SYS_LOG_SBB_RSTKEY_REBOOT                 (0x28a00001 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_CLI_REBOOT                    (0x28a00002 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_UPG_REBOOT                    (0x28a00003 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_WEBUI_REBOOT                  (0x28a00004 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_OTHER_REBOOT                  (0x28a00005 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_RSTKEY_RESET                  (0x28a00006 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_WEBUI_RESET                   (0x28a00007 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_OS_BOOTUP                     (0x28a00008 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_VERSION_REPORT                (0x28a00009 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_WATCHDOG_AFTER_REBOOT         (0x28a0000a | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_TASK_RESTART                  (0x28a0000b | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_SOFT_LOOKUP                   (0x28a0000c | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_CFGFILE_DOWNLOAD_ERR          (0x28a0000d | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_FIRMWARE_DOWNLOAD_ERR         (0x28a0000e | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_CFGFILE_READ_ERR              (0x28a0000f | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_CFGFILE_SYNTAX_ERR            (0x28a00010 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_FIRMWARE_CHKSUM_ERR           (0x28a00011 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_FIRMWARE_WRITE_TO_OLSPACE_ERR (0x28a00012 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_FIRMWARE_SIZE_ERR             (0x28a00013 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_FIRMWARE_WRITE_TO_WKSPACE_ERR (0x28a00014 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_WAN_UP                        (0x28a00015 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_WAN_DOWN                      (0x28a00016 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_TELNET_LOGIN_FAILED           (0x28a00017 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_TELNET_LOGIN_SUCCESS          (0x28a00018 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_WPS_PIN                       (0x28a00019 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_WPS_PBC                       (0x28a0001a | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_DFS                           (0x28a0001b | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_REGULAR_REPORT                (0x28a0001c | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_CEREG_REPORT                  (0x28a0001d | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_RSRP_REPORT                   (0x28a0001e | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_RSRQ_REPORT                   (0x28a0001f | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_SINR_REPORT                   (0x28a00020 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_PCONI_REPORT                  (0x28a00021 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_NBCELL_REPORT                 (0x28a00022 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_MIMO_REPORT                   (0x28a00023 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_CPE_INFO                      (0x28a00024 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_UPTIME_FREEMEN_REPORT         (0x28a00025 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_WIFI_STATUS_REPORT            (0x28a00026 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_LTE_INFO_REPORT               (0x28a00027 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_SYSLOG_SERVER_CHANGE          (0x28a00028 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_BAND_FDD_REPORT               (0x28a00029 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_TDDTOFDD_REBOOT               (0x28a0002a | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_FDDCHECKTDD_REBOOT            (0x28a0002b | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_NOTDD_TOFDD_REBOOT            (0x28a0002c | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_NOFDD_TOTDD_REBOOT            (0x28a0002d | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_FDDTOTDD_REBOOT               (0x28a0002e | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_FDD_REBOOT_COUNTER            (0x28a0002f | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_TFTPSERVER_CHANGE             (0x28a00030 | LOG_FLUSH_MASK)
#define ATP_SYS_LOG_SBB_REPORT_ANT_RSRP_SINR          (0x28a00031 | LOG_FLUSH_MASK)
#endif /*SUPPORT_ATP_CPE_SBB*/
/*Hilink Message*/
#define ATP_SYS_LOG_HILINK_STA_ONLINE                 (0x28100001)     
#define ATP_SYS_LOG_HILINK_STA_ONEKEYCONNECTION       (0x28100002)
#define ATP_SYS_LOG_HILINK_EXTAP_ACCESS_BY_ETHERNET   (0x28100003)
#define ATP_SYS_LOG_HILINK_HAC_SYNC_KEY               (0x28100004)
#define ATP_SYS_LOG_HILINK_EXTAP_UPG                  (0x28100005)
#define ATP_SYS_LOG_HILINK_STA_FBT                    (0x28100006)

#ifdef SUPPORT_ATP_SMARTHOME
#define ATP_SYS_LOG_HILINK_DEV_ATTR_REPORT            (0x28d00007)
#define ATP_SYS_LOG_HILINK_DEV_STATUS_ONLINE          (0x28d00008)
#define ATP_SYS_LOG_HILINK_DEV_STATUS_OFFLINE         (0x28d00009)
#define ATP_SYS_LOG_HILINK_GW_LOGIN_SUCC              (0x28d0000a)
#define ATP_SYS_LOG_HILINK_GW_LOGIN_FAIL              (0x28d0000b)
#define ATP_SYS_LOG_HILINK_DEV_REG_SUCC               (0x28d0000c)
#define ATP_SYS_LOG_HILINK_DEV_REG_FAIL               (0x28d0000d)
#define ATP_SYS_LOG_HILINK_LOCAL_LOGIN_SUCC           (0x28d0000e)
#define ATP_SYS_LOG_HILINK_LOCAL_LOGIN_FAIL           (0x28d0000f)
#define ATP_SYS_LOG_HILINK_LOCAL_LOGIN_LOCK           (0x28d00010)
#define ATP_SYS_LOG_HILINK_LOCAL_LOGIN_UNLOCK         (0x28d00011)
#define ATP_SYS_LOG_HILINK_DEV_ONLINE_TOAPP           (0x28d00012)
#define ATP_SYS_LOG_HILINK_DEV_OFFLINE_TOAPP          (0x28d00013)
#define ATP_SYS_LOG_HILINK_DEV_DATACHANGE_TOAPP       (0x28d00014)
#define ATP_SYS_LOG_SMARTHOME_ACCOUNT_UPDATED_ERROR   (0x28d00015)
#define ATP_SYS_LOG_SMARTHOME_ACCOUNT_UPDATED_OK      (0x28d00016)
#define ATP_SYS_LOG_SMARTHOME_ROOM_UPDATED_ERROR      (0x28d00017)
#define ATP_SYS_LOG_SMARTHOME_ROOM_UPDATED_OK         (0x28d00018)
#define ATP_SYS_LOG_SMARTHOME_SCENE_UPDATED_ERROR     (0x28d00019)
#define ATP_SYS_LOG_SMARTHOME_SCENE_UPDATED_OK        (0x28d0001a)
#define ATP_SYS_LOG_SMARTHOME_TOKEN_GET               (0x28d0001b)
#define ATP_SYS_LOG_SMARTHOME_TOKEN_GENERATE          (0x28d0001c)
#define ATP_SYS_LOG_SMARTHOME_TOKEN_REFRESH           (0x28d0001d)
#define ATP_SYS_LOG_HILINK_DEV_SETATTR                (0x28d0001e)
#endif

#ifdef SUPPORT_ATP_HIBRIDGE
#define ATP_SYS_LOG_HILINK_BRIDGE_SESSION             (0x28200020)
#define ATP_SYS_LOG_HILINK_BRIDGE_DEVREGISTERED       (0x28200021)
#endif

#ifdef SUPPORT_ATP_PLC
#define ATP_SYS_LOG_PLC_LOG_ERR                		  (0x28300001)     
#define ATP_SYS_LOG_PLC_LOG_NOTICE       			  (0x28300002)
#endif

/* SEC */
/* FOR Upgrade management */
#define ATP_SEC_LOG_KM_UPGRADE_ADDKEY                       (0x9f000001)
#define ATP_SEC_LOG_KM_UPGRADE_UPDKEY                       (0x9f000002)
#define ATP_SEC_LOG_KM_UPGRADE_DELKEY                       (0x9f000003)
/* FOR Certificate  management */
#define ATP_SEC_LOG_KM_CERT_ADDKEY                          (0x9f000011)
#define ATP_SEC_LOG_KM_CERT_UPDKEY                          (0x9f000012)
#define ATP_SEC_LOG_KM_CERT_DELKEY                          (0x9f000013)
/* FOR Configuration management */
#define ATP_SEC_LOG_KM_CFG_ADDKEY                           (0x9f000021)
#define ATP_SEC_LOG_KM_CFG_UPDKEY                           (0x9f000022 | LOG_FLUSH_MASK)
#define ATP_SEC_LOG_KM_CFG_DELKEY                           (0x9f000023)
/* FOR CWMP */
#define ATP_SEC_LOG_KM_CWMP_ADDKEY                          (0x9f000031)
#define ATP_SEC_LOG_KM_CWMP_UPDKEY                          (0x9f000032)
#define ATP_SEC_LOG_KM_CWMP_DELKEY                          (0x9f000033)
/* FOR XMPP */
#define ATP_SEC_LOG_KM_XMPP_ADDKEY                          (0x9f000041)
#define ATP_SEC_LOG_KM_XMPP_UPDKEY                          (0x9f000042)
#define ATP_SEC_LOG_KM_XMPP_DELKEY                          (0x9f000043)
/* FOR OTHER */
#define ATP_SEC_LOG_KM_OTHER_ADDKEY                         (0x9f000051)
#define ATP_SEC_LOG_KM_OTHER_UPDKEY                         (0x9f000052)
#define ATP_SEC_LOG_KM_OTHER_DELKEY                         (0x9f000053)



#endif // __ATP_LOG_DEF_H__
