#include<stdio.h>
#include<malloc.h>
#include <conio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 10
#define LISTINCREMENT 10
#define ERROR     0
#define OK        1
#define OVERFLOW  -2

typedef struct{
   int *elem;
   int length;
   int listsize;
   }SqList;

int InitList_Sq(SqList *L) //括号中传递参数是是它的指针L,这样才能对它指向的元素改变。
{ 
  int i;
  L->elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
  if(!L->elem)  exit(OVERFLOW);
  L->length =10;
  L->listsize = LIST_INIT_SIZE;
  for(i=0;i<L->length;i++)
  {
      L->elem[i]=i;
  }
  return OK;
}//InitList_Sq

int get_length(SqList *L)
{
	return L->length;
}

int destroy(SqList *L)
{
	L->length=0;
	return OK;
}

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

int main()
{
	int i;
	SqList L;
	int get,e;
    InitList_Sq(&L);
	printf("请输入你要进行的操作序号\n");
	printf("1.线性表置空\n");
	printf("2.求线性表长度\n");
	printf("3.数据元素的插入操作\n");
	printf("4.数据元素的删除操作\n");
	printf("5.显示线性表中的全部元素\n");
	scanf("%d",&get);
	switch(get)
	{
	case 1: 
          destroy(*L);
	case 2:
          get_length(*L);
	case 3:
		  ListInsert_Sq(*L,5,10);
		  printf("");
	case 4:
          ListDelete_Sq(*L,5,&e);
	}
    return OK;
}
