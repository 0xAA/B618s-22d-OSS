/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file socketutil.h
  *
  *\copyright 2017-2030����Ϊ�������޹�˾
  *\author  
  *\date  2017-6-12
 
*/
#ifndef __ATP_SOCKET_UTIL_H__
#define __ATP_SOCKET_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*********************************************************************************************
   
  brief      �ر�socket����          
  param[in]  lSock:���ر�socket fd
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����

  retval  
***********************************************************************************************/
VOS_INT32 ATP_UTIL_SocketClose(VOS_INT32      lSock);
/*********************************************************************************************
   
  brief      ��ȡsocket���ص�ַ         
  param[in]  *pstSocket:socket�ṹ��
  param[out] *pcAddr:��ȡ���ı��ص�ַ
  param[in]  ulBufLen:��ַ����
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����

  retval  ATP_HTTP_RET_PARA_ERR:�������
          ATP_HTTP_RET_INTERNAL_ERR:��ȡ��ַ����
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketGetSourceAddr(
                                ATP_SOCKET_ST       *pstSocket,
                                VOS_CHAR			*pcAddr,
                                VOS_UINT32			ulBufLen);
/*********************************************************************************************
   
  brief      ��socket����TTL��Ϣ       
  param[in]  lSock:socket fd
  param[in]  ucTTLValue:���õ�TTL��Ϣ
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����

  retval  ATP_HTTP_RET_PARA_ERR:�������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketSetTTL(VOS_INT32 lSock, VOS_UINT8 ucTTLValue);
/*********************************************************************************************
   
  brief      ��socket�����鲥�ӿ���Ϣ     
  param[in]  lSock:socket fd
  param[in]  pstIpIf:���õ��鲥�ӿ���Ϣ 
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����

  retval  
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketSetMcastIf(VOS_INT32 lSock, const struct addrinfo *pstIpIf);
/*********************************************************************************************
   
  brief      ��socket�����鲥��ַ    
  param[in]  lSock:socket fd
  param[in]  *pcMCastIp:���õ��鲥��ַ
  param[in]  *pstLocalIp:�󶨵ı��ص�ַ
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����

  retval  ATP_HTTP_RET_PARA_ERR:�������
          ATP_HTTP_RET_INTERNAL_ERR:��ַת������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketJoinMcast(VOS_INT32 lSock, const VOS_CHAR *pcMCastIp, const struct addrinfo *pstLocalIp);

/*********************************************************************************************
   
  brief      ��socket�����鲥��ַ    
  param[in]  lSock:socket fd
  param[in]  *pcMCastIp:���õ��鲥��ַ
  param[in]  *pstLocalIp:�󶨵ı��ص�ַ
  param[in]  *pcInterface:�󶨵ı��ؽӿ�
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� ����

  retval  ATP_HTTP_RET_PARA_ERR:�������
          ATP_HTTP_RET_INTERNAL_ERR:��ַת������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketJoinMcastEx(
                                        VOS_INT32               lSock,
                                        const VOS_CHAR          *pcMCastIp,
                                        const struct addrinfo   *pstLocalIp,
                                        const VOS_CHAR          *pcInterface);

/*!
  \brief    �������������͵�socket��
  \param[in]  *pcLocalAddr: �󶨵ı���IP������Ϊ�գ������������ȷ�ĵ�ָ�ʽ��IP�ַ���
  \param[in]  ulPort: �����Ķ˿�
  \param[in]  enSockType: ������socket����
  \param[in]  *pcIpv6ScopeIdName: ipv6�Ķ˿�����Ĭ��Ϊbr0
  \return
  \retval   >= 0            ������socket
        ATP_SOCK_INVALID_FD ����ʧ��
*/
/*********************************************************************************************
   
  brief      �������������͵�socket   
  param[in]  *pcLocalAddr: �󶨵ı���IP������Ϊ�գ������������ȷ�ĵ�ָ�ʽ��IP�ַ���
  param[in]  ulPort: �����Ķ˿�
  param[in]  enSockType: ������socket����
  param[in]  *pcIpv6ScopeIdName: ipv6�Ķ˿�����Ĭ��Ϊbr0
  return     ���ش�����socket fd(>=0):�ɹ�
             -1:ʧ��
  
   ע����� 
1�� �˺������ڴ���䣬ʹ����Ϻ���Ҫ�ͷ�

  retval  
***********************************************************************************************/
VOS_INT32 ATP_UTIL_SocketCreateServerEx(
                                const VOS_CHAR      *pcLocalAddr,
                                VOS_UINT32          ulPort,
                                ATP_SOCK_FLAG_EN    enSockType,
                                const VOS_CHAR       *pcIpv6ScopeIdName);

