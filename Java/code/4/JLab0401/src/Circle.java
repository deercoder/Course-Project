
public class Circle {
	public double radius;
	public Circle(){
		radius = 1;
	}
	public Circle(double r){
		radius = r;
	}
	public double area(){
		return (radius * Math.PI * Math.PI);
	}
	public double circumference(){
		return (radius * 2 * Math.PI);
	}
	public String toString(){
		String s = new String("Circle with radius " + this.radius);
		return s;
	}
	public void setRadius(double r){
		this.radius = r;
	}
	public double getRadius(){
		return this.radius;
	}
}
