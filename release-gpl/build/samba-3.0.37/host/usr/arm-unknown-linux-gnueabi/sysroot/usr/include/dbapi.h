/******************************************************************************
  *         版权所有 (C), 2007-2020, 华为技术有限公司
*******************************************************************************/

#ifndef __DB_API_H__
#define __DB_API_H__

#include "atptypes.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*********************************宏定义*************************************/

//! CFM数据库多实例对象最深的层次
#define ATP_CFM_MAX_TREE_DEPTH      (6)
#define ATP_CFM_MSG_RETCODE_BASE    (1024)
#define ATP_CFM_INSTNUM_FAKE_OID    (0xFFFFFFFE)

#define ATP_CFM_CFG_ROOTNAME        "InternetGatewayDeviceConfig"
#define ATP_CFM_CFG_ENDTAG          "</InternetGatewayDeviceConfig>"
#define ATP_CFM_CFGFILE_HEAD        "<?xml version=\"1.0\" ?>"
#define ATP_CFM_CFG_EXTENTIONNAME   "ATPExtentionConfig"

#define ATP_CFM_MSG_BASE            ATP_MSG_CATEGORY_DEF(ATP_MODULE_CFM) /* = 0x200 = 512 */
#define ATP_CFM_INITKEYLIST         {0, 0, 0, 0, 0, 0}

#define ATP_TTREE_BBF_SEPERATOR_D       "{i}"
#define ATP_TTREE_UPNP_DM_SEPERATOR_D   "#"

/* CFM debug功能，通过menuconfig来选择使能debug模式
 * 或者通过make cfmcore ATP_DEBUG=1来使能
 */
#ifdef ATP_DEBUG
#define CFM_DEBUG(format, args...)      {printf("CFM DEBUG============file:%s, line:%d ", __FILE__, __LINE__);printf(format, ##args);printf("\n");}
#define ATP_CFM_DEBUG(format, args...)  {printf("FILE: %s LINE: %d: ", __FUNCTION__, __LINE__);printf(format, ##args);}
#else
#define CFM_DEBUG(format, args...)
#define ATP_CFM_DEBUG(x...)
#endif

/* Debug modules */
#define ATP_CFM_MODULE_DB_D         "db"

