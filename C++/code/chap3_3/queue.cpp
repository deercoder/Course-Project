#include "queue.h"

Queue::Queue()
{
	t = tail = (Node *)malloc(sizeof(Node)); //初始化表头
	t->next = tail->next = NULL;
	t->s = tail->s = NULL;
	size = 0;   //初始化的时候size也为0，没有插入数据
}

void Queue::insert(char m)
{
	if (size == 0)
	{
		t->s = tail->s = m;
		++size;
	}
	else if (size == 1)  //两个节点的话需要建立头节点和它们之间的关系
	{
		Node *p = (Node *)malloc(sizeof(Node));
		p->s = m;
		t->next = p;
		tail = p;
		p->next = NULL;
		++size;
	}
	else //两个节点以上的话直接在tail后面添加上去
	{
		Node *p = (Node *)malloc(sizeof(Node));
		p->s = m;
		tail -> next = p;
		tail = p;  //开始缺少这一句，那么tail就不移动了
		p->next = NULL;
		++size;
	}
}
void Queue::delete_p()
{
	if (size == 1) //只有一个数据
	{
		free(t);
		--size;		//大小为0.
	}
	else
	{
		Node *delet = t; //暂存原来的表头指针便于删除
	    t = t -> next ;
		free(delet);
		--size;
	}
}
int Queue::judge()
{
	if (size == 0)  //没插入数据就是空的
		return 1;
	else
		return 0;
}
void Queue::clean()
{
	if (size == 1) //仅仅只有一个节点的时候需要特殊处理
		free(t);
	else
	{
		for (int i = 0; i < size; i++)
		{
			Node *tmp = t; //暂存上面的那个指针
			t = t -> next;
			free(tmp);	
		}
	}
}
void Queue::print()
{
	Node *tmp = t;
	cout << "队列总的长度是:\t"<<size << endl;
	for (int i = 0; i < size ;i++)
	{
		cout << "i = " << i << "\t" << tmp->s << endl;
		tmp = tmp->next;
	}
}