package Tema;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Vector;

interface Node
{
	public Director accept(Command com);
	public int getDimensiune();
	public boolean getRead();
	public boolean getWrite();
	public String getNume();
	public String getUser();
}

class Fisier implements Node
{
	String nume;
	int dimensiune;
	String tip;
	String ora;
	boolean read;
	boolean write;
	String user;
	String cale;   //calea absoluta a fisierului
	Vector<Integer> v;    //un vector de 0 si 1 ce reprezinta datele din interiorul fisierului, afisat la comanda cat
	
	public Fisier(String nume, int dimensiune, String tip, boolean read, boolean write, String user)
	{
		this.nume=nume;
		this.dimensiune=dimensiune;
		this.tip=tip;
		this.read=read;
		this.write=write;
		this.user=user;
		this.cale=nume;
		DateFormat df = new SimpleDateFormat("dd/MM/yy,HH:mm:ss");
		Date date=new Date();
		this.ora=""+df.format(date);
		v=new Vector<Integer>();
		for(int i=0;i<32;i++)
		{
			int x=(int) (Math.random()*2);
			v.add(x);
		}
	}
	
	public Director accept(Command com) {
		return com.execute2(this);
	}
	
	public String getNume()
	{
		return this.nume;
	}
	
	public boolean getRead()
	{
		return this.read;
	}
	
	public boolean getWrite()
	{
		return this.write;
	}
	
	public int getDimensiune()
	{
		return this.dimensiune;
	}
	
	public String getUser()
	{
		return this.user;
	}
}

class Director implements Node
{
	List<Node> copii=new ArrayList<Node>();
	String nume;
	boolean read;
	boolean write;
	String user;
	String ora;
	int dimensiune;
	String cale;
	
	public Director(String nume, boolean read, boolean write, String user)
	{
		this.nume=nume;
		this.read=read;
		this.write=write;
		this.user=user;
		this.cale=nume;
		this.dimensiune=0;
		DateFormat df = new SimpleDateFormat("dd/MM/yy,HH:mm:ss");
		Date date=new Date();
		this.ora=""+df.format(date);
	}
	
	public Director accept(Command com) {
		return com.execute2(this);
		
	}
	
	public String getNume()
	{
		return this.nume;
	}
	
	public int getDimensiune()
	{
		return this.dimensiune;
	}
	
	public boolean getRead()
	{
		return this.read;
	}
	
	public boolean getWrite()
	{
		return this.write;
	}
	
	public String getUser()
	{
		return this.user;
	}
	
	public void add(Node nod, Director home)
	{
		copii.add(nod);
		this.dimensiune=this.dimensiune+nod.getDimensiune();
		cauta(this, home, nod.getDimensiune()); //actualizez dimensiunea tuturor directoarelor
	}
	
	public void remove(Node nod, Director home)
	{
		this.dimensiune=this.dimensiune-nod.getDimensiune();
		cauta2(this, home, nod.getDimensiune()); //actualizez dimensiunea tuturor directoarelor
		copii.remove(nod);
	}
	
	public Director cauta(Director x, Director d, int dim)
	{
		for(Node i: d.copii)
			if(i.getNume().equals(x.getNume()))
			{
				d.dimensiune=d.dimensiune+dim;
				return (Director) d;
			}
		for(Node i: d.copii)
		{
			if(i instanceof Director)
				if(cauta(x, (Director) i, dim)!=null)
				{
					d.dimensiune=d.dimensiune+dim; 
					return d;
				}
		}
		return null;
	}
	
	public Director cauta2(Director x, Director d, int dim)
	{
		for(Node i: d.copii)
			if(i.getNume().equals(x.getNume()))
			{
				d.dimensiune=d.dimensiune-dim;
				return (Director) d;
			}
		for(Node i: d.copii)
		{
			if(i instanceof Director)
				if(cauta(x, (Director) i, dim)!=null)
				{
					d.dimensiune=d.dimensiune-dim; 
					return d;
				}
		}
		return null;
	}

}

public class Arbore {
	
}
