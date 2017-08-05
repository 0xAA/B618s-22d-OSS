/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file dmmsgapi.h
  *
  *\copyright 2017-2030，华为技术有限公司
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
    VOS_UINT32          ulMagicNum;      // 魔术字
    VOS_UINT32          ulAllSize;       // 消息体总大小
    VOS_UINT32          ulFreeSize;      // 消息体剩余空间
    VOS_UINT32          ulErrCode;       // 错误码
    VOS_UINT32          ulIntfType;      // 配置工具类型
    VOS_UINT32          ulMsgSubCode;   // 配置操作码
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
    ATP_DMMSG_GET_DEVICE_INFO,                  //获取设备的版本等信息,用于业务自动发放和升级
    ATP_DMMSG_GET_DATAMODELS,
    ATP_DMMSG_GET_PARAMETERS,
} ATP_DMMSG_TYPE_EN;
/*********************************************************************************************
   
  brief      构造DMMSG
  param[out] **ppvDMMsg:构造后的DMMSG
  param[in]  *pcRecvAp:接收进程名
  param[in]  ulSubType:DM消息类型
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 此函数存在内存分配，使用完毕之后需要释放
  retval   ATP_E_ERR_CFM_PARA_INVALID:入参输入错误
           ATP_E_ERR_CFM_INTERNAL:内存不够，malloc失败
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_Builder(VOS_VOID **ppvDMMsg, const VOS_CHAR *pcRecvApp, VOS_UINT32 ulSubType);
/*********************************************************************************************
   
  brief      往DMMSG中添加NV对
  param[out] **ppvDMMsg:待添加内容的DMMSG
  param[in]  ulIdentity:接收标识名
  param[in]  pcName:添加内容的名字
  param[in]  pvValue:添加内容的值
  param[in]  ulValueLength:添加内容的长度
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 此函数存在内存分配，使用完毕之后需要释放
  retval   ATP_E_ERR_CFM_PARA_INVALID:入参输入错误
           ATP_E_ERR_CFM_MEM:内存不够，malloc失败
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_AppendItem(VOS_VOID **ppvDMMsg, VOS_UINT32 ulIdentity,
                            const VOS_CHAR *pcName, const VOS_VOID *pvValue, VOS_UINT32 ulValueLength);
/*********************************************************************************************
   
  brief      获取消息错误码
  param[in]  *pvDMMsg:消息结构体
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_DMMSG_TYPE_UNKNOWN:入参输入错误
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_GetErrCode(const VOS_VOID *pvDMMsg);
/*********************************************************************************************
   
  brief      获取消息SubType
  param[in]  *pvDMMsg:消息结构体
  return     消息SubType:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_DMMSG_TYPE_UNKNOWN:入参输入错误
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_GetSubType(const VOS_VOID *pvDMMsg);
/*********************************************************************************************
   
  brief      获取消息SubType
  param[in]  *pvDMMsg:消息结构体
  param[out] *pstItem:获取到的Item结构体
  param[in]  **ppvPos:需要获取的Item的位置
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_E_ERR_CFM_PARA_INVALID:入参输入错误
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_GetItem(const VOS_VOID *pvDMMsg, ATP_DMMSG_ITEM *pstItem, VOS_VOID **ppvPos);
/*********************************************************************************************
   
  brief      释放DMMsg
  param[in]  *pvDMMsg:消息结构体
  return     
  
   注意事项： 
1、 暂无
  retval   
***********************************************************************************************/
VOS_VOID ATP_DMMSG_Free(VOS_VOID *pvDMMsg);
/*********************************************************************************************
   
  brief      发送DMMsg
  param[in]  *pvDMMsg:消息结构体
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_E_ERR_CFM_PARA_INVALID:入参输入错误
           ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_Send(VOS_VOID *pvDMMsg);
/*********************************************************************************************
   
  brief      同步发送DMMsg
  param[in]  *pvDMMsg:消息结构体
  param[out] **ppvRespMsg:返回的消息结构体
  param[in]  ulTimeout:超时时间
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 回应的消息存在内存分配，使用完毕之后需要释放
  retval   ATP_E_ERR_CFM_PARA_INVALID:入参输入错误
           ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
           ATP_E_ERR_CFM_MSG_TYPE:回复消息的魔数字与发送的不匹配
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_SyncSend(VOS_VOID *pvDMMsg, VOS_VOID **ppvRespMsg, VOS_UINT32 ulTimeout);
/*********************************************************************************************
   
  brief      回应DMMsg消息的返回码
  param[in]  *pvDMMsg:消息结构体
  param[in]  ulErrCode:消息返回码
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_E_ERR_CFM_PARA_INVALID:入参输入错误
           ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
           ATP_E_ERR_CFM_MSG_TYPE:回复消息的魔数字与发送的不匹配
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_ReplyRetCode(VOS_VOID *pvDMMsg, VOS_UINT32 ulErrCode);
/*********************************************************************************************
   
  brief      回应DMMsg消息
  param[in]  *pvDMMsg:消息结构体
  param[in]  ulErrCode:消息返回码
  param[in]  *pvRespDMMsg:回应消息结构体
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_E_ERR_CFM_PARA_INVALID:入参输入错误
           ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
           ATP_E_ERR_CFM_MSG_TYPE:回复消息的魔数字与发送的不匹配
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_Reply(VOS_VOID *pvDMMsg, VOS_UINT32 ulErrCode, VOS_VOID *pvRespDMMsg);
/*********************************************************************************************
   
  brief      回应DMMsg消息
  param[in]  *pcDstApp:回应消息结构体
  param[in]  ulErrCode:消息返回码
  param[in]  *pvRespDMMsg:回应消息结构体
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无
  retval   ATP_E_ERR_CFM_PARA_INVALID:入参输入错误
           ATP_MSG_RET_PARA_ERR:消息指针入参错误 
           ATP_MSG_RET_NOT_INITED:消息未初始化
           ATP_MSG_RET_OVERFLOW:消息发送失败，选择fd错误
           ATP_MSG_RET_FILE_WRITE_FAIL:消息发送时写文件失败
           ATP_MSG_RET_PEER_DEAD:socket已经被关闭
           ATP_MSG_RET_INTERNAL_ERR:消息发送时发生其他的错误
           ATP_E_ERR_CFM_MSG_TYPE:回复消息的魔数字与发送的不匹配
***********************************************************************************************/
VOS_UINT32 ATP_DMMSG_ReplyEx(const VOS_CHAR *pcDstApp, VOS_UINT32 ulErrCode, VOS_VOID *pvRespDMMsg);

#ifdef ATP_DEBUG
/*********************************************************************************************
   
  brief      打印DMMsg消息
  param[in]  *pvDMMsg:消息结构体
  return     
  
   注意事项： 
1、 出于安全考虑，debug版本才可以打印，且隐去了关键信息
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


