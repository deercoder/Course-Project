
public class ProduceInteger extends Thread{
	private HoldInteger sharedObject;
	public ProduceInteger(HoldInteger shared){
		super("ProduceInteger");
		sharedObject = shared;
	}
	public void run(){
		for(int count = 1; count <= 10; count++){
			try{
				Thread.sleep((int)Math.random() * 3000);
			}catch(InterruptedException exception){
				System.err.println(exception.toString());
			}
			sharedObject.setSharedInt(count);
		}
		System.err.println(getName()+" finished producing values"+"\n Terminating "+getName());
	}
}
