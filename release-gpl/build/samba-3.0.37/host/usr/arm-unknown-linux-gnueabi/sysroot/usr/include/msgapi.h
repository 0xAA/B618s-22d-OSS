/*****************************************************************************
 *               Copyright (C) 2011, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/


#ifndef __ATP_MSG_API_H__
#define __ATP_MSG_API_H__

#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <grp.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <linux/version.h>
#include "atptypes.h"
#include "sysutil.h"

#include "dbapi.h"





#define ATP_MSG_CATEGORY_DEF(x)          (((x) & 0xFFF) << 8)

#define ATP_MSG_RECV_TIMEOUT_D           (1000 * 5) /*!<  5 seconds*/

#include "micmsgtypes.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*!<  Empty string*/
extern const VOS_CHAR *g_pcEmptyStr;

#define ATP_MSG_MAX_NAME_LEN     (11)

#define IPV6_FROMLAN             (96)
#define IP_FROMLAN               (24)
#ifdef SUPPORT_ATP_LANDEV_IN_27
#define IP_ORIGINDEV             (27)
#else
#define IP_ORIGINDEV             (21)
#endif

#ifdef SUPPORT_ATP_PKTSOURCEMAC_IN_28
#define IP_PKTSOURCEMAC          (28)
#else
#define IP_PKTSOURCEMAC          (22)
#endif

#define IPV6_ORIGINDEV           (97)


/* Message Header */
typedef struct tagATP_MSG_HEADER_ST
{
    VOS_UINT32  ulMsgType;
    VOS_UINT32  ulSeqNum;

    VOS_CHAR    aucSendApp[ATP_MSG_MAX_NAME_LEN + 1];    /*!< ���ͽ������� */
    VOS_CHAR    aucRecvApp[ATP_MSG_MAX_NAME_LEN + 1];    /*!< ���ս������� */

    VOS_UINT32  ulMsgData;
    VOS_UINT32  ulDataLen;
}ATP_MSG_HEADER_ST;

#define PRINT_MSG_PATTERN             "msg type:[0x%x] app:[%s] data:[%d] len:[%d] dst:[%s] src:[%s]"

#define PRINT_MSG_ARGS(pstMsg)          (pstMsg)->ulMsgType, g_stMsgCtx.aucAppName, (pstMsg)->ulMsgData, (pstMsg)->ulDataLen, (pstMsg)->aucRecvApp, (pstMsg)->aucSendApp
#include "eventapi.h"
#include "listapi.h"

#include "atploopapi.h"

#include "atptraceapi.h"
enum ATP_MSGCORE_MSGTYPES_EN
{
    ATP_MSG_MSGCORE_START    = ATP_MSG_CATEGORY_DEF(ATP_MODULE_MSGCORE), // = 0x100 = 256
	ATP_MSG_LOG_CTRL,
	ATP_MSG_TRACE_CTRL,
	ATP_MSG_REDIRECT_CTRL,
	ATP_MSG_DEBUG_CTRL,
	ATP_MSG_DIAGNOSTIC_CTRL,
	ATP_MSG_STATS_CTRL,
	ATP_MSG_DEBUG_TRACE_CTRL,
	ATP_MSG_UNRECHABLE_CTRL,
	ATP_MSG_WEBMODULE_REG,		/* ע��webģ�� */
	ATP_MSG_WEBRESTFUL_REQ,		/* WebRestful ���� */
	ATP_MSG_RESTFUL_MATCH_UPDATE,   /* RESTful�ӿ�ƥ���������¼� */
	ATP_MSG_UPGRADE_SAMBA,      /* ����Ϣ���Ӱ����ôӰ�samba��Ϣ */
	ATP_MSG_WEBRESTFUL_REQ_ASYNC,   /* WebRestful �첽���� */
	ATP_MSG_WEBRESTFUL_REQ_NOTIFY,
	ATP_MSG_WLAN_EVENT_TEST,
	ATP_MSG_WEBRESTFUL_LUA,
	ATP_MSG_MIC_BROADCAST
};

typedef enum tagATP_MSG_RET_CODE_EN
{
    ATP_MSG_RET_SOCKET_ERR        = ATP_MNT_ERR_CODE_DEF(ATP_TEAM_MNT, ATP_MODULE_MSGCORE), // = 0x10000 = 65536
    ATP_MSG_RET_PARA_ERR,
    ATP_MSG_RET_APPNAME_ERR,
    ATP_MSG_RET_NOT_INITED,
    ATP_MSG_RET_PEER_DEAD,
    ATP_MSG_RET_TIMEOUT,
    ATP_MSG_RET_MEM_ERR,
    ATP_MSG_RET_INTERNAL_ERR,
    ATP_MSG_RET_OVERFLOW,
    ATP_MSG_RET_FILE_NOT_EXIST,
    ATP_MSG_RET_NOT_FOUNDPWD,
    ATP_MSG_RET_UPROOT_FAIL,
    ATP_MSG_RET_NOT_FOUNDGROUP,
    ATP_MSG_RET_FILE_WRITE_FAIL,
    ATP_MSG_RET_PATH_PARA_NULL,
    ATP_MSG_RET_PATH_REALPATH_ERROR,
    ATP_MSG_RET_PATH_PATH_LONG,
    ATP_MSG_RET_PATH_PATH_EXCESS,
    ATP_MSG_RET_MKDIR_ERR,
    ATP_MSG_RET_CHOWN_ERR
} ATP_MSG_RET_CODE_EN;

typedef enum tagATP_MIC_BROADCAST_CMDTYPES_EN
{
    ATP_MIC_BROADCAST_DMALLOC_SHUTDOWN = 0,
    ATP_MIC_BROADCAST_LLT,
}ATP_MIC_BROADCAST_CMDTYPES_EN;


typedef VOS_VOID (*AtpMsgProc)(const ATP_MSG_HEADER_ST *pstMsg);
typedef ATP_MSG_HEADER_ST *(*AtpSyncMsgProc)(const ATP_MSG_HEADER_ST *pstMsg);

typedef struct tagATP_MSG_QUEUE_ST
{
	struct tagATP_MSG_QUEUE_ST 	*pstNext;
    ATP_MSG_HEADER_ST           *pstMsg;
} ATP_MSG_QUEUE_ST;

 /*!<  Top three bits are used for slave board index*/
#define ATP_MSG_TYPE_SLAVE_INDEX_MASK 0xE0000000

// Get real msg type with no mask
/*
 *      Msg type is 32 bit, lower 8 bits is used by package, middle 12 bits are for package index
 *      Higher 12 bits are reserved.
 */
