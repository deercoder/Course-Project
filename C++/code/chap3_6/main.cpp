#include "list.h"

int main()
{
	INTLIST list(3); //初始化10个元素，如果后面输入大于的话会自动扩展
	cout << "--------请输入数据的个数!-------" << endl;
	int getNum = 0;
	cin >> getNum;
	cout << "请输入" << getNum << "个整型数据" << endl;
	for (int i = 0; i < getNum; i++)
	{
		int getInt = 0;
		cin >> getInt ;
		list.insert(getInt);
	}
	list.print();
			//下面验证删除模块的功能
	cout << "----------输入你要删除的元素-------" << endl;
	int deleteNum=0;
	cin >> deleteNum ;
	if(list.remove(deleteNum))
		cout << "删除成功!" << endl;
	else
		cout << "删除失败!" << endl;
	list.print();
			//下面验证查找模块的功能
	cout <<"---------输入要你要查找的元素--------"<< endl;
	int findNum = 0;
	cin >> findNum;
	if (list.find(findNum))
		cout << "找到要查找的元素!" << endl;
	else
		cout << "没有找到要查找的元素!" << endl;
				//下面验证查找功能模块
	cout << "---------输入你要定位的表中数据的位置---------" << endl;
	int location = 0;
	cin >> location ;
	cout << "该位置处对应的数据值为:" << list.get(location) << endl;

	return 0;
}