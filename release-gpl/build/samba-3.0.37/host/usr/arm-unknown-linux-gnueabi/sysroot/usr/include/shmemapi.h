/******************************************************************************
  *         版权所有 (C), 2011-2014, 华为技术有限公司
*******************************************************************************/
/#ifndef __ATP_SHMEM_API_H__
#define __ATP_SHMEM_API_H__

#include "atptypes.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 *   Share Memory Module Definition
 */
typedef enum tagATP_UTIL_GVAR_MODULE
{
    ATP_UTIL_GVAR_MOD_CWMP = 0,
    ATP_UTIL_GVAR_MOD_UPNP,
    ATP_UTIL_GVAR_MOD_LOG,
    ATP_UTIL_GVAR_MOD_VOICE,
    ATP_UTIL_GVAR_MOD_PUBINFO,
    ATP_UTIL_GVAR_MOD_SMS,

    /* shem for fom(flash operation master) */
    ATP_UTIL_GVAR_MOD_FOM,
    ATP_UTIL_GVAR_MOD_SEC,
    ATP_UTIL_GVAR_MOD_WLAN,

    /* module max 16 */
    ATP_UTIL_GVAR_MOD_END   = 16,
} ATP_UTIL_GVAR_MODULE;

#define ATP_UTIL_BGET_MEM_LARGE     (256 * 1024)    // 256k
#define ATP_UTIL_BGET_MEM_MID       (128 * 1024)    // 128k
#define ATP_UTIL_BGET_MEM_SMALL     (64 * 1024)     // 64k
#define ATP_UTIL_BGET_MEM_VERY_SMALL (32 * 1024)    // 32k
#define ATP_UTIL_BGET_MEM_TINY      (16 * 1024)     // 16k

#define ATP_UTIL_GVAR_MOD_DEF(x)            ((x) << 16)
#define ATP_UTIL_GVAR_MOD_MASK(x)           (((x) & 0xFFFF0000) >> 16)

/*
 *      Global Variable definition for CWMP module
 */
typedef enum tagATP_UTIL_GVAR_CWMP_INDEX
{
    ATP_UTIL_GVAR_CWMP_EVT = ATP_UTIL_GVAR_MOD_DEF(ATP_UTIL_GVAR_MOD_CWMP),
    ATP_UTIL_GVAR_CWMP_PARA_REQ,
    ATP_UTIL_GVAR_CWMP_PARA_VAL_CHG,
    ATP_UTIL_GVAR_CWMP_PARA_CON_IP,
    ATP_UTIL_GVAR_CWMP_PUB_INFO,
}ATP_UTIL_GVAR_CWMP_INDEX;

/*
 *      Global Variable definition for TR064/UPnP module
 */
typedef enum tagATP_UTIL_GVAR_TR064_INDEX
{
    ATP_UTIL_GVAR_TR064_INIT = ATP_UTIL_GVAR_MOD_DEF(ATP_UTIL_GVAR_MOD_UPNP),
    ATP_UTIL_GVAR_TR064_HEAD,
    ATP_UTIL_GVAR_TR064_PUBINFO,
}ATP_UTIL_GVAR_TR064_INDEX;

/*
 *      Global Variable definition for VOICE module
 */
typedef enum tagATP_UTIL_GVAR_VOICE_INDEX
{
    ATP_UTIL_GVAR_VOICE_INIT = ATP_UTIL_GVAR_MOD_DEF(ATP_UTIL_GVAR_MOD_VOICE),
    ATP_UTIL_GVAR_VOICE_SVC,
    ATP_UTIL_GVAR_VOICE_STAT,
    ATP_UTIL_GVAR_VOICE_TAPI
}ATP_UTIL_GVAR_VOICE_INDEX;

/*
 *      Global Variable definition for FOM module
 */
typedef enum tagATP_UTIL_GVAR_FOM_INDEX
{
    ATP_UTIL_GVAR_FOM_INIT = ATP_UTIL_GVAR_MOD_DEF(ATP_UTIL_GVAR_MOD_FOM),
    ATP_UTIL_GVAR_FOM_LISTHEAD,
    ATP_UTIL_GVAR_FOM_MACCOUNT,
}ATP_UTIL_GVAR_FOM_INDEX;


