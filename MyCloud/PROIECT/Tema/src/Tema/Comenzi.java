package Tema;

interface Command
{
	public Director execute(Node nod);
	public Director execute2(Fisier f);
	public Director execute2(Director d);
}

abstract class ReadCommand implements Command
{
	public Director execute(Node nod)
	{
		if(Logger.getLogat().equals("root"))
			return nod.accept(this);
		else if(Logger.getLogat().equals("guest"))
			Output.setOutput("Fail");
		else
		{
		if(nod.getRead()==false && nod.getWrite()==false)
			return nod.accept(this);
		else
			if(nod.getUser().equals(Logger.getLogat()))
			{
				if(nod.getRead()==true)
					return nod.accept(this);
				else Output.setOutput("Fail");
			}
				else
					Output.setOutput("Fail");
		}
		return (Director) nod;
	}
	
	abstract public Director execute2(Fisier f);
	abstract public Director execute2(Director d);
	
}

abstract class WriteCommand implements Command
{
	public Director execute(Node nod)
	{
		if(Logger.getLogat().equals("root"))
			return nod.accept(this);
		else if(Logger.getLogat().equals("guest"))
			Output.setOutput("Fail");
		else
		{
		if(nod.getRead()==false && nod.getWrite()==false)
			return nod.accept(this);
		else
			if(nod.getUser().equals(Logger.getLogat()))
			{
				if(nod.getWrite()==true)
					return nod.accept(this);
				else Output.setOutput("Fail");
			}
				else
					Output.setOutput("Fail");
		}
		return (Director) nod;
	}
	
	abstract public Director execute2(Fisier f);
	abstract public Director execute2(Director d);
}

abstract class SystemCommand implements Command
{
	public Director execute(Node nod)
	{
		nod.accept(this);
		return (Director) nod;
	}
}

public class Comenzi {

}
