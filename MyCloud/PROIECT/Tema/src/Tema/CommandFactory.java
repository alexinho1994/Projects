package Tema;

import java.util.StringTokenizer;
import java.util.Vector;

public class CommandFactory {

	public Command getCommand(String com, Useri list, Director h, Director curent)
	{
		
		if(com.startsWith("pwd"))
			return new CommandPwd(curent);		
		if(com.startsWith("echo"))
			return new CommandEcho(com.substring(5), curent);
		if(com.startsWith("newuser"))
		{
			String substr=com.substring(8);
			Vector<String> v=new Vector<String>(4);
			StringTokenizer st=new StringTokenizer(substr, " ");
			while(st.hasMoreTokens())
				v.add(st.nextToken());
			return new CommandNewuser(v.get(0), v.get(1), v.get(2), v.get(3), list, curent);
		}
		if(com.startsWith("userinfo"))
			return new CommandUserinfo(list, curent);
		if(com.startsWith("logout"))
			return new CommandLogout(list, curent);
		if(com.startsWith("login"))
		{
			String substr=com.substring(6);
			Vector<String> v=new Vector<String>(2);
			StringTokenizer st=new StringTokenizer(substr, " ");
			while(st.hasMoreTokens())
				v.add(st.nextToken());
			return new CommandLogin(v.get(0), v.get(1), list, curent);
		}
		if(com.startsWith("touch"))
		{
			String substr=com.substring(6);
			Vector<String> v=new Vector<String>();
			StringTokenizer st=new StringTokenizer(substr, " ");
			while(st.hasMoreTokens())
				v.add(st.nextToken());
			boolean read=false;
			boolean write=false;
			int dim=0;
			if(v.size()==2)
			{
				if(v.get(1).contains("r"))
					read=true;
				if(v.get(1).contains("w"))
					write=true;
				if(!v.get(1).contains("r") && !v.get(1).contains("w"))
					dim= Integer.parseInt(v.get(1));
			}
			if(v.size()==3)
			{
				if(v.get(2).contains("r"))
					read=true;
				if(v.get(2).contains("w"))
					write=true;
				dim=Integer.parseInt(v.get(1));
			}
			return new CommandTouch(v.firstElement(), dim, read, write, curent, h);
		}
		if(com.startsWith("mkdir"))
		{
			String substr=com.substring(6);
			Vector<String> v=new Vector<String>();
			StringTokenizer st=new StringTokenizer(substr, " ");
			while(st.hasMoreTokens())
				v.add(st.nextToken());
			if(v.size()==1)
				return new CommandMkdir(v.firstElement(), false, false, curent, h);
			else
			{
				boolean read=false;
				boolean write=false;
				if(v.get(1).contains("r"))
					read=true;
				if(v.get(1).contains("w"))
					write=true;
				return new CommandMkdir(v.firstElement(), read, write, curent, h);
			}	
		}
		if(com.startsWith("ls"))
		{
			if(com.equals("ls"))
				return new CommandLs("", false, false, curent);
			String substr=com.substring(3);
			Vector<String> v=new Vector<String>();
			StringTokenizer st=new StringTokenizer(substr, " ");
			while(st.hasMoreTokens())
				v.add(st.nextToken());
			String nod="";
			boolean recursiv=false;
			boolean inf=false;
			if(v.size()==1)
			{
				if(v.get(0).equals("-a") || v.get(0).equals("-r") || v.get(0).equals("-ar") || v.get(0).equals("-ra"))
				{
					if(v.get(0).contains("r"))
						recursiv=true;
					if(v.get(0).contains("a"))
						inf=true;
				}
				else nod=v.get(0);
			}
			if(v.size()==2)
			{
				if(v.get(0).equals("-a") || v.get(0).equals("-r") || v.get(0).equals("-ar") || v.get(0).equals("-ra"))
				{
					if(v.get(0).contains("r"))
						recursiv=true;
					if(v.get(0).contains("a"))
						inf=true;
					nod=v.get(1);
				}
				else 
					{
					nod=v.get(0);
					if(v.get(1).contains("r"))
						recursiv=true;
					if(v.get(1).contains("a"))
						inf=true;
					}
			}
			return new CommandLs(nod, recursiv, inf, curent);
		}
		if(com.startsWith("cat"))
			return new CommandCat(com.substring(4), curent);
		if(com.startsWith("cd"))
		{
			String substr=com.substring(3);
			Vector<String> v=new Vector<String>();
			StringTokenizer st=new StringTokenizer(substr, "/");
			while(st.hasMoreTokens())
				v.add(st.nextToken());
			return new CommandCd(v, h, curent);
		}
		if(com.startsWith("rm"))
		{
			String substr=com.substring(3);
			Vector<String> v=new Vector<String>();
			StringTokenizer st=new StringTokenizer(substr, " ");
			while(st.hasMoreTokens())
				v.add(st.nextToken());
			boolean recursiv=false;
			if(v.size()==1)
			{
				substr=v.get(0);
				v.remove(0);
				StringTokenizer t=new StringTokenizer(substr, "/");
				while(t.hasMoreTokens())
					v.add(t.nextToken());
				return new CommandRm(recursiv, v, curent, h);
			}
			else
			{
				recursiv=true;
				substr=v.get(1);
				v.remove(0);
				v.remove(0);
				StringTokenizer t=new StringTokenizer(substr, "/");
				while(t.hasMoreTokens())
					v.add(t.nextToken());
				return new CommandRm(recursiv, v, curent, h);
			}
		}
		if(com.startsWith("upload"))
		{
			if(com.equals("upload"))
				return new CommandUpload("",curent);
			else
			{
				String substr=com.substring(7);
				return new CommandUpload(substr, curent);
			}
		}
		if(com.startsWith("sync"))
		{
			if(com.equals("sync"))
				return new CommandSync("",curent, h);
			else
			{
				String substr=com.substring(5);
				return new CommandSync(substr, curent, h);
			}
		}
		return null;
	}
	
}
