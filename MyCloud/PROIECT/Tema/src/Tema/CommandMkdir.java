package Tema;

public class CommandMkdir extends WriteCommand{
	
	String nume;
	boolean read;
	boolean write;
	String user;
	Director curent;
	Director home;
	
	public CommandMkdir(String nume, boolean read, boolean write, Director d, Director home)
	{
		this.nume=nume;
		this.read=read;
		this.write=write;
		this.user=Logger.getLogat();
		this.curent=d;
		this.home=home;
	}

	public Director execute2(Fisier f) {
		Output.setOutput("Eroare");
		return this.curent;
	}

	public Director execute2(Director d) {
		Director d2=new Director(nume, read, write, user);
		d2.cale=d.cale+"/"+d2.nume;
		d.add(d2, this.home);
		Output.setOutput("Success");
		return d;
	}

}
