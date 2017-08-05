/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
#ifndef __ATP_FILE_UTIL_H__
#define __ATP_FILE_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*
 *  File operation utilities
 */
/*********************************************************************************************
   
  brief      �ļ����뻺��
  param[in]  *pcFileName: ��ȡ���ļ�����
  param[out] **ppcContent: �ļ����ݴ����bufָ��
  param[in]  *pulLen: ��ȡ���ļ����ݳ���
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� �˺�������VOS_OK��ʱ������ڴ����룬��ʹ�����֮����Ҫ�ͷ�*ppcContent�Ŀռ䡣
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_FILE_NOT_EXIST:�ļ�������
          ATP_MSG_RET_MEM_ERR:�ڴ治��
          ATP_MSG_RET_INTERNAL_ERR:�ļ����ȶ�ȡ����
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ReadFileToBuf(const VOS_CHAR *pcFileName, VOS_CHAR **ppcContent, VOS_UINT32 *pulLen);

/*********************************************************************************************
   
  brief      ��ȡ�ļ��ĳ���
  param[in]  *pcFileName: ��ȡ���ļ�����
  return     >=0���ļ���С
             -1������
   ע����� 
1�� ����
  retval  
***********************************************************************************************/
VOS_INT32 ATP_UTIL_FileTell(const VOS_CHAR* pcFileName);
/*********************************************************************************************
   
  brief      ��ȡ�����ļ�����
  param[in]  *pcFileName: ��ȡ���ļ�����
  param[in]  *pcContent: �ļ����ݴ���ڴ�
  param[in]  *pulLen: ��ȡ�ļ�����
  param[in]  ulMaxLen: ��ȡ�ļ���󳤶�
  param[in]  ulOffset: ��ȡ�ļ�ƫ����
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� �˺����ڲ�û���ڴ���䣬��ȡ���ݴ���ڴ���Ҫ�ڵ��õĵط���ǰ�����
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_FILE_NOT_EXIST:�ļ�������
          ATP_MSG_RET_MEM_ERR:�ڴ治��
          ATP_MSG_RET_INTERNAL_ERR:�ļ����ȶ�ȡ����
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ReadPartFile(const VOS_CHAR *pcFileName, VOS_CHAR *pcContent, VOS_UINT32* pulLen,
    const VOS_UINT32 ulMaxLen, const VOS_UINT32 ulOffset);
/*********************************************************************************************
   
  brief      ����д���ļ�
  param[in]  *pcContent: ��д�뻺����Ϣ
  param[in]  ulLen: ��д��ĳ���
  param[in]  *pcFileName: ��д����ļ���
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� �����������ڴ���䣬�������֮����Ҫ�ͷŻ���
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_FILE_NOT_EXIST:�ļ�������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_WriteBufToFile(const VOS_CHAR *pcContent, VOS_UINT32 ulLen, const VOS_CHAR *pcFileName);

/*********************************************************************************************
   
  brief      �ļ����뻺��
  param[out] **ppcContent: �������ļ����ݻ���
  param[out] *pulLen: д�뻺�泤��
  param[in]  *pcFileName: ����ȡ���ļ���
  param[in]  uloffset: ���ļ�����ʼλ��
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� �����������ڴ���䣬�������֮����Ҫ�ͷŻ���
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_FILE_NOT_EXIST:�ļ�������
          ATP_MSG_RET_MEM_ERR:�ڴ治��
          ATP_MSG_RET_INTERNAL_ERR:�ļ����ȶ�ȡ����
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ReadFileToBuf_Ex(const VOS_CHAR *pcFileName
    , VOS_CHAR **ppcContent, VOS_UINT32 *pulLen, const VOS_UINT32 uloffset);

/*********************************************************************************************
   
  brief      ����ͬ��д���ļ�
  param[in]  *pcContent: ��д�뻺����Ϣ
  param[in]  ulLen: ��д��ĳ���
  param[in]  *pcFileName: ��д����ļ���
  param[in]  uloffset: д���ļ�����ʼλ��
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ��euapƽ̨�ϣ����д����ļ������ڣ����ȴ����ļ������euap��Ҫ�����ļ���Ȩ�ޣ��˴���Ҫ����
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_FILE_NOT_EXIST:�ļ�������
          VOS_NOK:�ļ�����ʧ��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_WriteBufToFile_Sync(const VOS_CHAR *pcContent
, VOS_UINT32 ulLen,const VOS_UINT32 uloffset, const VOS_CHAR *pcFileName);

/*********************************************************************************************
   
  brief      ����д���ļ�
  param[in]  *pcContent: ��д�뻺����Ϣ
  param[in]  ulLen: ��д��ĳ���
  param[in]  *pcFileName: ��д����ļ���
  param[in]  uloffset: д���ļ�����ʼλ��
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_FILE_NOT_EXIST:�ļ�������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_WriteBufToFile_Ex(const VOS_CHAR *pcContent
, VOS_UINT32 ulLen,const VOS_UINT32 uloffset, const VOS_CHAR *pcFileName);



/*********************************************************************************************
   
  brief      ɾ���ļ�/�ļ���
  param[in]  *pszSrcDir: ��ɾ���ļ�/�ļ���Ŀ¼
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� �������Ĳ�����һ���ļ���ֱ��ɾ��������������һ��Ŀ¼�������ɾ�����Ŀ¼�����е��ļ���
�ļ��У������ɾ�����м���ִ����޷��ع�
  retval  VOS_NOK:ɾ��ʧ��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_Remove_Files(const VOS_CHAR* pszSrcDir);
/*********************************************************************************************
   
  brief      �������浱ǰ����PID���ļ�
  param[in]  *pcPidFile: �������ļ�·��
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_FILE_NOT_EXIST:�ļ�������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_CreatePidFile(const VOS_CHAR *pcPidFile);

/*********************************************************************************************
   
  brief      ͨ��ָ����Ȩ�ޱ�־λ����������Ŀ¼
  param[in]  *pcDirName: ��������Ŀ¼��
  param[in]  ucMask: Ȩ�ޱ�־λ
  param[in]  *pcGroupName: ����
  return     VOS_OK: �ɹ�
             ����:ʧ��
   ע����� 
1�� ����
  retval  ATP_MSG_RET_PARA_ERR ��δ���
          ATP_MSG_RET_MKDIR_ERR ����Ŀ¼ʧ��
          ATP_MSG_RET_CHOWN_ERR �޸�Ŀ¼���Ȩ��ʧ��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_Mkdir(const VOS_CHAR *pcDirName, mode_t ucMask, const VOS_CHAR *pcGroupName);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

