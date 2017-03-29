#include<stdio.h>
#include<stdlib.h>

int maxx(int i, int j)
{
	if(i>j)
		return i;
	return j;
}

int main()
{
	FILE *sursa, *dest;
	sursa=fopen("cablaj.in", "r");
	dest=fopen("cablaj.out", "w");
	int n;
	fscanf(sursa, "%d\n", &n);
	int i, j, l, k;
	char v[100];
	for(i=0;i<2*n;i++)
		fscanf(sursa, "%c", &v[i]);
	int lungime[100][100];
	int verticala[100][100];
	int perechi[100]={0};
	n=2*n;
	for(i=0;i<n;i++)
		lungime[i][i]=9999;
	for(i=0;i<n-1;i++)
		if(v[i]!=v[i+1])
			{
			lungime[i][i+1]=3;
			verticala[i][i+1]=1;
			perechi[i]=i+1;
			}
		else
			lungime[i][i+1]=9999;
	for(l=3;l<=n;l++)
		for(i=0;i<n-l+1; i++)
			{
			j=i+l-1;
			int unu=0;
			int zero=0;
			k=i;
			while(k<=j)
				{
				if(v[k]=='1')
					unu++;
				else zero++;
				k++;				
				}
			if(zero==unu)
				{
				if(v[i]!=v[j])
					{
					lungime[i][j]=lungime[i+1][j-1]+j-i+2*(verticala[i+1][j-1]+1);
					verticala[i][j]=verticala[i+1][j-1]+1;
					perechi[i]=j;
					}
				else lungime[i][j]=9999;
				for(k=i+1;k<j;k++)
					{
					int q=99999;
					if(lungime[i][k]<9999 && lungime[k+1][j]<9999)
						q=lungime[i][k]+lungime[k+1][j];
					if(q<lungime[i][j])
						{
						lungime[i][j]=q;
						verticala[i][j]=maxx(verticala[i][k], verticala[k+1][j]);
						perechi[i]=k;
						}
					}
				}
			else lungime[i][j]=9999;
			}
	fprintf(dest, "%d\n",lungime[0][n-1]);
	for(i=0;i<n;i++)
		{
		if(perechi[i]!=0)
			{
			fprintf(dest, "%d %d\n", i, perechi[i]);
			perechi[perechi[i]]=0;
			}
		}
	fclose(sursa);
	fclose(dest);
	return 0;
}
