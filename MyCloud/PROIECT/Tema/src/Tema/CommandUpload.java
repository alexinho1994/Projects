package Tema;

public class CommandUpload extends ReadCommand {
	
	String parametru;
	Director curent;
	
	public CommandUpload(String a,Director Curent)
	{
		this.parametru=a;
		this.curent=Curent;
	}

	public Director execute2(Fisier f) {
		return null;
	}

	public Director execute2(Director d) {
		if(parametru.equals(""))
			CloudService.upload(d);
		else
		{
			for(Node i:d.copii)
				if(i.getNume().equals(parametru))
					CloudService.upload((Director) i);
		}
		return this.curent;
	}

}
