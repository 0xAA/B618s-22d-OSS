/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file strutil.h
  *
  *\copyright 2017-2030����Ϊ�������޹�˾
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
  \brief ִ���ַ���strcat��������pcSrc�е�����������pcDst���棬��ȫ���롣
  \param[in]  pcDst: Ŀ���ַ���
  \param[in]  size: ���Ӻ���ַ�������
  \param[in]  pcSrc: �������ַ���
  \return ���Ӻ���ַ���
  \retval pcDst
*/
/*********************************************************************************************
   
  brief      ִ���ַ���strcat��������pcSrc�е�����������pcDst���棬��ȫ����
  param[in]  pcDst: Ŀ���ַ���
  param[in]  size: ���Ӻ���ַ�������
  param[in]  pcSrc: �������ַ���
  return     ���Ӻ���ַ���:�ɹ�
             NULL:ʧ��
   ע����� 
1�� ����
  retval  �޴�����
***********************************************************************************************/
const VOS_CHAR * ATP_UTIL_StrCat(VOS_CHAR * pcDst, VOS_UINT32 size, const VOS_CHAR * pcSrc);
/*!
  \brief ִ���ַ���Trim������ȥ����ͷ�Ŀհ��ַ�,
          ��ԭ�ַ������޸ģ�δ���ٿռ�,����Ϊ�ո�ʱ��ֱ�ӷ���
  \param[in]  *pszStr: ������ַ���������Ϊ��
  \return  Trim����ַ���ָ��
  \retval pszStr  Trim����ַ���ָ�룬����Ϊ��
*/
/*********************************************************************************************
   
  brief      ִ���ַ���Trim������ȥ����ͷ�Ŀհ��ַ�,
             ��ԭ�ַ������޸ģ�δ���ٿռ�,����Ϊ�ո�ʱ��ֱ�ӷ���
  param[in]  *pszStr: ������ַ���������Ϊ��
  return     Trim����ַ���ָ��:�ɹ�
             NULL:ʧ��
   ע����� 
1�� �ú���ֱ�Ӷ����ָ�������������޸ģ��������ָ�����ݲ����޸ĵĳ�������ʹ��
  retval  �޴�����
***********************************************************************************************/
VOS_CHAR * ATP_UTIL_StrTrim( VOS_CHAR *pszStr );

typedef struct tagATP_UTIL_STR_IDX_MAP_ST
{
    const VOS_CHAR      *pcStrInfo;
    VOS_INT32           lIdx;
} ATP_UTIL_STR_IDX_MAP_ST;

/*********************************************************************************************
   
  brief      ͨ��ö�ٻ�������ֵ���õ���Ӧ���ַ���
  param[in]  lIdx: ���������ֵ
  param[in]  *pstSrcStrIdx: �����ö��ֵ--�ַ�����Ӧ�ṹ������(������{NULL ,-1}����)
  return     ����ֵ��Ӧ���ַ���:�ɹ�
             NULL:ʧ��
   ע����� 
1�� ����
  retval  �޴�����
***********************************************************************************************/
const VOS_CHAR *ATP_UTIL_StrIdxArrayGetStrByIdx(VOS_INT32 lIdx,const ATP_UTIL_STR_IDX_MAP_ST* pstSrcStrIdx);

/*********************************************************************************************
   
  brief      ͨ��������ַ����õ���Ӧ��ö��ֵ������ֵ
  param[in]  *pcStr: ������ַ���
  param[in]  pstSrcStrIdx: �����ö��ֵ--�ַ�����Ӧ�ṹ������(������{NULL ,-1}����)
  return     �ַ�����Ӧ������ֵ(>=0):�ɹ�
             -1:ʧ��
   ע����� 
1�� ����
  retval  �޴�����
***********************************************************************************************/
VOS_INT32 ATP_UTIL_StrIdxArrayGetIdxByStr(const VOS_CHAR *pcStr,const ATP_UTIL_STR_IDX_MAP_ST* pstSrcStrIdx);
/*********************************************************************************************
   
  brief      ���ַ���ָ�������в���ָ�����кŵ��ַ���
  param[in]  lIdx: �ַ����������ڵ����к�
  param[in]  *apcBaseLine:ָ�����ҵ�����(��������)
  param[in]  lBaseLineLen:ָ�����ҵ����鳤��
  param[in]  *apcExtension:ָ�������������չ����
  return     �������кŶ�Ӧ���ַ���:�ɹ�
             NULL:ʧ��
   ע����� 
1�� apcBaseLine[] �в��ܰ���NULLָ�룬 apcExtension�б�����NULL��β
  retval  �޴�����
***********************************************************************************************/
const VOS_CHAR *ATP_UTIL_GetStrFromIdx(VOS_INT32 lIdx, const VOS_CHAR * const apcBaseLine[],
                                  VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[]);

