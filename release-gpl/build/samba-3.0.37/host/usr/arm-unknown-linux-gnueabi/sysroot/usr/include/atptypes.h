

#ifndef __ATP_TYPES_H__
#define __ATP_TYPES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <stdarg.h>
#include "atpconfig.h"
#include "atpcbbid.h"
#include "atpconst.h"
#include "atpdeprecated.h"
#include "atpconfig_common.h"

#ifdef ATP_DMALLOC
#include "dmalloc.h"
#define DMALLOC_OPTION "debug=0x14040D07,inter=1000,lockon=20,log=/var/dmalloc/dmalloc_%p.log"
#endif
typedef const char  VOS_CONST_CHAR;

#define VOS_NOK                 1L

#define ATP_VERSION_CMD_KEY     "atpv"

#define ATP_ARRAY_LEN(x)        ((sizeof(x))/(sizeof(((x)[0]))))

#ifndef offsetof
#define offsetof(type, member) ((long) &((type *) 0)->member)
#endif


#define ATP_CONTAINER_OF(ptr, type, member) \
  ((type *) ((char *) (ptr) - offsetof(type, member)))

#define ATP_MAX_MALLOC      (2 * 1024 * 1024)    /*监视异常malloc申请，设置为2MB*/
#define ATP_MEM_LEAK_LOG    "/online/memleak.log"


/*!
  \brief  往文件中格式化写入字符串内容
  \param[in]  pcFileName: 待写的文件
  \param[in]  bAppend: VOS_FALSE表示覆盖文件原有的内容；VOS_TRUE表示往文件尾追加内容
  \param[in]  *fmt: 格式化的字符串
  \param[in]  ...: 
  \return 
  \retval -1:   出错
  \retval >=0:    写入的字符串个数
*/
static inline int ATP_UTIL_FilePrintf(const char *pcFileName, unsigned int bAppend, char *fmt, ...)
{
    FILE        *pfFile = NULL;
    va_list     ap;
    int         len = 0;

#ifdef ATP_PCLINT
    fmt = fmt;
#endif

    if (NULL == pcFileName)
    {
        return -1;
    }

    if (0 != bAppend) //not VOS_FALSE
    {
        pfFile = fopen(pcFileName, "a+");
    }
    else
    {
        pfFile = fopen(pcFileName, "wb");
    }
    if (NULL == pfFile)
    {
        return -1;
    }

    va_start(ap, fmt);
    //lint -save -e64
    len = vfprintf(pfFile, fmt, ap);
    //lint restore
    va_end(ap);
    fclose(pfFile);
    return len;
}

#if defined(SUPPORT_ATP_ATP_DEBUG_IAMGE) && !defined(ATP_DMALLOC)
/*!
  \author      
  \brief      内部封装malloc，便于监听异常malloc动作，使用者直接调用ATP_MALLOC；
              后续可考虑加上memset动作
  \param[in]  bytes: 要申请的字节数
  \param[in]  filename: 所在的文件名，用于打印
  \param[in]  funcname: 所在的函数名，用于打印
  \return     返回malloc的结果
  \retval     与malloc函数一致
*/
static inline void* atp_malloc_internal(size_t bytes, const char *filename, const char *funcname, unsigned int line)
{
    if (bytes > ATP_MAX_MALLOC)
    {
        printf("too large malloc, len=%d, file=%s, func=%s, line=%d, pid=%d!\n", bytes, filename, funcname, line, getpid());
        ATP_UTIL_FilePrintf(ATP_MEM_LEAK_LOG, 1, "too large malloc, len=%d, file=%s, func=%s, line=%d, pid=%d!\n", 
            bytes, filename, funcname, line, getpid());
    }
    return malloc(bytes);
}

#define ATP_MALLOC(x)   atp_malloc_internal((x), __FILE__, __FUNCTION__,__LINE__)
#define malloc(x)       atp_malloc_internal((x), __FILE__, __FUNCTION__,__LINE__)
#else
#define ATP_MALLOC(x)   malloc(x)
#endif


