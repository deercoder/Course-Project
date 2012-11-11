
public class JLab0503 {
	public static void main(String args[]){
		System.out.println("创建父类对象:");
		SuperClass sc0 = new SuperClass();
		System.out.println("\n 创建第一个子类对象: ");
		SubClass sc1 = new SubClass();
//		System.out.println("\n 创建第二个子类对象: ");
//		SubClass sc2 = new SubClass();
	}
}

class SuperClass{
	SuperClass(){
		System.out.println("父类的构造函数");
	}
}

class SubClass extends SuperClass{
//	SubClass(){
//		System.out.println("子类的第一个构造函数");
//	}
//	SubClass(int i){
//		System.out.println("子类的第二个构造函数");
//	}
}

