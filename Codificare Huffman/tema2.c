#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

typedef struct Huffman{
	unsigned char value;
	int16_t left;
	int16_t right;
}__attribute__((__packed__)) Huffman;

typedef struct coada{
	unsigned int val;
	int aparitii;
	char cod[510];
	struct coada* next;
	struct coada* left;
	struct coada* right;
	struct Huffman nod;
} coada;
// functie pentru adaugarea unui nod in coada, ordonat dupa aparitii
void adauga(coada **cap, coada *nou)
	{
	if(*cap==NULL)
		*cap=nou;
		else
			{
			coada *tmp;
			tmp=*cap;
			//verific daca trebuie introdus la inceputul cozii
			if(nou->aparitii<tmp->aparitii)
				{		
				nou->next=tmp;
				*cap=nou;
				}
				else
					{
					while(tmp->next!=NULL && tmp->next->aparitii<nou->aparitii)
						tmp=tmp->next;
					//verific daca trebuie introdus la sfarsitul cozii, daca nu, il introduc dupa nodul curent
					if(tmp->next==NULL)
						tmp->next=nou;
						else
							{
							coada *aux;
							aux=tmp->next;
							tmp->next=nou;
							nou->next=aux;
							}
					}
			}
	}
//numar recursiv numarul de noduri din arbore
int16_t noduri(coada *cap, int16_t i)
	{
	if(cap->left==NULL && cap->right==NULL)
		{
		cap->nod.value=cap->val;
		i++;
		}
		else
			{
			i++;
			if(cap->left!=NULL)
				i=noduri(cap->left, i);
			if(cap->right!=NULL)
				i=noduri(cap->right, i);
			}
	return i;
	}
//calculez codul fiecarui nod din arbore, in 0 si 1, si le introduc intr-o matrice
void coduri(coada *cap, char v[][510])
	{
	if(cap->left==NULL && cap->right==NULL)
		{
		strcpy(v[cap->val], cap->cod);
		}
		else
			{
			strcpy(cap->left->cod, cap->cod);
			strcpy(cap->right->cod, cap->cod);
			strcat(cap->left->cod, "0");
			strcat(cap->right->cod, "1");
			coduri(cap->left, v);
			coduri(cap->right, v);
			}
	}

int putere(int x)
	{
	int i, p=1;
	for(i=1;i<=x;i++)
		p=p*2;
	return p;
	}
//eliberez memoria din arbore
void dealocare(coada *cap)
	{
	if(cap->left==NULL && cap->right==NULL);
		else
			{
			dealocare(cap->left);
			dealocare(cap->right);
			}
	free(cap);
	}

int main(int argc, char *argv[])
{
	FILE *sursa, *dest;
	sursa=fopen(argv[2], "r");
	dest=fopen(argv[3], "wb");
	uint16_t j;
	unsigned int c;
	int *x=(int*)malloc(256*sizeof(int));
	//creez un vector in care voi numara de cate ori apare in text caracterul de pe pozitia codului ascii 
	for(j=0;j<=255;j++)
		x[j]=0;
	char v[256][510];
	struct Huffman *huffman;
	uint32_t nrch=0;
	uint16_t nrnod=0, i=0;
	coada *cap;
	cap=NULL;
	//prelucrez vectorul si numarul de caractere din text
	while((c=fgetc(sursa))!=EOF)
		{
		x[c]++;
		nrch++;
		}
	//pentru fiecare caracter creez un nod nou si il introduc in coada prin functia adauga
	for(j=0;j<=255;j++)
		if(x[j]>0)
			{
			coada *nou;
			nou=(coada*)malloc(sizeof(coada));
			nou->val=j;
			nou->aparitii=x[j];
			nou->next=NULL;
			nou->left=NULL;
			nou->right=NULL;
			adauga(&cap, nou);
			}
	huffman=malloc((2*nrch)*sizeof(Huffman));
	coada *tmp=cap;
	j=1;
	//introduc in vectorul de structuri pe pozitiile de dupa 0 structurile caracterelor aparute in text
	while(tmp!=NULL)
		{
		huffman[j].value=tmp->val;
		huffman[j].left=-1;
		huffman[j].right=-1;
		tmp->nod=huffman[j];
		tmp=tmp->next;
		j++;
		}
	//creez arborele huffman
	while(cap->next!=NULL)
		{
		//cat timp in coada mai sunt cel putin 2 elemente, creez un nod nou pe care il pun in coada
		coada *nou;
		nou=(coada*)malloc(sizeof(coada));
		nou->val=0;
		nou->aparitii=cap->aparitii+cap->next->aparitii;
		nou->next=NULL;
		i=1;
		//ii creez noului nod o structura huffman pe care o pun in vectorul de structuri
		while(cap->nod.left!=huffman[i].left || cap->nod.right!=huffman[i].right || cap->nod.value!=huffman[i].value)
			i++;
		huffman[j].left=i;
		i=1;
		while(cap->next->nod.left!=huffman[i].left || cap->next->nod.right!=huffman[i].right || cap->next->nod.value!=huffman[i].value)
			i++;
		huffman[j].right=i;
		nou->nod=huffman[j];
		j++;
		nou->left=cap;
		nou->right=cap->next;
		//sterg din coada elementele pe care le-am folosit sa creez noul nod
		coada *tmp;
		tmp=cap->next->next;
		cap->next->next=NULL;
		cap->next=NULL;
		cap=tmp;
		adauga(&cap, nou);
		}
	j--;
	huffman[0]=huffman[j];
	nrnod=noduri(cap, 0);
	fwrite(&nrch, 1, sizeof(uint32_t), dest);
	fwrite(&nrnod, 1, sizeof(uint16_t), dest);
	coduri(cap, v);
	fwrite(huffman, nrnod, sizeof(Huffman), dest);
	fclose(sursa);
	sursa=fopen(argv[2], "r");
	int n, m=0, *d, s;
	d=(int*)malloc(100*sizeof(int));
	//calculez codul in baza 10
	while((c=fgetc(sursa))!=EOF)
		{
		char *cod=(char*)malloc(510*sizeof(char));
		int k;
		//retin in cod codul caracterului citit si il introduc intr-un vector
		for(k=0;k<=255;k++)
			if(k==c)
				strcpy(cod, v[k]);
		n=strlen(cod);
		for(s=m;s<m+n;s++)
			if(cod[s-m]=='1')
				d[s]=1;
			else d[s]=0;
		m=m+n;
		//cat timp vectorul are mai mult de 7 elemente calculez codul primilor 8 biti
		while(m>7)
			{
			int8_t nr=d[7]*putere(0)+d[6]*putere(1)+d[5]*putere(2)+d[4]*putere(3)+d[3]*putere(4)+d[2]*putere(5)+d[1]*putere(6)+d[0]*putere(7);
			for(s=8;s<m;s++)
				d[s-8]=d[s];
			m=m-8;
			fwrite(&nr, sizeof(int8_t), 1, dest);
			}
		free(cod);
		}
	//adaug 0 daca e nevoie
	if(m!=0)
		for(i=m;i<8;i++)
			d[i]=0;
	int8_t nr=d[7]*putere(0)+d[6]*putere(1)+d[5]*putere(2)+d[4]*putere(3)+d[3]*putere(4)+d[2]*putere(5)+d[1]*putere(6)+d[0]*putere(7);
	fwrite(&nr, sizeof(int8_t), 1, dest);	
	//eliberez memoria
	fclose(sursa);
	fclose(dest);
	free(x);
	free(huffman);
	free(d);
	dealocare(cap);
	return 0;
}
