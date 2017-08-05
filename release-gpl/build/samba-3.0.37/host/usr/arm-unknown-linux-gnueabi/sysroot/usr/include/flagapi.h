/******************************************************************************
  *         版权所有 (C), 2001-2020, 华为技术有限公司
*******************************************************************************/

#ifndef __FLAG_API_H__
#define __FLAG_API_H__


typedef struct tagATP_FLAG_SET_ST
{
    VOS_UINT16  usSize;             // pucBits size
    VOS_UINT8   aucFlagBits[0];     // flag bits 
} ATP_FLAG_SET_ST;

typedef void*(*PFMalloc)(VOS_UINT32 size);
typedef void (*PFFree)(void *ptr);


/*!
  \author       
  \brief        在共享内存中创建FLAG_SET   
  \param[in]  usSize:  需要标记的最大长度
  \param[in]  pfMalloc: 分配内存函数
  \return 
  \retval 创建ATP_FLAG_SET_ST*
*/
ATP_FLAG_SET_ST* ATP_FLAG_CreateX(VOS_UINT16 usSize, PFMalloc pfMalloc);

/*!
  \author       
  \brief         释放
  \param[in]  *handle: 
  \param[in]  pfFree: 释放函数
  \return 
  \retval ERROR_CODE 错误码说明
*/
VOS_VOID ATP_FLAG_FreeX(ATP_FLAG_SET_ST *handle, PFFree pfFree);


/*!
  \author       
  \brief         设置标记
  \param[in]  handle: 
  \param[in]  usIndex: 索引
  \return 
  \retval ATP_MSG_RET_PARA_ERR 入参错误
  \retval VOS_OK 成功  
*/
VOS_UINT32 ATP_FLAG_SET(ATP_FLAG_SET_ST* handle, VOS_UINT16 usIndex);


/*!
  \author       
  \brief         标记是否设置
  \param[in]  handle: 
  \param[in]  usIndex: 
  \return 
  \retval VOS_TRUE   已标记
  \retval VOS_FALSE 未标记
*/
VOS_BOOL ATP_FLAG_ISSET(const ATP_FLAG_SET_ST* handle, VOS_UINT16 usIndex);


/*!
  \author       
  \brief         加载
  \param[in]  handle: 
  \param[in]  *pcValue: 
  \return 
  \retval ERROR_CODE 错误码说明
*/
VOS_UINT32 ATP_FLAG_Load(ATP_FLAG_SET_ST* handle, const VOS_CHAR *pcValue);


#endif
