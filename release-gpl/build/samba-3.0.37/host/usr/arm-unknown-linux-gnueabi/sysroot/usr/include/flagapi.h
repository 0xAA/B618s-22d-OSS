/******************************************************************************
  *         ��Ȩ���� (C), 2001-2020, ��Ϊ�������޹�˾
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
  \brief        �ڹ����ڴ��д���FLAG_SET   
  \param[in]  usSize:  ��Ҫ��ǵ���󳤶�
  \param[in]  pfMalloc: �����ڴ溯��
  \return 
  \retval ����ATP_FLAG_SET_ST*
*/
ATP_FLAG_SET_ST* ATP_FLAG_CreateX(VOS_UINT16 usSize, PFMalloc pfMalloc);

/*!
  \author       
  \brief         �ͷ�
  \param[in]  *handle: 
  \param[in]  pfFree: �ͷź���
  \return 
  \retval ERROR_CODE ������˵��
*/
VOS_VOID ATP_FLAG_FreeX(ATP_FLAG_SET_ST *handle, PFFree pfFree);


/*!
  \author       
  \brief         ���ñ��
  \param[in]  handle: 
  \param[in]  usIndex: ����
  \return 
  \retval ATP_MSG_RET_PARA_ERR ��δ���
  \retval VOS_OK �ɹ�  
*/
VOS_UINT32 ATP_FLAG_SET(ATP_FLAG_SET_ST* handle, VOS_UINT16 usIndex);


/*!
  \author       
  \brief         ����Ƿ�����
  \param[in]  handle: 
  \param[in]  usIndex: 
  \return 
  \retval VOS_TRUE   �ѱ��
  \retval VOS_FALSE δ���
*/
VOS_BOOL ATP_FLAG_ISSET(const ATP_FLAG_SET_ST* handle, VOS_UINT16 usIndex);


/*!
  \author       
  \brief         ����
  \param[in]  handle: 
  \param[in]  *pcValue: 
  \return 
  \retval ERROR_CODE ������˵��
*/
VOS_UINT32 ATP_FLAG_Load(ATP_FLAG_SET_ST* handle, const VOS_CHAR *pcValue);


#endif
