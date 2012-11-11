#include <iostream>
#include <cmath>
using namespace std;
class CirTrangle;

class Point{
public:
	double x;
	double y;
	Point(double x1,double y1):x(x1),y(y1){}
	~Point(){}
};

class Circle{
	double radius;
	Point circlePoint;
public:
	friend class CirTrangle;
	Circle(double r,double cx,double cy):radius(r),circlePoint(cx,cy){}
	~Circle(){}
	virtual void draw() {cout << "a Circle with radius("<<radius<<")"<<" is drawn!"<< endl;
		cout << "the circle point is "<<circlePoint.x<<"," << circlePoint.y << endl;}
};


class Trangle
{
	Point x,y,z;
public:
	friend class CirTrangle;
	Trangle(double x1,double y1,double x2,double y2,double x3,double y3):x(x1,y1),y(x2,y2),z(x3,y3){}
	~Trangle(){}
	virtual void draw() {
		cout << "A Trangle is drawn by three points"<< endl;
		cout << "Point1 (" << x.x <<","<<y.y << ")."<< endl;
		cout << "Point2 (" << y.x <<","<<y.y << ")."<< endl;
		cout << "Point3 (" << z.x <<","<<z.y << ")."<< endl;
	}
	double distance(Point x,Point y){
		return pow((x.x-y.x),2)+pow((x.y-y.y),2); //距离的平方和
	}
};
class CirTrangle:public Circle,public Trangle
{
public:
	CirTrangle(double x,double y,double radius,double mx1,double mx2,double my1,double my2,double mz1,double mz2):
	  Circle(radius,x,y),Trangle(mx1,mx2,my1,my2,mz1,mz2){}
	virtual void draw()
	{
		if(juege())
			cout << "OK,This is a Trangle in a Circle!" << endl;
		else
			cout << "Sorry,Although it inherited from Circle and Trangle,\n"
				<<"It is not a Trangle in a Circle" << endl;
	}
	bool juege(){
		if (CirTrangle::distance(CirTrangle::Trangle::x,CirTrangle::Circle::circlePoint)!= CirTrangle::Circle::radius)
			return false;
		else if(CirTrangle::distance(CirTrangle::Trangle::y,CirTrangle::Circle::circlePoint)!= CirTrangle::Circle::radius)
			return false;
		else if(CirTrangle::distance(CirTrangle::Trangle::z,CirTrangle::Circle::circlePoint)!= CirTrangle::Circle::radius)
			return false;
		else 
			return true;
	}
};

int main()
{
	Circle a(1,2,3);
	a.draw();
	Trangle b(2,3,4,5,6,7);
	b.draw();
	CirTrangle c(1,1,1,2,3,4,5,6,7);
	c.draw();
	CirTrangle d(0,0,1,-1,0,0,1,1,0);
	d.draw();
	return 0;
}