public class Transaction 
{
	public int[] buf = new int[100];
	private boolean available = false;
	
	public synchronized int get(int i) 
	{
		while (available == false) 
		{
			try 
			{
				wait();
			}
			catch (InterruptedException e) 
			{
			}
		}
		available = false;
		notifyAll(); // Notify producer 
		return buf[i];
	}
	
	public synchronized void put(int value, int i) 
	{
		while (available == true) 
		{
			try 
			{
				wait();
			}
			catch (InterruptedException e) 
			{ 
			} 
		}
		buf[i] = value;
		available = true;
		notifyAll(); // Notify consumer
	}
}