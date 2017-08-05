/******************************************************************************
  *         版权所有 (C), 2007-2020, 华为技术有限公司
*******************************************************************************/
/**\file        appdataapi.h
  *\brief       appdata相关的对外接口与定义，从dbapi.h中分离出来的
  *             本头文件仅用于嵌入dbapi.h使用，不要在别的文件中include
  *\author      
  *\date        2017-06-15

*****************************************************************************/
#ifndef __APPDATA_API_H__
#define __APPDATA_API_H__


/*AppData相关定义开始*/
#if DESC("Save AppData")

#define TYPE_APP_VALUE_CHANGE_SIZE              (4)
#define TYPE_APP_UPG_IN_DOWNLOAD_SIZE           (4)

#define MAX_EQUIP_BOARD_ID_SIZE                 (32)
#define MAX_EQUIP_PCBVERSION_SIZE               (64)
#define MAX_EQUIP_BOOTLOAD_VERSION_SIZE         (16)
#define MAX_EQUIP_VERSION_SIZE                  (64)
#define MAX_EQUIP_WIFI_SSID_NUM_SZIE            (4)

#define TYPE_APP_CFG_KEY_SIZE                   (32)
#define MAX_CFG_KEY_TOATAL_LEN                  (2*(TYPE_APP_CFG_KEY_SIZE + 4)) /*2个key长加上attibute属性*/

#define MAX_MAC_ADDRESS_LEN                     (6)
#define OBLI_MAC_ADDRESS_LEN                    (8)
#define EUAP_LANMAC_DEFNUM                      (1)
#define EUAP_WIFIMAC_DEFNUM                     (4)
#define EUAP_BTMAC_DEFNUM                       (1)
#define EUAP_USBMAC_DEFNUM                      (1)
#define EUAP_WANMAC_DEFNUM                      (4)

#define MAX_EQUIP_WIFI_2G_PAVARS_SIZE           (12)
#define MAX_EQUIP_WIFI_5G_PAVARS_SIZE           (72)
#define EUAP_PLC_PARAM_LEN                      (32)


