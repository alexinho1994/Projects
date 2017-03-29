package Tema;

public class CommandUserinfo extends SystemCommand {
	
	Useri list;
	String user;
	Director curent;
	
	public CommandUserinfo(Useri list, Director d)
	{
		this.list=list;
		user=Logger.getLogat();
		this.curent=d;
	}

	public Director execute2(Fisier f) {
		Output.setOutput("Fail");
		return this.curent;
	}

	public Director execute2(Director d) {
		
		for(User i: list.useri)
		{
			if(i.username.equals(user))
				Output.setOutput("UserName:"+user+" "+"FirstName:"+i.nume+" "+"LastName:"+i.prenume+" "+"Created:"+i.creare+" "+"LastLogin:"+i.logare);
		}
		return d;
		
	}
	
	

}
