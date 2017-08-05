/**************************************************************************//**

  Copyright (C), 2001-2012, Huawei Tech. Co., Ltd.

 ******************************************************************************
 * @file    upnpserviceapi.h
 * @brief   upnpserviceapi½Ó¿Ú
 * @author  zhangxiaotian
 * @date    2016/12/23
 * @version EMUI Router 5.1
 * History:
 *
 * Number : V1.00
 * Date   : 2016/12/23
 * Author : zhangxiaotian
 * Desc   : Created file, for common api used by upnp and mic
 *
******************************************************************************/


#ifndef __ATP_UPNP_SERVICE_API_H__
#define __ATP_UPNP_SERVICE_API_H__

VOS_BOOL UpnpGetLanIP();
VOS_INT32 UpnpSsdpCreateSocket(VOS_BOOL bIPv6State);
VOS_UINT32 ATP_GENA_NotifyMsgBuild(const ATP_UTIL_NV_PAIR_ST *pstEvtData, VOS_VOID **ppvMsg);
VOS_UINT32 ATP_GENA_GetLocalSubURL(VOS_CHAR *acBuf, VOS_UINT32 ulLen);

#endif // End of __ATP_UPNP_SERVICE_API_H__


