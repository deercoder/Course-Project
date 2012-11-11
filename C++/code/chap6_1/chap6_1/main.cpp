#include <iostream>
#include <math.h>
using namespace std;

const double PI = 3.14159;

class LOCATION
{
public:
	int x,y;
	LOCATION(int x1,int y1):x(x1),y(y1) { }
	void move(int x,int y);		
};

void LOCATION::move(int x1,int y1) //形参仅仅表示移动距离 
{
	x += x1;
	y += y1;
}

class POINT:public LOCATION
{
public:
	POINT(int x1,int y1):LOCATION(x1,y1){ }
	void move(int x1,int y1) { 
		LOCATION::move(x1,y1);
		cout << "移动后，点的坐标为:x= " << this->x << " \t y= " << this->y<< endl; 
	}
	void draw(){	
		cout << "已绘制一个点!\t" << "坐标为:x= " 
			<< this->x << " \t y= " << this->y<< endl;
	}	
};

class CIRCLE:public LOCATION
{
	int radius;    //圆要特殊些，有半径 
public:
	CIRCLE(int x,int y,int radius):LOCATION(x,y){ CIRCLE::radius = radius; }
	void move(int x,int y){
		LOCATION::move(x,y);
		cout << "移动后圆心的坐标为:x= " << this->x << " \t y= " << this->y<< endl;
	}
	void draw();	
};

void CIRCLE::draw()
{
	cout << "已绘制一个圆!\t" <<"圆心坐标为:x = " 
		<< this->x <<" \ty = "<< this->y 
		<< " \t半径为：" << this->radius << endl;
}

void main()
{
	POINT a(4,9);
	a.draw();
	cout << "移动(1,2)距离之后........" << endl;
	a.move(1,2);
	a.draw();
	cout << endl;
	CIRCLE b(4,3,3);
	b.draw();
	cout << "移动(4,9)距离之后........" << endl;
	b.move(4,9);
	b.draw();
}