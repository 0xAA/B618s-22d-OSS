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

#ifndef __ATP_UTIL_H__
#define __ATP_UTIL_H__

/********************** Include Files ***************************************/

// Includes.
/*atp inc*/

#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/if_link.h>
#include "atptypes.h"
#include "msgapi.h"
#include "atpconfig.h"
#include "msgapi.h"
#include "caltime.h"
//#include "securec.h"
#ifdef ATP_DMALLOC
#include "dmalloc.h"
#endif

/********************** macro ***********************************************/
/*String Safe Length*/
#define ATP_STRING_LEN_512                  516
#define ATP_STRING_LEN_128                  132
#define ATP_STRING_LEN_256                  260
#define ATP_STRING_LEN_64                   68
#define ATP_STRING_LEN_32                   36

/*String Actual Length*/
#define ATP_ACTUAL_LEN_512                  512
#define ATP_ACTUAL_LEN_256                  256
#define ATP_ACTUAL_LEN_128                  128
#define ATP_ACTUAL_LEN_64                   64
#define ATP_ACTUAL_LEN_32                   32

/*Cli User Instande Id*/
#define ATP_CLI_ADMIN_INSTID                1
#define ATP_CLI_ADMIN_TEL_INSTID         2
#define ATP_CLI_USER_INSTID                 3

/*System Length*/
#define ATP_SYS_MEDIUM_LEN                  240
#define ATP_SYS_DOMAIN_LEN                  64
#define ATP_SYS_CMD_LEN                     512

/*Read Buf Length*/
#define ATP_SYS_READ_BUF_SIZE               128

/*IP Addr LEN*/
#define ATP_SYS_IPADDR_LEN   16

/*����Э���ַ���*/
#define ATP_PROTO_TCP_STR                   "tcp"
#define ATP_PROTO_UDP_STR                   "udp"
#define ATP_PROTO_ICMP_STR                  "icmp"
#define ATP_PROTO_ICMPV6_STR                "icmpv6"

/*Mac Addr LEN*/
#define ATP_UTIL_MAC_BYTE_CNT_0             0
#define ATP_UTIL_MAC_BYTE_CNT_1             1
#define ATP_UTIL_MAC_BYTE_CNT_2             2
#define ATP_UTIL_MAC_BYTE_CNT_3             3
#define ATP_UTIL_MAC_BYTE_CNT_4             4
#define ATP_UTIL_MAC_BYTE_CNT_5             5

#define ATP_UTIL_MAC_BYTE                    6
#define ATP_UTIL_MAC_LENGTH                  18

/*TIME*/
#define ATP_TIME_US_PER_SECOND              (1000000L)
#define ATP_TIME_NS_PER_USECOND             (1000)
#define ATP_TIME_MS_PER_SECOND              (1000)
#define ATP_STAT_BYTE_PER_KBYTE             (1024)

#define ATP_TIME_MONTH_START_OF_YEAR        (1)
#define ATP_TIME_MONTH_OF_YEAR              (12)
#define ATP_TIME_DAY_OF_A_WEEK              (7)
#define ATP_TIME_MAX_WEEK_OF_MONTH          (5)
#define ATP_TIME_DAY_OF_WEEK_SUNDAY         (0)
#define ATP_TIME_DAY_OF_WEEK_SATURDAY       (6)
#define ATP_TIME_HOUR_OF_DAY                (24)                                                  /* һ���Сʱ�� */
#define ATP_TIME_SECOND_OF_MIN              (60)                                                  /* ÿ���ӵ����� */
#define ATP_TIME_SECOND_OF_HOUR             (60 * (ATP_TIME_SECOND_OF_MIN))                       /* ÿСʱ������ */
#define ATP_TIME_SECOND_OF_DAY              ((ATP_TIME_HOUR_OF_DAY) * (ATP_TIME_SECOND_OF_HOUR))  /* һ������� */
#define ATP_TIME_NEGATIVE_SECOND_OF_DAY     (0 - (ATP_TIME_SECOND_OF_DAY))

#define ATP_UINT32_MAX                      (~0U)

#define ATP_TIME_MS_PER_SECOND              (1000)

