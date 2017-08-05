/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file strutil.h
  *
  *\copyright 2017-2030，华为技术有限公司
  *\author  
  *\date  2017-6-12  
*/
#ifndef __ATP_STR_UTIL_H__
#define __ATP_STR_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*
  * String Utilities
  */

/*!
  \brief 执行字符串strcat操作，将pcSrc中的内容连接在pcDst后面，安全编码。
  \param[in]  pcDst: 目的字符串
  \param[in]  size: 连接后的字符串长度
  \param[in]  pcSrc: 待连接字符串
  \return 连接后的字符串
  \retval pcDst
*/
/*********************************************************************************************
   
  brief      执行字符串strcat操作，将pcSrc中的内容连接在pcDst后面，安全编码
  param[in]  pcDst: 目的字符串
  param[in]  size: 连接后的字符串长度
  param[in]  pcSrc: 待连接字符串
  return     连接后的字符串:成功
             NULL:失败
   注意事项： 
1、 暂无
  retval  无错误码
***********************************************************************************************/
const VOS_CHAR * ATP_UTIL_StrCat(VOS_CHAR * pcDst, VOS_UINT32 size, const VOS_CHAR * pcSrc);
/*!
  \brief 执行字符串Trim操作，去掉两头的空白字符,
          在原字符串上修改，未开辟空间,输入为空格时，直接返回
  \param[in]  *pszStr: 输入的字符串，可以为空
  \return  Trim后的字符串指针
  \retval pszStr  Trim后的字符串指针，可以为空
*/
/*********************************************************************************************
   
  brief      执行字符串Trim操作，去掉两头的空白字符,
             在原字符串上修改，未开辟空间,输入为空格时，直接返回
  param[in]  *pszStr: 输入的字符串，可以为空
  return     Trim后的字符串指针:成功
             NULL:失败
   注意事项： 
1、 该函数直接对入参指定的内容做了修改，对于入参指定内容不能修改的场景不能使用
  retval  无错误码
***********************************************************************************************/
VOS_CHAR * ATP_UTIL_StrTrim( VOS_CHAR *pszStr );

typedef struct tagATP_UTIL_STR_IDX_MAP_ST
{
    const VOS_CHAR      *pcStrInfo;
    VOS_INT32           lIdx;
} ATP_UTIL_STR_IDX_MAP_ST;

/*********************************************************************************************
   
  brief      通过枚举或者整型值来得到相应的字符串
  param[in]  lIdx: 输入的整型值
  param[in]  *pstSrcStrIdx: 输入的枚举值--字符串对应结构体数组(必须以{NULL ,-1}结束)
  return     整型值对应的字符串:成功
             NULL:失败
   注意事项： 
1、 暂无
  retval  无错误码
***********************************************************************************************/
const VOS_CHAR *ATP_UTIL_StrIdxArrayGetStrByIdx(VOS_INT32 lIdx,const ATP_UTIL_STR_IDX_MAP_ST* pstSrcStrIdx);

/*********************************************************************************************
   
  brief      通过输入的字符串得到相应的枚举值或整型值
  param[in]  *pcStr: 输入的字符串
  param[in]  pstSrcStrIdx: 输入的枚举值--字符串对应结构体数组(必须以{NULL ,-1}结束)
  return     字符串对应的整型值(>=0):成功
             -1:失败
   注意事项： 
1、 暂无
  retval  无错误码
***********************************************************************************************/
VOS_INT32 ATP_UTIL_StrIdxArrayGetIdxByStr(const VOS_CHAR *pcStr,const ATP_UTIL_STR_IDX_MAP_ST* pstSrcStrIdx);
/*********************************************************************************************
   
  brief      在字符串指针数组中查找指定序列号的字符串
  param[in]  lIdx: 字符串在数组内的序列号
  param[in]  *apcBaseLine:指定查找的数组(基本数组)
  param[in]  lBaseLineLen:指定查找的数组长度
  param[in]  *apcExtension:指定查找数组的扩展数组
  return     数组序列号对应的字符串:成功
             NULL:失败
   注意事项： 
1、 apcBaseLine[] 中不能包含NULL指针， apcExtension中必须以NULL结尾
  retval  无错误码
***********************************************************************************************/
const VOS_CHAR *ATP_UTIL_GetStrFromIdx(VOS_INT32 lIdx, const VOS_CHAR * const apcBaseLine[],
                                  VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[]);

