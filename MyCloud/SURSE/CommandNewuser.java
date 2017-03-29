package Tema;

public class CommandNewuser extends SystemCommand{
	
	String username;
	String password;
	String nume;
	String prenume;
	Useri list;
	Director curent;
	
	public CommandNewuser(String username, String parola, String nume, String prenume, Useri list, Director d)
	{
		this.username=username;
		this.password=parola;
		this.nume=nume;
		this.prenume=prenume;
		this.list=list;
		this.curent=d;
	}

	public Director execute2(Fisier f) {
		Output.setOutput("Fail");
		return this.curent;
	}

	public Director execute2(Director d) {
		User x=new User(username, password, nume, prenume);
		list.useri.add(x);
		Output.setOutput("Success");
		return d;
		}

}
