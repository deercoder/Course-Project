import java.lang.Number;

public class score{
	public static void main(String[] args){
		int b = Integer.valueOf(args[0]).intValue();
		int a = b / 10;
		switch(a){
			case 10: System.out.println("优秀");break;
			case 9: System.out.println("优秀");break;
			case 8: System.out.println("良好");break;
			case 7: System.out.println("中等");break;
			case 6: System.out.println("及格");break;
			default: System.out.println("不及格");
		}	
	}
}