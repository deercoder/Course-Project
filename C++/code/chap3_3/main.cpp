#include "queue.h"

int main()
{
	cout << "-----------用链表实现字符队列程序-----------\n" << endl;
	Queue qList;
	int getNum;
	cout <<"请输入要插入数据的个数" << endl;
	cin >> getNum;
	for (int i = 0; i < getNum; i++) //验证插入操作的正确性
	{
		char getChar = NULL;
		cin >> getChar;
		qList.insert(getChar);
	}
	qList.print();//显示插入后的结果
	cout << ">>>>>>>>>>>删除队首元素后>>>>>>>>>>" << endl;
	qList.delete_p();  //验证删除操作，并显示结果1
	qList.print();
	cout << "--------判断队列是否为空，若为空就输出信息，否则不输出-----" << endl;
	if (qList.judge())
		cout << "队列为空" << endl;
 	qList.clean();  //clean函数起到了析构函数的效果
	return 0;
}