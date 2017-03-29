package Tema;

public class CommandTouch extends WriteCommand {
	
	String nume;
	int dimensiune;
	boolean read;
	boolean write;
	String user;
	Director curent;
	Director home;
	
	public CommandTouch(String nume, int dimensiune, boolean read, boolean write, Director d, Director home)
	{
		this.nume=nume;
		this.dimensiune=dimensiune;
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
		Fisier f=new Fisier(nume, dimensiune, "text", read, write, user);
		f.cale=d.cale+"/"+f.nume;
		d.add(f, this.home);
		Output.setOutput("Success");
		return d;
	}
	
	

}
