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


/* 文件配置关键字列表 */
#define SNTP_CONF_TIME_ZONE                     "TimeZone"
#define SNTP_CONF_SERVER                        "NTPServer"
#define SNTP_CONF_FAILED_INTERVAL               "NTPFailUpdate"
#define SNTP_CONF_SUCCED_INTERVAL               "NTPSuccessUpdate"
#define SNTP_CONF_DEBUG                             "debug"

/*定义SNTP服务器的枚举变量，用于数组访问*/
typedef enum tagATP_SNTP_SERVER_EN
{ 
    SNTP_SERVER_1   = 0x00,
    SNTP_SERVER_2   = 0x01,
    SNTP_SERVER_3   = 0x02,
    SNTP_SERVER_4   = 0x03, 
    SNTP_SERVER_5   = 0x04, 
    SNTP_SERVER_NUM = 0x05,     /* 最多支持5个服务器 */
}ATP_SNTP_SERVER_EN;


/*sntp服务器名最大字符串长度*/
#define ATP_SNTP_SERVER_MAXLEN          (128 + 1)

/*所有服务器名加起来字符串最大长度*/
#define ATP_SNTP_ALLSERVER_LEN          (SNTP_SERVER_NUM * ATP_SNTP_SERVER_MAXLEN)

#define MONTH_START_OF_YEAR                     1
#define MONTH_OF_YEAR                           12
#define DAY_OF_A_WEEK                           7
#define MAX_WEEK_OF_MONTH                       5
#define DAY_OF_WEEK_SUNDAY                      0
#define DAY_OF_WEEK_SATURDAY                    6
#define HOUR_OF_DAY                             24                                  /* 一天的小时数 */
#define SECOND_OF_MIN                           60                                  /* 每分钟的秒数 */
#define SECOND_OF_HOUR                          (60 * (SECOND_OF_MIN))              /* 每小时的秒数 */
#define SECOND_OF_DAY                           ((HOUR_OF_DAY) * (SECOND_OF_HOUR))  /* 一天的秒数 */
#define NEGATIVE_SECOND_OF_DAY                  (0 - (SECOND_OF_DAY))

#define IPV4_TYPE_ENABLE 1
#define IPV6_TYPE_ENABLE 2


#define ATP_SNTP_LINE_MAX                           32


/* 目前支持设置两种格式的时区类型，一种是直接的 GMT+XX:XX 另外一种是设置国家码 */
#define SNTP_TIME_FORMAT_GMT                        1
//#define SNTP_TIME_FORMAT_COUNTRY                    2


#ifdef SUPPORT_ATP_SNTP_DST

/* 夏令时格式 不支持J 和 N 格式 */
#define ATP_SNTP_DST_FORMAT_M                       0          /* 对应的格式为M，也就是 某个月的某个星期的星期几 */ 
//#define ATP_SNTP_DST_FORMAT_J                       1          /* 对应的格式为J,也就是从第多少天开始，包括闰年 */
//#define ATP_SNTP_DST_FORMAT_N                       2          /* 对应的格式为N，也就是从第多少天开始，不包括闰年 */

#define ATP_SNTP_DEFAULT_DST_OFFSET                 3600       /* 默认夏令时调整时间 */


/* 夏令时格式日期结构体,目前仅支持夏令时格式为M
******************************************************************************/
typedef struct
{
    /* 夏令时开始月份(1-12), 
    注意:Linux的gmtime, localtime函数得到的struct tm 结构中tm_mon取值0-11
    作月份比较时要注意转换*/
    int iDstMonth;
    /* 第几个星期, 1--5 */
    int iWeekNum; 
    /* 夏令时时间周天，为0-6，表示周天-周六, 0表示星期天，1表示星期一，.... 6表示周六*/
    int iWday;        
    /* 夏令时从该天的哪一秒开始 0-86400(一天) */
    unsigned int ulDstTime;  
    /* 格式标志，夏令时是 M 格式还是J格式还是N格式 */
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

