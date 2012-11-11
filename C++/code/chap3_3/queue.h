#include <iostream>
#include <stdio.h>
using namespace std;

typedef struct Node{
	char s;
	Node *next;
}Node;

class Queue
{
	Node *t;     //头指针，也就是那个数组名
	Node *tail; //尾指针，指示最后一个元素
	int size;  //队列的长度，即元素个数
public :
	Queue();
	~Queue(){}
	void insert(char s);  //将一个字符s插入到队列尾部
	void delete_p(); //删除队列的队首元素
	int judge(); //判断一个队列是否为空，为空返回1，否则返回0
	void clean();  //清空队列
	void print();   //测试和调试代码用
};