/*appdata 枚举三种类型:
    ATP_APPDATA_CATEGORY_DEF:       写flash,恢复默认清除
    ATP_APPDATA_FLAG_NORESTORE_D:   写flash,恢复默认不清除
    ATP_APPDATA_FLAG_NOSAVE_D:      不写flash
*/
typedef enum tagAPPDATA_KEY_DEF_EN
{
    TYPE_APP_UPG_VALUE_CHANGE = ATP_APPDATA_CATEGORY_DEF(1), //"UPGVALUE"，0x100
    TYPE_APP_UPG_IN_DOWNLOAD,           //"UPG_DL"
    TYPE_APP_LOG_CHANGE_FLAG,           //"LOG_FLAG"
    TYPE_APP_PPP_SESSION,               //"PPP_SEEION"
    TYPE_APP_WAN_PPPSESSION,            //"WAN_PPPSEEION"
    TYPE_APP_WLAN_FLAG,                 //"WLAN_FLAG"
    TYPE_APP_WLAN_TIME_CONTROL,         //"WLAN_TM_CTL"
    TYPE_APP_WLAN_TIME,                 //"WLAN_TM"
    TYPE_APP_UGPINFO,                   //"UPG_INFO"
    TYPE_APP_PIN_INFO,                  //"PIN_INFO"
    TYPE_APP_DEVPING_INFO,              //"DEVPING_INFO"
    TYPE_APP_MIC_VALUE_CHANGED,
    TYPE_APP_SEC_KEY,
    TYPE_APP_DECT_PHONEBOOK,
    TYPE_APP_SEC_PBKDF2_SALT,
    TYPE_APP_CONFIGSYNC_FLAGS,
    TYPE_APP_DIALUP_CUSTOMER_PIN,
    TYPE_APP_ISPSYNC_IMSI,
    TYPE_APP_SOFTWARE_LASTVER,          //0x20000506 记录上一次的version
    TYPE_APP_TIMERULE_DATA,             //记录用户上网时长
    TYPE_APP_DMNODE_TOAPP,              //参数模型的数据节点放到appdata
    TYPE_APP_CFG_LOGFAIL,               //开机读取配置文件失败时记录标记，log进程起来后记录log
    TYPE_APP_WREPORT_LAST,              //每周质量报告，上周报告
    TYPE_APP_WREPORT_MON,               //每周质量报告，周一统计
    TYPE_APP_WREPORT_TUE,
    TYPE_APP_WREPORT_WED,
    TYPE_APP_WREPORT_THU,
    TYPE_APP_WREPORT_FRI,
    TYPE_APP_WREPORT_SAT,
    TYPE_APP_WREPORT_SUN,
    TYPE_APP_CWMP_CERT,
    TYPE_APP_HILINK_PROFILE,
    TYPE_APP_WEB_CA,
    TYPE_APP_WEB_PUBCERT,
    TYPE_APP_WEB_PRIKEY,
    TYPE_APP_BI_STATISTICS,
    TYPE_APP_CWMP_DOWNLOAD_FLAG,
    TYPE_LAN_FLASH_LIMIT,               //控制写lan模块写flash次数

    TYPE_FOTA_NDIS_STATE_ID = ATP_APPDATA_CATEGORY_DEF(2) ,
    TYPE_FOTA_PPP_APN_ID,               /*16 进行PPP拨号时的APN */
    TYPE_FOTA_PPP_USER_ID_ID,           /*17 进行PPP拨号所需的用户名 */
    TYPE_FOTA_PPP_PASSWORD_ID,          /*18 进行PPP拨号所需的密码 */
    TYPE_FOTA_PPP_AUTH_ID,              /*19 进行PPP拨号时所用的鉴权方式 */
    TYPE_FOTA_SERVER_IP_ID,             /*20 FOTA服务器的IP */
    TYPE_FOTA_SERVER_PORT_ID,           /*21 FOTA服务器的端口号 */
    TYPE_FOTA_MODE_ID,                  /*22 FOTA模式的设定 */
    TYPE_FOTA_DETECT_COUNT_ID,          /*23 本地计数器的值*/
    TYPE_FOTA_NWTIME_ID,                /*24 周期查询的基准时间 */
    TYPE_FOTA_TIMER_ID,                 /*25 定时器的步长 */
    TYPE_FOTA_INTERVAL_ID,              /*26 手动版本查询的间隔时间 */
    TYPE_FOTA_SMS_CONFIG_ID,            /*27 fota暂未使用，预留*/
    TYPE_FOTA_TIME_STAMP_ID,            /*28 fota暂未使用，预留*/
    TYPE_FOTA_RSA_PUB_MODE_ID,          /*29 fota暂未使用，预留*/
    TYPE_FOTA_RSA_PUB_EXP_ID,           /*30 fota暂未使用，预留*/
    TYPE_FOTA_SMS_FLAG_ID,              /*31 既标识短信FOTA 标志位，也保存收到FOTA 短信后的重启次数 */
    TYPE_FOTA_IPSEC_PRI1_ID,            /*32 ipsec 第一个实例的私有密钥*/
    TYPE_FOTA_IPSEC_PRI2_ID,            /*33 ipsec 第二个实例的私有密钥*/
    TYPE_FOTA_IPSEC_PRI3_ID,            /*34 ipsec 第三个实例的私有密钥*/
    TYPE_FOTA_IPSEC_PRI4_ID,            /*35 ipsec 第四个实例的私有密钥*/
    TYPE_FOTA_IPSEC_PUB1_ID,            /*37 ipsec 第一个实例的公有密钥*/
    TYPE_FOTA_IPSEC_PUB2_ID,            /*38 ipsec 第二个实例的公有密钥*/
    TYPE_FOTA_IPSEC_PUB3_ID,            /*39 ipsec 第三个实例的公有密钥*/
    TYPE_FOTA_IPSEC_PUB4_ID,            /*40 ipsec 第四个实例的公有密钥*/
    TYPE_FOTA_IPSEC_RPUB1_ID,           /*41 ipsec 第一个实例的对端公有密钥*/
    TYPE_FOTA_IPSEC_RPUB2_ID,           /*42 ipsec 第二个实例的对端公有密钥*/
    TYPE_FOTA_IPSEC_RPUB3_ID,           /*43 ipsec 第三个实例的对端公有密钥*/
    TYPE_FOTA_IPSEC_RPUB4_ID,           /*44 ipsec 第四个实例的对端公有密钥*/

    TYPE_EQUIP_START = ATP_APPDATA_CATEGORY_DEF(3) | ATP_APPDATA_FLAG_NOSAVE_D,
    TYPE_EQUIP_BOOTLOAD_VERSION,        // 0x80000301
    TYPE_EQUIP_KERNEL_VERSION,
    TYPE_EQUIP_SOFT_VERSION,
    TYPE_EQUIP_SOFT_WEB_VERSION,
    TYPE_EQUIP_PRODUCT_TYPE,            //0x80000305
    TYPE_EQUIP_NET_BASEMAC,
    TYPE_EQUIP_NET_ETH_MAC,
    TYPE_EQUIP_NET_WAN_MAC,
    TYPE_EQUIP_NET_WLAN_MAC,
    TYPE_EQUIP_NET_WLAN_BASE_MAC,       //0x8000030a
    TYPE_EQUIP_NET_WLAN_RESERVED_MAC,
    TYPE_EQUIP_BASE_MAC_ADDR,
    TYPE_EQUIP_BOARD_ID,
    TYPE_EQUIP_WEB_ACCOUNT,
    TYPE_EQUIP_PCBVERSION,              //0x8000030f
    TYPE_EQUIP_CUSTOMER_SN1,
    TYPE_EQUIP_BOARD_PRODUCTSN,
    TYPE_EQUIP_TR064_RESETPWD,
    TYPE_EQUIP_SSID,
    TYPE_EQUIP_WLAN_PWD,
    TYPE_EQUIP_WEP_PWD,                 //0x80000315
    TYPE_EQUIP_BASE_MAC_ADDR_HALF,
    TYPE_EQUIP_OUI,
    TYPE_EQUIP_CUSTOMER_HW_SN,
    TYPE_EQUIP_BOARD_VERSION,
    TYPE_EQUIP_USER_PWD,                //0x8000031a
    TYPE_EQUIP_USER_NAME,
    TYPE_EQUIP_CWMP_USERNAME,
    TYPE_EQUIP_CWMP_PWD,
    TYPE_EQUIP_SIP_PWD1,
    TYPE_EQUIP_APPINCODE,               //0x8000031f
    TYPE_EQUIP_WLAN_PWD_5G,
    TYPE_EQUIP_SSID_5G,
    TYPE_EQUIP_APPINCODE_5G,
    TYPE_EQUIP_WEP_PWD_5G,
    TYPE_EQUIP_PPPOE_USER,
    TYPE_EQUIP_PPPOE_PWD,               //0x80000325
    TYPE_EQUIP_FON_KEY,
    TYPE_EQUIP_MULTI_NVRAM_ID,
    TYPE_EQUIP_WLAN_COUNTRYCODE,
    TYPE_EQUIP_CFG_KEY,
    TYPE_APP_VOIPSTATE,
    TYPE_EQUIP_MAC_NUMS,                //euap macs结构，50517
    TYPE_EQUIP_MAC_GLOBALINFO,
    TYPE_EQUIP_USBMAC,
    TYPE_EQUIP_BLUETOOTHMAC,
    TYPE_EQUIP_EUAP_MACFLAG,            //record euap mac used and released
    TYPE_APP_CFGKEY,                    //临时保存cfgkey结构体,密文
    TYPE_EQUIP_PLC_NMKPASSWD,           //DTS2016012005767 add for plc test
    TYPE_EQUIP_PLC_DEK,
    TYPE_APP_CRASHFILE_FLAG,            //crashfile使用中，web不要删除

    TYPE_EQUIP_WIFI_START = ATP_APPDATA_CATEGORY_DEF(4) | ATP_APPDATA_FLAG_NOSAVE_D,
    TYPE_EQUIP_WIFI_MACNUM,             //0x80000401，暂未实现
    TYPE_EQUIP_WIFI_MAC,                //暂未实现
    TYPE_EQUIP_WIFI_SSID_NUM,
    TYPE_EQUIP_WIFI_SSID,
    TYPE_EQUIP_WIFI_KEY_NUM,            //0x80000405
    TYPE_EQUIP_WIFI_KEY,
    TYPE_EQUIP_WIFI_PIN,
    TYPE_APP_PINLOCK_STATUS,
    TYPE_EQUIP_LAN_MACNUM,
    TYPE_EQUIP_USB_MACNUM,
    TYPE_EQUIP_BT_MACNUM,
    TYPE_EQUIP_SSID_PASSWD,
    TYPE_EQUIP_WIFI_2G_PAVARS,
    TYPE_EQUIP_WIFI_5G_PAVARS,

    /*恢复默认不清除的数据添加在这里*/
    TYPE_APP_NORST_START = ATP_APPDATA_CATEGORY_DEF(5) |ATP_APPDATA_FLAG_NORESTORE_D,
    TYPE_APP_ATP_LOG,                   //"ATP_LOG"，0x20000501
    TYPE_APP_SEC_ROOT_CERT,
    TYPE_APP_SEC_SERVER_CERT,
    TYPE_APP_SEC_SERVER_KEY,
    TYPE_EQUIP_SETEQMAC,                //atp mac set to equip
    TYPE_APP_PINLOCK_DATA,
    TYPE_APP_GW_DEVID,                  //smarthome gateway devid
    TYPE_APP_GW_SECRET,                 //smarthome gateway secret
    TYPE_APP_WEIXIN_DATA,               //weixin data info
    TYPE_APP_REBOOT_TYPE,               //系统重启类型,详见APPDATA_REBOOT_TYPE_EN
    TYPE_APP_UPG_TIME,                  //系统升级时间
    TYPE_APP_UPG_LOG,                   //系统HOTA升级日志
    TYPE_APP_SAVE_MAC,                  //save access device mac info

    TYPE_APPDATA_PARAM_END,
} APPDATA_KEY_DEF_EN;


