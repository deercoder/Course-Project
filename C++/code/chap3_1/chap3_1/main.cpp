#include "Set.h"
#include <iostream>
using namespace std;

int main()
{
	SET a(10);
	cout << "初始化类的大小为10个，输入10个数据（以后即使超过也可以再次分配，动态扩展）" << endl;
	for (int i = 0; i < 10; i++) //这里看到即使越界了也可以成功插入，因为insert中实现重新分配
	{
		int getNumber = 0;
		cin >> getNumber;
		if (0 == a.insert(getNumber))
			cout << "插入元素已经存在，插入失败" << endl;
	}
	a.print();
	cout << "输入要插入元素" << endl;
	int getNumber2 = -1;
	cin >> getNumber2 ;
	if (0 == a.insert(getNumber2))    
		cout << "插入元素已经存在，插入失败" << endl;
	a.print();
	cout << "删除某个输入的元素，请输入一个数" << endl;
	int getNumber3 = 0;
	cin >> getNumber3;
	if (0 == a.remove(getNumber3))  
		cout << "没有找到所要删除的元素v，删除失败" << endl;   
	a.print();
	cout << "查找某个输入的元素，不存在就输出错误信息，请输入" << endl;
	int getNumber4 = 0;
	cin >> getNumber4;
	if (0 == a.has(getNumber4))
		cout << "没有找到元素v，查找失败" << endl;
	return 0;
}