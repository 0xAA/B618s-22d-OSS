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

#ifndef _ATPFLASHAPI_H_
#define _ATPFLASHAPI_H_

#include "atptypes.h"

#ifndef FLASHINITNUM
#define FLASHINITNUM            0xFF  
#endif

#define WEB_FLAG_SIZE   (16)
#define MAX_CFGKEYBUF_LEN (256)

#define RF_CFG_LEN 256

typedef enum 
{
    FOM_E_DEVICELOG,
    FOM_E_VOICELOG
}FOM_LOG_TYPE;

typedef enum
{
    READ_CUR_CFG,
    READ_BAK_CFG,
    READ_OTHER,
}CFG_READ_TYPE;

typedef enum 
{
    FLAG_BOOT,
    FLAG_WEB,
    FLAG_REBOOT,
}FLAG_TYPE;

typedef enum 
{
    UPG_TAG,
    UPG_CFG,
    UPG_WEB,
    UPG_WEBBAK,
    UPG_KERNEL,
    UPG_IMAGE,
    UPG_BIGIMAGE,
    UPG_BOOTLOADER,
    UPG_JVM
}UPG_TYPE;


typedef enum tagATP_DECT_CALIB_TYPE_EN
{
    ATP_DECT_CALIB_ALL = 0,
    ATP_DECT_CALIB_RVBG,
    ATP_DECT_CALIB_RVREF,
    ATP_DECT_CALIB_RXTUN,
    ATP_DECT_CALIB_RFPI,
    ATP_DECT_CALIB_IPUI,
    ATP_DECT_CALIB_MAGIC,
    ATP_DECT_CALIB_CLIMASK = 0x80,
    ATP_DECT_CALIB_END,
}ATP_DECT_CALIB_TYPE_EN;



VOS_UINT32 ATP_FLASH_WriteCfgData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength,VOS_UINT32 ulOffset);


VOS_UINT32 ATP_FLASH_WriteMainCfgData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength,VOS_UINT32 ulOffset);



VOS_UINT32 ATP_FLASH_WriteBackupCfgData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength,VOS_UINT32 ulOffset);


VOS_UINT32 ATP_FLASH_ReadCfgData(VOS_UINT32 ulReadCnt, VOS_UINT8 **ppucBuf, VOS_UINT32 *pulLength,VOS_UINT32 ulOffset);


VOS_UINT32 ATP_FLASH_WriteAppData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength);


VOS_UINT32 ATP_FLASH_ReadAppData(VOS_UINT32 ulReadCnt, VOS_UINT8 **ppucBuf, VOS_UINT32 *pulLength);


VOS_UINT32 ATP_FLASH_ReadEquip(VOS_UINT32 ulEquipInfoIdx,VOS_UINT8* pucBuf, VOS_UINT32 ulLength);


VOS_UINT32 ATP_FLASH_UpgradeData(VOS_UINT32 ulUPGType,const VOS_UINT8 *pcDataBuf);


VOS_UINT32 ATP_FLASH_ReadFlag(VOS_UINT32 ulType,VOS_UINT8 *pucBuf, VOS_UINT32 ulLen);


VOS_UINT32 ATP_FLASH_WriteFlag(VOS_UINT32 ulType,VOS_UINT8 *pucBuf, VOS_UINT32 ulLen);


VOS_UINT32 ATP_FLASH_ReadHwDiag(VOS_UINT8 *pucBuf, VOS_UINT32 ulLen, VOS_UINT32 ulAddress);


VOS_UINT32 ATP_FLASH_EraseCfg();


VOS_UINT32 ATP_FLASH_WriteCert();


VOS_UINT32 ATP_FLASH_ReadCert(VOS_UINT8 *pucBuf, VOS_UINT32 ulLen);


VOS_UINT32 ATP_FLASH_WriteBaseMac(VOS_UINT8 *pucBuf, VOS_UINT32 pulLen);


VOS_UINT32 ATP_HAL_Reboot();


VOS_UINT32 ATP_Flash_InitProcs();
#if defined(__cplusplus)
}
#endif
#endif /* _ATPFLASHAPI_H_ */

