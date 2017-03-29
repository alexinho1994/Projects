package Tema;

public class CommandCat extends ReadCommand {
	
	String nume;
	Director curent;
	
	public CommandCat(String nume, Director d)
	{
		this.nume=nume;
		this.curent=d;
	}

	public Director execute2(Fisier f) {
		Output.setOutput(f.v.toString());
		return this.curent;
	}

	public Director execute2(Director d) {
		for(Node i: d.copii)
		{
			if(i instanceof Fisier)
				if(i.getNume().equals(this.nume))
					execute2((Fisier) i);
		}
		return d;
	}

}
