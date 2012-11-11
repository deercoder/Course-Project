import java.lang.Math;

public class Triple extends Shape{
	public double line; //定义等边三角形的边
	public Triple(double l){
		line = l;
	}
	public String getName(){
		return "Triple";
	}
	public double area(){
		return Math.sqrt(3) * line * line / 4;
	}
	public double perimeter(){
		return 3 * line;
	}
}
