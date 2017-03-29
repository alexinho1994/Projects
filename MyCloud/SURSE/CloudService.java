package Tema;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class CloudService {
	
	private static final CloudService server=new CloudService();
	static int dim=30720;          //dimensiunea totala a celor 3 statii
	static Statie a;
	static Statie b;
	static Statie c;
	static List<Node> lista=new ArrayList<Node>();   //lista generata in urma parcurgerii arborelui
	
	public CloudService()
	{
		a=new Statie();
		a.id.id=1;
		b=new Statie();
		b.id.id=2;
		c=new Statie();
		c.id.id=3;
	}
	
	public static CloudService getServer()
	{
		return server;
	}
	
	public static Statie getPrima()
	{
		return a;
	}
	
	public static Statie getAdoua()
	{
		return b;
	}
	
	public static Statie getAtreia()
	{
		return c;
	}
	
	public static void upload(Director d)
	{
		try
		{
			if(d.getDimensiune()>dim)
			{
				DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
				Date date=new Date();
				String ora=""+df.format(date);
				throw (new MyNotEnoughSpaceException("Fail", dim, Logger.getLogat(),ora));
			}
			else
			{
				Output.setOutput("Success");
				parcurgere(d);    //introduc nodurile in lista
				int stcurenta=1;
				for(Node i:lista)
				{
					if(i instanceof Fisier)      //pun fisierul in cloud
					{
						if(stcurenta==1)
							if(a.dim>i.getDimensiune())
								{
								a.store(i);
								a.dim=a.dim-i.getDimensiune();
								dim=dim-i.getDimensiune();
								}
							else
								stcurenta++;
						if(stcurenta==2)
							if(b.dim>i.getDimensiune())
							{
								b.store(i);
								b.dim=b.dim-i.getDimensiune();
								dim=dim-i.getDimensiune();
							}
							else stcurenta++;
						if(stcurenta==3)
						{
								c.store(i);
								c.dim=c.dim-i.getDimensiune();
								dim=dim-i.getDimensiune();
						}
					}
					if(i instanceof Director)
					{
						List<Node> temp=new ArrayList<Node>();  //schimb lista de succesori ai directorului cu MachineId-uri
						for(Node j:((Director) i).copii)    
						{
							if(a.contains(j))
							{
								MachineId nod=new MachineId();
								nod.id=1;
								nod.nume=j.getNume();
								temp.add(nod);
							}
							if(b.contains(j))
							{
								MachineId nod=new MachineId();
								nod.id=2;
								nod.nume=j.getNume();
								temp.add(nod);
							}
							if(c.contains(j))
							{
								MachineId nod=new MachineId();
								nod.id=3;
								nod.nume=j.getNume();
								temp.add(nod);
							}
						}
						while(((Director) i).copii.isEmpty()==false)
							((Director) i).copii.remove(0);
						for(Node j:temp)
						{
							((Director) i).copii.add(j);
						}
						if(stcurenta==1)
							a.store(i);
						if(stcurenta==2)
							b.store(i);
						if(stcurenta==3)
							c.store(i);
					}
				}
			}
		}
		catch(MyNotEnoughSpaceException e)
		{
			Output.setOutput(e.getMesage());
		}
	}
	
	public static Director sync(Director d)
	{
		Node nod=a.cauta(d);
		if(nod==null)
			nod=b.cauta(d);
		if(nod==null)
			nod=c.cauta(d);
		Director clona=new Director(nod.getNume(), nod.getRead(), nod.getWrite(), nod.getUser());
		clona.cale=((Director) nod).cale;
		clona.ora=((Director) nod).ora;
		clona.dimensiune=nod.getDimensiune();
		for(Node i: ((Director) nod).copii)
		{
			clona.copii.add(i);
		}
		List<Node> temp=new ArrayList<Node>();
		for(Node i:clona.copii)
		{
			if(((MachineId) i).id==1)
				nod=a.cauta(i);
			if(((MachineId) i).id==2)
				nod=b.cauta(i);
			if(((MachineId) i).id==3)
				nod=c.cauta(i);
			if(nod instanceof Director)
			{
				Director clona2=new Director(nod.getNume(), nod.getRead(), nod.getWrite(), nod.getUser());
				clona2.cale=((Director) nod).cale;
				clona2.ora=((Director) nod).ora;
				clona2.dimensiune=nod.getDimensiune();
				for(Node j: ((Director) nod).copii)
				{
					clona2.copii.add(j);
				}
				temp.add(clona2);
			}
			
			if(nod instanceof Fisier)
			{
				Fisier clona2=new Fisier(nod.getNume(), nod.getDimensiune(), ((Fisier) nod).tip, nod.getRead(), nod.getWrite(), nod.getUser());
				clona2.ora=((Fisier) nod).ora;
				clona2.cale=((Fisier) nod).cale;
				for(int j:((Fisier) nod).v)
				{
					clona2.v.add(j);
				}
				temp.add(clona2);
			}
		}
		while(clona.copii.isEmpty()==false)
			clona.copii.remove(0);
		for(Node i:temp)
			clona.copii.add(i);
		for(Node i:clona.copii)
			if(i instanceof Director)
				sync2((Director) i);
		return clona;
	}
	
	public static void sync2(Director d)
	{
		Node nod=null;
		List<Node> temp=new ArrayList<Node>();
		for(Node i:d.copii)
		{
			if(((MachineId) i).id==1)
				nod=a.cauta(i);
			if(((MachineId) i).id==2)
				nod=b.cauta(i);
			if(((MachineId) i).id==3)
				nod=c.cauta(i);
			if(nod instanceof Director)
			{
				Director clona2=new Director(nod.getNume(), nod.getRead(), nod.getWrite(), nod.getUser());
				clona2.cale=((Director) nod).cale;
				clona2.ora=((Director) nod).ora;
				clona2.dimensiune=nod.getDimensiune();
				for(Node j: ((Director) nod).copii)
				{
					clona2.copii.add(j);
				}
				temp.add(clona2);
			}
			
			if(nod instanceof Fisier)
			{
				Fisier clona2=new Fisier(nod.getNume(), nod.getDimensiune(), ((Fisier) nod).tip, nod.getRead(), nod.getWrite(), nod.getUser());
				clona2.ora=((Fisier) nod).ora;
				clona2.cale=((Fisier) nod).cale;
				for(int j:((Fisier) nod).v)
				{
					clona2.v.add(j);
				}
				temp.add(clona2);
			}
		}
		while(d.copii.isEmpty()==false)
			d.copii.remove(0);
		for(Node i:temp)
			d.copii.add(i);
		for(Node i:d.copii)
			if(i instanceof Director)
				sync2((Director) i);
	}
	
	public static void parcurgere(Node d)
	{
		if(d instanceof Director)
		{
			for(Node i:((Director) d).copii)
				parcurgere(i);
			Director clona=new Director(d.getNume(), d.getRead(), d.getWrite(), d.getUser());
			clona.cale=((Director) d).cale;
			clona.ora=((Director) d).ora;
			clona.dimensiune=d.getDimensiune();
			for(Node i:((Director) d).copii)
				clona.copii.add(i);
			lista.add(clona);
		}
		if(d instanceof Fisier)
		{
			Fisier clona=new Fisier(d.getNume(), d.getDimensiune(), ((Fisier) d).tip, d.getRead(), d.getWrite(), d.getUser());
			clona.ora=((Fisier) d).ora;
			clona.cale=((Fisier) d).cale;
			for(int i:((Fisier) d).v)
			{
				clona.v.add(i);
			}
			lista.add(clona);
		}
	}

}
