public class JLab0304_1{
	public static void main(String[] args){
		int n,num,num1;
		System.out.println("在1~100可被3与7整除的数为");
		for (n = 1; n <= 100; n++){
			num = n  % 3;
			num1 = n % 7;
			if (num == 0){
			   if (num1 == 0)
				System.out.print(n+ " ");
			}
		}
	System.out.println(" ");
	}

}	
