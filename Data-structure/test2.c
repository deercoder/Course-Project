#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR  0
#define OK  1
#define OVERFLOW -2
#define queuesize 20
typedef struct BiTNode{
	int data;
	struct BiTNode *lchild,*rchild; //左右孩子指针
}BiTNode,*BiTree;
typedef struct Queue{
	 int front ,rear ;
     BiTree data[queuesize]; //循环队列元素类型为二叉链表结点指针
	 int count;
}Queue; //循环队列结构定义

int CreateBiTree(BiTree * T) { //声明的就是一个BiTree类型的指针,通过修改来对main中的T做修改，然后使其指向根结点
  // 按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树，
  // 构造二叉链表表示的二叉树T。
  int ch;
  printf("请输入一个根结点的值（如果为空，则输入0）\n");
  scanf("%d",&ch);
  if (ch==0) (*T)= NULL;
  else {
    if (!(*T = (BiTNode *)malloc(sizeof(BiTNode))))  return ERROR;
    (*T)->data = ch;              // 生成根结点
    CreateBiTree(&(*T)->lchild);   // 构造左子树
    CreateBiTree(&(*T)->rchild);   // 构造右子树
  }
  return OK;
} // CreateBiTree

int PreOrderTraverse(BiTree T) //用递归算法写的遍历函数，按照先序遍历，同时输出结点的值
{
	if(T!=NULL) 
	{
		printf("%d  ",T->data); 
		PreOrderTraverse(T->lchild); 
		PreOrderTraverse(T->rchild);
	} 
	return OK;
} 

int InorderTraverse(BiTree T)
{
	if(T!=NULL)
	{
		InorderTraverse(T->lchild);
		printf("%d ",T->data);
		InorderTraverse(T->rchild);
	}
	return OK;
}
int PreOrderTraverse2(BiTree T)  //用非递归的算法写的遍历函数，按照先序遍历，同时输出结点的值
{
   BiTree p,s[20];
   int top=0;
   p=T;
   while((p!=NULL)||(top>0))
   {
	   while(p!=NULL)
	   {
		   printf("%d ",p->data);
		   s[++top]=p;
		   p=p->lchild;
	   }
	   p=s[top--];
	   p=p->rchild;
   }
   return OK;
}

int get_all_node(BiTree T)  //求出总的结点的个数
{
   BiTree p,s[20];
   int num_node=0;
   int top=0;
   p=T;
   while((p!=NULL)||(top>0))
   {
	   while(p!=NULL)
	   {
		   num_node++;
		   s[++top]=p;
		   p=p->lchild;
	   }
	   p=s[top--];
	   p=p->rchild;
   }
   return num_node;
}

int get_node0_1(BiTree T)//利用递归算法得到度为0的结点的个数
{
	int num1,num2;
	if(T==NULL)
		return 0;
	else
	{
        if((T->lchild==NULL)&&(T->rchild==NULL))
			return 1;
		else
		{
			num1=get_node0_1(T->lchild);
            num2=get_node0_1(T->rchild);
			return (num1+num2);
		}
	}
}
int get_node0_2(BiTree T) //利用非递归算法，同时采用层次遍历的方法，得到度为0的结点  
{
     Queue *q;
     BiTree p=T;
	 int num=0; 
	 q=(Queue *)malloc(sizeof(Queue));
	 q->front=0;
	 q->rear=0;
	 q->data[q->rear]=p;
	 q->rear++;
	 while(q->front < q->rear)
	 {
		 p=q->data[q->front];
		 q->front++;
		 if(p->lchild==NULL && p->rchild==NULL)
		 {
			 num++;
		 }
		 if(p->lchild!=NULL)
		 {
			 q->data[q->rear]=p->lchild;
			 q->rear++;
		 }
		 if(p->rchild!=NULL)
		 {
			 q->data[q->rear]=p->rchild;
			 q->rear++;
		 }
	 }
	return num;
}

