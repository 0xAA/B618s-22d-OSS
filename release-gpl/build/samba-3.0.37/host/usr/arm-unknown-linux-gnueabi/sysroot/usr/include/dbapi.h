/******************************************************************************
  *         ��Ȩ���� (C), 2007-2020, ��Ϊ�������޹�˾
*******************************************************************************/

#ifndef __DB_API_H__
#define __DB_API_H__

#include "atptypes.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*********************************�궨��*************************************/

//! CFM���ݿ��ʵ����������Ĳ��
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

/* CFM debug���ܣ�ͨ��menuconfig��ѡ��ʹ��debugģʽ
 * ����ͨ��make cfmcore ATP_DEBUG=1��ʹ��
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


/*********************************���ݽṹ*************************************/

/* ��ö������ʵ����;���������Ƿ��� */
typedef enum tagATP_E_CFGFILE_TYPE
{
    ATP_E_CFGFILE_FULLFILE,
    ATP_E_CFGFILE_PARTFILE,
    ATP_E_CFGFILE_OUTERFILE,
}ATP_E_CFGFILE_TYPE;

/* CFM Core�Ĵ����� */
typedef enum tagATP_E_ERR_CFM
{
    /* CFM����Ĵ����� */
    ATP_E_ERR_CFM_PARA_INVALID = ATP_MNT_ERR_CODE_DEF(ATP_TEAM_MNT, ATP_MODULE_LIBCFMAPI), // = 0x30000 = 196608
    ATP_E_ERR_CFM_NOT_INIT,                 //û�г�ʼ��
    ATP_E_ERR_CFM_OPEN_FILE,
    ATP_E_ERR_CFM_FILE_INVALID,
    ATP_E_ERR_CFM_CREATE_SHM_FAILED,
    ATP_E_ERR_CFM_LOAD_SHM_FAILED,
    ATP_E_ERR_CFM_SHM_NOT_ATTACH,
    ATP_E_ERR_CFM_INTERNAL,
    ATP_E_ERR_CFM_CFGFILE_MATCH,
    ATP_E_ERR_CFM_MEM,
    ATP_E_ERR_CFM_OID_ERR,
    ATP_E_ERR_CFM_KEYLIST_OR_OID,           //keylist����oid��Ч
    ATP_E_ERR_CFM_PARANUM_ZERO,
    ATP_E_ERR_CFM_PARA_ERR_OR_INST_ZERO,    //������Ч����ʵ������Ϊ0
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

    /* ��Ϣ��Ӧ�� */
    ATP_E_ERR_CFM_RETMSG_BGN = ATP_MNT_ERR_CODE_DEF(ATP_TEAM_MNT, ATP_MODULE_LIBCFMAPI) + ATP_CFM_MSG_RETCODE_BASE, // = 0x30400 = 197632
    ATP_E_ERR_CFM_RETMSG_DONE,
    ATP_E_ERR_CFM_NO_VISIT_DB,              //����дFLASH��ֻд�����ڴ����ݿ�
    ATP_E_ERR_CFM_NEED_REBOOT,
    ATP_E_ERR_CFM_NO_VISIT_ANY,             //����Ҫ����FLASH�͹����ڴ�
    ATP_E_ERR_CFM_RETMSG_END,
    ATP_E_ERR_CFM_FLASH_ONLY,               //ֻ���л���FLASH������д�����ڴ����ݿ�
    ATP_E_ERR_CFM_MAX
}ATP_E_ERR_CFM;

/* CFM KeyID���� */
enum ATP_CFM_KEYID_EN
{
    ATP_CFM_KEY_EXPORT = ATP_SEC_KEYID_CODE_DEF(ATP_MODULE_LIBCFMAPI),
    ATP_CFM_KEY_FLASH,
    ATP_CFM_KEY_PARAM,
    ATP_CFM_KEY_CFGSIGN,
    ATP_CFM_KEY_DEFAULTCFG,
    ATP_CFM_KEY_CFGFLASH,       //�����ļ���̬key
};

/* ���ù�������ֵ�����ATP���������ɹ����е�ֵһ��(�μ�datamodel��excel�ļ�) */
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
    ATP_CFM_E_IF_TYPE_END           = 0xFFFF    //��಻�ܳ���16�����ù���
} ATP_CFM_E_IF_TYPE;

#define ATP_CFM_CurrUserIsWeb(user)     ((ATP_CFM_E_IF_TYPE_WEB_USER == (user)) || (ATP_CFM_E_IF_TYPE_WEB_ADMIN == (user)))
#define ATP_CFM_CurrUserIsCwmp(user)    (ATP_CFM_E_IF_TYPE_CWMP_ADMIN == (user))

/* CFMֵ����ö�� */
typedef enum tagATP_CFM_VALUETYPE_EN
{
    ATP_CFM_VALUETYPE_UNKNOWN = 0,
    ATP_CFM_VALUETYPE_STRING,
    ATP_CFM_VALUETYPE_NUMBER,

    ATP_CFM_VALUETYPE_EXTEND
} ATP_CFM_VALUETYPE_EN;

/* CFMȫ�������ļ�
 * ʹ�����ù�����̵�cfmȫ�ֽṹ���ýṹ��ֵ��ATP_CFM_ExtConfig��ʼ����
 * �����п��޸ĸ�ֵ���ṹ��Աֵ�޸Ĳ�Ӱ���������̡�
 */
