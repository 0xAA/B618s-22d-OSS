/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file cfmdbapi.h
  *
  *\copyright 2017-2030����Ϊ�������޹�˾
  *\author 
  *\date  2017-6-12
*/
#ifndef __ATP_CFMDB_API_H__
#define __ATP_CFMDB_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*********************************************************************************************
  author      
  brief      �������ݿ�
  param[in]  *pcFile: ��ӡ����ǰ�����ߵ��ļ���
  param[in]  ulLine: ��ӡ����ǰ�����ߵ��ļ�����
  param[in]  *pcFunction: ��ӡ����ǰ�����ߵĺ�����
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_DBSaveFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      �������ݿ�
  param[in]
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
#define ATP_DBSave(...)  ATP_DBSaveFunc(__FILE__, __LINE__, __func__)

/*********************************************************************************************
  author      
  brief      �����������ݿ�
  param[in]  *pcFile: ��ӡ����ǰ�����ߵ��ļ���
  param[in]  ulLine: ��ӡ����ǰ�����ߵ��ļ�����
  param[in]  *pcFunction: ��ӡ����ǰ�����ߵĺ�����
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_DBSaveSyncFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      �����������ݿ�
  param[in]
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
#define ATP_DBSaveSync(...) ATP_DBSaveSyncFunc(__FILE__, __LINE__, __func__)


/*********************************************************************************************
  author      
  brief      �������õ�APPDATA
  param[in]  *pcFile: ��ӡ����ǰ�����ߵ��ļ���
  param[in]  ulLine: ��ӡ����ǰ�����ߵ��ļ�����
  param[in]  *pcFunction: ��ӡ����ǰ�����ߵĺ�����
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/

VOS_UINT32 ATP_DBSaveToAppFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      �������õ�APPDATA
  param[in]  
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
#define ATP_DBSaveToApp(...)  ATP_DBSaveToAppFunc(__FILE__, __LINE__, __func__)

/*********************************************************************************************
  author      
  brief      �����������õ�APPDATA
  param[in]  *pcFile: ��ӡ����ǰ�����ߵ��ļ���
  param[in]  ulLine: ��ӡ����ǰ�����ߵ��ļ�����
  param[in]  *pcFunction: ��ӡ����ǰ�����ߵĺ�����
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_DBSaveToAppSyncFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      �����������õ�APPDATA
  param[in]  
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
#define ATP_DBSaveToAppSync(...) ATP_DBSaveToAppSyncFunc(__FILE__, __LINE__, __func__)

/*********************************************************************************************
  author      
  brief      ��������APPDATA
  param[in]  *pcFile: ��ӡ����ǰ�����ߵ��ļ���
  param[in]  ulLine: ��ӡ����ǰ�����ߵ��ļ�����
  param[in]  *pcFunction: ��ӡ����ǰ�����ߵĺ�����
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_AppSaveSyncFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      ��������APPDATA
  param[in]  
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����FLASH��д�������ƣ�������Ƶ�����ô˺���
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
#define ATP_AppSaveSync(...) ATP_AppSaveSyncFunc(__FILE__, __LINE__, __func__)
/*********************************************************************************************
  author      
  brief      У�������ļ��Ƿ�Ϸ�
  param[in]  *pcFileName:�����ļ�·��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_DBCheckFile(const VOS_CHAR *pcFileName);
/*********************************************************************************************
  author      
  brief      �������ܺ�������ļ�
  param[in]  *pcTargetFileName:�����ļ�·��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_CFM_ExtExportEncryptedCfgFile(const VOS_CHAR *pcTargetFileName);
/*********************************************************************************************
  author      
  brief      �������ù��ߵ������ܺ�������ļ�
  param[in]  *pcTargetFileName:�����ļ�·��
  param[in]  enIfType:���ù���
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_CFM_ExtExportEncCfgFileByUser(const VOS_CHAR *pcTargetFileName, ATP_CFM_E_IF_TYPE enIfType);
/*********************************************************************************************
  author      
  brief      ����Flash���򵼳������ļ�
  param[in]  *pcTargetFileName:�����ļ�·��
  param[in]  flashArea:Flash����
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_CFM_ExportFlashCfgFile(VOS_UINT32 flashArea, const VOS_CHAR *pcTargetFileName);
/*********************************************************************************************
  author      
  brief      ������ܺ�������ļ�
  param[in]  *pcFileName:�����ļ�·��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_CFM_ExtImportEncryptedCfgFile(const VOS_CHAR *pcFileName);


#ifdef __cplusplus
#if __cplusplus
}
#endif 
#endif


#endif

