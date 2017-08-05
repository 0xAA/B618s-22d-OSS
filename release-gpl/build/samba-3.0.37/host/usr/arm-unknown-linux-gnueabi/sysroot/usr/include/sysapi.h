/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file sysapi.h
  *
  *\copyright 2017-2030，华为技术有限公司
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
  \brief 更新动态应用程序是否被mic 启动
  \param[in]  *pcAppName: 需更新的应用程序名
  \param[in]  bStop: 是否停止当前被mic 启动进程
  \return 返回发送消息错误码
  \retval VOS_OK 更新消息发送成功
  \retval VOS_NOK pcAppName为NULL
  \retval ATP_MSG_RET_PARA_ERR  消息参数错误
  \retval ATP_MSG_RET_NOT_INITED 未初始化
  \retval ATP_MSG_RET_OVERFLOW  消息溢出
  \retval ATP_MSG_RET_PEER_DEAD  socket被peer关闭
  \retval ATP_MSG_RET_INTERNAL_ERR  内部错误
*/
/*********************************************************************************************
   
  brief      更新动态启动进程的状态
  param[in]  *pcAppName: 需更新状态的进程名字
  param[in]  bStart: 是否启动当前被mic启动进程
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 暂无
  retval  VOS_NOK: pcAppName为NULL
          ATP_MSG_RET_PARA_ERR:消息参数错误
          ATP_MSG_RET_NOT_INITED:消息未初始化
          ATP_MSG_RET_OVERFLOW:消息溢出
          ATP_MSG_RET_PEER_DEAD:socket被peer关闭
          ATP_MSG_RET_INTERNAL_ERR:内部错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_UpdateDynAppStatus(const VOS_CHAR *pcAppName, VOS_BOOL bStart);
/*********************************************************************************************
   
  brief      重启动态进程
  param[in]  *pcAppName: 需更新状态的进程名字
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 暂无
  retval  VOS_NOK: pcAppName为NULL
          ATP_MSG_RET_PARA_ERR:消息参数错误
          ATP_MSG_RET_NOT_INITED:消息未初始化
          ATP_MSG_RET_OVERFLOW:消息溢出
          ATP_MSG_RET_PEER_DEAD:socket被peer关闭
          ATP_MSG_RET_INTERNAL_ERR:内部错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_RestartDynApp(const VOS_CHAR *pcAppName);

/*
\author       
\brief       资源同步机制wait接口
\param[in]   pcEntry: 资源名称
\param[in]   ulTimeOut: 超时时间,单位为毫秒
\return 
\retval VOS_OK   成功
\retval VOS_NOK  失败
*/
/*********************************************************************************************
  author      
  brief      资源同步机制wait接口
  param[in]  *pcEntry: 资源名称
  param[in]  ulTimeOut: 超时时间,单位为毫秒
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 暂无
  retval  ATP_MSG_RET_PARA_ERR:消息参数错误
          ATP_MSG_RET_NOT_INITED:消息未初始化
          ATP_MSG_RET_OVERFLOW:消息溢出
          ATP_MSG_RET_PEER_DEAD:socket被peer关闭
          ATP_MSG_RET_INTERNAL_ERR:内部错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_AtpSyncWait(const VOS_CHAR *pcEntry, const VOS_UINT32 ulTimeOut);

/*
\author       
\brief       资源同步机制post接口
\param[in]   pcEntry: 资源名称
\return 
\retval VOS_OK   成功
\retval VOS_NOK  失败
*/
/*********************************************************************************************
  author      
  brief      资源同步机制post接口
  param[in]  *pcEntry: 资源名称
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 暂无
  retval  ATP_MSG_RET_PARA_ERR:消息参数错误
          ATP_MSG_RET_NOT_INITED:消息未初始化
          ATP_MSG_RET_OVERFLOW:消息溢出
          ATP_MSG_RET_PEER_DEAD:socket被peer关闭
          ATP_MSG_RET_INTERNAL_ERR:内部错误
***********************************************************************************************/
VOS_UINT32 ATP_MSG_AtpSyncPost(const VOS_CHAR *pcEntry);


/*!
  \brief  去除文件或文件夹的全局可写属性，只适用于eUAP产品
  \param[in]  *mod: 文件的期望权限属性，
                    本接口将用此mod传递给chmod生成该文件新的权限属性
  \param[in]  *path: 文件的绝对路径
  \return
  \retval NA
  \retval NA
*/
/*********************************************************************************************
  author      
  brief      去除文件或文件夹的全局可写属性，只适用于eUAP产品
  param[in]  *mod: 文件的期望权限属性，
                    本接口将用此mod传递给chmod生成该文件新的权限属性
  param[in]  *path: 文件的绝对路径
  return     
  
   注意事项： 
1、 该接口仅适用于euap产品
  retval  
***********************************************************************************************/
void ATP_UTIL_RemoveAndroidWPerm(char* path, char* mod);

