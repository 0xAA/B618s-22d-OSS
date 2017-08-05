/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 *
 * mobile@huawei.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define __ATP_DEPRECATED_H__

#include "atptypes.h"
#include "atputil.h"

#define  ATP_UTIL_ASCII_ZERO  48

/*5. Common*/

VOS_BOOL ATP_UTIL_RmDelimitor( VOS_CHAR *pcBuf)
{
    VOS_BOOL  bRet = VOS_TRUE;    
    VOS_INT   i = 0;
    VOS_INT   j = 0;


    if ( pcBuf == VOS_NULL ) 
    {
        return VOS_FALSE;
    }

    while((*(pcBuf + i) != '\0') || (*(pcBuf + i + 1) != '\0'))
    {
        if(*(pcBuf + i) == '\0')
        {
            i++;
            continue;
        }
        *(pcBuf + j) = *(pcBuf + i);
        j++;
        i++;
    }
    *(pcBuf + j) = '\0';

    return bRet;

}

/*6. String*/

const VOS_CHAR * ATP_UTIL_StrCat( VOS_CHAR * pcDst, VOS_UINT32 size, const VOS_CHAR * pcSrc )
{
    VOS_UINT32 end = 0;

    if ( ( NULL == pcDst ) || ( NULL == pcSrc ) )
    {
        return pcDst;
    }

    end = strlen ( pcDst );
    if ( end >= size )
    {
        return pcDst;
    }

    snprintf(pcDst + end, size - end - 1,  "%s", pcSrc);


    return pcDst;
}

VOS_CHAR * ATP_UTIL_StrTrim( VOS_CHAR *pszStr )
{ 
    VOS_UINT32   ulLen         = 0;
    VOS_UINT32   ulSeq         = 0;
    VOS_UINT32   ulStart       = 0;
    VOS_UINT32   ulEnd         = 0;

    /*入口参数合法性判断*/
    if ( VOS_NULL_PTR == pszStr )
    {
        return pszStr;
    }

    ulLen = strlen( pszStr );
    if(0 == ulLen)
    {
        return pszStr;
    }

    /*找到非空字符串起始位置*/
    while( isspace( pszStr[ulStart] ))
    {        
        ulStart++; 
    }

    /*找到非空字符串结束位置*/

    ulEnd = strlen(pszStr) -1;

    while((ulEnd > 0) && isspace(pszStr[ulEnd]))
    {
        ulEnd --;
    }

    if(0 == ulEnd)
    {
		/*字符串长度为1的时候有问题*/
        //pszStr[0] = '\0';

        return pszStr;
    }


    ulSeq=0;

    while( ulStart <= ulEnd )
    {
        pszStr[ulSeq] = pszStr[ulStart];
        ulSeq++;
        ulStart++;   
    }
    while( ulSeq < ulLen )
    {
        pszStr[ulSeq] = '\0';   
        ulSeq++;
    }

    return pszStr;
}


/*13. Match Type*/
// return the enum match type according to input string match pattern
ATP_UTIL_CSTRMATCH_PATTERN ATP_UTIL_GetMatchType(const VOS_CHAR * str)
{     
    struct MATCH_TYPE {
        const VOS_CHAR * patternStr;
        ATP_UTIL_CSTRMATCH_PATTERN type;
    };

    const struct MATCH_TYPE matchType[] =
    {
        {"Exact", ATP_UTIL_STRMATCH_EXACT},
        {"Prefix", ATP_UTIL_STRMATCH_PREFIX},
        {"Suffix", ATP_UTIL_STRMATCH_SUFFIX},
        {"Substring", ATP_UTIL_STRMATCH_SUBSTRING},
        {NULL, ATP_UTIL_STRMATCH_ERROR}
    };
    
    VOS_UINT i = 0;
    
    if ( NULL == str ||  '\0' == str[0])
    {
        return ATP_UTIL_STRMATCH_EXACT;
    }

    while (matchType[i].patternStr != NULL)
    {
        if (strcasecmp(matchType[i].patternStr, str) == 0)
        {
            ATP_UTIL_DEBUG("Get match type is %s\n", matchType[i].patternStr);
            return matchType[i].type;
        }
        i++;
    }

    return ATP_UTIL_STRMATCH_ERROR;
}


/****************************************************************************
 * Function:     ATP_UTIL_CstrMatch
 * Parameter:   str: string to be matched, NULL TERMINATED, sample string: "STB 110"
 *                   pattern: source string, pattern used to match, NULL TERMINATED, sample string: "STB"
 *                   type: match type, can be exact, prefix, suffix, substring or others      
 * Return:       VOS_TRUE:  destination string match source string pattern
 *                   VOS_FALSE: destination string not match source string pattern
 * Descripton:  Check whether dst in src string according to the pattern rule, case sensitive
 *****************************************************************************/