/*!
  \brief  ���ַ���ָ�������в���ָ�����ַ��������ظ��ַ��������
  \param[in]  const VOS_CHAR *pcStr: Ҫ���ҵ��ַ���
  \param[in]  const VOS_CHAR * const apcBaseLine[]: �ַ���ָ������
  \param[in]  VOS_INT32 lBaseLineLen: apcBaseLine[]���ַ���ָ�����
  \param[in]  const VOS_CHAR * const apcExtension[]: �󱸲��ҵ��ַ���ָ������
  \param[in]  const VOS_CHAR * const apcExtension[]: ƥ��ʱ�Ƿ����Сд
  \return �ַ���ָ�����
*/
/*********************************************************************************************
   
  brief      �����ַ����������е����к�
  param[in]  *pcStr: �����ҵ��ַ���
  param[in]  *apcBaseLine:ָ�����ҵ�����(��������)
  param[in]  lBaseLineLen:ָ�����ҵ����鳤��
  param[in]  *apcExtension:ָ�������������չ����
  param[in]  ƥ��ʱ�Ƿ����Сд
  return     �ַ�����Ӧ�����к�(>=0):�ɹ�
             -1:ʧ��
   ע����� 
1�� apcBaseLine[] �в��ܰ���NULLָ�룬 apcExtension�б�����NULL��β
  retval  �޴�����
***********************************************************************************************/
VOS_INT32 ATP_UTIL_GetIdxFromStrEx(const VOS_CHAR *pcStr, const VOS_CHAR * const apcBaseLine[],
                                      VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[],
                                      VOS_BOOL bCaseSensitive);
/*********************************************************************************************
   
  brief      �����ַ����������е����к�
  param[in]  *pcStr: �����ҵ��ַ���
  param[in]  *apcBaseLine:ָ�����ҵ�����(��������)
  param[in]  lBaseLineLen:ָ�����ҵ����鳤��
  param[in]  *apcExtension:ָ�������������չ����
  return     �ַ�����Ӧ�����к�(>=0):�ɹ�
             -1:ʧ��
   ע����� 
1�� apcBaseLine[] �в��ܰ���NULLָ�룬 apcExtension�б�����NULL��β
  retval  �޴�����
***********************************************************************************************/
VOS_INT32 ATP_UTIL_GetIdxFromStr(const VOS_CHAR *pcStr, const VOS_CHAR * const apcBaseLine[],
                                      VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[]);
