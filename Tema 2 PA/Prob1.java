import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Vector;

class Muchie implements Comparable
{
	int x;
	int y;
	int cost;
	
	public Muchie(int x, int y, int cost)
	{
		this.x=x;
		this.y=y;
		this.cost=cost;
	}
	
	public int compareTo(Object o) {
		return this.cost - ((Muchie) o).cost;
	}
}

class Arbore
{
	int n;
	Vector<Vector<Integer>> list;
	boolean []visited;
	int parinte[];
	
	public Arbore(int n)
	{
		this.n=n;
		list=new Vector<Vector<Integer>>(n+1);
		for(int i=0;i<=n;i++)
			list.add(new Vector<Integer>());
		visited=new boolean[n+1];
		for(int i=0; i<=n;i++)
		{
			visited[i]=false;
		}
		parinte= new int[n+1];
	}
	
	public void addMuchie(int x, int y)
	{
		this.list.get(x).add(y);
		this.list.get(y).add(x);
	}
	
	void dfs(int x, int y)
	{
		if(x!=y)
		{
			visited[x]=true;
			Vector<Integer> muchiiNod=this.list.get(x);
			for(Integer i:muchiiNod)
			{
				if(visited[i]==false)
				{
					parinte[i]=x;
					dfs(i, y);
				}
			}
		}
	}
	
	Vector<Integer> refac(int x, int y)
	{
		Vector<Integer> vect=new Vector<Integer>();
		vect.add(y);
		while(x!=y)
		{
			vect.add(parinte[y]);
			y=parinte[y];
		}
		for(int i=0;i<=n;i++)
		{
			parinte[i]=0;
			visited[i]=false;
		}
		return vect;
	}
}

class Graf
{
	int n;
	int m;
	int q;
	long cost=0;
	Muchie []muchii;
	Muchie []muchiisort;
	int []rez;
	int [][]arbore;
	int []parinte;
	
	public Graf() throws Exception
	{
		Scanner scanner = new Scanner(new File("kim.in"));
		this.n=scanner.nextInt();
		this.m=scanner.nextInt();
		this.q=scanner.nextInt();
		muchii=new Muchie[m];
		muchiisort=new Muchie[m];
		rez= new int[q];
		arbore = new int[n+1][n+1];
		parinte = new int[n+1];
		for(int i=1;i<=n;i++)
			parinte[i]=0;
		for(int i=0;i<m;i++)
		{
			int a, b, c;
			a=scanner.nextInt();
			b=scanner.nextInt();
			c=scanner.nextInt();
			muchii[i]=new Muchie(a, b, c);
			muchiisort[i]=new Muchie(a, b, c);
		}
		Arrays.sort(muchiisort);
		for(int i=0;i<q;i++)
		{
			int a=scanner.nextInt();
			rez[i]=a;
		}
		scanner.close();
	}
	
	public int radacina(int nod)
	{
		while(parinte[nod]!=0)
			nod=parinte[nod];
		return nod;
	}
	
	public void Kruskal() throws IOException
	{
		int nr=0;
		int i=0;
		Arbore arb=new Arbore(this.n);
		while(nr<this.n-1)
		{
			while(radacina(muchiisort[i].x)==radacina(muchiisort[i].y) && radacina(muchiisort[i].x)!=0)
				i++;
			cost=cost+muchiisort[i].cost;
			parinte[radacina(muchiisort[i].y)]=muchiisort[i].x;
			arb.addMuchie(muchiisort[i].x, muchiisort[i].y);
			nr++;
			arbore[muchiisort[i].x][muchiisort[i].y]=muchiisort[i].cost;
			arbore[muchiisort[i].y][muchiisort[i].x]=muchiisort[i].cost;
		}
		Writer wr = new FileWriter("kim.out");
		wr.write(this.cost+"\n");
		//System.out.println(this.cost);
		for( i=0;i<q;i++)
		{
			if(arbore[muchii[rez[i]-1].x][muchii[rez[i]-1].y]==muchii[rez[i]-1].cost)
				//System.out.println(cost);
				wr.write(this.cost+"\n");
			else
			{
				arb.dfs(muchii[rez[i]-1].x, muchii[rez[i]-1].y);
				Vector<Integer> vect= arb.refac(muchii[rez[i]-1].x, muchii[rez[i]-1].y);
				int max=0;
				for(int j=vect.size()-1;j>0; j--)
				{
					int a=vect.get(j);
					int b=vect.get(j-1);
					if(arbore[a][b]>max)
						max=arbore[a][b];
				}
				wr.write(cost-max+muchii[rez[i]-1].cost+"\n");
				//System.out.println(cost-max+muchii[rez[i]-1].cost);
			}
		}
		wr.close();
	}
	
}


public class Prob1 {
	
	public static void main(String args[]) throws Exception
	{
		Graf g=new Graf();
		g.Kruskal();
	}

}