#define ATP_FREE(x) \
{\
    if (x)\
    {\
        free((void*)(x));\
        (x) = NULL;\
    }\
}

#define ATP_CHECK_RETURN(ret)   \
{\
    if (VOS_OK != ret)\
    {\
        return ret;\
    }\
}

#define ATP_IF_OPER(condition, operation) \
{ \
    if ((condition)) \
    { \
        operation; \
    } \
}

#ifdef SUPPORT_ATP_PTHREAD_LOCAL_STORAGE
#ifdef ATP_PCLINT
#define ATP_THREAD_SAFE
#else
#define ATP_THREAD_SAFE     __thread
#endif
#else
#define ATP_THREAD_SAFE
#endif

/* if vos.h is not included */
#ifndef  _V_TYPDEF_H

/************************* MACRO & TYPE DEFINITION ***************************/
#define VOS_NULL               (0)
#define VOS_NULL_PTR           (0L)

#define VOS_OK                 (0)
#define VOS_ERROR              (-1)
#define VOS_TRUE               1L
#define VOS_FALSE              0L

#ifndef  VOS_TYPE
#define  VOS_TYPE               1
#if defined(__cplusplus)
#define                     VOS_VOID void
#else
typedef void                    VOS_VOID;
#endif

typedef unsigned char           VOS_UINT8;
typedef char                    VOS_INT8;
typedef char                    VOS_CHAR;

typedef unsigned short          VOS_UINT16;
typedef signed short            VOS_INT16;

typedef unsigned int           VOS_UINT32;
typedef signed int             VOS_INT32;

typedef unsigned int            VOS_UINT;
typedef int                     VOS_INT;
#endif

typedef unsigned int           VOS_BOOL;

typedef float                   VOS_FLOAT;
typedef double                  VOS_DOUBLE;

typedef unsigned int           VOS_SOCKET;

typedef unsigned long long      VOS_UINT64;
typedef long long               VOS_INT64;
#endif /* _V_TYPDEF_H */

#define UINT16_MAXVALUE (0xFFFF)
#define INT32_MAXVALUE  (0x7FFFFFFF)
#define UINT32_MAXVALUE (0xFFFFFFFF)

#define    VTOP_LITTLE_ENDIAN        1234 /* least-significant byte first (vax) */
#define    VTOP_BIG_ENDIAN           4321 /* most-significant byte first (IBM, net) */

#define VTOP_LITTLE_BYTE_ORDER

#ifdef VTOP_LITTLE_BYTE_ORDER
#define    VTOP_BYTE_ORDER          VTOP_LITTLE_ENDIAN
#endif

#ifdef VTOP_BIG_BYTE_ORDER
#define    VTOP_BYTE_ORDER          VTOP_BIG_ENDIAN
#endif

#undef DESC
#define DESC(x) 1

typedef enum tagATP_TEAM_EN
{
    ATP_TEAM_MNT        = 1,
    ATP_TEAM_SYS,
    ATP_TEAM_NTWK,
    ATP_TEAM_VOICE,
    ATP_TEAM_CMS,
} ATP_TEAM_EN;

#define ATP_MNT_ERR_CODE_DEF(team, module)    ((module) << 16)
#define ATP_SEC_KEYID_CODE_DEF(module)  ((module) << 16)

#ifndef ATP_MSG_LOCAL_HOST
#define ATP_MSG_LOCAL_HOST        ("127.0.0.1")
#endif
#ifndef ATP_MSG_LOCAL_PORT
#define ATP_MSG_LOCAL_PORT        (9267)
#endif

#ifdef SUPPORT_DESKTOP
#define ATP_MSG_SVR_PATH        "../var/msgsvr"
#else
#define ATP_MSG_SVR_PATH        "/var/msgsvr"
#endif


#ifdef SUPPORT_UNIT_TEST
#define ATP_STATIC
#else
#define ATP_STATIC              static
#endif

#define ATP_SOCK_INVALID_FD     (-1)
#define ATP_PID_INVALID_NUM     (-1)

#define ATP_DIGIT_STR_MAX_LEN_D     (32)

