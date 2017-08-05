/*********************************************************************************
  *         版权所有 (C), 2010-2030, 华为技术有限公司
**********************************************************************************/

#ifndef __ATPCONFIG_COMMON_H__
#define __ATPCONFIG_COMMON_H__

#include <stdio.h>
#include <stdlib.h>

/*特性宏梳理，需要将常规的宏定义到该头文件下*/
#ifndef ATP_SYSINFO_MANUFACTURER
#define  ATP_SYSINFO_MANUFACTURER   "Huawei Technologies Co., Ltd."
#endif
#ifndef ATP_SYSINFO_MODELNAME
#define ATP_SYSINFO_MODELNAME    "Router"
#endif
#ifndef ATP_SYSINFO_DESCRIPTION
#define ATP_SYSINFO_DESCRIPTION    "Huawei Home Gateway"
#endif 
#ifndef ATP_SYSINFO_SPECVERSION
#define ATP_SYSINFO_SPECVERSION    "1.0"
#endif
#ifndef ATP_MANUFACTURER_OUI
#define ATP_MANUFACTURER_OUI "00E0FC"
#endif
#ifndef ATP_UPG_WEB_IMAGE_FILENAME1
#define ATP_UPG_WEB_IMAGE_FILENAME1  "imagefilename"
#endif
#ifndef ATP_USB_PRINTER_CUPS_BUFFER_SIZE
#define ATP_USB_PRINTER_CUPS_BUFFER_SIZE  40
#endif
#ifndef ATP_WANETH_LAN_PORT_SELECT
#define ATP_WANETH_LAN_PORT_SELECT   "LAN4"
#endif
#ifndef ATP_BALONG_INTERFACE
#define ATP_BALONG_INTERFACE    ""
#endif
#ifndef ATP_BALONG_MACADDR
#define ATP_BALONG_MACADDR      ""
#endif
#ifndef ATP_UPGRADE_VALUESCHANGE_LUA_FILE
#define ATP_UPGRADE_VALUESCHANGE_LUA_FILE    "changevalues.lua"
#endif
#ifndef SUPPORT_ATP_WEB_PASSWORD_SHA256
#define SUPPORT_ATP_WEB_PASSWORD_SHA256 1
#endif
#ifndef ATP_WEB_HTML_PATH_PERFIX
#ifdef SUPPORT_ATP_EUAP
#define ATP_WEB_HTML_PATH_PERFIX   "/app/webroot/WebApp/common/"
#else
#define ATP_WEB_HTML_PATH_PERFIX   "/html/"
#endif
#endif
#ifndef ATP_WEB_HTML_TITLE
#define ATP_WEB_HTML_TITLE   "ATP"
#endif
#ifndef ATP_WEB_DEFAULT_IDLE_TIME
#define ATP_WEB_DEFAULT_IDLE_TIME 300
#endif
#ifndef ATP_WEB_SESSIONID_LEN
#define ATP_WEB_SESSIONID_LEN   128
#endif
#ifndef ATP_WEB_DEFAULT_STATUS_FRESHEN_TIME
#define ATP_WEB_DEFAULT_STATUS_FRESHEN_TIME  10000
#endif
#ifndef ATP_WEB_LOGIN_PAGE_PATH
#define ATP_WEB_LOGIN_PAGE_PATH   "/"
#endif
#ifndef ATP_WEB_REPLACE_PAGE_PATH
#define ATP_WEB_REPLACE_PAGE_PATH  "/html/relocation.html"
#endif
#ifndef WANPPP_PASSWORD_RULE_LIST
#define WANPPP_PASSWORD_RULE_LIST  ""
#endif
#ifndef WANPPP_PASSWORD_SPECIAL_CHAR
#define WANPPP_PASSWORD_SPECIAL_CHAR ""
#endif
#ifndef ATP_WAN_PPPOA_WITH_MAC
#define ATP_WAN_PPPOA_WITH_MAC "FALSE"
#endif
#ifndef ETH_LAN_PORT_NUM
#define ETH_LAN_PORT_NUM 1
#endif
#ifndef IPCHECK_MAX_MAC_IN_DB_NUM
#define IPCHECK_MAX_MAC_IN_DB_NUM 32
#endif
#ifndef ATP_URL_MAX_LEN
#define ATP_URL_MAX_LEN 255
#endif
#ifndef ATP_IGMP_MAX_GROUP_NUMBER
#define ATP_IGMP_MAX_GROUP_NUMBER 32
#endif
#ifndef ATP_IGMP_MAX_MSF
#define ATP_IGMP_MAX_MSF 10
#endif
#ifndef SUPPORT_ATP_IGMP_LOGCLI
#define SUPPORT_ATP_IGMP_LOGCLI  SUPPORT_ATP_IGMP
#endif
#ifndef SUPPORT_ATP_IGMP_V3
#define SUPPORT_ATP_IGMP_V3  SUPPORT_ATP_IGMP
#endif
#ifndef ATP_FTP_REDIRECT_PORT
#define ATP_FTP_REDIRECT_PORT 0
#endif
#ifndef ATP_HTTPS_REDIRECT_PORT
#define ATP_HTTPS_REDIRECT_PORT  0
#endif
#ifndef ATP_SSH_REDIRECT_PORT
#define ATP_SSH_REDIRECT_PORT 0
#endif
#ifndef ATP_TELNET_REDIRECT_PORT
#define ATP_TELNET_REDIRECT_PORT 0
#endif
#ifndef ATP_SNMP_REDIRECT_PORT
#define ATP_SNMP_REDIRECT_PORT 0
#endif
#ifndef ATP_WEB_REDIRECT_PORT
#define ATP_WEB_REDIRECT_PORT 0
#endif
#ifndef VOICE_DIGITMAP_MAX_LEN
#define VOICE_DIGITMAP_MAX_LEN 1024
#endif
#ifndef ATP_CFM_SHARE_MEM_SIZE_D
#ifdef  SUPPORT_ATP_SMARTHOME
#define ATP_CFM_SHARE_MEM_SIZE_D   524288
#else
#define ATP_CFM_SHARE_MEM_SIZE_D   262144
#endif
#endif
#ifndef ATP_CFM_MAX_OBJ_PER_MSG_D
#define ATP_CFM_MAX_OBJ_PER_MSG_D   64
#endif
#ifndef ATP_CFM_TEMP_STRFILE_LENGTH_D
#define ATP_CFM_TEMP_STRFILE_LENGTH_D 5
#endif
#ifndef HGW_PRODUCTCLASS
#ifdef SUPPORT_ATP_EUAP
#define  HGW_PRODUCTCLASS   "ATP"
#else
#define HGW_PRODUCTCLASS "Honor"
#endif
#endif

#ifndef HGW_PRODUCTTYPE
#define  HGW_PRODUCTTYPE   "HGW"
#endif

#ifndef BOOTLOADER_VENDOR
#define BOOTLOADER_VENDOR  "REALTEK"
#endif

#ifndef HGW_RELEASE_ENGINEERING
#define HGW_RELEASE_ENGINEERING "MBB"
#endif

#ifndef HGW_PRODUCTNAME
#define HGW_PRODUCTNAME "MBB"
#endif

#ifndef HGW_SOFTVERSION
#define HGW_SOFTVERSION "MBB"
#endif

#endif /* __ATPCONFIG_COMMON_H__ */
