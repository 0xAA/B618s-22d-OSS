/*****************************************************************************
 *               Copyright (C) 2017, Huawei Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
******************************************************************************/
/**\file listapi.h
  *
  *\copyright 2017-2030，华为技术有限公司
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
   
  brief      删除列表中所有的元素
  param[in]  *pstList: 列表头
  param[in]  pfDestroy: 删除元素的回调函数
  return 
   注意事项： 
1、如果元素在添加到列表中的时候，元素内部还有其他内存申请，需要在pfDestroy回调函数中进行释放
retval 无返回值
***********************************************************************************************/

VOS_VOID ATP_UTIL_ListDeleteAll(
                        ATP_UTIL_LIST_ST            *pstList,
                        PFUtilListItemDestroyProc   pfDestroy);

/*********************************************************************************************
   
  brief      删除列表中特定元素
  param[in]  **ppstStart: 列表头
  param[in]  *pstDelItem: 待删除元素
  param[in]  pfDestroy: 删除元素的回调函数
  return 
   注意事项： 
1、如果元素在添加到列表中的时候，元素内部还有其他内存申请，需要在pfDestroy回调函数中进行释放
retval 无返回值
***********************************************************************************************/
VOS_VOID ATP_UTIL_ListDeleteItem(
                        ATP_UTIL_LIST_ST            **ppstStart,
                        ATP_UTIL_LIST_ST            *pstDelItem,
                        PFUtilListItemDestroyProc   pfDestroy);
/*********************************************************************************************
   
  brief      删除列表中特定元素
  param[in]  **ppstStart: 列表头
  param[in]  *pstDelItem: 待删除元素
  return 
   注意事项： 
1、这个函数与ATP_UTIL_ListDeleteItem的区别是，只删除元素，不释放元素内存，调用这个函数需要注意
在元素内容使用完毕后释放元素的内存
retval 无返回值
***********************************************************************************************/
VOS_VOID ATP_UTIL_ListDeleteItemEx(
                        ATP_UTIL_LIST_ST            **ppstStart,
                        ATP_UTIL_LIST_ST            *pstDelItem);

/*********************************************************************************************
   
  brief      获取列表中的元素个数
  param[in]  *pstList: 列表头
  return     列表中元素个数
   注意事项： 
1、当列表为空的时候，元素个数为0
retval 列表中的元素个数
***********************************************************************************************/
VOS_UINT32 ATP_UTIL_ListGetCount(ATP_UTIL_LIST_ST *pstList);

/*********************************************************************************************
   
  brief      往列表中添加元素
  param[in]  **ppstList: 列表头
  param[in]  *pstItem: 待添加元素
  return
   注意事项： 
1、待添加元素在外部申请内存，释放的时候调用ATP_UTIL_ListDeleteAll/ATP_UTIL_ListDeleteItem会进行释放。
retval 无返回值
***********************************************************************************************/
VOS_VOID ATP_UTIL_ListAppend(
                        ATP_UTIL_LIST_ST            **ppstList,
                        ATP_UTIL_LIST_ST            *pstItem);
/*********************************************************************************************
   
  brief      从列表中对应的元素
  param[in]  *pstList: 列表头
  param[in]  *pvData: 待查找元素的关键字
  param[in]  pfCompareProc: 待查找元素的比较函数
  return     找到的元素，如果找不到返回为NULL
   注意事项： 
1、遍历列表中的每个元素，将元素跟关键字进行比较，回调函数中是比较算法
retval NULL或者找到的元素
***********************************************************************************************/
ATP_UTIL_LIST_ST *ATP_UTIL_ListFindItem(const ATP_UTIL_LIST_ST *pstList, const VOS_VOID *pvData,
                                        PFUtilListItemCompareProc pfCompareProc);

/*********************************************************************************************
   
  brief      遍历列表中的元素，对元素进行回调函数处理
  param[in]  *pstList: 列表头
  param[in]  *pvCookie: 遍历元素的回调函数的输入参数
  param[in]  pfIterateProc: 遍历元素的回调函数
  return     VOS_OK : 遍历成功
             其他:  遍历失败，具体返回值由回调函数决定
   注意事项： 
1、对列表的每次元素进行回调函数的处理，如果回调函数中无入参，则pvCookie的值输入为NULL
retval VOS_OK : 遍历成功
       其他:  遍历失败，具体返回值由回调函数决定
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
   
  brief      按照顺序将新元素添加到列表中
  param[in]  **ppstList: 列表头
  param[in]  *pstItem: 待添加元素
  return     
   注意事项： 
1、新增元素在调用前有内存申请，列表在使用完毕后需要进行内存释放
2、如果新增的元素ulOrder的值为-1，表示需要将元素添加到列表的最末端
3、整个列表是按照ulOrder从小到大的顺序排列的，元素根据ulOrder的大小排序插入到对应的位子，
如果插入元素ulOrder跟列表中已有的元素相同，则新元素插入到相同ulOrder元素的最后
retval 
***********************************************************************************************/
VOS_VOID ATP_UTIL_OrderListAppend(
                    ATP_UTIL_ORDER_LIST_ST            **ppstList,
                    ATP_UTIL_ORDER_LIST_ST            *pstItem);

/*
 *  Reorder pstList from 1 to the end with no gaps
 */
/*********************************************************************************************
   
  brief      对列表的元素重新排序
  param[in]  *pstList: 列表头
  return     
   注意事项： 
1、调用该函数会对列表中元素的ulOrder重新赋值，列表中ulOrder从1开始，每遍历一个元素+1
retval 
***********************************************************************************************/ 
VOS_VOID ATP_UTIL_OrderListReorder(ATP_UTIL_ORDER_LIST_ST *pstList);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif

