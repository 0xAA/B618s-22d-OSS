/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
#ifndef __ATP_NLS_API_H__
#define __ATP_NLS_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*
 * ATP Kernel NLS support interface, this will substitute iconv library
 */

#ifdef SUPPORT_ATP_ATP_NLS
#define ATP_NLS_ENCODING_UTF8       "utf8"
#define ATP_NLS_ENCODING_GB2312     "cp936"
#define ATP_NLS_ENCODING_BIG5       "cp950"
#define ATP_NLS_ENCODING_ISO8859_1  "iso8859-1"
#else
#define ATP_NLS_ENCODING_UTF8       "UTF-8"
#define ATP_NLS_ENCODING_GB2312     "GBK"
#define ATP_NLS_ENCODING_BIG5       "BIG5"
#define ATP_NLS_ENCODING_ISO8859_1  "ISO-8859-1"
#endif
/*********************************************************************************************
   
  brief      ���ַ���ת����GB2312��ʽ
  param[in]  *pszInput:��ת���ַ���
  param[in]  *tocode:ת���ĸ�ʽ
  param[in]  *fromcode:��ת���ĸ�ʽ
  return     ת����ʽ����ַ���:�ɹ�
             NULL:ʧ��
  
   ע����� 
1�� �˺������ڴ����룬ʹ�����֮����Ҫ�ͷ�
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_NLS_GB2312Convert (const VOS_CHAR *pszInput, const char* tocode, const char* fromcode);
/*********************************************************************************************
   
  brief      ���ַ���ת���ɶ�Ӧ��ʽ
  param[in]  *pszInput:��ת���ַ���
  param[in]  *tocode:ת���ĸ�ʽ
  param[in]  *fromcode:��ת���ĸ�ʽ
  return     ת����ʽ����ַ���:�ɹ�
             NULL:ʧ��
  
   ע����� 
1�� �˺������ڴ����룬ʹ�����֮����Ҫ�ͷ�
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_NLS_IconvConvert (const VOS_CHAR *pszInput, const char* tocode, const char* fromcode);
/*********************************************************************************************
   
  brief      ��ȡ�ַ���ת��֮��ĳ���
  param[in]  *pcInputEncoding:��ת���ĸ�ʽ
  param[in]  *pcInputSt:��ת�����ַ���
  param[in]  ulInputLen:��ת���ַ����ĳ���
  param[in]  *pcOutputEncoding:��ת���ĸ�ʽ
  param[in]  bForce:�Ƿ�ǿ�ƻ�ȡ
  return     ת����ʽ����ַ����ĳ���(>=0):�ɹ�
             -1:ʧ��
  
   ע����� 
1�� ����
  retval          
***********************************************************************************************/
VOS_INT32 ATP_NLS_ConvertGetLength(const VOS_CHAR *pcInputEncoding, const VOS_CHAR *pcInputStr, VOS_UINT32 ulInputLen, const VOS_CHAR *pcOutputEncoding, VOS_BOOL bForce);
/*********************************************************************************************
   
  brief      ���ַ���ת���ɶ�Ӧ�ĸ�ʽ
  param[in]  *pcInputEncoding:��ת���ĸ�ʽ
  param[in]  *pcInputSt:��ת�����ַ���
  param[in]  ulInputLen:��ת���ַ����ĳ���
  param[in]  *pcOutputEncoding:��ת���ĸ�ʽ
  param[out] *pulOutputlen:ת�����ַ����ĳ���  
  return     ת����ʽ����ַ���:�ɹ�
             NULL:ʧ��
  
   ע����� 
1�� �˺������ڴ����룬ʹ�����֮����Ҫ�ͷ�
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_NLS_ConvertString(const VOS_CHAR *pcInputEncoding, const VOS_CHAR *pcInputStr, VOS_UINT32 ulInputLen, const VOS_CHAR *pcOutputEncoding, VOS_UINT32 *pulOutputlen);
/*********************************************************************************************
   
  brief      �ж��ַ����Ƿ���UTF-8
  param[in]  *pszStr:���ж��ַ��� 
  return     VOS_TRUE:��UTF-8
             VOS_FALSE:��
  
   ע����� 
1�� ����
  retval          
***********************************************************************************************/
VOS_BOOL ATP_NLS_IsStringUtf8(const VOS_UINT8 *pszStr);
/*********************************************************************************************
   
  brief      ���Խ��ַ���ת��ΪUTF-8��ʽ
  param[in]  *pszInput:��ת���ַ�
  return     ת�����ַ���:�ɹ�
             NULL:ʧ��
  
   ע����� 
1�� �˺������ڴ����룬ʹ�����֮����Ҫ�ͷ�
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_NLS_TryConvertToUtf8(const VOS_CHAR *pszInput);
/*********************************************************************************************
   
  brief      ���Խ��ַ���ת��ΪUTF-8��ʽ����������ȫ�ֱ����в��ͷ�
  param[in]  *pszInput:��ת���ַ�
  return     ת�����ַ���:�ɹ�
             NULL:ʧ��
  
   ע����� 
1�� �˺������ڴ汣����ȫ�ֱ����У����Է���ȫ�ֱ�����ȡ���ͷŵ�ʱ��ע�⽫ȫ�ֱ�����Ϊ��
  retval          
***********************************************************************************************/
const VOS_CHAR *ATP_NLS_TryConvertToUtf8NoFree(const VOS_CHAR *pszInput);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

