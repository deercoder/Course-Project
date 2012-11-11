public class JLab0603 {
	public static void change(String s){
		s = s + " changed?";
	}
	public static void change(StringBuffer sb){
		sb.append(" changed?");
	}
	public static void main(String[] args){
		String s = "test";
		StringBuffer sb = new StringBuffer("test");
		System.out.println("s="+s+",sb="+sb);
		change(s);
		change(sb);
		System.out.println("s="+s+",sb="+sb);
	}
}