#define APP_MAX_PIN_LEN         (32)
#define APP_MAX_MAC_NUM         (8)
#define APP_MAX_MAC_LEN         (20)
#define APP_MAX_SSID_NUM        (8)
#define APP_MAX_SSID_LEN        (33)
#define APP_MAX_KEY_LEN         (128)
#define APP_MAX_WAPKEY_LEN      (68)


typedef enum tagAPPDATA_REBOOT_TYPE_EN
{
    APPDATA_REBOOT_TYPE_NONE = 0,
    APPDATA_REBOOT_TYPE_CLI,
    APPDATA_REBOOT_TYPE_UPNP,
    APPDATA_REBOOT_TYPE_WEB,
    APPDATA_REBOOT_TYPE_HOTA,
    APPDATA_REBOOT_TYPE_UPG,
    APPDATA_REBOOT_TYPE_CWMP,
    APPDATA_REBOOT_TYPE_BUTTON,
    APPDATA_REBOOT_TYPE_LAN,
    APPDATA_REBOOT_TYPE_RESTORE,
    APPDATA_REBOOT_TYPE_POWEROFF,
    APPDATA_REBOOT_TYPE_MCAST,
    APPDATA_REBOOT_TYPE_TIMER,
    APPDATA_REBOOT_TYPE_PANIC,
}APPDATA_REBOOT_TYPE_EN;


