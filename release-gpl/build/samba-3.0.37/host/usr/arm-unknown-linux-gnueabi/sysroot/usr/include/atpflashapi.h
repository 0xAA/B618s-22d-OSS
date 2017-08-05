/******************************************************************************
  *         版权所有 (C), 2001-2020, 华为技术有限公司
*******************************************************************************/

#ifndef _ATPFLASHAPI_H_
#define _ATPFLASHAPI_H_

#include "atptypes.h"


#ifndef FLASHINITNUM
#define FLASHINITNUM        0xFF  
#endif

#define WEB_FLAG_SIZE       16
#define MAX_CFGKEYBUF_LEN   256


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
    //zhoupeng write jvm-osgi 2015/09/30 DTS2015092105730
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


/*!
  \author        
  \brief        将DB共享内存写入flash的currentcfg和customizecfg文件，
                如果内部实现支持双备份，
                需要把pucBuf中的内容同时写入到备份分区中
  \param[in]    *pucBuf:  配置文件的内容
  \param[in]    ulLength: 配置文件内容的长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FLASH_WriteCfgData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength,VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        将DB共享内存写入flash的currentcfg文件
  \param[in]    *pucBuf:  配置文件的内容
  \param[in]    ulLength: 配置文件内容的长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    新平台不应调用该接口，该接口用于未支持KMC安全方案的老产品
*/
VOS_UINT32 ATP_FLASH_WriteMainCfgData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength,VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        将DB共享内存写入flash的customizecfg文件，只用于未开启KMC宏的老产品
  \param[in]    *pucBuf:  配置文件的内容
  \param[in]    ulLength: 配置文件内容的长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    新平台不应调用该接口，该接口用于未支持KMC安全方案的老产品
*/
VOS_UINT32 ATP_FLASH_WriteBackupCfgData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength,VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        从flash读取currentcfg到DB共享内存
  \param[in]    ulReadCnt: 读取的次数，默认从0开始。
                           读取到数据，如果上层校验失败，会把ulReadCnt加1继续读取。
                           内部实现时，如果发现ulReadCnt不为0，需要从备份分区中读取。
  \param[out]   **ppucBuf:  输出的buffer内容，内部分配内存，调用的地方释放。
  \param[out]   *pulLength: 输出的buffer长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FLASH_ReadCfgData(VOS_UINT32 ulReadCnt, VOS_UINT8 **ppucBuf, VOS_UINT32 *pulLength,VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        把应用数据的内容写入到Flash中
                如果内部实现支持双备份，
                需要把pucBuf中的内容同时写入到备份分区中。
  \param[in]    *pucBuf:  配置文件的内容
  \param[in]    ulLength: 配置文件内容的长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FLASH_WriteAppData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength);


/*!
  \author        
  \brief        从flash读取appdata内容，目前只有mic模块使用
  \param[in]    ulReadCnt: 读取的次数，默认从0开始。
                           读取到数据，如果上层校验失败，会把ulReadCnt加1继续读取。
                           内部实现时，如果发现ulReadCnt不为0，需要从备份分区中读取。
  \param[out]   **ppucBuf:  输出的buffer内容，内部分配内存，调用的地方释放。
  \param[out]   *pulLength: 输出的buffer长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FLASH_ReadAppData(VOS_UINT32 ulReadCnt, VOS_UINT8 **ppucBuf, VOS_UINT32 *pulLength);


/*!
  \author        
  \brief        将log日志写入flash，目前只有log模块使用
  \param[in]    pucBuf: the buffer which is used to store the write data, 
                        provided by caller
  \param[in]    ulLength: write length
  \param[in]    ulOffset: the offset relative to the begin of the log
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FlashWriteLogdataProc(const VOS_UINT8 *pucBuf,VOS_UINT32 ulLength, VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        从flash读取log日志，目前只有log模块使用
  \param[in]    ulReadCnt: 读取的次数，默认从0开始。
                           读取到数据，如果上层校验失败，会把ulReadCnt加1继续读取。
                           内部实现时，如果发现ulReadCnt不为0，需要从备份分区中读取。
  \param[out]   **ppucBuf:  输出的buffer内容，内部分配内存，调用的地方释放。
  \param[out]   *pulLength: 输出的buffer长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FlashReadLogdataProc(VOS_UINT32 ulReadCnt, VOS_UINT8 **ppucBuf, VOS_UINT32 *pulLength);


/*!
  \author        
  \brief        读取装备信息，对于2B来说是读取/dev/nv下的相应节点值
  \param[in]    ulEquipInfoIdx: 待读取的装备信息编号。
  \param[out]   *pucBuf:  装备信息缓冲区
  \param[out]   ulLength: 装备信息缓冲区长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FLASH_ReadEquip(VOS_UINT32 ulEquipInfoIdx,VOS_UINT8* pucBuf, VOS_UINT32 ulLength);


/*!
  \author        
  \brief        将升级文件写入对应分区
  \param[in]    ulUPGType:  分区类型
  \param[in]    *pcDataBuf: 数据buffer
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FLASH_UpgradeData(VOS_UINT32 ulUPGType,const VOS_UINT8 *pcDataBuf);


/*!
  \author        
  \brief        从对应MTD分区读取flag，目前只有tinyupg模块使用
  \param[in]    ulType:  flag类型见FLAG_TYPE
  \param[out]   *pucBuf: upgradeflag数据buf 
  \param[out]   ulLen: upgradeflag buf长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FLASH_ReadFlag(VOS_UINT32 ulType,VOS_UINT8 *pucBuf, VOS_UINT32 ulLen);


/*!
  \author       zwx346084
  \brief        擦除智能家居middleware分区，目前只有tinyupg模块使用
  \param[in]
  \param[out]
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FLASH_EraseMiddleWare();


/*!
  \author        
  \brief        写基MAC地址到装备
  \param[out]   ppucBuf:数据buf
  \param[out]   pulLen:数据buf长度
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_FLASH_WriteBaseMac(VOS_UINT8 *pucBuf, VOS_UINT32 pulLen);


/*!
  \author        
  \brief        用于重启单板，对于2B来说相当于sleep 1秒后执行reboot命令
  \param[in]  
  \param[out] 
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_HAL_Reboot();


/*!
  \author        
  \brief        DB初始化工作，主要是DB共享内存创建，目前只供mic模块使用
  \param[in]  
  \param[out] 
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    调用该接口之前，应先调用ATP_Flash_InitProcs接口
*/
VOS_UINT32 ATP_FLASH_Init();


/*!
  \author        
  \brief        初始化所有flash操作接口回调函数，进程启动时使用
  \param[in]
  \param[out] 
  \return       执行结果
  \retval       ERROR_CODE 错误码说明
  \注意事项:    无
*/
VOS_UINT32 ATP_Flash_InitProcs();


#if defined(__cplusplus)
}
#endif
#endif /* _ATPFLASHAPI_H_ */