/*!
  \brief  在字符串指针数组中查找指定的字符串，返回该字符串的序号
  \param[in]  const VOS_CHAR *pcStr: 要查找的字符串
  \param[in]  const VOS_CHAR * const apcBaseLine[]: 字符串指针数组
  \param[in]  VOS_INT32 lBaseLineLen: apcBaseLine[]中字符串指针个数
  \param[in]  const VOS_CHAR * const apcExtension[]: 后备查找的字符串指针数组
  \param[in]  const VOS_CHAR * const apcExtension[]: 匹配时是否检查大小写
  \return 字符串指针序号
*/
/*********************************************************************************************
   
  brief      查找字符串在数组中的序列号
  param[in]  *pcStr: 待查找的字符串
  param[in]  *apcBaseLine:指定查找的数组(基本数组)
  param[in]  lBaseLineLen:指定查找的数组长度
  param[in]  *apcExtension:指定查找数组的扩展数组
  param[in]  匹配时是否检查大小写
  return     字符串对应的序列号(>=0):成功
             -1:失败
   注意事项： 
1、 apcBaseLine[] 中不能包含NULL指针， apcExtension中必须以NULL结尾
  retval  无错误码
***********************************************************************************************/
VOS_INT32 ATP_UTIL_GetIdxFromStrEx(const VOS_CHAR *pcStr, const VOS_CHAR * const apcBaseLine[],
                                      VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[],
                                      VOS_BOOL bCaseSensitive);
/*********************************************************************************************
   
  brief      查找字符串在数组中的序列号
  param[in]  *pcStr: 待查找的字符串
  param[in]  *apcBaseLine:指定查找的数组(基本数组)
  param[in]  lBaseLineLen:指定查找的数组长度
  param[in]  *apcExtension:指定查找数组的扩展数组
  return     字符串对应的序列号(>=0):成功
             -1:失败
   注意事项： 
1、 apcBaseLine[] 中不能包含NULL指针， apcExtension中必须以NULL结尾
  retval  无错误码
***********************************************************************************************/
VOS_INT32 ATP_UTIL_GetIdxFromStr(const VOS_CHAR *pcStr, const VOS_CHAR * const apcBaseLine[],
                                      VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[]);
/*********************************************************************************************
   
  brief      判断字符串是否在数组内
  param[in]  *pcStr: 待查找的字符串
  param[in]  *apcArray:指定查找的数组
  return     字符串对应的序列号(>=0):成功
             -1:失败
   注意事项： 
1、 apcArray[] 中不能包含NULL指针
  retval  无错误码
***********************************************************************************************/
#define ATP_UTIL_IsStrInArray(pcStr, apcArray) (ATP_UTIL_GetIdxFromStr((pcStr), (apcArray), ATP_ARRAY_LEN((apcArray)), NULL) >= 0)
/*********************************************************************************************
   
  brief      将十六进制数转换为字符形式
  param[out] *pcdst: 转换后字符串
  param[in]  lDstlen: 转换后字符串的长度范围
  param[in]  *pcsrc: 转换前字符串
  param[in]  lStrlen: 源字符串长度
  return     
   注意事项： 
1、 暂无
  retval  无错误码
***********************************************************************************************/
VOS_VOID ATP_UTIL_Hex2Str(VOS_CHAR *pcdst, VOS_INT32 lDstlen, const VOS_CHAR *pcsrc, VOS_INT32 lStrlen);
/*********************************************************************************************
   
  brief      将十六进制数转换为字符形式
  param[out] *pucDst: 转换后字符串
  param[in]  ulDstlen: 转换后字符串的长度范围
  param[in]  *pucSrc: 转换前字符串
  param[in]  ulStrlen: 源字符串长度
  param[in]  bUpper: 将转换后的字符是否改为大写
  return     
   注意事项： 
1、 ulDstlen 的长度应该为ulStrlen*2+1 因为snprintf_s会将最后一个字符设置为"\0"
  retval  无错误码
***********************************************************************************************/
VOS_VOID ATP_UTIL_Hex2StrEx(const VOS_UINT8 *pucSrc, VOS_UINT32 ulStrlen, VOS_UINT8 *pucDst,  VOS_UINT32 ulDstlen, VOS_BOOL bUpper );
/*********************************************************************************************
   
  brief      将原来是16进制字符串转变为ASCII字符串
  param[out] *pDestStr: 转换后字符串
  param[in]  ulDstlen: 转换后字符串的长度范围
  param[in]  *pSrcStr: 原字符串
  return     
   注意事项： 
1、 暂无
  retval  无错误码
***********************************************************************************************/
VOS_VOID ATP_UTIL_HexStr2Bin(VOS_UINT8 *pDestStr, VOS_UINT32 ulDstlen, const VOS_CHAR *pSrcStr);

/*********************************************************************************************
  author      
  brief      将一行字符串按指定的分隔符分离，并返回分隔得到的
              二维字符串数组， 忽略多余的空格和TAB，功能类似js的split
  param[in]  *str: 将被分隔的一个长字符串，一般是文件的一行
  param[in]  *sep:用于分隔长字符串的分隔符，可以是空格
  param[in]  max_strs:允许的最大分隔数组维度
  param[in]  meta:需要忽略的字符
  param[out] *toks:输出的分隔数组的维度
  return     保存分割后结果的数组:成功
             NULL:失败
   注意事项： 
1、 此函数分割成功之后，存在内存分配，需要调用ATP_UTIL_MSplitFree进行释放
  retval  无错误码
***********************************************************************************************/
VOS_CHAR **ATP_UTIL_MSplit(VOS_CHAR *str, VOS_CHAR *sep, VOS_INT32 max_strs, VOS_INT32 *toks, VOS_CHAR meta);
/*********************************************************************************************
  author      
  brief      释放由ATP_UTIL_MSplit分配的内存
  param[in]  ***pbuf: ATP_UTIL_MSplitFree返回的指针的地址
  param[in]  num_toks:ATP_UTIL_MSplitFree分配的数组的维度
  return     
   注意事项： 
1、 pbuf和num_toks为ATP_UTIL_MSplit返回的值
  retval  无错误码
***********************************************************************************************/
VOS_VOID ATP_UTIL_MSplitFree(VOS_CHAR ***pbuf, VOS_INT32 num_toks);

