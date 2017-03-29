package Tema;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class User {
	
	String username;
	String parola;
	String nume;
	String prenume;
	String creare;
	String logare;
	
	public User(String username, String parola, String nume, String prenume)
	{
		this.username=username;
		this.parola=parola;
		this.nume=nume;
		this.prenume=prenume;
		DateFormat df = new SimpleDateFormat("dd/MM/yy,HH:mm:ss");
		Date date=new Date();
		this.creare=""+df.format(date);
	}
}

class Logger
{
	private static final Logger instance=new Logger();
	private static String logat;
	
	
	private Logger()
	{
		logat="guest";
	}
	
	public static Logger getInstance()
	{
		return instance;
	}
	
	public static String getLogat()
	{
		return logat;
	}
	
	public static void login(String nou)
	{
		logat=nou;
	}

}

class Useri
{
	List<User> useri=new ArrayList<User>();
	
	public Useri()
	{
		useri.add(new User("root", "rootpass", "", ""));
		useri.add(new User("guest", "", "", ""));
		for(User i: useri)
		{
			if(i.username.equals("guest"))
			{
				DateFormat df = new SimpleDateFormat("dd/MM/yy,HH:mm:ss");
				Date date=new Date();
				i.logare=""+df.format(date);
			}
		}
	}
	
}