/* CFM assert function, disabled when debug */
#if defined(ATP_CFM_SAFE_RUN) && !defined(ATP_PCLINT)
#define cfmAssert(x, format, args...)   \
    if (!(x))\
    {\
        printf("CFM ASSERT>>>>>>>>file:%s, line:%d ", __FILE__, __LINE__);\
        printf(format, ##args);\
        printf("\n");\
    }
#define cfmAssertReturn(x, retval, format, args...) \
    if (!(x))\
    {\
        printf("CFM ASSERT>>>>>>>>file:%s, line:%d ", __FILE__, __LINE__);\
        printf(format, ##args);\
        printf("\n");\
        return retval;\
    }
#else
#define cfmAssert(x...)
#define cfmAssertReturn(x...)
#endif


/*********************************数据结构*************************************/

/* 该枚举暂无实质用途，后续考虑废弃 */
typedef enum tagATP_E_CFGFILE_TYPE
{
    ATP_E_CFGFILE_FULLFILE,
    ATP_E_CFGFILE_PARTFILE,
    ATP_E_CFGFILE_OUTERFILE,
}ATP_E_CFGFILE_TYPE;

/* CFM Core的错误码 */
typedef enum tagATP_E_ERR_CFM
{
    /* CFM组件的错误码 */
    ATP_E_ERR_CFM_PARA_INVALID = ATP_MNT_ERR_CODE_DEF(ATP_TEAM_MNT, ATP_MODULE_LIBCFMAPI), // = 0x30000 = 196608
    ATP_E_ERR_CFM_NOT_INIT,                 //没有初始化
    ATP_E_ERR_CFM_OPEN_FILE,
    ATP_E_ERR_CFM_FILE_INVALID,
    ATP_E_ERR_CFM_CREATE_SHM_FAILED,
    ATP_E_ERR_CFM_LOAD_SHM_FAILED,
    ATP_E_ERR_CFM_SHM_NOT_ATTACH,
    ATP_E_ERR_CFM_INTERNAL,
    ATP_E_ERR_CFM_CFGFILE_MATCH,
    ATP_E_ERR_CFM_MEM,
    ATP_E_ERR_CFM_OID_ERR,
    ATP_E_ERR_CFM_KEYLIST_OR_OID,           //keylist或者oid无效
    ATP_E_ERR_CFM_PARANUM_ZERO,
    ATP_E_ERR_CFM_PARA_ERR_OR_INST_ZERO,    //参数无效或者实例个数为0
    ATP_E_ERR_CFM_BUILD_CFG_FILE,
    ATP_E_ERR_CFM_SEM_CREATE,
    ATP_E_ERR_CFM_MSG_CREATE,               // 0x10
    ATP_E_ERR_CFM_REG_INFO,
    ATP_E_ERR_CFM_MSG_TYPE,
    ATP_E_ERR_CFM_MSG_OPCODE,
    ATP_E_ERR_CFM_CFG_TOOL_TYPE,
    ATP_E_ERR_CFM_MSG_ITEM,
    ATP_E_ERR_CFM_MSG_RESP,
    ATP_E_ERR_CFM_MSG_GETRESP,
    ATP_E_ERR_CFM_MAINPROC_DIFF,
    ATP_E_ERR_CFM_LIB_LAOD,
    ATP_E_ERR_CFM_TOO_MANY_INSTS,
    ATP_E_ERR_CFM_INVALID_INST_NUM,
    ATP_E_ERR_CFM_DOMAIN_STRING,
    ATP_E_ERR_CFM_STRING_SHORT,
    ATP_E_ERR_CFM_OBJ_DIFF,
    ATP_E_ERR_CFM_ACCESS_DENY,
    ATP_E_ERR_CFM_NOTIFY_REJECTED,          //0x20
    ATP_E_ERR_CFM_NOT_FOUND_KEY,

    /* for tr181 alias parameter */
    ATP_E_ERR_CFM_ALIAS_NOT_FOUND,
    ATP_E_ERR_CFM_NOT_ALIAS_MODE,
    ATP_E_ERR_CFM_OBJ_HAVE_NO_ALIAS_PARA,
    ATP_E_ERR_CFM_USERDADA_ACCESS_DENY,
    ARP_E_ERR_APPDATA_NOT_FOUND,
    ARP_E_ERR_APPDATA_ADD_FAIL,             // 0x27
    ARP_E_ERR_APPDATA_SHM_ERR,
    ARP_E_ERR_APPDATA_LENGTH_ERR,
    ARP_E_ERR_APPDATA_NULL_ERR,

    ARP_E_ERR_APPMAC_INIT_ERR,
    ARP_E_ERR_APPMAC_NULL_ERR,
    ARP_E_ERR_APPMAC_GET_ERR,
    ARP_E_ERR_APPMAC_LEN_ERR,

    /* 消息响应码 */
    ATP_E_ERR_CFM_RETMSG_BGN = ATP_MNT_ERR_CODE_DEF(ATP_TEAM_MNT, ATP_MODULE_LIBCFMAPI) + ATP_CFM_MSG_RETCODE_BASE, // = 0x30400 = 197632
    ATP_E_ERR_CFM_RETMSG_DONE,
    ATP_E_ERR_CFM_NO_VISIT_DB,              //不回写FLASH，只写共享内存数据库
    ATP_E_ERR_CFM_NEED_REBOOT,
    ATP_E_ERR_CFM_NO_VISIT_ANY,             //不需要保存FLASH和共享内存
    ATP_E_ERR_CFM_RETMSG_END,
    ATP_E_ERR_CFM_FLASH_ONLY,               //只序列化到FLASH，不回写共享内存数据库
    ATP_E_ERR_CFM_MAX
}ATP_E_ERR_CFM;

/* CFM KeyID定义 */
enum ATP_CFM_KEYID_EN
{
    ATP_CFM_KEY_EXPORT = ATP_SEC_KEYID_CODE_DEF(ATP_MODULE_LIBCFMAPI),
    ATP_CFM_KEY_FLASH,
    ATP_CFM_KEY_PARAM,
    ATP_CFM_KEY_CFGSIGN,
    ATP_CFM_KEY_DEFAULTCFG,
    ATP_CFM_KEY_CFGFLASH,       //配置文件动态key
};

/* 配置工具类型值必须和ATP配置项生成工具中的值一致(参见datamodel的excel文件) */
typedef enum tagATP_CFM_E_IF_TYPE
{
    ATP_CFM_E_IF_TYPE_BGN           = 0,
    ATP_CFM_E_IF_TYPE_CWMP_ADMIN    = 1 << 0,
    ATP_CFM_E_IF_TYPE_CLI_ADMIN     = 1 << 1,
    ATP_CFM_E_IF_TYPE_WEB_USER      = 1 << 2,
    ATP_CFM_E_IF_TYPE_WEB_ADMIN     = 1 << 3,
    ATP_CFM_E_IF_TYPE_TR064_ADMIN   = 1 << 4,
    ATP_CFM_E_IF_TYPE_CLI_USER      = 1 << 5,

    ATP_CFM_E_IF_TYPE_RESET_BUTTON  = 1 << 7,
    ATP_CFM_E_IF_TYPE_TELNET_SERVER = 1 << 8,
    ATP_CFM_E_IF_TYPE_CLOUDC        = 1 << 9,
    ATP_CFM_E_IF_TYPE_ELINK         = 1 << 10,

    ATP_CFM_E_IF_TYPE_CMS           = 1 << 14,
    ATP_CFM_E_IF_TYPE_OTHER         = 1 << 15,
    ATP_CFM_E_IF_TYPE_END           = 0xFFFF    //最多不能超过16种配置工具
} ATP_CFM_E_IF_TYPE;

#define ATP_CFM_CurrUserIsWeb(user)     ((ATP_CFM_E_IF_TYPE_WEB_USER == (user)) || (ATP_CFM_E_IF_TYPE_WEB_ADMIN == (user)))
#define ATP_CFM_CurrUserIsCwmp(user)    (ATP_CFM_E_IF_TYPE_CWMP_ADMIN == (user))

/* CFM值类型枚举 */
typedef enum tagATP_CFM_VALUETYPE_EN
{
    ATP_CFM_VALUETYPE_UNKNOWN = 0,
    ATP_CFM_VALUETYPE_STRING,
    ATP_CFM_VALUETYPE_NUMBER,

    ATP_CFM_VALUETYPE_EXTEND
} ATP_CFM_VALUETYPE_EN;

/* CFM全局配置文件
 * 使用配置管理进程的cfm全局结构，该结构的值由ATP_CFM_ExtConfig初始化，
 * 进程中可修改该值，结构成员值修改不影响其他进程。
 */
typedef struct tagATP_CFM_GLOBAL_CONFIG
{
    const VOS_CHAR  *pcUserName;
    VOS_UINT16      usCfgToolType;
    VOS_UINT16      usExtendNameCfgTool;
} ATP_CFM_GLOBAL_CONFIG;

/* CFM中可以自动进行TR098参数模型中NumberOfEntries的处理 */
typedef struct tagATP_CFM_ENTRYNUMBER_ST
{
    VOS_UINT32  ulOID;       /* ulOID para value = ulAddOID1 obj number + ulAddOID2 obj number */
    VOS_UINT32  ulAddOID1;   /* test */
    VOS_UINT32  ulAddOID2;   /* 0 for ignore, not used now */
} ATP_CFM_ENTRYNUMBER_ST;

#ifdef SUPPORT_ATP_CFM_VOICE_NODE_MAP
/* node InternetGatewayDevice.Services.VoiceService.{i}.VoiceProfile.{i}.NumberingPlan.X_OutgoSuffixInfo.{i}.
 * mapped to X_CommonConfig.OutgoSuffixInfo.{i}. , the last 1 {i} need copy, so ulInstLevel = 1;
 */
typedef struct tagATP_CFM_VOICE_PARA_MAP_ST
{
    VOS_UINT32  ulFromOID;
    VOS_BOOL    bCopyLastInstNum;
    VOS_UINT32  ulToOID;
} ATP_CFM_VOICE_PARA_MAP_ST;
#endif

typedef struct tagATP_PARA_ATTR_VAL_ST
{
    VOS_UINT16  usAccessBits;    /* 访问列表 */
    VOS_UINT8   ucNotifyType;    /* 参数改变通知 */
    VOS_UINT8   ucReserve;       /* 保留 */
} ATP_PARA_ATTR_VAL_ST;

typedef enum tagATP_CFM_ATTR_CHG_TYPE
{
    ATP_CFM_ATTR_CHG_ACC_LIST = 1,
    ATP_CFM_ATTR_CHG_NOTIFY   = 2,
    ATP_CFM_ATTR_CHG_RESERVE  = 4
} ATP_CFM_ATTR_CHG_TYPE;

typedef struct tagATP_CFM_ATTR_SET_ST
{
    struct tagATP_CFM_ATTR_SET_ST *pstNext;
    VOS_UINT32              ulOID;
    VOS_UINT32              ulKeyList[ATP_CFM_MAX_TREE_DEPTH];
    ATP_CFM_ATTR_CHG_TYPE   enChgType;
    ATP_PARA_ATTR_VAL_ST    stAttr;
} ATP_CFM_ATTR_SET_ST;

typedef struct tagCFM_OBJ_ADDSET_LIST_ST
{
    struct tagCFM_OBJ_ADDSET_LIST_ST *pstNext;
    VOS_UINT32  ulOID;
    VOS_UINT32  ulNextObjID;
    VOS_UINT32  ulParaNum;
    VOS_UINT32  *apulOldValues;
    VOS_UINT32  *apulChgParas;
    VOS_UINT32  *apulSetValues;
    VOS_UINT32  ulKeyList[ATP_CFM_MAX_TREE_DEPTH];
} CFM_OBJ_ADDSET_LIST_ST;

typedef enum tagATP_DB_ITERATE_TYPE_EN
{
    ATP_DB_ITERATE_VALUE = 1,
    ATP_DB_ITERATE_ATTR  = 2,
} ATP_DB_ITERATE_TYPE_EN;

typedef struct tagATP_CFM_AliasDomian_ST
{
    VOS_UINT32      ulOID;
    const VOS_CHAR  *pcName;
    const VOS_CHAR  *pcAliasName;
} ATP_CFM_AliasDomian_ST;

typedef VOS_BOOL (*PFCfmEndParseHook)(VOS_UINT32 ulOID, const VOS_CHAR *pcEndBuf);

typedef VOS_UINT32 (*PFCfmDBIterator)(
    VOS_UINT32                  ulOID,
    const VOS_CHAR              *pcDomainName,
    const VOS_VOID              *pvValue,
    const ATP_PARA_ATTR_VAL_ST  *pstAttr,
    VOS_VOID                    *pvArg);

typedef VOS_UINT32 (* PFCfmTTreeIterator)(
    VOS_UINT32                  ulOID,
    VOS_VOID                    *pvArg);


/********************************接口函数定义************************************/

/*!
  \author        
  \brief        进行数据库的初始化
  \param[in]    enIfType: enIfType 配置工具类型
  \param[in]    bReInit:  是否需要重新初始化共享内存，若是，填VOS_TRUE
  \return       返回ATP_E_ERR_CFM类型的错误码
  \retval       ATP_E_ERR_CFM_SHM_NOT_ATTACH 初始化共享内存失败
  \注意事项:    1、需要调用ATP_DBDestroy来释放共享内存；
                2、不必重复调用ATP_AppDataInit，因为ATP_DBInit中会调用ATP_AppDataInit初始化AppData共享内存区；
                3、只需要在系统初始化的一个进程中调用一次；
                4、只有mic进程调用时，bReInit需要填VOS_TRUE；其它进程调用时，都需填充为VOS_FALSE
*/
VOS_UINT32 ATP_DBInit(ATP_CFM_E_IF_TYPE enIfType, VOS_BOOL bReInit);


/*!
  \author        
  \brief        CFM共享内存卸载(去初始化)
  \param[in]
  \return       返回ATP_E_ERR_CFM类型的错误码
  \retval       ATP_E_ERR_CFM_SHM_NOT_ATTACH 初始化共享内存失败
  \注意事项:    1、要与ATP_DBInit配对使用；
                2、该函数若被业务进程或配置工具调用，作用是断开对共享内存的连接；
                   该函数若被主控制进程调用，作用是卸载共享内存，去初始化CFM
*/
VOS_UINT32 ATP_DBDestroy(VOS_VOID);


/*!
  \author        
  \brief        设置配置当前使用CFM API库的配置工具
  \param[in]    enIfType:  配置工具类型
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    该接口可在一个进程中多次调用
*/
VOS_UINT32 ATP_DBSetCurrUser(ATP_CFM_E_IF_TYPE enIfType);


/*!
  \author        
  \brief        获取当前使用CFM API库的配置工具类型
  \param[in]
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_DBGetCurrUser(VOS_VOID);


/*!
  \author        
  \brief        设置当前Web配置工具及其用户名
  \param[in]    enIfType:       配置工具类型
  \param[in]    pcWebUserName:  当前用户名
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_DBSetCurrWebUser(ATP_CFM_E_IF_TYPE enIfType, const VOS_CHAR* pcWebUserName);


/*!
  \author        
  \brief        获取当前使用CFM API库使用的Web用户名
  \param[in]
  \return       当前Web用户名
  \retval       用户名字符串
  \注意事项:    无
*/
const VOS_CHAR* ATP_DBGetCurrWebUser();


/*!
  \author        
  \brief        根据对象ID来获取整个对象的值
  \param[in]    ulKeyList:      对象的实例号列表，如果是简单对象，可以为空
  \param[in]    ulOID:          待获取对象的CMO
  \param[out]   ppulObj:        对象的值，需要通过ATP_CFM_FreeObj释放内存
  \param[out]   pulNumOfParas:  对象的总参数个数
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    调用该接口后，ppulObj将持有堆内存，务必调用ATP_CFM_FreeObj释放内存
*/
VOS_UINT32 ATP_DBGetObj(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_UINT32 **ppulObj,
    VOS_UINT32 *pulNumOfParas);


/*!
  \author        
  \brief        根据对象ID来获取DB对象的扩展接口
  \param[in]    ulKeyList:      对象的实例号列表，如果是简单对象，可以为空
  \param[in]    ulOID:          待获取对象的CMO
  \param[in]    bGetOldDB:      是否从AddSet列表读取，为VOS_TRUE则从AddSet列表读取
  \param[out]   ppulObj:        对象的值，需要通过ATP_CFM_FreeObj释放内存
  \param[out]   pulNumOfParas:  对象的总参数个数
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    1、调用该接口后，ppulObj将持有堆内存，务必调用ATP_CFM_FreeObj释放内存；
                2、该接口目前仅QOS业务路由桥模式cms子模块使用，后续考虑废弃；
                3、该接口与ATP_DBGetObj区别主要是读取对象是否从m_pstAddSetObjList读取
*/
VOS_UINT32 ATP_DBGetObj_Ex(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_UINT32 **ppulObj,
    VOS_UINT32 *pulNumOfParas,
    VOS_BOOL bGetOldDB);


/*!
  \author        
  \brief        根据对象名称读取DB对象
  \param[in]    pcObjName:      对象名称，采用点分格式
  \param[out]   ppulObj:        对象的值，需要通过ATP_CFM_FreeObj释放内存
  \param[out]   pulNumOfParas:  对象的总参数个数
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    调用该接口后，ppulObj将持有堆内存，务必调用ATP_CFM_FreeObj释放内存
*/
VOS_UINT32 ATP_DBGetObjByName(const VOS_CHAR *pcObjName,
    VOS_UINT32 **ppulObj,
    VOS_UINT32 *pulNumOfParas);


/*!
  \author        
  \brief        通过OID以对象为单位设置对象的值
  \param[in]    ulKeyList:      对象的实例号列表，如果是简单对象，可以为空
  \param[in]    ulOID:          待设置对象的CMO
  \param[in]    pulObj:         待设置对象的值
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    调用该接口后，需要调用ATP_CFM_FreeObj或ATP_CFM_FreeObjByName释放pulObj持有的内存
*/
VOS_UINT32 ATP_DBSetObj(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32       ulOID,
    const VOS_UINT32 *pulObj);


/*!
  \author        
  \brief        通过OID以对象为单位设置对象值的扩展接口
  \param[in]    ulKeyList:      对象的实例号列表，如果是简单对象，可以为空
  \param[in]    ulOID:          待设置对象的CMO
  \param[in]    pulObj:         待设置对象的值
  \param[in]    pulChgParas:    VOS_BOOL类型的数组，标识了每个参数是否改变
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    1、调用该接口后，需要调用ATP_CFM_FreeObj或ATP_CFM_FreeObjByName释放pulObj持有的内存
                2、该接口与ATP_DBSetObj只有在BUILD_CFM_VOICE_NODE_MAP开启时有区别，
                   区别在于本接口可以携带一个flag数组，其中标识了每个参数是否改变
*/
VOS_UINT32 ATP_DBSetObjEx(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32       ulOID,
    const VOS_UINT32 *pulObj,
    const VOS_UINT32 *pulChgParas);


/*!
  \author        
  \brief        添加一个DB对象
  \param[in]    ulKeyList:      待添加对象的实例号列表
  \param[in]    ulOID:          待添加对象的CMO
  \param[in]    pulObjValues:   新增对象的值
  \param[out]   pulInstanceId:  新增对象的实例号
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    1、若想获取对象默认值，可通过ATP_CFM_GetObjDftValue接口获取；
                2、若被添加对象的父对象尚未创建，则添加失败
                3、循环调用该接口可能导致DB无限增大，比如每次开机都Add一个节点
*/
VOS_UINT32 ATP_DBAddObj(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    const VOS_UINT32 *pulObjValues,
    VOS_UINT32 *pulInstanceId);


/*!
  \author        
  \brief        删除一个DB对象
  \param[in]    ulKeyList:      对象的实例号列表
  \param[in]    ulOID:          待删除对象的CMO
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_DBDelObj(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID);


/*!
  \author        
  \brief        删除一个DB对象，但不检查Change Flag标记
  \param[in]    ulKeyList:      对象的实例号列表
  \param[in]    ulOID:          待删除对象的CMO
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    1、该接口与ATP_DBDelObj的区别在于，本接口不检查标记，
                   防止升级版本后节点不能添加；
                2、该接口目前仅防火墙cms子模块使用，其他地方未用到
*/
VOS_UINT32 ATP_DBDelObjIgnoreFlag(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH], 
    VOS_UINT32 ulOID);


/*!
  \author        
  \brief        获取指定实例号列表下对象的个数
  \param[in]    ulKeyList:      对象的实例号列表，可以为空。如果是空，则表示所有实例的个数
  \param[in]    ulOID:          待获取对象的CMO
  \param[out]   pulNum:         获取到的对象个数
  \param[out]   ppulInstArray:  实例号数组
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    调用该接口后，ppulInstArray将持有堆内存，需要调用ATP_FREE释放内存
*/
VOS_UINT32 ATP_DBGetNumOfObjs(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_UINT32 *pulNum,
    VOS_UINT32 **ppulInstArray);


/*!
  \author        
  \brief        根据序号获取对象值
  \param[in]    ulKeyList:      对象的实例号列表，可以为空。如果是空，则表示所有实例的个数
  \param[in]    ulOID:          待获取对象的CMO
  \param[in]    ulSeqNum:       需要获取的对象序号，从0开始
  \param[out]   ppulObj:        对象的值，需要通过ATP_CFM_FreeObj释放内存
  \param[out]   puInstNo:       输出的对象实例号，可以为空
  \param[out]   pulNumOfParas:  输出的参数个数，可以为空
  \param[out]   ulNewKeyList:   更新后的对象实例号列表
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    调用该接口后，ppulObj将持有堆内存，务必调用ATP_CFM_FreeObj释放内存
*/
VOS_UINT32 ATP_DBGetObjectBySeqNum(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_UINT32 ulSeqNum,
    VOS_UINT32 **ppulObj,
    VOS_UINT32 *puInstNo,
    VOS_UINT32 *pulNumOfParas,
    VOS_UINT32 ulNewKeyList[ATP_CFM_MAX_TREE_DEPTH]);


/*!
  \author        
  \brief        根据实例号列表及参数的CMO，获取单个参数的值
  \param[in]    ulKeyList:      参数的实例号列表，如果是简单对象，可以为空
  \param[in]    ulOID:          对象的OID
  \param[out]   pValue:         参数值指针
  \param[in]    ulValueLen:     参数值buff长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    该接口一次只能获取一个参数的值
*/
VOS_UINT32 ATP_DBGetPara(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_VOID *pValue,
    VOS_UINT32 ulValueLen);


/*!
  \author        
  \brief        根据域名，获取单个参数的值
  \param[in]    pcParaName:     参数的域名
  \param[out]   pValue:         参数值指针
  \param[in]    ulValueLen:     参数值buff长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    该接口一次只能获取一个参数的值
*/
VOS_UINT32 ATP_DBGetParaByName(const VOS_CHAR *pcParaName,
    VOS_VOID *pValue,
    VOS_UINT32 ulValueLen);


/*!
  \author        
  \brief        根据对象OID设置对象参数
  \param[in]    ulKeyList:      参数的实例号列表
  \param[in]    ulOID:          对象的OID
  \param[in]    pvData:         设置的数据。填充的指针必须和OID的值类型相同。
                                如果是字符串类型的，直接填字符串指针；
                                否则，直接填充整数值
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_DBSetPara(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    const VOS_VOID *pvData);


/*!
  \author        
  \brief        根据对象域名设置对象参数
  \param[in]    pcPara:      参数的域名
  \param[in]    pvValue:     设置的数据。填充的指针必须和OID的值类型相同。
                             如果是字符串类型的，直接填字符串指针；
                             否则，直接填充整数值
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_DBSetParaByName(const VOS_CHAR *pcPara, const VOS_VOID *pvValue);


/*!
  \author        
  \brief        将点分格式域名转换为实例号列表和OID，忽略前缀
  \param[in]    pszDomain:      对象的域名
  \param[out]   ulKeyList:      参数的实例号列表
  \param[out]   pulOID:         对象的OID
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    该接口与ATP_DBDomainToKeyList的区别在于，本接口提供了一种更灵活的传参方式，
                允许域名参数省略"InternetGatewayDevice.Device."前缀
*/
VOS_UINT32 ATP_DBDomainToKeyListIgnorePrefix(const VOS_CHAR* pszDomain,
    VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32* pulOID);


/*!
  \author        
  \brief        将点分格式域名转换为实例号列表和OID
  \param[in]    pszDomain:      对象的域名
  \param[out]   ulKeyList:      参数的实例号列表
  \param[out]   pulOID:         对象的OID
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_DBDomainToKeyList(const VOS_CHAR* pszDomain,
    VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32* pulOID);


/*!
  \author        
  \brief        将点分格式域名转换为实例号列表和OID，带访问控制策略检查
  \param[in]    pszDomain:      对象的域名
  \param[out]   ulKeyList:      参数的实例号列表
  \param[out]   pulOID:         对象的OID
  \param[in]    bReadAccess:    是否检查读写标志位，VOS_TRUE则检查ReadBits，否则检查WriteBits
  \param[in]    bAddOperate:    是否是Add操作，若是则只检查ReadBits和WriteBits
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    1、该接口与ATP_DBDomainToKeyList的区别在于，本接口会进行参数的访问控制检查；
                2、本接口目前仅cwmp模块一处使用，后续考虑废弃
*/
VOS_UINT32 ATP_DBDomainToKeyListWithAccCheck(const VOS_CHAR* pszDomain,
    VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32* pulOID, VOS_BOOL bReadAccess,
    VOS_BOOL bAddOperate);


/*!
  \author        
  \brief        根据对象实例号列表和OID转换为点分格式域名
  \param[in]    ulKeyList:      参数的实例号列表
  \param[in]    pulOID:         对象的OID
  \param[out]   pszDomain:      对象的域名
  \param[in]    ulDomainLen:    对象的域名buffer长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_DBKeyListToDomain(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_CHAR* pszDomain,
    VOS_UINT32 ulDomainLen);


/*!
  \author        
  \brief        根据对象实例号列表和OID转换为点分格式域名的扩展接口
  \param[in]    ulKeyList:      参数的实例号列表
  \param[in]    pulOID:         对象的OID
  \param[out]   pszDomain:      对象的域名
  \param[in]    ulDomainLen:    对象的域名buffer长度
  \param[in]    bDecreaseByOne: 是否对最后一位实例号做减一操作
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    1、该接口与ATP_DBKeyListToDomain的区别在于，本接口可选择对最后一位实例号减一；
                2、本接口的实质调用仅cfmmsg一处，后续考虑优化废弃
*/
VOS_UINT32 ATP_DBKeyListToDomainEx(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_CHAR* pszDomain,
    VOS_UINT32 ulDomainLen,
    VOS_BOOL  bDecreaseByOne);


/*!
  \author        
  \brief        根据对象OID获取域名深度
  \param[in]    ulOID:          对象的OID
  \return       对象的域名深度
  \retval       无符号整数
  \注意事项:    无
*/
VOS_UINT32 ATP_DBGetInstDepthOfOID(VOS_UINT32 ulOID);


/*!
  \author        
  \brief        将多实例节点下的子树移动到另一个同OID的多实例节点下
  \param[in]    ulSourceKeyList:    源实例号列表
  \param[in]    ulSourceObj:        源对象的OID
  \param[in]    ulDestKeyList:      目标实例号列表
  \param[out]   pulNewObjInstId:    移动后的新实例号
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_DBObjMove(
    const VOS_UINT32    ulSourceKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32          ulSourceObj,
    const VOS_UINT32    ulDestKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32          *pulNewObjInstId);


/*!
  \author        
  \brief        根据参数名获取参数的OID
  \param[out]   ulObjOID:       对象的OID
  \param[in]    pszParaName:    获取到的参数名
  \return       返回参数的OID
  \retval       成功返回OID，失败返回0
  \注意事项:    该接口只有web的lua模块一处使用，属于可替代接口，后续考虑废弃
*/
VOS_UINT32 ATP_DBGetParaOIDByParaName(VOS_UINT32 ulObjOID, const VOS_CHAR* pszParaName);


/*!
  \author        
  \brief        根据CMO，获取对象的默认值
  \param[in]    ulOID:          对象的OID
  \param[out]   ppulDftValues:  对象的默认值，需要通过ATP_Free释放内存
  \param[out]   pulNumOfParas:  对象的总参数个数
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    调用该接口后，ppulDftValues将持有堆内存，务必调用ATP_Free释放内存
*/
VOS_UINT32 ATP_DBGetDftObject(VOS_UINT32 ulOID,
    VOS_UINT32 **ppulDftValues,
    VOS_UINT32 *pulNumOfParas);


/*!
  \author        
  \brief        根据对象OID将对应的对象参数恢复为默认值
  \param[in]    ulKeyList:      参数的实例号列表
  \param[in]    pulOID:         对象的OID
  \param[in]    bSaveDB:        是否保存到DB(目前未使用)
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    该函数增加bSaveDB参数不合理，数据库的操作尽量纯粹些，不涉及Flash操作；
                后续应废弃bSaveDB参数
*/
VOS_UINT32 ATP_DBSetDftObject(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_BOOL bSaveDB);


/*!
  \author        
  \brief        根据OID获取对象或参数名称
  \param[in]    ulOID:          对象或参数的OID
  \return       返回对象或参数的域名
  \retval       域名字符串
  \注意事项:    该接口仅mic一处使用，后续考虑优化废弃
*/
const VOS_CHAR *ATP_DBGetNameOfOID(VOS_UINT32 ulOID);


/*!
  \author        
  \brief        根据对象OID获取对象名称
  \param[in]    ulOID:          对象的OID
  \return       返回对象的域名
  \retval       域名字符串
  \注意事项:    该接口仅cfma两处使用，与ATP_DBGetNameOfOID完全重复，后续应废弃
*/
const VOS_CHAR *ATP_DBGetObjNameOfOID(VOS_UINT32 ulOID);


/*!
  \author        
  \brief        提前获取对象的实例编号
  \param[in]    ulKeyList:      参数的实例号列表
  \param[in]    pulOID:         对象的OID
  \param[out]   pulInstId:      获取到的对象实例ID
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    该接口仅cfma一处使用，后续考虑优化废弃
*/
VOS_UINT32 ATP_DBPreGetObjInstID(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_UINT32 *pulInstId);


/*!
  \author        
  \brief        标记用户修改了DB数据
  \param[in]    
  \return       NA
  \retval       void
  \注意事项:    1、同步时不记录用户修改记录
                2、系统启动之后识别到ISP商加载ISP时不能覆盖用户修改的数据
*/
VOS_VOID ATP_DBOpenSaveChgFlags();


/*!
  \author        
  \brief        清除用户修改了DB数据的标记
  \param[in]    
  \return       NA
  \retval       void
  \注意事项:    1、同步时不记录用户修改记录
                2、系统启动之后识别到ISP商加载ISP时不能覆盖用户修改的数据
*/
VOS_VOID ATP_DBCloseSaveChgFlags();


/*!
  \author        
  \brief        标记运营商(ISP)修改了DB数据
  \param[in]    
  \return       NA
  \retval       void
  \注意事项:    1、同步时不记录用户修改记录
                2、系统启动之后识别到ISP商加载ISP时不能覆盖用户修改的数据
*/
VOS_VOID ATP_DBOpenChangeISPCfg();


/*********************************CFM对象相关接口******************************/

/*!
  \author        
  \brief        根据对象OID获取域名
  \param[in]    ulKeyList:      参数的实例号列表
  \param[in]    ulOID:          对象的OID
  \return       对象的域名
  \retval       域名字符串
  \注意事项:    1、该接口内部对于keylist为NULL的场景是取所有节点的第一个实例；
                2、该接口功能与ATP_DBGetNameOfOID相似度很高，建议后续废弃
*/
VOS_CHAR *ATP_CFM_GetDomainForOID(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH], 
    VOS_UINT32 ulOID);