/*!
  \brief 进程权限临时切换至root
  \return
  \retval ATP_MSG_RET_UPROOT_FAIL 权限提升失败
  \retval VOS_OK 成功
*/
/*********************************************************************************************
  author      
  brief      进程权限临时切换至root
  param[in]  无
  return     ATP_MSG_RET_UPROOT_FAIL 权限提升失败
             VOS_OK 成功
   
   注意事项： 
1、 最新版本已经支持权限控制，该函数在全面整改完毕后需要删除
  retval  ATP_MSG_RET_UPROOT_FAIL: 权限提升失败
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_UpRootPrivileges(VOS_VOID);

/*!
  \brief 恢复eUAP进程自己权限，设置为system权限
  \param[in]  NA
  \return
  \retval
  \retval VOS_OK 权限设置成功
*/
/*********************************************************************************************
  author      
  brief      恢复eUAP进程自己权限，设置为system权限
  param[in]  无
  return     VOS_OK 成功
   
   注意事项： 
1、 该函数仅在euap产品上有效
  retval  
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_DropAndroidRootPrivileges();

/*!
  \brief 恢复进程自己权限
  \param[in]  *pcAppName: 进程名称
  \return
  \retval ATP_MSG_RET_NOT_FOUNDPWD /etc/passwd 找不到该进程名
  \retval VOS_OK 权限设置成功
*/
/*********************************************************************************************
  author      
  brief      恢复进程自己权限
  param[in]  *pcAppName: 进程名称
  return     VOS_OK:成功
             其他:失败
   注意事项： 
1、 进程在启动时调用这个函数控制自己的权限
  retval  ATP_MSG_RET_NOT_FOUNDPWD:未找到PWD
          ATP_MSG_RET_NOT_FOUNDGROUP:未找到GROUP
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_DropRootPrivileges(const VOS_CHAR *pcAppName);


/*!
  \author      fwx276421
  \brief         检查传入的进程名是否是需要配置特殊权限的非root进程
  \param[in]  *processname: 进程名
  \return   0:表示当前进程不需要配置特殊权限
            1:表示当前进程需要配置特殊权限
  \retval ERROR_CODE 错误码说明
*/
/*********************************************************************************************
  author     fwx276421
  brief      检查传入的进程名是否是需要配置特殊权限的非root进程
  param[in]  *processname: 进程名称
  return     0:表示当前进程不需要配置特殊权限
             1:表示当前进程需要配置特殊权限
   注意事项： 
1、 暂无
  retval  无错误码说明
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_check_capability(const char *processname);


/*!
  \brief 改变文件或文件夹的所属组
  \param[in]  acGroup:组名称(从/etc/group中获取)
              acPath:文件路径
  \return
  \retval
*/
/*********************************************************************************************
  author      
  brief      改变文件或文件夹的所属组
  param[in]  acGroup:组名称(从/etc/group中获取)
  param[in]  acPath:文件路径
  return     VOS_OK:成功
             VOS_NOK:失败
   注意事项： 
1、 暂无
  retval  VOS_NOK:失败
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ChangeFileGrp(const VOS_CHAR *acGroup, VOS_CHAR *acPath);

/*!
  \brief 改变文件或文件夹的权限
  \param[in]  acPath:文件路径
              acMod:文件权限
  \return
  \retval
*/
/*********************************************************************************************
  author      
  brief      改变文件或文件夹的权限
  param[in]  acPath:文件路径
  param[in]  acMod:文件权限
  return     VOS_OK:成功
             VOS_NOK:失败
   注意事项： 
1、 暂无
  retval  VOS_NOK:失败
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ChangeFileMod(VOS_CHAR *acMod, VOS_CHAR *acPath);

/*!
  \brief 强制设置进程权限，不可恢复
  \param[in]  *pcAppName:
  \return
  \retval ATP_MSG_RET_NOT_FOUNDPWD /etc/passwd 找不到该进程名
*/
/*********************************************************************************************
  author      
  brief      强制设置进程权限，不可恢复
  param[in]  *pcAppName进程名字
  return     VOS_OK:成功
             其他:失败
   注意事项： 
1、 暂无
  retval  VOS_NOK:获取进程的GROUP信息失败
          ATP_MSG_RET_NOT_FOUNDPWD:未找到PWD
          ATP_MSG_RET_NOT_FOUNDGROUP:未找到GROUP
          ATP_MSG_RET_PARA_ERR:输入参数错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ForceSetPrivileges(const VOS_CHAR *pcAppName);

/*!
  \brief
  \param[in]  *pcUserName: 用户名
  \param[in]  ulGroupId: 默认组
  \return
  \retval
*/

/*!
  \brief cms拉起进程时降为非root,不关心子进程的status
  \param[in]  VOS_CHAR *pcCmd  启动参数
  \return
  \retval -1 fails
*/
/*********************************************************************************************
  author      
  brief      cms拉起进程时降为非root,不关心子进程的status
  param[in]  *pcCmd  启动参数
  return     >=0:子进程的PID
             -1:失败
   注意事项： 
1、 暂无
  retval  -1:入参错误或者命令解析失败
***********************************************************************************************/
VOS_INT32 ATP_UTIL_ExecCmdWithPermissions(const VOS_CHAR *pcCmd);
/*!
  \brief fork子进程执行pcCmd中命令,子进程启动时已降成非root
         注意:在进程权限新方案下，cms拉起的进程需要将为非root，而且父进程要关注plStatus
  \param[in] pcCmd  启动参数
            lWaitMiliSecs:0 不等, -1 一直等,其他等待的ms数
  \param[out]   *plStatus: 如果返回值 >0  并且 *pbWaitTimeout 是 VOS_FALSE ,*plStatus 是 waitpid输出的 *status
                *pbWaitTimeout: VOS_TRUE ulWaitMiliSecs 是 0 or 等待超时
                                          其他 VOS_FALSE
  \return  -1:出错
            >0:fork子进程pid
  \retval -1 fails
*/
/*********************************************************************************************
  author      
  brief      fork子进程执行pcCmd中命令,子进程启动时已降成非root
  param[in]  *pcCmd  启动参数
  param[in]  lWaitMiliSecs:0 不等, -1 一直等,其他等待的ms数
  param[out] *plStatus: 如果返回值 >0  并且 *pbWaitTimeout 是 VOS_FALSE ,*plStatus 是 waitpid输出的 *status
  param[out] *pbWaitTimeout: VOS_TRUE ulWaitMiliSecs 是 0 or 等待超时
                                          其他 VOS_FALSE
  return     >=0:子进程的PID
             -1:失败
   注意事项： 
1、 在进程权限新方案下，cms拉起的进程需要将为非root，而且父进程要关注plStatus
  retval  -1:入参错误或者命令解析失败
***********************************************************************************************/
VOS_INT32 ATP_UTIL_ExecCmdWithPermissionsFullEx(const VOS_CHAR *pcCmd, VOS_INT32 lWaitMiliSecs,
                                            VOS_INT32 *plStatus, VOS_BOOL *pbWaitTimeout);

/*!
  \brief 用户是否存在
  \param[in]  *pcUserName:
  \return
  \retval VOS_TRUE 已存在此用户
  \retval VOS_FALSE 不存在此用户
*/
/*********************************************************************************************
  author     fwx276421
  brief      用户是否存在
  param[in]  *pcUserName:待确认用户名
  return     VOS_TRUE 已存在此用户
             VOS_FALSE 不存在此用户
   注意事项： 
1、 暂无
  retval  无错误码
***********************************************************************************************/

VOS_BOOL ATP_UTIL_PrivilegesIsUserExist(const VOS_CHAR *pcUserName);


/*!
  \brief 修改文件所属的主id和组id。
  \param[in]  *pcFileName: 修改的文件名。
  \param[in]  *pcUserName: 用户名
  \param[in]  *pcGroupName: 组名。
  \return
  \retval VOS_OK 创建成功。
  \retval ATP_MSG_RET_PARA_ERR 入参错误。
  \retval ATP_MSG_RET_MKDIR_ERR 创建目录失败。
*/
/*********************************************************************************************
   
  brief      修改文件所属的主id和组id
  param[in]  *pcFileName: 修改的文件名
  param[in]  *pcUserName: 用户名
  param[in]  *pcGroupName: 组名。
  return     VOS_OK: 成功
             其他:失败
   注意事项： 
1、 暂无
  retval  ATP_MSG_RET_PARA_ERR 入参错误
          ATP_MSG_RET_CHOWN_ERR 修改目录组或权限失败
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ChangeFileUGid(const VOS_CHAR *pcFileName, const VOS_CHAR *pcUserName, const VOS_CHAR *pcGroupName);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