int get_node1(BiTree T) //利用总的关系求出度为1的结点的个数
{
	int num=get_all_node(T)-2*get_node0_1(T)+1;
	return num;
}
int get_node1_1(BiTree T)   //非递归算法，同时利用关系求度为1的结点。
{
	int num=get_all_node(T)-2*get_node0_2(T)+1;
	return num;
}
int get_node2(BiTree T) //利用度为2的结点个数与度为0的结点个数的关系得到
{
	int num=get_node0_1(T)-1;
	return num;
}
int get_node2_1(BiTree T)   //非递归算法，同时利用关系求度为2的结点。
{
	int num=get_node0_2(T)-1;
	return num;
}
int get_node(BiTree T)
{
	int get;
   printf("请输入你要查找的结点的度\n");
   printf("1.查询度为0的所有结点的个数\n");
   printf("2.查询度为1的所有结点的个数\n");
   printf("3.查询度为2的所有结点的个数\n");
   scanf("%d",&get);
   switch(get){
   case 1:
	  printf("度为0的所有结点的个数是%d\n",get_node0_1(T));
	  break;
   case 2:
	   printf("度为1的所有结点的个数是%d\n",get_node1(T));
	   break;
   case 3:
	   printf("度为2的所有结点的个数是%d\n",get_node2(T));
	   break;
   }
   return OK;
}
int get_node_1(BiTree T)        //利用非递归算法的实现
{
	int get;
	printf("下面是用非递归算法来查询\n");
   printf("请输入你要查找的结点的度\n");
   printf("1.查询度为0的所有结点的个数\n");
   printf("2.查询度为1的所有结点的个数\n");
   printf("3.查询度为2的所有结点的个数\n");
   scanf("%d",&get);
   switch(get){
   case 1:
	  printf("度为0的所有结点的个数是%d\n",get_node0_2(T));
	  break;
   case 2:
	   printf("度为1的所有结点的个数是%d\n",get_node1_1(T));
	   break;
   case 3:
	   printf("度为2的所有结点的个数是%d\n",get_node2_1(T));
	   break;
   }
   return OK;
}
int LevelOrder(BiTree T)
{    Queue *q;
     BiTree p;
	 int flag=0;                      //定义flag为层号
	 q=(Queue *)malloc(sizeof(Queue));  //申请循环队列空间
	 q->rear=q->front=q->count=0;      //将循环队列初始化为空
	 q->data[q->rear]=T;
	 q->count++;
	 q->rear=(q->rear+1)%queuesize;       //将根结点入队
	 while (q->count)                   //若队列不为空，做以下操作
		 if(q->data[q->front]){            //当队首元素不为空指针，做以下操作
			 p=q->data[q->front];           //取队首元素*p
			 printf("%d ",p->data);        //打印*p结点的数据域信息
			 ++flag;
			 q->front=(q->front+1)%queuesize;
			 q->count--;       //队首元素出队
			 if (q->count==queuesize)//若队列为队满，则打印队满信息，退出程序的执行
				 printf("the queue full!\n");
			 else{            //若队列不满，将*p结点的左孩子指针入队
				 q->count++;q->data[q->rear]=p->lchild;
				 q->rear=(q->rear+1)%queuesize;
			 }                        //enf of if
			 if (q->count==queuesize)        //若队列为队满，则打印队满信息，退出程序的执行
				 printf("the queue full!\n");
			 else{                      //若队列不满，将*p结点的右孩子指针入队
				 q->count++;q->data[q->rear]=p->rchild;
				 q->rear=(q->rear+1)%queuesize;
			 }                              //end of if
		 }                                //end of if 
		 else{                          //当队首元素为空指针，将空指针出队
			 q->front=(q->front+1)%queuesize;
			 q->count--;
		 }
		 printf("\n");
		 return OK;
}      //end of LevelOrder

int height(BiTree T)
{
	BiTree p=T;
	int a,b;
	if(p==NULL)
		return 0;
	else{
	   if((p->lchild==NULL)&&(p->rchild==NULL))
		    return 1;
    else{
		  a=height(p->rchild);
	      b=height(p->lchild);
		  if(a>b)   return (a+1);
		  else    return (b+1);
		  }
	}
}

