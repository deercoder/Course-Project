#include "queue.h"

int main()
{
	Queue qList;
	for (int i = 0; i < 5; i++)
	{
		char getChar = NULL;
		cin >> getChar;
		qList.insert(getChar);
	}
	qList.print();
	return 0;
}