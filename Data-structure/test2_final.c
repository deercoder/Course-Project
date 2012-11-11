#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<stdlib.h>
#define ERROR     0
#define OK        1
#define OVERFLOW  -2
typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*LinkList;

int Create_List(LinkList L,int length)
{//创建一个带表头结点的大小为n个的单链表
	int i;                   
	LinkList p, tail; //声明一定要在前面，否则会出错
	    tail=L;
	for(i=0;i<length;i++)
	{
        p=(LinkList)malloc(sizeof(LNode));
		printf("请输入%d个数据\n",length);
		scanf("%d",&p->data);
		p->next=NULL;
        tail->next=p;
		tail=tail->next;
	}
       return OK;
}

int display_all(LinkList L,int length) //依赖于长度，可是却不定，长度函数有问题。
{//显示所有的数据元素
	int i;
	printf("线性表的全部数据元素如下：\n");
	for(i=0;i<length-1;i++)
	{
		printf("%d ",L->next->data);
		L=L->next;
	}
	printf("\n");
	return OK;
}

int length_L(LinkList L) //有问题
{//求得线性表的长度
	int length=0;
	LinkList p=L;
	while(p!=NULL)
	{
		++length;
		p=p->next;
	}
	return length;
}

int ListInsert(LinkList L,int i ,int *e)
{//插入元素
	LinkList p=L,s;
	int j=0;
	while(p&&j<i-1)
	{
		p=p->next;
		++j;
	}
     if(!p||j>i-1) return ERROR;
	 s=(LinkList)malloc(sizeof(LNode));
	 s->data=*e;
	 s->next=p->next;
     p->next=s;
	 return OK;
}
int ListDelet(LinkList L, int i) 
{//删除指定位置的结点
	LinkList p=L,q;
	int j=0;
	while(p->next&&j<i-1)  //寻找第i-1个结点
	{
		p=p->next;
		++j;
	}
    if(!(p->next)||j>i-1) return ERROR;
    q=p->next; p->next=q->next;
    free(q);
	return OK;
}
int Destroy_L(LinkList L)   //这里会遇到一个问题，如果将头结点free掉的话就会出错，
                            //因为头结点不是自己分配的，而是系统分配的，在主函数中，所以无法释放
{
     LinkList head=L,p;
	 p=head;
	 if (head)
		 p = head->next ;
	 head = head->next ;
	 while(head!=NULL)
	 {
		 p=head;
		 head=head->next;
		 free(p);
	 }
	 return OK;
}
int ClearList(LinkList L)
{//线性表置空
	L->next=NULL;  //将头结点指针域置为NULL
	return OK;
}
int max_num(LinkList L)
{
	LinkList p=L->next;
	int max=0;
	while(p!=NULL)
	{
		if(max<=p->data)
			max=p->data;
		p=p->next;
	}
	return max;
}

float aver_num(LinkList L)  //注意函数名不要和变量同名，很容易出错
{ //求出所有元素的平均值
    LinkList p=L->next;
	float average;
	int sum=0;
	int length=length_L(L);
	while(p!=NULL)
	{
		sum+=p->data;
		p=p->next;
	}
	average=(float)sum/(length-1);
	return average;
}

void main()
{
	int i,get,length,e;
	LNode L;           //创建头结点L
	L.next=NULL;
	do{
		printf("\n");
		printf("1.输入数据元素，以先进先出形式创建单链表\n");
        printf("2.销毁单链表\n");
	    printf("3.线性表置空\n");
	    printf("4.求线性表长度\n");
	    printf("5.在第i个数据元素前插入新的元素\n");
	    printf("6. 删除第i个元素\n");
	    printf("7.显示线性表中的全部元素\n");
        printf("8.求最大元素的值和平均值\n");
		printf("9.退出\n");
	    printf("请输入你选择的操作序号\n");
	    scanf("%d",&get);
	    switch(get){
	         case 1:
		            printf("请输入数据元素的个数\n");
		             scanf("%d",&length);
                    Create_List(&L,length);
			        break;
             case 2:
                     Destroy_L(&L);
					 break;
			 case 3:
                     ClearList(&L);
					 break;
			 case 4:
				 length=length_L(&L);
                 printf("这个线性链表的长度(含头结点)为%d\n",length);
				 break;
			 case 5:
				 printf("请分别输入你要插入数据的元素的位置(第i个元素之前)和值(整型)\n");
				 scanf("%d,%d",&i,&e);
                 ListInsert(&L,i,&e);
				 break;
			 case 6:
				 printf("请分别输入你要删除数据的元素的位置(第i个元素)\n");
				 scanf("%d",&i);
                 ListDelet(&L,i);
				 break;
			 case 7:
				   length=length_L(&L);
                   display_all(&L,length);
					break;
			 case 8:
				   printf("线性表中的最大元素是%d\n",max_num(&L));
                   printf("线性表中所有元素的平均值%f\n",aver_num(&L));
				    break;
			 case 9:
				 break;
		}
	}while(get!=9);
            
}
