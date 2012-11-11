
public class JLab0504B {
	public static void main(String[] args) {
		Cat myCat = new Cat("Betty");
		System.out.println(myCat.toString()+"\n"+"Speak:"+
				myCat.speak()+"\n"+myCat.move()+""+
				myCat.getName()+"\n");
	}

}
class Cat implements Pet{
	protected String name;
	public Cat(String n){
		name = n;
	}
	public String getName(){
		return name;
	}
	public String move(){
		return "run";
	}
	public String speak(){
		return "miao miao";
	}
	public String toString(){
		return "my Pet " + name;
	}
}
