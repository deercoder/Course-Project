#include <iostream>
using namespace std;
class SEQUENCE;
class TREE{		//表示一个节点,包含值和指针
	int item;
	TREE *left,*right;
	friend SEQUENCE;
public:
	TREE(int value,TREE *l,TREE *r);	//构造一个树
	int getNode();			//返回节点数
	int getNode(int *items);
};

TREE::TREE(int value,TREE *l,TREE *r){
	item = value;
	left = l;
	right = r;
}

int TREE::getNode(){	
	int l =0, r = 0;
	if(left != NULL)
		l = left-> getNode();
	if(right != NULL)
		r = right->getNode();
	return l+r+1;
}
int TREE::getNode(int *items){	//返回节点数,下面需要递归调用
	int    n=0; 
	if(left)   n=left->getNode(items); 
	items[n++] = TREE::item; 
	if(right)   n= n + right->getNode(items); 
	return   n;
} 

class SEQUENCE{
	int *items;
	int size;
public:
	SEQUENCE(TREE &);
	void print();	//为了便于输出而作了个测试代码函数
};

SEQUENCE::SEQUENCE(TREE &b)
{
	int   m; 
	size=b.getNode();
	items=new int[size];	//动态创建一个数组,插入数值
	b.getNode(items);
}
void SEQUENCE::print(){
	for(int i = 0; i < size; i++)
		cout << items[i] << " ";
}
int main()
{
	TREE a(5,NULL,NULL);
	TREE b(0,NULL,NULL);
	TREE c(1,&b,&a);	//构造两个子节点的树
	SEQUENCE seq(c);
	seq.print();
	return 0;
}