#define ATP_INSTALL_BIN_DIR_D       "/mupg/install"
#define ATP_TMP_BIN_DIR_D           "/mupg/slave"


/****************************************************************************
 BELOW IS OID MAP:

 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |I|W|S|K|N|M|VTYPE| MPROC |X_E|  OBJECT_ID      | PARAMETER_ID  |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 I: if TRUE, object has multi-INSTANCE, else object has single-instance.
 W: if TRUE, object or parameter can WRITE, or cannot write.
 S: if TRUE, object or parameter need to SAVE to database.
 K: if TRUE, parameter is KEY value.
 N: if FALSE, patameter cannot set attribute NOTIFY.
 M: if TRUE, get or get inst MSG need to send to process.
 VTYPE: VALUE TYPE: 000:object, 001:string, 010:int, 011:unsignedint, 100:bool, 101:datetime,
                    110:base64 , 111: anysimpletype
 MPROC: MAIN PROC
 OBJECT_ID: 9bit
 PARAMETER_ID: 8bit
 X_E: 2bit X_EXTENTION VALUE: 0, 1, 2, 3
****************************************************************************/
#define CMO_OBJ_HAS_INSTANCE        0x80000000
#define CMO_OBJ_ATTR_HAS_VALUE      0x80000000
#define CMO_OBJ_ATTR_CAN_WRITE      0x40000000
#define CMO_OBJ_ATTR_CAN_SAVE       0x20000000
#define CMO_ATTR_IS_KEY             0x10000000
#define CMO_ATTR_IS_NOTIFY          0x08000000
#define CMO_ATTR_SEND_GET_MSG       0x04000000
#define CMO_DATA_TYPE_OBJECT        0x00000000
#define CMO_DATA_TYPE_STRING        0x00800000
#define CMO_DATA_TYPE_INT           0x01000000
#define CMO_DATA_TYPE_UINT          0x01800000
#define CMO_DATA_TYPE_BOOL          0x02000000
#define CMO_DATA_TYPE_DATETIME      0x02800000
#define CMO_DATA_TYPE_BASE64        0x03000000
#define CMO_DATA_TYPE_UINTL         0x03800000
#define CMO_DATA_TYPE_MASK          0x03800000

#define CMO_NODE_INDEX_MASK         0x0FFFFF00
#define CMO_NODE_OBJID_MASK         0x0001FF00
#define CMO_MAIN_PROC_MASK          0x00780000
#define CMO_X_EXT_MASK              0x00060000

#define IS_OBJECT_HAS_INSTANCE(x)   ((((x)&CMO_OBJ_HAS_INSTANCE) == 0) ? VOS_FALSE : VOS_TRUE)
#define IS_ATTR_HAS_VALUE(x)        ((((x)&CMO_OBJ_HAS_INSTANCE) == 0) ? VOS_FALSE : VOS_TRUE)
#define IS_ATTR_CAN_WRITE(x)        ((((x)&CMO_OBJ_ATTR_CAN_WRITE) == 0) ? VOS_FALSE : VOS_TRUE)
#define IS_ATTR_CAN_SAVE(x)         ((((x)&CMO_OBJ_ATTR_CAN_SAVE) == 0) ? VOS_FALSE : VOS_TRUE)
#define IS_ATTR_IS_KEY(x)           ((((x)&CMO_ATTR_IS_KEY) == 0) ? VOS_FALSE : VOS_TRUE)
#define IS_ATTR_SEND_GET_MSG(x)     ((((x)&CMO_ATTR_SEND_GET_MSG) == 0) ? VOS_FALSE : VOS_TRUE)
#define IS_ATTR_NOTIFY(x)           ((((x)&CMO_ATTR_IS_NOTIFY) == 0) ? VOS_FALSE : VOS_TRUE)

