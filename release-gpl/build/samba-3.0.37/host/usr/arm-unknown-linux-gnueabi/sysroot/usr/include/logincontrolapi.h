/******************************************************************************
  *         ��Ȩ���� (C), 2001-2020, ��Ϊ�������޹�˾
*******************************************************************************/
#ifndef __LOGINCONTROLAPI_H__
#define __LOGINCONTROLAPI_H__

#include "atptypes.h"
#include "msgapi.h"


typedef enum tagATP_LOGINCTRLAPI_ERR_CODE_EN
{
    ATP_ERR_LOGINCTRLAPI_INVALID_PARA = ATP_MNT_ERR_CODE_DEF(ATP_TEAM_MNT, ATP_MODULE_LIBLOGINCONTROLAPI), 
    ATP_ERR_LOGINCTRLAPI_NO_RESPONSE,    
} ATP_LOGINCTRLAPI_ERR_CODE_EN;


enum ATP_LCTRLAPI_MSGTYPES_EN
{
    ATP_MSG_LCTRLAPI_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_LIBLOGINCONTROLAPI), // = 0x2CF00 = 184064

    /* ��¼У�鲢��¼ */
    ATP_MSG_LCTRLAPI_LOGIN, 
    /* ���ж� */
    ATP_MSG_LCTRLAPI_CHECK,
    /* ���ò��� */
    ATP_MSG_LCTRLAPI_SET_MAXFAILEDTIMES,
    /* ���forbidden�б� */
    ATP_MSG_LCTRLAPI_CLEAR_FORBID_LIST,
    /* ��ȡ���������������� */
    ATP_MSG_LCTRLAPI_GET_TOTAL_FORBID_ROUND,
};


/*!< У���ҵ�� */
typedef enum tag_atp_sctrl_service_type_en
{
    ATP_SCTRL_SERVICE_FTP = 0,
    ATP_SCTRL_SERVICE_SAMBA,
    ATP_SCTRL_SERVICE_WEB,
    ATP_SCTRL_SERVICE_CWMP,
    ATP_SCTRL_SERVICE_UPNP,
    ATP_SCTRL_SERVICE_TELNET,
    ATP_SCTRL_SERVICE_CLI,
    ATP_SCTRL_SERVICE_SSH,
    ATP_SCTRL_SERVICE_CABINET,
    ATP_SCTRL_SERVICE_TEST,    
}ATP_SCTRL_SERVICE_TYPE_EN;


/*!< ��¼��Ϣ�ṹ�� */
typedef struct tag_atp_sctrl_login_info_st
{
    ATP_SCTRL_SERVICE_TYPE_EN enService;
    VOS_CHAR    acIPAddress[64];
    VOS_CHAR    acUsername[64];
    VOS_BOOL    bSuccess;
}ATP_SCTRL_LOGIN_INFO_ST;

typedef enum
{
    ATP_SCTRL_LOGIN_RET_SUCCESS = 0,    /* ��¼�ɹ�,��ʱulErrorTimes��ulMaxFailTimes��Ч */
    ATP_SCTRL_LOGIN_RET_FORBIDDEN,      /* ����ֹ,��ʱulErrorTimes��ulMaxFailTimes��Ч */
    ATP_SCTRL_LOGIN_RET_FULL,           /* ������,��ʱulErrorTimes��ulMaxFailTimes��Ч */
    ATP_SCTRL_LOGIN_RET_OTHER,          /* ��������,�粻֧�ֵ�ҵ�� */
    ATP_SCTRL_LOGIN_RET_CONTROL,        /* ���ڽ����ڼ䣬���µ�½��forbidden�������ǽ����ڼ���˺ż��ʧ�ܳ����� */
}ATP_SCTRL_LOGIN_RET_EN;

/*!< ��¼����ṹ�� */
typedef struct tag_atp_sctrl_login_ret_st
{
    VOS_UINT32    ulErrorTimes;         /* �ܴ������ */
    VOS_UINT32    ulMaxFailTimes;       /* ÿ�����ʧ�ܴ��� */
    ATP_SCTRL_LOGIN_RET_EN    enRet;    /* �������� */
    ATP_SCTRL_LOGIN_RET_EN    enForbiddenType;    /* ��ֹ���� */
}ATP_SCTRL_LOGIN_RET_ST;


typedef struct tag_atp_sctrl_maxfailedtimes_set_st
{
    ATP_SCTRL_SERVICE_TYPE_EN enService;
    VOS_UINT32 ulMaxFailedTimes;
}ATP_SCTRL_LOGIN_MAXFAILEDTIMES_SET_ST;


