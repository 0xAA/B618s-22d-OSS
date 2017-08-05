/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file notifyutil.h
  *
  *\copyright 2017-2030����Ϊ�������޹�˾
  *\author  
  *\date  2017-6-12
  
*/
#ifndef __ATP_NOTIFY_UTIL_H__
#define __ATP_NOTIFY_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*
 * Notify utility
 */
typedef VOS_UINT32 (*AtpNotifierProc)(VOS_VOID *pvNotifier, VOS_VOID *pvNotifyHook);
typedef VOS_BOOL (*AtpNotifierPostProc)(const VOS_VOID *pvNotifier, const VOS_VOID *pvNotifyHook, VOS_UINT32 ulRetVal);
typedef VOS_BOOL (*AtpNotifierFilterProc)(const VOS_VOID *pvNotifier, const VOS_VOID *pvNotifyHook, const VOS_VOID *pvArg);

typedef struct tagATP_UTIL_NOTIFY_HOOKS_ST
{
    AtpNotifierProc                         pfPreProc;
    AtpNotifierPostProc                     pfPostProc;
    AtpNotifierFilterProc                   pfFilterProc;
    const VOS_VOID                          *pvFilterArg;
} ATP_UTIL_NOTIFY_HOOKS_ST;

typedef struct tagATP_UTIL_NOTIFY_ENTRY_ST
{
    struct tagATP_UTIL_NOTIFY_ENTRY_ST      *pstNext;
    AtpNotifierProc                         pfProc;
    VOS_UINT32                              ulPriority;
    VOS_VOID                                *pvNotifyHook;
} ATP_UTIL_NOTIFY_ENTRY_ST;

typedef struct tagATP_UTIL_NOTIFIER_ST
{
    struct tagATP_UTIL_NOTIFIER_ST          *pstNext;
    VOS_VOID                                *pvNotifier;
    ATP_UTIL_NOTIFY_ENTRY_ST                *pstNotifyEntries;
} ATP_UTIL_NOTIFIER_ST;
/*********************************************************************************************
   
  brief      ֪ͨ���Ƴ�ʼ��
  param[in]  *pvNotifier: ע��ʱ����Ļص�����
  param[in]  **ppstNewNotifyEntry: ��ʼ�����֪ͨ���ƽṹ��
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����ͨ����cms��ʹ�ã����¼����ͷ���ʼ��������ģ��ע���ע��Ϣ���¼�����ʱ���¼����ͷ�֪ͨ����ģ��
�˺������¼����ͷ�ʹ��
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierInit(VOS_VOID               *pvNotifier,
                                      ATP_UTIL_NOTIFIER_ST   **ppstNewNotifyEntry);
/*********************************************************************************************
   
  brief      ע���¼���ע
  param[in]  *pstNotifier: ֪ͨ���ƽṹ��
  param[in]  pfProc: �¼��ص�����
  param[in]  ulPriority: ֪ͨ���ȼ�
  param[in]  pvNotifyHook: ֪ͨ�ص��������
  param[in]  ppstNotifyEntry: NotifyEntry�ṹ�壬һ�����������ΪNULL
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����ͨ����cms��ʹ�ã����¼����ͷ���ʼ��������ģ��ע���ע��Ϣ���¼�����ʱ���¼����ͷ�֪ͨ����ģ��
�˺������¼���ע������
2�� ����������ڴ����룬��ʹ�����֮��ע���ͷ�
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierRegister(ATP_UTIL_NOTIFIER_ST           *pstNotifier,
                                            AtpNotifierProc                 pfProc,
                                            VOS_UINT32                      ulPriority,
                                            VOS_VOID                        *pvNotifyHook,
                                            const ATP_UTIL_NOTIFY_ENTRY_ST  **ppstNotifyEntry);
/*********************************************************************************************
   
  brief      ע���¼���ע�����������ȼ�����ʽ����
  param[in]  *pstNotifier: ֪ͨ���ƽṹ��
  param[in]  pfProc: �¼��ص�����
  param[in]  ulPriority: ֪ͨ���ȼ�
  param[in]  pvNotifyHook: ֪ͨ�ص��������
  param[in]  ppstNotifyEntry: NotifyEntry�ṹ�壬һ�����������ΪNULL
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����ͨ����cms��ʹ�ã����¼����ͷ���ʼ��������ģ��ע���ע��Ϣ���¼�����ʱ���¼����ͷ�֪ͨ����ģ��
�˺������¼���ע������
2�� ����������ڴ����룬��ʹ�����֮��ע���ͷ�
  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierReverseRegister(ATP_UTIL_NOTIFIER_ST  *pstNotifier,
                                            AtpNotifierProc                 pfProc,
                                            VOS_UINT32                      ulPriority,
                                            VOS_VOID                        *pvNotifyHook,
                                            const ATP_UTIL_NOTIFY_ENTRY_ST  **ppstNotifyEntry);
/*********************************************************************************************
   
  brief      ȥע���¼���ע
  param[in]  *pstNotifier: ֪ͨ���ƽṹ��
  param[in]  ppstNotifyEntry: NotifyEntry�ṹ�壬һ�����������ΪNULL
  return     
  
   ע����� 
1�� ����ͨ����cms��ʹ�ã����¼����ͷ���ʼ��������ģ��ע���ע��Ϣ���¼�����ʱ���¼����ͷ�֪ͨ����ģ��
�˺������¼���ע������
  retval  
***********************************************************************************************/
VOS_VOID ATP_UTIL_NotifierUnRegister(ATP_UTIL_NOTIFIER_ST *pstNotifier, ATP_UTIL_NOTIFY_ENTRY_ST *pstNotifyEntry);
/*********************************************************************************************
   
  brief      �¼�����
  param[in]  *pstNotifier: ֪ͨ���ƽṹ��
  param[in]  bStopWhenError: ����ʱ�Ƿ�ֹͣ
  param[in]  *pstHooks: ����ʱЯ�����
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����ͨ����cms��ʹ�ã����¼����ͷ���ʼ��������ģ��ע���ע��Ϣ���¼�����ʱ���¼����ͷ�֪ͨ����ģ��
�˺������¼�����������
  retval  ATP_MSG_RET_PARA_ERR:����������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierDoNotifyEx(const ATP_UTIL_NOTIFIER_ST *pstNotifier,
                VOS_BOOL bStopWhenError, const ATP_UTIL_NOTIFY_HOOKS_ST *pstHooks);
/*********************************************************************************************
   
  brief      �¼�������Я��trace��Ϣ
  param[in]  *pcFunc: ��������Ϣ
  param[in]  ulCbbId: ������CbbId
  param[in]  *pstNotifier: ֪ͨ���ƽṹ��
  param[in]  bStopWhenError: ����ʱ�Ƿ�ֹͣ
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����ͨ����cms��ʹ�ã����¼����ͷ���ʼ��������ģ��ע���ע��Ϣ���¼�����ʱ���¼����ͷ�֪ͨ����ģ��
�˺������¼�����������
  retval  ATP_MSG_RET_PARA_ERR:����������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_NotifierDoNotifyWrap(const VOS_CHAR *pcFunc, VOS_UINT32 ulCbbId, const ATP_UTIL_NOTIFIER_ST *pstNotifier, VOS_BOOL bStopWhenError);
/*********************************************************************************************
   
  brief      �¼�����
  param[in]  *pstNotifier: ֪ͨ���ƽṹ��
  param[in]  bStopWhenError: ����ʱ�Ƿ�ֹͣ
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����ͨ����cms��ʹ�ã����¼����ͷ���ʼ��������ģ��ע���ע��Ϣ���¼�����ʱ���¼����ͷ�֪ͨ����ģ��
�˺������¼�����������
  retval  ATP_MSG_RET_PARA_ERR:����������
***********************************************************************************************/
#define ATP_UTIL_NotifierDoNotify(pstNotifier, bStopWhenError) ATP_UTIL_NotifierDoNotifyWrap(__FUNCTION__, ATP_MODULE_IDX, (pstNotifier), (bStopWhenError))

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

