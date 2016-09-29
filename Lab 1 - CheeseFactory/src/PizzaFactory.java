
public class PizzaFactory extends Thread{
	static int count = 0;
	
	public void run(){
		int i = ++count;
		while(true){
			try{Thread.sleep(100);
			} catch (InterruptedException e){
				// TO-DO auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("Pepperoni " + i);
			DerinaAllen.shared = 1;

			System.out.println("Pepperoni [ " + DerinaAllen.shared + " ]");
		}
	}
}
