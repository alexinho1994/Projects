package temaApd;

import java.util.Vector;

class Workr extends Thread {
	WorkPool wp;
	Vector prim;
	Vector fib;
	Vector fact;
	Vector square;

	public Workr(WorkPool workpool, Vector prim, Vector fib, Vector fact, Vector square) {
		this.wp = workpool;
		this.prim = prim;
		this.fib = fib;
		this.fact = fact;
		this.square = square;
	}
	
	public void run() {
		while (true) {
			Event ev = wp.getWork();
			if (ev == null)
				break;
			
			if(ev.com.equals("PRIME"))
			{
				prim.add(prim(ev));
			}
			if(ev.com.equals("SQUARE"))
			{
				square.add(square(ev));
			}
			if(ev.com.equals("FIB"))
			{
				fib.add(fib(ev));
			}
			if(ev.com.equals("FACT"))
			{
				fact.add(fact(ev));
			}
		}
	}
	
	private int prim(Event ev)
	{
		for(int i = ev.n; i>1; i--)
		{
			boolean prim = false;
			for(int j = 2; j<=Math.sqrt(i); j++)
				if(i%j == 0)
				{
					prim = true;
					break;
				}
			if(prim == false){
				return i;
			}
		}
		return 1;
	}
	
	private int fact(Event ev)
	{
		for(int i = ev.n; i>1; i--)
		{
			int fact = 1;
			boolean ok = false;
			for(int j=2;j<=i;j++)
			{
				fact *= j;
				if(fact > ev.n)
				{
					ok = true;
					break;
				}
			}
			if(ok == false)
			{
				return i;
			}
		}
		return 0;
	}
	
	private int square(Event ev)
	{
		return (int) Math.sqrt(ev.n);
	}
	
	private int fib(Event ev)
	{
		int fibb[] = new int[ev.n];
		fibb[0]=0;
		fibb[1]=1;
		if(fibb[1]> ev.n)
			return 0;
		
		for(int i=2;i<=ev.n;i++)
		{
			fibb[i] = fibb[i-1] + fibb[i-2];
			if(fibb[i] > ev.n)
			{
				return i-1;
			}
		}
		
		return ev.n;
	}

	
}