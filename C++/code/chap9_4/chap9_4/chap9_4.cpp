#include <string.h>
#include <iostream>
using namespace  std;

class STRING{
	char *str;
public:
	STRING(char *s=0);
	STRING(const STRING &);
	virtual int strlen(void) const;
	virtual int strcmp(const STRING &) const;
	virtual STRING &operator+(const STRING &);
	virtual STRING &operator=(const STRING &);
	virtual STRING &operator+=(const STRING &);
	virtual operator const char *(void) const;
	virtual ~STRING();
};

STRING::STRING(char *s/*=0*/){
	str = new char[::strlen(s)+1];
	::strcpy(str,s);
}
STRING::~STRING(){
	delete str;
}
int STRING::strlen(void) const{
	return ::strlen(this->str); //采用字符串的通用表示，不含null
}
int STRING::strcmp(const STRING &b) const{
	return ::strcmp(this->str,b.str);
}
STRING &STRING::operator+(const STRING &b){
	::strcat(this->str,b.str);
	return *this;
}
STRING &STRING::operator=(const STRING &b){
	this->str = b.str;
	return *this;
}
STRING &STRING::operator+=(const STRING &b){
	::strcat(this->str,b.str);
	return *this;
}
STRING::operator const char *(void) const{
	return this->str;
}
int main()
{
	STRING s("Hello,world");
	STRING e("I Love C++");
	cout << "STRING:" << s << "\t strlen:" << s.strlen()<< endl;
	cout << "STRING:" << e << "\t strlen:" << e.strlen()<< endl;
	if(!e.strcmp("I Love C++")) //和e("I Love C++")相比相等
		cout << "The String \"I Love C++ \"Equals !" << endl;
	else
		cout << "The String \"I Love C++ \"are not Equal to the string!" << endl;
	if(!s.strcmp("I Love C++")) //和s("Hello,world")相比不相等
		cout << "The String \"I Love C++ \"Equals !" << endl;
	STRING test("just for test");
	s = test;
	cout << "after operator =...............s is " << s << endl; 
	s = s + e;
	cout << "after operator+................s is " << s << endl;
	s += e;
	cout << "after operator+=...............s is " << s << endl;
	const char *constString = s;  //验证了强制类型转换的函数virtual operator const char *(void) const;
	cout << constString << endl;
	return 0;

}