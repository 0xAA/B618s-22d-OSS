/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file eventapi.h
  *
  *\copyright 2017-2030����Ϊ�������޹�˾
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
  brief      ����NV��ʽ��װ�����Ͳ���ֵ
  param[in]  **ppstPairs: NV�б�ͷ
  param[in]  *pcName: ��������
  param[in]  *pcValue: ����ֵ
  return     ��װ�ɹ����Ԫ�ؽṹ�壬���ʧ�ܣ�����ΪNULL
   ע����� 
1�������ڲ����ڴ����룬�б�ʹ����Ϻ���Ҫ����ATP_UTIL_NVPairDelAll�ͷ��б��ڴ�
retval 
***********************************************************************************************/
ATP_UTIL_NV_PAIR_ST *ATP_UTIL_NVPairSet(
                ATP_UTIL_NV_PAIR_ST     **ppstPairs,
                const VOS_CHAR          *pcName,
                const VOS_CHAR          *pcValue);

/*********************************************************************************************
  author      
  brief      ���ݲ������ֻ�ȡ����ֵ
  param[in]  *pstPairs: NV�б�ͷ
  param[in]  *pcName: ��������
  return     ����ҵ��ˣ��򷵻ض�Ӧ�Ĳ���ֵ�����򷵻�ΪNULL
   ע����� 
1������
retval 
***********************************************************************************************/
const VOS_CHAR *ATP_UTIL_NVPairGetValue(
                    ATP_UTIL_NV_PAIR_ST     *pstPairs,
                    const VOS_CHAR          *pcName);
/*********************************************************************************************
  author      
  brief      ���ݲ������ִ��б���ɾ���ṹ
  param[in]  **ppstPairs: NV�б�ͷ
  param[in]  *pcName: ��������
  return    
   ע����� 
1������
retval 
***********************************************************************************************/
VOS_VOID ATP_UTIL_NVPairDelByName(
                ATP_UTIL_NV_PAIR_ST     **ppstPairs,
                const VOS_CHAR          *pcName);

/*********************************************************************************************
  author      
  brief      ɾ�����е�NV����
  param[in]  *pstPairs: NV�б�ͷ
  return    
   ע����� 
1������
retval 
***********************************************************************************************/
VOS_VOID ATP_UTIL_NVPairDelAll(ATP_UTIL_NV_PAIR_ST *pstPairs);
/*********************************************************************************************
  author      
  brief      ��ӡ���е�NV����
  param[in]  *pstPairs: NV�б�ͷ
  return    
   ע����� 
1�����ڰ�ȫ���ǣ��ڴ�ӡ�Ĺ����й����˿����漰������Ϣ���ֶ�
retval 
***********************************************************************************************/
VOS_VOID ATP_UTIL_NVPairPrint(const ATP_UTIL_NV_PAIR_ST *pstPairs);
/*********************************************************************************************
  author      
  brief      ���ݲ������ֲ���NVԪ��
  param[in]  *pstPairs: NV�б�ͷ
  param[in]  *pcName: ��������
  return    ����ҵ��ˣ����ض�ӦԪ�ؽṹ�壬��֮������NULL
   ע����� 
1������
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

