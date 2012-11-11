#include<malloc.h>
#include <conio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define ERROR     0
#define OK        1
#define OVERFLOW  -2

typedef struct{
   int *elem;
   int length;
   int listsize;
   }SqList;
   
int InitList_Sq(SqList L) //括号中传递参数是用L，而不是它的指针&L。
{  /*构造一个空的线性表L*/
  L.elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
  if(!L.elem)  exit(OVERFLOW);
  L.length = 0;
  L.listsize = LIST_INIT_SIZE;
  return OK;
}//InitList_Sq

/*
int ListInsert_Sq(Sqlist &L,int i, int e)
{ //在顺序表L中的第i个位置之前插入新的元素e；
	//i的合法值为1<=i<=ListLength_Sq(L)+1;
	if(i<1||i>L.length+1) return ERROR;
	if(L.length>=L.listsize){// 当前的存储空间已满，增加分配
		 newbase = ( int *)realloc(L.elem,( L.listsize +LISTINCREMENT)*sizeof(int));
		 if(!newbase) exit(OVERFLOW) ; //存储空间分配失败
		 L.elem = newbase;
		 L.listsize+=LISTINCREMENT;	 
   }
   q=&(L.elem[i-1]);
   for(p=&(L.elem[L.length-1]);p>=q;--p)  *(p+1)=*p;
                                       //插入位置及之后的元素右移            
   *q=e;
   ++L.length;
   return OK;
}//ListInsert_Sq;

int ListDelete_Sq(SqList &L, int i, int &e) {  // 算法2.5
  // 在顺序线性表L中删除第i个元素，并用e返回其值。
  // i的合法值为1≤i≤ListLength_Sq(L)。
  int *p, *q;
  if (i<1 || i>L.length) return ERROR;  // i值不合法
  p = &(L.elem[i-1]);                   // p为被删除元素的位置
  e = *p;                               // 被删除元素的值赋给e
  q = L.elem+L.length-1;                // 表尾元素的位置
  for (++p; p<=q; ++p) *(p-1) = *p;     // 被删除元素之后的元素左移
  --L.length;                           // 表长减1
  return OK;
} // ListDelete_Sq

int LocateElem_Sq(SqList L, int e,
        Status (*compare)(ElemType, ElemType)) {  // 算法2.6
  // 在顺序线性表L中查找第1个值与e满足compare()的元素的位序。
  // 若找到，则返回其在L中的位序，否则返回0。
  int i;
  ElemType *p;
  i = 1;        // i的初值为第1个元素的位序
  p = L.elem;   // p的初值为第1个元素的存储位置
  while (i <= L.length && !(*compare)(*p++, e)) 
    ++i;
  if (i <= L.length) return i;
  else return 0;
} // LocateElem_Sq
*/
int main()
{
	SqList L;
    InitList_Sq(L);
    system("pause");
    return OK;
}