/*********************************************************************************************
   
  brief      �ж��ַ����Ƿ���������
  param[in]  *pcStr: �����ҵ��ַ���
  param[in]  *apcArray:ָ�����ҵ�����
  return     �ַ�����Ӧ�����к�(>=0):�ɹ�
             -1:ʧ��
   ע����� 
1�� apcArray[] �в��ܰ���NULLָ��
  retval  �޴�����
***********************************************************************************************/
#define ATP_UTIL_IsStrInArray(pcStr, apcArray) (ATP_UTIL_GetIdxFromStr((pcStr), (apcArray), ATP_ARRAY_LEN((apcArray)), NULL) >= 0)
/*********************************************************************************************
   
  brief      ��ʮ��������ת��Ϊ�ַ���ʽ
  param[out] *pcdst: ת�����ַ���
  param[in]  lDstlen: ת�����ַ����ĳ��ȷ�Χ
  param[in]  *pcsrc: ת��ǰ�ַ���
  param[in]  lStrlen: Դ�ַ�������
  return     
   ע����� 
1�� ����
  retval  �޴�����
***********************************************************************************************/
VOS_VOID ATP_UTIL_Hex2Str(VOS_CHAR *pcdst, VOS_INT32 lDstlen, const VOS_CHAR *pcsrc, VOS_INT32 lStrlen);
/*********************************************************************************************
   
  brief      ��ʮ��������ת��Ϊ�ַ���ʽ
  param[out] *pucDst: ת�����ַ���
  param[in]  ulDstlen: ת�����ַ����ĳ��ȷ�Χ
  param[in]  *pucSrc: ת��ǰ�ַ���
  param[in]  ulStrlen: Դ�ַ�������
  param[in]  bUpper: ��ת������ַ��Ƿ��Ϊ��д
  return     
   ע����� 
1�� ulDstlen �ĳ���Ӧ��ΪulStrlen*2+1 ��Ϊsnprintf_s�Ὣ���һ���ַ�����Ϊ"\0"
  retval  �޴�����
***********************************************************************************************/
VOS_VOID ATP_UTIL_Hex2StrEx(const VOS_UINT8 *pucSrc, VOS_UINT32 ulStrlen, VOS_UINT8 *pucDst,  VOS_UINT32 ulDstlen, VOS_BOOL bUpper );
/*********************************************************************************************
   
  brief      ��ԭ����16�����ַ���ת��ΪASCII�ַ���
  param[out] *pDestStr: ת�����ַ���
  param[in]  ulDstlen: ת�����ַ����ĳ��ȷ�Χ
  param[in]  *pSrcStr: ԭ�ַ���
  return     
   ע����� 
1�� ����
  retval  �޴�����
***********************************************************************************************/
VOS_VOID ATP_UTIL_HexStr2Bin(VOS_UINT8 *pDestStr, VOS_UINT32 ulDstlen, const VOS_CHAR *pSrcStr);

/*********************************************************************************************
  author      
  brief      ��һ���ַ�����ָ���ķָ������룬�����طָ��õ���
              ��ά�ַ������飬 ���Զ���Ŀո��TAB����������js��split
  param[in]  *str: �����ָ���һ�����ַ�����һ�����ļ���һ��
  param[in]  *sep:���ڷָ����ַ����ķָ����������ǿո�
  param[in]  max_strs:��������ָ�����ά��
  param[in]  meta:��Ҫ���Ե��ַ�
  param[out] *toks:����ķָ������ά��
  return     ����ָ����������:�ɹ�
             NULL:ʧ��
   ע����� 
1�� �˺����ָ�ɹ�֮�󣬴����ڴ���䣬��Ҫ����ATP_UTIL_MSplitFree�����ͷ�
  retval  �޴�����
***********************************************************************************************/
VOS_CHAR **ATP_UTIL_MSplit(VOS_CHAR *str, VOS_CHAR *sep, VOS_INT32 max_strs, VOS_INT32 *toks, VOS_CHAR meta);
/*********************************************************************************************
  author      
  brief      �ͷ���ATP_UTIL_MSplit������ڴ�
  param[in]  ***pbuf: ATP_UTIL_MSplitFree���ص�ָ��ĵ�ַ
  param[in]  num_toks:ATP_UTIL_MSplitFree����������ά��
  return     
   ע����� 
1�� pbuf��num_toksΪATP_UTIL_MSplit���ص�ֵ
  retval  �޴�����
***********************************************************************************************/
VOS_VOID ATP_UTIL_MSplitFree(VOS_CHAR ***pbuf, VOS_INT32 num_toks);

/*!
  \brief ȥ��ԴpszSrc�ַ�����Ļ��з��������������pszDst��
  \param[in]  VOS_CHAR *pszSrc Դ�ַ���
  \param[in]  VOS_UINT32 ulDstLen  Ŀ���ַ������Դ�ŵ�����ֽ���������������
  \param[out] VOS_CHAR *pszDst ����ȥ�����з����ַ���
  \return ��
*/
/*********************************************************************************************
  author      
  brief      ȥ��ԴpszSrc�ַ�����Ļ��з��������������pszDst��
  param[in]  *pszSrc Դ�ַ���
  param[in]  ulDstLen  Ŀ���ַ������Դ�ŵ�����ֽ���������������
  param[out] *pszDst ����ȥ�����з����ַ���
  return     
   ע����� 
1�� ����
  retval  �޴�����
***********************************************************************************************/
VOS_VOID ATP_UTIL_GetRidOfNewlineSign(VOS_CHAR *pszSrc,  VOS_CHAR *pszDst, VOS_UINT32 ulDstLen);

