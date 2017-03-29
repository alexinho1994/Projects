import java.io.File;
import java.io.FileWriter;
import java.io.Writer;
import java.util.Scanner;
import java.util.Vector;

class Graph
{
	int n;
	int m;
	Vector<Vector<Integer>> list;
	boolean []visited;
	int muchii[][];
	Vector<Integer> cicluri;
	
	public Graph(int n, int m)
	{
		this.n=n;
		this.m=m;
		list=new Vector<Vector<Integer>>(n+1);
		for(int i=0;i<=n;i++)
			list.add(new Vector<Integer>());
		visited=new boolean[n+1];
		for(int i=0; i<=n;i++)
		{
			visited[i]=false;
		}
		this.muchii=new int[m][2];
		this.cicluri= new Vector<Integer>();
	}
	
	public void addMuchie(int x, int y, int n)
	{
		this.list.get(x).add(y);
		this.list.get(y).add(x);
		this.muchii[n][0]=x;
		this.muchii[n][1]=y;
	}
	
	public int dfs()
	{
		for(int i=1;i<=n;i++)
		{
			this.explorare2(i);
		}
		for(int i=0;i<m;i++)
		{
			this.list.get(this.muchii[i][0]).add(this.muchii[i][1]);
			this.list.get(this.muchii[i][1]).add(this.muchii[i][0]);
		}
		for(int i=1;i<=n;i++)
			this.visited[i]=false;
		for(Integer i: this.cicluri)
		{
			if(this.visited[i]==false)
				this.explorare(i);
		}
		for(int i=1;i<=n;i++)
			if(this.visited[i]==false)
				this.explorare(i);
		int x=0;
		for(int i=1;i<=n;i++)
			if(visited[i]==false)
				x++;
		return x;
	}
	
	void explorare(int u)
	{
		Vector<Integer> muchiiNod=this.list.get(u);
		for(int i=muchiiNod.size()-1;i>-1; i--)
		{
			if(i<muchiiNod.size())
			{
				int j=muchiiNod.get(i);
				if(this.visited[j]==false)
				{
				this.visited[j]=true;
				muchiiNod.remove((Object) j);
				this.list.get(j).remove((Object) u);
				this.explorare(j);
				}
			}
		}
	}
	
	void explorare2(int u)
	{
		Vector<Integer> muchiiNod=this.list.get(u);
		this.visited[u]=true;
		for(int i=muchiiNod.size()-1;i>-1;i--)
		{
			if(i<muchiiNod.size())
			{
				int j=muchiiNod.get(i);
				if(this.visited[j]==true)
				{
					this.cicluri.add(j);
				}
				else
				{
					this.visited[j]=true;
					muchiiNod.remove((Object) j);
					this.list.get(j).remove((Object) u);
					this.explorare2(j);
				}
			}
		}
	}
	
	
}


public class Prob2 {
	
	public static void main(String args[]) throws Exception
	{
		Scanner scanner = new Scanner(new File("portal.in"));
		int n, m;
		n=scanner.nextInt();
		m=scanner.nextInt();
		Graph g =new Graph(n, m);
		for(int i=0;i<m;i++)
		{
			int a=scanner.nextInt();
			int b=scanner.nextInt();
			g.addMuchie(a, b, i);
		}
		Writer wr = new FileWriter("portal.out");
		wr.write(g.dfs() + "");
		scanner.close();
		wr.close();
	}
	
}