/*!
  \author        
  \brief        根据访问控制列表获取访问权限标志
  \param[in]    pcAccList:      访问控制列表字符串
  \return       返回访问权限标志
  \retval       若pcAccList为NULL，返回ATP_CFM_E_IF_TYPE_CWMP_ADMIN；
                若pcAccList为"Subscriber"，返回usAccessBits标志位；
                否则，返回0
  \注意事项:    无
*/
VOS_UINT32 ATP_CFM_ExtGetAccListItem(const VOS_CHAR *pcAccList);


/*!
  \author        
  \brief        根据访问控制权限标记获取访问控制名称字符串
  \param[in]    ulAccList:      访问控制标记
  \param[out]   apcNames:       访问控制名称字符串
                                若ulAccList为ATP_CFM_E_IF_TYPE_CWMP_ADMIN，则返回空字符串，
                                否则返回"Subscriber"
  \param[in]    ulBufLen:       访问控制名称字符串buffer长度
  \return       返回执行结果
  \retval       成功返回1，失败返回0
  \注意事项:    无
*/
VOS_UINT32 ATP_CFM_ExtGetAccListStrings(VOS_UINT32 ulAccList, 
    const VOS_CHAR *apcNames[],
    VOS_UINT32 ulBufLen);


/*!
  \author        
  \brief        设置参数或者对象的属性
  \param[in]    pstSetAttrList: 属性列表
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    1、参数的属性主要用于TR069的参数改变上报和访问列表信息；
                2、后续该接口要重命名为ATP_CFM_SetAttrOfCMO
*/
VOS_UINT32 ATP_CFM_SetAttrOfCMOEx(ATP_CFM_ATTR_SET_ST *pstSetAttrList);


