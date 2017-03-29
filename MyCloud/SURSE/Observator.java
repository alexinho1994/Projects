package Tema;

import java.io.FileWriter;

interface Subject{
	public String getUpdate();
}



public class Observator{
	
	private static final Observator observer=new Observator();
	private static String obs;
	
	private Observator()
	{
		obs="";
	}
	
	public static Observator getInstance()
	{
		return observer;
	}
	
	public static String getLog()
	{
		return obs;
	}

	public static void update(Subject subject){
		
		obs=obs+subject.getUpdate();
		try {
			write();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void write() throws Exception
	{
		FileWriter out=new FileWriter("out.txt");
		out.write(obs);
		out.close();
	}
	
}
