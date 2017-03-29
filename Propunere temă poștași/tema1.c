#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct cartiere
		{
		int id;
		char *nume;
		} cartiere;
typedef struct pachet
		{
		int id, adresa[18], idcartier, strada, numar, prioritate,cod,codcorect;
		float greutate;
		char *mesaj;
		} pachet;
typedef struct postas
		{
		int id, nrpachete;
		struct pachet pachete[50];
		} postas;
void citire1(cartiere *a, int nrc)
{
	int i;
	char *sir;
	sir=malloc(100*sizeof(char));
	for(i=0;i<nrc;i++)
		{
		gets(sir);
		a[i].nume=strdup(sir);
		a[i].id=i; 
		}
}
void citire2(pachet *b,int nrp)
{
	int i, j;
	char *sir;
	sir=malloc(100*sizeof(char));
	for(i=0;i<nrp;i++) 
		{
		for(j=0;j<17;j++)
			scanf("%d", &b[i].adresa[j]);
		scanf("%d\n", &b[i].adresa[17]);
		scanf("%d", &b[i].prioritate);
		scanf("%f\n", &b[i].greutate);
		gets(sir);
		b[i].mesaj=strdup(sir);
		b[i].id=i;
		}
}
void scrie1(cartiere *a, int nrc)
{
	int i;
	printf("Punctul 1\n");
	for(i=0;i<nrc;i++)
		{
		printf("%d ", a[i].id);
		puts(a[i].nume);
		}
}
void scrie2(pachet *b, int nrp)
{
	int i, j;	
	for(i=0;i<nrp;i++)
		{
		printf("%d\n", b[i].id);
		for(j=0;j<18;j++)
			printf("%d ", b[i].adresa[j]);
		printf("\n");
		printf("%d %f ", b[i].prioritate, b[i].greutate);
		puts(b[i].mesaj);
		}
}
void adresa(pachet *b, int nrp)
{
	int i,j,k,exp;
	for(i=0;i<nrp;i++)
		{
		b[i].idcartier=0;
		b[i].strada=0;
		b[i].numar=0;
		for(j=4;j>=0;j--)
			{
			exp=1;
			k=4;
			while(k!=j)
				{
				exp=exp*2;
				k--;
				}
			b[i].idcartier=b[i].idcartier+b[i].adresa[j]*exp;
			}
		for(j=9;j>=5;j--)
			{
			exp=1;
			k=9;
			while(k!=j)
				{
				exp=exp*2;
				k--;
				}
			b[i].strada=b[i].strada+b[i].adresa[j]*exp;
			}
		for(j=17;j>=10;j--)
			{
			exp=1;
			k=17;
			while(k!=j)
				{
				exp=exp*2;
				k--;
				}
			b[i].numar=b[i].numar+b[i].adresa[j]*exp;
			}
		}
	printf("Punctul 2\n");
	for(i=0;i<nrp;i++)
		printf("%d %d %d %d\n", b[i].id, b[i].idcartier, b[i].strada, b[i].numar);
}
void distribuire(postas *c, pachet *b, int nrc, int nrp)
{
	int i,j,k;
	for(i=0;i<nrc;i++)
		{
		c[i].id=i;
		c[i].nrpachete=0;
		for(j=0;j<nrp;j++)
			if(b[j].idcartier==c[i].id) 
				{
				c[i].pachete[c[i].nrpachete].id=b[j].id;
				for(k=0;k<18;k++)
					c[i].pachete[c[i].nrpachete].adresa[k]=b[j].adresa[k];
				c[i].pachete[c[i].nrpachete].idcartier=b[j].idcartier;
				c[i].pachete[c[i].nrpachete].strada=b[j].strada;
				c[i].pachete[c[i].nrpachete].numar=b[j].numar;
				c[i].pachete[c[i].nrpachete].prioritate=b[j].prioritate;
				c[i].pachete[c[i].nrpachete].cod=b[j].cod;
				c[i].pachete[c[i].nrpachete].greutate=b[j].greutate;
				c[i].pachete[c[i].nrpachete].mesaj=strdup(b[j].mesaj);
				c[i].nrpachete++;
				}
		}
	printf("Punctul 3\n");
	for(i=0;i<nrc;i++)
		{
		printf("%d %d ", c[i].id, c[i].nrpachete);
		for(j=0;j<c[i].nrpachete;j++)
			printf("%d ", c[i].pachete[j].id);
		printf("\n");
		}
}
void ordonare(pachet *c, int nrpachete, int id)
{
	int i, j, k, aux;
	float auxf;
	char *auxchar;
	for(i=0;i<nrpachete-1;i++)
		for(j=i;j<nrpachete;j++)
			if(c[i].prioritate<c[j].prioritate)
				{
				aux=c[i].id;
				c[i].id=c[j].id;
				c[j].id=aux;
				aux=c[i].idcartier;
				c[i].idcartier=c[j].idcartier;
				c[j].idcartier=aux;
				for(k=0;k<18;k++)
					{
					aux=c[i].adresa[k];
					c[i].adresa[k]=c[j].adresa[k];
					c[j].adresa[k]=aux;
					}
				aux=c[i].strada;
				c[i].strada=c[j].strada;
				c[j].strada=aux;
				aux=c[i].numar;
				c[i].numar=c[j].numar;
				c[j].numar=aux;
				aux=c[i].prioritate;
				c[i].prioritate=c[j].prioritate;
				c[j].prioritate=aux;
				aux=c[i].cod;
				c[i].cod=c[j].cod;
				c[j].cod=aux;
				auxf=c[i].greutate;
				c[i].greutate=c[j].greutate;
				c[j].greutate=auxf;
				auxchar=c[i].mesaj;
				c[i].mesaj=c[j].mesaj;
				c[j].mesaj=auxchar;
				}
			else if(c[i].prioritate==c[j].prioritate && c[i].greutate<c[j].greutate)
				{
				aux=c[i].id;
				c[i].id=c[j].id;
				c[j].id=aux;
				aux=c[i].idcartier;
				c[i].idcartier=c[j].idcartier;
				c[j].idcartier=aux;
				for(k=0;k<18;k++)
					{
					aux=c[i].adresa[k];
					c[i].adresa[k]=c[j].adresa[k];
					c[j].adresa[k]=aux;
					}
				aux=c[i].strada;
				c[i].strada=c[j].strada;
				c[j].strada=aux;
				aux=c[i].numar;
				c[i].numar=c[j].numar;
				c[j].numar=aux;
				aux=c[i].prioritate;
				c[i].prioritate=c[j].prioritate;
				c[j].prioritate=aux;
				aux=c[i].cod;
				c[i].cod=c[j].cod;
				c[j].cod=aux;
				auxf=c[i].greutate;
				c[i].greutate=c[j].greutate;
				c[j].greutate=auxf;
				auxchar=c[i].mesaj;
				c[i].mesaj=c[j].mesaj;
				c[j].mesaj=auxchar;
				}
	printf("%d %d ", id, nrpachete);
	for(i=0;i<nrpachete;i++)
		printf("%d ", c[i].id);
	printf("\n");
}
int cod(pachet b, char text[ ])
{
	int s=0,i;
	int n=strlen(text);
	for(i=0;i<n;i++)
	s=s+text[i]*i;
	b.cod=s%(b.strada*b.numar);
	return b.cod;
}	
int inversare(char *text, pachet b)
{	
	char * sep=".,:?! ";
	char sir2[100], textinv[100];
	strcpy(textinv, "\0");
	text=strtok(text, sep);
	while(text)
		{
		strcpy(sir2, text);
		strcat(sir2, textinv);
		strcpy(textinv, sir2);
		text=strtok(NULL, sep);
		}
	b.cod=cod(b, textinv);
	return b.cod;
}
int prim(int n)
{
	int d=2;
	while(d<=n/2)
		if(n%d==0) return 0;
			else d++;
	return 1;
}
int modifcod(int id, int cod)
{
	int pozitii[31]={0},i, biti[31]={0}, exp, j;
	if(id==1)
		pozitii[1]=1;
	if(id==0) 
		pozitii[0]=1;
		else 
			for(i=2;i<=id;i++)
				if(id%i==0)
					if(prim(i)) pozitii[i]=1;
	i=0;
	while(cod && i<=31)
		{
		biti[i]=cod%2;
		cod=cod/2;
		i++;
		}
	for(i=0;i<=31;i++)
	if(pozitii[i]) 
			{
			if(biti[i]) 
				biti[i]=0;
				else 
					biti[i]=1;
			}
	for(i=0;i<=31;i++)
		{
		exp=1;
		for(j=1;j<=i;j++)
			exp=exp*2;
		cod=cod+exp*biti[i];
		}
	return cod;
}
int punct6(int id, int cod)
{
	if(id<10)
		if(cod%10==id)
			cod=modifcod(id, cod);
	if(id>9)
		if(cod%100==id)
			cod=modifcod(id, cod);
	return cod;
}
void scor(postas *c, int nrc)
{
	int i, j;
	float scor,corect;
	for(i=0;i<nrc;i++)
		{
		scor=0;
		corect=0;
		for(j=0;j<c[i].nrpachete;j++)
			if(c[i].pachete[j].cod==c[i].pachete[j].codcorect)
				corect++;
		scor=corect/c[i].nrpachete;
		printf("%d %.6f\n", c[i].id, scor);
		}
}
int main()
{
	int nrc, nrp, i,j;
	struct cartiere a[32];
	struct pachet b[50];
	struct postas c[32];
	scanf("%d\n", &nrc);
	citire1(a, nrc);
	scanf("%d\n", &nrp);
	citire2(b, nrp);
	scrie1(a, nrc);
	scrie2(b, nrp);
	adresa(b, nrp);
	distribuire(c, b, nrc, nrp);
	printf("Punctul 4\n");
	for(i=0;i<nrc;i++)
		ordonare(c[i].pachete, c[i].nrpachete, c[i].id);
	printf("Punctul 5\n");
	for(i=0;i<nrc;i++)
		{
		printf("%d %d ", c[i].id, c[i].nrpachete);
		for(j=0;j<c[i].nrpachete;j++)
			{
			printf("%d ", c[i].pachete[j].id);
			c[i].pachete[j].cod=inversare(c[i].pachete[j].mesaj, c[i].pachete[j]);
			c[i].pachete[j].codcorect=c[i].pachete[j].cod;
			printf("%d ", c[i].pachete[j].cod);
			}
		printf("\n");
		}
	printf("Punctul 6\n");
	for(i=0;i<nrc;i++)
		{
		printf("%d %d ", c[i].id, c[i].nrpachete);
		for(j=0;j<c[i].nrpachete;j++)
			{
			printf("%d ", c[i].pachete[j].id);
			c[i].pachete[j].cod=punct6(c[i].id, c[i].pachete[j].cod);
			printf("%d ", c[i].pachete[j].cod);
			}
		printf("\n");
		}
	printf("Punctul 7\n");
	scor(c, nrc);
	return 0;
}
