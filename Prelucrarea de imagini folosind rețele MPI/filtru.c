#include<mpi.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int* vecini;
int parent = -1;
int nrImagini;
int filtru;
int h, w;
int** matrix;
int liniiPrelucrate = 0;
int** liniiVecini;
int nrCopii;


void final(int rank, int nrVecini)
{
	int i;
	int x=1;
	MPI_Status status;
	if(rank != 0)
		MPI_Recv(&i, 1, MPI_INT, MPI_ANY_SOURCE, 10, MPI_COMM_WORLD, &status);
	for(i = 0; i<nrVecini; i++)
	{
		MPI_Send(&i, 1, MPI_INT, vecini[i], 10, MPI_COMM_WORLD);
	}
	for(i = 0; i<nrVecini; i++)
	{
		int nr;
		MPI_Recv(&nr, 1, MPI_INT, vecini[i], 10, MPI_COMM_WORLD, &status);
		MPI_Recv(&liniiVecini[x][0], nr*2, MPI_INT, vecini[i], 10, MPI_COMM_WORLD, &status);
		//printf("%d %d %d\n", rank, liniiVecini[0][0], liniiVecini[0][1]);
		x+=nr;		
	}
	if(rank!=0)
	{
		MPI_Send(&nrCopii, 1, MPI_INT, parent, 10, MPI_COMM_WORLD);
		MPI_Send(&liniiVecini[0][0], nrCopii*2, MPI_INT, parent, 10, MPI_COMM_WORLD);
	}
}

void totiCopiii(int rank, int nrVecini)
{
	int i;
	MPI_Status status;
	if(nrVecini == 0)
	{
		nrCopii = 1;
		MPI_Send(&nrCopii, 1, MPI_INT, parent, 8, MPI_COMM_WORLD);
		int j;
		int* data = (int*)malloc(nrCopii*2*sizeof(int));
		liniiVecini = (int**)malloc(nrCopii*sizeof(int*));
		for(j=0;j<nrCopii;j++)
			liniiVecini[j] = &(data[2*j]);
		liniiVecini[0][0] = rank;
		liniiVecini[0][1] = liniiPrelucrate;
	}
	else
	{
		int nr = 0;
		int x, j;
		for(i = 0; i<nrVecini; i++)
		{
			MPI_Recv(&x, 1, MPI_INT, vecini[i], 8, MPI_COMM_WORLD, &status);
			nr+=x;
		}
		nr++;
		nrCopii = nr;
		int* data = (int*)malloc(nr*2*sizeof(int));
		liniiVecini = (int**)malloc(nr*sizeof(int*));
		for(j=0;j<nr;j++)
			liniiVecini[j] = &(data[2*j]);
		liniiVecini[0][0] = rank;
		liniiVecini[0][1] = liniiPrelucrate;
		if(rank!=0)
			MPI_Send(&nr, 1, MPI_INT, parent, 8, MPI_COMM_WORLD);
	}
}




void receiveMatrix(int rank, int nrVecini)
{
	int i;
	MPI_Status status;
	if(nrVecini == 0)
		MPI_Send(&matrix[1][1], h*w, MPI_INT, parent, 7, MPI_COMM_WORLD);
	else
	{
		int height= h;
		int startH = 1;
		for(i = 0; i<nrVecini; i++)
		{
			int sendH = height/(nrVecini-i);
			height-=sendH;
			MPI_Recv(&matrix[startH][0], sendH*w, MPI_INT, vecini[i], 7, MPI_COMM_WORLD, &status);
			startH+=sendH;
		}
		if(rank != 0)
		{
			MPI_Send(&matrix[1][1], h*w, MPI_INT, parent, 7, MPI_COMM_WORLD);
		}
	}
}

void aplyFilter(int nrVecini)
{
	if(nrVecini == 0)
	{
		int i, j;
		int* data = (int*)malloc((h+2)*(w+2)*sizeof(int));
		int** matrixF = (int**)malloc((h+2)*sizeof(int*));
		for(i=0;i<h+2;i++)
			matrixF[i] = &(data[(w+2)*i]);
		for(i = 1; i<=h; i++)
			for(j = 1; j<=w; j++)
			{
				if(filtru == 1)
					matrixF[i][j] = (matrix[i-1][j-1] + matrix[i-1][j]+matrix[i-1][j+1]+matrix[i][j-1]+matrix[i][j]+matrix[i][j+1]+matrix[i+1][j-1]+matrix[i+1][j]+matrix[i+1][j+1])/9;
				if(filtru == 2)
					matrixF[i][j] = (matrix[i-1][j-1] + 2*matrix[i-1][j]+matrix[i-1][j+1]+2*matrix[i][j-1]+4*matrix[i][j]+2*matrix[i][j+1]+matrix[i+1][j-1]+2*matrix[i+1][j]+matrix[i+1][j+1])/16;
				if(filtru == 3)
					matrixF[i][j] = (11*matrix[i][j] -2*matrix[i-1][j]-2*matrix[i][j-1]-2*matrix[i][j+1]-2*matrix[i+1][j])/3;
				if(filtru == 4)
					matrixF[i][j] = (9*matrix[i][j]-matrix[i-1][j-1] - matrix[i-1][j]-matrix[i-1][j+1]-matrix[i][j-1]-matrix[i][j+1]-matrix[i+1][j-1]-matrix[i+1][j]-matrix[i+1][j+1]);
				if(matrixF[i][j]<0)
					matrixF[i][j] = 0;
				if(matrixF[i][j]>255)
					matrixF[i][j] = 255;
			}
		for(i = 1; i<=h; i++)
			for(j = 1; j<=w; j++)
				matrix[i][j]= matrixF[i][j];
		liniiPrelucrate +=h;
	}
}

