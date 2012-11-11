#include "stack.h"
const int MAXNUM = 15;

class REVERSE:STACK{
public:
	REVERSE(char *str); //½«×Ö·û´®Ñ¹Õ»
	~REVERSE();			//°´ÄæÐòÊä³ö×Ö·û´®
};
REVERSE::REVERSE(char *str):STACK(MAXNUM)
{
	int length = strlen(str);
	for(int i = 0; i < length; i++){
		this->push(str[i]);	
	}
}
REVERSE::~REVERSE(){
	char v = NULL;
	while(this->pop(v)!=0)
		cout << v ;
	cout << endl;
}
void main()
{
	REVERSE a("abcdefghij");
	REVERSE b("abcdefghijk");
}