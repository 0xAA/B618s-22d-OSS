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

#ifndef __ATP_SNTP_MSGTYPES_H__
#define __ATP_SNTP_MSGTYPES_H__


#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>

//#include "ntwkcmsapi.h"

#define ATP_CBBID_SNTP_NAME "sntp"

#define ATP_SNTP_PATH                       "/var/sntp"
#define ATP_SNTP_PID_FILE                   "/var/sntp/pidfile"
#define ATP_SNTP_CONFIG_FILE                "/var/sntp/sntp.conf"
#define ATP_SNTP_WANTYPE_FILE               "/var/sntp/sntpwantype"
#define ATP_SNTP_SYNCSERVER_FILE           "/var/sntp/SyncServer"
#define NTP_DEFAULT_CREDENTIAL_FILE         "/var/defaultCredentital"
#define ATP_SNTP_OFFSET_FILE                        "/var/sntp/offset"           



//TR181 specific CMO marco, the data model same as tr098, but with subtle different names
#ifdef SUPPORT_ATP_TR181
// Device.Time
#define CMO_TIME_LOCALTIMEZONENAME      CMO_TIME_LOCALTIMEZONE
#endif

#define ATP_SNTP_SYNC_FAILED_DEFAULT_INTERVAL  (5)
#define ATP_SNTP_SYNC_SUCCESS_DEFAULT_INTERVAL  (24 * 60 * 60)


/* �ļ����ùؼ����б� */
#define SNTP_CONF_TIME_ZONE                     "TimeZone"
#define SNTP_CONF_SERVER                        "NTPServer"
#define SNTP_CONF_FAILED_INTERVAL               "NTPFailUpdate"
#define SNTP_CONF_SUCCED_INTERVAL               "NTPSuccessUpdate"
#define SNTP_CONF_DEBUG                             "debug"

/*����SNTP��������ö�ٱ����������������*/
typedef enum tagATP_SNTP_SERVER_EN
{ 
    SNTP_SERVER_1   = 0x00,
    SNTP_SERVER_2   = 0x01,
    SNTP_SERVER_3   = 0x02,
    SNTP_SERVER_4   = 0x03, 
    SNTP_SERVER_5   = 0x04, 
    SNTP_SERVER_NUM = 0x05,     /* ���֧��5�������� */
}ATP_SNTP_SERVER_EN;


/*sntp������������ַ�������*/
#define ATP_SNTP_SERVER_MAXLEN          (128 + 1)

/*���з��������������ַ�����󳤶�*/
#define ATP_SNTP_ALLSERVER_LEN          (SNTP_SERVER_NUM * ATP_SNTP_SERVER_MAXLEN)

#define MONTH_START_OF_YEAR                     1
#define MONTH_OF_YEAR                           12
#define DAY_OF_A_WEEK                           7
#define MAX_WEEK_OF_MONTH                       5
#define DAY_OF_WEEK_SUNDAY                      0
#define DAY_OF_WEEK_SATURDAY                    6
#define HOUR_OF_DAY                             24                                  /* һ���Сʱ�� */
#define SECOND_OF_MIN                           60                                  /* ÿ���ӵ����� */
#define SECOND_OF_HOUR                          (60 * (SECOND_OF_MIN))              /* ÿСʱ������ */
#define SECOND_OF_DAY                           ((HOUR_OF_DAY) * (SECOND_OF_HOUR))  /* һ������� */
#define NEGATIVE_SECOND_OF_DAY                  (0 - (SECOND_OF_DAY))

#define IPV4_TYPE_ENABLE 1
#define IPV6_TYPE_ENABLE 2


#define ATP_SNTP_LINE_MAX                           32


/* Ŀǰ֧���������ָ�ʽ��ʱ�����ͣ�һ����ֱ�ӵ� GMT+XX:XX ����һ�������ù����� */
#define SNTP_TIME_FORMAT_GMT                        1
//#define SNTP_TIME_FORMAT_COUNTRY                    2


#ifdef SUPPORT_ATP_SNTP_DST

/* ����ʱ��ʽ ��֧��J �� N ��ʽ */
#define ATP_SNTP_DST_FORMAT_M                       0          /* ��Ӧ�ĸ�ʽΪM��Ҳ���� ĳ���µ�ĳ�����ڵ����ڼ� */ 
//#define ATP_SNTP_DST_FORMAT_J                       1          /* ��Ӧ�ĸ�ʽΪJ,Ҳ���Ǵӵڶ����쿪ʼ���������� */
//#define ATP_SNTP_DST_FORMAT_N                       2          /* ��Ӧ�ĸ�ʽΪN��Ҳ���Ǵӵڶ����쿪ʼ������������ */

#define ATP_SNTP_DEFAULT_DST_OFFSET                 3600       /* Ĭ������ʱ����ʱ�� */


/* ����ʱ��ʽ���ڽṹ��,Ŀǰ��֧������ʱ��ʽΪM
******************************************************************************/
typedef struct
{
    /* ����ʱ��ʼ�·�(1-12), 
    ע��:Linux��gmtime, localtime�����õ���struct tm �ṹ��tm_monȡֵ0-11
    ���·ݱȽ�ʱҪע��ת��*/
    int iDstMonth;
    /* �ڼ�������, 1--5 */
    int iWeekNum; 
    /* ����ʱʱ�����죬Ϊ0-6����ʾ����-����, 0��ʾ�����죬1��ʾ����һ��.... 6��ʾ����*/
    int iWday;        
    /* ����ʱ�Ӹ������һ�뿪ʼ 0-86400(һ��) */
    unsigned int ulDstTime;  
    /* ��ʽ��־������ʱ�� M ��ʽ����J��ʽ����N��ʽ */
    unsigned int ulFlag;           
}ATP_SNTP_DST_TIME_ST;

typedef struct
{
    long lDstOffsetTime;
    time_t DstStartSeconds;
    time_t DstEndSeconds;
    ATP_SNTP_DST_TIME_ST stDstStart;
    ATP_SNTP_DST_TIME_ST stDstEnd;    
}ATP_SNTP_DST_ST;

#endif




#endif // End of __ATP_SNTP_MSGTYPES_H__

