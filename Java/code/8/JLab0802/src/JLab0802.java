
public class JLab0802 {
	public static void main(String[] args) {
		HoldInteger sharedObject = new HoldInteger();
		ProduceInteger producer = new ProduceInteger(sharedObject);
		ConsumeInteger consumer = new ConsumeInteger(sharedObject);
		producer.start();
		consumer.start();
	}

}
