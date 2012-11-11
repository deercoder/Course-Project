#include "Set.h"
#include <iostream>
using namespace std;

SET::SET(int card):set(0),card(0),used(0)
{
	set = (int *)malloc(card * sizeof(int));
	this->card = card;
	this->used = 0;
}

SET::~SET()
{
	free(set);
}

int SET::size()
{
	return used;
}

int SET::insert(int v)
{
	for (int i = 0; i < used; i++)
	{
		if (v == set[i])  //插入元素已经存在,插入失败
		{
		/*	cout << "插入元素已经存在，插入失败" << endl;*/
			return 0;
		}
	}
	if (card == 0) //集合已满，需要重新分配
	{
		set = (int *)realloc(set,(used + INCRESEMENT)*sizeof(int));
		card = INCRESEMENT; //重新赋值能够存放的元素个数
		set[used] = v;
		--card;   //每次插入后剩余的能够存放个数减少
		++used;	  //每次插入后已经存放的个数增加
		return 1;
	}
	else
	{
		set[used] = v;
		--card;   //每次插入后剩余的能够存放个数减少
		++used;   //每次插入后已经存放的个数增加
		return 1;
	}
}

int SET::remove(int v)
{
	int mark = -1; //标记找到元素的位置
	for (int i = 0; i < used; i++)
	{
		if (v == set[i])
		{
			mark = i;
			break;
		}
	}
	if (-1 == mark) //没有找到所要删除的元素，错误
	{
	/*	cout << "没有找到所要删除的元素v，删除失败" << endl;*/
		return 0;
	}
	else
	{
		for (int i = mark; i < used - 1; i++)
		{
			set[i] = set[i+1];
		}
		--used;  //删除一个元素后已存储空间减少
		++card;  //删除一个元素后可用空间增加
		return 1;
	}
}
int SET::has(int v)
{
	for (int i = 0; i < used; i++)
	{
		if (v == set[i])
		{
			cout << "找到元素v，所在的位置是" << i+1 << endl; //位置是下标加1
			return 1;
		}
	}
	//cout << "没有找到元素v，查找失败" << endl;
	return 0;
}

void SET::print()
{
	cout << "已存放元素个数为：" << size() << endl;
	for (int i = 0; i < used; i++)
	{
		cout << set[i] << "  ";
	}
	cout << endl;
}