void sendMatrix(int rank, int nrVecini)
{
	int i;
	MPI_Status status;
	if(rank != 0)
		MPI_Recv(&matrix[0][0], (h+2)*(w+2), MPI_INT, MPI_ANY_SOURCE, 6, MPI_COMM_WORLD, &status);
	int height= h;
	int startH = 1;
	for(i =0; i<nrVecini; i++)
	{
		int sendH = height/(nrVecini-i);
		height-=sendH;
		MPI_Send(&matrix[startH-1][0], (sendH+2)*(w+2), MPI_INT, vecini[i], 6, MPI_COMM_WORLD);
		startH+=sendH;
	}
}

void createMatrix(int rank)
{
	int i;
	int* data = (int*)malloc((h+2)*(w+2)*sizeof(int));
	matrix = (int**)malloc((h+2)*sizeof(int*));
	for(i=0;i<h+2;i++)
		matrix[i] = &(data[(w+2)*i]);
	if(rank == 0)
	{
		for(i = 0; i<h+2; i++)
		{
			matrix[i][0] = 0;
			matrix[i][w+1] = 0;
		}
		for(i = 0; i<w+2; i++)
		{
			matrix[0][i] = 0;
			matrix[h+1][i] = 0;
		}
	}
}

void sendHeight(int rank, int nrVecini)
{
	int i;
	MPI_Status status;
	if(rank != 0)
		MPI_Recv(&h, 1, MPI_INT, MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, &status);
	int height= h;
	for(i = 0; i<nrVecini; i++)
	{
		int sendH = height/(nrVecini-i);
		height-=sendH;
		MPI_Send(&sendH, 1, MPI_INT, vecini[i], 5, MPI_COMM_WORLD);
	}
}

void sendWidth(int rank, int nrVecini)
{
	int i;
	MPI_Status status;
	if(rank != 0)
		MPI_Recv(&w, 1, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &status);

	for(i = 0; i<nrVecini; i++)
		MPI_Send(&w, 1, MPI_INT, vecini[i], 4, MPI_COMM_WORLD);
}

void setFiltru(int rank, int nrVecini)
{
	int i;
	MPI_Status status;
	if(rank != 0)
		MPI_Recv(&filtru, 1, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);

	for(i = 0; i<nrVecini; i++)
		MPI_Send(&filtru, 1, MPI_INT, vecini[i], 3, MPI_COMM_WORLD);
}

void numarImagini(int rank, int nrVecini)
{
	int i;
	MPI_Status status;
	if(rank != 0)
		MPI_Recv(&nrImagini, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);

	for(i = 0; i<nrVecini; i++)
		MPI_Send(&nrImagini, 1, MPI_INT, vecini[i], 2, MPI_COMM_WORLD);
}

void parinte(int rank, int nrVecini)
{
	MPI_Status status;
	MPI_Request *send =(MPI_Request*)malloc(nrVecini*sizeof(MPI_Request));
	int temp = -1, i;

	if(rank != 0)
	{
		MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
	}

	if(rank!= 0 && temp !=-1 && parent == -1)
		parent = temp;

	for(i = 0; i<nrVecini; i++)
		if(parent != vecini[i])
		{
			MPI_Isend(&rank, 1, MPI_INT, vecini[i], 0, MPI_COMM_WORLD, send+i);
			MPI_Wait(send+i, &status);
		}			
}

void arbore(int rank, int nrVecini)
{
	MPI_Status status;
	MPI_Request *recv =(MPI_Request*)malloc(nrVecini*sizeof(MPI_Request));
	MPI_Request *send =(MPI_Request*)malloc(nrVecini*sizeof(MPI_Request));
	int temp, i;
	if(rank !=0)
	{	
		for(i=0;i<nrVecini; i++)
		{
			MPI_Isend(&parent, 1, MPI_INT, vecini[i], 1, MPI_COMM_WORLD, send+i);
			MPI_Wait(send+i, &status);
		}
	}
	for(i=0;i<nrVecini; i++)
	{
		if(vecini[i]!=parent)
			MPI_Irecv(&temp, 1, MPI_INT, vecini[i], 1, MPI_COMM_WORLD, recv+i); 
	}

	for(i=0; i<nrVecini; i++)
		if(vecini[i]!=parent)
		{
			MPI_Wait(recv+i, &status); 
			if(temp != rank)
				vecini[i] = -1;
		}
}

