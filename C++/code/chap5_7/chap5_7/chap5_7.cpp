#include <iostream>
using namespace std;

class TREE{ 
	int   item; 
	TREE   *left, *right;	//左右子树
public: 
	TREE(int *a, int b);
	friend void print(TREE *p);
}; 
void print(TREE *p);		//测试函数，实现输出来观察是否正确
TREE::TREE(int *a, int b){	//递归创建二叉树
	int   x = b / 2;
	item = a[x]; 
	if(x > 1)
		left = new TREE(a,x-1);
	else
		left = NULL;
	if(b > x + 1)
		right = new TREE(a+x+1,b-x-1);
	else
		right = NULL;
} 
void print(TREE *p){
	cout << p->item << " ";
	if( p->left!= NULL)
		print(p->left);
	if( p->right!=NULL)
		print(p->right);
}
int main(){ 
	int  s[]={1,2,3,4,5,6,7,8,9,10}; 
	TREE t(s, 10);
	print(&t);
	return 0;
} 
