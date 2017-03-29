package Tema;

class MyInvalidPathException extends Exception implements Subject
{
	private static final long serialVersionUID = 1L;
	Director d;
	String parametru;
	String user;
	String data;
	
	public MyInvalidPathException()
	{
		super();
	}
	
	public MyInvalidPathException(String mesage, Director d, String parametru, String user, String data)
	{
		super(mesage);
		this.d=d;
		this.parametru=parametru;
		this.user=user;
		this.data=data;
		Observator.update(this);
	}
	
	public String getMesage()
	{
		return "Fail";
	}
	
	public String getUpdate()
	{
		return "MyInvalidPathException "+d.getNume()+" "+parametru+" "+user+" "+data+"\n";
	}
}

class MyPathTooLongException extends MyInvalidPathException implements Subject
{
	private static final long serialVersionUID = 1L;
	
	public MyPathTooLongException()
	{
		super();
	}
	
	public MyPathTooLongException(String mesage, Director d, String parametru, String user, String data)
	{
		super(mesage, d, parametru, user, data);
	}
	
	public String getMesage()
	{
		return "Fail";
	}
	
	public String getUpdate()
	{
		return "MyPathTooLongException "+d.getNume()+" "+parametru+" "+user+" "+data+"\n";
	}
}

class MyNotEnoughSpaceException extends Exception implements Subject{

	private static final long serialVersionUID = 1L;
	
	int dimensiune;
	String user;
	String data;
	
	public MyNotEnoughSpaceException()
	{
		super();
	}
	
	public MyNotEnoughSpaceException(String mesage, int dimensiune, String user, String data )
	{
		super(mesage);
		this.dimensiune=dimensiune;
		this.user=user;
		this.data=data;
		Observator.update(this);
	}
	
	public String getMesage()
	{
		return "Fail";
	}
	
	public String getUpdate()
	{
		return "MyNotEnoughSpaceException "+dimensiune+" "+user+" "+data+"\n";
	}
	
}

public class Exceptii {

}
