/*****************************************************************************
 *               Copyright (C) 2011, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file gpldevstatusutil.h
  *
  *\copyright 2007-2020，华为技术有限公司
  *\ 
  *\date  2016-11-5
*/

#ifndef __GPL_DEVSTATUS_UTIL_INCLUDE__
#define __GPL_DEVSTATUS_UTIL_INCLUDE__

#include "atptypes.h"
#ifdef SUPPORT_ATP_DEVICE_STATUS

/*!
  \brief 设置统计业务的使用状态，当前暂不记录次数，若后续业务有需要，再增加该功能
  \param[in]  pcModule: 业务模块名称，如smaba、dlna等
  \return 
  \retval 
*/
extern VOS_UINT32 ATP_DevStatus_UsedCountAdd(const VOS_CHAR* pcModule);

#else
 
#define ATP_DevStatus_UsedCountAdd(pcModule)
#endif


#endif

