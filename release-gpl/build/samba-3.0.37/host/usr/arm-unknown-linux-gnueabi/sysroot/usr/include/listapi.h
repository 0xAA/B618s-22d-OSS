/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file listapi.h
  *
  *\copyright 2017-2030����Ϊ�������޹�˾
  *\author  
  *\date  2017-6-12
 
*/
#ifndef __ATP_LIST_API_H__
#define __ATP_LIST_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*
 *  General List Utilities
 */
typedef struct tagATP_UTIL_LIST_ST
{
    struct tagATP_UTIL_LIST_ST      *pstNext;
} ATP_UTIL_LIST_ST;
typedef VOS_VOID (* PFUtilListItemDestroyProc)(ATP_UTIL_LIST_ST *pstItem);
typedef VOS_BOOL (* PFUtilListItemCompareProc)(const ATP_UTIL_LIST_ST *pstItem, const VOS_VOID *pvCompare);
typedef VOS_UINT32 (* PFUtilListItemIterateProc)(const ATP_UTIL_LIST_ST *pstItem, const VOS_VOID *pvCookie);

/*********************************************************************************************
   
  brief      ɾ���б������е�Ԫ��
  param[in]  *pstList: �б�ͷ
  param[in]  pfDestroy: ɾ��Ԫ�صĻص�����
  return 
   ע����� 
1�����Ԫ������ӵ��б��е�ʱ��Ԫ���ڲ����������ڴ����룬��Ҫ��pfDestroy�ص������н����ͷ�
retval �޷���ֵ
***********************************************************************************************/

VOS_VOID ATP_UTIL_ListDeleteAll(
                        ATP_UTIL_LIST_ST            *pstList,
                        PFUtilListItemDestroyProc   pfDestroy);

/*********************************************************************************************
   
  brief      ɾ���б����ض�Ԫ��
  param[in]  **ppstStart: �б�ͷ
  param[in]  *pstDelItem: ��ɾ��Ԫ��
  param[in]  pfDestroy: ɾ��Ԫ�صĻص�����
  return 
   ע����� 
1�����Ԫ������ӵ��б��е�ʱ��Ԫ���ڲ����������ڴ����룬��Ҫ��pfDestroy�ص������н����ͷ�
retval �޷���ֵ
***********************************************************************************************/
VOS_VOID ATP_UTIL_ListDeleteItem(
                        ATP_UTIL_LIST_ST            **ppstStart,
                        ATP_UTIL_LIST_ST            *pstDelItem,
                        PFUtilListItemDestroyProc   pfDestroy);
/*********************************************************************************************
   
  brief      ɾ���б����ض�Ԫ��
  param[in]  **ppstStart: �б�ͷ
  param[in]  *pstDelItem: ��ɾ��Ԫ��
  return 
   ע����� 
1�����������ATP_UTIL_ListDeleteItem�������ǣ�ֻɾ��Ԫ�أ����ͷ�Ԫ���ڴ棬�������������Ҫע��
��Ԫ������ʹ����Ϻ��ͷ�Ԫ�ص��ڴ�
retval �޷���ֵ
***********************************************************************************************/
VOS_VOID ATP_UTIL_ListDeleteItemEx(
                        ATP_UTIL_LIST_ST            **ppstStart,
                        ATP_UTIL_LIST_ST            *pstDelItem);

/*********************************************************************************************
   
  brief      ��ȡ�б��е�Ԫ�ظ���
  param[in]  *pstList: �б�ͷ
  return     �б���Ԫ�ظ���
   ע����� 
1�����б�Ϊ�յ�ʱ��Ԫ�ظ���Ϊ0
retval �б��е�Ԫ�ظ���
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ListGetCount(ATP_UTIL_LIST_ST *pstList);

/*********************************************************************************************
   
  brief      ���б������Ԫ��
  param[in]  **ppstList: �б�ͷ
  param[in]  *pstItem: �����Ԫ��
  return
   ע����� 
1�������Ԫ�����ⲿ�����ڴ棬�ͷŵ�ʱ�����ATP_UTIL_ListDeleteAll/ATP_UTIL_ListDeleteItem������ͷš�
retval �޷���ֵ
***********************************************************************************************/
VOS_VOID ATP_UTIL_ListAppend(
                        ATP_UTIL_LIST_ST            **ppstList,
                        ATP_UTIL_LIST_ST            *pstItem);
/*********************************************************************************************
   
  brief      ���б��ж�Ӧ��Ԫ��
  param[in]  *pstList: �б�ͷ
  param[in]  *pvData: ������Ԫ�صĹؼ���
  param[in]  pfCompareProc: ������Ԫ�صıȽϺ���
  return     �ҵ���Ԫ�أ�����Ҳ�������ΪNULL
   ע����� 
1�������б��е�ÿ��Ԫ�أ���Ԫ�ظ��ؼ��ֽ��бȽϣ��ص��������ǱȽ��㷨
retval NULL�����ҵ���Ԫ��
***********************************************************************************************/
ATP_UTIL_LIST_ST *ATP_UTIL_ListFindItem(const ATP_UTIL_LIST_ST *pstList, const VOS_VOID *pvData,
                                        PFUtilListItemCompareProc pfCompareProc);

/*********************************************************************************************
   
  brief      �����б��е�Ԫ�أ���Ԫ�ؽ��лص���������
  param[in]  *pstList: �б�ͷ
  param[in]  *pvCookie: ����Ԫ�صĻص��������������
  param[in]  pfIterateProc: ����Ԫ�صĻص�����
  return     VOS_OK : �����ɹ�
             ����:  ����ʧ�ܣ����巵��ֵ�ɻص���������
   ע����� 
1�����б��ÿ��Ԫ�ؽ��лص������Ĵ�������ص�����������Σ���pvCookie��ֵ����ΪNULL
retval VOS_OK : �����ɹ�
       ����:  ����ʧ�ܣ����巵��ֵ�ɻص���������
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ListIterateItem(const ATP_UTIL_LIST_ST *pstList, const VOS_VOID *pvCookie,
                                      PFUtilListItemIterateProc pfIterateProc);

#define LIST_NEXT(item) \
        (item ? item->pstNext: NULL)
#define LIST_FOR_EACH_SAFE(item, nextItem, list) \
        for (item = list, nextItem = LIST_NEXT(item); item != NULL; item = nextItem, nextItem = LIST_NEXT(nextItem))


/*
 *  List with Orders Utilities
 */
typedef struct tagATP_UTIL_ORDER_LIST_ST
{
    struct tagATP_UTIL_ORDER_LIST_ST *pstNext;
    VOS_UINT32                       ulOrder;
} ATP_UTIL_ORDER_LIST_ST;

/*
 *  Append pstItem to ppstList according to the ulOrder
 *      1) If ulOrder is -1, pstItem will be appended to the last of the list
 *      2) Else ulOrder will be inserted in the asendding order
 *
 *      If pstItem is already in the ppstList, pstItem will be moved to the correct postion in asending order
 */
/*********************************************************************************************
   
  brief      ����˳����Ԫ����ӵ��б���
  param[in]  **ppstList: �б�ͷ
  param[in]  *pstItem: �����Ԫ��
  return     
   ע����� 
1������Ԫ���ڵ���ǰ���ڴ����룬�б���ʹ����Ϻ���Ҫ�����ڴ��ͷ�
2�����������Ԫ��ulOrder��ֵΪ-1����ʾ��Ҫ��Ԫ����ӵ��б����ĩ��
3�������б��ǰ���ulOrder��С�����˳�����еģ�Ԫ�ظ���ulOrder�Ĵ�С������뵽��Ӧ��λ�ӣ�
�������Ԫ��ulOrder���б������е�Ԫ����ͬ������Ԫ�ز��뵽��ͬulOrderԪ�ص����
retval 
***********************************************************************************************/
VOS_VOID ATP_UTIL_OrderListAppend(
                    ATP_UTIL_ORDER_LIST_ST            **ppstList,
                    ATP_UTIL_ORDER_LIST_ST            *pstItem);

/*
 *  Reorder pstList from 1 to the end with no gaps
 */
/*********************************************************************************************
   
  brief      ���б��Ԫ����������
  param[in]  *pstList: �б�ͷ
  return     
   ע����� 
1�����øú�������б���Ԫ�ص�ulOrder���¸�ֵ���б���ulOrder��1��ʼ��ÿ����һ��Ԫ��+1
retval 
***********************************************************************************************/ 
VOS_VOID ATP_UTIL_OrderListReorder(ATP_UTIL_ORDER_LIST_ST *pstList);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif

