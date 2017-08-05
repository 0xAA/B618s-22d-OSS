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

#ifndef __ATP_DEBUG_API_H__
#define __ATP_DEBUG_API_H__

#include "strfileapi.h"

#define ATP_DEBUG_MOD_ALL       "all"

#define ATP_DEBUG_HELP          "help"      /*!< debug help */
#define ATP_DEBUG_SWITCH        "switch"    /*!< debug 级别设置 */
#define ATP_DEBUG_INFO          "info"      /*!< 打印关键变量值 */

typedef VOS_UINT32 (*ATP_UTIL_Debug_Proc_CallBack)(VOS_UINT32 ulArgc, VOS_CHAR  *acLastPara[]);
typedef struct tagATP_UTIL_Debug_CMD_ST
{
    const VOS_CHAR              *pcCmd;
    ATP_UTIL_Debug_Proc_CallBack pfDebugProc;
}ATP_UTIL_Debug_CMD_ST;

/*!
  \brief reg module debug cmds
  \param[in]  *pcModName:模块名 
  \param[in]  *astDebugCmds: debug调试命令
  \param[in]  ulCmdNum: 命令个数
  \return  ATP_MSG_RET_PARA_ERR para error
*/
VOS_UINT32 ATP_Debug_RegModCmds(
                const VOS_CHAR                  *pcModName, 
                const ATP_UTIL_Debug_CMD_ST     *astDebugCmds, 
                VOS_UINT32                      ulCmdNum);

VOS_VOID ATP_Debug_Print(VOS_CHAR *fmt, ...) FORMAT_ATTRIBUTE(1, 2);

#endif