typedef struct tagATP_CFM_GLOBAL_CONFIG
{
    const VOS_CHAR  *pcUserName;
    VOS_UINT16      usCfgToolType;
    VOS_UINT16      usExtendNameCfgTool;
} ATP_CFM_GLOBAL_CONFIG;

/* CFM�п����Զ�����TR098����ģ����NumberOfEntries�Ĵ��� */
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
    VOS_UINT16  usAccessBits;    /* �����б� */
    VOS_UINT8   ucNotifyType;    /* �����ı�֪ͨ */
    VOS_UINT8   ucReserve;       /* ���� */
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


/********************************�ӿں�������************************************/

/*!
  \author        
  \brief        �������ݿ�ĳ�ʼ��
  \param[in]    enIfType: enIfType ���ù�������
  \param[in]    bReInit:  �Ƿ���Ҫ���³�ʼ�������ڴ棬���ǣ���VOS_TRUE
  \return       ����ATP_E_ERR_CFM���͵Ĵ�����
  \retval       ATP_E_ERR_CFM_SHM_NOT_ATTACH ��ʼ�������ڴ�ʧ��
  \ע������:    1����Ҫ����ATP_DBDestroy���ͷŹ����ڴ棻
                2�������ظ�����ATP_AppDataInit����ΪATP_DBInit�л����ATP_AppDataInit��ʼ��AppData�����ڴ�����
                3��ֻ��Ҫ��ϵͳ��ʼ����һ�������е���һ�Σ�
                4��ֻ��mic���̵���ʱ��bReInit��Ҫ��VOS_TRUE���������̵���ʱ���������ΪVOS_FALSE
*/
VOS_UINT32 ATP_DBInit(ATP_CFM_E_IF_TYPE enIfType, VOS_BOOL bReInit);


/*!
  \author        
  \brief        CFM�����ڴ�ж��(ȥ��ʼ��)
  \param[in]
  \return       ����ATP_E_ERR_CFM���͵Ĵ�����
  \retval       ATP_E_ERR_CFM_SHM_NOT_ATTACH ��ʼ�������ڴ�ʧ��
  \ע������:    1��Ҫ��ATP_DBInit���ʹ�ã�
                2���ú�������ҵ����̻����ù��ߵ��ã������ǶϿ��Թ����ڴ�����ӣ�
                   �ú������������ƽ��̵��ã�������ж�ع����ڴ棬ȥ��ʼ��CFM
*/
VOS_UINT32 ATP_DBDestroy(VOS_VOID);


/*!
  \author        
  \brief        �������õ�ǰʹ��CFM API������ù���
  \param[in]    enIfType:  ���ù�������
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    �ýӿڿ���һ�������ж�ε���
*/
VOS_UINT32 ATP_DBSetCurrUser(ATP_CFM_E_IF_TYPE enIfType);


/*!
  \author        
  \brief        ��ȡ��ǰʹ��CFM API������ù�������
  \param[in]
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_DBGetCurrUser(VOS_VOID);


/*!
  \author        
  \brief        ���õ�ǰWeb���ù��߼����û���
  \param[in]    enIfType:       ���ù�������
  \param[in]    pcWebUserName:  ��ǰ�û���
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_DBSetCurrWebUser(ATP_CFM_E_IF_TYPE enIfType, const VOS_CHAR* pcWebUserName);


/*!
  \author        
  \brief        ��ȡ��ǰʹ��CFM API��ʹ�õ�Web�û���
  \param[in]
  \return       ��ǰWeb�û���
  \retval       �û����ַ���
  \ע������:    ��
*/
const VOS_CHAR* ATP_DBGetCurrWebUser();


/*!
  \author        
  \brief        ���ݶ���ID����ȡ���������ֵ
  \param[in]    ulKeyList:      �����ʵ�����б�����Ǽ򵥶��󣬿���Ϊ��
  \param[in]    ulOID:          ����ȡ�����CMO
  \param[out]   ppulObj:        �����ֵ����Ҫͨ��ATP_CFM_FreeObj�ͷ��ڴ�
  \param[out]   pulNumOfParas:  ������ܲ�������
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ���øýӿں�ppulObj�����ж��ڴ棬��ص���ATP_CFM_FreeObj�ͷ��ڴ�
*/
VOS_UINT32 ATP_DBGetObj(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_UINT32 **ppulObj,
    VOS_UINT32 *pulNumOfParas);


/*!
  \author        
  \brief        ���ݶ���ID����ȡDB�������չ�ӿ�
  \param[in]    ulKeyList:      �����ʵ�����б�����Ǽ򵥶��󣬿���Ϊ��
  \param[in]    ulOID:          ����ȡ�����CMO
  \param[in]    bGetOldDB:      �Ƿ��AddSet�б��ȡ��ΪVOS_TRUE���AddSet�б��ȡ
  \param[out]   ppulObj:        �����ֵ����Ҫͨ��ATP_CFM_FreeObj�ͷ��ڴ�
  \param[out]   pulNumOfParas:  ������ܲ�������
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    1�����øýӿں�ppulObj�����ж��ڴ棬��ص���ATP_CFM_FreeObj�ͷ��ڴ棻
                2���ýӿ�Ŀǰ��QOSҵ��·����ģʽcms��ģ��ʹ�ã��������Ƿ�����
                3���ýӿ���ATP_DBGetObj������Ҫ�Ƕ�ȡ�����Ƿ��m_pstAddSetObjList��ȡ
*/
VOS_UINT32 ATP_DBGetObj_Ex(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_UINT32 **ppulObj,
    VOS_UINT32 *pulNumOfParas,
    VOS_BOOL bGetOldDB);