/*!
  \author        
  \brief        获取参数或者对象的属性
  \param[in]    ulKeyList:      参数的实例号列表
  \param[in]    ulOID:          对象的OID
  \param[out]   pstParaAttr:    参数的属性
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_CFM_GetAttrOfCMO(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32  ulOID,
    ATP_PARA_ATTR_VAL_ST *pstParaAttr);


/*!
  \author        
  \brief        设置对象的HideBits标志位
  \param[in]    ulKeyList:      参数的实例号列表
  \param[in]    ulOID:          对象的OID
  \param[in]    ulHideBits:     待设置的HideBits标志位
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_CFM_SetHideBitsOfCMO(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32  ulOID,
    VOS_UINT32  ulHideBits);


/*!
  \author        
  \brief        比较两个对象的值是否相同
  \param[in]    ulOID:          对象OID，或者对象下任意参数的OID
  \param[in]    pulSrcObj:      比较的第一个对象的值
  \param[in]    pulDstObj:      比较的第二个对象的值
  \return       比较结果
  \retval       相同返回VOS_TRUE，不同返回VOS_FALSE
  \注意事项:    pulSrcObj和pulDstObj需要是相同对象的值
*/
VOS_BOOL ATP_CFM_CompareObj(VOS_UINT32 ulOID,
    const VOS_UINT32 *pulSrcObj,
    const VOS_UINT32 *pulDstObj);


