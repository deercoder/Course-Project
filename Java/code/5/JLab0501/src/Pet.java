
class Pet {
	protected String name;
	public Pet(String n){
		name = n;
	}
	public String getName(){
		return name;
	}
	public String move(){
		return "run";
	}
	public String speak(){
		return "";
	}
	public String toString(){
		return "My pet " + name;
	}
}
