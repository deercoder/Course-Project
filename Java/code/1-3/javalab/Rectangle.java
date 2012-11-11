package project;
class Rectangle{
	double width,length;
	public Rectangle(double width,double length){
		this.width = width;
		this.length = length;
	}
	public double area(){
		double a;
		a = length  * width;
		return a;
	}
}