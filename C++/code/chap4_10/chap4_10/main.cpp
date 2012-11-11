#include "stack.h"

int main()
{
	STACK a(10);
	char p = 'b';
	char &v = p;
	a.push('a');
	a.pop(v);
	cout << v << endl;
	a.push('b');
	a.pop(v);
	cout << v << endl;
	a.push('c');
	a.pop(v);
	cout << v << endl;
	return 0;
}