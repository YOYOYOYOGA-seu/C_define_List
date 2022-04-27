/*
 * @Author Shi Zhangkun
 * @Date 2020-08-01 06:22:43
 * @LastEditTime 2022-04-28 01:52:57
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /C_define_List/test.c
 */ 
#include "miniList.h"
#include <stdio.h>
#include <stdlib.h>
/* list item struct */
typedef struct test{
  miniListItem_t(struct test) lru; //list item obj
  int a;
  float b;
}test_t;

/**
 * @brief  cmp function
 * @note  
 * @param {int} a
 * @param {int} b
 * @retval none
 */
int cmp_Func(test_t* item1, test_t* item2)
{
  return item1->a <= item2->a;
}

int mach_Func(test_t* pItem, int b)
{
  if (b == 0) return 0;
  return (pItem->a != 0)&&(pItem->a%b == 0);
}

int main(int argc, char * aragv[])
{
  test_t testArror[10];
  test_t* p;
  int x;
 
  miniList_t(test_t) head; //list 
  miniList_t(test_t)* pHead = (void*)&head;

  miniList_init(pHead);//list init 

  /* insert & pop */
  for(int i = 0; i < 10; i++)
  {
    testArror[i].a = 2*i;
    testArror[i].b = (random()%100)/3;
    miniList_insertTail(pHead,&testArror[i],lru);
  }
  for(int i = 0; i < 5; i++)
  {
    p = miniList_PopHead(pHead,lru);
  }
  for(int i = 0; i < 5; i++)
  {
    p = miniList_PopTail(pHead,lru);
  }
  miniList_remove(pHead,p,lru);// remove item
  
  /* insert by range */
  miniList_init(pHead);
  miniList_insert(pHead, &testArror[9], <=, a, lru);
  miniList_insert(pHead, &testArror[4], <=, a, lru);
  miniList_insert(pHead, &testArror[2], <=, a, lru);
  miniList_insert(pHead, &testArror[1], <=, a, lru);
  miniList_insert(pHead, &testArror[6], <=, a, lru);
  miniList_insertByFunc(pHead, &testArror[3], cmp_Func, lru);
  miniList_insertByFunc(pHead, &testArror[8], cmp_Func, lru);
  miniList_insertByFunc(pHead, &testArror[0], cmp_Func, lru);
  miniList_insertByFunc(pHead, &testArror[7], cmp_Func, lru);
  miniList_insertByFunc(pHead, &testArror[5], cmp_Func, lru);
  
  printf("list insert(ascending order by test_t::a):");
  const struct test* itor = pHead->firstItem;
  do {
    printf("%d  ", itor->a);
    itor = itor->lru.pNext;
  } while (itor != pHead->firstItem);
  printf("\n\r");

  /* match item */
  miniList_matchMtoM(pHead ,p ,a ,> ,b ,lru);
  if (p)
    printf("machMtoM test_t::a > test_t::b  => a:%d b:%f \n\r", p->a, p->b);
  miniList_matchMtoV(pHead ,p ,a ,== ,0 ,lru);
  if (p)
    printf("machMtoV test_t::a == 0  => a:%d b:%f \n\r", p->a, p->b);
  miniList_matchByFunc(pHead ,p , lru, mach_Func, 7);
  if (p)
    printf("matchByFunc cmp_Func (test_t::a%%7 == 0) => a:%d b:%f \n\r", p->a, p->b);
 
  return 0;
}