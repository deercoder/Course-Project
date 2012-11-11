
public class Triangle extends Shape{
	public double width;
	public double height;
	public String getName(){
		return "Triangle";
	}
	public Triangle(double w,double h){
		width = w;
		height = h;
	}
	public double area(){
		return width * height;
	}
	public double perimeter(){
		return 2 * (width + height);
	}
}
