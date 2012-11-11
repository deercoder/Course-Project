import java.util.Arrays;

public class JLab0602 {
	public static void main(String[] args) {
		String[] animals = {"cat","fish","mouse"};
		int[] lengthOfString = new int[animals.length];  //数组的话直接是一个成员，不加括号
		for (int j = 0; j < animals.length; j++){
			lengthOfString[j] = animals[j].length(); //string类的是length方法，要加括号
		}
		Arrays.sort(lengthOfString);
		for(int i = lengthOfString.length-1 ; i >=0 ; i--){
			for (int j = 0; j < animals.length;j++){
				if (animals[j].length() == lengthOfString[i])
					System.out.print(animals[j].toUpperCase()+" ");
			}
		}
		System.out.println();
	}
}
