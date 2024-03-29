/*
 * @Author Shi Zhangkun
 * @Date 2020-08-02 00:32:10
 * @LastEditTime 2022-04-28 01:49:57
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /C_define_List/miniList.h
 */ 
#ifndef __MINI_LIST_H
#define __MINI_LIST_H

/** A mini list (ring list) creat define, this define can creat a struct obj that 
 * using the specified input type, so it can easily embed into any data struct 
 * and can opreate the struct as a list item.
 * 
 * for example :
 *         miniList_t(type) listHead;
 * 
 *         struct listObj{
 *            ...
 *            miniList_t(srtuct Obj) lp;
 *            ...
 *        };
 */

#define miniList_t(type)   struct{ unsigned int value; type * firstItem; }
#define miniListItem_t(type)   struct{ type * pNext; type * pPrevious; }
/**
 * @brief  
 * @note  
 * @param {miniList_t *} pHead : : list pHead
 * @retval none
 */
#define miniList_init(pHead){ \
          (pHead)->firstItem = 0; \
          (pHead)->value = 0; \
        }
/**
 * @brief  
 * @note  
 * @param {miniList_t *} pHead : : list pHead
 * @retval number of items in this list 
 */
#define miniList_size(pHead) (pHead)->value;

/**
 * @brief  templete func of match a item in list
 * @note  
 * @param 
 * @retval 
 */
#define __miniList_matchTemplate(pHead,pItem,__expl,__operator,__expr,__listItemObjName) {  \
  if((pHead)->firstItem != 0&&(pHead)->value > 0){ \
    void *pTempHead = (pHead)->firstItem; \
    while(!(__expl __operator __expr)) \
    { \
      (pHead)->firstItem = (pHead)->firstItem->__listItemObjName.pNext; \
      if((pHead)->firstItem == pTempHead) \
      { \
        (pHead)->firstItem = 0; \
        break; \
      } \
    } \
    pItem = (pHead)->firstItem; \
    (pHead)->firstItem = pTempHead; \
  }else{ \
    pItem = 0; \
  } \
}
/**
 * @brief match a item in list, search condition is the relationship between item member and a value
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type*>} pItem : return the match result in this point 
 * @param {} __expl :  expression left, must be the member of list item 
 * @param {} __operator : operator, like == , < , >
 * @param {} __expr : expression left, must be a value 
 * @param {} __listItemObjName : the name of the miniListItem object 
 * @retval 
 */
#define miniList_matchMtoV(pHead,pItem,__expl,__operator,__expr,__listItemObjName) \
          __miniList_matchTemplate(pHead,pItem,(pHead)->firstItem->__expl,__operator,__expr,__listItemObjName)
/**
 * @brief match a item in list, search condition is the relationship between item member and item member
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type*>} pItem : return the match result in this point 
 * @param {} __expl :  expression left, must be the member of list item 
 * @param {} __operator : operator, like == , < , >
 * @param {} __expr : expression left, must be the member of list item
 * @param {} __listItemObjName : the name of the miniListItem object 
 * @retval 
 */
#define miniList_matchMtoM(pHead,pItem,__expl,__operator,__expr,__listItemObjName) \
          __miniList_matchTemplate(pHead,pItem,(pHead)->firstItem->__expl,__operator,(pHead)->firstItem->__expr,__listItemObjName)
 
/**
 * @brief match a item in list by function
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type*>} pItem : return the match result in this point 
 * @param {} __listItemObjName : the name of the miniListItem object 
 * @param {} matchFunc : match function (bool equal(itemType_t* a, Args...))
 * @retval 
 */
#define miniList_matchByFunc(pHead,pItem,__listItemObjName, matchFunc, ...) {  \
  if((pHead)->firstItem != 0&&(pHead)->value > 0){ \
    void *pTempHead = (pHead)->firstItem; \
    while(!matchFunc((pHead)->firstItem, __VA_ARGS__)) \
    { \
      (pHead)->firstItem = (pHead)->firstItem->__listItemObjName.pNext; \
      if((pHead)->firstItem == pTempHead) \
      { \
        (pHead)->firstItem = 0; \
        break; \
      } \
    } \
    pItem = (pHead)->firstItem; \
    (pHead)->firstItem = pTempHead; \
  }else{ \
    pItem = 0; \
  } \
}

/**
 * @brief  insert a item to a mini list by range
 * @note 
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} __operator : operator for range, like  < , >
 * @param {} __rangeItemObjName : ranged item name
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insert(pHead,pItem, __operator, __rangeItemObjName, __listItemObjName) {   \
          if((pHead)->firstItem != 0){   \
            void *pTempHead = (pHead)->firstItem; \
            int ifHead = 1; \
            while (!((pItem)->__rangeItemObjName __operator ((pHead)->firstItem->__rangeItemObjName))) { \
              (pHead)->firstItem = (pHead)->firstItem->__listItemObjName.pNext;  \
               ifHead = 0; \
              if ((pHead)->firstItem == pTempHead) { \
                break; \
              } \
            } \
            (pItem)->__listItemObjName.pNext = (pHead)->firstItem;  \
            (pItem)->__listItemObjName.pPrevious = (pHead)->firstItem->__listItemObjName.pPrevious; \
            (pHead)->firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            (pHead)->firstItem->__listItemObjName.pPrevious = (pItem);  \
            if ((pHead)->firstItem == pTempHead && ifHead) { \
              (pHead)->firstItem = (pItem); \
            } else { \
              (pHead)->firstItem = pTempHead; \
            } \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
            (pHead)->firstItem = (pItem); \
          } \
          (pHead)->value++;   \
        }

/**
 * @brief  insert a item to a mini list by range
 * @note 
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} cmpFunc : compare function for range(bool compare(itemType_t* a, itemType_t* b))
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insertByFunc(pHead,pItem, cmpFunc, __listItemObjName) {   \
          if((pHead)->firstItem != 0){   \
            void *pTempHead = (pHead)->firstItem; \
            int ifHead = 1; \
            while (!cmpFunc((pItem),((pHead)->firstItem))) { \
              (pHead)->firstItem = (pHead)->firstItem->__listItemObjName.pNext;  \
               ifHead = 0; \
              if ((pHead)->firstItem == pTempHead) { \
                break; \
              } \
            } \
            (pItem)->__listItemObjName.pNext = (pHead)->firstItem;  \
            (pItem)->__listItemObjName.pPrevious = (pHead)->firstItem->__listItemObjName.pPrevious; \
            (pHead)->firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            (pHead)->firstItem->__listItemObjName.pPrevious = (pItem);  \
            if ((pHead)->firstItem == pTempHead && ifHead) { \
              (pHead)->firstItem = (pItem); \
            } else { \
              (pHead)->firstItem = pTempHead; \
            } \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
            (pHead)->firstItem = (pItem); \
          } \
          (pHead)->value++;   \
        }

/**
 * @brief  insert a item to a mini list
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insertHead(pHead,pItem,__listItemObjName) {   \
          if((pHead)->firstItem != 0){   \
            (pItem)->__listItemObjName.pNext = (pHead)->firstItem;  \
            (pItem)->__listItemObjName.pPrevious = (pHead)->firstItem->__listItemObjName.pPrevious; \
            (pHead)->firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            (pHead)->firstItem->__listItemObjName.pPrevious = (pItem);  \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
          } \
          (pHead)->firstItem = pItem; \
          (pHead)->value++;   \
        }
/**
 * @brief  insert a item to a mini list
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insertTail(pHead,pItem,__listItemObjName) {   \
          if((pHead)->firstItem != 0){   \
            (pItem)->__listItemObjName.pNext = (pHead)->firstItem;  \
            (pItem)->__listItemObjName.pPrevious = (pHead)->firstItem->__listItemObjName.pPrevious; \
            (pHead)->firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            (pHead)->firstItem->__listItemObjName.pPrevious = (pItem);  \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
             (pHead)->firstItem = pItem; \
          } \
          (pHead)->value++;   \
        }
/**
 * @brief  pop the first item in this list
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval <type> * : the point to the item be poped
 */
#define miniList_PopHead(pHead, __listItemObjName) (pHead)->firstItem;  \
        {   \
          if((pHead)->firstItem != 0&&(pHead)->value != 0) \
          { \
            (pHead)->value--; \
            if((pHead)->value == 0){   \
              (pHead)->firstItem->__listItemObjName.pNext = 0;  \
              (pHead)->firstItem->__listItemObjName.pPrevious = 0;  \
              (pHead)->firstItem = 0; \
            }else{ \
              (pHead)->firstItem->__listItemObjName.pNext->__listItemObjName.pPrevious =  (pHead)->firstItem->__listItemObjName.pPrevious;  \
              (pHead)->firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pHead)->firstItem->__listItemObjName.pNext; \
              void* p =  (pHead)->firstItem->__listItemObjName.pNext; \
              (pHead)->firstItem->__listItemObjName.pNext = 0;  \
              (pHead)->firstItem->__listItemObjName.pPrevious = 0;  \
              (pHead)->firstItem = p; \
            } \
          } \
        }
/**
 * @brief  pop the last item in this list
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval <type> * : the point to the item be poped
 */
#define miniList_PopTail(pHead, __listItemObjName) \
        ((pHead)->firstItem==0)?0:((pHead)->firstItem->__listItemObjName.pPrevious);  \
        {   \
          if((pHead)->firstItem != 0) \
          { \
            (pHead)->firstItem = (pHead)->firstItem->__listItemObjName.pPrevious; \
            miniList_PopHead(pHead,__listItemObjName) \
          } \
        }
        
/**
 * @brief  remove item from a list
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type*>} pHead : pItem
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_remove(pHead,pItem,__listItemObjName)  \
        { \
          if((pHead)->firstItem != 0&&(pHead)->value != 0) \
          { \
            if((pHead)->firstItem == pItem){ \
              miniList_PopHead(pHead,__listItemObjName); \
            }else{ \
              pItem->__listItemObjName.pNext->__listItemObjName.pPrevious = pItem->__listItemObjName.pPrevious; \
              pItem->__listItemObjName.pPrevious->__listItemObjName.pNext = pItem->__listItemObjName.pNext; \
              pItem->__listItemObjName.pPrevious = 0; \
              pItem->__listItemObjName.pNext = 0; \
              (pHead)->value--; \
            } \
          } \
        }



#endif