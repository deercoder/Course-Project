
public class JLab0502 {
	public static void test(){
		System.out.println("test() invoked");
	}
	public static int test(int i){
		System.out.println("test("+i+") invoked");
		return i;
	}
	public static String test(String s){
		System.out.println("test("+s+s+") invoked");
		return s;
	}
	public static void test(String s,int i){
		System.out.println("test("+s+","+i+") invoked");
	}
	public static void test(int i,String s){
		System.out.println("test("+i+","+s+") invoked");
	}
	public static int test(int j){
		System.out.println("test("+j+") invoked");
		return j;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		test();
		test(100);
		test("test",100);
		test(100,"test");
	}

}
