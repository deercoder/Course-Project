#pragma warning(disable: 4996)
#include <iostream>
using namespace std;
const int MAX = 12;

class Clerk{
public:
	char name[MAX];	//姓名
	int ID;	//职工号
	float salary;	//工资
	int temp;	//用于区分不同员工
	char leader[MAX];	//定义这个员工的经理，负责发工资的人
	virtual void print(){}
};

class TempClerk:public Clerk{
public:
	TempClerk(char *str,int bnum,char *lead=NULL,float sal=0){ //临时工temp就初始化为1
		temp = 1;
		strcpy(name,str);	//姓名
		ID = bnum;			//职工号
		strcpy(leader,lead);	//直接主管
		salary = sal;	
	}
	void print(){ cout << "I am a Temporary Clerk!" << endl;}
	~TempClerk(){}
};
class PermenClerk:public Clerk{
public:
	PermenClerk(char *str,int bnum,char *lead=NULL,float sal=0){	//非临时工temp就初始化为0
		temp = 0;
		strcpy(name,str);	//姓名
		ID = bnum;			//职工号
		strcpy(leader,lead);
		salary = sal;
	}
	void print(){ cout << "I am a stuff!" << endl;}
	~PermenClerk(){}
};
class Manager:public PermenClerk{	
public:
	int Maneger_flag;	//定义的经理和老板的区别
	Manager(char *str,int bnum,char *lead=NULL,float sal=NULL)
		:PermenClerk(str,bnum,lead,sal){ //普通的经理，而不是boss
			Maneger_flag = 1;			
	}
	void print(){cout << "I am a manager!" << endl;	} //项目经理
	~Manager(){}
};

class Boss:public Manager{
public:
	Boss(char *str,int bnum,char *lead=NULL,float sal=NULL)
		:Manager(str,bnum,NULL,NULL){ //老板是没有主管和工资的
		Maneger_flag = 0;	//标志是老板
	}
	void print(){   cout << "I am a Boss!" << endl;		}//老板
	~Boss(){}
};

int main()
{
	PermenClerk   a("Tom",0001,"Jerry",1000);
	TempClerk	  b("Jack",0002,"Jerry",800);
	Manager		c("Jerry",0003,"Boss",3000);
//	Boss		d("Boss",0,0,0);
	Clerk *newClerk = &a;
	newClerk->print();
	newClerk = &b;
	newClerk->print();
	newClerk = &c;
	newClerk->print();
	cout << "I am a Boss!" << endl;
}