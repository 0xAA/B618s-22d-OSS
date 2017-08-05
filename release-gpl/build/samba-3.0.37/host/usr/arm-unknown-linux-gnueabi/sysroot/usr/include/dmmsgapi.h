/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file dmmsgapi.h
  *
  *\copyright 2017-2030����Ϊ�������޹�˾
  *\author  
  *\date  2017-6-12

*/
#ifndef __ATP_DMMSG_API_H__
#define __ATP_DMMSG_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif 

// For DM Message
typedef struct tagATP_DMMSG_HEAD
{
    VOS_UINT32          ulMagicNum;      // ħ����
    VOS_UINT32          ulAllSize;       // ��Ϣ���ܴ�С
    VOS_UINT32          ulFreeSize;      // ��Ϣ��ʣ��ռ�
    VOS_UINT32          ulErrCode;       // ������
    VOS_UINT32          ulIntfType;      // ���ù�������
    VOS_UINT32          ulMsgSubCode;   // ���ò�����
} ATP_DMMSG_HEAD;

typedef struct tagATP_DMMSG_ITEM
{
    VOS_UINT32          ulIdentity;
    VOS_UINT32          ulNameLen;
    VOS_UINT32          ulValueLen;
    const VOS_CHAR      *pcName;
    const VOS_CHAR      *pcValue;
} ATP_DMMSG_ITEM;

