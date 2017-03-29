package Tema;

public class Output {
	
	private static final Output instance=new Output();
	private static String output;
	
	public static Output getInstance()
	{
		return instance;
	}
	
	public static String getOutput()
	{
		return output;
	}
	
	public static void setOutput(String nou)
	{
		output=nou;
	}

}
