
public class JLab0506 {
	public static void main(String[] args) {
		Triangle myTriangle = new Triangle(12.0,6.0);
		System.out.println("name: "+ myTriangle.getName());
		System.out.println("area: " +myTriangle.area());
		System.out.println("perimeter:"+myTriangle.perimeter());
		Triple myTriple = new Triple(6.0);
		System.out.println("name: "+ myTriple.getName());
		System.out.println("area: " +myTriple.area());
		System.out.println("perimeter:"+myTriple.perimeter());
		Oval myOval = new Oval(6.0,8.0);
		System.out.println("name: "+ myOval.getName());
		System.out.println("area: " +myOval.area());
		System.out.println("perimeter:"+myOval.perimeter());
		Circle myCircle = new Circle(6.0);
		System.out.println("name: "+ myCircle.getName());
		System.out.println("area: " +myCircle.area());
		System.out.println("perimeter:"+myCircle.perimeter());
	}

}