#define ATP_MSG_TYPE_NO_MASK(ulMsgType)    ((VOS_UINT32)((ulMsgType) & 0xFFFFF))

 /*!< Get which slave board the msg is from by msg type */
#define ATP_MSG_TYPE_GET_SLAVE_BOARD_INDEX(ulMsgType)    ((VOS_UINT32)(((ulMsgType) & ATP_MSG_TYPE_SLAVE_INDEX_MASK) >> 29))

 /*!<  Set which slave board the msg to send by msg type*/
#define ATP_MSG_TYPE_SET_SLAVE_BOARD_INDEX(ulMsgType, ulSlaveIndex)    (ulMsgType) &= (~ATP_MSG_TYPE_SLAVE_INDEX_MASK); (ulMsgType) |= ((VOS_UINT32)((ulSlaveIndex) << 29))

/*!< Recvd big message with file */
#define ATP_MSG_TYPE_RECV_FILE_MASK             ((VOS_UINT32)(0x10000000))
#define ATP_MSG_TYPE_IS_RECV_FILE(ulIndex)      ((VOS_UINT32)((ulIndex) & ATP_MSG_TYPE_RECV_FILE_MASK))
#define ATP_MSG_TYPE_SET_RECV_FILE(ulMsgType)   (ulMsgType) |= (ATP_MSG_TYPE_RECV_FILE_MASK)

/*!< Board index for master board */
#define ATP_MSG_MASTER_BOARD_INDEX_NUM_D        7

typedef struct tagATP_MSG_CONTEXT_ST
{
    VOS_CHAR            aucAppName[ATP_MSG_MAX_NAME_LEN + 1];
    VOS_INT32           lSock;
    VOS_BOOL            bExitLoop;
    AtpMsgProc          pfMsgProc;
    VOS_UINT32          ulDbgLevel;
    FILE                *pfTraceFile;
    VOS_INT32           lTraceFd;
    ATP_MSG_QUEUE_ST    *pstMsgQueue;   /*!<  Internal usage*/
    VOS_INT32           lAccessMode;
    VOS_UINT32          ulMsgFlags;
    VOS_VOID            *handle;
    VOS_UINT32          ulSeqNum;
} ATP_MSG_CONTEXT_ST;

typedef enum tagATP_MSG_FLAGS_EN
{
    ATP_MSG_FLAG_ENABLE_STATS           = (1 << 0),
    ATP_MSG_FLAG_NEED_ENDIAN_SWAP       = (1 << 1),
    ATP_MSG_FLAG_NEED_SLAVE_CONNECTED   = (1 << 2),
    ATP_MSG_FLAG_BODY_ENDIAN_SWAP       = (1 << 3),
} ATP_MSG_FLAGS_EN;

#define ATP_MSG_STATS_ENABLE        (0 != (g_stMsgCtx.ulMsgFlags & ((VOS_UINT32)ATP_MSG_FLAG_ENABLE_STATS)))

/*
  *  Endian Swap Flag for msg client
  */
#define ENDIAN32_SWAP(value) \
         ((((VOS_UINT32)((value) & 0x000000FF)) << 24) | \
         (((VOS_UINT32)((value) & 0x0000FF00)) << 8) | \
         (((VOS_UINT32)((value) & 0x00FF0000)) >> 8) | \
         (((VOS_UINT32)((value) & 0xFF000000)) >> 24))

/*!<  Check if the current msg client need to swap endian for recvd msg*/
#define ATP_MSG_NEED_ENDIAN_SWAP()   (0 != (g_stMsgCtx.ulMsgFlags & ((VOS_UINT32)ATP_MSG_FLAG_NEED_ENDIAN_SWAP)))
/*!<  Mark the the current msg client need to swap endian for recvd msg*/
#define ATP_MSG_SET_ENDIAN_SWAP()   (g_stMsgCtx.ulMsgFlags |= ((VOS_UINT32)ATP_MSG_FLAG_NEED_ENDIAN_SWAP))
/*!<  Clear the mark the the current msg client need to swap endian for recvd msg*/
#define ATP_MSG_CLR_ENDIAN_SWAP()   (g_stMsgCtx.ulMsgFlags &= ((VOS_UINT32)(~ATP_MSG_FLAG_NEED_ENDIAN_SWAP)))

 /*!<  Safe do 32 bit endian swap*/
#define ATP_MSG_SAFE_ENDIAN_SWAP(ulData) (ATP_MSG_NEED_ENDIAN_SWAP() ? (ENDIAN32_SWAP(ulData)) : (ulData))

/*
 *  Multi Board Communication Message Context
 */
 /*!< Recvd Message board index */
/*!< Top three bits are used for slave board index */
#define ATP_MSG_RECV_BOARD_INDEX_MASK ((VOS_UINT32)(0xE0000000))
#define ATP_MSG_GET_RECV_BOARD_INDEX()          ((VOS_UINT32)((g_stMsgCtx.ulMsgFlags & ATP_MSG_RECV_BOARD_INDEX_MASK) >> 29))
#define ATP_MSG_SET_RECV_BOARD_INDEX(ulIndex)   g_stMsgCtx.ulMsgFlags &= (~ATP_MSG_RECV_BOARD_INDEX_MASK); g_stMsgCtx.ulMsgFlags |= ((VOS_UINT32)((ulIndex) << 29))

#define ATP_MSG_DEST_BOARD_INDEX_MASK ((VOS_UINT32)(0x1C000000))
#define ATP_MSG_GET_DEST_BOARD_INDEX()          ((g_stMsgCtx.ulMsgFlags & ATP_MSG_DEST_BOARD_INDEX_MASK) >> 26)
#define ATP_MSG_SET_DEST_BOARD_INDEX(ulIndex)   g_stMsgCtx.ulMsgFlags &= (~ATP_MSG_DEST_BOARD_INDEX_MASK); g_stMsgCtx.ulMsgFlags |= ((VOS_UINT32)((ulIndex) << 26))

extern ATP_THREAD_SAFE ATP_MSG_CONTEXT_ST g_stMsgCtx;

/*********************************************************************************************
   
  brief      ����Ϣ�ṹ���е�Ԫ�����ֽ����ת��
  param[in]  *pstMsg: ��ת������Ϣ�����
  return     
   ע����� 
1�����øú��������Ϣ�ṹ���е�������Ԫ�����ֽ����ת��������֮ǰ��Ҫͨ������ATP_MSG_NEED_ENDIAN_SWAP
�ж��Ƿ���Ҫת��
retval 
***********************************************************************************************/ 
VOS_VOID ATP_MSG_HeaderEndianSwap(ATP_MSG_HEADER_ST *pstMsg);