/*!
  \brief ȥ��ԴpszStr�ַ������ĵ�
  \param[in]  VOS_CHAR *pszStr Դ�ַ���
  \param[out] VOS_CHAR *pszStr ����ȥ��������ַ���
  \return ��
*/
/*********************************************************************************************
  author      
  brief      ȥ��ԴpszStr�ַ������ĵ�
  param[in]  *pszStr Դ�ַ���
  return     
   ע����� 
1�� �ú���ֱ���޸�����б�������ݣ��������ָ�����ݲ��ܱ仯�ĳ�������ʹ��
  retval  �޴�����
***********************************************************************************************/
VOS_VOID ATP_UTIL_GetRidOfLastdot(VOS_CHAR *pszStr);

/*!
  \brief �Ƚ�����DNS�����Ƿ���ͬ, �����ִ�Сд������ȫ����(���Ϊ��)
  \param[in]  VOS_CHAR *pszStr1 : ����1
  \param[in]  VOS_CHAR *pszStr2 : ����2
  \return VOS_TRUE: ������ͬ
*/
/*********************************************************************************************
  author      
  brief      �Ƚ�����DNS�����Ƿ���ͬ, �����ִ�Сд������ȫ����(���Ϊ��)
  param[in]  *pszStr1 : ����1
  param[in]  *pszStr2 : ����2
  return     VOS_TRUE:��ͬ
             VOS_FLASE:����ͬ
   ע����� 
1�� �ú����Ƚϲ����ִ�Сд��ͬʱ������ȫ���������Ϊ��
  retval  �޴�����
***********************************************************************************************/
VOS_BOOL ATP_UTIL_CmpDnsDomain(const VOS_CHAR *pszStr1, const VOS_CHAR *pszStr2);
/*********************************************************************************************
  author      
  brief      ���·�����Ƿ������·��������������޸�·��Ϊ��
  param[in]  *pcFilePath : ������·��
  return     
   ע����� 
1�� ����
  retval  �޴�����
***********************************************************************************************/
VOS_VOID ATP_UTIL_StripSlashes(VOS_CHAR *pcFilePath);

/*********************************************************************************************
  author      
  brief      ����һ��ָ���ַ��ҵ����ַ�������ַ���
  param[in]  *pcStr : �������ַ���
  param[in]  cMatch : ָ���ַ�
  return     ָ���ַ�������ַ���:�ɹ�
             �������ַ���:ʧ��
  
   ע����� 
1�� ����ʧ�ܵ�ʱ����ֱ�ӷ�����ԭ�ַ���
  retval  �޴�����
***********************************************************************************************/
const VOS_CHAR *ATP_UTIL_StrRightChr(const VOS_CHAR *pcStr, VOS_CHAR cMatch);
/*********************************************************************************************
   
  brief      ��ȫ�����ַ�������
  param[in]  *pcStr:�������ַ���
  return     �������ַ���:�ɹ�
             ���ַ���:ʧ��
  
   ע����� 
1�� �˺������ڴ���䣬ʹ�����ע���ͷ�
  retval          
***********************************************************************************************/
VOS_CHAR *ATP_UTIL_SafeStrDup(const VOS_CHAR *pcStr);
/*********************************************************************************************
   
  brief      ·���Ƿ�ƥ��
  param[in]  *pattern:�������·��������"|"�ָ����Ϊ����·��
  param[in]  *string:����·��
  return     VOS_TRUE:ƥ��ɹ�
             VOS_FALSE:ƥ��ʧ��
  
   ע����� 
1�� ���pattern����ĳ��·��������"*"��ʾ��·��ֻ��Ҫƥ��"*"ǰ��Ĳ���
  retval          
***********************************************************************************************/
VOS_BOOL ATP_UTIL_MatchPrefixPath(const VOS_CHAR *pattern, const VOS_CHAR *string);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif


