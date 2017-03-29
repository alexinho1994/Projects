package Tema;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class CommandLogout extends SystemCommand implements Subject{
	
	Useri list;
	Director curent;
	
	public CommandLogout(Useri list, Director d)
	{
		this.list=list;
		this.curent=d;
	}

	public Director execute2(Fisier f) {
		Output.setOutput("Eroare");
		return this.curent;
	}

	public Director execute2(Director d) {
		Output.setOutput("Success");
		Observator.update(this);
		Logger.login("guest");
		for(User i: list.useri)
		{
			if(i.username.equals("guest"))
			{
				DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
				Date date=new Date();
				i.logare=""+df.format(date);
			}
		}
		return d;
		
	}

	public String getUpdate() {
		return "User "+Logger.getLogat()+" delogat"+"\n";
	}

}