/*********************************************************************************************
   
  brief      ����Ϣ��ӵ���Ϣ�������
  param[in]  **ppstMsgQueue: ��Ϣ�������
  param[in]  *pstMsg: ��������Ϣ
  return     VOS_OK:��ӳɹ�
             ����:���ʧ��
   ע����� 
1������Ϣ���뵽��Ϣ����֮����Ϣ�����������ͣ������ڿ���ʱ����
retval  ATP_MSG_RET_PARA_ERR:�������������Ϊ��
        ATP_MSG_RET_MEM_ERR:�ڴ���������ڴ治��
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_QueueAppend(
                                ATP_MSG_QUEUE_ST        **ppstMsgQueue,
                                ATP_MSG_HEADER_ST       *pstMsg);
/*********************************************************************************************
   
  brief      ������Ϣ�������
  param[in]  *pstMsgQueue: ��Ϣ�������
  return     
   ע����� 
1������
retval  
***********************************************************************************************/ 
VOS_VOID ATP_MSG_QueueDestroy(ATP_MSG_QUEUE_ST *pstMsgQueue);

/*********************************************************************************************
   
  brief      ��ʼ����Ϣ���
  param[in]  *pszAppName: �������ƣ�����Ϊ�ա�Ϊ��ʱ����Ϣ�������������������ơ�
  return     VOS_OK:��ӳɹ�
             ����:���ʧ��
   ע����� 
1�������ʼ����ʱ��ֻ�ܽ��̵����ƣ���Ҫȷ���������Ƶ�Ψһ�ԣ�������������
2����ʼ����ʱ��ᷢ����Ϣ��mic����ע�ᣬ����ϢĬ���ǻ����ڶ������ӳٷ��͵ģ������Ҫ�����ɹ��ĳ���
��Ҫ���⴦��
retval  ATP_MSG_RET_SOCKET_ERR:����socketʧ��
        ATP_MSG_RET_MEM_ERR:�ڴ治����mallocʧ��
        ATP_MSG_RET_PARA_ERR��ע��ʱ�����������
        ATP_MSG_RET_OVERFLOW:ע����Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:ע����Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣע�ᷢ�������Ĵ���
        ��֧��notifyclient������»��᷵��
        ATP_NOTIFY_RET_APPNAME_ERR:notifyclient��ʼ����ʱ��ulMID����Ƿ�
        ATP_NOTIFY_RET_SOCKET_ERR:����notifyclient socketʧ��
        ATP_NOTIFY_RET_PEER_DEAD:notify clientע��ʧ��
        ATP_NOTIFY_RET_MEM_ERR:mallocʧ��
        ATP_NOTIFY_RET_OVERFLOW:ע����Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_NOTIFY_RET_INTERNAL_ERR:��Ϣע�ᷢ�������Ĵ���
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_Init(const VOS_CHAR *pszAppName);

/*********************************************************************************************
   
  brief      ȥ��ʼ����Ϣ����
  param[in]  
  return     
   ע����� 
1������
retval  
***********************************************************************************************/ 
VOS_VOID ATP_MSG_Destroy(VOS_VOID);


/*
 *    Message Dispatch Interfaces
 */
/*********************************************************************************************
   
  brief      ע����Ϣ������
  param[in]  pFunc:��Ϣ������
  return     
   ע����� 
1���˴�����ע������Լ�ʵ�ֵ�ÿ����Ϣ�Ĵ����������Ǳ������Լ��Ļص������������ATP_MSG_DefaultMsgProc
�ſ���ͨ��ATP_MSG_RegMsgProc�ķ�ʽע����Ϣ�Ĵ�����
retval  
***********************************************************************************************/ 
VOS_VOID ATP_MSG_RegisterMsgProc(AtpMsgProc pFunc);


/*********************************************************************************************
   
  brief      ������Ϣ�ַ�ѭ��
  param[in]  
  return     
   ע����� 
1������
retval  ATP_MSG_RET_TIMEOUT:��Ϣ�ַ���ʱ 
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ�ַ���������

***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_GetAndDispatch();



/*
 *    Message Sending & Recving Interfaces
 */

typedef VOS_UINT32 (*AtpMsgSendHookProc)(const ATP_MSG_HEADER_ST *pstMsg, VOS_BOOL *pbHooked, VOS_INT32 *pulSendSock);

extern AtpMsgSendHookProc g_pfMsgSendHook;

/*********************************************************************************************
   
  brief      ��Ϣ���ͽӿ�
  param[in]  *pstMsg:��Ϣָ��
  return     VOS_OK:��Ϣ���ͳɹ�
             ��������ֵ:��Ϣ����ʧ�ܣ�����ԭ��ο�������
   ע����� 
1����δָ��g_pfMsgSendHookΪ�յ�ʱ��ֱ�ӵ���ATP_MSG_Send���ܵ�����Ϣ�ӳٷ���
2��pstMsg���ڴ������malloc�ģ�ע���ڵ���ATP_MSG_Send֮������ͷ�
retval  ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_Send(ATP_MSG_HEADER_ST *pstMsg);
/*********************************************************************************************
   
  brief      ��Ϣ���ͽӿ�
  param[in]  lSock:ָ��������Ϣ��sock
  param[in]  *pstMsg:��Ϣָ��
  return     VOS_OK:��Ϣ���ͳɹ�
             ��������ֵ:��Ϣ����ʧ�ܣ�����ԭ��ο�������
   ע����� 
1����δָ��g_pfMsgSendHookΪ�յ�ʱ��ֱ�ӵ���ATP_MSG_SendEx���ܵ�����Ϣ�ӳٷ���
2��pstMsg���ڴ������malloc�ģ�ע���ڵ���ATP_MSG_SendEx֮������ͷ�
retval  ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_SendEx(VOS_INT32 lSock, ATP_MSG_HEADER_ST *pstMsg);


/*********************************************************************************************
   
  brief      ������Ϣ�����ҽ������Ӧ��Ϣ
  param[in]  *pstMsg: �����͵���Ϣ
  param[out] **ppstResp: ��Ӧ��Ϣ
  param[in]  ulTimeout: ��ʱʱ�䣬Ϊ0��ʾ������������λms
  return     VOS_OK:��Ϣ����/���ճɹ�
             ��������ֵ:��Ϣ����/����ʧ�ܣ�����ԭ��ο�������
   ע����� 
1��pstMsg���ڴ������malloc�ģ�ע���ڵ���ATP_MSG_SendAndRecv֮������ͷ�
2������յ��˻�Ӧ��Ϣ��ppstResp�����ڴ����룬��ʹ�����֮����Ҫ�ͷ�
retval  ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
        ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_SendAndRecv(ATP_MSG_HEADER_ST  *pstMsg,
                                        ATP_MSG_HEADER_ST        **ppstResp,
                                        VOS_UINT32               ulTimeout);
/*********************************************************************************************
   
  brief      ������Ϣ�����ҽ������Ӧ��Ϣ,У�鷢����Ϣ��SendApp Name
              �������Ϣ��RecvApp Name�Ƿ���ͬ
  param[in]  *pstMsg: �����͵���Ϣ
  param[out] **ppstResp: ��Ӧ��Ϣ
  param[in]  ulTimeout: ��ʱʱ�䣬Ϊ0��ʾ������������λms
  return     VOS_OK:��Ϣ����/���ճɹ�
             ��������ֵ:��Ϣ����/����ʧ�ܣ�����ԭ��ο�������
   ע����� 
1��pstMsg���ڴ������malloc�ģ�ע���ڵ���ATP_MSG_SendAndRecvWithAppName֮������ͷ�
2������յ��˻�Ӧ��Ϣ��ppstResp�����ڴ����룬��ʹ�����֮����Ҫ�ͷ�
retval  ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
        ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
***********************************************************************************************/ 
VOS_UINT32 ATP_MSG_SendAndRecvWithAppName(ATP_MSG_HEADER_ST   *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);

