#include "stack.h"

STACK::STACK(int max):max(max)
{
	stk = (char *)malloc(max * sizeof(char));
	top = 0;
}
STACK::~STACK()
{
	if(stk)
		free(stk);
}
int STACK::push(char v)
{
	if ((top+1 )==max)
	{
		return 0;
	}
	else
	{
		stk[top] = v;
		++top;
		return 1;
	}
}
int STACK::pop(char &v)
{
	if (top == 0)
		return 0;
	else
	{
		v = stk[top-1];
		--top;
		return 1;
	}
}