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
 
 #ifndef	_IFADDRS_H
#define	_IFADDRS_H

struct ifaddrs {
	struct ifaddrs  *ifa_next;
	char		*ifa_name;
	unsigned short	 ifa_flags;
	struct sockaddr	*ifa_addr;
	struct sockaddr	*ifa_netmask;
	union{
	    struct sockaddr *ifu_broadaddr;
	    struct sockaddr *ifu_dstaddr;
	} ifa_ifu;
	void		*ifa_data;
};

/*
 * This may have been defined in <net/if.h>.  Note that if <net/if.h> is
 * to be included it must be included before this header file.
 */
#ifndef	ifa_broadaddr
#define	ifa_broadaddr	ifa_ifu.ifu_broadaddr	/* broadcast address */
#endif
#ifndef	ifa_dstaddr
#define	ifa_dstaddr	ifa_ifu.ifu_dstaddr	/* other end of link */
#endif

#include <sys/cdefs.h>

__BEGIN_DECLS
extern int getifaddrs __P((struct ifaddrs **));
extern void freeifaddrs __P((struct ifaddrs *));
__END_DECLS

#endif	/* _IFADDRS_H */
