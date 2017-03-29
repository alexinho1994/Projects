#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//fiecare nod va avea o lista de succesori si una de predecesori, in liste apare si de cate ori apare o sintagma
typedef struct lista{
	char *cuv;
	int aparitii;
	struct lista *next;
	struct lista *back;
}* Lista;

typedef struct graf{
	int n;
	Lista *lista_adiac;
}* Graf;
//initializaz graful
Graf initG (Graf g, int n) 
	{
	int i;
	g->n = n;
	g->lista_adiac = (Lista*)malloc(n * sizeof(Lista));
	for(i = 0; i < n; i++)
		g->lista_adiac[i] = NULL;
	return g;
	}
//adaug noduri in graf
Graf addNode(Graf g, char *cuv, char *cuv2)
	{
	//daca graful nu are noduri, pun pe pozitia 0
	if(g->lista_adiac[0]==NULL)
		{
		Lista new;
		new=(Lista)malloc(sizeof(Lista));
		new->cuv=malloc(25*sizeof(char));
		strcpy(new->cuv, cuv);
		new->aparitii=1;
		new->next=NULL;
		new->back=NULL;
		g->lista_adiac[0]=new;
		}
		else
			{
			int i=0, ok=0, j;
			//verific daca in graf mai am cuvantul
			while(g->lista_adiac[i]!=NULL)
				{
				if(strcmp(cuv, g->lista_adiac[i]->cuv)==0)
					{
					ok=1;
					j=i;
					}
				i++;
				}
			//daca in graf mai am cuvantul, modific lista succesorilor si predecesorilor
			if(ok==1)
				{
				g->lista_adiac[j]->aparitii++;
				Lista tmp;
				tmp=g->lista_adiac[j];
				while(tmp->back!=NULL && strcmp(cuv2, tmp->back->cuv)!=0)
					tmp=tmp->back;
				if(tmp->back!=NULL)
					tmp->back->aparitii++;
					else
						{
						Lista nou;
						nou=(Lista)malloc(sizeof(Lista));
						nou->cuv=malloc(25*sizeof(char));
						strcpy(nou->cuv, cuv2);
						nou->aparitii=1;
						nou->next=NULL;
						nou->back=NULL;
						tmp->back=nou;
						}
				int k=0;
				while(strcmp(g->lista_adiac[k]->cuv, cuv2)!=0)
					k++;
				Lista tmp2;
				tmp2=g->lista_adiac[k];
				while(tmp2->next!=NULL && strcmp(cuv, tmp2->next->cuv)!=0)
					tmp2=tmp2->next;
				if(tmp2->next!=NULL)
					tmp2->next->aparitii++;
					else
						{
						Lista nou;
						nou=(Lista)malloc(sizeof(Lista));
						nou->cuv=malloc(25*sizeof(char));
						strcpy(nou->cuv, cuv);
						nou->aparitii=1;
						nou->next=NULL;
						nou->back=NULL;
						tmp2->next=nou;
						}
				}
				//daca nu mai am cuvantul, il pun intr-un nod nou
				else
					{
					Lista new;
					new=(Lista)malloc(sizeof(Lista));
					new->cuv=malloc(25*sizeof(char));
					strcpy(new->cuv, cuv);
					new->aparitii=1;
					new->next=NULL;
					new->back=NULL;
					g->lista_adiac[i]=new;
					Lista nou;
					nou=(Lista)malloc(sizeof(Lista));
					nou->cuv=malloc(25*sizeof(char));
					strcpy(nou->cuv, cuv2);
					nou->aparitii=1;
					nou->next=NULL;
					nou->back=NULL;
					g->lista_adiac[i]->back=nou;
					int k=0;
					while(strcmp(g->lista_adiac[k]->cuv, cuv2)!=0)
						k++;
					Lista tmp2;
					tmp2=g->lista_adiac[k];
					while(tmp2->next!=NULL && strcmp(cuv, tmp2->next->cuv)!=0)
						tmp2=tmp2->next;
					if(tmp2->next!=NULL)
						tmp2->next->aparitii++;
						else
							{
							Lista nou;
							nou=(Lista)malloc(sizeof(Lista));
							nou->cuv=malloc(25*sizeof(char));
							strcpy(nou->cuv, cuv);
							nou->aparitii=1;
							nou->next=NULL;
							nou->back=NULL;
							tmp2->next=nou;
							}
					}
			}
	return g;
	}

