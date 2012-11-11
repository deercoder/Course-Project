#include <iostream>
using namespace  std;

class LIST{
	struct NODE{
		int value;
		NODE *next;
		NODE(int a,NODE *p){
			value = a;
			next = p;
		}
	}*head;
public:
	LIST();
	LIST(const LIST &);
	int find(int value) const;//查找value，找到返回1，否则返回0
	int operator[](int k)const;	//取表的第k个元素
	virtual LIST operator+(const LIST&);	//表的合并运算
	virtual LIST operator+(int value);	//插入一个元素
	virtual LIST operator-(int value);	//删除一个元素
	virtual LIST &operator+=(const LIST&);	//表的合并运算
	virtual LIST &operator+=(int value);	//插入一个元素
	virtual LIST &operator-=(int value);	//删除一个元素
	virtual LIST &operator=(const LIST &);
	virtual ~LIST();
};
LIST::LIST():head(NULL){}
LIST::LIST(const LIST &b){
	NODE *tmp = b.head; 
	int count = 0;	//节点个数
	while(tmp != NULL){
		count++;
		tmp = tmp ->next ;
	}
	tmp = b.head;	//执行完后将临时指针置为初始位置，下面要使用
	this->head = new NODE(tmp->value,NULL);	//创建第一个节点
	for(int i = 1; i < count; i++){
		NODE *newNode = new NODE(tmp->value,head);	//逆序构建，刚好形成链表
		head = newNode;
		tmp = tmp ->next;	//形参的那个链表不断遍历，然后创建新的节点
	}
}

LIST::~LIST(){
	NODE *phead = this->head;
	while(phead !=NULL){
		NODE *tmp = phead->next;
		delete tmp;
		phead = tmp;
	}
}

int LIST::find(int value) const{
	NODE *tmp = this->head;
	int count = 0;
	while(tmp!=NULL){
		if(value == tmp->value)
			return 1;	//找到返回1
		tmp = tmp->next;
	}
	return 0;	//没有找到返回0
}

int LIST::operator[](int k)const{
	NODE *tmp = this->head;
	for(int i = 0; i < k; i++){
		tmp = tmp ->next;
	}
	return tmp->value;
}

LIST LIST::operator+(const LIST& b){
	NODE *tmp = b.head;
	while(tmp != NULL){
		NODE *newNode = new NODE(tmp->value,head);	//待拷贝的链创建相同值的节点
		head = newNode;
		tmp = tmp ->next ;
	}
	return *this;
}

LIST LIST::operator+(int value)
{
	NODE *newNode = new NODE(value,NULL);//创建一个节点域指针为空的节点，放在最后
	NODE *tmp = this->head;
	while(tmp!=NULL){
		tmp = tmp ->next;
	}
	tmp = newNode;
	return *this;
}
LIST LIST::operator-(int value){
	if(find(value)==0)
		return  *this;	//删除失败，没有找到该元素
	else{
		NODE *tmp = this->head;
		while(tmp->value != value)
			tmp = tmp->next;
		NODE *freep = tmp->next;
		delete(tmp);	//删除那个单元
		tmp = freep;	//指针指向下下个
		return *this;
	}
}
LIST &LIST::operator+=(const LIST&b){
	*this = *this + b;
	return *this;
}

LIST &LIST::operator+=(int value){	//插入一个元素
	*this = *this + value;
	return *this;
}
LIST &LIST::operator-=(int value){	//删除一个元素
	*this = *this - value;
	return *this;
}
LIST &LIST::operator=(const LIST &b){	//赋值运算符，需要先清空原来的
	NODE *tmp = this->head->next;
	while(tmp !=NULL){
		NODE *freep = tmp;
		delete freep;
		tmp = tmp->next;
	}
	NODE *flagb = b.head;
	while(flagb!=NULL){
		NODE *newNode = new NODE(flagb->value,this->head);	//待拷贝的链创建相同值的节点
		this->head = newNode;
		flagb = flagb ->next ;
	}
	return *this;
}

int main(){
	return 0;
}