/*********************************************************************************************
  author      
  brief      �첽�ص���Ϣ����    
  param[in]  *pstMsg: ������Ϣ
  param[in]  callback: �ص�����
  param[in]  ulTimeout: ��ʱʱ��
  param[in]  *pvData: �ص��������
  return     VOS_OK:��Ϣ���ͽ��ճɹ�
             ��������ֵ:��Ϣ���ͽ���ʧ�ܣ�����ʧ��ֵ�ο�������
   ע����� 
1�� pstMsg���ڴ������malloc�ģ�ע���ڵ���ATP_MSG_AsyncSendAndRecv֮������ͷ�
2�� pvData��Ҫָ����յ���Ϣ���еĽṹ�壬��Ҫ�ڵ���ATP_MSG_AsyncSendAndRecv����malloc
3�� pvDataʹ����Ϻ���Ҫ�ͷ�
�ú�������Ϊͬ�����������̳߳����¸��ʳ�������
�����߱���ȷ���ý���Ϊ���̣߳����Ϊ���߳���ʹ��  ATP_MSG_Send ����
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
         ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
         ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
         ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
         ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
         ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_MSG_AsyncSendAndRecv(ATP_MSG_HEADER_ST  *pstMsg, VOS_UINT32 ulTimeout, VOS_VOID *pvData, PfMsgWatcherProc callback);
/*********************************************************************************************
   
  brief      ��Ϣ���Ͳ����ջ�Ӧ��Ϣ��MSGDATA  
  param[in]  *pcDest: ��Ϣ���շ�
  param[in]  ulMsgType: ��Ϣ����
  param[in]  ulMsgData: ��Ϣ��Я��MSGDATA
  param[in]  ulTimeout: ��Ϣ��ʱʱ��
  param[in]  *pulMsgData: ������Ϣ�е�MSGDATA
  return     VOS_OK:��Ϣ���ͽ��ճɹ�
             ��������ֵ:��Ϣ���ͽ���ʧ�ܣ�����ʧ��ֵ�ο�������
   ע����� 
1�� ����
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
         ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
         ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
         ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
         ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
         ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
         ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendAndRecvMsgData(const VOS_CHAR * pcDest, VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData, VOS_UINT32 ulTimeout, VOS_UINT32 *pulMsgData);
/*********************************************************************************************
   
  brief      ������Ϣ���ͽ�����Ϣ  
  param[in]  ulMsgType: ��Ϣ����
  param[out] **ppstResp: ���յ�����Ϣ
  param[in]  ulTimeout: ��Ϣ��ʱʱ��
  return     VOS_OK:��Ϣ���ճɹ�
             ��������ֵ:��Ϣ����ʧ�ܣ�����ʧ��ֵ�ο�������
   ע����� 
1�� ���յ�����ϢppstResp���ڴ����룬ʹ�������Ҫ�ͷ�
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
         ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
         ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvWithType(VOS_UINT32              ulMsgType,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);
/*********************************************************************************************
   
  brief      ������Ϣ  
  param[in]  *pstMsg: ������Ϣ�ṹ
  param[out] **ppstResp: ���յ�����Ϣ
  param[in]  ulTimeout: ��Ϣ��ʱʱ��
  return     VOS_OK:��Ϣ���ճɹ�
             ��������ֵ:��Ϣ����ʧ�ܣ�����ʧ��ֵ�ο�������
   ע����� 
1�� ���յ�����ϢppstResp���ڴ����룬ʹ�������Ҫ�ͷ�
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
         ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
         ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvResponse(const ATP_MSG_HEADER_ST *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);
/*********************************************************************************************
   
  brief      ������Ϣ,У�鷢����Ϣ��SendApp Name
              �������Ϣ��RecvApp Name�Ƿ���ͬ
  param[in]  *pstMsg: ������Ϣ�ṹ
  param[out] **ppstResp: ���յ�����Ϣ
  param[in]  ulTimeout: ��Ϣ��ʱʱ��
  return     VOS_OK:��Ϣ���ճɹ�
             ��������ֵ:��Ϣ����ʧ�ܣ�����ʧ��ֵ�ο�������
   ע����� 
1�� ���յ�����ϢppstResp���ڴ����룬ʹ�������Ҫ�ͷ�
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
         ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
         ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvResponseWithAppName(const ATP_MSG_HEADER_ST *pstMsg,
                                        ATP_MSG_HEADER_ST         **ppstResp,
                                        VOS_UINT32                ulTimeout);

/*********************************************************************************************
   
  brief      ��socket������Ϣ
  param[in]  sSock: socket������
  param[out] **ppstResp: ���յ�����Ϣ
  param[in]  ulTimeout: ��Ϣ��ʱʱ�䣬Ϊ0��ʾ������������λms
  return     VOS_OK:��Ϣ���ճɹ�
             ��������ֵ:��Ϣ����ʧ�ܣ�����ʧ��ֵ�ο�������
   ע����� 
1�� ���յ�����ϢppstResp���ڴ����룬ʹ�������Ҫ�ͷ�
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
         ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
         ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
         ATP_MSG_RET_MEM_ERR:�ڴ�����ʧ��
         ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_MSG_Recv(VOS_INT32           sSock,
                              ATP_MSG_HEADER_ST   **ppstMsg,
                              VOS_UINT32          ulTimeout);
/*********************************************************************************************
   
  brief      ��socket������Ϣ�������ֽ����������
  param[in]  sSock: socket������
  param[out] **ppstResp: ���յ�����Ϣ
  param[in]  ulTimeout: ��Ϣ��ʱʱ�䣬Ϊ0��ʾ������������λms
  param[in]  bWithEndian: �ֽ���
  return     VOS_OK:��Ϣ���ճɹ�
             ��������ֵ:��Ϣ����ʧ�ܣ�����ʧ��ֵ�ο�������
   ע����� 
1�� ���յ�����ϢppstResp���ڴ����룬ʹ�������Ҫ�ͷ�
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
         ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
         ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
         ATP_MSG_RET_MEM_ERR:�ڴ�����ʧ��
         ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvWithEndian(VOS_INT32             sSock,
                              ATP_MSG_HEADER_ST     **ppstMsg,
                              VOS_UINT32            ulTimeout,
                              VOS_BOOL              bWithEndian);

/*
 *    Message Utilities
 */
/*********************************************************************************************
   
  brief      �޸�trace��Ϣ��fd
  param[in]  lNewFd: ����tracelog��fd
  return     
   ע����� 
1�� ����
  retval 
***********************************************************************************************/
VOS_VOID ATP_MSG_TraceProc(VOS_INT32 lNewFd);
/*********************************************************************************************
   
  brief      ע����ϢĬ�ϴ�����
  param[in]  *pstMsg: ������Ϣ�ṹ����Ϣ
  return     
   ע����� 
1�� ����
  retval 
***********************************************************************************************/
VOS_VOID ATP_MSG_MsgFilterProc(const ATP_MSG_HEADER_ST *pstMsg);
/*********************************************************************************************
   
  brief      ����һ����Ϣ�峤��ΪulMsgSize����Ϣ
  param[in]  *pstMsg: ������Ϣ�ṹ����Ϣ
  return     ����ɹ�������ָ�룬����ʧ�ܣ�����NULL
   ע����� 
1�� ����������ڴ����룬�ҷ���ֵ����ƫ�ƣ����ͷŵ�ʱ����Ҫ�ȵ���ATP_MSG_GetMsgHead��ȡͷָ�룬֮�����free
  retval 
***********************************************************************************************/
VOS_VOID* ATP_MSG_GetMsgBlock(VOS_UINT32 ulMsgSize);
/*********************************************************************************************
   
  brief      ����Msg�ṹ��ͷָ�����MSG BODY
  param[in]  *pstMsgHead: ��Ϣ�ṹͷָ��
  return     ���ҳɹ�������ָ�룬����ʧ�ܣ�����NULL
   ע����� 
1�� ����
  retval 
***********************************************************************************************/
VOS_VOID* ATP_MSG_GetMsgByHead(ATP_MSG_HEADER_ST* pstMsgHead);
/*********************************************************************************************
   
  brief      ����Msg Bodyָ�����MSG Header
  param[in]  *pvMsg: ��Ϣ�ṹBodyָ��
  return     ���ҳɹ�������ָ�룬����ʧ�ܣ�����NULL
   ע����� 
1�� ����
  retval 
***********************************************************************************************/
ATP_MSG_HEADER_ST* ATP_MSG_GetMsgHead(VOS_VOID* pvMsg);

/*
 *    Message Structure Utilities
 */