VOS_BOOL ATP_UTIL_CstrMatch(const VOS_CHAR * str, const VOS_CHAR * pattern, ATP_UTIL_CSTRMATCH_PATTERN type)
{
     VOS_UINT32 str_len;
     VOS_UINT32 pattern_len;
    if ( NULL == str || NULL == pattern )
    {
        ATP_UTIL_DEBUG("Invalid input parameter\n");
        return VOS_FALSE;
    }

    str_len = strlen(str);
    pattern_len = strlen(pattern);

    if (str_len < pattern_len)   
    {
        ATP_UTIL_DEBUG("string len %d is shorter then pattern string len %d,  match failure\n", str_len, pattern_len);
        return VOS_FALSE;
    }

    ATP_UTIL_DEBUG("Input match type is %d\n", type);
    switch (type)
    {
        case ATP_UTIL_STRMATCH_EXACT :
            if (str_len == pattern_len)
            {  
                return (VOS_BOOL)( strncmp(pattern, str, pattern_len) == 0 ? VOS_TRUE : VOS_FALSE ); 
            }
            return VOS_FALSE;
            
        case ATP_UTIL_STRMATCH_PREFIX :
            return (VOS_BOOL)( strncmp(pattern, str, pattern_len) == 0 ? VOS_TRUE : VOS_FALSE );  

        case ATP_UTIL_STRMATCH_SUFFIX :
            return (VOS_BOOL)( strncmp(pattern, (str + str_len - pattern_len), pattern_len) == 0 ? VOS_TRUE : VOS_FALSE );
           
        case ATP_UTIL_STRMATCH_SUBSTRING :
            return (VOS_BOOL)( strstr(str, pattern) != NULL ? VOS_TRUE : VOS_FALSE );

        default:
            ATP_UTIL_DEBUG("Unkowned match type %d\n", type);
            return VOS_FALSE;
    }

}


VOS_BOOL ATP_UTIL_ConvertStrToShellStr(VOS_CHAR *pszStr, VOS_CHAR *pszConvertedStr) 
{
    VOS_UINT32  j = 0;
    VOS_UINT32  i = 0;
    VOS_UINT32  ulLen = 0;
    VOS_BOOL    bRet = VOS_TRUE;
    
    if ( pszConvertedStr == VOS_NULL ) 
    {
        return VOS_FALSE;
    }

    if ( pszStr == VOS_NULL ) 
    {
        return VOS_FALSE;
    }

#ifdef ATP_PCLINT
    pszStr = pszStr;
#endif
    ulLen = strlen(pszStr);
   
    while(i < ulLen)
    {
        if ( pszStr[i] == '\'' ) 
        {
            pszConvertedStr[j++] = '"';
            pszConvertedStr[j++] = pszStr[i];
            pszConvertedStr[j++] = '"';
        } 
        else 
        {
            pszConvertedStr[j++] = '\'';
            pszConvertedStr[j++] = pszStr[i];
            pszConvertedStr[j++] = '\'';
        }
        i++;
    }

    pszConvertedStr[j]  = '\0';

    return bRet;
}

/*!
  \brief 通过枚举或者整型值来得到相应的字符串
  \param[in]  lIdx: 输入的整型值
  \param[in]  pstSrcStrIdx: 输入的枚举值--字符串对应结构体数组(必须以{NULL ,-1}结束)
  \return 返回整型值对应的字符串
  \retval ATP_E_ERR_CFM_SHM_NOT_ATTACH 初始化共享内存失败
*/
const VOS_CHAR *ATP_UTIL_StrIdxArrayGetStrByIdx(VOS_INT32 lIdx,const ATP_UTIL_STR_IDX_MAP_ST* pstSrcStrIdx)
{
    VOS_UINT32 i = 0;
    
    //!输入的参数不能为空，序号不能小于0
    if(( lIdx < 0)||(NULL == pstSrcStrIdx))
    {
        return NULL;
    }

    //!遍历查找整型值为lIdx的字符串
    while(NULL != pstSrcStrIdx[i].pcStrInfo)
    {
        if(lIdx == pstSrcStrIdx[i].lIdx)
        {
            return pstSrcStrIdx[i].pcStrInfo;
        }
        i++;
    }    
    return NULL;
}