/* ��ѯ�������� */
typedef struct tag_atp_sctrl_totalfailedround_st
{
    ATP_SCTRL_SERVICE_TYPE_EN enService;    //ҵ������
    VOS_BOOL bGet;                              //�Ƿ��ȡ
    VOS_BOOL bClear;                            //�Ƿ��ȡ�����
}ATP_SCTRL_LOGIN_TOTALFAILEDROUND_ST;


/* ��ȡ����������������            */
typedef enum
{
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_NONE = 0,          /* �� */
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_SUCCESS,           /* ��ȡ�ɹ� */
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_NOTEXIST,          /* ҵ�񲻴��� */
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_INTERNAL,          /* �ڲ����� */
}ATP_SCTRL_LOGIN_FAILEDROUND_RET_EN;

/* ��ѯ����������� */
typedef struct tag_atp_sctrl_totalfailedround_ret_st
{
    ATP_SCTRL_LOGIN_FAILEDROUND_RET_EN enRet;          //������
    VOS_UINT32 ulTotalFailedRound;                     //��������
}ATP_SCTRL_LOGIN_TOTALFAILEDROUND_RET_ST;


/*!< У��ʱ�ص��ýṹ�� */
typedef struct tag_atp_sctrl_check_user_st
{
    VOS_CHAR    acUsername[66];
    VOS_CHAR    acIPAddress[64];
    ATP_SCTRL_SERVICE_TYPE_EN enService;
    VOS_INT32   lPid;
    VOS_BOOL    bIn;
    VOS_BOOL    bRemote;
    VOS_BOOL    bSuccess;
    VOS_UINT32  ulCheckMask; 
    VOS_UINT32  stTime;
}ATP_SCTRL_CHECK_USER_ST;


#if defined(__cplusplus)
extern "C"
{
#endif

/*!
  \ 
  \brief         ��¼У��,����¼��Ϣ
  \param[in]  pstLoginInfo: 
  \param[in]  pstLoginRet: 
  \return 
  \retval ERROR_CODE ������˵��
*/
extern VOS_UINT32 ATP_LCTRLAPI_Login(ATP_SCTRL_LOGIN_INFO_ST* pstLoginInfo, ATP_SCTRL_LOGIN_RET_ST* pstLoginRet);


/*!
  \ 
  \brief         ��¼У��,����̽
  \param[in]  pstLoginInfo: 
  \param[in]  pstLoginRet: 
  \return 
  \retval ERROR_CODE ������˵��
*/
extern VOS_UINT32 ATP_LCTRLAPI_Check(ATP_SCTRL_LOGIN_INFO_ST* pstLoginInfo, ATP_SCTRL_LOGIN_RET_ST* pstLoginRet);


/* ��Сʧ�ܴ������ */
#define ATP_SCTRL_MIN_MAX_FAILED_TIMES  (3)

/*!
  \ 
  \brief         �޸�ָ��ģ������������
  \param[in]  ulMaxFailedTimes: 
  \param[in]  enService: 
  \return 
  \retval ERROR_CODE ������˵��
*/
extern VOS_UINT32 ATP_LCTRLAPI_SetMaxFailedTimes(ATP_SCTRL_LOGIN_MAXFAILEDTIMES_SET_ST* pstMaxFailedPara);


/*!
  \ 
  \brief       ����ض�ģ��Ķ�ʱ������Ϣ��Ŀǰ��Ҫ���ڼٹػ�ʱ�����½ʧ�ܺ�һ��ʱ���ڲ������½�Ķ�ʱ����
  \param[in]   enService: ����������͵�forbidden�б�
  \return      void
  \retval ERROR_CODE ������˵��
*/
extern VOS_VOID ATP_LCTRLAPI_ClearForbiddenList(ATP_SCTRL_SERVICE_TYPE_EN enService);


/*****************************************************************
Parameters    :  pstSettings    ҵ�񣬻�ȡ�����
                 pstRet         ����������ҵ�������
Return        :  ��ȡ��Ϣ�Ĵ�����
Description   :  ��ȡָ��ҵ��ķ������ƽ�����������֧�����
Note          :  ֧����գ�����Ҫע����ǣ�һ����գ�����ģ��ͨ���ýӿڻ�ȡ������ʵ��Ҳ�������
*****************************************************************/
extern VOS_UINT32 ATP_LCTRLAPI_GetForbiddenRound(ATP_SCTRL_LOGIN_TOTALFAILEDROUND_ST *pstSettings, ATP_SCTRL_LOGIN_TOTALFAILEDROUND_RET_ST* pstRet);

#if defined(__cplusplus)
}
#endif
    
#endif


