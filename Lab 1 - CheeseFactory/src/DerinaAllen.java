
public class DerinaAllen {
	
	public static int shared = 0;
	
	public static void main(String[] argo){
		
		Runnable r = new CheeseFactory(); // fix this
				
		Thread t = new Thread(r);
		
		t.start();
		
		PizzaFactory p1 = new PizzaFactory();
		
		p1.start();
		
		PizzaFactory p2 = new PizzaFactory();
		
		p2.start();
	}
}
