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
   
  brief      将字符串转换成GB2312格式
  param[in]  *pszInput:待转换字符串
  param[in]  *tocode:转换的格式
  param[in]  *fromcode:被转换的格式
  return     转换格式后的字符串:成功
             NULL:失败
  
   注意事项： 
1、 此函数有内存申请，使用完毕之后需要释放
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_NLS_GB2312Convert (const VOS_CHAR *pszInput, const char* tocode, const char* fromcode);
/*********************************************************************************************
   
  brief      将字符串转换成对应格式
  param[in]  *pszInput:待转换字符串
  param[in]  *tocode:转换的格式
  param[in]  *fromcode:被转换的格式
  return     转换格式后的字符串:成功
             NULL:失败
  
   注意事项： 
1、 此函数有内存申请，使用完毕之后需要释放
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_NLS_IconvConvert (const VOS_CHAR *pszInput, const char* tocode, const char* fromcode);
/*********************************************************************************************
   
  brief      获取字符串转换之后的长度
  param[in]  *pcInputEncoding:待转换的格式
  param[in]  *pcInputSt:待转换的字符串
  param[in]  ulInputLen:待转换字符串的长度
  param[in]  *pcOutputEncoding:待转换的格式
  param[in]  bForce:是否强制获取
  return     转换格式后的字符串的长度(>=0):成功
             -1:失败
  
   注意事项： 
1、 暂无
  retval          
***********************************************************************************************/
VOS_INT32 ATP_NLS_ConvertGetLength(const VOS_CHAR *pcInputEncoding, const VOS_CHAR *pcInputStr, VOS_UINT32 ulInputLen, const VOS_CHAR *pcOutputEncoding, VOS_BOOL bForce);
/*********************************************************************************************
   
  brief      将字符串转换成对应的格式
  param[in]  *pcInputEncoding:待转换的格式
  param[in]  *pcInputSt:待转换的字符串
  param[in]  ulInputLen:待转换字符串的长度
  param[in]  *pcOutputEncoding:待转换的格式
  param[out] *pulOutputlen:转换后字符串的长度  
  return     转换格式后的字符串:成功
             NULL:失败
  
   注意事项： 
1、 此函数有内存申请，使用完毕之后需要释放
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_NLS_ConvertString(const VOS_CHAR *pcInputEncoding, const VOS_CHAR *pcInputStr, VOS_UINT32 ulInputLen, const VOS_CHAR *pcOutputEncoding, VOS_UINT32 *pulOutputlen);
/*********************************************************************************************
   
  brief      判断字符串是否是UTF-8
  param[in]  *pszStr:待判断字符串 
  return     VOS_TRUE:是UTF-8
             VOS_FALSE:否
  
   注意事项： 
1、 暂无
  retval          
***********************************************************************************************/
VOS_BOOL ATP_NLS_IsStringUtf8(const VOS_UINT8 *pszStr);
/*********************************************************************************************
   
  brief      尝试将字符串转换为UTF-8格式
  param[in]  *pszInput:待转换字符
  return     转换后字符串:成功
             NULL:失败
  
   注意事项： 
1、 此函数有内存申请，使用完毕之后需要释放
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_NLS_TryConvertToUtf8(const VOS_CHAR *pszInput);
/*********************************************************************************************
   
  brief      尝试将字符串转换为UTF-8格式，并保存在全局变量中不释放
  param[in]  *pszInput:待转换字符
  return     转换后字符串:成功
             NULL:失败
  
   注意事项： 
1、 此函数将内存保存在全局变量中，可以访问全局变量获取，释放的时候注意将全局变量置为空
  retval          
***********************************************************************************************/
const VOS_CHAR *ATP_NLS_TryConvertToUtf8NoFree(const VOS_CHAR *pszInput);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

