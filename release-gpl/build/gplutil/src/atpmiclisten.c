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
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#define __ATP_DEPRECATED_H__

#include "atptypes.h"
#include "atpmiclisten.h"



VOS_UINT32 ATP_UTIL_MIC_ResetBackupAppFds( VOS_UINT32 * pulFdsArray, const VOS_UINT32 ulFdsArrSize )
{
    VOS_UINT32              ulIdx = 0;

    if( pulFdsArray != NULL && ulFdsArrSize > 0 )
    {
        for( ulIdx = 0; ulIdx < ulFdsArrSize; ulIdx++ )
        {
            *(pulFdsArray + ulIdx) = 0;
        }

        return VOS_OK;
    }

    return VOS_NOK;
}


VOS_UINT32 ATP_UTIL_MIC_AddBackupAppFds( VOS_UINT32 * pulFdsArray, const VOS_UINT32 ulFdsArrSize, const VOS_UINT32 ulAddFd )
{
    VOS_UINT32              ulIdx = 0;

    if( pulFdsArray != NULL && ulFdsArrSize > 0 && ulAddFd > 0 )
    {
        for( ulIdx = 0; ulIdx < ulFdsArrSize; ulIdx++ )
        {
            if( 0 == *(pulFdsArray + ulIdx) )
            {
                *(pulFdsArray + ulIdx) = ulAddFd;
                return VOS_OK;
            }
        }

        return VOS_NOK;
    }

    return VOS_NOK;
}


VOS_UINT32 ATP_UTIL_MIC_CloseBackupAppFdsReadableConnection( const VOS_UINT32 * pulFdsArray, const VOS_UINT32 ulFdsArrSize )
{
    VOS_UINT32              ulMaxFd = 0;
    VOS_UINT32              ulIdx = 0;
    VOS_INT32               lAcceptFd = 0;
    VOS_INT32               lFind = 0;

    fd_set                  stFdset;
    struct timeval          stTimeVal;

    FD_ZERO(&stFdset);

    for( ulIdx = 0; ulIdx < ulFdsArrSize; ulIdx++ )
    {
        if( *(pulFdsArray + ulIdx) > 0 )
        {
            FD_SET( *(pulFdsArray + ulIdx), &stFdset );
            ulMaxFd = ( ulMaxFd > *(pulFdsArray + ulIdx) ) ? ulMaxFd : *(pulFdsArray + ulIdx);

            lFind = 1;
        }
    }

    if( 1 == lFind )
    {
        stTimeVal.tv_sec  = 0;
        stTimeVal.tv_usec = 0;
        while( select( ulMaxFd + 1, &stFdset, NULL, NULL, &stTimeVal ) > 0 )
        {
            for( ulIdx = 0; ulIdx < ulFdsArrSize; ulIdx++ )
            {
                if ( *(pulFdsArray + ulIdx) > 0 && FD_ISSET( *(pulFdsArray + ulIdx), &stFdset ) )
                {
                    lAcceptFd = accept( *(pulFdsArray + ulIdx), NULL, NULL );

                    if( lAcceptFd > 0 )
                    {
                        close( lAcceptFd );
                    }
                }
            }
        }
    }

    return VOS_OK;
}


