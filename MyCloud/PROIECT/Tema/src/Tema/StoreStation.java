package Tema;

import java.util.HashSet;

public abstract class StoreStation {
	
	MachineId id;
	int dim=10240;
	HashSet<Node> spatiu;
	
	public abstract void store(Node d);
	public abstract Node cauta(Node n);
	public abstract boolean contains(Node n);

}

class Statie extends StoreStation{
	
	public Statie()
	{
		id=new MachineId();
		spatiu=new HashSet<Node>();
	}
	
	public void store(Node d)
	{
		spatiu.add(d);
	}
	
	public Node cauta(Node n)
	{
		for(Node i:spatiu)
			if(n.getNume().equals(i.getNume()))
				return i;
		return null;
	}
	
	public boolean contains(Node n)
	{
		for(Node i:spatiu)
			if(i.getNume().equals(n.getNume()))
			return true;
		return false;
	}
	
}
