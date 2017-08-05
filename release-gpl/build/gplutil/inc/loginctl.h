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

#ifndef __LOGINCTL_H__
#define __LOGINCTL_H__
#include "atptypes.h"
#include "logincontrolapi.h"

#define LOGIN_OK	0
#define LOGIN_FAIL	1

#define LOGIN_VALID		1
#define LOGIN_INVALID		0

//#define LOGIN_DEBUG

#ifdef LOGIN_DEBUG
#define LoginDebugPrint(format, args...)       do{printf("FILE: %s FUNC: %s LINE: %d: ", __FILE__,__FUNCTION__, __LINE__);printf(format, ##args);}while(0)
#else
#define LoginDebugPrint(format, args...) 	
#endif

/*!< ��¼���ؽ�� */
typedef enum ATP_LOGINRET_EN    
{
    ATP_LOGINRET_OK        	= 0,                  /*!<  ��ʾ���û��ɼ�����¼*/
    ATP_LOGINRET_LOGINED,                      /*!< ��ʾ���û��Ѿ���¼�� */
    ATP_LOGINRET_TOOMANY_FAIL,          /*!<  ��ʾ��ǰ�û���¼ʧ�ܴ����Ѿ��������ƴ��� */
    ATP_LOGINRET_EXISTED,                      /*!< ��ʾͬһ���û�ͬһ���ն��Ѿ���¼��һ�� */
    
    ATP_LOGINRET_INNORMAL,                   /*!<  ��ʾ���������� */
    ATP_LOGINRET_END,
} ATP_LOGINRET_EN;

#define ATP_LOGINTYPE_REMOTE    0x8000

typedef enum ATP_LOGINTYPE_EN
{
    ATP_LOGINTYPE_NONE        	= 0,        /*!< δ֪��¼��ʽ */
    ATP_LOGINTYPE_FTP,             		     /*!< ͨ��FTP ��¼ */
    ATP_LOGINTYPE_SAMBA,          	     /*!< ͨ��SAMBA ��¼ */
    ATP_LOGINTYPE_FTPTIMEOUT,            /*!< ͨ��FTP ��¼��ʱ�� */

    ATP_LOGINTYPE_END = 0x7FFF
} ATP_LOGINTYPE_EN;

#ifdef SUPPORT_ATP_FTP_ACCESS_CONTROL
typedef enum ATP_FTPTYPE_EN
{
    ATP_FTPTYPE_NONE        	= 0,         /*!< δ֪��¼��ʽ */
    ATP_FTPTYPE_FTPNORMAL,          /*!< δ����FTP���� */
    ATP_FTPTYPE_FTPSEXPLICIT,       /*!< ��ʾ����FTP���� */
    ATP_FTPTYPE_FTPSIMPLICIT,      /*!< ��ʽ����FTP���� */

    ATP_FTPTYPE_END
} ATP_FTPTYPE_EN;

typedef enum ATP_FROMTYPE_EN
{
    ATP_FROMTYPE_WAN        	= 0,  /*!<  wan������� */
    ATP_FROMTYPE_LAN,                      /*!<  lan������� */
    ATP_FROMTYPE_END
} ATP_FROMTYPE_EN;
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifdef SUPPORT_ATP_USBSTORAGE

/*!
  \brief ��ʼ����¼����ģ��, ��ʼ��ȫ�ֱ�����������¼ģ�����õ�Ŀ¼
  \param[in]  ulLogType:��¼���ƵĽ�������
  \return 
  \retval VOS_OK   �ɹ�
             VOS_ERROR  ʧ��
*/

VOS_UINT32 ATP_LoginCtlInit(VOS_UINT32 ulLogType);
/*!
  \brief ���ݴ�FTP/SMB ������û���¼��Ϣ���жϸ��û�Ŀǰ�Ƿ�ɺϷ���¼,������Ӧ��Ϣд���¼�ļ�LOGIN_FILE ��
  \param[in]  *pszUsername: �û���
  \param[in]  *pszIpAddr: ��¼�ն˵�IP ��ַ
  \param[in]  ulLogType: ��¼��ʽ, FTP/SMB
  \param[in]  ulLogStatus: ��¼״̬, �ɹ�LOGIN_OK / ʧ��LOGIN_FAIL
  \return 
  \retval ATP_LOGINRET_OK        	             //��ʾ���û��ɼ�����¼
    	    ATP_LOGINRET_LOGINED            //��ʾ���û��Ѿ���¼��
     	    ATP_LOGINRET_FAIL_EXD           //��ʾ��ǰ�û���¼ʧ�ܴ����Ѿ��������ƴ���
            ATP_LOGINRET_EXISTED,            //��ʾͬһ���û�ͬһ���ն��Ѿ���¼��һ��
     	    ATP_LOGINRET_INNORMAL          //��ʾ����������
  			     
*/

ATP_SCTRL_LOGIN_RET_EN ATP_LoginCtlCheck(const VOS_CHAR *pszUsername ,const VOS_CHAR *pszIpAddr ,VOS_UINT32 ulLogType , 
                                                                VOS_UINT ulLogStatus);
/*!
  \brief �û��ǳ�, ����û��Ѿ�������ǳ�ʱ����û���ص�������Ϣ
  \param[in]  *pszUsername: �û���
  \param[in]  *pszAddrInfo: ��¼�ն˵�IP ��ַ
  \param[in]  ulLogintype: ��¼��ʽ, FTP/SMB
  \return 
  \retval VOS_OK �ɹ�
             VOS_ERROR ʧ��
*/

VOS_INT32 ATP_LoginCtlLogout(const VOS_CHAR *pszUsername , const VOS_CHAR *pszAddrInfo,VOS_UINT32 ulLogintype);
/*!
  \brief �ж�һ��ָ���û��Ƿ����ͨ��WAN�����,��Ҫ�õ������ļ�/var/ftp/ftpwanacc
  \param[in]  *pszUsername: �û���
  \param[in]  ulLogintype: ��¼��ʽ,Ŀǰδ��
  \return 
  \retval VOS_OK ���û�����ͨ��WAN�����
             VOS_ERROR �����쳣,���ļ�/var/ftp/ftpwanacc ������
  	     VOS_NOK ���û�����ͨ��WAN�����
*/

VOS_INT32 ATP_LoginCtlAllowWanAcc(const VOS_CHAR *pszUsername , VOS_UINT32 ulLogintype);

#ifdef SUPPORT_ATP_FTP_ACCESS_CONTROL
/*!
  \brief  ����FTP ���ͺ����������͵��жϴ������Ƿ���Խ���
  \param[in]  *pszUsername: 
  \param[in]  ulFtpType: 
  \param[in]  ulFromType: 
  \return 
  \retval VOS_OK �����ӿ��Խ���
  	    VOS_NOK�����Ӳ����Խ���
*/

VOS_INT32 ATP_LoginCtlCheckFtpAcc(const VOS_CHAR *pszUsername, VOS_UINT32 ulFtpType,VOS_UINT32 ulFromType);
#endif
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */



#endif  //end #ifndef __LOGINCTL_H__


