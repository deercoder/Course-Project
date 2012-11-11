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
class Dog extends Pet{
	protected int weight;
	public Dog(String s){
		super(s);
	}
}

public class JLab0504 {
	public static void main(String args[]){
		Dog myDog = new Dog("Spot");
		System.out.println(myPet.toString()+"\n"+"Speak:"+
				myPet.speak()+"\n"+myPet.move()+""+
				myPet.getName()+"\n");
		System.out.println(myDog.toString()+"\n"+"Speak:"+
				myDog.speak()+"\n"+myDog.move()+""
				+myDog.getName()+"\n");
	}
}
