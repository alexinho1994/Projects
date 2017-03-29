package Tema;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

public class CommandCd extends ReadCommand{
	
	Vector<String> v;
	Director home;
	Director plecare;
	Director curent;
	
	public CommandCd(Vector<String> v, Director h, Director d)
	{
		this.v=v;
		this.home=h;
		this.curent=d;
	}

	public Director execute2(Fisier f) {
		Output.setOutput("Fail");
		return this.curent;
	}

	public Director execute2(Director d)  {
			this.plecare=d;
			Director x=change(d);
			if(x!=this.plecare)
				Output.setOutput("Success");
			return x;
	}
		
	
	public Director change(Director d)
	{
		try{
			if(v.isEmpty())
			{
				return d;
			}
			if(v.firstElement().equals(this.home.getNume()))
			{
				v.remove(v.firstElement());
				return change(this.home);
			}	
			if(v.firstElement().equals(".."))
				{
					if(d.getNume().equals(this.home.getNume()))
					{
						DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
						Date date=new Date();
						String ora=""+df.format(date);
						throw(new MyInvalidPathException("Fail", this.plecare, "", Logger.getLogat(), ora));
					}
					else
					{
						v.remove(v.firstElement());
						return change(cauta(d, this.home));
						
					}
				}
				else
					{
						for(Node i: d.copii)
							if(v.firstElement().equals(i.getNume()))
								if(i instanceof Director)
								{
									Director x=(Director) i;
									v.remove((v.firstElement()));
									return change(x);
								}
							DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
							Date date=new Date();
							String ora=""+df.format(date);
							throw(new MyInvalidPathException("Fail", this.plecare, "", Logger.getLogat(), ora));
					}
		}
		
		catch(MyInvalidPathException e)
		{
			Output.setOutput(e.getMesage());
			return this.plecare;
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
				if(cauta(x, (Director) i)!=this.plecare)
					return cauta(x, (Director) i);
		}
		return this.plecare;
	}

}