/*!
  \author        
  \brief        ���ݶ������ƶ�ȡDB����
  \param[in]    pcObjName:      �������ƣ����õ�ָ�ʽ
  \param[out]   ppulObj:        �����ֵ����Ҫͨ��ATP_CFM_FreeObj�ͷ��ڴ�
  \param[out]   pulNumOfParas:  ������ܲ�������
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ���øýӿں�ppulObj�����ж��ڴ棬��ص���ATP_CFM_FreeObj�ͷ��ڴ�
*/
VOS_UINT32 ATP_DBGetObjByName(const VOS_CHAR *pcObjName,
    VOS_UINT32 **ppulObj,
    VOS_UINT32 *pulNumOfParas);


/*!
  \author        
  \brief        ͨ��OID�Զ���Ϊ��λ���ö����ֵ
  \param[in]    ulKeyList:      �����ʵ�����б�����Ǽ򵥶��󣬿���Ϊ��
  \param[in]    ulOID:          �����ö����CMO
  \param[in]    pulObj:         �����ö����ֵ
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ���øýӿں���Ҫ����ATP_CFM_FreeObj��ATP_CFM_FreeObjByName�ͷ�pulObj���е��ڴ�
*/
VOS_UINT32 ATP_DBSetObj(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32       ulOID,
    const VOS_UINT32 *pulObj);


/*!
  \author        
  \brief        ͨ��OID�Զ���Ϊ��λ���ö���ֵ����չ�ӿ�
  \param[in]    ulKeyList:      �����ʵ�����б�����Ǽ򵥶��󣬿���Ϊ��
  \param[in]    ulOID:          �����ö����CMO
  \param[in]    pulObj:         �����ö����ֵ
  \param[in]    pulChgParas:    VOS_BOOL���͵����飬��ʶ��ÿ�������Ƿ�ı�
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    1�����øýӿں���Ҫ����ATP_CFM_FreeObj��ATP_CFM_FreeObjByName�ͷ�pulObj���е��ڴ�
                2���ýӿ���ATP_DBSetObjֻ����BUILD_CFM_VOICE_NODE_MAP����ʱ������
                   �������ڱ��ӿڿ���Я��һ��flag���飬���б�ʶ��ÿ�������Ƿ�ı�
*/
VOS_UINT32 ATP_DBSetObjEx(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32       ulOID,
    const VOS_UINT32 *pulObj,
    const VOS_UINT32 *pulChgParas);


/*!
  \author        
  \brief        ���һ��DB����
  \param[in]    ulKeyList:      ����Ӷ����ʵ�����б�
  \param[in]    ulOID:          ����Ӷ����CMO
  \param[in]    pulObjValues:   ���������ֵ
  \param[out]   pulInstanceId:  ���������ʵ����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    1�������ȡ����Ĭ��ֵ����ͨ��ATP_CFM_GetObjDftValue�ӿڻ�ȡ��
                2��������Ӷ���ĸ�������δ�����������ʧ��
                3��ѭ�����øýӿڿ��ܵ���DB�������󣬱���ÿ�ο�����Addһ���ڵ�
*/
VOS_UINT32 ATP_DBAddObj(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    const VOS_UINT32 *pulObjValues,
    VOS_UINT32 *pulInstanceId);


/*!
  \author        
  \brief        ɾ��һ��DB����
  \param[in]    ulKeyList:      �����ʵ�����б�
  \param[in]    ulOID:          ��ɾ�������CMO
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_DBDelObj(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID);


/*!
  \author        
  \brief        ɾ��һ��DB���󣬵������Change Flag���
  \param[in]    ulKeyList:      �����ʵ�����б�
  \param[in]    ulOID:          ��ɾ�������CMO
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    1���ýӿ���ATP_DBDelObj���������ڣ����ӿڲ�����ǣ�
                   ��ֹ�����汾��ڵ㲻����ӣ�
                2���ýӿ�Ŀǰ������ǽcms��ģ��ʹ�ã������ط�δ�õ�
*/
VOS_UINT32 ATP_DBDelObjIgnoreFlag(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH], 
    VOS_UINT32 ulOID);


/*!
  \author        
  \brief        ��ȡָ��ʵ�����б��¶���ĸ���
  \param[in]    ulKeyList:      �����ʵ�����б�����Ϊ�ա�����ǿգ����ʾ����ʵ���ĸ���
  \param[in]    ulOID:          ����ȡ�����CMO
  \param[out]   pulNum:         ��ȡ���Ķ������
  \param[out]   ppulInstArray:  ʵ��������
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ���øýӿں�ppulInstArray�����ж��ڴ棬��Ҫ����ATP_FREE�ͷ��ڴ�
*/
VOS_UINT32 ATP_DBGetNumOfObjs(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_UINT32 *pulNum,
    VOS_UINT32 **ppulInstArray);


