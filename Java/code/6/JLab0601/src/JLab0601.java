
public class JLab0601 {
	public static void main(String args[]){
		double []fatGrams = new double [6];
		fatGrams[0] = 12.6;
		fatGrams[1] = 32.0;
		fatGrams[2] = 2.0;
		fatGrams[3] = 11.2;
		fatGrams[4] = 0.5;
		fatGrams[5] = 3.99;
		double  temp=0.0; 
		for (int i = 0; i < fatGrams.length ; i++) { 
			for (int j = 0; j < fatGrams.length - i - 1; j++){
				if (fatGrams[j]< fatGrams[j + 1]){ 
					temp=fatGrams[j];
					fatGrams[j]=fatGrams[j + 1];
					fatGrams[j + 1]=temp;
				}
			}
		}
		for (int j = 0; j < fatGrams.length; j++){
			System.out.println(fatGrams[j]);
		}
	}
}
