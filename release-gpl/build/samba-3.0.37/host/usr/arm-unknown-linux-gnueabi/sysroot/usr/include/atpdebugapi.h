/*****************************************************************************
 *               Copyright (C) 2011, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file atpdebugapi.h
  *
  *\copyright 2007-2020����Ϊ�������޹�˾
  *\author  
  *\date  2012-8-10
  *- <���ⵥ��>         <��  ��>    <�޸�ʱ��>   <�汾>   <�޸�����> 
*/
#ifndef __ATP_DEBUG_API_H__
#define __ATP_DEBUG_API_H__

#include "strfileapi.h"

#define ATP_DEBUG_MOD_ALL       "all"

#define ATP_DEBUG_HELP          "help"      /*!< debug help */
#define ATP_DEBUG_SWITCH        "switch"    /*!< debug �������� */
#define ATP_DEBUG_INFO          "info"      /*!< ��ӡ�ؼ�����ֵ */

typedef VOS_UINT32 (*ATP_UTIL_Debug_Proc_CallBack)(VOS_UINT32 ulArgc, VOS_CHAR  *acLastPara[]);
typedef struct tagATP_UTIL_Debug_CMD_ST
{
    const VOS_CHAR              *pcCmd;
    ATP_UTIL_Debug_Proc_CallBack pfDebugProc;
}ATP_UTIL_Debug_CMD_ST;

/*!
  \brief reg module debug cmds
  \param[in]  *pcModName:ģ���� 
  \param[in]  *astDebugCmds: debug��������
  \param[in]  ulCmdNum: �������
  \return  ATP_MSG_RET_PARA_ERR para error
*/
VOS_UINT32 ATP_Debug_RegModCmds(
                const VOS_CHAR                  *pcModName, 
                const ATP_UTIL_Debug_CMD_ST     *astDebugCmds, 
                VOS_UINT32                      ulCmdNum);

VOS_VOID ATP_Debug_Print(VOS_CHAR *fmt, ...) FORMAT_ATTRIBUTE(1, 2);

#endif