int allign(int nrVecini)
{
	int i, j;
	for(i=0; i<nrVecini; i++)
		if(vecini[i] == -1 || vecini[i]==parent)
		{
			for(j = i+1; j<nrVecini; j++)
			{
				int aux = vecini[j];
				vecini[j] = vecini[j-1];
				vecini[j-1] = aux;
			}
			nrVecini--;
			i--;
		}
	return nrVecini;
}


int main(int argc, char* argv[])
{
	int rank;
	int nProcesses;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	FILE* topologie;
	topologie = fopen(argv[1], "r");
	if(topologie == NULL)
	{
		fprintf(stderr, "%d: Fisierul nu poate fi deschis\n", rank);
		MPI_Finalize();
		return 1;
	}

	int i, j;
	char line[200], *vecin;
	
	for(i=0;i<=rank;i++)
	{
		fgets(line, nProcesses*3, topologie);
	}

	vecini = (int*)calloc(strlen(line)/2, sizeof(int));
	i = 0;
	char* separatori = ": \n";
	vecin = strtok(line, separatori);
	while(vecin!=NULL)
	{
		vecin = strtok(NULL, separatori);
		if(vecin!=NULL)
		{
			vecini[i] = atoi(vecin);
			i++;
		}
	}

	fclose(topologie);

	MPI_Barrier(MPI_COMM_WORLD);
	parinte(rank, i);
	MPI_Barrier(MPI_COMM_WORLD);
	arbore(rank, i);
	MPI_Barrier(MPI_COMM_WORLD);
	i = allign(i);

	FILE *imagini;
	if(rank == 0)
	{
		imagini = fopen(argv[2], "r");
		fscanf(imagini, "%d\n", &nrImagini);
	}

	numarImagini(rank, i);

	char b[25], c[25];

	while(nrImagini)
	{
		if(rank == 0)
		{
			char a[25];
			fscanf(imagini, "%s %s %s\n", a, b, c);
			if(strcmp(a, "smooth") == 0) 
				filtru = 1;
			if(strcmp(a, "blur") == 0) 
				filtru = 2;
			if(strcmp(a, "sharpen") == 0) 
				filtru = 3;
			if(strcmp(a, "mean_removal") == 0) 
				filtru = 4;
		}
		setFiltru(rank, i);
		
		if(rank == 0)
		{		
			FILE* imagine;
			FILE* imagine2;
			imagine = fopen(b, "r");
			imagine2 = fopen(c, "w");
			fgets(line, 5, imagine);
			fprintf(imagine2, "%s", line);
			fgets(line, 200, imagine);
			fprintf(imagine2, "%s", line);
			fscanf(imagine, "%d %d\n", &w, &h);
			fprintf(imagine2, "%d %d\n", w, h);
			fgets(line, 5, imagine);
			fprintf(imagine2, "%s", line);
			sendWidth(rank, i);
			sendHeight(rank, i);
			createMatrix(rank);
			int m, n;
			for(m = 1; m<=h; m++)
				for(n = 1; n<=w; n++)
					fscanf(imagine, "%d", &matrix[m][n]);
			sendMatrix(rank, i);
			aplyFilter(i);
			receiveMatrix(rank, i);
			for(m = 1; m<=h; m++)
			{
				for(n = 1; n<=w; n++)
					fprintf(imagine2, "%d ", matrix[m][n]);
				fprintf(imagine2, "\n");
			}
			fclose(imagine);
			fclose(imagine2);
			
		}
		else
		{
			sendWidth(rank, i);
			sendHeight(rank, i);
			createMatrix(rank);
			sendMatrix(rank, i);
			aplyFilter(i);
			receiveMatrix(rank, i);
		}
		nrImagini--;
	}

	if(rank==0)
		fclose(imagini);

	totiCopiii(rank, i);
	MPI_Barrier(MPI_COMM_WORLD);
	final(rank, i);
	
	if(rank == 0)
	{
		for(i = 0; i<nrCopii; i++)
			for(j=i+1; j<nrCopii; j++)
				if(liniiVecini[i][0]>liniiVecini[j][0])
				{
				int aux = liniiVecini[i][0];
				liniiVecini[i][0]=liniiVecini[j][0];
				liniiVecini[j][0]=aux;
				
				aux = liniiVecini[i][1];
				liniiVecini[i][1]=liniiVecini[j][1];
				liniiVecini[j][1]=aux;
				}
		FILE* statistica;
		statistica = fopen(argv[3], "w");
		for(j = 0; j<nrCopii; j++)
			fprintf(statistica, "%d: %d\n", liniiVecini[j][0], liniiVecini[j][1]);
	}

	MPI_Finalize();
	return 0;
}
