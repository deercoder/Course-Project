#include "queue.h"

Queue::Queue()
{
	t = tail = (Node *)malloc(sizeof(Node)); //初始化表头
	t->next = tail->next = NULL;
	t->s = tail->s = NULL;
	size = 0;
}
//Queue::~Queue()
//{
//	if (size == 1) //仅仅只有一个节点的时候需要特殊处理
//		free(t);
//	for (int i = 0; i < size; i++)
//	{
//		Node *tmp = t; //暂存上面的那个指针
//		t = t -> next;
//		free(tmp);	
//	}
//}
void Queue::insert(char s)
{
	if (size == 0)
	{
		t->s = tail->s = s;
		++size;
	}
	else
	{
		Node *p = (Node *)malloc(sizeof(Node));
		p->s = s;
		tail -> next = p;
		p->next = NULL;
		++size;
	}
}
void Queue::delete_p()
{
	Node *delet = t; //暂存原来的表头指针便于删除
	t = t -> next ;
	free(delet);
	--size;
}
int Queue::judge()
{
	if (size == 0)
		return 1;
	else
		return 0;
}
void Queue::clean()
{
	if (size == 1) //仅仅只有一个节点的时候需要特殊处理
		free(t);
	for (int i = 0; i < size; i++)
	{
		Node *tmp = t; //暂存上面的那个指针
		t = t -> next;
		free(tmp);	
	}
}
void Queue::print()
{
	for (int i = 0; i < size ;i++)
	{
		Node *tmp = t;
		cout << "i = " << i << "\t" << tmp->s << endl;
		tmp = tmp->next;
	}
}