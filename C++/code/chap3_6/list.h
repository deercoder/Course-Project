#include <iostream>
#include <stdio.h>
using namespace std;

#define INCREMENT 10

class INTLIST{
	int *list;  //动态申请的内存的指针
	int size;   //线性表能够存放的元素个数
	int used;   //线性表已经存放的元素个数
public:
	INTLIST(int s);  //s为线性表能够存放的元素个数
	int insert(int v);   //插入元素v成功时返回1，否则返回0
	int remove(int v);  //删除元素v成功时返回1，否则返回0
	int find(int v);   //查找元素v成功时返回1，否则返回0
	int get(int v);   //取表的第k个元素的值作为返回值
	void print();     //为了输出结果便于调试用而加的。
	~INTLIST();
};