/*!
  \author        
  \brief        ������Ż�ȡ����ֵ
  \param[in]    ulKeyList:      �����ʵ�����б�����Ϊ�ա�����ǿգ����ʾ����ʵ���ĸ���
  \param[in]    ulOID:          ����ȡ�����CMO
  \param[in]    ulSeqNum:       ��Ҫ��ȡ�Ķ�����ţ���0��ʼ
  \param[out]   ppulObj:        �����ֵ����Ҫͨ��ATP_CFM_FreeObj�ͷ��ڴ�
  \param[out]   puInstNo:       ����Ķ���ʵ���ţ�����Ϊ��
  \param[out]   pulNumOfParas:  ����Ĳ�������������Ϊ��
  \param[out]   ulNewKeyList:   ���º�Ķ���ʵ�����б�
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ���øýӿں�ppulObj�����ж��ڴ棬��ص���ATP_CFM_FreeObj�ͷ��ڴ�
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
  \brief        ����ʵ�����б�������CMO����ȡ����������ֵ
  \param[in]    ulKeyList:      ������ʵ�����б�����Ǽ򵥶��󣬿���Ϊ��
  \param[in]    ulOID:          �����OID
  \param[out]   pValue:         ����ֵָ��
  \param[in]    ulValueLen:     ����ֵbuff����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    �ýӿ�һ��ֻ�ܻ�ȡһ��������ֵ
*/
VOS_UINT32 ATP_DBGetPara(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_VOID *pValue,
    VOS_UINT32 ulValueLen);


/*!
  \author        
  \brief        ������������ȡ����������ֵ
  \param[in]    pcParaName:     ����������
  \param[out]   pValue:         ����ֵָ��
  \param[in]    ulValueLen:     ����ֵbuff����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    �ýӿ�һ��ֻ�ܻ�ȡһ��������ֵ
*/
VOS_UINT32 ATP_DBGetParaByName(const VOS_CHAR *pcParaName,
    VOS_VOID *pValue,
    VOS_UINT32 ulValueLen);


/*!
  \author        
  \brief        ���ݶ���OID���ö������
  \param[in]    ulKeyList:      ������ʵ�����б�
  \param[in]    ulOID:          �����OID
  \param[in]    pvData:         ���õ����ݡ�����ָ������OID��ֵ������ͬ��
                                ������ַ������͵ģ�ֱ�����ַ���ָ�룻
                                ����ֱ���������ֵ
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_DBSetPara(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    const VOS_VOID *pvData);


/*!
  \author        
  \brief        ���ݶ����������ö������
  \param[in]    pcPara:      ����������
  \param[in]    pvValue:     ���õ����ݡ�����ָ������OID��ֵ������ͬ��
                             ������ַ������͵ģ�ֱ�����ַ���ָ�룻
                             ����ֱ���������ֵ
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_DBSetParaByName(const VOS_CHAR *pcPara, const VOS_VOID *pvValue);


/*!
  \author        
  \brief        ����ָ�ʽ����ת��Ϊʵ�����б��OID������ǰ׺
  \param[in]    pszDomain:      ���������
  \param[out]   ulKeyList:      ������ʵ�����б�
  \param[out]   pulOID:         �����OID
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    �ýӿ���ATP_DBDomainToKeyList���������ڣ����ӿ��ṩ��һ�ָ����Ĵ��η�ʽ��
                ������������ʡ��"InternetGatewayDevice.Device."ǰ׺
*/
VOS_UINT32 ATP_DBDomainToKeyListIgnorePrefix(const VOS_CHAR* pszDomain,
    VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32* pulOID);


/*!
  \author        
  \brief        ����ָ�ʽ����ת��Ϊʵ�����б��OID
  \param[in]    pszDomain:      ���������
  \param[out]   ulKeyList:      ������ʵ�����б�
  \param[out]   pulOID:         �����OID
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_DBDomainToKeyList(const VOS_CHAR* pszDomain,
    VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32* pulOID);


/*!
  \author        
  \brief        ����ָ�ʽ����ת��Ϊʵ�����б��OID�������ʿ��Ʋ��Լ��
  \param[in]    pszDomain:      ���������
  \param[out]   ulKeyList:      ������ʵ�����б�
  \param[out]   pulOID:         �����OID
  \param[in]    bReadAccess:    �Ƿ����д��־λ��VOS_TRUE����ReadBits��������WriteBits
  \param[in]    bAddOperate:    �Ƿ���Add������������ֻ���ReadBits��WriteBits
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    1���ýӿ���ATP_DBDomainToKeyList���������ڣ����ӿڻ���в����ķ��ʿ��Ƽ�飻
                2�����ӿ�Ŀǰ��cwmpģ��һ��ʹ�ã��������Ƿ���
*/
VOS_UINT32 ATP_DBDomainToKeyListWithAccCheck(const VOS_CHAR* pszDomain,
    VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32* pulOID, VOS_BOOL bReadAccess,
    VOS_BOOL bAddOperate);


