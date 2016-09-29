
public class CheeseFactory extends java.lang.Object implements java.lang.Runnable {
	public void run(){
		while(true){
			try{Thread.sleep(100);
			} catch (InterruptedException e){
				// TO-DO auto-generated catch block
				e.printStackTrace();
			}
			
			System.out.println("Making Cashel Blue!!!");
			DerinaAllen.shared = 0;
			
			System.out.println("Making Cashel Blue [ " + DerinaAllen.shared + " ]");
		}		
	}
}
