package Tema;

public class CommandSync extends WriteCommand {
	
	String parametru;
	Director curent;
	Director home;
	
	public CommandSync(String a, Director Curent, Director home)
	{
		this.parametru=a;
		this.curent=Curent;
		this.home=home;
	}

	public Director execute2(Fisier f) {
		return null;
	}

	public Director execute2(Director d) {
		if(parametru.equals(""))
		{
			if(d.getNume().equals("home"))
			{
				return CloudService.sync(d);
			}
			else
			{
				int x=0;
				Director c=cauta(d, home);
				for(Node i:c.copii)
					if(i.getNume().equals(d.getNume()))
						x=c.copii.indexOf(i);
				c.remove(c.copii.get(x), home);
				d=CloudService.sync(d);
				c.add(d, home);
				return d;
			}
		}
		else
		{
			Node a=null;
			for(Node i:d.copii)
				if(i.getNume().equals(parametru))
					a=i;
			d.remove(a, home);
			a=CloudService.sync((Director) a);
			d.add(a, home);
			return d;
		}
	}
	
	public Director cauta(Director x, Director d)
	{
		for(Node i: d.copii)
			if(i.getNume().equals(x.getNume()))
			{
				return (Director) d;
			}
		for(Node i: d.copii)
		{
			if(i instanceof Director)
				if(cauta(x, (Director) i)!=this.curent)
					return cauta(x, (Director) i);
		}
		return this.curent;
	}

}