/*********************************************************************************************
   
  brief      ͨ����Ϣ����FD
  param[in]  lFdToSend: �����͵�FDָ��
  return     VOS_OK:���ͳɹ�
             ��������ֵ:����ʧ�ܣ�ԭ��ο�������
   ע����� 
1�� ����
  retval ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
         ATP_MSG_RET_MEM_ERR:�ڴ治�㣬mallocʧ��
         ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʧ��
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendFd(VOS_INT32 lFdToSend);
/*********************************************************************************************
   
  brief      ͨ����Ϣ����FD
  param[out] *plFdToRecv: ���յ���FD
  param[in]  ulTimeout: ���ճ�ʱʱ��
  return     VOS_OK:���ճɹ�
             ��������ֵ:����ʧ�ܣ�ԭ��ο�������
   ע����� 
1�� ����
  retval ATP_MSG_RET_PARA_ERR:�����������
         ATP_MSG_RET_NOT_INITED:��Ϣû�г�ʼ��
         ATP_MSG_RET_MEM_ERR:�ڴ治�㣬mallocʧ��
         ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʧ��
         ATP_MSG_RET_TIMEOUT:���ճ�ʱ
         ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RecvFd(VOS_INT32 *plFdToRecv, VOS_UINT32 ulTimeout);

/*********************************************************************************************
   
  brief      ����Ϣ����ӿ�
  param[in]  *pstMsg: ��Ϣ�ṹָ��
  param[in]  *pcDest: ��Ϣ���շ�
  param[in]  ulMsgType: ��Ϣ����
  param[in]  ulMsgData: ����Ϣ��������
  return     
   ע����� 
1�� ��Ϣ�ṹ���ڴ���Ҫ���ⲿָ��������ⲿ�������ڴ棬ע���ͷ�
2�� ����Ϣֻ��Я�������͵���Ϣ���ݷ��ͣ����ڽṹ����ַ�����Ҫ���������ӿڽ��й���
  retval 
***********************************************************************************************/
VOS_VOID ATP_MSG_SimpleBuilder(ATP_MSG_HEADER_ST *pstMsg, const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData);
/*********************************************************************************************
   
  brief      ͬ����Ϣͳһ�����Ӧ��Ϣ�ӿ�
  param[in]  *pstReq: ��Ϣ�ṹָ��
  param[in]  ulBuffLen: ��Ӧ��ϢЯ�����ݳ��ȣ���pvMsgBuff��Ӧ
  param[in]  pvMsgBuff: ��Ӧ��ϢЯ������
  param[in]  ulMsgData: ��Ӧ��ϢЯ������
  return     ����ɹ���������Ϣָ��
             ����ʧ�ܣ�����NULL
   ע����� 
1�� ����������������ڴ����룬����֮����Ҫ�ͷ�
2�� �����Ӧ��Ϣֻ��ҪЯ��һ�����֣�ֱ�����ulMsgData���ɣ�pvMsgBuff����Ϊ��
  retval 
***********************************************************************************************/
ATP_MSG_HEADER_ST *ATP_MSG_MsgResponseBuilder(const ATP_MSG_HEADER_ST *pstReq, VOS_UINT32 ulMsgData,
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen);
/*********************************************************************************************
   
  brief      �������Ϣ��������
  param[in]  *pcDest: ��Ϣ���շ�
  param[in]  ulMsgType: ��Ϣ����
  param[in]  ulMsgData: ��ϢЯ������
  return     VOS_OK:���췢�ͳɹ�
             ����:�������ʧ��
   ע����� 
1�� �ýӿ�ֻ�ܹ������Ϣ����Ϣ��ֻ��Я�����֣������Ҫ���ͽṹ������ַ�������Ҫ���������ӿ�
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendSimpleMsg(const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData);
/*********************************************************************************************
   
  brief      ����Я�����кŵļ���Ϣ��������
  param[in]  *pcDest: ��Ϣ���շ�
  param[in]  ulMsgType: ��Ϣ����
  param[in]  ulMsgData: ��ϢЯ������
  param[in]  ulSeqNum: ���к�
  return     VOS_OK:���췢�ͳɹ�
             ����:�������ʧ��
   ע����� 
1�� �ýӿ�ֻ�ܹ������Ϣ����Ϣ��ֻ��Я�����֣������Ҫ���ͽṹ������ַ�������Ҫ���������ӿ�
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendSimpleMsgWithSeqNum(const VOS_CHAR *pcDest,
                                     VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgData, VOS_UINT32 ulSeqNum);

/*********************************************************************************************
   
  brief      ע���¼���ע
  param[in]  ulEvtType: ��ע�¼�
  return     VOS_OK:���췢�ͳɹ�
             ����:�������ʧ��
   ע����� 
1�� ����
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
#define ATP_MSG_SubscribeEvent(ulEvtType)   ATP_MSG_SendSimpleMsg(NULL, ATP_MSG_SUBSCRIBE_EVT, (ulEvtType))
/*********************************************************************************************
   
  brief      ȥע���¼���ע
  param[in]  ulEvtType: ��ע�¼�
  return     VOS_OK:���췢�ͳɹ�
             ����:�������ʧ��
   ע����� 
1�� ����
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
#define ATP_MSG_UnSubscribeEvent(ulEvtType) ATP_MSG_SendSimpleMsg(NULL, ATP_MSG_UNSUBSCRIBE_EVT, (ulEvtType))
/*********************************************************************************************
   
  brief      Ϊ��������ע���¼���ע
  param[in]  ulEvtType: �¼�����
  param[in]  *pcName: ��������
  return     VOS_OK:ע��ɹ�
             ����:ע��ʧ��
   ע����� 
1�� �ú������ڸ���������ע���¼���ע��ע����ע��Ľ����ڲ�ʵ���¼�����ʱ�Ļص�����
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SubscribeEventForOtherApp(VOS_UINT32 ulEvtType, const VOS_CHAR *pcName);
/*********************************************************************************************
   
  brief      Ϊ��������ȥע���¼���ע
  param[in]  ulEvtType: �¼�����
  param[in]  *pcName: ��������
  return     VOS_OK:ȥע��ɹ�
             ����:ȥע��ʧ��
   ע����� 
1�� �ú������ڸ���������ȥע���¼���ע��ע�������������ڲ���Ҫ֪�����ȥע�����
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_MSG_UnSubscribeEventForOtherApp(VOS_UINT32 ulEvtType, const VOS_CHAR *pcName);
/*********************************************************************************************
   
  brief      ������Ϣ���ݲ�����
  param[in]  *pcProcName: ��Ϣ���շ�
  param[in]  ulMsgType: �¼�����
  param[in]  *pvMsgBuff: ��Ϣ����
  param[in]  ulBuffLen: ��Ϣ���ݳ���
  return     VOS_OK:���ͳɹ�
             ����:����ʧ��
   ע����� 
1�� �ú���������Ҫ���ͽṹ������ַ����ĳ���
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendMsgData(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType,
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen);
/*********************************************************************************************
   
  brief      ��ȡ��ǰ����MSGCTL����
  param[in]  *pcName: ��Ϣ���շ�
  return     VOS_OK:���ͳɹ�
             ����:����ʧ��
   ע����� 
1�� ����
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
        ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
***********************************************************************************************/
VOS_UINT32 ATP_MSG_GetNumOfProcesses(const VOS_CHAR *pcName);
/*********************************************************************************************
   
  brief      ��ǰ���̰�ȫ�˳�
  param[in]  *pcName: �˳���������
  return     VOS_OK:�ɹ�
             ����:ʧ��
   ע����� 
1�� ����
  retval ATP_MSG_RET_PARA_ERR:��Ϣָ����δ��� 
        ATP_MSG_RET_NOT_INITED:��Ϣδ��ʼ��
        ATP_MSG_RET_OVERFLOW:��Ϣ����ʧ�ܣ�ѡ��fd����
        ATP_MSG_RET_FILE_WRITE_FAIL:��Ϣ����ʱд�ļ�ʧ��
        ATP_MSG_RET_PEER_DEAD:socket�Ѿ����ر�
        ATP_MSG_RET_INTERNAL_ERR:��Ϣ����ʱ���������Ĵ���
        ATP_MSG_RET_TIMEOUT:�ظ���Ϣ���ճ�ʱ
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SafeExitProcesses(const VOS_CHAR *pcName);
/*********************************************************************************************
   
  brief      ������Ϣ
  param[in]  *pstMsg: ��������Ϣ
  return     �ɹ������ؿ��������Ϣָ��
             ʧ�ܣ�����NULL
   ע����� 
1�� ����
  retval 
***********************************************************************************************/
ATP_MSG_HEADER_ST *ATP_MSG_Dup(const ATP_MSG_HEADER_ST *pstMsg);

#include "notifyutil.h"
#include "fileutil.h"
#include "sysapi.h"
#include "strutil.h"