/*!
  \brief 通过输入的字符串得到相应的枚举值或整型值
  \param[in]  *pcStr: 输入的字符串
  \param[in]  pstSrcStrIdx: 输入的枚举值--字符串对应结构体数组(必须以{NULL ,-1}结束)
  \return 返回字符串对应的整型值
  \retval ATP_E_ERR_CFM_SHM_NOT_ATTACH 初始化共享内存失败
*/
VOS_INT32 ATP_UTIL_StrIdxArrayGetIdxByStr(const VOS_CHAR *pcStr,const ATP_UTIL_STR_IDX_MAP_ST* pstSrcStrIdx)
{
    VOS_INT32 i = 0;
    
    if((NULL == pcStr)||(NULL == pstSrcStrIdx))
    {
        return -1;
    }

    //!遍历查找整型值为lIdx的字符串
    while(NULL != pstSrcStrIdx[i].pcStrInfo)
    {
        if(0 == strcmp(pcStr,(const VOS_CHAR*)pstSrcStrIdx[i].pcStrInfo))
        {
            return pstSrcStrIdx[i].lIdx;
        }
        i++;
    }    
    return -1;    
}

/*
 *  String array utility
 */
const VOS_CHAR *ATP_UTIL_GetStrFromIdx(VOS_INT32 lIdx, const VOS_CHAR * const apcBaseLine[],
                                      VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[])
{
    VOS_INT32       lTmp;

    if (lIdx < 0)
    {
        return "";
    }

    /* Return from baseline imediately */
    if (lIdx < lBaseLineLen)
    {
        return apcBaseLine[lIdx];
    }

    /* No extension */
    if (NULL == apcExtension)
    {
        return "";
    }

    /* Find in extension */
    lTmp = 0;
    lIdx -= lBaseLineLen;
    while (NULL != apcExtension[lTmp])
    {
        if (lTmp == lIdx)
        {
            return apcExtension[lTmp];
        }
        lTmp++;
    }

    /* Not found */
    return "";
}


VOS_INT32 ATP_UTIL_GetIdxFromStrEx(const VOS_CHAR *pcStr, const VOS_CHAR * const apcBaseLine[],
                                      VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[],
                                      VOS_BOOL bCaseSensitive)
{
    VOS_INT32           lTmp;

    /* Check input parameters */
    if (NULL == pcStr)
    {
        return -1;
    }

    /* Find in the baseline */
    for (lTmp = 0; (lTmp < lBaseLineLen) && (apcBaseLine) && (NULL != apcBaseLine[lTmp]); lTmp++)
    {
        if (VOS_FALSE == bCaseSensitive)
        {
            if (0 == strcasecmp(pcStr, apcBaseLine[lTmp]))
            {
                return lTmp;
            }
        }
        else
        {
            if (0 == strcmp(pcStr, apcBaseLine[lTmp]))
            {
                return lTmp;
            }
        }
    }

    /* Check in the extension */
    if (NULL == apcExtension)
    {
        return -1;
    }

    /* Find in the extension */
    lTmp = 0;
    while (NULL != apcExtension[lTmp])
    {
        if (VOS_FALSE == bCaseSensitive)
        {
            if (0 == strcasecmp(pcStr, apcExtension[lTmp]))
            {
                return (lTmp + lBaseLineLen);
            }
        }
        else
        {
            if (0 == strcmp(pcStr, apcExtension[lTmp]))
            {
                return (lTmp + lBaseLineLen);
            }
        }        
        lTmp++;
    }

    /* Not found */
    return -1;
}

VOS_INT32 ATP_UTIL_GetIdxFromStr(const VOS_CHAR *pcStr, const VOS_CHAR * const apcBaseLine[],
                                      VOS_INT32 lBaseLineLen, const VOS_CHAR * const apcExtension[])
{
    return ATP_UTIL_GetIdxFromStrEx(pcStr, apcBaseLine, lBaseLineLen, apcExtension, VOS_FALSE);
}

