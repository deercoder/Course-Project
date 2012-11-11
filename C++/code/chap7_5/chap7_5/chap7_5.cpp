#include <iostream>
using namespace std;

class List;
class Abstrcat{
	int size;	//定义线性表容量
	int number;	//定义线性表当前元素个数
public:
	virtual int insert(int pinsert)=0;		//插入成功成功返回1，否则返回0
	virtual int delete_p(int pdelete)=0;	//删除成功成功返回1，否则返回0
	virtual int search(int psearch)=0;		//查找到元素返回1，否则返回0
	friend class List;	//定义派生类为它的友元，注意就可以访问私有成员
};

class List:public Abstrcat{
	int *pList;
public:
	List(int psize){
		pList = new int [psize];
		Abstrcat::size = psize;
		Abstrcat::number = 0;
	}
	~List(){
		if(!pList)
			return ;
		delete pList; 
	}
	int insert(int pinsert){
		if(Abstrcat::number==Abstrcat::size)	//数组已满，插入失败
			return 0;
		else{
			pList[Abstrcat::number++] = pinsert;
			return 1;
		}
	}
	int delete_p(int pdelete){
		int mark = -1;	//标志删除元素所在位置
		for(int i = 0; i < Abstrcat::number;i++){
			if (pdelete == pList[i]){
				mark = i;
			}
		}
		if(-1 == mark)
			return 0; //删除失败，没有找到该元素
		else{
			for (int j = mark; j < Abstrcat::number-1;j++){
				pList[j] = pList[j+1];
			}
			Abstrcat::number--;
			return 1;
		}
		
	}
	int search(int psearch){
		for(int i = 0; i < Abstrcat::number;i++){
			if (psearch == pList[i]){
				return 1;	//找到该元素
			}
		}
		return 0;
	}
	void print(){
		for(int i = 0; i < Abstrcat::number;i++){
			cout << pList[i] << " " ;
		}
		cout << endl;
	}
};

int main()
{
	List list(10);
	for (int i = 0; i < 10; i++)
		list.insert(i);			//通过insert函数来创建各个元素
	cout << "创建后各个节点的信息如下：" << endl;
	list.print();
	if (1==list.search(5))
		cout << "找到元素5！" << endl;
	else
		cout << "没有找到元素5！\n" << endl;
	cout << "删除元素后......" << endl;
	if (0==list.delete_p(10))
		cout << "进行删除操作......删除失败，没有元素为10的节点!" << endl;
	list.delete_p(5);
	cout << "删除元素5后......." << endl;
	list.print();
}