/******************************************************************************
  *         ��Ȩ���� (C), 2001-2020, ��Ϊ�������޹�˾
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
  \brief        ��DB�����ڴ�д��flash��currentcfg��customizecfg�ļ���
                ����ڲ�ʵ��֧��˫���ݣ�
                ��Ҫ��pucBuf�е�����ͬʱд�뵽���ݷ�����
  \param[in]    *pucBuf:  �����ļ�������
  \param[in]    ulLength: �����ļ����ݵĳ���
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FLASH_WriteCfgData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength,VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        ��DB�����ڴ�д��flash��currentcfg�ļ�
  \param[in]    *pucBuf:  �����ļ�������
  \param[in]    ulLength: �����ļ����ݵĳ���
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��ƽ̨��Ӧ���øýӿڣ��ýӿ�����δ֧��KMC��ȫ�������ϲ�Ʒ
*/
VOS_UINT32 ATP_FLASH_WriteMainCfgData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength,VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        ��DB�����ڴ�д��flash��customizecfg�ļ���ֻ����δ����KMC����ϲ�Ʒ
  \param[in]    *pucBuf:  �����ļ�������
  \param[in]    ulLength: �����ļ����ݵĳ���
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��ƽ̨��Ӧ���øýӿڣ��ýӿ�����δ֧��KMC��ȫ�������ϲ�Ʒ
*/
VOS_UINT32 ATP_FLASH_WriteBackupCfgData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength,VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        ��flash��ȡcurrentcfg��DB�����ڴ�
  \param[in]    ulReadCnt: ��ȡ�Ĵ�����Ĭ�ϴ�0��ʼ��
                           ��ȡ�����ݣ�����ϲ�У��ʧ�ܣ����ulReadCnt��1������ȡ��
                           �ڲ�ʵ��ʱ���������ulReadCnt��Ϊ0����Ҫ�ӱ��ݷ����ж�ȡ��
  \param[out]   **ppucBuf:  �����buffer���ݣ��ڲ������ڴ棬���õĵط��ͷš�
  \param[out]   *pulLength: �����buffer����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FLASH_ReadCfgData(VOS_UINT32 ulReadCnt, VOS_UINT8 **ppucBuf, VOS_UINT32 *pulLength,VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        ��Ӧ�����ݵ�����д�뵽Flash��
                ����ڲ�ʵ��֧��˫���ݣ�
                ��Ҫ��pucBuf�е�����ͬʱд�뵽���ݷ����С�
  \param[in]    *pucBuf:  �����ļ�������
  \param[in]    ulLength: �����ļ����ݵĳ���
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FLASH_WriteAppData(const VOS_UINT8 *pucBuf, VOS_UINT32 ulLength);


/*!
  \author        
  \brief        ��flash��ȡappdata���ݣ�Ŀǰֻ��micģ��ʹ��
  \param[in]    ulReadCnt: ��ȡ�Ĵ�����Ĭ�ϴ�0��ʼ��
                           ��ȡ�����ݣ�����ϲ�У��ʧ�ܣ����ulReadCnt��1������ȡ��
                           �ڲ�ʵ��ʱ���������ulReadCnt��Ϊ0����Ҫ�ӱ��ݷ����ж�ȡ��
  \param[out]   **ppucBuf:  �����buffer���ݣ��ڲ������ڴ棬���õĵط��ͷš�
  \param[out]   *pulLength: �����buffer����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FLASH_ReadAppData(VOS_UINT32 ulReadCnt, VOS_UINT8 **ppucBuf, VOS_UINT32 *pulLength);


/*!
  \author        
  \brief        ��log��־д��flash��Ŀǰֻ��logģ��ʹ��
  \param[in]    pucBuf: the buffer which is used to store the write data, 
                        provided by caller
  \param[in]    ulLength: write length
  \param[in]    ulOffset: the offset relative to the begin of the log
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FlashWriteLogdataProc(const VOS_UINT8 *pucBuf,VOS_UINT32 ulLength, VOS_UINT32 ulOffset);


/*!
  \author        
  \brief        ��flash��ȡlog��־��Ŀǰֻ��logģ��ʹ��
  \param[in]    ulReadCnt: ��ȡ�Ĵ�����Ĭ�ϴ�0��ʼ��
                           ��ȡ�����ݣ�����ϲ�У��ʧ�ܣ����ulReadCnt��1������ȡ��
                           �ڲ�ʵ��ʱ���������ulReadCnt��Ϊ0����Ҫ�ӱ��ݷ����ж�ȡ��
  \param[out]   **ppucBuf:  �����buffer���ݣ��ڲ������ڴ棬���õĵط��ͷš�
  \param[out]   *pulLength: �����buffer����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FlashReadLogdataProc(VOS_UINT32 ulReadCnt, VOS_UINT8 **ppucBuf, VOS_UINT32 *pulLength);


/*!
  \author        
  \brief        ��ȡװ����Ϣ������2B��˵�Ƕ�ȡ/dev/nv�µ���Ӧ�ڵ�ֵ
  \param[in]    ulEquipInfoIdx: ����ȡ��װ����Ϣ��š�
  \param[out]   *pucBuf:  װ����Ϣ������
  \param[out]   ulLength: װ����Ϣ����������
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FLASH_ReadEquip(VOS_UINT32 ulEquipInfoIdx,VOS_UINT8* pucBuf, VOS_UINT32 ulLength);


/*!
  \author        
  \brief        �������ļ�д���Ӧ����
  \param[in]    ulUPGType:  ��������
  \param[in]    *pcDataBuf: ����buffer
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FLASH_UpgradeData(VOS_UINT32 ulUPGType,const VOS_UINT8 *pcDataBuf);


/*!
  \author        
  \brief        �Ӷ�ӦMTD������ȡflag��Ŀǰֻ��tinyupgģ��ʹ��
  \param[in]    ulType:  flag���ͼ�FLAG_TYPE
  \param[out]   *pucBuf: upgradeflag����buf 
  \param[out]   ulLen: upgradeflag buf����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FLASH_ReadFlag(VOS_UINT32 ulType,VOS_UINT8 *pucBuf, VOS_UINT32 ulLen);


/*!
  \author       zwx346084
  \brief        �������ܼҾ�middleware������Ŀǰֻ��tinyupgģ��ʹ��
  \param[in]
  \param[out]
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FLASH_EraseMiddleWare();


/*!
  \author        
  \brief        д��MAC��ַ��װ��
  \param[out]   ppucBuf:����buf
  \param[out]   pulLen:����buf����
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_FLASH_WriteBaseMac(VOS_UINT8 *pucBuf, VOS_UINT32 pulLen);


/*!
  \author        
  \brief        �����������壬����2B��˵�൱��sleep 1���ִ��reboot����
  \param[in]  
  \param[out] 
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_HAL_Reboot();


/*!
  \author        
  \brief        DB��ʼ����������Ҫ��DB�����ڴ洴����Ŀǰֻ��micģ��ʹ��
  \param[in]  
  \param[out] 
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ���øýӿ�֮ǰ��Ӧ�ȵ���ATP_Flash_InitProcs�ӿ�
*/
VOS_UINT32 ATP_FLASH_Init();


/*!
  \author        
  \brief        ��ʼ������flash�����ӿڻص���������������ʱʹ��
  \param[in]
  \param[out] 
  \return       ִ�н��
  \retval       ERROR_CODE ������˵��
  \ע������:    ��
*/
VOS_UINT32 ATP_Flash_InitProcs();


#if defined(__cplusplus)
}
#endif
#endif /* _ATPFLASHAPI_H_ */