/*!
  \brief 去掉源pszSrc字符串后的换行符，将结果保存在pszDst中
  \param[in]  VOS_CHAR *pszSrc 源字符串
  \param[in]  VOS_UINT32 ulDstLen  目的字符串可以存放的最大字节数，包含结束符
  \param[out] VOS_CHAR *pszDst 保存去掉换行符的字符串
  \return 无
*/
/*********************************************************************************************
  author      
  brief      去掉源pszSrc字符串后的换行符，将结果保存在pszDst中
  param[in]  *pszSrc 源字符串
  param[in]  ulDstLen  目的字符串可以存放的最大字节数，包含结束符
  param[out] *pszDst 保存去掉换行符的字符串
  return     
   注意事项： 
1、 暂无
  retval  无错误码
***********************************************************************************************/
VOS_VOID ATP_UTIL_GetRidOfNewlineSign(VOS_CHAR *pszSrc,  VOS_CHAR *pszDst, VOS_UINT32 ulDstLen);

/*!
  \brief 去掉源pszStr字符串最后的点
  \param[in]  VOS_CHAR *pszStr 源字符串
  \param[out] VOS_CHAR *pszStr 保存去掉最后点的字符串
  \return 无
*/
/*********************************************************************************************
  author      
  brief      去掉源pszStr字符串最后的点
  param[in]  *pszStr 源字符串
  return     
   注意事项： 
1、 该函数直接修改入参中保存的内容，对于入参指定内容不能变化的场景不能使用
  retval  无错误码
***********************************************************************************************/
VOS_VOID ATP_UTIL_GetRidOfLastdot(VOS_CHAR *pszStr);

/*!
  \brief 比较两个DNS域名是否相同, 不区分大小写，考虑全域名(最后为点)
  \param[in]  VOS_CHAR *pszStr1 : 域名1
  \param[in]  VOS_CHAR *pszStr2 : 域名2
  \return VOS_TRUE: 域名相同
*/
/*********************************************************************************************
  author      
  brief      比较两个DNS域名是否相同, 不区分大小写，考虑全域名(最后为点)
  param[in]  *pszStr1 : 域名1
  param[in]  *pszStr2 : 域名2
  return     VOS_TRUE:相同
             VOS_FLASE:不相同
   注意事项： 
1、 该函数比较不区分大小写，同时域名是全域名，最后为点
  retval  无错误码
***********************************************************************************************/
VOS_BOOL ATP_UTIL_CmpDnsDomain(const VOS_CHAR *pszStr1, const VOS_CHAR *pszStr2);
/*********************************************************************************************
  author      
  brief      检查路径中是否存在虚路径，如果存在则修改路径为空
  param[in]  *pcFilePath : 待检查的路径
  return     
   注意事项： 
1、 暂无
  retval  无错误码
***********************************************************************************************/
VOS_VOID ATP_UTIL_StripSlashes(VOS_CHAR *pcFilePath);

/*********************************************************************************************
  author      
  brief      根据一个指定字符找到该字符后面的字符串
  param[in]  *pcStr : 待查找字符串
  param[in]  cMatch : 指定字符
  return     指定字符后面的字符串:成功
             待查找字符串:失败
  
   注意事项： 
1、 查找失败的时候，是直接返回了原字符串
  retval  无错误码
***********************************************************************************************/
const VOS_CHAR *ATP_UTIL_StrRightChr(const VOS_CHAR *pcStr, VOS_CHAR cMatch);
/*********************************************************************************************
   
  brief      安全拷贝字符串函数
  param[in]  *pcStr:待拷贝字符串
  return     拷贝后字符串:成功
             空字符串:失败
  
   注意事项： 
1、 此函数有内存分配，使用完毕注意释放
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_UTIL_SafeStrDup(const VOS_CHAR *pcStr);
/*********************************************************************************************
   
  brief      路径是否匹配
  param[in]  *pattern:包含多个路径，且以"|"分割，或者为单个路径
  param[in]  *string:单个路径
  return     VOS_TRUE:匹配成功
             VOS_FALSE:匹配失败
  
   注意事项： 
1、 如果pattern中有某个路径包含了"*"表示，路径只需要匹配"*"前面的部分
  retval          
***********************************************************************************************/
VOS_BOOL ATP_UTIL_MatchPrefixPath(const VOS_CHAR *pattern, const VOS_CHAR *string);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif


