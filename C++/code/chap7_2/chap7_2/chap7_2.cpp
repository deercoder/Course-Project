#pragma warning(disable:4996) 

#include <iostream>
using namespace std;
const int MAX = 25;

class Base{
public:
	char name[MAX];
	int age;
	char social_Num[MAX];
	virtual void print(){}
	virtual void set_next(Base *p){}
	virtual Base *get_next(){ return NULL;}
};

class Student:public Base{
	char grad[MAX];
	double average_score;
public:
	Base *next;
	Student(char *name,int age1,char *social,char *grad,double average):next(NULL){
		strcpy(this->name,name);
		this->age = age1;
		strcpy(this->social_Num,social);
		strcpy(this->grad,grad);
		this->average_score = average;
	}
	void set_next(Base *p){		next = p;}
	Base *get_next(){	return this->next; }
	void print(){
		cout << "姓名: "<<this->name << "\t年龄：" << this->age << "\n社会保险号:"
			<< this->social_Num << "\t年级:" << this->grad << "\t\t平均成绩:" << this->average_score << endl;
	}
};

class Clerk:public Base{
	double wage;
public:
	Base *next;
	Clerk(char *name,int age1,char *social,double wage1):next(NULL){
		strcpy(this->name,name);
		this->age = age1;
		strcpy(this->social_Num,social);
		this->wage = wage1;
	}
	void set_next(Base *p){		next = p;}
	Base *get_next(){	return this->next;}
	void print(){
		cout << "姓名: "<<this->name << "\t年龄：" << this->age << "\n社会保险号:"
			<< this->social_Num << "\t工资:" << this->wage  << endl;
	}
};

class Professer:public Base{
	double wage;
	char major[MAX];
public:
	Base *next;
	Professer(char *name,int age1,char *social,double wage1,char *major1):next(NULL){
		strcpy(this->name,name);
		this->age = age1;
		strcpy(this->social_Num,social);
		this->wage = wage1;
		strcpy(this->major,major1);
	}
	void set_next(Base *p){		next = p;}
	Base *get_next(){	return this->next;}
	void print(){
		cout << "姓名: "<<this->name << "\t年龄：" << this->age << "\n社会保险号:"
			<< this->social_Num << "\t工资:" << this->wage << "\t研究方向:" << this->major << endl;
	}
};

class List{//逆序建立链表
	Base *head;
public:
	List(Base *p){
		head = p;
		p->set_next(NULL);	//将插入节点域的next赋值为NULL
	}
	void insert(Base *p){
		p->set_next(head);	//新的节点插入前面,建立两个节点之间的联系，即使不是同一个类，也可以利用指针
		head = p;		//重置初始表头指针
	}
	void delete_list(Base *p){ 
		Base *tmp = head;
		if(head == p){		//如果删除的恰好是头指针(开始的时候没有注意此特殊情况而出错)
			head = p->get_next();
		}
		else{
			while(tmp->get_next()!= p){
				tmp = tmp->get_next();
			}
			Base *tmp2 = tmp->get_next()->get_next();
			delete tmp->get_next();		//删除那个中间的节点
			tmp->set_next(tmp2);
		}
	}
	void print(){
		Base *ptmp = head;
		while(ptmp->get_next()!=NULL){
			ptmp->print();
			ptmp = ptmp->get_next();
		}
		ptmp->print();	//输出最后一个，因为后继节点为NULL，所以特殊处理
	}
};
//可以实现的是输出，而且是满足虚函数的特性，这里针对的是next指针和print虚函数，从结果可以看到，是根据虚指针
//实际指向的单元的类型来输出的。next指针都是Base *类型的，不过输出的不是Base的信息（那样就没有输出了）,
//而是实际指向的类型，比如这里的是Clerk。
int main()
{
	Student student("jack",20,"132343","g1",87.8);
	Clerk clerk("Clerk",34,"23434",1000);
	Professer professer("Professor",50,"234356",10000,"computer");
	List aList(&student);
	cout << "初始化，通过插入函数来构造链表.......\n" << endl;
	aList.insert(&clerk);
	aList.insert(&professer);
	aList.print();
	cout << "\n删除教授这个节点信息后........"<< endl;
	aList.delete_list(&professer);
	aList.print();
	cout << "\n重新插入教授信息节点，然后删除学生节点...." << endl;
	aList.insert(&professer);
	aList.delete_list(&student);
	aList.print();
	return 0;
}

