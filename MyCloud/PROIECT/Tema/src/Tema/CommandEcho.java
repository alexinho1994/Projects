package Tema;

public class CommandEcho extends SystemCommand {
	
	String parametru;
	Director curent;
	
	public CommandEcho(String parametru, Director d)
	{
		this.parametru=parametru;
		this.curent=d;
	}

	public Director execute2(Fisier f) {
		Output.setOutput(this.parametru);	
		return this.curent;
	}

	public Director execute2(Director d) {
		Output.setOutput(this.parametru);
		return d;
	}
	
	

}
