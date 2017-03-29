package Tema;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

public class CommandRm extends WriteCommand {
	
	boolean recursiv;
	Vector<String> v;
	Director curent;
	Director home;
	
	public CommandRm(boolean recursiv, Vector<String> v, Director d, Director home)
	{
		this.recursiv=recursiv;
		this.v=v;
		this.curent=d;
		this.home=home;
	}

	public Director execute2(Fisier f) {
		
		return this.curent;
	}

	public Director execute2(Director d) {
		d=change(d);
		int ok=0;
		for(Node i:d.copii)
		{
			if(i.getNume().equals(v.firstElement()))
			{
				ok=1;
				if(recursiv=true)
				{
					if(Logger.getLogat().equals("root"))
					{
						d.remove(i, home);
						Output.setOutput("Success");
						return this.curent;
					}
					else
					{
						if(i.getUser().equals(Logger.getLogat()) && i.getWrite()==true)
						{
							d.remove(i, home);
							Output.setOutput("Success");
							return this.curent;
						}
						else 
							if(i.getWrite()==false && i.getRead()==false)
							{
								d.remove(i, home);
								Output.setOutput("Success");
								return this.curent;
							}
							else Output.setOutput("Fail");
					}
				}
				else
				{
					if(Logger.getLogat().equals("root"))
					{
						if(i instanceof Fisier)
						{
							d.remove(i, home);
							Output.setOutput("Success");
							return this.curent;
						}
						if(i instanceof Director)
							if(((Director) i).copii.isEmpty())
							{
								d.remove(i, home);
								Output.setOutput("Success");
								return this.curent;
							}
					}
					else
					{
						if(i.getUser().equals(Logger.getLogat()) && i.getWrite()==true)
						{
							if(i instanceof Fisier)
							{
								d.remove(i, home);
								Output.setOutput("Success");
								return this.curent;
							}
							if(i instanceof Director)
								if(((Director) i).copii.isEmpty())
								{
									d.remove(i, home);
									Output.setOutput("Success");
									return this.curent;
								}
						}
						else 
							if(i.getWrite()==false && i.getRead()==false)
							{
								if(i instanceof Fisier)
								{
									d.remove(i, home);
									Output.setOutput("Success");
									return this.curent;
								}
								if(i instanceof Director)
									if(((Director) i).copii.isEmpty())
									{
										d.remove(i, home);
										Output.setOutput("Success");
										return this.curent;
									}
							}
							else Output.setOutput("Fail");
					}	
				}
			}
		}
		if(ok==0)
			try{
				if(rmregex(d)==true) Output.setOutput("Success");
				else
				{
					DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
					Date date=new Date();
					String ora=""+df.format(date);
					throw(new MyInvalidPathException("Fail", this.curent, "", Logger.getLogat(), ora));
				}
			}
				catch(MyInvalidPathException e)
				{
					Output.setOutput(e.getMesage());
					return this.curent;
				}
		return this.curent;
	}
	
	public Director change(Director d)
	{
		try{
			if(v.size()==1)
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
						throw(new MyInvalidPathException("Fail", this.curent, "", Logger.getLogat(), ora));
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
							throw(new MyInvalidPathException("Fail", this.curent, "", Logger.getLogat(), ora));
					}
		}
		
		catch(MyInvalidPathException e)
		{
			Output.setOutput(e.getMesage());
			return this.curent;
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

	public boolean rmregex(Director d)
	{
		boolean x=false;
		if(recursiv==false)
		{
			for(int li=d.copii.size()-1;li>=0; li--)
			{
				Node i=d.copii.get(li);
				if(i.getNume().matches(v.firstElement()))
				{
					if((i.getUser().equals(Logger.getLogat()) && i.getWrite()==true) || Logger.getLogat().equals("root"))
					{
						if(i instanceof Fisier)
						d.remove(i, home);
						if(i instanceof Director)
							if(((Director) i).copii.isEmpty())
								d.remove(i, home);
					}
					else 
						if(i.getWrite()==false && i.getRead()==false)
						{
							if(i instanceof Fisier)
							d.remove(i, home);
							if(i instanceof Director)
								if(((Director) i).copii.isEmpty())
									d.remove(i, home);
						}
				x=true;	
				}
			}
		}
		else
		{
			for(int li=d.copii.size()-1;li>=0; li--)
			{
				Node i=d.copii.get(li);
				if(i.getNume().matches(v.firstElement()))
				{
					if((i.getUser().equals(Logger.getLogat()) && i.getWrite()==true) || Logger.getLogat().equals("root"))
					{
						d.remove(i, home);
					}
					else 
						if(i.getWrite()==false && i.getRead()==false)
						{
						d.remove(i, home);
						}
					x=true;
				}
				else
				{
					if(x=false)
						x=rmregex((Director) i);
					else rmregex((Director) i);
				}
			}
		}
	return x;		
	}

}
