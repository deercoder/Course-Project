#include <iostream>
using namespace std;

class QUEUE{
	struct NODE{
		int value;
		NODE *next;
		NODE(int a,NODE *p){
			value = a;
			next = p;
		}
	}*head;
public:
	QUEUE();
	QUEUE(const QUEUE &);
	virtual operator int() const;	//返回队列元素个数
	virtual QUEUE &operator>>(const int &);	//从队列取一个元素
	virtual QUEUE &operator<<(int);		//往队列中加入一个元素
	virtual ~QUEUE();
	void print();
};

QUEUE::QUEUE(){
	head = 0;
}
QUEUE::QUEUE(const QUEUE &b){
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

QUEUE::~QUEUE(){
	NODE *phead = this->head;
	while(phead !=NULL){
		NODE *tmp = phead->next;
		delete tmp;
		phead = tmp;
	}
}

QUEUE::operator int() const{	//返回队列元素个数
	NODE *tmp = this->head; 
	int count = 0;	//节点个数
	while(tmp != NULL){
		count++;
		tmp = tmp ->next ;
	}
	return count;	
}
QUEUE &QUEUE::operator>>(const int &b){	//从队列取一个元素
	NODE *tmp = this->head;
	NODE *ptmp = NULL;
	while(tmp != NULL){
		ptmp = tmp;
		tmp = tmp->next;
	}
	*(int *)(&b) = tmp->value;	//由于是逆序创建的，所以需要遍历得到最后一个，这样才是先进先出策略
	delete tmp;
	ptmp->next = NULL;//取走一个元素后删除并封口。
	return *this;
}
QUEUE &QUEUE::operator<<(int b){		//往队列中加入一个元素
	NODE *newNode = new NODE(b,head);	//创建一个新节点，并放在队列中
	head = newNode;	//更改表头
	return *this;
}

void QUEUE::print(){
	NODE *tmp = head;
	while(tmp != NULL){
		cout << tmp->value << " ";
		tmp = tmp ->next;
	}
	cout << endl;
}
int main()
{
	QUEUE que;
	for(int i = 0; i < 5; i++)
		que << i;	//加入数据
	que.print();
	int num = que;	//强制类型转换
	cout << num << endl;
	return 0;
}



