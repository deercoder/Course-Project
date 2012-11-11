#define MAX 5
#include <iostream>

using namespace std;

class qArray
{
	char qArr[MAX];  //定义一个大的字符数组,满队列的时候大小为MAX-1
	int front;	//表示队列头部的位置,指的是下标的位置
	int rear;	//表示对垒尾部的下一个位置
	int size ;   //队列的实际长度
public:
	qArray();
	~qArray();
	void insert(char m);  //将一个字符插入到队列尾部,插入失败返回1，否则返回0
	void delete_p(); //删除队列的队首元素，删除成功返回0，否则返回1
	int judge(); //判断一个队列是否为空，为空返回1，否则返回0
	void clean();  //清空队列,相当于析构函数的作用
	void print();   //测试和调试代码用
	void print_size();	//显示代码的正确，便于调试用。
};