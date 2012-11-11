
class LOCATION
{
private:
	int x,y;
public:
	LOCATION(int x,int y):LOCATION::x(x),LOCATION::y(y) { }
	void move(int x,int y);		
};

void LOCATION::move(int x,int y) //形参仅仅表示移动距离 
{
	LOCATION::x += x;
	LOCATION::y += y;
	cout << "after move(" << LOCATION::x << "," << LOCATION::y <<")" << endl;
}

class POINT:public LOCATION
{
public:
	POINT(int x,int y):LOCATION(x,y){ }
	void move(int x,int y) { LOCATION::move(x,y); }
	void draw(){	putpixel(x,y);	}	
};

class CIRCLE:public LOCATION
{
	int radius;    //圆要特殊些，有半径 
public:
	CIRCLE(int x,int y,int radius):LOCATION(x,y){ CIRCLE::radius = radius; }
	void move(int x,int y):POINT(x,y){}
	void draw();	
};
void CIRCLE::draw()
{
	for(int i = 0; i < 8; i++)
	{
		putpixel(x+radius*cos(PI* i/4),y+radius*sin(PI*i/4));
	}
}