#define ATP_TIME_MONTH_START_OF_YEAR        (1)
#define ATP_TIME_MONTH_OF_YEAR              (12)
#define ATP_TIME_DAY_OF_A_WEEK              (7)
#define ATP_TIME_MAX_WEEK_OF_MONTH          (5)
#define ATP_TIME_DAY_OF_WEEK_SUNDAY         (0)
#define ATP_TIME_DAY_OF_WEEK_SATURDAY       (6)
#define ATP_TIME_HOUR_OF_DAY                (24)                                                  /* һ���Сʱ�� */
#define ATP_TIME_SECOND_OF_MIN              (60)                                                  /* ÿ���ӵ����� */
#define ATP_TIME_SECOND_OF_HOUR             (60 * (ATP_TIME_SECOND_OF_MIN))                       /* ÿСʱ������ */
#define ATP_TIME_SECOND_OF_DAY              ((ATP_TIME_HOUR_OF_DAY) * (ATP_TIME_SECOND_OF_HOUR))  /* һ������� */
#define ATP_TIME_NEGATIVE_SECOND_OF_DAY     (0 - (ATP_TIME_SECOND_OF_DAY))

/*NFMARK*/
/* ���ֵ��������չ�ں˵�setsockopt�ı�ŵģ����Ҫ�����ں��е� asm/socket.h �еı仯 */
/*SO_NFMARK��21�ں��õģ�30�ں�ֻ��SO_MARK*/
#ifdef SO_MARK
#define SO_NFMARK       SO_MARK
#else
#define SO_NFMARK       66
#endif /* SO_MARK */
/* Ŀǰ������ʱȫ������ͬһ����ǣ������������Ҫϸ�ֳ�SIP,RTP�ȣ���ô�������޸ĸú�Ϳ����� */
#define NFMARK_WEB_CAPTURE  0x9
#define NFMARK_SIP      0xa
#define NFMARK_SIPALG   0xa
#define NFMARK_RTP      0xb
#define NFMARK_RTCP     0xc
/* TR069 */
#define NFMARK_TR069_CONTRACK   0xd
#define NFMARK_GRE      0xe    /* Hybrid Bonding GRE���Ʊ��� */
/* DNS */
#define NFMARK_DNS      0xB7
#define NFMARK_DNS_CONTRACK 0xBA

#define QOSTELMEX_TOS_VOIP_CTL 0xB8

/*for HG526V3 USB RECOVER configfile*/
#define USB_CONF_PATH "e8_Config_backup"
#define USB_CONF_FILE "ctce8.cfg"

/* Host Info Macro */
#define ATP_UTIL_BR_FDB_MAX   128
#define ATP_UTIL_MAC_LEN   18
#define ATP_UTIL_INTERFACE_LEN  16
#define ATP_UTIL_ISLOCAL_LEN    8
#define ATP_UTIL_ONLINEUPGRADE_READ_LEN (5)

#define STRNCPY(DstStr,SrcStr) \
    do \
    {\
        strncpy_s(DstStr,sizeof(DstStr),SrcStr,sizeof(DstStr) - 1);\
        DstStr[sizeof(DstStr) - 1] = 0; \
    }while(0)