/*!
  \author        
  \brief        ���ݶ���ʵ�����б��OIDת��Ϊ��ָ�ʽ����
  \param[in]    ulKeyList:      ������ʵ�����б�
  \param[in]    pulOID:         �����OID
  \param[out]   pszDomain:      ���������
  \param[in]    ulDomainLen:    ���������buffer����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_DBKeyListToDomain(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_CHAR* pszDomain,
    VOS_UINT32 ulDomainLen);


/*!
  \author        
  \brief        ���ݶ���ʵ�����б��OIDת��Ϊ��ָ�ʽ��������չ�ӿ�
  \param[in]    ulKeyList:      ������ʵ�����б�
  \param[in]    pulOID:         �����OID
  \param[out]   pszDomain:      ���������
  \param[in]    ulDomainLen:    ���������buffer����
  \param[in]    bDecreaseByOne: �Ƿ�����һλʵ��������һ����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    1���ýӿ���ATP_DBKeyListToDomain���������ڣ����ӿڿ�ѡ������һλʵ���ż�һ��
                2�����ӿڵ�ʵ�ʵ��ý�cfmmsgһ�������������Ż�����
*/
VOS_UINT32 ATP_DBKeyListToDomainEx(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_CHAR* pszDomain,
    VOS_UINT32 ulDomainLen,
    VOS_BOOL  bDecreaseByOne);


/*!
  \author        
  \brief        ���ݶ���OID��ȡ�������
  \param[in]    ulOID:          �����OID
  \return       ������������
  \retval       �޷�������
  \ע������:    ��
*/
VOS_UINT32 ATP_DBGetInstDepthOfOID(VOS_UINT32 ulOID);


/*!
  \author        
  \brief        ����ʵ���ڵ��µ������ƶ�����һ��ͬOID�Ķ�ʵ���ڵ���
  \param[in]    ulSourceKeyList:    Դʵ�����б�
  \param[in]    ulSourceObj:        Դ�����OID
  \param[in]    ulDestKeyList:      Ŀ��ʵ�����б�
  \param[out]   pulNewObjInstId:    �ƶ������ʵ����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_DBObjMove(
    const VOS_UINT32    ulSourceKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32          ulSourceObj,
    const VOS_UINT32    ulDestKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32          *pulNewObjInstId);


/*!
  \author        
  \brief        ���ݲ�������ȡ������OID
  \param[out]   ulObjOID:       �����OID
  \param[in]    pszParaName:    ��ȡ���Ĳ�����
  \return       ���ز�����OID
  \retval       �ɹ�����OID��ʧ�ܷ���0
  \ע������:    �ýӿ�ֻ��web��luaģ��һ��ʹ�ã����ڿ�����ӿڣ��������Ƿ���
*/
VOS_UINT32 ATP_DBGetParaOIDByParaName(VOS_UINT32 ulObjOID, const VOS_CHAR* pszParaName);


/*!
  \author        
  \brief        ����CMO����ȡ�����Ĭ��ֵ
  \param[in]    ulOID:          �����OID
  \param[out]   ppulDftValues:  �����Ĭ��ֵ����Ҫͨ��ATP_Free�ͷ��ڴ�
  \param[out]   pulNumOfParas:  ������ܲ�������
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ���øýӿں�ppulDftValues�����ж��ڴ棬��ص���ATP_Free�ͷ��ڴ�
*/
VOS_UINT32 ATP_DBGetDftObject(VOS_UINT32 ulOID,
    VOS_UINT32 **ppulDftValues,
    VOS_UINT32 *pulNumOfParas);


/*!
  \author        
  \brief        ���ݶ���OID����Ӧ�Ķ�������ָ�ΪĬ��ֵ
  \param[in]    ulKeyList:      ������ʵ�����б�
  \param[in]    pulOID:         �����OID
  \param[in]    bSaveDB:        �Ƿ񱣴浽DB(Ŀǰδʹ��)
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    �ú�������bSaveDB�������������ݿ�Ĳ�����������Щ�����漰Flash������
                ����Ӧ����bSaveDB����
*/
VOS_UINT32 ATP_DBSetDftObject(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_BOOL bSaveDB);


/*!
  \author        
  \brief        ����OID��ȡ������������
  \param[in]    ulOID:          ����������OID
  \return       ���ض�������������
  \retval       �����ַ���
  \ע������:    �ýӿڽ�micһ��ʹ�ã����������Ż�����
*/
const VOS_CHAR *ATP_DBGetNameOfOID(VOS_UINT32 ulOID);


/*!
  \author        
  \brief        ���ݶ���OID��ȡ��������
  \param[in]    ulOID:          �����OID
  \return       ���ض��������
  \retval       �����ַ���
  \ע������:    �ýӿڽ�cfma����ʹ�ã���ATP_DBGetNameOfOID��ȫ�ظ�������Ӧ����
*/
const VOS_CHAR *ATP_DBGetObjNameOfOID(VOS_UINT32 ulOID);


/*!
  \author        
  \brief        ��ǰ��ȡ�����ʵ�����
  \param[in]    ulKeyList:      ������ʵ�����б�
  \param[in]    pulOID:         �����OID
  \param[out]   pulInstId:      ��ȡ���Ķ���ʵ��ID
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    �ýӿڽ�cfmaһ��ʹ�ã����������Ż�����
*/
VOS_UINT32 ATP_DBPreGetObjInstID(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID,
    VOS_UINT32 *pulInstId);


