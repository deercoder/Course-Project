#include <string>
#include <iostream>
using namespace std;

class STACK{
	const int max; //栈能够存放的最大元素个数
	int top;		//栈顶元素的位置,指向元素的上面一个单元
	char *stk;		//栈顶指针
public:
	STACK(int max);
	~STACK();
	int push(char v);	//将v压栈，成功时返回1，否则返回0
	int pop(char &v);	//弹出栈顶元素，成功返回1，否则返回0
};