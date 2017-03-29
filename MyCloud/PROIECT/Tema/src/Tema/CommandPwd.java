package Tema;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class CommandPwd extends ReadCommand{
	
	Director curent;
	
	public CommandPwd(Director d)
	{
		this.curent=d;
	}
	
	public Director execute2(Fisier f) {
		Output.setOutput("Eroare");
		return this.curent;
	}

	public Director execute2(Director d) {
		try
		{
			if(d.cale.length()<255)
				Output.setOutput(d.cale);
			else 
			{
				DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
				Date date=new Date();
				String ora=""+df.format(date);
				throw (new MyPathTooLongException("Fail", d, "", Logger.getLogat(), ora));
			}
		}
		catch(MyPathTooLongException e)
		{
			Output.setOutput(e.getMesage());
		}
		return d;
		
	}
	
	

}
