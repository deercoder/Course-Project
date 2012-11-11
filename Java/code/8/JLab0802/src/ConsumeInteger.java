public class ConsumeInteger extends Thread{
	private HoldInteger sharedObject;
	public ConsumeInteger(HoldInteger shared){
		super("ConsumeInteger");
		sharedObject = shared;
	}
	public void run(){
		int value,sum = 0;
		do{
			try{
				Thread.sleep((int)(Math.random() * 3000));
			}catch(InterruptedException exception){
				System.err.println(exception.toString());
			}
			value = sharedObject.getSharedInt();
			sum+= value;
		}while(value != 10);
		System.err.println(getName()+" retrieved values totaling "+
				sum + "\n Terminating "+getName());
	}
}