int main(int argc, char *argv[])
{
	FILE *sursa, *dest, *sursa2;
	sursa=fopen(argv[1], "r");
	dest=fopen(argv[2], "w");
	char *fisier;
	fisier=malloc(100*sizeof(char));
	fscanf(sursa, "%s", fisier);
	sursa2=fopen(fisier, "r");
	int c,i=0, j;
	//calculez aproximativ numarul de cuvinte pentru a initializa cat mai eficient graful
	while((c=fgetc(sursa2))!=EOF)
		{
		if(c==' ' || c=='-' || c=='\n')
			{
			i++;
			while(c==' '  || c=='\n' || c=='-')
				c=fgetc(sursa2);
			}
		if(c==EOF)
			break;
		}
	fclose(sursa2);
	sursa2=fopen(fisier, "r");
	Graf g;
	g=(Graf)malloc(sizeof(struct graf));
	g=initG(g, i);
	int nrcuv=i;
	char *cuv, *cuv2;
	cuv=malloc(25*sizeof(char));
	cuv2=malloc(25*sizeof(char));
	//citesc caracter cu caracter si formez cuvinte, in cuv retin cuvantul curent si in cuv2 retin cuvantul precedent
	while((c=fgetc(sursa2))!=EOF)
		{
		int j=0;
		while(c!=' ' && c!='-' && c!='\n')
			{
			if(c>='a' && c<='z')
				{
				cuv[j]=c;
				j++;
				}
			if(c>='0' && c<='9')
				{
				cuv[j]=c;
				j++;
				}
			if(c>='A' && c<='Z')
				{
				cuv[j]=c+32;
				j++;
				}
			if(c==39)
				{
				cuv[j]=c;
				j++;
				}
			c=fgetc(sursa2);
			}
		cuv[j]='\0';
		if(cuv[0]!='\0')
			{
			g=addNode(g, cuv, cuv2);
			strcpy(cuv2, cuv);
			}
		}	
	//calculez numarul de noduri	
	int nrnod=0;
	while(g->lista_adiac[nrnod]!=NULL)
		{
		nrnod++;
		}
	//calculez maximul odds pentru a calcula costurile
	double max=0;
	for(i=0;i<nrnod;i++)
		for(j=0;j<nrnod;j++)
			if(i!=j)
				{
				strcpy(cuv2, g->lista_adiac[j]->cuv);
				Lista tmp;
				tmp=g->lista_adiac[i]->next;
				while(tmp!=NULL && strcmp(cuv2, tmp->cuv)!=0)
					tmp=tmp->next;
				if(tmp!=NULL)
					{
					double o11, o12, o21, o22, max2;
					o11=tmp->aparitii;
					int aparitii=0;
					tmp=g->lista_adiac[i]->next;
					while(tmp!=NULL)
						{
						aparitii=aparitii+tmp->aparitii;
						tmp=tmp->next;
						}
					o12=aparitii - o11;
					o21=g->lista_adiac[j]->aparitii - o11;
					o22=nrcuv-o11-o12-o21-1;
					o11=o11+0.5;
					o12=o12+0.5;
					o21=o21+0.5;
					o22=o22+0.5;
					o11=log(o11);
					o22=log(o22);
					o12=log(o12);
					o21=log(o21);
					max2=o11+o22-o12-o21;
					if(max<max2)
						max=max2;
					}
				}
	//creez o matrice de costuri, astfel ca pe linia i coloana j voi avea costul sintagmei i-j
	double **costuri;
	costuri=(double**)malloc(nrnod*sizeof(double*));
	for(i=0;i<nrnod;i++)
		costuri[i]=(double*)malloc(nrnod*sizeof(double));
	//calculez costurile si le pun in matrice
	for(i=0;i<nrnod;i++)
		for(j=0;j<nrnod;j++)
			{
			strcpy(cuv2, g->lista_adiac[j]->cuv);
			Lista tmp;
			tmp=g->lista_adiac[i]->next;
			while(tmp!=NULL && strcmp(cuv2, tmp->cuv)!=0)
				tmp=tmp->next;
			if(tmp!=NULL)
				{
				double o11, o12, o21, o22;
				o11=tmp->aparitii;
				int aparitii=0;
				tmp=g->lista_adiac[i]->next;
				while(tmp!=NULL)
					{
					aparitii=aparitii+tmp->aparitii;
					tmp=tmp->next;
					}
				o12=aparitii-o11;
				o21=g->lista_adiac[j]->aparitii - o11;
				o22=nrcuv-o11-o12-o21-1;
				o11=o11+0.5;
				o12=o12+0.5;
				o21=o21+0.5;
				o22=o22+0.5;
				o11=log(o11);
				o22=log(o22);
				o12=log(o12);
				o21=log(o21);
				costuri[i][j]=max-(o11+o22-o12-o21)+1;
				}
				else
					costuri[i][j]=999999;
			}
	int nrstg;
	fscanf(sursa, "%d", &nrstg);
	int l;		
	//afisez costurile
	for(l=1;l<=nrstg;l++)
		{
		fscanf(sursa, "%s%s", cuv, cuv2);
		i=0;
		while(strcmp(g->lista_adiac[i]->cuv, cuv))
			i++;
		j=0;
		while(strcmp(g->lista_adiac[j]->cuv, cuv2))
			j++;
		fprintf(dest, "%.5lf\n", costuri[i][j]);
		}
	//drumul cel mai scurt il calculez cu dijkstra
	fscanf(sursa, "%d", &nrstg);
	for(l=1;l<=nrstg;l++)
		{
		fscanf(sursa, "%s%s", cuv, cuv2);
		int *s, *t;
		double *d;
		i=0;
		while(strcmp(g->lista_adiac[i]->cuv, cuv))
			i++;
		//in d voi retine drumul cel mai scurt de la un nod la toate celelalte noduri
		d=(double*)malloc(nrnod*sizeof(double));
		//in s pun nodurile deja vizitate
		s=(int*)malloc(nrnod*sizeof(int));
		//in t pun nodul "tata" pentru fiecare nod
		t=(int*)malloc(nrnod*sizeof(int));
		for(j=0;j<nrnod;j++)
			d[j]=costuri[i][j];
		s[i]=1;
		for(j=0;j<nrnod;j++)
			if(costuri[i][j]<999999)
				t[j]=i;
		for(j=0;j<nrnod-1;j++)
			{
			int min=999999;
			int x, y;
			for(x=0;x<nrnod;x++)
				if(s[x]!=1)
					if(d[x]<min)
						{
						min=d[x];
						y=x;
						}
			s[y]=1;
			for(x=0;x<nrnod;x++)
				if(costuri[y][x]<999999)
					if(d[x]>d[y]+costuri[y][x])
						{
						d[x]=d[y]+costuri[y][x];
						t[x]=y;
						}
			}
		j=0;
		while(strcmp(g->lista_adiac[j]->cuv, cuv2))
			j++;
		int *f;
		f=(int*)malloc(nrnod*sizeof(int));
		int y=0;
		while(j!=i)
			{
			f[y]=j;
			j=t[j];
			y++;
			}
		f[y]=j;
		while(y)
			{
			fprintf(dest, "%s ", g->lista_adiac[f[y]]->cuv);
			y--;
			}
		fprintf(dest, "%s", g->lista_adiac[f[y]]->cuv);
		fprintf(dest, "\n");
		free(s);
		free(d);
		free(t);
		free(f);
		}
	free(cuv);
	free(cuv2);
	fclose(sursa);
	fclose(sursa2);
	free(fisier);
	fclose(dest);
	return 0;
}