/*!
  \brief  将十六进制数转换为字符形式
  \param[out] *pcdst: 转换后字符串
  \param[in]  *lDstlen: 转换后字符串的长度范围
  \param[in]  *pcsrc: 转换前字符串
  \param[in]  lStrlen: 源字符串长度
  \return 
  \retval ATP_E_ERR_CFM_SHM_NOT_ATTACH 初始化共享内存失败
*/
VOS_VOID ATP_UTIL_Hex2Str(VOS_CHAR *pcdst, VOS_INT32 lDstlen, const VOS_CHAR *pcsrc,  VOS_INT32 lStrlen )
{
    VOS_INT32 i = 0;
    VOS_INT32 j = 0;
    VOS_INT32 num = 0;

    if( NULL == pcsrc )
    {
        printf("ATP_UTIL_Hex2Str pcsrc is empty\n");
        return;
    }
    
    //获取字节的高四位和低四位
    for(i = 0; (i < lStrlen) && (j + 1 < lDstlen); i++)
    {
        pcdst[j] = (pcsrc[i] & 0xf0) >> 4;
        pcdst[j+1] = pcsrc[i] & 0x0f;
        j = j + 2;
    }
    //将获取的十六进制值转为字符形式
    for(i = 0; i < j; i++)
    {   
        num = pcdst[i] % 16;
        switch(num)
        {
            case 15:
                pcdst[i]='f';
                break;
            case 14:
                pcdst[i]='e';
                break;
            case 13:
                pcdst[i]='d';
                break;
            case 12:
                pcdst[i]='c';
                break;
            case 11:
                pcdst[i]='b';
                break;
            case 10:
                pcdst[i]='a';
                break;
            default:
                pcdst[i]=num+ATP_UTIL_ASCII_ZERO;
                break;
        }
    }  
    pcdst[i]='\0';
}


VOS_CHAR **ATP_UTIL_MSplit(VOS_CHAR *str, VOS_CHAR *sep, VOS_INT32 max_strs, VOS_INT32 *toks, VOS_CHAR meta)
{
    VOS_CHAR **retstr;      /* 2D array which is returned to caller */
    VOS_CHAR *idx;          /* index pointer into str */
    VOS_CHAR *end;          /* ptr to end of str */
    VOS_CHAR *sep_end;      /* ptr to end of seperator string */
    VOS_CHAR *sep_idx;      /* index ptr into seperator string */
    VOS_INT32 len = 0;        /* length of current token string */
    VOS_INT32 curr_str = 0;       /* current index into the 2D return array */
    VOS_CHAR last_char = (VOS_CHAR) 0xFF;

    if (!toks)
    {
        return VOS_NULL;
    }

    *toks = 0;

    if (!str)
    {
        return VOS_NULL;
    }

    /* find the ends of the respective passed strings so our while() loops know where to stop */
    sep_end = sep + strlen(sep);
    end = str + strlen(str);

    /* remove trailing whitespace */
    while (isspace((VOS_INT32) *(end - 1)) && ((end - 1) >= str))
    {
        *(--end) = '\0';    /* -1 because of NULL */
    }

    /* set our indexing pointers */
    sep_idx = sep;
    idx = str;

    /* alloc space for the return string, this is where the pointers to the tokens will be stored */
	if ( sizeof(VOS_CHAR *) * max_strs <= 0 )
	{
	    return VOS_NULL;
	}
    retstr = (VOS_CHAR **)malloc((sizeof(VOS_CHAR *) * max_strs));
    if (VOS_NULL == retstr)
    {
        return VOS_NULL;
    }

    memset(retstr, 0, sizeof(char *) * max_strs);
	//memset_s(retstr, sizeof(VOS_CHAR *) * max_strs, 0, sizeof(VOS_CHAR *) * max_strs);

    max_strs--;

    /* loop thru each letter in the string being tokenized */
    while (idx < end)
    {
        /* loop thru each seperator string char */
        while (sep_idx < sep_end)
        {
            /* if the current string-indexed char matches the current seperator char... */
            if ('\0' == *idx)
            {
                *toks = curr_str;
                return retstr;
            }

            if ((*idx != *sep_idx) || (last_char == meta))
            {
                /* go to the next seperator */
                sep_idx++;
                continue;
            }

            /* otherwise, the previous char was a seperator as well, and we should just continue */
            if (0 >= len)
            {
                last_char = *idx;
                idx++;
                /* make sure to reset this so we test all the sep. chars */
                sep_idx = sep;
                len = 0;
                continue;
            }
            
            /* if there's something to store... */
            if (curr_str <= max_strs)
            {
                /* allocate space for the new token */
                retstr[curr_str] = (VOS_CHAR *)malloc((sizeof(VOS_CHAR) * len) + 1);
                if (VOS_NULL == retstr[curr_str])
                {
                    *toks = curr_str;
                    return retstr;
                }

                /* copy the token into the return string array */
                memcpy(retstr[curr_str], (idx - len), (sizeof(char) * len));
                retstr[curr_str][len] = 0;

                /* twiddle the necessary pointers and vars */
                len = 0;
                curr_str++;
                last_char = *idx;
                idx++;
            }

            /* if we've gotten all the tokens requested, return the list */
            if (curr_str >= max_strs)
            {
                while (isspace((VOS_INT32) *idx))
                {
                    idx++;
                }

                len = (VOS_INT32)(end - idx);

                retstr[curr_str] = (VOS_CHAR *)malloc((sizeof(VOS_CHAR) * len) + 1);
                if (VOS_NULL == retstr[curr_str])
                {
                    *toks = curr_str;
                    return retstr;
                }
                memcpy(retstr[curr_str], idx, len);
                retstr[curr_str][len] = 0;

                *toks = curr_str + 1;
                return retstr;
            }
        }

        sep_idx = sep;
        len++;
        last_char = *idx;
        idx++;
    }

    /* put the last string into the list */
    if(len > 0)
    {
        retstr[curr_str] = (VOS_CHAR *)malloc((sizeof(VOS_CHAR) * len) + 1);
        if (VOS_NULL == retstr[curr_str])
        {
            *toks = curr_str;
            return retstr;
        }
        
        memcpy(retstr[curr_str], (idx - len), len);
        retstr[curr_str][len] = 0;
        *toks = curr_str + 1;
    }

    /* return the token list */
    return retstr;
}



