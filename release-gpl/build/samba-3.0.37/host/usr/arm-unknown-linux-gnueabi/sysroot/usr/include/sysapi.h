/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file sysapi.h
  *
  *\copyright 2017-2030����Ϊ�������޹�˾
  *\author  
  *\date  2017-6-12
 
*/
#ifndef __ATP_SYS_API_H__
#define __ATP_SYS_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*!
  \brief ���¶�̬Ӧ�ó����Ƿ�mic ����
  \param[in]  *pcAppName: ����µ�Ӧ�ó�����
  \param[in]  bStop: �Ƿ�ֹͣ��ǰ��mic ��������
  \return ���ط�����Ϣ������
  \retval VOS_OK ������Ϣ���ͳɹ�
  \retval VOS_NOK pcAppNameΪNULL
  \retval ATP_MSG_RET_PARA_ERR  ��Ϣ��������
  \retval ATP_MSG_RET_NOT_INITED δ��ʼ��
  \retval ATP_MSG_RET_OVERFLOW  ��Ϣ���
  \retval ATP_MSG_RET_PEER_DEAD  socket��peer�ر�
  \retval ATP_MSG_RET_INTERNAL_ERR  �ڲ�����
*/
/*********************************************************************************************
   
  brief      ���¶�̬�������̵�״̬
  param[in]  *pcAppName: �����״̬�Ľ�������
  param[in]  bStart: �Ƿ�������ǰ��mic��������
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����
  retval  VOS_NOK: pcAppNameΪNULL
          ATP_MSG_RET_PARA_ERR:��Ϣ��������
          ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
          ATP_MSG_RET_OVERFLOW:��Ϣ���
          ATP_MSG_RET_PEER_DEAD:socket��peer�ر�
          ATP_MSG_RET_INTERNAL_ERR:�ڲ�����
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_UpdateDynAppStatus(const VOS_CHAR *pcAppName, VOS_BOOL bStart);
/*********************************************************************************************
   
  brief      ������̬����
  param[in]  *pcAppName: �����״̬�Ľ�������
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����
  retval  VOS_NOK: pcAppNameΪNULL
          ATP_MSG_RET_PARA_ERR:��Ϣ��������
          ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
          ATP_MSG_RET_OVERFLOW:��Ϣ���
          ATP_MSG_RET_PEER_DEAD:socket��peer�ر�
          ATP_MSG_RET_INTERNAL_ERR:�ڲ�����
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_RestartDynApp(const VOS_CHAR *pcAppName);

/*
\author       
\brief       ��Դͬ������wait�ӿ�
\param[in]   pcEntry: ��Դ����
\param[in]   ulTimeOut: ��ʱʱ��,��λΪ����
\return 
\retval VOS_OK   �ɹ�
\retval VOS_NOK  ʧ��
*/
/*********************************************************************************************
  author      
  brief      ��Դͬ������wait�ӿ�
  param[in]  *pcEntry: ��Դ����
  param[in]  ulTimeOut: ��ʱʱ��,��λΪ����
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����
  retval  ATP_MSG_RET_PARA_ERR:��Ϣ��������
          ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
          ATP_MSG_RET_OVERFLOW:��Ϣ���
          ATP_MSG_RET_PEER_DEAD:socket��peer�ر�
          ATP_MSG_RET_INTERNAL_ERR:�ڲ�����
***********************************************************************************************/
VOS_UINT32 ATP_MSG_AtpSyncWait(const VOS_CHAR *pcEntry, const VOS_UINT32 ulTimeOut);

/*
\author       
\brief       ��Դͬ������post�ӿ�
\param[in]   pcEntry: ��Դ����
\return 
\retval VOS_OK   �ɹ�
\retval VOS_NOK  ʧ��
*/
/*********************************************************************************************
  author      
  brief      ��Դͬ������post�ӿ�
  param[in]  *pcEntry: ��Դ����
  return     �ɹ���VOS_OK
             ʧ�ܣ����������
   ע����� 
1�� ����
  retval  ATP_MSG_RET_PARA_ERR:��Ϣ��������
          ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
          ATP_MSG_RET_OVERFLOW:��Ϣ���
          ATP_MSG_RET_PEER_DEAD:socket��peer�ر�
          ATP_MSG_RET_INTERNAL_ERR:�ڲ�����
***********************************************************************************************/
VOS_UINT32 ATP_MSG_AtpSyncPost(const VOS_CHAR *pcEntry);


/*!
  \brief  ȥ���ļ����ļ��е�ȫ�ֿ�д���ԣ�ֻ������eUAP��Ʒ
  \param[in]  *mod: �ļ�������Ȩ�����ԣ�
                    ���ӿڽ��ô�mod���ݸ�chmod���ɸ��ļ��µ�Ȩ������
  \param[in]  *path: �ļ��ľ���·��
  \return
  \retval NA
  \retval NA
*/
/*********************************************************************************************
  author      
  brief      ȥ���ļ����ļ��е�ȫ�ֿ�д���ԣ�ֻ������eUAP��Ʒ
  param[in]  *mod: �ļ�������Ȩ�����ԣ�
                    ���ӿڽ��ô�mod���ݸ�chmod���ɸ��ļ��µ�Ȩ������
  param[in]  *path: �ļ��ľ���·��
  return     
  
   ע����� 
1�� �ýӿڽ�������euap��Ʒ
  retval  
***********************************************************************************************/
void ATP_UTIL_RemoveAndroidWPerm(char* path, char* mod);

/*!
  \brief ����Ȩ����ʱ�л���root
  \return
  \retval ATP_MSG_RET_UPROOT_FAIL Ȩ������ʧ��
  \retval VOS_OK �ɹ�
*/
/*********************************************************************************************
  author      
  brief      ����Ȩ����ʱ�л���root
  param[in]  ��
  return     ATP_MSG_RET_UPROOT_FAIL Ȩ������ʧ��
             VOS_OK �ɹ�
   
   ע����� 
1�� ���°汾�Ѿ�֧��Ȩ�޿��ƣ��ú�����ȫ��������Ϻ���Ҫɾ��
  retval  ATP_MSG_RET_UPROOT_FAIL: Ȩ������ʧ��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_UpRootPrivileges(VOS_VOID);

/*!
  \brief �ָ�eUAP�����Լ�Ȩ�ޣ�����ΪsystemȨ��
  \param[in]  NA
  \return
  \retval
  \retval VOS_OK Ȩ�����óɹ�
*/
/*********************************************************************************************
  author      
  brief      �ָ�eUAP�����Լ�Ȩ�ޣ�����ΪsystemȨ��
  param[in]  ��
  return     VOS_OK �ɹ�
   
   ע����� 
1�� �ú�������euap��Ʒ����Ч
  retval  
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_DropAndroidRootPrivileges();

/*!
  \brief �ָ������Լ�Ȩ��
  \param[in]  *pcAppName: ��������
  \return
  \retval ATP_MSG_RET_NOT_FOUNDPWD /etc/passwd �Ҳ����ý�����
  \retval VOS_OK Ȩ�����óɹ�
*/
/*********************************************************************************************
  author      
  brief      �ָ������Լ�Ȩ��
  param[in]  *pcAppName: ��������
  return     VOS_OK:�ɹ�
             ����:ʧ��
   ע����� 
1�� ����������ʱ����������������Լ���Ȩ��
  retval  ATP_MSG_RET_NOT_FOUNDPWD:δ�ҵ�PWD
          ATP_MSG_RET_NOT_FOUNDGROUP:δ�ҵ�GROUP
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_DropRootPrivileges(const VOS_CHAR *pcAppName);


/*!
  \author      fwx276421
  \brief         ��鴫��Ľ������Ƿ�����Ҫ��������Ȩ�޵ķ�root����
  \param[in]  *processname: ������
  \return   0:��ʾ��ǰ���̲���Ҫ��������Ȩ��
            1:��ʾ��ǰ������Ҫ��������Ȩ��
  \retval ERROR_CODE ������˵��
*/
/*********************************************************************************************
  author     fwx276421
  brief      ��鴫��Ľ������Ƿ�����Ҫ��������Ȩ�޵ķ�root����
  param[in]  *processname: ��������
  return     0:��ʾ��ǰ���̲���Ҫ��������Ȩ��
             1:��ʾ��ǰ������Ҫ��������Ȩ��
   ע����� 
1�� ����
  retval  �޴�����˵��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_check_capability(const char *processname);


/*!
  \brief �ı��ļ����ļ��е�������
  \param[in]  acGroup:������(��/etc/group�л�ȡ)
              acPath:�ļ�·��
  \return
  \retval
*/
/*********************************************************************************************
  author      
  brief      �ı��ļ����ļ��е�������
  param[in]  acGroup:������(��/etc/group�л�ȡ)
  param[in]  acPath:�ļ�·��
  return     VOS_OK:�ɹ�
             VOS_NOK:ʧ��
   ע����� 
1�� ����
  retval  VOS_NOK:ʧ��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ChangeFileGrp(const VOS_CHAR *acGroup, VOS_CHAR *acPath);

/*!
  \brief �ı��ļ����ļ��е�Ȩ��
  \param[in]  acPath:�ļ�·��
              acMod:�ļ�Ȩ��
  \return
  \retval
*/
/*********************************************************************************************
  author      
  brief      �ı��ļ����ļ��е�Ȩ��
  param[in]  acPath:�ļ�·��
  param[in]  acMod:�ļ�Ȩ��
  return     VOS_OK:�ɹ�
             VOS_NOK:ʧ��
   ע����� 
1�� ����
  retval  VOS_NOK:ʧ��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ChangeFileMod(VOS_CHAR *acMod, VOS_CHAR *acPath);

/*!
  \brief ǿ�����ý���Ȩ�ޣ����ɻָ�
  \param[in]  *pcAppName:
  \return
  \retval ATP_MSG_RET_NOT_FOUNDPWD /etc/passwd �Ҳ����ý�����
*/
/*********************************************************************************************
  author      
  brief      ǿ�����ý���Ȩ�ޣ����ɻָ�
  param[in]  *pcAppName��������
  return     VOS_OK:�ɹ�
             ����:ʧ��
   ע����� 
1�� ����
  retval  VOS_NOK:��ȡ���̵�GROUP��Ϣʧ��
          ATP_MSG_RET_NOT_FOUNDPWD:δ�ҵ�PWD
          ATP_MSG_RET_NOT_FOUNDGROUP:δ�ҵ�GROUP
          ATP_MSG_RET_PARA_ERR:�����������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ForceSetPrivileges(const VOS_CHAR *pcAppName);

/*!
  \brief
  \param[in]  *pcUserName: �û���
  \param[in]  ulGroupId: Ĭ����
  \return
  \retval
*/

/*!
  \brief cms�������ʱ��Ϊ��root,�������ӽ��̵�status
  \param[in]  VOS_CHAR *pcCmd  ��������
  \return
  \retval -1 fails
*/
/*********************************************************************************************
  author      
  brief      cms�������ʱ��Ϊ��root,�������ӽ��̵�status
  param[in]  *pcCmd  ��������
  return     >=0:�ӽ��̵�PID
             -1:ʧ��
   ע����� 
1�� ����
  retval  -1:��δ�������������ʧ��
***********************************************************************************************/
VOS_INT32 ATP_UTIL_ExecCmdWithPermissions(const VOS_CHAR *pcCmd);
/*!
  \brief fork�ӽ���ִ��pcCmd������,�ӽ�������ʱ�ѽ��ɷ�root
         ע��:�ڽ���Ȩ���·����£�cms����Ľ�����Ҫ��Ϊ��root�����Ҹ�����Ҫ��עplStatus
  \param[in] pcCmd  ��������
            lWaitMiliSecs:0 ����, -1 һֱ��,�����ȴ���ms��
  \param[out]   *plStatus: �������ֵ >0  ���� *pbWaitTimeout �� VOS_FALSE ,*plStatus �� waitpid����� *status
                *pbWaitTimeout: VOS_TRUE ulWaitMiliSecs �� 0 or �ȴ���ʱ
                                          ���� VOS_FALSE
  \return  -1:����
            >0:fork�ӽ���pid
  \retval -1 fails
*/
/*********************************************************************************************
  author      
  brief      fork�ӽ���ִ��pcCmd������,�ӽ�������ʱ�ѽ��ɷ�root
  param[in]  *pcCmd  ��������
  param[in]  lWaitMiliSecs:0 ����, -1 һֱ��,�����ȴ���ms��
  param[out] *plStatus: �������ֵ >0  ���� *pbWaitTimeout �� VOS_FALSE ,*plStatus �� waitpid����� *status
  param[out] *pbWaitTimeout: VOS_TRUE ulWaitMiliSecs �� 0 or �ȴ���ʱ
                                          ���� VOS_FALSE
  return     >=0:�ӽ��̵�PID
             -1:ʧ��
   ע����� 
1�� �ڽ���Ȩ���·����£�cms����Ľ�����Ҫ��Ϊ��root�����Ҹ�����Ҫ��עplStatus
  retval  -1:��δ�������������ʧ��
***********************************************************************************************/
VOS_INT32 ATP_UTIL_ExecCmdWithPermissionsFullEx(const VOS_CHAR *pcCmd, VOS_INT32 lWaitMiliSecs,
                                            VOS_INT32 *plStatus, VOS_BOOL *pbWaitTimeout);

/*!
  \brief �û��Ƿ����
  \param[in]  *pcUserName:
  \return
  \retval VOS_TRUE �Ѵ��ڴ��û�
  \retval VOS_FALSE �����ڴ��û�
*/
/*********************************************************************************************
  author     fwx276421
  brief      �û��Ƿ����
  param[in]  *pcUserName:��ȷ���û���
  return     VOS_TRUE �Ѵ��ڴ��û�
             VOS_FALSE �����ڴ��û�
   ע����� 
1�� ����
  retval  �޴�����
***********************************************************************************************/

VOS_BOOL ATP_UTIL_PrivilegesIsUserExist(const VOS_CHAR *pcUserName);


/*!
  \brief �޸��ļ���������id����id��
  \param[in]  *pcFileName: �޸ĵ��ļ�����
  \param[in]  *pcUserName: �û���
  \param[in]  *pcGroupName: ������
  \return
  \retval VOS_OK �����ɹ���
  \retval ATP_MSG_RET_PARA_ERR ��δ���
  \retval ATP_MSG_RET_MKDIR_ERR ����Ŀ¼ʧ�ܡ�
*/
/*********************************************************************************************
   
  brief      �޸��ļ���������id����id
  param[in]  *pcFileName: �޸ĵ��ļ���
  param[in]  *pcUserName: �û���
  param[in]  *pcGroupName: ������
  return     VOS_OK: �ɹ�
             ����:ʧ��
   ע����� 
1�� ����
  retval  ATP_MSG_RET_PARA_ERR ��δ���
          ATP_MSG_RET_CHOWN_ERR �޸�Ŀ¼���Ȩ��ʧ��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ChangeFileUGid(const VOS_CHAR *pcFileName, const VOS_CHAR *pcUserName, const VOS_CHAR *pcGroupName);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