/*!
  \brief    �������������͵�socket��
  \param[in]  *pcLocalAddr: �󶨵ı���IP������Ϊ�գ������������ȷ�ĵ�ָ�ʽ��IP�ַ���
  \param[in]  ulPort: �����Ķ˿�
  \param[in]  enSockType: ������socket����
  \return
  \retval   >= 0            ������socket
        ATP_SOCK_INVALID_FD ����ʧ��
*/
/*********************************************************************************************
   
  brief      �������������͵�socket   
  param[in]  *pcLocalAddr: �󶨵ı���IP������Ϊ�գ������������ȷ�ĵ�ָ�ʽ��IP�ַ���
  param[in]  ulPort: �����Ķ˿�
  param[in]  enSockType: ������socket����
  return     ���ش�����socket fd(>=0):�ɹ�
             -1:ʧ��
  
   ע����� 
1�� �˺������ڴ���䣬ʹ����Ϻ���Ҫ�ͷ�

  retval  
***********************************************************************************************/
VOS_INT32 ATP_UTIL_SocketCreateServer(
                                const VOS_CHAR      *pcLocalAddr,
                                VOS_UINT32          ulPort,
                                ATP_SOCK_FLAG_EN    enSockType);

/*********************************************************************************************
   
  brief      ����URL��ɵ�ַ�ṹ��   
  param[in]  *pcHostName: ������URL
  param[in]  *pstLocalInterface: ����ʱ�󶨵ı��ص�ַ
  param[in]  ulRemotePort: Զ�̶˿�
  param[out] **ppstResovledAddr: ���������ĵ�ַ����
  return     VOS_OK:�ɹ�
             ����:ʧ��
  
   ע����� 
1�� �˺������ڴ���䣬ʹ����Ϻ���Ҫ�ͷ�
2�� ��ַ�������������ж�������������Ʒ���

  retval   ATP_MSG_RET_PARA_ERR:����������
           ATP_MSG_RET_INTERNAL_ERR:URL����ʧ��
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_GetIpAddresses(
                                const VOS_CHAR          *pcHostName,
                                const struct addrinfo    *pstLocalInterface,
                                VOS_UINT32                ulRemotePort,
                                struct addrinfo            **ppstResovledAddr);
/*********************************************************************************************
   
  brief      ���Ƶ�ַ  
  param[in]  *pstSrc: �����Ƶ�ַ
  param[in]  bCopyList: �Ƿ񿽱���ַ����
  return     �����ɹ���ĵ�ַ���ߵ�ַ����:�ɹ�
             NULL:ʧ��
  
   ע����� 
1�� �˺������ڴ���䣬ʹ����Ϻ���Ҫ�ͷ�
2�� ��bCopyListΪTRUEʱ����Ҫ����pstSrcָ��ĵ�ַ�����ͷŵ�ʱ����Ҫ�ͷŵ�ַ��
  retval   
***********************************************************************************************/
struct addrinfo *ATP_UTIL_CopyAddrInfo(const struct addrinfo *pstSrc, VOS_BOOL bCopyList);
/*********************************************************************************************
   
  brief      �Ƚϵ�ַ�Ƿ���ͬ  
  param[in]  *pstAddrL: �Ƚϵ�ַ1
  param[in]  *pstAddrR: �Ƚϵ�ַ2
  return     VOS_TRUE:��ͬ
             VOS_FALSE:����ͬ
  
   ע����� 
1�� ����
  retval   
***********************************************************************************************/
VOS_BOOL ATP_UTIL_IsAddrInfoSame(const struct addrinfo *pstAddrL, const struct addrinfo *pstAddrR);
/*********************************************************************************************
   
  brief      ����ַ�ַ���ת��Ϊ�ṹ��  
  param[in]  ulSockType: ��ַ����ipv4/ipv6
  param[in]  *pcAddr: ��ת���ַ���
  param[in]  ulPort: ��ַ��Ӧ�Ķ˿�
  return     ���������ĵ�ַ�ṹ��:�ɹ�
             NULL:ʧ��
  
   ע����� 
1�� �ú������ڴ����룬ʹ�����֮����Ҫ�ͷ�
  retval   
***********************************************************************************************/
struct addrinfo *ATP_UTIL_ParseIPAddress(
                                VOS_UINT32              ulSockType,
                                const VOS_CHAR          *pcAddr,
                                VOS_UINT32              ulPort);
/*********************************************************************************************
   
  brief      ��ַ�ṹ���ͷź���  
  param[in]  *pstSockAddr: ���ͷŵ�ַ�ṹ��
  return     
  
   ע����� 
1�� ����
  retval   
***********************************************************************************************/
VOS_VOID ATP_UTIL_FreeAddrInfo(struct addrinfo *pstSockAddr);

/*********************************************************************************************
   
  brief      ��socket��ʽת��Ϊ��ַ��ʽ  
  param[in]  ulSockFlag: socket flag
  param[in]  *pstSockAddr: ��ת��socket��ַ
  param[in]  socklen: socket��ַ����
  return     
  
   ע����� 
1�� �ú������ڴ����룬ʹ�����֮����Ҫ�ͷ�
  retval   
***********************************************************************************************/
struct addrinfo *ATP_UTIL_MakeAddrInfo(
                                VOS_UINT32               ulSockFlag,
                                const struct sockaddr   *pstSockAddr,
                                socklen_t                   socklen);
/*********************************************************************************************
   
  brief      �жϵ�ַ�Ƿ��ǻػ���ַ
  param[in]  *pstAddr: ���жϵ�ַ
  return     VOS_TRUE:�ǻػ���ַ
             VOS_FALSE:�ǻػ���ַ
  
   ע����� 
1�� ����
  retval   
***********************************************************************************************/
VOS_BOOL ATP_UTIL_IsAddrLoopback(const struct addrinfo *pstAddr);
/*********************************************************************************************
   
  brief      ����URL������ת��
  param[in]  *src: ���жϵ�ַ
  return     ת���ɹ�֮����ַ���:�ɹ�
             NULL:ʧ��
  
   ע����� 
1�� �˺������ڴ����룬ʹ�����֮����Ҫ�ͷ�
  retval   
***********************************************************************************************/
VOS_CHAR *ATP_UTIL_UrlEncode(const VOS_CHAR *src);

typedef VOS_UINT32 (*PFUtilNameResolveFunc)(
                                const VOS_CHAR       *pcName,    /*!<  Э��ջ������������*/
                                const struct addrinfo *pstLocalInterface,   /*!<  Э��ջ���󶨵�IP*/
                                VOS_UINT32             ulRemotePort,
                                struct addrinfo         **ppstResovledAddr);  /*!<  �������IP��ַ*/
/*********************************************************************************************
   
  brief      ע��DNS�����ص�����
  param[in]  pfFunc: �ص�����
  return     
  
   ע����� 
1�� ����
  retval   
***********************************************************************************************/
VOS_VOID  ATP_UTIL_RegNameResolveFunc(PFUtilNameResolveFunc pfFunc);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