VOS_VOID ATP_UTIL_MSplitFree(VOS_CHAR ***pbuf, VOS_INT32 num_toks)
{
    VOS_INT32 i;
    VOS_CHAR** buf;  /* array of string pointers */

    if (VOS_NULL == pbuf || VOS_NULL == *pbuf)
    {
        return;
    }

    buf = *pbuf;

    for (i = 0; i < num_toks; i++ )
    {
        ATP_FREE(buf[i]);
    }

    ATP_FREE(buf);
    *pbuf = VOS_NULL;
}


VOS_VOID ATP_UTIL_GetRidOfNewlineSign(VOS_CHAR *pszSrc,  VOS_CHAR *pszDst, VOS_UINT32 ulDstLen)
{
    VOS_UINT32 ulLen = 0;
    if ((NULL == pszSrc) || (NULL == pszDst))
    {
        return;
    }
    snprintf(pszDst, ulDstLen - 1, "%s", pszSrc);
    
    /*如果最后字符为换行字符，转换为结束符，否则不做任何操作*/
    ulLen = strlen(pszDst);
    if (0 == ulLen)
    {
       return;
    }
    if ('\n' == pszDst[ulLen-1])
    {
        pszDst[ulLen-1] = '\0';
    }
    return;
}


VOS_VOID ATP_UTIL_GetRidOfLastdot(VOS_CHAR *pszStr)
{
    VOS_UINT32 ulLen = 0;
    if (NULL == pszStr)
    {
        return ;
    }    
    ulLen = strlen(pszStr);
    if ((0 < ulLen) &&(pszStr[ulLen-1] == '.'))
    {
        pszStr[ulLen-1] = '\0';
    }    
    return;
}


VOS_BOOL ATP_UTIL_CmpDnsDomain(const VOS_CHAR *pszStr1, const VOS_CHAR *pszStr2)
{
    VOS_CHAR acDomain1[ATP_STRING_LEN_256] = {0};
    VOS_CHAR acDomain2[ATP_STRING_LEN_256] = {0};

    if (NULL == pszStr1 || NULL == pszStr2)
    {
        return VOS_FALSE;
    }    
    
    snprintf(acDomain1, sizeof(acDomain1) - 1, "%s", pszStr1);
    snprintf(acDomain2, sizeof(acDomain2) - 1, "%s", pszStr2);

    ATP_UTIL_GetRidOfLastdot(acDomain1);
    ATP_UTIL_GetRidOfLastdot(acDomain2);
    if (0 == strcasecmp(acDomain1, acDomain2))
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}


VOS_VOID ATP_UTIL_StripSlashes(VOS_CHAR *pcFilePath)
{
    if (NULL == pcFilePath)
    {
        return;
    }
    if ((NULL != strstr(pcFilePath, "../")) || (NULL != strstr(pcFilePath, "./")))
    {
        pcFilePath[0] = '\0';
    }
}



const VOS_CHAR *ATP_UTIL_StrRightChr(const VOS_CHAR *pcStr, VOS_CHAR cMatch)
{
    const VOS_CHAR *pcRet;

    pcRet = strchr(pcStr, cMatch);
    if (NULL == pcRet)
    {
        return pcStr;
    }
    while (NULL != pcRet)
    {
        pcStr = pcRet + 1;
        pcRet = strchr(pcStr, cMatch);
    }
    return pcStr;
}


