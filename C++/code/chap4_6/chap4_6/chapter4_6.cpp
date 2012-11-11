#include <iostream>
#include <string>
using namespace std;
const int MAX = 10;

class Item
{
public:
	void print();
	int insert(string s);
	int search(string s);
	int delete_item(int i);
	Item():stored(0){}
private:
	string a[MAX];  //利用数组存放
	int stored ;	//标志已存放的下标
};

int Item::insert(string s)
{
	if (stored== MAX-1)
		return 0;	//数组已满，插入失败
	else{
		a[stored] = s;
		stored++;
		return 1;
	}
}
int Item::search(string s)
{
	for(int i = 0; i <= stored; i++)
	{
		if (s == a[i])
			return 1;  //找到
	}
	return 0;	//没有找到该string
}

int Item::delete_item(int i) //删除指定下标的item
{
	if(i > stored)
		return 0;	//没有这么大的下标元素，删除失败
	else{
		for(int j = i; j <= stored; j++){
			a[j] = a[j+1];
		}
		return 1;
	}
}
void Item::print()
{
	for(int i = 0; i <= stored; i++)
		cout << a[i] << endl;
}
void main()
{
	Item a;
	a.insert("Hello,world");
	a.insert("Me!");
	a.insert("I Love C++");
	a.insert("just for test");
	a.print();
	if(a.search("sjife"))
		cout << "find" << endl;
	if(!a.search("Me!"))
		cout << "not found!" << endl;
	if(a.delete_item(2)){
		cout << "after deleting the item 3" << endl;
		a.print();
	}
}