/*voip state*/
typedef enum
{
    APPDATA_VOIP_OFF = 0,       /* 没有进行VOIP业务 */
    APPDATA_VOIP_ON,            /* 正在进行VOIP业务 */
    APPDATA_VOIP_END,           /* 结束项 */
} APPDATA_VOIP_STATE_EN;


/*wifi key */
typedef struct tagATP_EQUIP_WLAN_KEY_ST
{
    VOS_UINT8 ulWepKey1[APP_MAX_KEY_LEN];
    VOS_UINT8 ulWepKey2[APP_MAX_KEY_LEN];
    VOS_UINT8 ulWepKey3[APP_MAX_KEY_LEN];
    VOS_UINT8 ulWepKey4[APP_MAX_KEY_LEN];
    VOS_UINT8 ulWpaPsk[APP_MAX_WAPKEY_LEN];
} ATP_EQUIP_WIFI_KEY_ST;


/*mac */
typedef struct tagATP_EQUIP_WLAN_MAC_ST
{
    VOS_UINT8 ulMacAddr[APP_MAX_MAC_LEN];
} ATP_EQUIP_WIFI_MAC_ST;


/*ssid */
typedef struct tagATP_EQUIP_WLAN_SSID_ST
{
    VOS_UINT8 ulSsid[APP_MAX_SSID_LEN];
} ATP_EQUIP_WIFI_SSID_ST;


/*pin */
typedef struct tagATP_EQUIP_WLAN_PIN_ST
{
    VOS_UINT8 ulWlanPin[APP_MAX_PIN_LEN];
} ATP_EQUIP_WIFI_PIN_ST;


