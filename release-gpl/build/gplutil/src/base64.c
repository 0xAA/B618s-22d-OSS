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

#include "atptypes.h"

static const VOS_CHAR cb64[]="";
static const VOS_CHAR cd64[]="";

/* encode 3 8-bit binary bytes as 4 '6-bit' characters */
static VOS_VOID B64_EncodeBlock(const VOS_UINT8 in[3], VOS_UINT8 out[4], VOS_INT32 len )
{
    out[0] = (VOS_UINT8)cb64[ in[0] >> 2 ];
    out[1] = (VOS_UINT8)cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (VOS_UINT8) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (VOS_UINT8) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}



VOS_INT32 ATP_UTIL_Base64Encode(const VOS_UINT8* pucInput, VOS_INT32 lInputlen, VOS_UINT8** ppucOutput)
{
    VOS_UINT8* out;
    const VOS_UINT8* in;

    if ((NULL == pucInput) || (lInputlen <= 0) || (NULL == ppucOutput))
    {
        if (NULL != ppucOutput)
        {
            (*ppucOutput) = NULL;
        }
        return 0;
    }

    *ppucOutput = (VOS_UINT8*)malloc((VOS_UINT32)((lInputlen * 4) / 3) + 5);
    if (NULL == *ppucOutput)
    {
        return 0;
    }
    out = *ppucOutput;
    in  = pucInput;

    while ((in+3) <= (pucInput+lInputlen))
    {
        B64_EncodeBlock(in, out, 3);
        in += 3;
        out += 4;
    }
    if ((pucInput+lInputlen)-in == 1)
    {
        B64_EncodeBlock(in, out, 1);
        out += 4;
    }
    else
        if ((pucInput+lInputlen)-in == 2)
        {
            B64_EncodeBlock(in, out, 2);
            out += 4;
        }
    *out = 0;

    return (VOS_INT32)(out-*ppucOutput);
}

/* Decode 4 '6-bit' characters into 3 8-bit binary bytes */
static VOS_VOID B64_DecodeBlock( VOS_UINT8 in[4], VOS_UINT8 out[3] )
{
#ifdef ATP_PCLINT
    in = in;
#endif
    out[ 0 ] = (VOS_UINT8 ) (in[0] << 2 | in[1] >> 4);
    out[ 1 ] = (VOS_UINT8 ) (in[1] << 4 | in[2] >> 2);
    out[ 2 ] = (VOS_UINT8 ) (((in[2] << 6) & 0xc0) | in[3]);
}

/*
 * Return VOS_TRUE if 'c' is a valid base64 character, otherwise VOS_FALSE
 */
static VOS_BOOL B64_IsBase64Char(char c)
{
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
       (c >= '0' && c <= '9') || (c == '+')             ||
       (c == '/'))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_INT32 ATP_UTIL_Base64Decode(const VOS_UINT8* pucInput, VOS_INT32 lInputlen, VOS_UINT8** ppucOutput)
{
    const VOS_UINT8* inptr;
    VOS_UINT8* out;
    VOS_UINT8 v;
    VOS_UINT8 in[4];
    VOS_INT32 i, len;

    if ((NULL == pucInput) || (lInputlen < 4) || (NULL == ppucOutput))
    {
        if (NULL != ppucOutput)
        {
            (*ppucOutput) = NULL;
        }
        return 0;
    }

    len = lInputlen;
    if ('=' == pucInput[len - 1])
    {
        len -= 1;
        if ('=' == pucInput[len - 1])
        {
            len -= 1;
        }
    }
    for (i = 0; i < len; i++)
    {
        if (VOS_FALSE == B64_IsBase64Char((VOS_CHAR)pucInput[i]))
        {
            return 0;
        }
    }

    *ppucOutput = (VOS_UINT8*)malloc((VOS_UINT32)((lInputlen * 3) / 4) + 4);
    out = *ppucOutput;
    inptr = pucInput;

    while( inptr <= (pucInput+lInputlen) )
    {
        for( len = 0, i = 0; i < 4 && inptr <= (pucInput+lInputlen); i++ )
        {
            v = 0;
            while( inptr <= (pucInput+lInputlen) && v == 0 )
            {
                v = (VOS_UINT8) *inptr;
                inptr++;
                v = (VOS_UINT8) ((v < 43 || v > 122) ? 0 : cd64[ v - 43 ]);
                if( v ) 
                {
                    v = (VOS_UINT8) ((v == '$') ? 0 : v - 61);
                }
            }
            if( inptr <= (pucInput+lInputlen) ) 
            {
                len++;
                if (v)
                {
                    in[ i ] = (VOS_UINT8) (v - 1);
                }
            }
            else 
            {
                in[i] = 0;
            }
        }
        if( len )
        {
            B64_DecodeBlock( in, out );
            out += len-1;
        }
    }
    *out = 0;
    return (VOS_INT32)(out-*ppucOutput);
}

VOS_UINT32 ATP_UTIL_Base64EncodeEx(
                                const VOS_UINT8* pucInput, 
                                const VOS_UINT32 ulInputlen, 
                                VOS_UINT8** ppucOutput, 
                                VOS_UINT32 *pulOutputLen)
{
    VOS_INT32 iRetVal = 0;

    iRetVal = ATP_UTIL_Base64Encode(pucInput, (VOS_INT32)ulInputlen, ppucOutput);
    if (0 == iRetVal)
    {
        return VOS_NOK;
    }

    if (pulOutputLen)
    {
        *pulOutputLen = (VOS_UINT32)iRetVal;
    }

    return VOS_OK;
}


VOS_UINT32 ATP_UTIL_Base64DecodeEx(
                                const VOS_UINT8* pucInput, 
                                VOS_UINT32 ulInputlen, 
                                VOS_UINT8** ppucOutput, 
                                VOS_UINT32 *pulOutputLen)
{
    VOS_INT32 iRetVal = 0;

    iRetVal = ATP_UTIL_Base64Decode(pucInput, (VOS_INT32)ulInputlen, ppucOutput);
    if (0 == iRetVal)
    {
        return VOS_NOK;
    }

    if (pulOutputLen)
    {
        *pulOutputLen = (VOS_UINT32)iRetVal;
    }

    return VOS_OK;
}

