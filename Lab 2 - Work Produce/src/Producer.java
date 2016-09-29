class Producer extends Thread 					// process Producer
{
	private Transaction tran;
	
	private int a[] = new int[Main.n]; 							// int a[n];
	private int producerID = 0;	
	
	public Producer(Transaction t, int id) 
	{
		for (int i = 0; i < Main.n; i++)
		{
			a[i] = (int)(Math.random() * 100);
		}
		
		tran = t;
		this.producerID = id;
	}

	public void run() 
	{
		while (Main.p < Main.n) 						// while ( p < n)
		{
			if (Main.p == Main.c)  						// <await (p == c); >
			{
				tran.put(a[producerID], producerID); 	// buf = a[p]; // Add new product to queue
				System.out.println("Producer " + producerID + " produced product : " + Main.p);
				
				Main.p++; // p = p + 1;
			}
		}
	}
}