#define NV_SSID_NUM                    (4)
#define NV_WL_SSID_LEN                 (33)
#define NV_WL_KEY_LEN                  (27)
#define NV_WL_WPAPSK_LEN               (65)


typedef struct
{
    VOS_UINT8 aucwlSsid[NV_SSID_NUM][NV_WL_SSID_LEN];
    VOS_UINT8 aucwlWpaPsk[NV_SSID_NUM][NV_WL_WPAPSK_LEN];
    VOS_UINT8 ucwlKeys1[NV_SSID_NUM][NV_WL_KEY_LEN];
    VOS_UINT8 ucwlKeys2[NV_SSID_NUM][NV_WL_KEY_LEN];
    VOS_UINT8 ucwlKeys3[NV_SSID_NUM][NV_WL_KEY_LEN];
    VOS_UINT8 ucwlKeys4[NV_SSID_NUM][NV_WL_KEY_LEN];
}EUAP_MULT_WIFI_TYPE;


#pragma pack(1)
typedef struct
{
    VOS_UINT8 lanmac_num;   /*LAN_MAC/Cradle MAC个数*/
    VOS_UINT8 wifimac_num;  /*WIFI_MAC个数*/
    VOS_UINT8 btmac_num;    /*BLUETOOTH_MAC个数*/
    VOS_UINT8 usbmac_num;   /*USB_MAC个数*/
    VOS_UINT8 reserve[4];   /*预留字段*/
}EUAP_MAC_NUMS;
#pragma pack()


typedef struct Globe_Mac
{
    VOS_INT16 sWanMacNum;
    VOS_INT16 sWlanMacNum;
    VOS_INT32 lmacInUse;
    char szBaseMacAddr[OBLI_MAC_ADDRESS_LEN]; /*基MAC地址*/
}ATP_GlobeMac_ST;


/*!
  \author        
  \brief        写AppData
  \param[in]    ulAppID:    数据id
  \param[in]    pvBuffer:   数据buffer
  \param[in]    ulLength:   数据buffer长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    调用该接口时，若pvBuffer为空或者ulLength为0，则删除该id项
*/
#define ATP_WriteAppData(ulAppID, pvBuffer, ulLength) ATP_WriteAppDataFunc(__FUNCTION__, __LINE__, __func__, ulAppID, pvBuffer, ulLength)
VOS_UINT32 ATP_WriteAppDataFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction, VOS_UINT32 ulAppID, const VOS_VOID *pvBuffer, VOS_UINT32 ulLength);


/*!
  \author        
  \brief        读AppData
  \param[in]    ulAppID:    数据id
  \param[out]   pvBuffer:   读出数据buffer
  \param[in]    ulLength:   读出数据buffer长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT ATP_ReadAppData(VOS_UINT32 ulAppID,  VOS_VOID *pvBuffer, VOS_UINT32 ulLength);


/*!
  \author        
  \brief        获取AppData数据项的长度
  \param[in]    ulAppID:   数据id
  \param[out]   ulLength:  返回的数据长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT ATP_GetAppDataLen(VOS_UINT32 ulAppID, VOS_UINT32 *pulLength);


/*!
  \author        
  \brief        读取AppData装备数据
  \param[in]    ulID:       数据id
  \param[out]   pvBuffer:   读出数据buffer
  \param[in]    ulLength:   读出数据buffer长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    该接口与ATP_ReadAppData功能完全相同，后续考虑废弃
*/
VOS_UINT ATP_ReadEquip(VOS_UINT32 ulID, VOS_VOID *pvBuffer, VOS_UINT32 ulLength);


/*!
  \author        
  \brief        初始化AppData共享内存
  \param[in]
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    ATP_DBInit内会调用此接口，使用到appdata的进程启动时使用
*/
VOS_UINT32 ATP_AppDataInit();


/*!
  \author        
  \brief        清除整个AppData
  \param[in]
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    恢复出厂时会用到该接口
*/
VOS_UINT32 ATP_CleanAppData();


/*!
  \author        
  \brief        释放所有AppData所占内存
  \param[in]
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    将AppData置为invalid时会用到该接口
*/
VOS_UINT32 ATP_AppDataDelAll();

#endif /*appdata相关定义结束*/


#endif