#define IS_TYPE_OBJ(x)              ((((x)&CMO_DATA_TYPE_MASK) == CMO_DATA_TYPE_OBJECT)?VOS_TRUE : VOS_FALSE)
#define IS_TYPE_STRING(x)           ((((x)&CMO_DATA_TYPE_MASK) == CMO_DATA_TYPE_STRING)?VOS_TRUE : VOS_FALSE)
#define IS_TYPE_INT(x)              ((((x)&CMO_DATA_TYPE_MASK) == CMO_DATA_TYPE_INT)?VOS_TRUE : VOS_FALSE)
#define IS_TYPE_UINT(x)             ((((x)&CMO_DATA_TYPE_MASK) == CMO_DATA_TYPE_UINT)?VOS_TRUE : VOS_FALSE)
#define IS_TYPE_BOOL(x)             ((((x)&CMO_DATA_TYPE_MASK) == CMO_DATA_TYPE_BOOL)?VOS_TRUE : VOS_FALSE)
#define IS_TYPE_DATETIME(x)         ((((x)&CMO_DATA_TYPE_MASK) == CMO_DATA_TYPE_DATETIME)?VOS_TRUE : VOS_FALSE)
#define IS_TYPE_BASE64(x)           ((((x)&CMO_DATA_TYPE_MASK) == CMO_DATA_TYPE_BASE64)?VOS_TRUE : VOS_FALSE)
#define IS_TYPE_UINTL(x)            ((((x)&CMO_DATA_TYPE_MASK) == CMO_DATA_TYPE_UINTL)?VOS_TRUE : VOS_FALSE)

#define IS_CMO_OBJECT(x)            ((((x)&0x000000FF) == 0) ? VOS_TRUE: VOS_FALSE)
#define IS_CMO_ATTRIBUTE(x)         ((((x)&0x000000FF) != 0) ? VOS_TRUE: VOS_FALSE)

#define GET_PARA_IDX(x)             ((((x)&0x000000FF) == 0) ? 0: (((x)&0x000000FF) - 1))
#define GET_OBJ_CMO(x)              ((x)&0xFFFFFF00)
#define GET_DATA_TYPE(x)            ((x)&0x03800000)
#define GET_OBJID_VALUE(x)          (((x)&CMO_NODE_OBJID_MASK) >> 8)
#define GET_MAINPROC(x)             (((x)&CMO_MAIN_PROC_MASK) >> 19)
#define GET_EXT_IDX(x)              (((x)&CMO_X_EXT_MASK) >> 17)

#define NOT_USE 0

#define MULTI_INSTANCE 1
#define SINGLE_INSTANCE 0

#define WRITE_TRUE 1
#define WRITE_FALSE 0

#define SAVE_TRUE 1
#define SAVE_FALSE 0

#define KEY_TRUE 1

#define KEY_FALSE 0

#define CMO_DEF(InstFlag, WriteFlag, SaveFlag, KeyFlag, NotifyFlag, GetMsgFlag, ValueType, MainProc, ObjID, ParaID)\
        (unsigned int)( ((InstFlag)<<31) | ((WriteFlag)<<30) | ((SaveFlag)<<29) | ((KeyFlag)<<28) | ((NotifyFlag)<<27) | ((GetMsgFlag)<<26) | (ValueType)<<23 | (MainProc)<<19 | ((ObjID)<<8) | (ParaID) )


// BELOW IS LINT MACRO FOR ATP CMS

#ifdef ATP_PCLINT
#define SET_MSG_LINT_MACRO \
{ \
    ulObjId      = ulObjId; \
    ulNumOfPara  = ulNumOfPara; \
    ulNextObjId  = ulNextObjId; \
    pulSetValues = pulSetValues; \
    pulChgParas  = pulChgParas; \
    pulOldValues = pulOldValues;\
    aucInstId    = aucInstId;\
}

#define GET_MSG_LINT_MACRO \
{ \
    ulObjId      = ulObjId; \
    ulNumOfPara  = ulNumOfPara; \
    aucInstId    = aucInstId; \
    pbFocusParas = pbFocusParas; \
    pulGetdValues = pulGetdValues; \
}

#define TR181_SET_MSG_LINT_MACRO \
{ \
    ulObjId      = ulObjId; \
    ulNumOfPara  = ulNumOfPara; \
    ulNextObjId  = ulNextObjId; \
    pulSetValues = pulSetValues; \
    pulChgParas  = pulChgParas; \
    pulOldValues = pulOldValues;\
    aucInstId    = aucInstId;\
    bSetObj = bSetObj;\
}

