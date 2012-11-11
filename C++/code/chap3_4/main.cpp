#include "que_Array.h"

int main()
{
	qArray a;
	cout << "请输入你要插入个数" << endl;
	int getNumber = 0;
	cin >> getNumber;
	cout << "输入各个字符" << endl;
	for (int i = 0; i < getNumber; i++)
	{
		char getChar = 0;
		cin >> getChar;
		a.insert(getChar);
	}
	cout << "显示各个元素的内容及队列大小如下:" << endl;
	a.print();
	a.print_size();
	a.delete_p();

	a.insert('m');
	a.insert('n');

	cout << "删除队首元素之后，剩余的各个元素如下：" << endl;
	a.print();
	a.print_size();

	a.clean();
	cout << "清空队列后队列的元素" << endl;
	a.print();
	a.print_size();
	return 0;
}