public class flower{
	public static void main(String[] args){
		int i = 0;
		for (i = 100; i < 1000; i++){
			int x = i / 100;
			int y = (i%100) / 10;
			int z = i%10;
			if ((x*x*x+y*y*y+z*z*z)==i)
				System.out.println(i);
	      }
	}
}