/*!
  \author        
  \brief        释放对象的值所持有的内存
  \param[in]    ulOID:          待释放对象的OID
  \param[out]   pulObj:         待释放对象的结构体指针
  \return       NA
  \retval       void
  \注意事项:    本接口用于释放OBJ结构成员中字符串类型的内存，OBJ结构本身还需要外部释放
*/
VOS_VOID ATP_CFM_FreeObj(VOS_UINT32 ulOID, VOS_UINT32 *pulObj);


/*!
  \author        
  \brief        根据域名释放对象的值所持有的内存
  \param[in]    pcObjName:      待释放对象的域名
  \param[out]   pulObj:         待释放对象的结构体指针
  \return       NA
  \retval       void
  \注意事项:    本接口用于释放OBJ结构成员中字符串类型的内存，OBJ结构本身还需要外部释放
*/
VOS_VOID ATP_CFM_FreeObjByName(const VOS_CHAR *pcObjName, VOS_UINT32 *pulObj);


/*!
  \author        
  \brief        拷贝一个对象的值
  \param[in]    ulOID:          源对象的OID
  \param[in]    pulSrcObj:      源对象的值
  \return       克隆出来的新对象指针
  \retval       新对象的指针
  \注意事项:    调用该接口后，返回值将会持有堆内存，需要使用ATP_CFM_FreeObj释放内存
*/
VOS_UINT32 *ATP_CFM_CopyObj(VOS_UINT32 ulOID, const VOS_UINT32 *pulSrcObj);