#define SNPRINTF(DstStr,format,arg...) \
    do \
    { \
        snprintf_s(DstStr,sizeof(DstStr),sizeof(DstStr),format,## arg); \
    }while(0)


/*Interface Info*/
//!\brief �ӿ���Ϣ�ṹ
/*!
 *  ��¼�ӿھ��ϴθ�λ����ա����͵ķ��������ֽ��������������
 */
typedef struct
{
    unsigned long ulBytesReceived;        /* �ϴθ�λ�󣬴˽ӿڽ��յ����ֽ��� */
    unsigned long ulPacketsReceived;      /* �ϴθ�λ�󣬴˽ӿڽ��յķ������� */
    unsigned long ulPacketsReceivedErr;   /* �ϴθ�λ�󣬴˽ӿڽ��յĴ���ķ�������*/
    unsigned long ulPacketsReceivedDrops; /* �ϴθ�λ�󣬴˽ӿڽ��յĶ����ķ�������*/
    unsigned long ulBytesSent;            /* �ϴθ�λ�󣬴˽ӿڷ��͵����ֽ��� */
    unsigned long ulPacketsSent;          /* �ϴθ�λ�󣬴˽ӿڷ��͵ķ������� */
    unsigned long ulPacketsSentErr;       /* �ϴθ�λ�󣬴˽ӿڷ��͵Ĵ���������� */
    unsigned long ulPacketsSentDrops;     /* �ϴθ�λ�󣬴˽ӿڷ��͵Ķ����������� */
}ATP_UTIL_INTERFACE_STAT_ST;

/* Host Info which got by brctl showmacs */
typedef struct
{
    VOS_UINT8  portNum;
    VOS_CHAR    macAddr[ATP_UTIL_MAC_LEN];
    VOS_CHAR    intfaceName[ATP_UTIL_INTERFACE_LEN];
    VOS_CHAR    isLocal[ATP_UTIL_ISLOCAL_LEN];
} ATP_UTIL_BR_FDB_INFO;

#define ATP_XTM_INTERFACE_FILE "/var/wan/xtm_interface"

#define WAN_TO_INTERFACE "/var/wan/wan2interface"
#define WAN_CMDWORD_LEN 256
#define WAN_STATUS_OK 1
#define WAN_STATUS_NOK 0

typedef enum tagWAN_KEYWORD_EN
{
    ATP_WAN_NONE=0,
    ATP_WAN_PPPOE,
    ATP_WAN_DHCP,
    ATP_WAN_UMTS,
}WAN_KEYWORD_EN;

typedef enum tagWAN_LEVEL_EN
{
    ATP_WAN_LEVEL_PHY=1,
    ATP_WAN_LEVEL_LINK,
    ATP_WAN_LEVEL_IP,
}WAN_LEVEL_EN;

typedef enum
{
    ATP_XDSL_MODE_ATM,
    ATP_XDSL_MODE_PTM,
    ATP_XDSL_MODE_UNKNOWN,
}ATP_XTM_MODE_EN;

typedef enum
{
    ATP_TYPE_PATH_USB=0,
    ATP_TYPE_PATH_HTML,
    ATP_TYPE_PATH_WEBROOT,
    ATP_TYPE_PATH_APPHTML,
    ATP_TYPE_PATH_WEBCOMMON,
    ATP_TYPE_PATH_WEBAPI,
    ATP_TYPE_PATH_WEBCOMMONCONFIG,
    ATP_TYPE_PATH_CRASH,
    ATP_TYPE_PATH_USERDATA,
    ATP_TYPE_PATH_APPCONFIG,
    ATP_TYPE_PATH_CURCFG,
    ATP_TYPE_PATH_MLOG,
    ATP_TYPE_PATH_END,

}ATP_PATH_TYPE;

#define ATP_UTIL_USleep(us)                     \
    do {                                        \
        struct timespec req = {0};              \
        req.tv_sec = ((int)((us)/1000000L));    \
        req.tv_nsec = ((us) % 1000000L) * 1000; \
        while(nanosleep(&req,&req)==-1) {       \
            continue;                           \
        }                                       \
    } while (0)

#define ATP_UTIL_MSleep(ms) ATP_UTIL_USleep((ms) * 1000)

#define ATP_UTIL_Sleep(s) sleep(s)

VOS_VOID ATP_UTIL_SendDhcp6cRelease(const char* dirname);

/*һ.Valid Function*/
/*1.IPv6 Valid*/
/*!
  \brief ��ȡIpv6 ������·��ַ
  \param[in]  pszIfc: �ӿ���
  \param[out]  pszAddr: ��ȡ���ı�����·��ַ
  \return �Ƿ��ȡ�ɹ�
  \retval VOS_TRUE  ��ȡ�ɹ�
  \retval VOS_FALSE ��ȡʧ��
*/
VOS_BOOL ATP_UTIL_GetIpv6LinkAddress(const VOS_CHAR* pszIfc, VOS_CHAR* pszAddr, VOS_UINT32 ulSize);

/*��.common call functions*/
/*1.convert & get & set Function*/
/*!
  \brief  ���ַ���ת�����ܱ�Shell ʶ����ַ���
  \param[in]  *pszStr: ��ת���ַ���
  \param[out]  *pszConvertedStr: ת������ַ���
  \return �Ƿ�ת���ɹ�
  \retval VOS_TRUE  ת���ɹ�
  \retval VOS_FALSE ת��ʧ��
*/
VOS_BOOL ATP_UTIL_ConvertStrToShellStr(VOS_CHAR *pszStr, VOS_CHAR *pszConvertedStr);

/*2.ExecCmd Function*/
/*!
  \brief ִ��SHELL������ȴ�20s
  \param[in]  *pcCommand: SHELL����
  \param[in]  ucSecond: �ȴ���ʱ�䣬��λΪ��
  \return  0  ��ʾ����ִ�гɹ�
  \return -1 ��ʾ����ִ��ʧ��
*/
VOS_INT ATP_UTIL_ExecCmd_ByTime(VOS_CHAR *pcCommand, VOS_UINT32 ucSecond);

/*!
  \brief  ִ�������������sh����, ���������滻system����, ���ȴ�40s,��ʱ�ӽ�killִ�н���,����-1
           ������ں�ִ̨��,����ĩβ��&
  \param[in]  *pcCommand: ��ִ������
  \return �����Ƿ�ִ�гɹ�
  \retval lStatus ����ִ��״̬
  \retval 0  �����Ľ���pid��Ϊ0
  \retval -1 ��ʾ����ִ��ʧ��(e.g.  fork() failed , pcCommand is null, timout)
*/
VOS_INT  ATP_UTIL_ExecCmdNoHang(VOS_CHAR *pcCommand);
/*!
  \brief ���������ȡ�����̺�
  \param[in]  pcCommand: ����ȡ���̺ŵ�����
  \return�Ƿ���ҳɹ�
  \retval pPid  ���ҵ��Ľ��̺� ������0
  \retval 0  ��ʾ����ʧ��
*/
VOS_INT ATP_UTIL_GetPid(const VOS_CHAR * pcCommand);
/*!
  \brief  ���ݽ������õ����̺ţ�����ж��ƥ������г�����ƥ��Ľ���ID
  \param[in]  pszPidName: ������
  \return ָ����̺��б��ָ��
  \retval pPidList  ��ȡ���Ľ��̺��б�ָ��
  \retval VOS_NULL ��ȡ���̺��б�ΪNULL
*/
VOS_INT32 *ATP_UTIL_FindPidByName( VOS_CHAR* pszPidName);


VOS_INT32 ATP_UTIL_FindKernelPidByName( VOS_CHAR* pszPidName);

/* ע��ATP_Exec��ATP_ExecDebug��ATP_UTIL_ExecCmdNoHang�Ȳ�����ȫ�滻system��������ʹ��ʱ��֤������֤
   ���������ͨ���ʱ����Ч���� * ? �ȣ�ͬʱֻ���õ������� */
#define ATP_Exec(cmd)                       ATP_UTIL_ExecCmdNoHang (cmd) //����ӡ��������Ϣ
#define ATP_ExecDebug(cmd)                  ATP_UTIL_ExecCmdNoHang (cmd) //��ӡ��������Ϣ1->0

/*3.InterfaceName Function*/
/*!
  \brief ���ݽӿ�����ȡIp��ַ��ֻ���Ipv4
  \param[in]  pszIfName: �ӿ���
  \param[out]  pstAddr: ��ȡ����sockaddr_in Ip��ַ
  \return �Ƿ��ȡ��ַ�ɹ�
  \retval VOS_OK   ��ȡ��ַ�ɹ�
  \retval VOS_NOK ��ȡ��ַʧ��
*/
VOS_UINT32 ATP_UTIL_GetIpByName(const VOS_CHAR* pszIfName, struct sockaddr_in* pstAddr);

VOS_UINT32 ATP_UTIL_GetMaskByName(const VOS_CHAR* pszIfName, struct sockaddr_in* pstAddr);

/*4. 3GUsbStickNode*/

/*5. Common*/
/*!
  \brief ���ַ����е�'\0'ȥ��
  \param[in]  *pcBuf: ��ȥ��'\0'���ַ���
  \return �Ƿ�ȥ���ɹ�
  \retval VOS_TRUE  ȥ���ɹ�
  \retval VOS_FALSE ȥ��ʧ��
*/
VOS_BOOL ATP_UTIL_RmDelimitor( VOS_CHAR *pcBuf);


/*7. Qos*/

/*11. Upg*/

/*12. TTL*/


/*13. Match Type*/
typedef enum tagATP_UTIL_CSTRMATCH_PATTERN {
    ATP_UTIL_STRMATCH_EXACT = 0,
    ATP_UTIL_STRMATCH_PREFIX,
    ATP_UTIL_STRMATCH_SUFFIX,
    ATP_UTIL_STRMATCH_SUBSTRING,
    ATP_UTIL_STRMATCH_ERROR
} ATP_UTIL_CSTRMATCH_PATTERN;
/*!
  \brief �����ַ�����ȡ��Ӧ��ATP_UTIL_CSTRMATCH_PATTERN����
  \param[in]  str: ����ѯ�ַ���
  \return ����ƥ�䵽������
  \retva type  �ҵ��Ŀ�ƥ������
  \retval ATP_UTIL_STRMATCH_EXACT strΪ��ʱ
  \retva ATP_UTIL_STRMATCH_ERROR δ�ҵ���ƥ�������
*/
ATP_UTIL_CSTRMATCH_PATTERN ATP_UTIL_GetMatchType(const VOS_CHAR * str);

/*15.Dynamic Launched Application Update*/
/*!
  \brief ���¶�̬Ӧ�ó����б�
  \param[in]  *pcAppName: ����µ�Ӧ�ó�����
  \param[in]  bStop: �Ƿ�ֹͣ����
  \return ���ط�����Ϣ������
  \retval VOS_OK ������Ϣ���ͳɹ�
  \retval VOS_NOK pcAppNameΪNULL
  \retval ATP_MSG_RET_PARA_ERR  ��Ϣ��������
  \retval ATP_MSG_RET_NOT_INITED δ��ʼ��
  \retval ATP_MSG_RET_OVERFLOW  ��Ϣ���
  \retval ATP_MSG_RET_PEER_DEAD  socket��peer�ر�
  \retval ATP_MSG_RET_INTERNAL_ERR  �ڲ�����
*/
VOS_UINT32 ATP_UTIL_UpdateDynAppListenFd(const VOS_CHAR *pcAppName, VOS_BOOL bStop);

/*16.InterfaceInfo Function*/
/*!
  \brief  ��ȡ�ӿ�pszIfcName��ͳ����Ϣ
  \param[in]  *pszIfcName: ����ȡͳ����Ϣ�Ľӿ���
  \param[out]  *pstState: �ӿ�ͳ����Ϣ
  \return ��
  \retval ��
*/
VOS_VOID ATP_UTIL_GetIfcStatInfo(VOS_CHAR *pszIfcName, ATP_UTIL_INTERFACE_STAT_ST *pstState);

#ifdef ATP_DEBUG
#define ATP_UTIL_DEBUG(format, args...)\
{\
    printf("FILE: %s FUNC: %s LINE: %d: ", __FILE__,__func__, __LINE__);\
    printf(format, ##args);\
}
#else
#define ATP_UTIL_DEBUG(x...)
#endif
/*!
  \brief ���ַ���str�и��ݴ�ƥ������typeƥ���Ƿ����*pattern
  \param[in]  str: ����֤�ַ���
  \param[in]  pattern: ����ƥ����ַ���
  \param[in]  type: ��ƥ������
  \return �����Ƿ�ƥ��ɹ���־
  \retval VOS_TRUE ƥ��ɹ�
  \retval VOS_FALSE ƥ��ʧ��
*/
VOS_BOOL ATP_UTIL_CstrMatch(const VOS_CHAR * str, const VOS_CHAR * pattern, ATP_UTIL_CSTRMATCH_PATTERN type);


/*!
  \brief ����LAN�ӿ���(eth0.4)��ȡbr
  \param[in]  pszLan:
  \param[in]  pszBrName:
  \param[in]  ulLen:
  \return
  \retval ATP_E_ERR_CFM_SHM_NOT_ATTACH ��ʼ�������ڴ�ʧ��
*/
VOS_UINT32 ATP_UTIL_GetBrByLanInterface(const VOS_CHAR* pszLan, VOS_CHAR* pszBrName, VOS_UINT32 ulLen);

/*!
  \brief ͨ��mac ��ַ��ȡ�ӿ���
  \param[in]  psMacaddr: ����ȡ�ӿڵ�MAC ��ַ
  \param[out]  psInterfaceName: ��ȡ���ýӿ���
  \param[in]  ulInfNameLen: �ӿ�������
  \return ��ȡ�ӿ����Ƿ�ɹ�
  \retval VOS_OK  ��ȡ�ӿ����ɹ�
  \retval VOS_NOK  ��ȡ�ӿ���ʧ��
*/
VOS_UINT32 ATP_UTIL_GetInterfaceNameByMacAddr(const VOS_CHAR * psMacaddr, VOS_CHAR* psInterfaceName, VOS_UINT32 ulInfNameLen);

/*!
  \brief ��ȡ����bridge�Ľӿ�����
  \param[in]  pcNameBuf: ��Žӿ����Ļ�����
  \param[in]  ulBufLen: ��Žӿ����Ļ���������
  \return �ӿڸ���
*/
VOS_UINT32 ATP_UTIL_GetBridgeAllNames(VOS_CHAR *pcNameBuf, VOS_UINT32 ulBufLen);

VOS_UINT32 ATP_UTIL_GetBrFdbInfoByMac(const VOS_CHAR* psMacaddr, ATP_UTIL_BR_FDB_INFO * pstFdbInfo);
VOS_UINT32 ATP_UTIL_GetBrFdbInfoByMacSpecBr(const VOS_CHAR* psMacaddr, ATP_UTIL_BR_FDB_INFO * pstFdbInfo, char * pszbrname);


VOS_UINT32 ATP_UTIL_GetBrFdbInfoByInterface(const VOS_CHAR* psInterfaceName, ATP_UTIL_BR_FDB_INFO * pstHostInfo, VOS_UINT32 ulNum);

VOS_BOOL ATP_UTIL_ValidatePort(VOS_UINT32 ulPort);

VOS_UINT32 ATP_GetWan2InterfaceName(WAN_KEYWORD_EN ulWanKeyWord,VOS_CHAR *pszInterface, VOS_UINT32 ulIntfLen);

VOS_UINT32 ATP_GetWan2InterfaceStatus(WAN_LEVEL_EN ulConnLevel,WAN_KEYWORD_EN ulWanKeyWord,VOS_UINT32 *puzStatus);
VOS_VOID ATP_UTIL_TriggerDemand(VOS_VOID);

VOS_UINT32 ATP_UTIL_CheckTimeValid(ATP_UTIL_PERIODICTIMEINT_ST astPerTimeInfo);
VOS_UINT32 ATP_UTIL_GetDifTime(const VOS_CHAR *pstPrdTime, const VOS_CHAR *pstCurTime,
                                                VOS_UINT32 *pstDifVal, VOS_UINT32 *pstPrdicFlag);
VOS_VOID ATP_UTIL_GetDelayTime(VOS_UINT32 ulDetaTime, VOS_UINT32 ulInformInterval, VOS_UINT32 ulPrdFlag, VOS_UINT32 *pulDelayTime);
VOS_UINT32 ATP_UTIL_UCTTimeFormatCheck(const VOS_CHAR *pstTime, ATP_UTIL_PERIODICTIMEINT_ST *pstTimeInt);

VOS_UINT32 ATP_UTIL_GetXdslActiveMode(VOS_UINT32 *pulActiveMode);
VOS_VOID ATP_UTIL_GetWanMacAddress(const VOS_CHAR* pszNasIfc, VOS_CHAR* pszMacAddress);

VOS_UINT32 ATP_IS_ValidDomain(VOS_CHAR *acDomainName, VOS_UINT32 ulMaxLength);

VOS_BOOL    ATP_UTIL_JudgeIsLittleEnd(VOS_VOID);
VOS_UINT64 ATP_UTIL_Htonll(const VOS_UINT64 ullHostLonglong);
VOS_UINT64 ATP_UTIL_Ntohll(const VOS_UINT64 ullNetLonglong);
VOS_BOOL ATP_UTIL_ValidateLength(VOS_CHAR *pszStr, VOS_UINT ulMax);
VOS_BOOL ATP_UTIL_ValidStr(const VOS_CHAR *pszStr);

VOS_BOOL ATP_UTIL_ValidateNumber(VOS_CHAR* pcNum);

void ATP_UTIL_get_dev_stats(const char * pszDev, struct rtnl_link_stats * pstStats);

/*!
  \brief ��ȡ����stat���ݵĲ�ֵ,���Ƿ�ת,��Ҫ���ڶ�ʱ���ڻ�ȡ�������ݱȽϲ�ֵ
  \param[in]  VOS_UINT32 ulOldValue:��ֵ
  \param[in]  VOS_UINT32 ulNewValue:��ֵ
  \return ��ֵ
*/
VOS_UINT32 ATP_UTIL_GetStatDiffValue(VOS_UINT32 ulOldValue, VOS_UINT32 ulNewValue);


/*!
  \brief  get system current time
  \return
  \retval str format hh:mm:ss
*/
const VOS_CHAR* ATP_UTIL_GetCurrTime();

/*!
  \brief  get system current time
  \return
  \retval str format Y-m-dThh:mm:ss
*/
const VOS_CHAR* ATP_UTIL_GetCurrUTCTime();
/*!
  \brief  get system current time
  \return
  \retval str format %a, %d %b %Y %H:%M:%S GMT
*/
const VOS_CHAR* ATP_UTIL_GetCurrGMTTime();
const VOS_CHAR* ATP_UTIL_GetCurrTimeStamp();
const VOS_CHAR* ATP_UTIL_GetCurrUTCTimeStamp();

VOS_INT32 ATP_UTIL_CheckDatacardExsit(VOS_VOID);

VOS_UINT32 ATP_UTIL_Delete_Sub_Str(const VOS_CHAR *str, const VOS_CHAR *sub_str, VOS_CHAR *result_str);

VOS_VOID ATP_UTIL_GetReleaseDate(VOS_CHAR *pcDate, VOS_UINT32 ulDateLen);
VOS_UINT32 ATP_UTIL_GetXdslCoVenderStr(VOS_CHAR *pcVenderStr,VOS_UINT32 ulLen);
/*!
  \brief ����pid �жϽ���״̬����
  \param[in]  iPid: ���жϽ���pid
  \return �����Ƿ����
  \retval VOS_OK  �����Դ���
  \retval VOS_NOK ���̲�����
*/
VOS_UINT32 ATP_UTIL_GetProcessStatus(VOS_INT32 iPid);

/*!
  \brief gen random buffer
  \param[in]  pcBuffer:
  \param[in]  ulLen:
  \return
  \retval
*/
VOS_UINT32 ATP_UTIL_GenRandomBuffer(VOS_UINT8 * pucBuffer, VOS_UINT32 ulLen);

/*!
  \brief  gen Random str
  \param[in]  *pcStrBuffer:
  \param[in]  ulLen:
  \return
  \retval
*/
VOS_UINT32 ATP_UTIL_GenRandomStr(VOS_CHAR *pcStrBuffer, VOS_UINT32 ulLen);

/*!
  \brief gen random integer
  \param[in]  *pulRandomNum:
  \return
  \retval
*/
VOS_UINT32 ATP_UTIL_GenRandomInteger();

/*!
  \brief get ms seconds after system reboot
  \param[in]  null
  \return
  \retval ms seconds after system reboot
*/
VOS_UINT64 ATP_UTIL_GetMsecondAfterStart();
VOS_VOID ATP_UTIL_BindCpu(VOS_UINT32 ulId);

VOS_UINT32 ATP_UTIL_PostLua(const VOS_CHAR *pcPath, const VOS_CHAR* pcBody);

VOS_UINT32 ATP_UTIL_GetLinuxVersion();

VOS_VOID ATP_SYS_KillProcessForUpg(const VOS_CHAR *pcCfgTool);

VOS_VOID ATP_UTIL_SetHTTPRedirect(VOS_VOID);
VOS_VOID ATP_UTIL_RemoveHTTPRedirect(VOS_VOID);

VOS_UINT32 ATP_UTIL_GetBytesMacAddress(const VOS_CHAR* pszNasIfc, VOS_CHAR* pacMacAddress);
/*!
  \brief ����eType �жϵ�ǰ·���Ƿ�Ϸ�
  \param[in]  pszDir: �����·��
  \return
  \retval VOS_TRUE  ·���Ϸ�
  \retval VOS_FALSE ·�����Ϸ�
*/
VOS_BOOL ATP_UTIL_ValidatePath(const VOS_CHAR* pszDir, ATP_PATH_TYPE eType);

VOS_BOOL ATP_UTIL_IsIPv4LanAddr(const VOS_CHAR * pszIp);
VOS_BOOL ATP_UTIL_IsIPv6GlobalAddr(const VOS_CHAR * pszIp);


VOS_UINT32 ATP_UTIL_IsPathAllowAccess(const VOS_CHAR* pucRootPath, const VOS_CHAR* pucCheckPath);
VOS_UINT32 ATP_UTIL_IsPathAllowAccessEx(const VOS_CHAR* pucRootPath, const VOS_CHAR* pucCheckPath, VOS_BOOL bCheckRealPath);
VOS_UINT32 ATP_UTIL_RemoveSuffix(const VOS_CHAR *string, VOS_CHAR* pcDest, VOS_UINT32 ulLen,VOS_CHAR cMatch);


VOS_BOOL ATP_UTIL_ValidateMacAddress(VOS_CHAR *pcMacAddr);



VOS_UINT32 ATP_UTIL_GetSecureMacAddress(const VOS_CHAR *psOrigMac, VOS_CHAR *psSecMac, VOS_UINT32 ulSecMacLen);

/*
 *  HTTP Packet Format Definition
 */
typedef enum tagATP_NTWK_PROTOCOL_EN
{
    ATP_NTWK_PROTOCOL_UNKNOWN    = -1,  // Unknown protocol
    ATP_NTWK_PROTOCOL_HTTP    = 0,      // HTTP
    ATP_NTWK_PROTOCOL_HTTPS,            // HTTPS
    ATP_NTWK_PROTOCOL_FTP,              // FTP
    ATP_NTWK_PROTOCOL_TFTP,             // TFTP,

    ATP_NTWK_PROTOCOL_EXTEND
} ATP_NTWK_PROTOCOL_EN;

VOS_CHAR *ATP_UTIL_GetEscapedUri(const VOS_CHAR *pcSrcUri);

VOS_BOOL ATP_UTIL_ParseUrl(
                           const VOS_CHAR   *pcURL,     // In
                           VOS_INT32        *enProtocol,// Out
                           VOS_CHAR         **ppcIP,    // Out
                           VOS_UINT32       *pulPort,   // Out
                           VOS_CHAR         **ppcPath);

VOS_BOOL ATP_UTIL_ParseUrlEx(
                           const VOS_CHAR   *pcURL,     // In
                           VOS_INT32        *enProtocol,// Out
                           VOS_CHAR         **ppcIP,    // Out
                           VOS_UINT32       *pulPort,   // Out
                           VOS_CHAR         **ppcPath,
                           VOS_BOOL         bIgnorIpv6);  // Out

extern const VOS_CHAR **g_apcExtendProtocols;
extern const VOS_UINT32 *g_aulExtendPorts;

/*!
  \brief  do strip separator
  \param[in]  const VOS_CHAR* pstOrigString: original string
  \param[in]  VOS_CHAR cSeparator: the separator
  \param[in]  VOS_UINT32 ulOutLen: the max lenth of pstOutString
  \param[out] VOS_CHAR* pstOutString: the string without the separator
  \return
  \retval result code
*/
VOS_VOID ATP_UTIL_Strip_Separator(const VOS_CHAR* pstOrigString, VOS_CHAR cSeparator, VOS_CHAR* pstOutString, VOS_UINT32 ulOutLen);

/*!
  \brief  ģ��������MAC��ַ,����BYTE0/BYTE3/BYTE5
  \param[in]  const VOS_UINT8 pszSrcHexMac: ��Bytesλ�洢��MAC��ַ����Ҫ��֤�ڴ��Ѿ���ʼ����
  \param[in]  VOS_CHAR *pszSrcMac: ��:�ָ��MAC�ַ���
  \param[in]  VOS_UINT32 ulDstLen: �������������󳤶�
  \param[out] VOS_CHAR *pszDstDisguiseMac: ģ���������MAC��ַ
  \return
  \retval result code
*/
VOS_VOID ATP_UTIL_Disguise_MacAddress(const VOS_UINT8 *pszSrcHexMac, const VOS_CHAR *pszSrcMac, VOS_CHAR *pszDstDisguiseMac, VOS_UINT32 ulDstLen);


VOS_UINT32 ATP_UTIL_FindModuleAndFuncByUri(const VOS_CHAR* pcUri, VOS_CHAR *pcMod,
                                            VOS_UINT32 ulModLen, VOS_CHAR *pcFunc, VOS_UINT32 ulFunLen);

#define ATP_HILINK_TRACE(format, args...)  {printf("\r\n[HILINK_TRACE %s %s:%d]: ", ATP_UTIL_GetCurTimeStamp(), __FILE__, __LINE__);printf(format, ##args);printf("\n");}


static inline void* atp_realloc_internal(void *src, size_t src_size, size_t alloc_size,
    const char *filename, const char *funcname, unsigned int line)
{
    void *dest = NULL;

#ifdef ATP_PCLINT
    filename = filename;
    funcname = funcname;
    line = line;
#endif

    if (alloc_size <= 0)
    {
        ATP_FREE(src);
        return NULL;
    }

#ifdef SUPPORT_ATP_ATP_DEBUG_IAMGE
    if (alloc_size > ATP_MAX_MALLOC)
    {
        printf("too large realloc, len=%d, file=%s, func=%s, line=%d, pid=%d!\n", alloc_size, filename, funcname, line, getpid());
        ATP_UTIL_FilePrintf(ATP_MEM_LEAK_LOG, 1, "too large realloc, len=%d, file=%s, func=%s, line=%d, pid=%d!\n",
            alloc_size, filename, funcname, line, getpid());
    }
#endif

    dest = malloc(alloc_size);
    if (NULL == src)
    {
        if (NULL != dest)
        {
            memset_s(dest, alloc_size, 0, alloc_size);
        }

        return dest;
    }

    if (NULL == dest)
    {
        ATP_FREE(src);
        src = NULL;
        return NULL;
    }

    memset_s(dest, alloc_size, 0, alloc_size);

    if (alloc_size <= src_size)
    {
        memcpy_s(dest, alloc_size, src, alloc_size);
    }
    else
    {
        memcpy_s(dest, alloc_size, src, src_size);
    }

    ATP_FREE(src);
    src = NULL;
    return dest;
}

#define atp_realloc(src, src_size, alloc_size) atp_realloc_internal((src), (src_size), (alloc_size), __FILE__, __FUNCTION__,__LINE__)

#define ATP_UNLINK(file)        unlink(file)


VOS_VOID ATP_UTIL_CopyFile(const VOS_CHAR *psSrcFile, const VOS_CHAR *psDestFile);

#define GET_TIME_OUT(new, old) (((VOS_UINT64)((new).tv_sec - (old).tv_sec)) * 1000 + (VOS_UINT64)(new).tv_usec / 1000 - (VOS_UINT64)(old).tv_usec / 1000)

#endif //__ATP_UTIL_H__
