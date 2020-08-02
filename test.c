/*
 * @Author Shi Zhangkun
 * @Date 2020-08-01 06:22:43
 * @LastEditTime 2020-08-02 02:24:29
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /test/test.c
 */ 
#include "miniList.h"

/* list item struct */
typedef struct test{
  miniListItem_t(struct test) lru; //list item obj
  int a;
  float b;
}test_t;

int main(int argc, char * aragv[])
{
  test_t testArror[10];
  test_t* p;
  int x;
 
  miniList_t(test_t) head; //list 
  miniList_t(test_t) * pHead = &head;

  miniList_init(pHead);//list init 
  for(int i = 0; i < 10; i++)
  {
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

  for(int i = 0; i < 10; i++)
  {
    miniList_insertHead(pHead,&testArror[i],lru);
  }
  miniList_matchMtoM(pHead ,p ,a ,> ,b ,lru);//march item, condition: test_t::a > test_t::b
  miniList_matchMtoV(pHead ,p ,a ,== ,0 ,lru);//march itemcondition: test_t::a == 0
  miniList_remove(pHead,p,lru);// remove item
  while(1)
  {

  }
}