typedef struct tagATP_MSG_HDL_LIST_ST
{
    struct tagATP_MSG_HDL_LIST_ST       *pstNext;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulPriority;
    AtpMsgProc                          pfProc;
    AtpSyncMsgProc                      pfSyncProc;
} ATP_MSG_HDL_LIST_ST;
/*********************************************************************************************
  author      
  brief      �첽��Ϣע��ص������ӿ�
  param[in]  ulMsgType : ��Ϣ����
  param[in]  pfProc : �첽��Ϣ����ص�����
  param[in]  ulPriority : �첽��Ϣ�������ȼ�
  param[in]  **ppstMsgHdl:�ص����������Ϣ��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval  ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��          
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RegSyncMsgProc(VOS_UINT32 ulMsgType, AtpSyncMsgProc pfProc, VOS_UINT32 ulPriority, ATP_MSG_HDL_LIST_ST **ppstMsgHdl);

/*********************************************************************************************
   
  brief      ͬ����Ϣע��ص������ӿ�
  param[in]  ulMsgType : ��Ϣ����
  param[in]  pfProc : ͬ����Ϣ����ص�����
  param[in]  ulPriority : ͬ����Ϣ�������ȼ�
  param[in]  **ppstMsgHdl:�ص����������Ϣ��
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����
  retval  ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��          
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RegMsgProc(VOS_UINT32 ulMsgType, AtpMsgProc pfProc, VOS_UINT32 ulPriority, ATP_MSG_HDL_LIST_ST **ppstMsgHdl);
/*********************************************************************************************
   
  brief      ����Ϣ�����б���ɾ����ǰ��Ϣ����ṹ
  param[in]  *ppstMsgHdl:��ɾ����Ϣ����ṹ
  return     
  
   ע����� 
1�� ����
  retval          
***********************************************************************************************/
VOS_VOID ATP_MSG_UnRegMsgProc(ATP_MSG_HDL_LIST_ST *ppstMsgHdl);
/*********************************************************************************************
   
  brief      Ĭ����Ϣ������
  param[in]  *pstMsg:���յ�����Ϣ
  return     
  
   ע����� 
1�� ������Ҫ���ȵ����������������ͨ��ע����Ϣ�ص������ķ�ʽ��������Ϣ
  retval          
***********************************************************************************************/
VOS_VOID ATP_MSG_DefaultMsgProc(const ATP_MSG_HEADER_ST *pstMsg);

