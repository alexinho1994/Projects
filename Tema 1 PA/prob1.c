#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *sursa, *dest;
	sursa=fopen("joc.in", "r");
	dest=fopen("joc.out", "w");
	int n;
	fscanf(sursa, "%d\n", &n);
	int nr;
	for(nr=0;nr<n;nr++)
		{
		char cuvant[350];
		fscanf(sursa, "%s\n", cuvant);
		int mutari=0;
		int i=0;
		int j=strlen(cuvant)-1;
		while(i!=j && i!=j-1)
			{
			if(cuvant[i]==cuvant[j])
				{
				i++;
				j--;
				}
				else
				{
				int dist1=1;
				int dist2=1;
				while(cuvant[j-dist1]!=cuvant[i])
					dist1++;
				while(cuvant[i+dist2]!=cuvant[j])
					dist2++;
				if(j-dist1==i && i+dist2==j)
					{
					mutari=-1;
					break;
					}
				if(dist1<dist2)
					{
					while(dist1)
						{
						char aux;
						aux=cuvant[j-dist1];
						cuvant[j-dist1]=cuvant[j-dist1+1];
						cuvant[j-dist1+1]=aux;
						mutari++;
						dist1--;
						}
					}
					else
						{
						while(dist2)
							{
							char aux;
							aux=cuvant[i+dist2];
							cuvant[i+dist2]=cuvant[i+dist2-1];
							cuvant[i+dist2-1]=aux;
							mutari++;
							dist2--;
							}
						}
				}
			
			}
		fprintf(dest, "%d\n", mutari);
		}
	fclose(sursa);
	fclose(dest);
	return 0;
}
