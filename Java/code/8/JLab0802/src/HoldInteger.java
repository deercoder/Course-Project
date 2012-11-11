
public class HoldInteger {
	private int sharedInt = -1;
	private boolean available = false;
	public  synchronized void setSharedInt(int value){
		while (available == true){
			try{
				wait();
			}catch(InterruptedException e){ }
		}
		available = true;
		System.err.println(Thread.currentThread().getName()+
				" setting sharedInt to "+ value);
		sharedInt = value; 
		notifyAll();
	}
	public  synchronized int getSharedInt(){
		while (available == false){
			try{
				wait();
			}catch(InterruptedException e){ }
		}
		available = false;
		System.err.println(Thread.currentThread().getName()+
				" retrieving sharedInt value "+ sharedInt);
		notifyAll();
		return sharedInt;
	}
}
