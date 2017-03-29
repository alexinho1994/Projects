package Tema;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class CommandLogin extends SystemCommand implements Subject {
	
	Useri list;
	String username;
	String password;
	Director curent;
	
	public CommandLogin(String username, String password, Useri list, Director d)
	{
		this.list=list;
		this.username=username;
		this.password=password;
		this.curent=d;
	}
	
	public Director execute2(Fisier f) {
		Output.setOutput("Eroare");
		return this.curent;
	}
	
	public Director execute2(Director d) {
		
		boolean log=false;
		
		for(User i: this.list.useri)
		{
			if(i.username.equals(username))
				if(i.parola.equals(password))
					log=true;
		}
		
		if(log==true)
		{
			Observator.update(this);
			Output.setOutput("Success");
			Logger.login(username);
			for(User i: list.useri)
			{
				if(i.username.equals(username))
				{
					DateFormat df = new SimpleDateFormat("dd/MM/yy,HH:mm:ss");
					Date date=new Date();
					i.logare=""+df.format(date);
				}
			}
		}
		else Output.setOutput("Fail");
		return d;
		
	}

	public String getUpdate() {
		return "User "+username+" logat"+"\n";
	}

}