/*
 *  bget api for shared memory dynamic allocation and free
 */
#define ATP_UTIL_BGET_INFO_BUFF_LEN (28) // !!DO NOT CHANGE, ref:ATP_UTIL_BGET_GLOBAL_ST in bget.h
#define ATP_UTIL_MEM_MASK_LEN       (512)  //xor mask len

// Do bget init for the specified memory
VOS_VOID ATP_UTIL_BgetInit(VOS_VOID *pvBgetHandle, VOS_VOID *pvBaseAddr, VOS_UINT32 ulLen);
VOS_VOID* ATP_UTIL_BgetMalloc(VOS_VOID *pvBgetHandle, const VOS_UINT32 ulSize);
VOS_VOID* ATP_UTIL_BgetStrdup(VOS_VOID *pvBgetHandle, const VOS_VOID *pvString);
VOS_VOID ATP_UTIL_BgetFree(VOS_VOID *pvBgetHandle, VOS_VOID *pvBuf);

#ifdef SUPPORT_ATP_MEM_CHECK
#define ATP_UTIL_MEMCHECK_FILEANAME_LEN (8)
#define ATP_UTIL_MEMCHECK_LINE_NO_LEN   (4)
#define ATP_UTIL_MEMCHECK_TIME_LEN      (4)

VOS_VOID* ATP_UTIL_BgetMallocEx(VOS_VOID* pvBgetHandle, VOS_UINT32 ulSize, 
    const VOS_CHAR* pszFileName, VOS_UINT32 ulLine);
VOS_VOID* ATP_UTIL_BgetStrdupEx(VOS_VOID* pvBgetHandle, const VOS_VOID* pvString,
    const VOS_CHAR* pszFileName, VOS_UINT32 ulLine);
VOS_VOID ATP_UTIL_BgetFreeEx(VOS_VOID* pvBgetHandle, VOS_VOID* pvBuf);
#endif

/*
 *  Module Global Variable api
 */
#define ATP_UTIL_GVAR_MIN_OFFSET    (52) // == sizeof(ATP_UTIL_GVAR_INFO)

// Do the module global variable init
VOS_UINT32 ATP_UTIL_GVarInit(VOS_UINT32 ulGvarModule, VOS_UINT32 ulBuffSize, VOS_UINT32 ulBgetOffset, VOS_BOOL* pbNewCreate);

VOS_UINT32 ATP_UTIL_GVarInitEx(VOS_UINT32 ulGvarModule, VOS_UINT32 ulBuffSize,
    VOS_UINT32 ulBgetOffset, VOS_BOOL bLock, VOS_BOOL* pbNewCreate);

// Attach to an already inited module shared memory
// GPL version provided
VOS_UINT32 ATP_UTIL_GVarAttach(VOS_UINT32 ulGvarModule);

// Release the shared memory for a module
VOS_UINT32 ATP_UTIL_GVarDelModule(VOS_UINT32 ulGvarModule, VOS_UINT32 ulBuffSize);

// Get the bget handler for the module shared memory
VOS_VOID *ATP_UTIL_GVarGetMemHandle(VOS_UINT32 ulModIdx);

// Get the value of global variable ulVarIdx to the buffer of pvValue
// GPL version provided
VOS_UINT32 ATP_UTIL_GVarGetValueEx(VOS_UINT32 ulVarIdx, VOS_VOID *pvValue,
    VOS_UINT32 ulBufLen, VOS_UINT32 *pulValueLength);

// Set value for global variable ulGVarIdx
// GPL version provided
VOS_UINT32 ATP_UTIL_GVarSetValue(VOS_UINT32 ulGVarIdx, const VOS_VOID *pvValue, VOS_UINT32 ulValLen);

// Get the shared memory address for the global variable ulVarIdx
// This function return the shared memory address directly, no lock for the following read and write
// So use it only when you know what you are doing
VOS_VOID *ATP_UTIL_GVarGetValue(VOS_UINT32 ulVarIdx, VOS_UINT32 *pulValueLength);


#ifdef __cplusplus
}
#endif

#endif

