package Tema;

public class CommandLs extends ReadCommand {
	boolean recursiv;
	boolean inf;
	String nume;
	Director curent;
	
	public CommandLs(String nume, boolean recursiv, boolean inf, Director d)
	{
		this.nume=nume;
		this.recursiv=recursiv;
		this.inf=inf;
		this.curent=d;
	}
	
	public Director execute2(Fisier f)
	{
		if(inf==false)
			Output.setOutput(Output.getOutput()+f.nume+"\n");
		else
		{
			Output.setOutput(Output.getOutput()+"F: "+ f.nume+" "+f.dimensiune+" ["+f.ora+"] ");
			if(f.getRead()==true || f.getWrite()==true)
			{
				Output.setOutput(Output.getOutput()+"-");
				if(f.getRead()==true)
					Output.setOutput(Output.getOutput()+"r");
				if(f.getWrite()==true)
					Output.setOutput(Output.getOutput()+"w");
				Output.setOutput(Output.getOutput()+"-");
			}
			Output.setOutput(Output.getOutput()+"\n");
		}
		return this.curent;
	}
	
	public Director execute2(Director d)
	{
		if(nume.equals(""))
		{
			if(this.recursiv==false && this.inf==false)
				for(Node i:d.copii)
					if((i.getRead()==false && i.getWrite()==false) || (i.getRead()==true && i.getUser()==Logger.getLogat()) || Logger.getLogat().equals("root"))
						Output.setOutput(Output.getOutput()+i.getNume()+"\n");
			if(this.recursiv==true && this.inf==false)
			{
				Output.setOutput(Output.getOutput()+d.getNume()+"\n");
				for(Node i: d.copii)
					if((i.getRead()==false && i.getWrite()==false) || (i.getRead()==true && i.getUser()==Logger.getLogat()) || Logger.getLogat().equals("root"))
						if(i instanceof Fisier)
							execute2((Fisier) i);
						else execute2((Director) i);
			}
			if(this.recursiv==false && this.inf==true)
				for(Node i:d.copii)
					if((i.getRead()==false && i.getWrite()==false) || (i.getRead()==true && i.getUser()==Logger.getLogat()) || Logger.getLogat().equals("root"))
						if(i instanceof Fisier)
							execute2((Fisier) i);
						else
						{
							Output.setOutput(Output.getOutput()+"D: "+ ((Director) i).nume+" "+((Director) i).dimensiune+" ["+((Director) i).ora+"] ");
							if(i.getRead()==true || i.getWrite()==true)
							{
								Output.setOutput(Output.getOutput()+"-");
								if(i.getRead()==true)
									Output.setOutput(Output.getOutput()+"r");
								if(i.getWrite()==true)
									Output.setOutput(Output.getOutput()+"w");
								Output.setOutput(Output.getOutput()+"-");
							}
							Output.setOutput(Output.getOutput()+"\n");
						}
			if(this.recursiv==true && this.inf==true)
			{
				Output.setOutput(Output.getOutput()+"D: "+ d.nume+" "+d.dimensiune+" ["+d.ora+"] ");
				if(d.getRead()==true || d.getWrite()==true)
				{
					Output.setOutput(Output.getOutput()+"-");
					if(d.getRead()==true)
						Output.setOutput(Output.getOutput()+"r");
					if(d.getWrite()==true)
						Output.setOutput(Output.getOutput()+"w");
					Output.setOutput(Output.getOutput()+"-");
				}
				Output.setOutput(Output.getOutput()+"\n");
				for(Node i:d.copii)
					if((i.getRead()==false && i.getWrite()==false) || (i.getRead()==true && i.getUser()==Logger.getLogat()) || Logger.getLogat().equals("root"))
						if(i instanceof Fisier)
							execute2((Fisier) i);
						else execute2((Director) i);
			}
		}
		else
		{
			for(Node i:d.copii)
				if(i.getNume().equals(nume))
				{
					this.nume="";
					if(i instanceof Fisier)
						return execute2((Fisier) i);
					else return execute2((Director) i);
				}
			String parametru=this.nume;
			for(Node i:d.copii)
				if(i.getNume().matches(parametru))
				{
					this.nume="";
					if(i instanceof Fisier)
						execute2((Fisier) i);
					else execute2((Director) i);
				}
		}
		return this.curent;
	}
}