#ifdef SUPPORT_ATP_BOOT_TRACK
#define ATP_UTIL_BOOT_TRACK(format, args...) \
    do { \
            struct timeval cur_time; \
            (VOS_VOID)ATP_UTIL_GetSysTime(&cur_time); \
            (VOS_VOID)ATP_UTIL_FilePrintf("/var/atp_boot_track.log", VOS_TRUE, "[tv_sec:%03ld tv_usec:%06ld] ", cur_time.tv_sec, cur_time.tv_usec); \
            (VOS_VOID)ATP_UTIL_FilePrintf("/var/atp_boot_track.log", VOS_TRUE, format, ##args); \
            (VOS_VOID)ATP_UTIL_FilePrintf("/var/atp_boot_track.log", VOS_TRUE, "\r\n"); \
    } while(0)

#else
#define ATP_UTIL_BOOT_TRACK(x...)
#endif

/*
 *  ATP_UTIL_ExecCmdNoHang execute mode function
 */
typedef enum tagATP_UTIL_EXEC_MODE_EN
{
    ATP_UTIL_EXEC_MODE_DFT,     /*!<  Default mode, using msleep to check if child process finished*/
    ATP_UTIL_EXEC_MODE_BLOCK,   /*!<  Wait util child process finished with waitpid*/
    ATP_UTIL_EXEC_MODE_SYSTEM,  /*!<  Use system directly*/
    ATP_UTIL_EXEC_MODE_BACKLOG  /*!<  No exec at all, just log to a file*/
} ATP_UTIL_EXEC_MODE_EN;

typedef struct tagATP_UTIL_EXEC_CTX_ST
{
    VOS_UINT32          ulMode;
    const VOS_CHAR      *pcBackTraceFile;
} ATP_UTIL_EXEC_CTX_ST;

extern const ATP_UTIL_EXEC_CTX_ST *g_pstExecCtx;

#include "atpdebugapi.h"
#include "nlsapi.h"
/*
 *	Kernel version api
 */
typedef enum tagATP_LINUX_VERSION_EN
{
	ATP_LINUX_VERSION_2_6_21 = 0,
	ATP_LINUX_VERSION_2_6_30 = 1,
	ATP_LINUX_VERSION_2_6_36 = 2,
} ATP_LINUX_VERSION_EN;

/*
*    WEB Restful ����
*/
#ifndef REQ_TYPE_FLAG
#define REQ_TYPE_FLAG 1
typedef enum _REQ_TYPE
{
    REQ_GET  = 1,    /*!< HTTP����ΪGET*/
    REQ_POST = 2,    /*!< HTTP����ΪPOST*/
    REQ_HEAD = 4,    /*!< HTTP����ΪHEAD*/
}REQ_TYPE;
#endif

#if defined(SUPPORT_ATP_SMARTHOME) || defined(SUPPORT_ATP_OPEN_EE)
    #define ATP_MSG_WEB_RESTFUL_LEN    (128)
#else
    #define ATP_MSG_WEB_RESTFUL_LEN    (64)
#endif

typedef struct tagATP_MSG_WEBRESTFUL_REQ_ST
{
    VOS_UINT32  ulHttpDirect;                           /* �������� */
    VOS_UINT32  ulIntfType;                             /* ���ù�������    ��ǰ�û��� */
    VOS_CHAR    acModuleName[ATP_MSG_WEB_RESTFUL_LEN];  /*module ����*/
    VOS_CHAR    acFunction[ATP_MSG_WEB_RESTFUL_LEN];    /* ����Ľӿ� */
    VOS_CHAR    acBodyBuff[0];                             /* �����BODY���ݣ��ı���*/
} ATP_MSG_WEBRESTFUL_REQ_ST;

typedef VOS_UINT32 (*PFWebRestfulHandle)(const ATP_MSG_WEBRESTFUL_REQ_ST *pstRestfulReq, VOS_CHAR **pszResp);

typedef struct tagATP_UTIL_RESTFUL_ST
{
    const VOS_CHAR          *pcAPIName;
    PFWebRestfulHandle      pfHandle;
} ATP_UTIL_RESTFUL_ST;
/*********************************************************************************************
   
  brief      ע��restful����ص�����
  param[in]  *pszModuleName:restful�ӿڶ�Ӧ��ģ������
  param[in]  *pstRestfulAPI:restful�ӿ�API���ƺͶ�Ӧ�ص�����
  param[in]  bExactMatch:�Ƿ���ж���ƥ��
  return     VOS_OK:ע��ɹ�
             ����:ʧ��
  
   ע����� 
1�� pstRestfulAPI��Ӧ����һ�����飬һ��api��Ӧһ���ص�����
  static ATP_UTIL_RESTFUL_ST m_astStaRestAPIExs[] =
  {
      {"wps-pbc",             sta_wps_pbc_restful},
      {"wps-cancel",          sta_wps_cancel_restful},
      {NULL, NULL}
  } ;

  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RegRestfulProcsEx(
                const VOS_CHAR            *pszModuleName,
                const ATP_UTIL_RESTFUL_ST *pstRestfulAPI,
                VOS_BOOL                  bExactMatch);
/*********************************************************************************************
   
  brief      ע��restful����ص�����
  param[in]  *pszModuleName:restful�ӿڶ�Ӧ��ģ������
  param[in]  *pstRestfulAPI:restful�ӿ�API���ƺͶ�Ӧ�ص�����
  return     VOS_OK:ע��ɹ�
             ����:ʧ��
  
   ע����� 
1�� pstRestfulAPI��Ӧ����һ�����飬һ��api��Ӧһ���ص�����
  static ATP_UTIL_RESTFUL_ST m_astStaRestAPIExs[] =
  {
      {"wps-pbc",             sta_wps_pbc_restful},
      {"wps-cancel",          sta_wps_cancel_restful},
      {NULL, NULL}
  } ;

  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��
***********************************************************************************************/
VOS_UINT32 ATP_MSG_RegRestfulProcs(
                const VOS_CHAR* pszModuleName,
                const ATP_UTIL_RESTFUL_ST *pstRestfulAPI);

/*********************************************************************************************
   
  brief      ����restful������Ϣ
  param[in]  enType:restful����
  param[in]  ulIntfType:restful�ӿ�ע����Ϣ���ù�������
  param[in]  *pcModName:restful�ӿ�ģ����
  param[in]  *pcFuncName:restful�ӿں�����
  param[in]  *pcBody:restful�ӿ�������
  param[in]  lBodyLen:restful�ӿ������ĳ���
  return     ����ɹ���Ϣ��:�ɹ�
             NULL:ʧ��
  
   ע����� 
1�� �ú������ڴ���䣬��ʹ����Ϻ���Ҫɾ��

  retval  
***********************************************************************************************/
ATP_MSG_HEADER_ST *ATP_MSG_BuildRestfulReqMsg(REQ_TYPE enType, VOS_UINT32 ulIntfType, const VOS_CHAR *pcModName,
                                                const VOS_CHAR *pcFuncName, const VOS_CHAR *pcBody, const VOS_INT32 lBodyLen);
/*********************************************************************************************
   
  brief      ����restful��Ӧ��Ϣ
  param[in]  *pcProcName:restful�ӿڻ�Ӧ��Ϣ���ͷ�
  param[in]  ulMsgType:restful�ӿڻ�Ӧ��Ϣ����
  param[in]  *pvMsgBuff:restful�ӿڻ�Ӧ��Ϣ��Ϣ��
  param[in]  ulBuffLen:restful�ӿڻ�Ӧ��Ϣ��Ϣ�峤��
  param[in]  ulMsgData:restful�ӿڻ�Ӧ��ϢMsgData
  param[in]  ulSeqNum:restful�ӿڻ�Ӧ��Ϣ���к�
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� �ú������ڴ���䣬��ʹ����Ϻ���Ҫɾ��

  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendRestfulResponseMsg(const VOS_CHAR *pcProcName, VOS_UINT32 ulMsgType,
    const VOS_CHAR* pvMsgBuff, VOS_UINT32 ulBuffLen, VOS_UINT32 ulMsgData, VOS_UINT32 ulSeqNum);
/*********************************************************************************************
  author      
  brief      ������Ϣ
  param[in]  *pcProcName:��Ϣ���ͷ�
  param[in]  ulMsgType:��Ϣ����
  param[in]  *pvMsgBuff:��Ϣ��Ϣ��
  param[in]  ulBuffLen:��Ϣ��Ϣ�峤��
  param[in]  ulMsgData:��ϢMsgData
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� �ú������ڴ���䣬��ʹ����Ϻ���Ҫɾ��

  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendMsgDataWithData(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType,
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen, VOS_UINT32 ulMsgData);
/*********************************************************************************************
  author      
  brief      ������Ϣ
  param[in]  *pcProcName:��Ϣ���ͷ�
  param[in]  ulMsgType:��Ϣ����
  param[in]  *pvMsgBuff:��Ϣ��Ϣ��
  param[in]  ulBuffLen:��Ϣ��Ϣ�峤��
  param[in]  ulMsgData:��ϢMsgData
  param[in]  ulSeqNum:restful�ӿڻ�Ӧ��Ϣ���к�
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� �ú������ڴ���䣬��ʹ����Ϻ���Ҫɾ��

  retval  ATP_MSG_RET_PARA_ERR:����������
          ATP_MSG_RET_MEM_ERR:mallocʧ�ܣ��ڴ治��
***********************************************************************************************/
VOS_UINT32 ATP_MSG_SendMsgDataWithDataSeq(const VOS_CHAR* pcProcName, VOS_UINT32 ulMsgType,
                               const VOS_VOID* pvMsgBuff, VOS_UINT32 ulBuffLen, VOS_UINT32 ulMsgData, VOS_UINT32 ulSeqNum);


#ifdef ATP_DEBUG
#define ATP_MSG_DEBUG(format, args...)       {printf("FILE: %s LINE: %d: ", __FILE__, __LINE__);printf(format, ##args);}
#else
#define ATP_MSG_DEBUG(x...)
#endif

// Debug modules
#define ATP_MSG_MODULE_LOOP_D           "loop"
#define ATP_MSG_MODULE_MSG_D            "msg"
#define ATP_MSG_MODULE_TIMER_D          "timer"
#define ATP_MSG_MODULE_NOTIFY_D         "notify"
#define ATP_MSG_MODULE_SOCKBASE_D       "sockbase"

#include "sockbaseapi.h"
//#include "dnspubapi.h"


/*
 *  Socket and address api
 */
#if !defined(__KERNEL__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/*********************************************************************************************
  author      
  brief      ͳһreboot�ӿ�,��ִ�ж��Ʋ�����Ȼ����Ϣ��mic ����        
  param[in]  ulRebootType:��������
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� �������null��ʹ��Ĭ�ϵ�reboot����

  retval  
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_Reboot(VOS_UINT32 ulRebootType);
#include "socketutil.h"
#endif
#include "cfmdbapi.h"
#include "dmmsgapi.h"
#include "cfgmsgapi.h"

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