typedef enum tagATP_DMMSG_TYPE_EN
{
    ATP_DMMSG_TYPE_UNKNOWN,
    ATP_DMMSG_GET_NAMES,
    ATP_DMMSG_GET_VALUES,
    ATP_DMMSG_GET_ATTRS,
    ATP_DMMSG_SET_VALUES,
    ATP_DMMSG_SET_ATTRS,
    ATP_DMMSG_ADD_OBJ,
    ATP_DMMSG_DEL_OBJ,
    ATP_DMMSG_REBOOT,
    ATP_DMMSG_RESET,
    ATP_DMMSG_DOWNLOAD,
    ATP_DMMSG_UPLOAD,
    ATP_DMMSG_GET_DEVICE_STATUS,
    ATP_DMMSG_GET_DOWNLOAD_STATUS,
    //...
    ATP_DMMSG_CONFIG_SERVICE,
    ATP_DMMSG_GET_DEVICE_INFO,                  //��ȡ�豸�İ汾����Ϣ,����ҵ���Զ����ź�����
    ATP_DMMSG_GET_DATAMODELS,
    ATP_DMMSG_GET_PARAMETERS,
} ATP_DMMSG_TYPE_EN;
/*********************************************************************************************
   
  brief      ����DMMSG
  param[out] **ppvDMMsg:������DMMSG
  param[in]  *pcRecvAp:���ս�����
  param[in]  ulSubType:DM��Ϣ����
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� �˺��������ڴ���䣬ʹ�����֮����Ҫ�ͷ�
  retval   ATP_E_ERR_CFM_PARA_INVALID:����������
           ATP_E_ERR_CFM_INTERNAL:�ڴ治����mallocʧ��
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_Builder(VOS_VOID **ppvDMMsg, const VOS_CHAR *pcRecvApp, VOS_UINT32 ulSubType);
/*********************************************************************************************
   
  brief      ��DMMSG�����NV��
  param[out] **ppvDMMsg:��������ݵ�DMMSG
  param[in]  ulIdentity:���ձ�ʶ��
  param[in]  pcName:������ݵ�����
  param[in]  pvValue:������ݵ�ֵ
  param[in]  ulValueLength:������ݵĳ���
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� �˺��������ڴ���䣬ʹ�����֮����Ҫ�ͷ�
  retval   ATP_E_ERR_CFM_PARA_INVALID:����������
           ATP_E_ERR_CFM_MEM:�ڴ治����mallocʧ��
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_AppendItem(VOS_VOID **ppvDMMsg, VOS_UINT32 ulIdentity,
                            const VOS_CHAR *pcName, const VOS_VOID *pvValue, VOS_UINT32 ulValueLength);
/*********************************************************************************************
   
  brief      ��ȡ��Ϣ������
  param[in]  *pvDMMsg:��Ϣ�ṹ��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_DMMSG_TYPE_UNKNOWN:����������
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_GetErrCode(const VOS_VOID *pvDMMsg);
/*********************************************************************************************
   
  brief      ��ȡ��ϢSubType
  param[in]  *pvDMMsg:��Ϣ�ṹ��
  return     ��ϢSubType:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_DMMSG_TYPE_UNKNOWN:����������
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_GetSubType(const VOS_VOID *pvDMMsg);
/*********************************************************************************************
   
  brief      ��ȡ��ϢSubType
  param[in]  *pvDMMsg:��Ϣ�ṹ��
  param[out] *pstItem:��ȡ����Item�ṹ��
  param[in]  **ppvPos:��Ҫ��ȡ��Item��λ��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_E_ERR_CFM_PARA_INVALID:����������
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_GetItem(const VOS_VOID *pvDMMsg, ATP_DMMSG_ITEM *pstItem, VOS_VOID **ppvPos);
/*********************************************************************************************
   
  brief      �ͷ�DMMsg
  param[in]  *pvDMMsg:��Ϣ�ṹ��
  return     
  
   ע����� 
1�� ����
  retval   
***********************************************************************************************/
VOS_VOID ATP_DMMSG_Free(VOS_VOID *pvDMMsg);
/*********************************************************************************************
   
  brief      ����DMMsg
  param[in]  *pvDMMsg:��Ϣ�ṹ��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_E_ERR_CFM_PARA_INVALID:����������
           ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_Send(VOS_VOID *pvDMMsg);
/*********************************************************************************************
   
  brief      ͬ������DMMsg
  param[in]  *pvDMMsg:��Ϣ�ṹ��
  param[out] **ppvRespMsg:���ص���Ϣ�ṹ��
  param[in]  ulTimeout:��ʱʱ��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ��Ӧ����Ϣ�����ڴ���䣬ʹ�����֮����Ҫ�ͷ�
  retval   ATP_E_ERR_CFM_PARA_INVALID:����������
           ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
           ATP_E_ERR_CFM_MSG_TYPE:�ظ���Ϣ��ħ�����뷢�͵Ĳ�ƥ��
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_SyncSend(VOS_VOID *pvDMMsg, VOS_VOID **ppvRespMsg, VOS_UINT32 ulTimeout);
/*********************************************************************************************
   
  brief      ��ӦDMMsg��Ϣ�ķ�����
  param[in]  *pvDMMsg:��Ϣ�ṹ��
  param[in]  ulErrCode:��Ϣ������
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_E_ERR_CFM_PARA_INVALID:����������
           ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
           ATP_E_ERR_CFM_MSG_TYPE:�ظ���Ϣ��ħ�����뷢�͵Ĳ�ƥ��
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_ReplyRetCode(VOS_VOID *pvDMMsg, VOS_UINT32 ulErrCode);
/*********************************************************************************************
   
  brief      ��ӦDMMsg��Ϣ
  param[in]  *pvDMMsg:��Ϣ�ṹ��
  param[in]  ulErrCode:��Ϣ������
  param[in]  *pvRespDMMsg:��Ӧ��Ϣ�ṹ��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_E_ERR_CFM_PARA_INVALID:����������
           ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
           ATP_E_ERR_CFM_MSG_TYPE:�ظ���Ϣ��ħ�����뷢�͵Ĳ�ƥ��
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_Reply(VOS_VOID *pvDMMsg, VOS_UINT32 ulErrCode, VOS_VOID *pvRespDMMsg);
/*********************************************************************************************
   
  brief      ��ӦDMMsg��Ϣ
  param[in]  *pcDstApp:��Ӧ��Ϣ�ṹ��
  param[in]  ulErrCode:��Ϣ������
  param[in]  *pvRespDMMsg:��Ӧ��Ϣ�ṹ��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval   ATP_E_ERR_CFM_PARA_INVALID:����������
           ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
           ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
           ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
           ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
           ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
           ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
           ATP_E_ERR_CFM_MSG_TYPE:�ظ���Ϣ��ħ�����뷢�͵Ĳ�ƥ��
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_ReplyEx(const VOS_CHAR *pcDstApp, VOS_UINT32 ulErrCode, VOS_VOID *pvRespDMMsg);

#ifdef ATP_DEBUG
/*********************************************************************************************
   
  brief      ��ӡDMMsg��Ϣ
  param[in]  *pvDMMsg:��Ϣ�ṹ��
  return     
  
   ע����� 
1�� ���ڰ�ȫ���ǣ�debug�汾�ſ��Դ�ӡ������ȥ�˹ؼ���Ϣ
  retval   
***********************************************************************************************/
VOS_VOID ATP_DMMSG_Print(VOS_VOID *pvDMMsg);
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif


