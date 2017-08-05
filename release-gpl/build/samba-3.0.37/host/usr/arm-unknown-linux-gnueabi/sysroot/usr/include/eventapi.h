/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file eventapi.h
  *
  *\copyright 2017-2030，华为技术有限公司
  *\author  
  *\date  2017-6-12
*/
#ifndef __ATP_EVENT_API_H__
#define __ATP_EVENT_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct tagATP_UTIL_NV_PAIR_ST
{
    struct tagATP_UTIL_NV_PAIR_ST   *pstNext;
    const VOS_CHAR                  *pcName;
    const VOS_CHAR                  *pcValue;
} ATP_UTIL_NV_PAIR_ST;

/*********************************************************************************************
  author      
  brief      按照NV格式封装参数和参数值
  param[in]  **ppstPairs: NV列表头
  param[in]  *pcName: 参数名称
  param[in]  *pcValue: 参数值
  return     封装成功后的元素结构体，如果失败，返回为NULL
   注意事项： 
1、函数内部有内存申请，列表使用完毕后，需要调用ATP_UTIL_NVPairDelAll释放列表内存
retval 
***********************************************************************************************/
ATP_UTIL_NV_PAIR_ST *ATP_UTIL_NVPairSet(
                ATP_UTIL_NV_PAIR_ST     **ppstPairs,
                const VOS_CHAR          *pcName,
                const VOS_CHAR          *pcValue);

/*********************************************************************************************
  author      
  brief      根据参数名字获取参数值
  param[in]  *pstPairs: NV列表头
  param[in]  *pcName: 参数名称
  return     如果找到了，则返回对应的参数值，否则返回为NULL
   注意事项： 
1、暂无
retval 
***********************************************************************************************/
const VOS_CHAR *ATP_UTIL_NVPairGetValue(
                    ATP_UTIL_NV_PAIR_ST     *pstPairs,
                    const VOS_CHAR          *pcName);
/*********************************************************************************************
  author      
  brief      根据参数名字从列表中删除结构
  param[in]  **ppstPairs: NV列表头
  param[in]  *pcName: 参数名称
  return    
   注意事项： 
1、暂无
retval 
***********************************************************************************************/
VOS_VOID ATP_UTIL_NVPairDelByName(
                ATP_UTIL_NV_PAIR_ST     **ppstPairs,
                const VOS_CHAR          *pcName);

/*********************************************************************************************
  author      
  brief      删除所有的NV对象
  param[in]  *pstPairs: NV列表头
  return    
   注意事项： 
1、暂无
retval 
***********************************************************************************************/
VOS_VOID ATP_UTIL_NVPairDelAll(ATP_UTIL_NV_PAIR_ST *pstPairs);
/*********************************************************************************************
  author      
  brief      打印所有的NV对象
  param[in]  *pstPairs: NV列表头
  return    
   注意事项： 
1、出于安全考虑，在打印的过程中过滤了可能涉及敏感信息的字段
retval 
***********************************************************************************************/
VOS_VOID ATP_UTIL_NVPairPrint(const ATP_UTIL_NV_PAIR_ST *pstPairs);
/*********************************************************************************************
  author      
  brief      根据参数名字查找NV元素
  param[in]  *pstPairs: NV列表头
  param[in]  *pcName: 参数名字
  return    如果找到了，返回对应元素结构体，反之，返回NULL
   注意事项： 
1、暂无
retval 
***********************************************************************************************/
const ATP_UTIL_NV_PAIR_ST *ATP_UTIL_NVPairFindByName(
                const ATP_UTIL_NV_PAIR_ST     *pstPairs,
                const VOS_CHAR                *pcName);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif

