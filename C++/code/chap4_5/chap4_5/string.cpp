#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;

class STRING{
	char *str;
public:
	int strlen() const;
	int strcmp(const STRING&) const;
	STRING &strcpy(const STRING &);
	STRING &strcat(const STRING &);
	STRING(char *);
	~STRING();
};

int STRING::strlen() const
{
	return ::strlen(str);
}

int STRING::strcmp(const STRING& bstr) const
{
	return ::strcmp(this->str,bstr.str);
}
STRING &STRING::strcpy(const STRING &bstr)
{
	::strcpy(this->str,bstr.str);
	return *this;
}

STRING &STRING::strcat(const STRING &bstr)
{
	::strcat(this->str,bstr.str);
	return *this;
}

STRING::STRING(char *strstr)
{
	str = new char[::strlen(strstr)+1];
	::strcpy(str,strstr);
}

STRING::~STRING()
{
	delete str;
}

void main()
{
	STRING s1("I like apple");
	STRING s2("and peat");
	STRING s3("and orange");
	cout << "Length of s1=" << s1.strlen()<< "\n";
	s1.strcat(s2).strcat(s3);
	cout << "Length of s1=" << s1.strlen() << "\n";
	s3.strcpy(s2).strcpy(s1);
	cout << "Length of s3=" << s3.strlen() << "\n";
}