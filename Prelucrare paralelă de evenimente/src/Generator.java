package temaApd;

import java.io.FileReader;
import java.io.LineNumberReader;
import java.util.Vector;

public class Generator extends Thread{
	
	int n;
	String nume;
	Vector coada;
	int size;
	WorkPool wp;
	
	public Generator()
	{
		
	}
	
	public Generator(int n, String nume, Vector coada, int size, WorkPool wp)
	{
		this.n = n;
		this.nume = nume;
		this.coada = coada;
		this.size = size;
		this.wp = wp;
	}
	
	public void run()
	{
		FileReader f = null;
	    LineNumberReader lnr = null;
		try {
		f=new FileReader(this.nume);
		lnr=new LineNumberReader(f);
		String linie;
		while((linie=lnr.readLine())!=null)
		{
				String line[] = linie.split(",");
				this.sleep(Integer.parseInt(line[0]));
				Event event = new Event(line[1], Integer.parseInt(line[2]));
				while(wp.tasks.size()==size)
				{
					synchronized (wp.tasks) {
						wp.tasks.wait();
					}
				}
				synchronized (wp.tasks) {
					wp.putWork(event);
					wp.tasks.notifyAll();
				}
		}
		}
		catch(Exception e){
			 e.printStackTrace();
		}
	}

}
