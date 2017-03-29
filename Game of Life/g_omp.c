#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>

int main(int argc, char* argv[])
{
	FILE *sursa, *dest;
	sursa=fopen(argv[1], "r");
	dest=fopen(argv[3], "w");
	int linii, coloane;
	char c;
	
	//citesc dimensiunea matricii
	fscanf(sursa, "%d %d\n", &linii, &coloane);
	int i, j;

	//aloc memorie pentru matrici
	int **m1, **m2;
	m1 = (int**) malloc ((linii+2)*sizeof(int*));
	m2 = (int**) malloc ((linii+2)*sizeof(int*));
	for(i=0;i<=linii+1;i++)
	{
		m1[i] = (int*) calloc ((coloane+2), sizeof(int));
		m2[i] = (int*) calloc ((coloane+2), sizeof(int));
	}

	//citesc matricea
	for(i=1;i<=linii;i++)
		for(j=1;j<=coloane;j++)
		{
			fscanf(sursa, "%c ", &c);
			if(c=='.')
			{
				m1[i][j]=0;
				m2[i][j]=0;
			}
			if(c=='X')
			{
				m1[i][j]=1;
				m2[i][j]=1;
			}
		}
	#pragma omp parallel for shared(m1) private(i)
	for(i=1;i<=linii;i++)
	{
		m1[i][0]=m1[i][coloane];
		m1[i][coloane+1]=m1[i][1];
	}
	#pragma omp parallel for shared(m1) private(i)
	for(i=1;i<=coloane;i++)
	{
		m1[0][i]=m1[linii][i];
		m1[linii+1][i]=m1[1][i];
	}
	m1[0][0] = m1[linii][coloane];
	m1[0][coloane+1] = m1[linii][1];
	m1[linii+1][0] = m1[1][coloane];
	m1[linii+1][coloane+1] = m1[1][1];
	int iteratii = atoi(argv[2]);
	int it;

	//primul for e pentru numarul de iteratii, dupa pentru vecini
	for(it=0;it<iteratii;it++)
	{
		#pragma omp parallel for collapse(2) shared(m1, m2) private(i, j)
		for(i=1;i<=linii;i++)
			for(j=1;j<=coloane;j++)
			{
				int alive=0;
				int dead=0;
				if(m1[i-1][j-1] == 0)
					dead++;
				else alive++;
				if(m1[i-1][j] == 0)
					dead++;
				else alive++;
				if(m1[i-1][j+1] == 0)
					dead++;
				else alive++;
				if(m1[i][j-1] == 0)
					dead++;
				else alive++;
				if(m1[i][j+1] == 0)
					dead++;
				else alive++;
				if(m1[i+1][j-1] == 0)
					dead++;
				else alive++;
				if(m1[i+1][j] == 0)
					dead++;
				else alive++;
				if(m1[i+1][j+1] == 0)
					dead++;
				else alive++;

				if(alive < 2)
					m2[i][j] = 0;
				if(m1[i][j] == 1 && alive>=2 && alive<=3)
					m2[i][j] = 1;
				if(alive > 3)
					m2[i][j] = 0;
				if(m1[i][j] == 0 && alive == 3)
					m2[i][j] = 1;
			}

		//copiez a doua matrice in prima
		#pragma omp parallel for collapse(2) private(i, j) shared(m1)
		for(i=1;i<=linii;i++)
			for(j=1;j<=coloane;j++)
				m1[i][j]=m2[i][j];

		//bordez matricea
		#pragma omp parallel for private(i, j) shared(m1, m2)
		for(i=1;i<=linii;i++)
		{
			m1[i][0]=m1[i][coloane];
			m1[i][coloane+1]=m1[i][1];
		}
		#pragma omp parallel for private(i, j) shared(m1, m2)
		for(i=1;i<=coloane;i++)
		{
			m1[0][i]=m1[linii][i];
			m1[linii+1][i]=m1[1][i];
		}
		m1[0][0] = m1[linii][coloane];
		m1[0][coloane+1] = m1[linii][1];
		m1[linii+1][0] = m1[1][coloane];
		m1[linii+1][coloane+1] = m1[1][1];
	}

	//afisez matricea
	for(i=1;i<linii+1;i++)
	{
		for(j=1;j<coloane+1;j++)
			if(m1[i][j]==1)
				fprintf(dest, "X "); 
			else fprintf(dest, ". ");
		fprintf(dest, "\n");
	}
	fclose(sursa);
	fclose(dest);
	return 0;
}	
