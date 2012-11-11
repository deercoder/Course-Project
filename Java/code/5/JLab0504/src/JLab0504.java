abstract class Pet{
	protected String name;
	public Pet(String n){
		name = n;
	}
	public String getName(){
		return name;
	}
	abstract String move();
	abstract String speak();
	public String toString(){
		return "My pet "+name;
	}
}
class Cat extends Pet{
	protected int weight;
	String move(){
		return "run";
	}
	String speak(){
		return "miao miao";
	}
	public Cat(String s){
		super(s);
	}
}

public class JLab0504 {
	public static void main(String args[]){
		Cat myCat = new Cat("Spot");
		System.out.println(myCat.toString()+"\n"+"Speak:"+
				myCat.speak()+"\n"+myCat.move()+""+
				myCat.getName()+"\n");
	}
}
