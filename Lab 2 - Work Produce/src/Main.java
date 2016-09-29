public class Main 
{	 
	// Shared Variables 
	// int buf, p = 0. c = 0;
	public static int p = 0;
	public static int c = 0;
	public static int n = 5;
	
	public static int maxRange = 2; // -1 = number of producers/ consumers
	
	
    public static void main(String[] args)
    {  
    	Transaction t = new Transaction();
       
    	Producer[] producerArray = new Producer[maxRange];
    	Consumer[] consumerArray = new Consumer[maxRange]; 
       
    	for(int i = 1; i < maxRange; i++)
    	{
    		producerArray[i] = new Producer(t, i);
    		consumerArray[i] = new Consumer(t, i);    	   
    	   
    		producerArray[i].start();  //start thread.
    	   	consumerArray[i].start();  //start thread.
    	}
	} 
}

//// Initialize classes
//Producer producer = new Producer(t, 1);   
//Thread producerThread = new Thread(producer);
//producerThread.start();  //start consumer thread.
//
//Consumer consumer = new Consumer(t, 1);       
//consumer.start();  //start producer thread.
