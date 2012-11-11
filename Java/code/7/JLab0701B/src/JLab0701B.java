
public class JLab0701B {
	public static void main(String[] args) {
		try{
			throwException();	
		}
		catch(Exception e){
			System.out.println("Excepton Catched!");
		}
	}
	public static void throwException()throws Exception{
		System.out.println("Method throwException");
		throw new Exception();
	}

}
