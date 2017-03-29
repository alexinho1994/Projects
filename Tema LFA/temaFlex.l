/*GRAMENI STERE-ALEXANDRE 333CC*/
%s VALORI
%{
	int nrSeparatori = 0;  /*nr de separatori din numele de camp*/
	char* a;
	int valoare = 0;
%}

Nume	[^\t\n/]*
NumedeCamp	{Nume}"/"
Valoare		[^\t\n ]*
Separatori	[\t\n]

%%

<INITIAL>{NumedeCamp}		{ nrSeparatori++;      /*daca gasesc un /, cresc nr lor si retin sirul daca este primul*/
				  if(nrSeparatori == 1)
					{
					yytext[yyleng-1] = ':';
				  	a = malloc(yyleng+1);
					strcpy(a, yytext);
					}
				 }
<INITIAL>{Nume}			{ if(nrSeparatori == 2)
					{
					printf("%s ", a);  /*daca am gasit un nume de camp valid, il afisez si caut valoarea*/
				  	BEGIN(VALORI);
					}
				  else ;
				}
<INITIAL>{Separatori}		{ nrSeparatori = 0; }    /*daca gasesc un separator, numele de camp nu este valid*/

<VALORI>{Separatori}		{ if(valoare == 1)
					{
					valoare = 0;
					printf("\n");        /*daca am gasit valoarea si un separator, caut iar nume de camp*/
					BEGIN(INITIAL); 
					}}
<VALORI>{Valoare}		{
				 printf("%s", yytext);
				 nrSeparatori = 0;       /*am gasit valoarea, caut separatori*/
				 valoare = 1;
				 }
<VALORI>[ ]			{ printf("|"); }

%%
char **fileList;
unsigned int currentFile = 0;
unsigned int fileNr;

main(int argc, char **argv)
{
	FILE *fisier; 
	fileList = argv + 1;
	fileNr = argc - 1;
	while(currentFile < fileNr)
	{
		fisier = fopen(fileList[currentFile], "r");
		yyin = fisier;
		yylex();
		fclose(yyin);
		currentFile++;
	}
}
int yywrap()
{
	return 1;
}
