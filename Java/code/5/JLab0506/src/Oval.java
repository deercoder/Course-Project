import java.lang.Math;

public class Oval extends Shape{
	public double longradius; //³¤Öá
	public double shortradius; //¶ÌÖá
	public String getName(){
		return "Oval";
	}
	public double area(){
		return Math.PI * longradius * shortradius / 4;
	}
	public double perimeter(){
		return Math.PI * (1.5 *(longradius + shortradius)-
				Math.sqrt(longradius * shortradius));
	}
	public Oval(double m,double n){
		longradius = m;
		shortradius = n;
	}
}
