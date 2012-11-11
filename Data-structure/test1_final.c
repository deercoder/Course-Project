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
  L->listsize = LIST_INIT_SIZE; //分配初始的空间
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

int ListInsert_Sq(SqList *L,int i, int e)
{ //在顺序表L中的第i个位置之前插入新的元素e；
	//i的合法值为1<=i<=ListLength_Sq(L)+1;
	int *newbase,*q,*p;
	if(i<1||i>L->length+1) return ERROR;
	if(L->length>=L->listsize){// 当前的存储空间已满，增加分配
		 newbase = ( int *)realloc(L->elem,( L->listsize +LISTINCREMENT)*sizeof(int));
		 if(!newbase) exit(OVERFLOW) ; //存储空间分配失败
		 L->elem = newbase;
		 L->listsize+=LISTINCREMENT;	 
   }
   q=&(L->elem[i-1]);
   for(p=&(L->elem[L->length-1]);p>=q;--p)  *(p+1)=*p;
                                       //插入位置及之后的元素右移            
   *q=e;
   ++L->length;
   return OK;
}//ListInsert_Sq;

int ListDelete_Sq(SqList *L, int i, int e) {  
  // 在顺序线性表L中删除第i个元素，并用e返回其值。
  // i的合法值为1≤i≤ListLength_Sq(L)。
  int *p, *q;
  if (i<1 || i>L->length) return ERROR;  // i值不合法
  p = &(L->elem[i-1]);                   // p为被删除元素的位置
  e = *p;                               // 被删除元素的值赋给e
  q = L->elem+L->length-1;                // 表尾元素的位置
  for (++p; p<=q; ++p) *(p-1) = *p;     // 被删除元素之后的元素左移
  --L->length;                           // 表长减1
  return OK;
} // ListDelete_Sq

int display_all(SqList *L)
{
	int i;
	for(i=0;i<L->length;i++)
	{
		printf("%d",L->elem[i]);
		printf(" ");
	}
	return OK;
}
int main()
{
	SqList L;
	int get,e=0;
	int i,num;
    InitList_Sq(&L);
	printf("数据的初始化已经做好，直接可以观察，具体使用方法见实验报告\n");
	do{
	printf("请输入你要进行的操作序号\n");
	printf("1.线性表置空\n");
	printf("2.求线性表长度\n");
	printf("3.数据元素的插入操作\n");
	printf("4.数据元素的删除操作\n");
	printf("5.显示线性表中的全部元素\n");
	printf("6.退出\n");
	scanf("%d",&get);
	switch(get)
	{
	case 1: 
          destroy(&L);//将顺序表置空，只需要将其长度置零
		  break;
	case 2:
          printf("该线性表的长度是%d\n",get_length(&L)); //求取线性表的长度
		  break;
	case 3:
		  //在指定的位置上插入指定的数据元素
		  printf("请输入你要插入的元素的位置（即在第i个元素之前插入）以及插入元素(中间以逗号分开)\n");
		  scanf("%d,%d",&i,&num);
		  ListInsert_Sq(&L,i,num); 
		  printf("新的线性表是\n");
		  display_all(&L);
		  break;
	case 4:
		//删除指定位置的数据元素
		  printf("请输入你要删除的元素的位置（即删除第i个元素）\n");
		  scanf("%d",&i);
          ListDelete_Sq(&L,i,e);
		  printf("新的线性表是\n");
		  display_all(&L);
		  break;
	case 5:
		//显示线性表的所有元素
		  display_all(&L);
		  printf("\n");
		  break;
	case 6:
		//退出程序
		  break;
	}
	}while(get!=6);
    return OK;
}
