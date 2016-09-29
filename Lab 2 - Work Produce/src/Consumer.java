class Consumer extends Thread 							// process Consumer
{
	private Transaction tran;
	
	private int b[] = new int[Main.n]; 					// int b[n];
	private int consumerID = 0;
	
	public Consumer(Transaction t, int id) 
	{
		tran = t;
		this.consumerID = id;
	}


	public void run()
	{
		while (Main.c < Main.n)							// while (c < n)
		{ 						
			if (Main.p > Main.c)						// <await (p > c); > 			// wait - while p is less than or equal to c;	
			{
				b[Main.c] = tran.get(0);				// b[c] = buf; 					// get first product in queue					
				for(int i = 0; i < tran.buf.length - 1; i++) 							// remove first product in queue
				{ 
					tran.buf[i] = tran.buf[i + 1];
				}
				
				System.out.println("Consumer " + consumerID + " consumed product : " + Main.c);			
				
				Main.c++; 								// c + c + 1;		
			}
		}	
	}
}
