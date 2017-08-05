/*****************************************************************************
 *               Copyright (C) 2011, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file gpldevstatusutil.h
  *
  *\copyright 2007-2020����Ϊ�������޹�˾
  *\ 
  *\date  2016-11-5
*/

#ifndef __GPL_DEVSTATUS_UTIL_INCLUDE__
#define __GPL_DEVSTATUS_UTIL_INCLUDE__

#include "atptypes.h"
#ifdef SUPPORT_ATP_DEVICE_STATUS

/*!
  \brief ����ͳ��ҵ���ʹ��״̬����ǰ�ݲ���¼������������ҵ������Ҫ�������Ӹù���
  \param[in]  pcModule: ҵ��ģ�����ƣ���smaba��dlna��
  \return 
  \retval 
*/
extern VOS_UINT32 ATP_DevStatus_UsedCountAdd(const VOS_CHAR* pcModule);

#else
 
#define ATP_DevStatus_UsedCountAdd(pcModule)
#endif


#endif