int judge(BiTree T)   //采用递归算法来实现判断是否为完全二叉树
{
      if(T ==NULL)  
          return   0;  
      if(T->lchild == NULL && T->rchild== NULL)  
          return   1;   
      if(T->lchild  == NULL  && T->rchild != NULL||T->lchild!=NULL &&T->rchild==NULL)  
          return   0;  
      return   judge(T->lchild) & judge(T->rchild);  

}

int exchange(BiTree T)
{
     BiTree p=T;
	 int exch;
     if(p==NULL)
	     return OK;
	 else
	 {
		 if(p->lchild!=NULL && p->rchild!=NULL)
		 {
             exch=p->lchild->data;
			 p->lchild->data=p->rchild->data;
			 p->rchild->data=exch;
			 exchange(p->lchild);
			 exchange(p->rchild);
		 }
		 else
		 {
			 if(p->lchild==NULL)
				 exchange(p->rchild);
			 else
				 exchange(p->lchild);
		 }
		 return OK;
	 }
}

void copy_TERM(const char *filename,BiTree T)
{
	FILE *fp;
	BiTree p=T,s[20];
	int top=0;
	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("can't open file\n");
		exit(-1);
	}
   while((p!=NULL)||(top>0))
   {
	   while(p!=NULL)
	   {
		   putw(p->data,fp);
		   s[++top]=p;
		   p=p->lchild;
	   }
	   p=s[top--];
	   p=p->rchild;
   }
   fclose(fp);
}
void type(const char *filename,BiTree T)
{
	 FILE *fp;
	 BiTree p=T,s[20];
	 int top=0;
	 if((fp=fopen(filename,"r"))==NULL)
	 {
		 printf("can't open file\n");
		 exit(-1);
	 }		 
	while((p!=NULL)||(top>0))
	{
	   while(p!=NULL)
	   {  
		   printf("%d ",getw(fp));
		   s[++top]=p;
		   p=p->lchild;
	   }
	   p=s[top--];
	   p=p->rchild;
    }
	 fclose(fp);
}

void main()
{
	BiTree T;         //定义一个指向BiTNode结点的指针
	int choice;
	do{
	printf("\n");
	printf("请选择操作：\n");
	printf("1.按照先序的次序生成一颗二叉树\n");
	printf("2.递归算法实现二叉树的先序遍历，输出各结点值\n");
    printf("3.用非递归算法实现二叉树的遍历，输出各结点值\n");
	printf("4.求度分别为0、1、2的结点的数目（递归算法实现）\n");
	printf("5.求度分别为0、1、2的结点的数目（非递归算法实现）\n");
	printf("6.按层次遍历二叉树\n");
	printf("7.求二叉树的高度(深度)\n");
	printf("8.判断是否为完全二叉树，输出\"Yes!\"或\"No!\"\n");
	printf("9.交换每个结点的左右子树,并用先序遍历的方式输出\n");
	printf("10.对交换左右子树后的二叉树作中序遍历\n");
    printf("11.保存到文件\n");
	printf("12.从文件中读取并输出\n");
	printf("13.退出\n");
	scanf("%d",&choice);
	switch(choice){
	case 1:
		CreateBiTree(&T);   //创建二叉树
		break;
    case 2:
		PreOrderTraverse(T); //利用递归算法的先序遍历，输出结点值
		break;
	case 3:
		PreOrderTraverse2(T);//利用非递归算法的先序遍历，输出结点值
		break;
	case 4:
		get_node(T); //利用递归算法得到的各个结点的个数
		break;
	case 5:
		get_node_1(T);  //利用非递归算法得到的各个结点的个数
		break;
	case 6:
		LevelOrder(T);
		break;
	case 7:
		printf("二叉树的高度为%d\n",height(T));
		break;
	case 8:
		if(judge(T)==0)
			printf("No!\n");
		else
			printf("Yes!\n");
		break;
    case 9:
         exchange(T);
		 PreOrderTraverse(T);
		 break;
	case 10:
         InorderTraverse(T);
		 break;
	case 11:
		copy_TERM("d:\\aaa.dat",T);
		break;
	case 12:
		type("d:\\aaa.dat",T);
		break;
	}	
	}while(choice!=13);	
}