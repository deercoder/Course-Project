
class Dog extends Pet{
	protected int weight;
	public Dog(String s,int weight){
		super(s);
		this.weight = weight;
	}
	public int getWeight(){
		return this.weight;
	}
	//public String speak(){
		//return "Wolf Wolf";
	//}
}
