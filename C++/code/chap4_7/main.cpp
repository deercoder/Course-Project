#pragma warning(disable C4996)

#include <iostream>
#include "List.h"
#include <cstring>
using namespace std;

int main()
{
	cout << "---------学生成绩记录管理系统:-------------" << endl;
	cout << "\t\t 1.创建一个学生记录" << endl;
	cout << "\t\t 2.查询学生成绩" << endl;
	cout << "\t\t 3.修改密码" << endl;
	cout << "\t\t 4.修改成绩" << endl;
	cout << "\t\t 5.退出" << endl;
	cout << "请输入你的选项：1,2,3,4,5输入后点击回车" << endl;
	int getChoice = 0;
	scanf("%d",&getChoice);
	char NAME[MAX];char PASSWORD[MAX];
	float ENG;float MATH; float PHYS;float CHEM;
	if(getChoice == 1){
		cout << "请输入姓名:";  cin >> NAME;
		cout << "请输入密码:";  cin >>PASSWORD;
		cout << "请输入英语成绩:";  cin >> ENG;
		cout << "请输入数学成绩:";  cin >> MATH;
		cout << "请输入物理成绩:"; cin >> PHYS;
		cout << "请输入化学成绩:";  cin >> CHEM;
	}
	Student a(NAME, PASSWORD, ENG, MATH, PHYS, CHEM);
	cout << "please enter your password:" << endl;
	char Pssword[MAX];
	cin >> Pssword;
	if (!a.enterPsw(Pssword))
		a.print();
	return 0;
}