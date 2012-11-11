#include "que_Array.h"

qArray::qArray()
{
	front = rear = 0;
	size = 0;
}
qArray::~qArray()
{
}
void qArray::insert(char m)
{
	if (size < MAX-1) //队列没有满的时候
	{
		qArr[rear] = m;
		++rear;
		++size;
	}
	else
		cout << "队列已满，删除失败" << endl;

}
void qArray::delete_p()
{
	if (size == 0)
		cout << "队列为空，删除失败" << endl;
	else
	{
		qArr[front] = '\0';
		++front;
		--size;
	}
}
int qArray::judge()
{
	if (size == 0)
		return 1;
	else
		return 0;
}
void qArray::clean()
{
	for (int i = front; i < rear; i++) //将所有的元素置为空
	{
		qArr[i] = '\0';
	}
	front = rear = 0;
	size = 0;
}
void qArray::print()
{
	for (int i = front; i < rear; i++)
	{
		cout << qArr[i] << "\t" ;
	}
	cout << endl;
}
void qArray::print_size()
{
	cout << "size :" << size << endl;
}