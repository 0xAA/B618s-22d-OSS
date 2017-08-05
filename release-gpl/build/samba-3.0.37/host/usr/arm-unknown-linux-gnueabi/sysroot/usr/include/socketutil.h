/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file socketutil.h
  *
  *\copyright 2017-2030，华为技术有限公司
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
   
  brief      关闭socket连接          
  param[in]  lSock:待关闭socket fd
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无

  retval  
***********************************************************************************************/
VOS_INT32 ATP_UTIL_SocketClose(VOS_INT32      lSock);
/*********************************************************************************************
   
  brief      获取socket本地地址         
  param[in]  *pstSocket:socket结构体
  param[out] *pcAddr:获取到的本地地址
  param[in]  ulBufLen:地址长度
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无

  retval  ATP_HTTP_RET_PARA_ERR:输入错误
          ATP_HTTP_RET_INTERNAL_ERR:获取地址错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketGetSourceAddr(
                                ATP_SOCKET_ST       *pstSocket,
                                VOS_CHAR			*pcAddr,
                                VOS_UINT32			ulBufLen);
/*********************************************************************************************
   
  brief      给socket设置TTL信息       
  param[in]  lSock:socket fd
  param[in]  ucTTLValue:设置的TTL信息
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无

  retval  ATP_HTTP_RET_PARA_ERR:输入错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketSetTTL(VOS_INT32 lSock, VOS_UINT8 ucTTLValue);
/*********************************************************************************************
   
  brief      给socket设置组播接口信息     
  param[in]  lSock:socket fd
  param[in]  pstIpIf:设置的组播接口信息 
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无

  retval  
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketSetMcastIf(VOS_INT32 lSock, const struct addrinfo *pstIpIf);
/*********************************************************************************************
   
  brief      给socket设置组播地址    
  param[in]  lSock:socket fd
  param[in]  *pcMCastIp:设置的组播地址
  param[in]  *pstLocalIp:绑定的本地地址
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无

  retval  ATP_HTTP_RET_PARA_ERR:输入错误
          ATP_HTTP_RET_INTERNAL_ERR:地址转换错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketJoinMcast(VOS_INT32 lSock, const VOS_CHAR *pcMCastIp, const struct addrinfo *pstLocalIp);

/*********************************************************************************************
   
  brief      给socket设置组播地址    
  param[in]  lSock:socket fd
  param[in]  *pcMCastIp:设置的组播地址
  param[in]  *pstLocalIp:绑定的本地地址
  param[in]  *pcInterface:绑定的本地接口
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 暂无

  retval  ATP_HTTP_RET_PARA_ERR:输入错误
          ATP_HTTP_RET_INTERNAL_ERR:地址转换错误
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_SocketJoinMcastEx(
                                        VOS_INT32               lSock,
                                        const VOS_CHAR          *pcMCastIp,
                                        const struct addrinfo   *pstLocalIp,
                                        const VOS_CHAR          *pcInterface);

/*!
  \brief    创建服务器类型的socket。
  \param[in]  *pcLocalAddr: 绑定的本地IP，可以为空；否则必须是正确的点分格式的IP字符串
  \param[in]  ulPort: 侦听的端口
  \param[in]  enSockType: 创建的socket类型
  \param[in]  *pcIpv6ScopeIdName: ipv6的端口名，默认为br0
  \return
  \retval   >= 0            创建的socket
        ATP_SOCK_INVALID_FD 创建失败
*/
/*********************************************************************************************
   
  brief      创建服务器类型的socket   
  param[in]  *pcLocalAddr: 绑定的本地IP，可以为空；否则必须是正确的点分格式的IP字符串
  param[in]  ulPort: 侦听的端口
  param[in]  enSockType: 创建的socket类型
  param[in]  *pcIpv6ScopeIdName: ipv6的端口名，默认为br0
  return     返回创建的socket fd(>=0):成功
             -1:失败
  
   注意事项： 
1、 此函数有内存分配，使用完毕后需要释放

  retval  
***********************************************************************************************/
VOS_INT32 ATP_UTIL_SocketCreateServerEx(
                                const VOS_CHAR      *pcLocalAddr,
                                VOS_UINT32          ulPort,
                                ATP_SOCK_FLAG_EN    enSockType,
                                const VOS_CHAR       *pcIpv6ScopeIdName);

/*!
  \brief    创建服务器类型的socket。
  \param[in]  *pcLocalAddr: 绑定的本地IP，可以为空；否则必须是正确的点分格式的IP字符串
  \param[in]  ulPort: 侦听的端口
  \param[in]  enSockType: 创建的socket类型
  \return
  \retval   >= 0            创建的socket
        ATP_SOCK_INVALID_FD 创建失败
*/
/*********************************************************************************************
   
  brief      创建服务器类型的socket   
  param[in]  *pcLocalAddr: 绑定的本地IP，可以为空；否则必须是正确的点分格式的IP字符串
  param[in]  ulPort: 侦听的端口
  param[in]  enSockType: 创建的socket类型
  return     返回创建的socket fd(>=0):成功
             -1:失败
  
   注意事项： 
1、 此函数有内存分配，使用完毕后需要释放

  retval  
***********************************************************************************************/
VOS_INT32 ATP_UTIL_SocketCreateServer(
                                const VOS_CHAR      *pcLocalAddr,
                                VOS_UINT32          ulPort,
                                ATP_SOCK_FLAG_EN    enSockType);

/*********************************************************************************************
   
  brief      解析URL变成地址结构体   
  param[in]  *pcHostName: 待解析URL
  param[in]  *pstLocalInterface: 解析时绑定的本地地址
  param[in]  ulRemotePort: 远程端口
  param[out] **ppstResovledAddr: 解析出来的地址链表
  return     VOS_OK:成功
             其他:失败
  
   注意事项： 
1、 此函数有内存分配，使用完毕后需要释放
2、 地址解析出来可能有多个，用链表形势返回

  retval   ATP_MSG_RET_PARA_ERR:入参输入错误
           ATP_MSG_RET_INTERNAL_ERR:URL解析失败
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_GetIpAddresses(
                                const VOS_CHAR          *pcHostName,
                                const struct addrinfo    *pstLocalInterface,
                                VOS_UINT32                ulRemotePort,
                                struct addrinfo            **ppstResovledAddr);
/*********************************************************************************************
   
  brief      复制地址  
  param[in]  *pstSrc: 待复制地址
  param[in]  bCopyList: 是否拷贝地址链表
  return     拷贝成功后的地址或者地址链表:成功
             NULL:失败
  
   注意事项： 
1、 此函数有内存分配，使用完毕后需要释放
2、 当bCopyList为TRUE时，需要拷贝pstSrc指向的地址链，释放的时候需要释放地址链
  retval   
***********************************************************************************************/
struct addrinfo *ATP_UTIL_CopyAddrInfo(const struct addrinfo *pstSrc, VOS_BOOL bCopyList);
/*********************************************************************************************
   
  brief      比较地址是否相同  
  param[in]  *pstAddrL: 比较地址1
  param[in]  *pstAddrR: 比较地址2
  return     VOS_TRUE:相同
             VOS_FALSE:不相同
  
   注意事项： 
1、 暂无
  retval   
***********************************************************************************************/
VOS_BOOL ATP_UTIL_IsAddrInfoSame(const struct addrinfo *pstAddrL, const struct addrinfo *pstAddrR);
/*********************************************************************************************
   
  brief      将地址字符串转换为结构体  
  param[in]  ulSockType: 地址类型ipv4/ipv6
  param[in]  *pcAddr: 待转换字符串
  param[in]  ulPort: 地址对应的端口
  return     解析出来的地址结构体:成功
             NULL:失败
  
   注意事项： 
1、 该函数有内存申请，使用完毕之后需要释放
  retval   
***********************************************************************************************/
struct addrinfo *ATP_UTIL_ParseIPAddress(
                                VOS_UINT32              ulSockType,
                                const VOS_CHAR          *pcAddr,
                                VOS_UINT32              ulPort);
/*********************************************************************************************
   
  brief      地址结构体释放函数  
  param[in]  *pstSockAddr: 待释放地址结构体
  return     
  
   注意事项： 
1、 暂无
  retval   
***********************************************************************************************/
VOS_VOID ATP_UTIL_FreeAddrInfo(struct addrinfo *pstSockAddr);

/*********************************************************************************************
   
  brief      将socket格式转换为地址格式  
  param[in]  ulSockFlag: socket flag
  param[in]  *pstSockAddr: 待转换socket地址
  param[in]  socklen: socket地址长度
  return     
  
   注意事项： 
1、 该函数有内存申请，使用完毕之后需要释放
  retval   
***********************************************************************************************/
struct addrinfo *ATP_UTIL_MakeAddrInfo(
                                VOS_UINT32               ulSockFlag,
                                const struct sockaddr   *pstSockAddr,
                                socklen_t                   socklen);
/*********************************************************************************************
   
  brief      判断地址是否是回环地址
  param[in]  *pstAddr: 待判断地址
  return     VOS_TRUE:是回环地址
             VOS_FALSE:非回环地址
  
   注意事项： 
1、 暂无
  retval   
***********************************************************************************************/
VOS_BOOL ATP_UTIL_IsAddrLoopback(const struct addrinfo *pstAddr);
/*********************************************************************************************
   
  brief      对于URL做编码转换
  param[in]  *src: 待判断地址
  return     转换成功之后的字符串:成功
             NULL:失败
  
   注意事项： 
1、 此函数有内存申请，使用完毕之后需要释放
  retval   
***********************************************************************************************/
VOS_CHAR *ATP_UTIL_UrlEncode(const VOS_CHAR *src);

typedef VOS_UINT32 (*PFUtilNameResolveFunc)(
                                const VOS_CHAR       *pcName,    /*!<  协议栈待解析的域名*/
                                const struct addrinfo *pstLocalInterface,   /*!<  协议栈所绑定的IP*/
                                VOS_UINT32             ulRemotePort,
                                struct addrinfo         **ppstResovledAddr);  /*!<  解析后的IP地址*/
/*********************************************************************************************
   
  brief      注册DNS解析回调函数
  param[in]  pfFunc: 回调函数
  return     
  
   注意事项： 
1、 暂无
  retval   
***********************************************************************************************/
VOS_VOID  ATP_UTIL_RegNameResolveFunc(PFUtilNameResolveFunc pfFunc);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