/*!
  \author        
  \brief        修改对象中字符串参数的值
  \param[in]    ulParaIndex:    参数索引
  \param[in]    pulObj:         对象的指针
  \param[in]    pcNewValue:     待设置的新参数值
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_CFM_SetObjStrValue(VOS_UINT32 ulParaIndex,
    VOS_UINT32 *pulObj,
    const VOS_CHAR *pcNewValue);


/*!
  \author        
  \brief        修改对象中整型参数的值
  \param[in]    ulParaIndex:    参数索引
  \param[in]    pulObj:         对象的指针
  \param[in]    ullNewValue:    待设置的新参数值，无符号长整型
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_CFM_SetObjUintLongValue(VOS_UINT32 ulParaIndex,
    VOS_UINT32 *pulObj,
    const VOS_UINT64 ullNewValue);


/*!
  \author        
  \brief        比较两个实例号列表是否相同
  \param[in]    ulKeyList1:     待比较的第一个实例号列表
  \param[in]    ulKeyList2:     待比较的第二个实例号列表
  \param[in]    ulCMO:          对象的OID
  \return       比较结果
  \retval       相同返回VOS_TRUE，不同返回VOS_FALSE
  \注意事项:    无
*/
VOS_BOOL ATP_CFM_IsKeyListSame(const VOS_UINT32 ulKeyList1[ATP_CFM_MAX_TREE_DEPTH],
    const VOS_UINT32 ulKeyList2[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulCMO);


/*!
  \author        
  \brief        是否需要通知配置工具参数改变
  \param[in]    ulKeyList:      参数的实例号列表
  \param[in]    ulOID:          对象的OID
  \return       返回是否需要通知
  \retval       需要notify则返回VOS_TRUE，否则返回VOS_FALSE
  \注意事项:    无
*/
VOS_BOOL ATP_CFM_IsAttrNeedNotify(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID);


/*!
  \author        
  \brief        将一个字符串转换为无符号长整型
  \param[in]    pcValue:        待转换的字符串
  \param[out]   pulValue:       转换后的长整型
  \return       是否转换成功
  \retval       成功返回VOS_TRUE，失败返回VOS_FALSE
  \注意事项:    1、该接口与DB无关，后续移到msgapi的公共util文件中；
                2、后续该接口应内部使用，对外只暴露ATP_CFM_UtilConvertValueType接口
*/
VOS_BOOL ATP_CFM_UtilChar2Ulong(const VOS_CHAR *pcValue, VOS_UINT32 *pulValue);


/*!
  \author        
  \brief        将一个字符串转换为有符号长整型
  \param[in]    pcValue:        待转换的字符串
  \param[out]   plValue:        转换后的长整型
  \return       是否转换成功
  \retval       成功返回VOS_TRUE，失败返回VOS_FALSE
  \注意事项:    1、该接口与DB无关，后续移到msgapi的公共util文件中；
                2、后续该接口应内部使用，对外只暴露ATP_CFM_UtilConvertValueType接口
*/
VOS_BOOL ATP_CFM_UtilChar2Long(const VOS_CHAR *pcValue, VOS_INT32 *plValue);


/*!
  \author        
  \brief        将一个字符串转换为无符号long long类型
  \param[in]    pcValue:        待转换的字符串
  \param[out]   pulValue:       转换后的值
  \return       是否转换成功
  \retval       成功返回VOS_TRUE，失败返回VOS_FALSE
  \注意事项:    1、该接口与DB无关，后续移到msgapi的公共util文件中；
                2、后续该接口应内部使用，对外只暴露ATP_CFM_UtilConvertValueType接口
*/
VOS_BOOL ATP_CFM_UtilChar2ULongLong(const VOS_CHAR *pcValue, VOS_UINT64 **pulValue);


/*!
  \author        
  \brief        将一个字符串转换为其它类型
  \param[in]    pcValue:        待转换的字符串
  \param[out]   pvValue:        转换后的值
  \param[in]    ulValueType:    转换为哪种类型，当前支持的类型有:
                                CMO_DATA_TYPE_UINT
                                CMO_DATA_TYPE_INT
                                CMO_DATA_TYPE_UINTL
                                CMO_DATA_TYPE_BOOL
  \return       是否转换成功
  \retval       成功返回VOS_TRUE，失败返回VOS_FALSE
  \注意事项:    该接口与DB无关，后续移到msgapi的公共util文件中
*/
VOS_BOOL ATP_CFM_UtilConvertValueType(const VOS_CHAR *pcValue,
    VOS_VOID    **pvValue,
    VOS_UINT32  ulValueType);


/*!
  \author        
  \brief        判断一个CMO是否需要加密
  \param[in]    ulCmo:          对象的OID
  \return       返回是否需要加密
  \retval       需要则返回VOS_TRUE，不需要则返回VOS_FALSE
  \注意事项:    该接口内部维护了一个局部数组aulEncodeCmos，所有需要加密的CMO都需要加入该数组
*/
VOS_BOOL ATP_CFM_ExtIsCmoNeedEncrypt(VOS_UINT32 ulCmo);


/*
 *  PPPConnection.{i}.X_LowerLayers的值
 *      cwmp要求为InternetGatewayDevice.X_ATP_VLANTermination.1
 *      web则要求为InternetGatewayDevice.X_VLANTermination.1
 *
 *      ATP_CFM_UtilValueStripExtension用于把X_ATP strip为X_
 *      ATP_CFM_UtilValueAddExtension  用于把X_扩展为X_ATP
 */
VOS_CHAR *ATP_CFM_UtilValueStripExtension(VOS_UINT32 ulCmo, const VOS_CHAR *pcValue);
VOS_CHAR *ATP_CFM_UtilValueAddExtension(VOS_UINT32 ulCmo, const VOS_CHAR *pcValue);
VOS_CHAR *ATP_CFM_UtilValueStripExtensionEx(VOS_UINT32 ulCmo, const VOS_CHAR *pcValue, VOS_BOOL bForce);
VOS_CHAR *ATP_CFM_UtilValueAddExtensionEx(VOS_UINT32 ulCmo, const VOS_CHAR *pcValue, VOS_BOOL bForce);


/*********************************全局变量*************************************/
extern ATP_THREAD_SAFE VOS_UINT32 g_ulCfmErr;               //用于cfm唯一的错误码记录
extern const VOS_UINT32 g_aulRecycleOids[];                 //循环回收OID
extern const VOS_CHAR *g_apcNameExtensions[];               //CMO名称扩展，成员定义在atpconfig.h
extern const VOS_UINT16 g_usHidePwdCfgTools;                //隐藏密码的配置工具
extern VOS_BOOL g_bCheckSetPara;                            //控制是否启动后台校验，默认为启动校验
extern PFCfmEndParseHook g_pfEndParseHook;                  //CFM域名解析后的回调函数
extern const ATP_CFM_AliasDomian_ST g_pstAliasDomianList[]; //Domain别名列表
extern const VOS_UINT32 g_aulEncodeCmos[];                  //需要加密编码处理的CMO节点
extern const VOS_UINT32 g_aulValueWithExtension[];          //带扩展名的CMO节点值


/*********************************内嵌头文件包含*******************************/
#include "appdataapi.h"
#include "shmemapi.h"
#include "flagapi.h"


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
