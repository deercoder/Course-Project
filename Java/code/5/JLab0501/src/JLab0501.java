
class JLab0501 {
	public static void main(String[] args) {
		Pet myPet = new Pet("George");
		Dog myDog = new Dog("Snoopy",10);
		System.out.println(myPet.toString()+"\n"+"Speak:"+
				myPet.speak()+"\n"+myPet.move()+" "+
				myPet.getName()+"\n");
		System.out.println(myDog.toString()+"\n"+"Speak:"+
				myDog.speak()+"\n"+myDog.move()+" "
				+myDog.getName()+"\n");
		System.out.println("the weight of the "+ myDog.toString() + " is " + myDog.getWeight());
	}

}
