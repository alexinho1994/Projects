/*GRAMENI Stere-Alexandru - 313CC*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nod
	{
	int linie;
	int index;
	char *data;
	int damage;
	struct nod *next;
	struct nod *up;
	struct nod *down;
	}node;
typedef struct comenzi
	{
	int linie;
	int index;
	char *comanda;
	char *data;
	int timp;
	int exec;
	struct comenzi *next;
	}comenzi;
typedef struct comenzistiva
	{
	int linie;
	int index;
	char *comanda;
	char *data;
	int timp;
	int exec;
	struct comenzistiva *next;
	} comenzistiva;
int putere(int l)
	{
	int i=1, x=1;
	while(i<=l)
		{
		x*=2;
		i++;
		}
	return x;
	}
comenzi* init(int linie, int index, char *comand, int timp, char *data)
	{
	comenzi *nou;
	nou=(comenzi*)malloc(sizeof(comenzi));
	nou->data=(char*)malloc(5*sizeof(char));
	nou->linie=linie;
	nou->index=index;
	nou->comanda=(char*)malloc(4*sizeof(char));
	nou->data=(char*)malloc(4*sizeof(char));
	strcpy(nou->data, data);
	strcpy(nou->comanda, comand);
	nou->timp=timp;
	nou->exec=0;
	nou->next=NULL;
	return nou;
	}
comenzi* stergecoada(comenzi *cap)
	{
	comenzi *nou;
	nou=cap;
	cap=cap->next;
	free(nou);
	return cap;
	}
comenzistiva* stergestiva(comenzistiva *cap)
	{
	comenzistiva *nou;
	nou=cap;
	cap=cap->next;
	free(nou);
	return cap;
	}
comenzistiva* adaugastiva(comenzistiva **cap, int linie, int index, char *comand, int timp, char *data)
	{
	comenzistiva *nou;
	nou=(comenzistiva*)malloc(sizeof(comenzistiva));
	nou->data=(char*)malloc(5*sizeof(char));
	nou->linie=linie;
	nou->index=index;
	nou->comanda=(char*)malloc(4*sizeof(char));
	nou->data=(char*)malloc(4*sizeof(char));
	strcpy(nou->data, data);
	strcpy(nou->comanda, comand);
	nou->timp=timp;
	nou->exec=0;
	nou->next=*cap;
	return nou;
	}

void adaugacoada(comenzi **cap, int linie, int index, char *comand, int timp, char *data)
	{
	comenzi *nou, *curent;
	nou=init(linie, index, comand, timp, data);
	curent=*cap;
	if(*cap==NULL)
		*cap=nou;
	else
		{
		while(curent->next!=NULL)
			curent=curent->next;
		curent->next=nou;
		}
	}
void adaugaindex(node **cap, int i, int l)
	{
	node *new, *curent;
	new=(node*)malloc(sizeof(node));
	new->linie=l;
	new->index=i;
	new->damage=0;
	new->data=(char*)malloc(5*sizeof(char));
	strcpy(new->data, "0000");
	new->up=NULL;
	new->down=NULL;
	new->next=NULL;
	curent=*cap;
	while(curent->next!=NULL)
		curent=curent->next;
	curent->next=new;
	if(i==16*putere(l)-1)
		new->next=*cap;
	}
void adaugalinie(node **cap, int l)
	{
	node *nou, *curent;
	nou=(node*)malloc(sizeof(node));
	nou->linie=l;
	nou->data=(char*)malloc(5*sizeof(char));
	strcpy(nou->data, "0000");
	nou->index=0;
	nou->damage=0;
	nou->up=NULL;
	nou->down=NULL;
	nou->next=NULL;
	curent=*cap;
	if(*cap==NULL)
		*cap=nou;
		else
			{
			while(curent->up!=NULL)
				curent=curent->up;
			curent->up=nou;
			nou->down=curent;
			}
	int i;
	for(i=1;i<16*putere(l);i++)
		adaugaindex(&nou, i, l);
	}
int main(int argc, char *argv[])
{
	FILE *sursa, *dest;
	sursa=fopen(argv[1], "r");
	dest=fopen(argv[2], "w");
	int l,i, mod,linie,index,timp;
	char *c, *data;
	c=(char*)malloc(4*sizeof(char));
	data=(char*)malloc(5*sizeof(char));
	int nrdmg1=0, nrdmg2=0, nrdmg3=0, nrdmg4=0;
	float damage1=0, damage2=0, damage3=0, damage4=0;
	fscanf(sursa, "%d%d\n", &mod, &l);
	node *list;
	list=NULL;
	for(i=0;i<l;i++)
		adaugalinie(&list, i);
	node* list2;
	list2=list;
	if(mod==1)
		{
		comenzi *coada;
		fscanf(sursa, "%s", c);
			if(strcmp(c,"::e")!=0)
				{
				fscanf(sursa, "%d%d", &linie, &index);
				if(strcmp(c, "::w")==0)
					fscanf(sursa, "%s", data);
					else
					strcpy(data, "0000");
				fscanf(sursa, "%d", &timp);
				}
		coada=init(linie, index, c, timp, data);
		while(strcmp(c,"::e"))
			{	
			for(i=0;i<timp;i++)
				{
				if(coada->exec==1 && coada->next!=NULL)
					coada=stergecoada(coada);
				if(coada->exec==0)
					{
					if(coada->linie!=list->linie && list->index!=0)
						list=list->next;
						else
						if(coada->linie!=list->linie)
							{
							if(coada->linie>list->linie)
								list=list->up;
								else 
									list=list->down;
							}
						else
							if(coada->index!=list->index)
								list=list->next;
								else
									{
									if(strcmp(coada->comanda, "::r")==0)
										{
										fprintf(dest, "%s\n", list->data);
										list->damage=list->damage+5;
										coada->exec=1;
										}
									if(strcmp(coada->comanda, "::w")==0)
										{
										strcpy(list->data, coada->data);
										list->damage=list->damage+30;
										coada->exec=1;
										}
									if(strcmp(coada->comanda, "::d")==0)
										{
										fprintf(dest, "%d\n", list->damage);
										list->damage=list->damage+2;
										coada->exec=1;
										}
									}
					}
				list->damage=list->damage+1;
				}
			fscanf(sursa, "%s", c);
			if(strcmp(c,"::e")!=0)
				{
				fscanf(sursa, "%d%d", &linie, &index);
				if(strcmp(c, "::w")==0)
					fscanf(sursa, "%s", data);
					else
					strcpy(data, "0000");
				fscanf(sursa, "%d", &timp);
				}	
			adaugacoada(&coada, linie, index, c, timp, data);
			} 
		while(strcmp(coada->comanda, "::e"))
			{
			
			if(coada->exec==1 && coada->next!=NULL)
					coada=stergecoada(coada);
			if(strcmp(coada->comanda, "::e")==0)
				break;
				if(coada->exec==0)
					{
					if(coada->linie!=list->linie && list->index!=0)
						list=list->next;
						else
						if(coada->linie!=list->linie)
							{
							if(coada->linie>list->linie)
								list=list->up;
								else 
									list=list->down;
							}
						else
							if(coada->index!=list->index)
								list=list->next;
								else
								{
								if(strcmp(coada->comanda, "::r")==0)
									{
									fprintf(dest, "%s\n", list->data);
									list->damage=list->damage+5;
									coada->exec=1;
									}
								if(strcmp(coada->comanda, "::w")==0)
									{
									strcpy(list->data, coada->data);
									list->damage=list->damage+30;
									coada->exec=1;
									}
								if(strcmp(coada->comanda, "::d")==0)
									{
									fprintf(dest, "%d\n", list->damage);
									list->damage=list->damage+2;
									coada->exec=1;
									}
								}
					}
				list->damage=list->damage+1;
			}	
		}
	if(mod==2)
		{
		comenzistiva *stiva;
		stiva=NULL;
		fscanf(sursa, "%s", c);
			if(strcmp(c,"::e")!=0)
				{
				fscanf(sursa, "%d%d", &linie, &index);
				if(strcmp(c, "::w")==0)
					fscanf(sursa, "%s", data);
					else
					strcpy(data, "0000");
				fscanf(sursa, "%d", &timp);
				}
		stiva=adaugastiva(&stiva, linie, index, c, timp, data);
		while(strcmp(c,"::e"))
			{	
			for(i=0;i<timp;i++)
				{
				if(stiva->exec==1 && stiva->next!=NULL)
					stiva=stergestiva(stiva);
				if(stiva->exec==0)
					{
					if(stiva->linie!=list->linie && list->index!=0)
						list=list->next;
						else
						if(stiva->linie!=list->linie)
							{
							if(stiva->linie>list->linie)
								list=list->up;
								else 
									list=list->down;
							}
						else
							if(stiva->index!=list->index)
								list=list->next;
								else
									{
									if(strcmp(stiva->comanda, "::r")==0)
										{
										fprintf(dest, "%s\n", list->data);
										list->damage=list->damage+5;
										stiva->exec=1;
										}
									if(strcmp(stiva->comanda, "::w")==0)
										{
										strcpy(list->data, stiva->data);
										list->damage=list->damage+30;
										stiva->exec=1;
										}
									if(strcmp(stiva->comanda, "::d")==0)
										{
										fprintf(dest, "%d\n", list->damage);
										list->damage=list->damage+2;
										stiva->exec=1;
										}
									}
					}
				list->damage=list->damage+1;
				}
			fscanf(sursa, "%s", c);
			if(strcmp(c,"::e")!=0)
				{
				fscanf(sursa, "%d%d", &linie, &index);
				if(strcmp(c, "::w")==0)
					fscanf(sursa, "%s", data);
					else
					strcpy(data, "0000");
				fscanf(sursa, "%d", &timp);
				}	
			stiva=adaugastiva(&stiva, linie, index, c, timp, data);
			} 
		
		while(strcmp(stiva->comanda, "::e"))
			{
			if(stiva->exec==1 && stiva->next!=NULL)
					stiva=stergestiva(stiva);
			if(strcmp(stiva->comanda, "::e")==0)
				break;
				if(stiva->exec==0)
					{
					if(stiva->linie!=list->linie && list->index!=0)
						list=list->next;
						else
						if(stiva->linie!=list->linie)
							{
							if(stiva->linie>list->linie)
								list=list->up;
								else 
									list=list->down;
							}
						else
							if(stiva->index!=list->index)
								list=list->next;
								else
								{
								if(strcmp(stiva->comanda, "::r")==0)
									{
									fprintf(dest, "%s\n", list->data);
									list->damage=list->damage+5;
									stiva->exec=1;
									}
								if(strcmp(stiva->comanda, "::w")==0)
									{
									strcpy(list->data, stiva->data);
									list->damage=list->damage+30;
									stiva->exec=1;
									}
								if(strcmp(stiva->comanda, "::d")==0)
									{
									fprintf(dest, "%d\n", list->damage);
									list->damage=list->damage+2;
									stiva->exec=1;
									}
								}
					}
				list->damage=list->damage+1;
			}	
		}
	for(i=0;i<l;i++)
	{
	do
		{
		if(list2->index<=(16*putere(list2->linie)-1)/4)
			{
			damage1=damage1+list2->damage;
			nrdmg1++;
			}
			else
				if(list2->index<=(16*putere(list2->linie)-1)/2)
					{
					damage2=damage2+list2->damage;
					nrdmg2++;
					}
					else
						if(list2->index<=(16*putere(list2->linie)-1)/4+(16*putere(list2->linie))/2)
							{
							damage3=damage3+list2->damage;
							nrdmg3++;
							}
							else
								{
								damage4=damage4+list2->damage;
								nrdmg4++;
								}
		list2=list2->next;
		}while(list2->index!=16*putere(i)-1);
		damage4=damage4+list2->damage;
		nrdmg4++;
		list2=list2->next;
		if(list2->linie!=l-1)
			list2=list2->up;
		}
		damage1=damage1/nrdmg1;
		damage2=damage2/nrdmg2;
		damage3=damage3/nrdmg3;
		damage4=damage4/nrdmg4;
		damage1=damage1*100;
		damage1=(int)damage1;
		damage1=damage1/100;
		damage2=damage2*100;
		damage2=(int)damage2;
		damage2=damage2/100;
		damage3=damage3*100;
		damage3=(int)damage3;
		damage3=damage3/100;
		damage4=damage4*100;
		damage4=(int)damage4;
		damage4=damage4/100;
		fprintf(dest, "%.2f %.2f %.2f %.2f", damage1, damage2, damage3, damage4);
	fclose(sursa);
	fclose(dest);
	return 0;
	}
