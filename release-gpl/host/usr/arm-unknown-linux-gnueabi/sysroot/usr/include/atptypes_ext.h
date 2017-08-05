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

#ifndef __ATP_TYPES_EXT_H__
#define __ATP_TYPES_EXT_H__

#include <asm/byteorder.h>
#include "atptypes.h"

#ifdef  __cplusplus
extern "C" {
#endif


/* hybrid增加的双整型 */
typedef union tagDULONG
{
	struct tagULONG_UL
	{
		VOS_UINT32 ulHi_l;
		VOS_UINT32 ulLo_l;
	}x;
	struct tagULONG_US
	{
#if defined (__BIG_ENDIAN_BITFIELD)
		VOS_UINT16 usHiHi_s;
		VOS_UINT16 usHiLo_s;
		VOS_UINT16 usLoHi_s;
		VOS_UINT16 usLoLo_s;
#else
		VOS_UINT16 usHiLo_s;
		VOS_UINT16 usHiHi_s;
		VOS_UINT16 usLoLo_s;
		VOS_UINT16 usLoHi_s;
#endif
	}y;
}DULONG;

#define ulHi	x.ulHi_l
#define ulLo	x.ulLo_l
#define usHiHi  y.usHiHi_s
#define usHiLo  y.usHiLo_s
#define usLoHi  y.usLoHi_s
#define usLoLo  y.usLoLo_s

/* 	dulFirst<dulSecond:		return -1;
	dulFirst>dulSecond: 	return 1;
	dulFirst==dulSecond:	return 0;
*/
#define DULONG_COMPARE(dulFirst,dulSecond) \
	(((dulFirst).ulHi<(dulSecond).ulHi)?-1: \
		(((dulFirst).ulHi>(dulSecond).ulHi)?1: \
			(((dulFirst).ulLo<(dulSecond).ulLo)?-1: \
				(((dulFirst).ulLo>(dulSecond).ulLo)?1:0))))
				
#define DULONG_ADD(dulSum,dulFirst,dulSecond)	\
{ \
	DULONG dulSum_temp; \
	\
	(dulSum_temp).ulLo = (dulFirst).ulLo+(dulSecond).ulLo; \
	(dulSum_temp).ulHi = (dulFirst).ulHi+(dulSecond).ulHi+(VOS_UINT32)((dulSum_temp).ulLo<(dulFirst).ulLo); \
	(dulSum)           =  dulSum_temp; \
}

#define DULONG_SUB(dulResult,dulFirst,dulSecond) \
{ \
	DULONG dulResult_temp; \
	\
	(dulResult_temp).ulLo = (dulFirst).ulLo-(dulSecond).ulLo; \
	(dulResult_temp).ulHi = (dulFirst).ulHi-(dulSecond).ulHi-(VOS_UINT32)((dulResult_temp).ulLo>(dulFirst).ulLo); \
	(dulResult)           =  dulResult_temp; \
}

/* second must < 65536(0-65535) */
#define DULONG_MUL(dulResult,dulFirst,ulSecond) \
{ \
	DULONG dulResult_temp; \
	\
	dulResult_temp.ulLo=(dulFirst).usLoLo*(ulSecond); \
	dulResult_temp.ulHi=(dulFirst).usLoHi*(ulSecond)+dulResult_temp.usLoHi; \
	dulResult_temp.usLoHi=dulResult_temp.usHiLo; \
	dulResult_temp.ulHi=(dulFirst).ulHi*(ulSecond)+dulResult_temp.usHiHi; \
	(dulResult)=dulResult_temp; \
}

/* second must <65536(0-65535) */
#define DULONG_DIV(dulResult,dulFirst,ulSecond,ulMod) \
{ \
	DULONG dulResult_temp,dulResult_temp2; \
	\
	dulResult_temp.ulHi=dulFirst.ulHi/(ulSecond); \
	dulResult_temp2.usHiHi=dulFirst.ulHi%(ulSecond); \
	dulResult_temp2.usHiLo=dulFirst.usLoHi; \
	dulResult_temp.usLoHi=dulResult_temp2.ulHi/(ulSecond); \
	dulResult_temp2.usLoHi=dulResult_temp2.ulHi%(ulSecond); \
	dulResult_temp2.usLoLo=dulFirst.usLoLo; \
	dulResult_temp.usLoLo=dulResult_temp2.ulLo/(ulSecond); \
	(ulMod)=dulResult_temp2.ulLo%(ulSecond); \
	(dulResult)=dulResult_temp; \
}

#define DULONG_SELFADD(dulResult)\
{\
    (dulResult).ulLo++;\
    if((dulResult).ulLo == 0)\
        (dulResult).ulHi++; \
}

#define DULONG_SELFSUB(dulResult)\
{\
    (dulResult).ulLo--;\
    if((dulResult).ulLo == 0xffffffff)\
        (dulResult).ulHi --; \
}


#define VOS_IntegerShiftLeft( A, B ) \
    ( ( (VOS_UINT32) (A) ) << (B) )


#if defined (__BIG_ENDIAN_BITFIELD)
#define VOS_GetIntegerValueByPointer( pA, type ) \
( \
    ( sizeof( type ) == 4 ) ? \
    ( (type)( VOS_IntegerShiftLeft( *( (VOS_UINT8*)(pA) ), 24 ) | VOS_IntegerShiftLeft( *( (VOS_UINT8*)(pA) + 1 ), 16 ) | \
        VOS_IntegerShiftLeft( *( (VOS_UINT8*)(pA) + 2 ), 8 ) | *( (VOS_UINT8*)(pA) + 3 ) ) ) : \
    ( (type)( VOS_IntegerShiftLeft( *( (VOS_UINT8*)(pA) ), 8 ) | *( (VOS_UINT8*)(pA) + 1 ) ) )\
)
#else
#define VOS_GetIntegerValueByPointer( pA, type ) \
( \
    ( sizeof( type ) == 4 ) ? \
    ( (type)( VOS_IntegerShiftLeft( *( (VOS_UINT8*)(pA) + 3), 24 ) | VOS_IntegerShiftLeft( *( (VOS_UINT8*)(pA) + 2 ), 16 ) | \
        VOS_IntegerShiftLeft( *( (VOS_UINT8*)(pA) + 1 ), 8 ) | *( (VOS_UINT8*)(pA) ) ) ) : \
    ( (type)( VOS_IntegerShiftLeft( *( (VOS_UINT8*)(pA) + 1), 8 ) | *( (VOS_UINT8*)(pA) ) ) )\
)
#endif


#ifdef  __cplusplus
}
#endif

#endif

