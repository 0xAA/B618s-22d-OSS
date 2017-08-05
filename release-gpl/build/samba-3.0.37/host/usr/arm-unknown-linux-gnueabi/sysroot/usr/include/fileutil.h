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
   
  brief      文件读入缓存
  param[in]  *pcFileName: 读取的文件名称
  param[out] **ppcContent: 文件内容存入的buf指针
  param[in]  *pulLen: 读取的文件内容长度
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 此函数返回VOS_OK的时候存在内存申请，在使用完毕之后需要释放*ppcContent的空间。
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_FILE_NOT_EXIST:文件不存在
          ATP_MSG_RET_MEM_ERR:内存不足
          ATP_MSG_RET_INTERNAL_ERR:文件长度读取错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ReadFileToBuf(const VOS_CHAR *pcFileName, VOS_CHAR **ppcContent, VOS_UINT32 *pulLen);

/*********************************************************************************************
   
  brief      获取文件的长度
  param[in]  *pcFileName: 读取的文件名称
  return     >=0，文件大小
             -1，出错
   注意事项： 
1、 暂无
  retval  
***********************************************************************************************/
VOS_INT32 ATP_UTIL_FileTell(const VOS_CHAR* pcFileName);
/*********************************************************************************************
   
  brief      读取部分文件内容
  param[in]  *pcFileName: 读取的文件名称
  param[in]  *pcContent: 文件内容存放内存
  param[in]  *pulLen: 读取文件长度
  param[in]  ulMaxLen: 读取文件最大长度
  param[in]  ulOffset: 读取文件偏移量
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 此函数内部没有内存分配，读取内容存放内存需要在调用的地方提前申请好
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_FILE_NOT_EXIST:文件不存在
          ATP_MSG_RET_MEM_ERR:内存不足
          ATP_MSG_RET_INTERNAL_ERR:文件长度读取错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ReadPartFile(const VOS_CHAR *pcFileName, VOS_CHAR *pcContent, VOS_UINT32* pulLen,
    const VOS_UINT32 ulMaxLen, const VOS_UINT32 ulOffset);
/*********************************************************************************************
   
  brief      缓存写入文件
  param[in]  *pcContent: 待写入缓存信息
  param[in]  ulLen: 待写入的长度
  param[in]  *pcFileName: 待写入的文件名
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 如果缓存存在内存分配，调用完毕之后需要释放缓存
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_FILE_NOT_EXIST:文件不存在
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_WriteBufToFile(const VOS_CHAR *pcContent, VOS_UINT32 ulLen, const VOS_CHAR *pcFileName);

/*********************************************************************************************
   
  brief      文件读入缓存
  param[out] **ppcContent: 待保存文件内容缓存
  param[out] *pulLen: 写入缓存长度
  param[in]  *pcFileName: 待读取的文件名
  param[in]  uloffset: 读文件的起始位置
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 如果缓存存在内存分配，调用完毕之后需要释放缓存
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_FILE_NOT_EXIST:文件不存在
          ATP_MSG_RET_MEM_ERR:内存不足
          ATP_MSG_RET_INTERNAL_ERR:文件长度读取错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ReadFileToBuf_Ex(const VOS_CHAR *pcFileName
    , VOS_CHAR **ppcContent, VOS_UINT32 *pulLen, const VOS_UINT32 uloffset);

/*********************************************************************************************
   
  brief      缓存同步写入文件
  param[in]  *pcContent: 待写入缓存信息
  param[in]  ulLen: 待写入的长度
  param[in]  *pcFileName: 待写入的文件名
  param[in]  uloffset: 写入文件的起始位置
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 在euap平台上，如果写入的文件不存在，会先创建文件，如果euap需要整改文件夹权限，此处需要考虑
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_FILE_NOT_EXIST:文件不存在
          VOS_NOK:文件操作失败
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_WriteBufToFile_Sync(const VOS_CHAR *pcContent
, VOS_UINT32 ulLen,const VOS_UINT32 uloffset, const VOS_CHAR *pcFileName);

/*********************************************************************************************
   
  brief      缓存写入文件
  param[in]  *pcContent: 待写入缓存信息
  param[in]  ulLen: 待写入的长度
  param[in]  *pcFileName: 待写入的文件名
  param[in]  uloffset: 写入文件的起始位置
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 暂无
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_FILE_NOT_EXIST:文件不存在
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_WriteBufToFile_Ex(const VOS_CHAR *pcContent
, VOS_UINT32 ulLen,const VOS_UINT32 uloffset, const VOS_CHAR *pcFileName);



/*********************************************************************************************
   
  brief      删除文件/文件夹
  param[in]  *pszSrcDir: 待删除文件/文件夹目录
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 如果传入的参数是一个文件，直接删除，如果传入的是一个目录，会遍历删除这个目录下所有的文件和
文件夹，如果在删除的中间出现错误，无法回滚
  retval  VOS_NOK:删除失败
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_Remove_Files(const VOS_CHAR* pszSrcDir);
/*********************************************************************************************
   
  brief      创建保存当前进程PID的文件
  param[in]  *pcPidFile: 待创建文件路径
  return     成功，VOS_OK
             失败，详见错误码
   注意事项： 
1、 暂无
  retval  ATP_MSG_RET_PARA_ERR:入参输入错误
          ATP_MSG_RET_FILE_NOT_EXIST:文件不存在
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_CreatePidFile(const VOS_CHAR *pcPidFile);

/*********************************************************************************************
   
  brief      通过指定的权限标志位和组名创建目录
  param[in]  *pcDirName: 待创建的目录名
  param[in]  ucMask: 权限标志位
  param[in]  *pcGroupName: 组名
  return     VOS_OK: 成功
             其他:失败
   注意事项： 
1、 暂无
  retval  ATP_MSG_RET_PARA_ERR 入参错误
          ATP_MSG_RET_MKDIR_ERR 创建目录失败
          ATP_MSG_RET_CHOWN_ERR 修改目录组或权限失败
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_Mkdir(const VOS_CHAR *pcDirName, mode_t ucMask, const VOS_CHAR *pcGroupName);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

