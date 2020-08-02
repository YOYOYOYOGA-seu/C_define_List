/*
 * @Author Shi Zhangkun
 * @Date 2020-08-02 00:32:10
 * @LastEditTime 2020-08-02 00:45:00
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /test/miniList.h
 */ 
#ifndef __MINI_LIST_H
#define __MINI_LIST_H
#define miniList_t(type)   struct{ unsigned int value; type * firstItem; }
#define miniListItem_t(type)   struct{ type * pNext; type * pPrevious; }
/**
 * @brief  
 * @note  
 * @param {miniList_t} head : : list head
 * @retval none
 */
#define miniList_init(head){ \
          head.firstItem = 0; \
          head.value = 0; \
        }
/**
 * @brief  
 * @note  
 * @param {miniList_t} head : : list head
 * @retval number of items in this list 
 */
#define miniList_size(head) head.value;

/**
 * @brief  templete func of match a item in list
 * @note  
 * @param 
 * @retval 
 */
#define miniList_matchTemplate(head,pItem,__expl,__operator,__expr,__listItemObjName) {  \
  if(head.firstItem != 0&&head.value > 0){ \
    void *pTempHead = head.firstItem; \
    while(!(__expl __operator __expr)) \
    { \
      head.firstItem = head.firstItem->__listItemObjName.pNext; \
      if(head.firstItem == pTempHead) \
      { \
        head.firstItem = 0; \
        break; \
      } \
    } \
    pItem = head.firstItem; \
    head.firstItem = pTempHead; \
  }else{ \
    pItem = 0; \
  } \
}
/**
 * @brief match a item in list, search condition is the relationship between item member and a value
 * @note  
 * @param {miniList_t} head : list head 
 * @param {<type*>} pItem : return the match result in this point 
 * @param {} __expl :  expression left, must be the member of list item 
 * @param {} __operator : operator, like == , < , >
 * @param {} __expr : expression left, must be a value 
 * @param {} __listItemObjName : the name of the miniListItem object 
 * @retval 
 */
#define miniList_matchMtoV(head,pItem,__expl,__operator,__expr,__listItemObjName) \
          miniList_matchTemplate(head,pItem,head.firstItem->__expl,__operator,__expr,__listItemObjName)
/**
 * @brief match a item in list, search condition is the relationship between item member and item member
 * @note  
 * @param {miniList_t} head : list head 
 * @param {<type*>} pItem : return the match result in this point 
 * @param {} __expl :  expression left, must be the member of list item 
 * @param {} __operator : operator, like == , < , >
 * @param {} __expr : expression left, must be the member of list item
 * @param {} __listItemObjName : the name of the miniListItem object 
 * @retval 
 */
#define miniList_matchMtoM(head,pItem,__expl,__operator,__expr,__listItemObjName) \
          miniList_matchTemplate(head,pItem,head.firstItem->__expl,__operator,head.firstItem->__expr,__listItemObjName)
 
/**
 * @brief  insert a item to a mini list
 * @note  don't support circle, it mean's the firstItem.pPrevious and lastItem.pNext are both 0
 * @param {miniList_t} head : list head 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insertHead(head,pItem,__listItemObjName) {   \
          if(head.firstItem != 0){   \
            (pItem)->__listItemObjName.pNext = head.firstItem;  \
            (pItem)->__listItemObjName.pPrevious = head.firstItem->__listItemObjName.pPrevious; \
            head.firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            head.firstItem->__listItemObjName.pPrevious = (pItem);  \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
          } \
          head.firstItem = pItem; \
          head.value++;   \
        }
/**
 * @brief  insert a item to a mini list
 * @note  don't support circle, it mean's the firstItem.pPrevious and lastItem.pNext are both 0
 * @param {miniList_t} head : list head 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insertTail(head,pItem,__listItemObjName) {   \
          if(head.firstItem != 0){   \
            (pItem)->__listItemObjName.pNext = head.firstItem;  \
            (pItem)->__listItemObjName.pPrevious = head.firstItem->__listItemObjName.pPrevious; \
            head.firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            head.firstItem->__listItemObjName.pPrevious = (pItem);  \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
             head.firstItem = pItem; \
          } \
          head.value++;   \
        }
/**
 * @brief  pop the first item in this list
 * @note  
 * @param {miniList_t} head : list head 
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval <type> * : the point to the item be poped
 */
#define miniList_PopHead(head, __listItemObjName) head.firstItem;  \
        {   \
          if(head.firstItem != 0&&head.value != 0) \
          { \
            head.value--; \
            if(head.value == 0){   \
              head.firstItem->__listItemObjName.pNext = 0;  \
              head.firstItem->__listItemObjName.pPrevious = 0;  \
              head.firstItem = 0; \
            }else{ \
              head.firstItem->__listItemObjName.pNext->__listItemObjName.pPrevious =  head.firstItem->__listItemObjName.pPrevious;  \
              head.firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = head.firstItem->__listItemObjName.pNext; \
              void* p =  head.firstItem->__listItemObjName.pNext; \
              head.firstItem->__listItemObjName.pNext = 0;  \
              head.firstItem->__listItemObjName.pPrevious = 0;  \
              head.firstItem = p; \
            } \
          } \
        }
/**
 * @brief  pop the last item in this list
 * @note  
 * @param {miniList_t} head : list head 
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval <type> * : the point to the item be poped
 */
#define miniList_PopTail(head, __listItemObjName) \
        (head.firstItem==0)?0:(head.firstItem->__listItemObjName.pPrevious);  \
        {   \
          if(head.firstItem != 0) \
          { \
            head.firstItem = head.firstItem->__listItemObjName.pPrevious; \
            miniList_PopHead(head,__listItemObjName) \
          } \
        }
        
/**
 * @brief  remove item from a list
 * @note  
 * @param {miniList_t} head : list head 
 * @param {<type*>} head : pItem
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_remove(head,pItem,__listItemObjName)  \
        { \
          if(head.firstItem != 0&&head.value != 0) \
          { \
            if(head.firstItem == pItem){ \
              miniList_PopHead(head,__listItemObjName); \
            }else{ \
              pItem->__listItemObjName.pNext->__listItemObjName.pPrevious = pItem->__listItemObjName.pPrevious; \
              pItem->__listItemObjName.pPrevious->__listItemObjName.pNext = pItem->__listItemObjName.pNext; \
              pItem->__listItemObjName.pPrevious = 0; \
              pItem->__listItemObjName.pNext = 0; \
              head.value--; \
            } \
          } \
        }



#endif