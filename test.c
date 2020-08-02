/*
 * @Author Shi Zhangkun
 * @Date 2020-08-01 06:22:43
 * @LastEditTime 2020-08-02 00:46:44
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
  miniList_init(head);//list init 

  for(int i = 0; i < 10; i++)
  {
    miniList_insertTail(head,&testArror[i],lru);
  }

  for(int i = 0; i < 5; i++)
  {
    p = miniList_PopHead(head,lru);
  }
  for(int i = 0; i < 5; i++)
  {
    p = miniList_PopTail(head,lru);
  }

  for(int i = 0; i < 10; i++)
  {
    miniList_insertHead(head,&testArror[i],lru);
  }
  miniList_matchMtoM(head ,p ,a ,> ,b ,lru);//march item, condition: test_t::a > test_t::b
  miniList_matchMtoV(head ,p ,a ,== ,0 ,lru);//march itemcondition: test_t::a == 0
  miniList_remove(head,p,lru);// remove item
  while(1)
  {

  }
}