/*!
  \author        
  \brief        ����û��޸���DB����
  \param[in]    
  \return       NA
  \retval       void
  \ע������:    1��ͬ��ʱ����¼�û��޸ļ�¼
                2��ϵͳ����֮��ʶ��ISP�̼���ISPʱ���ܸ����û��޸ĵ�����
*/
VOS_VOID ATP_DBOpenSaveChgFlags();


/*!
  \author        
  \brief        ����û��޸���DB���ݵı��
  \param[in]    
  \return       NA
  \retval       void
  \ע������:    1��ͬ��ʱ����¼�û��޸ļ�¼
                2��ϵͳ����֮��ʶ��ISP�̼���ISPʱ���ܸ����û��޸ĵ�����
*/
VOS_VOID ATP_DBCloseSaveChgFlags();


/*!
  \author        
  \brief        �����Ӫ��(ISP)�޸���DB����
  \param[in]    
  \return       NA
  \retval       void
  \ע������:    1��ͬ��ʱ����¼�û��޸ļ�¼
                2��ϵͳ����֮��ʶ��ISP�̼���ISPʱ���ܸ����û��޸ĵ�����
*/
VOS_VOID ATP_DBOpenChangeISPCfg();


/*********************************CFM������ؽӿ�******************************/

/*!
  \author        
  \brief        ���ݶ���OID��ȡ����
  \param[in]    ulKeyList:      ������ʵ�����б�
  \param[in]    ulOID:          �����OID
  \return       ���������
  \retval       �����ַ���
  \ע������:    1���ýӿ��ڲ�����keylistΪNULL�ĳ�����ȡ���нڵ�ĵ�һ��ʵ����
                2���ýӿڹ�����ATP_DBGetNameOfOID���ƶȺܸߣ������������
*/
VOS_CHAR *ATP_CFM_GetDomainForOID(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH], 
    VOS_UINT32 ulOID);


/*!
  \author        
  \brief        ���ݷ��ʿ����б��ȡ����Ȩ�ޱ�־
  \param[in]    pcAccList:      ���ʿ����б��ַ���
  \return       ���ط���Ȩ�ޱ�־
  \retval       ��pcAccListΪNULL������ATP_CFM_E_IF_TYPE_CWMP_ADMIN��
                ��pcAccListΪ"Subscriber"������usAccessBits��־λ��
                ���򣬷���0
  \ע������:    ��
*/
VOS_UINT32 ATP_CFM_ExtGetAccListItem(const VOS_CHAR *pcAccList);


/*!
  \author        
  \brief        ���ݷ��ʿ���Ȩ�ޱ�ǻ�ȡ���ʿ��������ַ���
  \param[in]    ulAccList:      ���ʿ��Ʊ��
  \param[out]   apcNames:       ���ʿ��������ַ���
                                ��ulAccListΪATP_CFM_E_IF_TYPE_CWMP_ADMIN���򷵻ؿ��ַ�����
                                ���򷵻�"Subscriber"
  \param[in]    ulBufLen:       ���ʿ��������ַ���buffer����
  \return       ����ִ�н��
  \retval       �ɹ�����1��ʧ�ܷ���0
  \ע������:    ��
*/
VOS_UINT32 ATP_CFM_ExtGetAccListStrings(VOS_UINT32 ulAccList, 
    const VOS_CHAR *apcNames[],
    VOS_UINT32 ulBufLen);


/*!
  \author        
  \brief        ���ò������߶��������
  \param[in]    pstSetAttrList: �����б�
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    1��������������Ҫ����TR069�Ĳ����ı��ϱ��ͷ����б���Ϣ��
                2�������ýӿ�Ҫ������ΪATP_CFM_SetAttrOfCMO
*/
VOS_UINT32 ATP_CFM_SetAttrOfCMOEx(ATP_CFM_ATTR_SET_ST *pstSetAttrList);


/*!
  \author        
  \brief        ��ȡ�������߶��������
  \param[in]    ulKeyList:      ������ʵ�����б�
  \param[in]    ulOID:          �����OID
  \param[out]   pstParaAttr:    ����������
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_CFM_GetAttrOfCMO(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32  ulOID,
    ATP_PARA_ATTR_VAL_ST *pstParaAttr);


/*!
  \author        
  \brief        ���ö����HideBits��־λ
  \param[in]    ulKeyList:      ������ʵ�����б�
  \param[in]    ulOID:          �����OID
  \param[in]    ulHideBits:     �����õ�HideBits��־λ
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_CFM_SetHideBitsOfCMO(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32  ulOID,
    VOS_UINT32  ulHideBits);


/*!
  \author        
  \brief        �Ƚ����������ֵ�Ƿ���ͬ
  \param[in]    ulOID:          ����OID�����߶��������������OID
  \param[in]    pulSrcObj:      �Ƚϵĵ�һ�������ֵ
  \param[in]    pulDstObj:      �Ƚϵĵڶ��������ֵ
  \return       �ȽϽ��
  \retval       ��ͬ����VOS_TRUE����ͬ����VOS_FALSE
  \ע������:    pulSrcObj��pulDstObj��Ҫ����ͬ�����ֵ
*/
VOS_BOOL ATP_CFM_CompareObj(VOS_UINT32 ulOID,
    const VOS_UINT32 *pulSrcObj,
    const VOS_UINT32 *pulDstObj);


/*!
  \author        
  \brief        �ͷŶ����ֵ�����е��ڴ�
  \param[in]    ulOID:          ���ͷŶ����OID
  \param[out]   pulObj:         ���ͷŶ���Ľṹ��ָ��
  \return       NA
  \retval       void
  \ע������:    ���ӿ������ͷ�OBJ�ṹ��Ա���ַ������͵��ڴ棬OBJ�ṹ������Ҫ�ⲿ�ͷ�
*/
VOS_VOID ATP_CFM_FreeObj(VOS_UINT32 ulOID, VOS_UINT32 *pulObj);


/*!
  \author        
  \brief        ���������ͷŶ����ֵ�����е��ڴ�
  \param[in]    pcObjName:      ���ͷŶ��������
  \param[out]   pulObj:         ���ͷŶ���Ľṹ��ָ��
  \return       NA
  \retval       void
  \ע������:    ���ӿ������ͷ�OBJ�ṹ��Ա���ַ������͵��ڴ棬OBJ�ṹ������Ҫ�ⲿ�ͷ�
*/
VOS_VOID ATP_CFM_FreeObjByName(const VOS_CHAR *pcObjName, VOS_UINT32 *pulObj);


/*!
  \author        
  \brief        ����һ�������ֵ
  \param[in]    ulOID:          Դ�����OID
  \param[in]    pulSrcObj:      Դ�����ֵ
  \return       ��¡�������¶���ָ��
  \retval       �¶����ָ��
  \ע������:    ���øýӿں󣬷���ֵ������ж��ڴ棬��Ҫʹ��ATP_CFM_FreeObj�ͷ��ڴ�
*/
VOS_UINT32 *ATP_CFM_CopyObj(VOS_UINT32 ulOID, const VOS_UINT32 *pulSrcObj);


/*!
  \author        
  \brief        �޸Ķ������ַ���������ֵ
  \param[in]    ulParaIndex:    ��������
  \param[in]    pulObj:         �����ָ��
  \param[in]    pcNewValue:     �����õ��²���ֵ
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_CFM_SetObjStrValue(VOS_UINT32 ulParaIndex,
    VOS_UINT32 *pulObj,
    const VOS_CHAR *pcNewValue);


/*!
  \author        
  \brief        �޸Ķ��������Ͳ�����ֵ
  \param[in]    ulParaIndex:    ��������
  \param[in]    pulObj:         �����ָ��
  \param[in]    ullNewValue:    �����õ��²���ֵ���޷��ų�����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_CFM_SetObjUintLongValue(VOS_UINT32 ulParaIndex,
    VOS_UINT32 *pulObj,
    const VOS_UINT64 ullNewValue);


/*!
  \author        
  \brief        �Ƚ�����ʵ�����б��Ƿ���ͬ
  \param[in]    ulKeyList1:     ���Ƚϵĵ�һ��ʵ�����б�
  \param[in]    ulKeyList2:     ���Ƚϵĵڶ���ʵ�����б�
  \param[in]    ulCMO:          �����OID
  \return       �ȽϽ��
  \retval       ��ͬ����VOS_TRUE����ͬ����VOS_FALSE
  \ע������:    ��
*/
VOS_BOOL ATP_CFM_IsKeyListSame(const VOS_UINT32 ulKeyList1[ATP_CFM_MAX_TREE_DEPTH],
    const VOS_UINT32 ulKeyList2[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulCMO);


/*!
  \author        
  \brief        �Ƿ���Ҫ֪ͨ���ù��߲����ı�
  \param[in]    ulKeyList:      ������ʵ�����б�
  \param[in]    ulOID:          �����OID
  \return       �����Ƿ���Ҫ֪ͨ
  \retval       ��Ҫnotify�򷵻�VOS_TRUE�����򷵻�VOS_FALSE
  \ע������:    ��
*/
VOS_BOOL ATP_CFM_IsAttrNeedNotify(const VOS_UINT32 ulKeyList[ATP_CFM_MAX_TREE_DEPTH],
    VOS_UINT32 ulOID);


/*!
  \author        
  \brief        ��һ���ַ���ת��Ϊ�޷��ų�����
  \param[in]    pcValue:        ��ת�����ַ���
  \param[out]   pulValue:       ת����ĳ�����
  \return       �Ƿ�ת���ɹ�
  \retval       �ɹ�����VOS_TRUE��ʧ�ܷ���VOS_FALSE
  \ע������:    1���ýӿ���DB�޹أ������Ƶ�msgapi�Ĺ���util�ļ��У�
                2�������ýӿ�Ӧ�ڲ�ʹ�ã�����ֻ��¶ATP_CFM_UtilConvertValueType�ӿ�
*/
VOS_BOOL ATP_CFM_UtilChar2Ulong(const VOS_CHAR *pcValue, VOS_UINT32 *pulValue);


/*!
  \author        
  \brief        ��һ���ַ���ת��Ϊ�з��ų�����
  \param[in]    pcValue:        ��ת�����ַ���
  \param[out]   plValue:        ת����ĳ�����
  \return       �Ƿ�ת���ɹ�
  \retval       �ɹ�����VOS_TRUE��ʧ�ܷ���VOS_FALSE
  \ע������:    1���ýӿ���DB�޹أ������Ƶ�msgapi�Ĺ���util�ļ��У�
                2�������ýӿ�Ӧ�ڲ�ʹ�ã�����ֻ��¶ATP_CFM_UtilConvertValueType�ӿ�
*/
VOS_BOOL ATP_CFM_UtilChar2Long(const VOS_CHAR *pcValue, VOS_INT32 *plValue);


/*!
  \author        
  \brief        ��һ���ַ���ת��Ϊ�޷���long long����
  \param[in]    pcValue:        ��ת�����ַ���
  \param[out]   pulValue:       ת�����ֵ
  \return       �Ƿ�ת���ɹ�
  \retval       �ɹ�����VOS_TRUE��ʧ�ܷ���VOS_FALSE
  \ע������:    1���ýӿ���DB�޹أ������Ƶ�msgapi�Ĺ���util�ļ��У�
                2�������ýӿ�Ӧ�ڲ�ʹ�ã�����ֻ��¶ATP_CFM_UtilConvertValueType�ӿ�
*/
VOS_BOOL ATP_CFM_UtilChar2ULongLong(const VOS_CHAR *pcValue, VOS_UINT64 **pulValue);


/*!
  \author        
  \brief        ��һ���ַ���ת��Ϊ��������
  \param[in]    pcValue:        ��ת�����ַ���
  \param[out]   pvValue:        ת�����ֵ
  \param[in]    ulValueType:    ת��Ϊ�������ͣ���ǰ֧�ֵ�������:
                                CMO_DATA_TYPE_UINT
                                CMO_DATA_TYPE_INT
                                CMO_DATA_TYPE_UINTL
                                CMO_DATA_TYPE_BOOL
  \return       �Ƿ�ת���ɹ�
  \retval       �ɹ�����VOS_TRUE��ʧ�ܷ���VOS_FALSE
  \ע������:    �ýӿ���DB�޹أ������Ƶ�msgapi�Ĺ���util�ļ���
*/
VOS_BOOL ATP_CFM_UtilConvertValueType(const VOS_CHAR *pcValue,
    VOS_VOID    **pvValue,
    VOS_UINT32  ulValueType);


/*!
  \author        
  \brief        �ж�һ��CMO�Ƿ���Ҫ����
  \param[in]    ulCmo:          �����OID
  \return       �����Ƿ���Ҫ����
  \retval       ��Ҫ�򷵻�VOS_TRUE������Ҫ�򷵻�VOS_FALSE
  \ע������:    �ýӿ��ڲ�ά����һ���ֲ�����aulEncodeCmos��������Ҫ���ܵ�CMO����Ҫ���������
*/
VOS_BOOL ATP_CFM_ExtIsCmoNeedEncrypt(VOS_UINT32 ulCmo);


/*
 *  PPPConnection.{i}.X_LowerLayers��ֵ
 *      cwmpҪ��ΪInternetGatewayDevice.X_ATP_VLANTermination.1
 *      web��Ҫ��ΪInternetGatewayDevice.X_VLANTermination.1
 *
 *      ATP_CFM_UtilValueStripExtension���ڰ�X_ATP stripΪX_
 *      ATP_CFM_UtilValueAddExtension  ���ڰ�X_��չΪX_ATP
 */
VOS_CHAR *ATP_CFM_UtilValueStripExtension(VOS_UINT32 ulCmo, const VOS_CHAR *pcValue);
VOS_CHAR *ATP_CFM_UtilValueAddExtension(VOS_UINT32 ulCmo, const VOS_CHAR *pcValue);
VOS_CHAR *ATP_CFM_UtilValueStripExtensionEx(VOS_UINT32 ulCmo, const VOS_CHAR *pcValue, VOS_BOOL bForce);
VOS_CHAR *ATP_CFM_UtilValueAddExtensionEx(VOS_UINT32 ulCmo, const VOS_CHAR *pcValue, VOS_BOOL bForce);


/*********************************ȫ�ֱ���*************************************/
extern ATP_THREAD_SAFE VOS_UINT32 g_ulCfmErr;               //����cfmΨһ�Ĵ������¼
extern const VOS_UINT32 g_aulRecycleOids[];                 //ѭ������OID
extern const VOS_CHAR *g_apcNameExtensions[];               //CMO������չ����Ա������atpconfig.h
extern const VOS_UINT16 g_usHidePwdCfgTools;                //������������ù���
extern VOS_BOOL g_bCheckSetPara;                            //�����Ƿ�������̨У�飬Ĭ��Ϊ����У��
extern PFCfmEndParseHook g_pfEndParseHook;                  //CFM����������Ļص�����
extern const ATP_CFM_AliasDomian_ST g_pstAliasDomianList[]; //Domain�����б�
extern const VOS_UINT32 g_aulEncodeCmos[];                  //��Ҫ���ܱ��봦���CMO�ڵ�
extern const VOS_UINT32 g_aulValueWithExtension[];          //����չ����CMO�ڵ�ֵ


/*********************************��Ƕͷ�ļ�����*******************************/
#include "appdataapi.h"
#include "shmemapi.h"
#include "flagapi.h"


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
