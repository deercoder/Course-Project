
public class Rectangle{
	double width,length;
	public Rectangle(double width,double length){
		this.width = width;
		this.length = length;
		System.out.println("rectangle's width " + this.width);
		System.out.println("rectangle's length " +this.length);
	}
	public double area(){
		double a;
		a = length  * width;
		return a;
	}
}