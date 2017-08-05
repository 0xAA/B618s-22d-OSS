/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file cfmdbapi.h
  *
  *\copyright 2017-2030，华为技术有限公司
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
  brief      保存数据库
  param[in]  *pcFile: 打印出当前调用者的文件名
  param[in]  ulLine: 打印出当前调用者的文件行数
  param[in]  *pcFunction: 打印出当前调用者的函数名
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_DBSaveFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      保存数据库
  param[in]
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
#define ATP_DBSave(...)  ATP_DBSaveFunc(__FILE__, __LINE__, __func__)

/*********************************************************************************************
  author      
  brief      立即保存数据库
  param[in]  *pcFile: 打印出当前调用者的文件名
  param[in]  ulLine: 打印出当前调用者的文件行数
  param[in]  *pcFunction: 打印出当前调用者的函数名
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_DBSaveSyncFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      立即保存数据库
  param[in]
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
#define ATP_DBSaveSync(...) ATP_DBSaveSyncFunc(__FILE__, __LINE__, __func__)


/*********************************************************************************************
  author      
  brief      保存配置到APPDATA
  param[in]  *pcFile: 打印出当前调用者的文件名
  param[in]  ulLine: 打印出当前调用者的文件行数
  param[in]  *pcFunction: 打印出当前调用者的函数名
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/

VOS_UINT32 ATP_DBSaveToAppFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      保存配置到APPDATA
  param[in]  
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
#define ATP_DBSaveToApp(...)  ATP_DBSaveToAppFunc(__FILE__, __LINE__, __func__)

/*********************************************************************************************
  author      
  brief      立即保存配置到APPDATA
  param[in]  *pcFile: 打印出当前调用者的文件名
  param[in]  ulLine: 打印出当前调用者的文件行数
  param[in]  *pcFunction: 打印出当前调用者的函数名
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_DBSaveToAppSyncFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      立即保存配置到APPDATA
  param[in]  
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
#define ATP_DBSaveToAppSync(...) ATP_DBSaveToAppSyncFunc(__FILE__, __LINE__, __func__)

/*********************************************************************************************
  author      
  brief      立即保存APPDATA
  param[in]  *pcFile: 打印出当前调用者的文件名
  param[in]  ulLine: 打印出当前调用者的文件行数
  param[in]  *pcFunction: 打印出当前调用者的函数名
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_AppSaveSyncFunc(const VOS_CHAR *pcFile, VOS_UINT32 ulLine, const VOS_CHAR *pcFunction);
/*********************************************************************************************
  author      
  brief      立即保存APPDATA
  param[in]  
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 出于FLASH读写次数限制，不允许频繁调用此函数
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
#define ATP_AppSaveSync(...) ATP_AppSaveSyncFunc(__FILE__, __LINE__, __func__)
/*********************************************************************************************
  author      
  brief      校验配置文件是否合法
  param[in]  *pcFileName:配置文件路径
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_DBCheckFile(const VOS_CHAR *pcFileName);
/*********************************************************************************************
  author      
  brief      导出加密后的配置文件
  param[in]  *pcTargetFileName:配置文件路径
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_CFM_ExtExportEncryptedCfgFile(const VOS_CHAR *pcTargetFileName);
/*********************************************************************************************
  author      
  brief      根据配置工具导出加密后的配置文件
  param[in]  *pcTargetFileName:配置文件路径
  param[in]  enIfType:配置工具
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_CFM_ExtExportEncCfgFileByUser(const VOS_CHAR *pcTargetFileName, ATP_CFM_E_IF_TYPE enIfType);
/*********************************************************************************************
  author      
  brief      根据Flash区域导出配置文件
  param[in]  *pcTargetFileName:配置文件路径
  param[in]  flashArea:Flash区域
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_CFM_ExportFlashCfgFile(VOS_UINT32 flashArea, const VOS_CHAR *pcTargetFileName);
/*********************************************************************************************
  author      
  brief      导入加密后的配置文件
  param[in]  *pcFileName:配置文件路径
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_CFM_ExtImportEncryptedCfgFile(const VOS_CHAR *pcFileName);


#ifdef __cplusplus
#if __cplusplus
}
#endif 
#endif


#endif

