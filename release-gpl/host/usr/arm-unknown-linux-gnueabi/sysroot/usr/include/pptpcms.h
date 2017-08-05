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


#ifndef _PPTP_CMS_H
#define _PPTP_CMS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <signal.h>
#include <syslog.h>
#include <assert.h>
#include <ctype.h>

#include <sys/uio.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#ifndef __BIONIC__
#include <bits/socket.h>
#else
#include <linux/socket.h>
#endif

#include <net/if.h>

#include <netinet/if_ether.h>
#include <netinet/in_systm.h>

#include <linux/ip.h>
#include <linux/mroute.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <atpconfig.h>
#include "atputil.h"
#include "atptypes.h"



#define PPTP_STATUS_DISCONNECTED        "Disconnected"
#define PPTP_STATUS_CONNECTED           "Connected"

#define PPTP_PPP_STR_AUTO               "Auto"
#define PPTP_PPP_STR_MANUAL             "Manual"

#define DefaultKeepALiveTime            60
#define MinKeepAliveTime                10
#define MaxKeepAliveTime                3600

#define PPPD_PPP_CHAP_AUTH_FILE          "/var/ppp/chap-secrets"
#define PPPD_PPP_PAP_AUTH_FILE           "/var/ppp/pap-secrets"
#define PPPD_OPTION_FILE                 "/var/ppp/options.pptp"
#define PPPD_INTERFACE_FILE              "var/ppp/pppinterface"
#define PPPD_DNSSERVER_FILE              "var/ppp/dns"
#define PPTP_VPN_FLAG_FILE               "/proc/atp_proc/vpn_flag"

#define PPTP_SRC_PORT                    1723
#define PPTP_DST_PORT                    1724
#define ATP_PPTP_ADDR_LEN                18
#define PPTP_PPP_IFC_LEN                 10
#define PPTP_MAC_BYTE                    6
#define PPTP_DEFAULT_MSS                 1200
#define TCP_IP_OFFSET                      80

#define PPTP_SUB_MASK                    "255.255.255.0"


#define PPTP_ROUTE_FLAG                  3

//#define ATP_DEBUG 1

#ifdef ATP_DEBUG
#define ATP_PPTP_DEBUG(format, args...)       {printf("FILE: %s LINE: %d: ", __FILE__, __LINE__);printf(format, ##args);printf("\n");}
#else
#define ATP_PPTP_DEBUG(x...)
#endif


VOS_VOID PPTPStart();
VOS_VOID PPTPStop(const VOS_CHAR *pszWanPath);
VOS_UINT32 PPTPInit(void);
VOS_VOID ATP_PptpDelPppSrcIpRule();
VOS_VOID ATP_PptpAddPppSrcIpRule();

VOS_VOID ATP_PptpPppdStatusMonitor(const ATP_MSG_HEADER_ST *pstMsg);

VOS_VOID  ATP_PptpGetUserinfo(const ATP_MSG_HEADER_ST *pstMsg);

#if defined(__cplusplus)
extern "C" {
#endif



#if defined(__cplusplus)
}
#endif







#endif
