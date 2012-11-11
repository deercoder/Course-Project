import java.lang.Math;

public class Circle extends Shape{
	public double radius;
	public Circle(double r){
		radius = r;
	}
	public String getName(){
		return "Circle";
	}
	public double area(){
		return Math.PI * radius * radius;
	}
	public double perimeter(){
		return 2 * Math.PI * radius;
	}
}
