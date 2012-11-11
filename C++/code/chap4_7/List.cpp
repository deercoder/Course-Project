#include "List.h"
#include <iostream>
#include <cstring>
using namespace std;

Student::Student():English(0.0f),Math(0.0f),Physics(0.0f),Chemistry(0.0f)
{
	name[0] = '\0';
	password[0] = '\0';
}
Student::Student(char *nam,char *psw):English(0.0f),Math(0.0f),Physics(0.0f),Chemistry(0.0f)
{
	int length = sizeof(nam) / sizeof(char);
	int length2 = sizeof(psw) / sizeof(char);
	if (length < MAX)
	{
		strcpy(name,nam);
	}
	else
	{
		cout << "输入太多的字符，初始化姓名失败" << endl;
	}
	if (length2 < MAX)
	{
		strcpy(password,psw);
	}
	else
	{
		cout << "输入太多的字符，初始化密码失败" << endl;
	}
}
Student::Student(char *nam, char *psw, float Eng, float Math, float phy, float chem)
{
	int length = sizeof(nam) / sizeof(char);
	int length2 = sizeof(psw) / sizeof(char);
	if (length < MAX)
	{
		strcpy(name,nam);
	}
	else
	{
		cout << "输入太多的字符，初始化姓名失败" << endl;
	}
	if (length2 < MAX)
	{
		strcpy(password,psw);
	}
	else
	{
		cout << "输入太多的字符，初始化密码失败" << endl;
	}
	this->setEnglish(Eng);
	this->setMath(Math);
	this->setPhysics(phy);
	this->setChemistry(chem);
	cout << "创建成功!" <<endl;
}

Student::~Student() //没有动态创建对象，所以不需要
{
}
void Student::setEnglish(float Englishscore)
{
	English = Englishscore;
}
void Student::setMath(float Mathscore)
{
	Math = Mathscore;
}
void Student::setPhysics(float Physicscore)
{
	Physics = Physicscore;
}
void Student::setChemistry(float Chemistryscore)
{
	Chemistry = Chemistryscore;
}
float Student::getEnglish()
{
	return English;
}
float Student::getMath()
{
	return Math;
}
float Student::getPhysics()
{
	return Physics;
}
float Student::getChemistry()
{
	return Chemistry;
}
void Student::changeName(char *newname)
{
	int length = sizeof(newname) / sizeof(char);
	if (length < MAX)
	{
		strcpy(name,newname);
	}
	else
		cout << "更改姓名失败，输入太多的字符" << endl;
}
void Student::changePassword(char *newpassword)    //更改密码
{
	int length = sizeof(newpassword) / sizeof(char);
	if (length < MAX)
	{
		strcpy(password,newpassword);
	}
	else
		cout << "更改密码失败，输入太多的字符" << endl;
}
int Student::enterPsw(char *input)
{
	if (strcmp(name,input)== 0)
		return 1;
	else
		return 0;
}
void Student::print()
{
	cout << "姓名:" << name <<" \t" << "密码:" << password << endl;
	cout << "物理:" << Physics << " \t" << "数学:" << Math << endl;
	cout << "英语:" << English << " \t" << "化学:" << Chemistry << endl;
}