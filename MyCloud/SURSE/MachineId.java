package Tema;

public class MachineId implements Node {
	
	int id;
	String nume;

	public MachineId()
	{
		this.id=0;
		this.nume="";
	}

	public Director accept(Command com) {
		return null;
	}

	public int getDimensiune() {
		return 0;
	}

	public boolean getRead() {
		return false;
	}

	public boolean getWrite() {
		return false;
	}

	public String getNume() {
		return this.nume;
	}

	public String getUser() {
		return null;
	}
	
	public int getId()
	{
		return this.id;
	}
	
	

}