#define TR181_GET_MSG_LINT_MACRO \
{ \
    ulObjId      = ulObjId; \
    ulNumOfPara  = ulNumOfPara; \
    aucInstId    = aucInstId; \
    pulFocusParas = pulFocusParas; \
    pulGetdValues = pulGetdValues; \
}

#define CHECK_MSG_LINT_MACRO \
{ \
    ulObjId      = ulObjId; \
    ulNumOfPara  = ulNumOfPara; \
    pulSetValues = pulSetValues; \
    pulOldValues = pulOldValues; \
    aucInstId    = aucInstId; \
}

#define DEL_MSG_LINT_MACRO \
{ \
    ulObjId      = ulObjId; \
    aucInstId    = aucInstId; \
}

#define GETINSTNUM_MSG_LINT_MACRO \
{ \
    aucInstId  = aucInstId;   \
    ulObjId    = ulObjId;     \
    ulArrayLen = ulArrayLen;  \
    pulInstValues = pulInstValues; \
    pulNumOfInst = pulNumOfInst; \
}
#else

#define SET_MSG_LINT_MACRO
#define GET_MSG_LINT_MACRO
#define TR181_SET_MSG_LINT_MACRO
#define TR181_GET_MSG_LINT_MACRO
#define CHECK_MSG_LINT_MACRO
#define DEL_MSG_LINT_MACRO
#define GETINSTNUM_MSG_LINT_MACRO

#endif

/*
  * ATP macro utitlity definition
  */
#define ATP_MACRO_STRINGFY_INTERNAL(x...)    #x      // Internal use only
#define ATP_MACRO_STRINGFY(x...)    ATP_MACRO_STRINGFY_INTERNAL(x)

#define ATP_MACRO_JOIN_AGAIN(x, y)  x ## y          // Internal use only
#define ATP_MACRO_JOIN(x, y)        ATP_MACRO_JOIN_AGAIN(x, y)

#define MODULE_CONSTRUCTOR() static void _init(void) __attribute__((constructor)); static void _init(void)
#define MODULE_DESTRUCTOR() static void _destroy(void) __attribute__((destructor)); static void _destroy(void)

#ifdef ENABLE_FORMAT_CHECK
#define FORMAT_ATTRIBUTE(x,y)  __attribute__((format(printf, (x), (y) )))
#else
#define FORMAT_ATTRIBUTE(x,y)
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#define FUNCTION_POINTER(f) (f)
#define ATP_UTIL_GetSymbolNameByPtr(func) ("")
#define ATP_UTIL_TraceSymbolPrint(x...)


#define ATP_END_OF_LINE_STR_D       "\r\n"

/*
 *  App Data definition
 */

// Higher 8 bits are reserved
#define ATP_APPDATA_ID_MASK_D       (0x00FFFFFF)

#define ATP_APPDATA_CATEGORY_DEF(x)  ((((x) & 0xFFF) << 8) & ATP_APPDATA_ID_MASK_D)

#define ATP_APPDATA_FLAG_NOSAVE_D   (0x80000000)    // The AppData no need to save
#define ATP_APPDATA_FLAG_EXPORT_D   (0x40000000)    // The AppData has to be exported
#define ATP_APPDATA_FLAG_NORESTORE_D   (0x20000000)    // The AppData not to be restore clean

/*
 *  Network common definitions
 */
#define ATP_INTERFACE_LEN 16

#define ATP_HTTP_SOCK_SEND_TIMEOUT_D    30
#define ATP_CFM_CONFIG_FILE_LENGTH_D    65536
#define ATP_CFM_MSG_TIMEOUT             30000
#define ATP_MAX_CFG_SIZE                0x10000

#ifdef SUPPORT_ATP_ATPFS
#define ETC_DIR_PREFIX "/atp"
#else
#define ETC_DIR_PREFIX ""
#endif

#endif /* __VTOP_TYPES_H__ */
