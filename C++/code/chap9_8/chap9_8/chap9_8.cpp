#include <iostream>
using namespace std;
const int MAX = 23;

class SET{
	int *elem;			//存放集合元素的动态内存
	int count,total;	//目前元素个数及最大元素个数
public:
	SET(int total);
	SET(const SET&);
	int find(int val) const;
	int full() const;
	int empty() const;
	virtual SET operator +(const SET&);
	virtual SET operator -(const SET &)const;        //集合的差集
	virtual SET operator *(const SET &)const;         //集合的交集 
	virtual SET &operator <<(int value);             //增加一个元素 
	virtual SET &operator >>(int value);             //删除一个元素 
	virtual SET &operator +=(const SET &);         //集合的并集 
	virtual SET &operator -=(const SET &);           //集合的差集 
	virtual SET &operator *=(const SET &);         //集合的交集 
	virtual SET &operator  <<=(int value);            //增加一个元素 
	virtual SET &operator  >>=(int value);            //删除一个元素 
	virtual SET &operator   =(const   SET   &); 
	virtual ~SET(); 
	void print();
}; 
SET::SET(int total){
	this->total = total;
	elem = new int[total];
	count = 0;
}
SET::SET(const SET& b){
	this->total = b.total;//初始化容量
	count = b.count;
	elem = new int[total]; //分配内存空间
	for(int i = 0; i < count; i++){
		elem[i] = b.elem[i];	//赋值
	}
}
SET::~SET(){
	if(elem){
		delete elem;//释放内存快
	}
}
int SET::find(int val) const{
	for(int i=0; i < count; i++){
		if(val == elem[i])
			return 1;	//找到
	}
	return 0;	//未找到
}
int SET::full() const{
	return (int)(count == total);
}
int SET::empty() const{
	return (int)(count==0);
}

SET SET::operator +(const SET& b){
	for(int i =0; i <b.count; i++){
		if(find(b.elem[i])==0){ //找到该元素，进行删除
			 elem[count++] = b.elem[i];	//从后面开始赋值添加
			}
		}
	return *this;
}
SET SET::operator -(const SET &b)const{      //集合的差集
	for(int i =0; i <b.count; i++){
		if(find(b.elem[i])){//找到该元素，进行删除
			int j;
			for ( j= 0; elem[j]!= b.elem[i]; j++){}
			for(int k = j ; j < this->count-1; j++){
					elem[k] = elem[k++];	//删除后前移一位
				}
			}
		}
	return *this;
}
SET   SET::operator *(const SET & b)const{         //集合的交集
	int a[MAX],count =0;
	for(int i = 0; i < this->count; i++)
	{
		for (int j = 0; j < b.count; j++)
		{
			if(elem[i]==b.elem[j])
				a[count++]=elem[i];	//保存集合相同的元素以备后用
		}
	}
	SET *newSet = new SET(MAX);
	for (int i = 0; i <count; i++)
	{
		newSet->elem[i] = a[i];
	}
	return *this;
}
SET  &SET::operator  <<(int value){             //增加一个元素 
	if(find(value) == 0)
		this->elem[count++] = value;
	return *this;
}
SET   &SET::operator >>(int value){	//删除一个元素
	int ptest = -1;	//标志位，删除的value的位置
	for(int i = 0; i < this->count; i++)
	{
		if(elem[i]==value){
			ptest = i; break;
		}		
	}
	for (int i = ptest; i < count; i++)
	{
		this->elem[i] = elem[i++];	//移动各个元素
	}
	count--;
	return *this;
}
SET  &SET::operator +=(const SET &b){         //集合的并集
	for(int i = 0; i<b.count; i++){
		if(find(b.elem[i])==0){     //不在本集合类中，直接添加
			elem[count++] = b.elem[i];
		}
	}
	return *this;
}

SET   &SET::operator -=(const SET &b){          //集合的差集 
	*this = *this - b;		//调用已经写好的差集函数
	return *this;
}
SET   &SET::operator *=(const SET &b){        //集合的交集 
	*this = *this * b;
	return *this;	//同上
}
SET   &SET::operator  <<=(int value){            //增加一个元素 
	*this = *this << value;
	return *this;
}
SET   &SET::operator  >>=(int value){            //删除一个元素 
	*this = *this >> value;
	return *this;
}
SET &SET::operator =(const  SET  &b){
	for(int i = 0; i < count; i++){
		elem[i] = 0;
	}
	for(int j = 0; j < b.count; j++){
		elem[j] = b.elem[j];
	}
	return *this;
}

void SET::print(){
	for (int i = 0; i < count; i++)
	{
		cout << elem[i] << " ";
	}
	cout << endl;
}
int main()	//测试代码
{	
	SET a(10);	//构造一个SET集合
	for(int i = 0; i < 5; i++)
		a << i;		//增加一个元素
	a.print();
	a>>4;	//删除值为4的节点
	a.print();
	if(a.find(2))	//验证find函数
		cout << "found!" << endl;
	if(a.full())	//验证full函数
		cout << "full!" << endl;
	if(a.empty())	//验证empty函数
		cout << "empty!" << endl;
	SET b(10);
	for(int i = 0; i < 6; i++)
		b << i;		//增加元素，其实就是初始化这个集合,为其添加元素
	const SET c(b);	//调用拷贝构造函数
	b = a + c;
	b.print();
	b = a - c;
	b.print();
	b = a * c;
	b.print();
	b += c;
	b.print();
	b -= c;
	b.print();
	b *= c;
	b.print();

	return 0;
}




