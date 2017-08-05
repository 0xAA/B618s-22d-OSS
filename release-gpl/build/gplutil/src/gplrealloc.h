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
#ifndef __GPLREALLOC_H__
#define __GPLREALLOC_H__

#include "atptypes.h"

static inline void* gpl_realloc(void *src, size_t src_size, size_t alloc_size)
{
    void *dest = NULL;
    dest = malloc(alloc_size);

    if (NULL == src)
    {
        if (NULL != dest)
        {
            memset(dest, 0, alloc_size);
        }
        return dest;
    }

    if (NULL == dest)
    {
        free(src);
		src = NULL;
        return NULL;
    }
	
	memset(dest, 0, alloc_size);
	
    if (alloc_size <= src_size)
    {
        memcpy(dest,  src, alloc_size);
    }
    else
    {
        memcpy(dest,  src, src_size);
    }

    free(src);
	src = NULL;
    return dest;
}


#endif  //end #ifndef __LOGINCTL_H__


