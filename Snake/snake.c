#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <sys/select.h>

#define FOREVER 	1
#define INIT_ROW 	10
#define INIT_COL 	20
#define SELECT_EVENT	1
#define SELECT_NO_EVENT	0

int generare(int max)
{
	int random_number;
	srand(time(NULL));
	random_number=rand()%max;
	return random_number;
}
int faraobstacole(int nrows, int ncols, int row, int col)
{
	int new_row, new_col,i, aux, miscare,die=1,hranarow,hranacol,hrana, milisec=1000000;
	int ok, digerarerow[25]={0}, digerarecol[25]={0}, x=0, j, scor=0, viteza=0;
	long max=nrows*ncols;
	long rowmax[max];
	long colmax[max];
	long lungime;
	int nfds, sel;
	char c;
	fd_set read_descriptors;
	struct timeval timeout;
	nfds=1;
	FD_ZERO(&read_descriptors);
	FD_SET(0, &read_descriptors);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	clear();
	for(i=1;i<nrows;i++)
		{
		move(i, 0);
		addch('x');
		move(i, ncols-1);
		addch('x');
		}
	for(i=0;i<ncols;i++)
		{
		move(1, i);
		addch('x');
		move(nrows-1, i);
		addch('x');
		}
	move(row, col);
	addch('@');
	rowmax[1]=row;
	colmax[1]=col;
	move(row, col+1);
	addch('o');
	rowmax[2]=row;
	colmax[2]=col+1;
	move(row, col+2);
	addch('o');
	rowmax[3]=row;
	colmax[3]=col+2;
	move(row, col+3);
	addch('o');
	rowmax[4]=row;
	colmax[4]=col+3;
	move(row, col+4);
	addch('o');
	rowmax[5]=row;
	rowmax[5]=col+4;
	lungime=5;
	hranarow=generare(nrows-2);
	while(hranarow==row || hranarow==1 || hranarow==0)	
		hranarow=generare(nrows-2);
	hranacol=generare(ncols-2);
	while(hranacol==0)
		hranacol=generare(ncols-2);
	move(hranarow, hranacol);
	addch('*');
	hrana=1;
	refresh();
	while (FOREVER && die) {
		move(0,0);
		addstr("Scor: ");
		move(0,6);
		printw("%d", scor);
		if(hrana==0)
			{
			hranarow=generare(nrows-2);
			hranacol=generare(ncols-2);
			if(hranarow<=1 || hranacol<=0)
				ok=0;
			for(i=1;i<=lungime;i++)
				if(hranarow==rowmax[i] && hranacol==colmax[i])
					ok=0;
			}
		while(ok==0)
			{
			ok=1;
			hranarow=generare(nrows-2);
			hranacol=generare(ncols-2);
			if(hranarow<=1 || hranacol<=1)
				ok=0;
			for(i=1;i<=lungime;i++)
				if(hranarow==rowmax[i] && hranacol==colmax[i])
					ok=0;
			
			}
		move(hranarow, hranacol);
		addch('*');
		hrana=1;
		refresh();
		miscare=0;
		sel = select(nfds, &read_descriptors, NULL, NULL, &timeout);
		if(sel==SELECT_EVENT)
			{
			c = getchar();

			if (tolower(c) == 'q') {
				return 0;
			}	
			switch (tolower(c)) {
			case 'a':
				new_row = row;
				if (col > 1)
					{
					new_col = col - 1;
					miscare=1;
					}
				if(new_row==rowmax[2] && new_col==colmax[2])
					miscare=0;
				if(col==1) die=0;
				break;
			
			case 'd':
				new_row = row;
				if (col + 1 < ncols-1)
					{
					miscare=1;
					new_col = col + 1;
					}
				if(new_row==rowmax[2] && new_col==colmax[2])
					miscare=0;
				if(col+1==ncols-1) die=0;
				break;
			
			case 'w':
				if (row > 2)
					{
					miscare=1;
					new_row = row - 1;
					}
				new_col = col;
				if(new_row==rowmax[2] && new_col==colmax[2])
					miscare=0;
				if(row==2) die=0;
				break;
	
			case 's':
				if (row + 1 < nrows-1)
					{
					miscare=1;
					new_row = row + 1;
					}
				new_col = col;
				if(new_row==rowmax[2] && new_col==colmax[2])
					miscare=0;
				if(row+1==nrows-1) die=0;
				break;
			}
			}
		if(sel==SELECT_NO_EVENT)
			{
			if(rowmax[1]==rowmax[2] && colmax[1]==colmax[2]+1);
				{
				new_row = row;
				miscare=1;
				new_col = col + 1;
				if(col+1==ncols-1) die=0;
				}
			if(rowmax[1]==rowmax[2] && colmax[1]+1==colmax[2])
				{
				new_row = row;
				new_col = col - 1;
				miscare=1;
				if(col==1) die=0;
				}
			if(rowmax[1]+1==rowmax[2] && colmax[1]==colmax[2])
				{
				miscare=1;
				new_row = row - 1;
				new_col = col;
				if(row==2) die=0;
				}
			if(rowmax[1]==rowmax[2]+1 && colmax[1]==colmax[2])
				{
				miscare=1;
				new_row = row + 1;
				new_col = col;
				if(row+1==nrows-1) die=0;
				}
			}
		
		if(miscare)
			for(i=0;i<=x;i++)
				if(rowmax[lungime]==digerarerow[i] && colmax[lungime]==digerarecol[i])
					{
					lungime++;
					for(j=i;j<x;j++)
						{
						digerarerow[j]=digerarerow[j+1];
						digerarecol[j]=digerarecol[j+1];
						}
					x--;
					}
		for(i=4;i<lungime;i++)
			if(new_row==rowmax[i] && new_col==colmax[i])
				die=0;
		if(die==0) miscare=0;
		if(miscare)
			{
			for(i=1;i<=lungime;i++)
				{
				move(rowmax[i], colmax[i]);
				addch(' ');
				}
			for(i=1;i<=lungime;i++)
				{
				aux=new_row;
				new_row=rowmax[i];
				rowmax[i]=aux;
				aux=new_col;
				new_col=colmax[i];
				colmax[i]=aux;			
				}
			for(i=1;i<=lungime;i++)
				{
				move(rowmax[i], colmax[i]);
				addch('o');
				for(j=0;j<=x;j++)
					if(rowmax[i]==digerarerow[j] && colmax[i]==digerarecol[j])
						{
						move(rowmax[i], colmax[i]);
						addch('@');
						}
				}
			}
		row=rowmax[1];
		col=colmax[1];
		
		if(miscare)
			{
			move(row,col);
			addch('@');
			}
		if(rowmax[1]==hranarow && colmax[1]==hranacol)
			{
			hrana=0;
			digerarerow[x]=hranarow;
			digerarecol[x]=hranacol;
			x++;
			scor++;
			viteza++;
			}
		refresh();
		FD_SET(0, &read_descriptors);
		if(viteza%5==0)
			if(scor<46 && viteza!=0)
				{
				milisec=milisec-90000;
				viteza=0;
				}
		timeout.tv_sec=0;
		timeout.tv_usec=milisec;
	}
	if(die==0)
		{
		clear();
		move(12, 30);
		addstr("Game Over");
		move(13, 31);
		addstr("Scor: ");
		move(13, 37);
		printw("%d", scor);
		move(14, 20);
		addstr("Apasati orice tasta pentru a continua");
		refresh();
		getchar();
		}
return 0;
}
void ajutor()
{
	char c;
	while(FOREVER)
		{
		
		if(tolower(c)=='q')
			{
			break;
			}
		clear();
		mvaddstr(5, 20, "Puteti sa mutati sarpele folosind tastele:");
		mvaddstr(8, 20, "A - stanga");
		mvaddstr(11, 20, "D - dreapta");
		mvaddstr(14, 20, "W - sus");
		mvaddstr(17, 20, "S - jos");
		mvaddstr(20, 20, "Pentru iesire, apasati tasta Q.");
		refresh();
		c=getchar();
		}
}
void cuobstacole(int nrows, int ncols, int row, int col, int obs)
{
	int new_row, new_col,i, aux, miscare,die=1,hranarow,hranacol,hrana=0, milisec=1000000;
	int ok, digerarerow[25]={0}, digerarecol[25]={0}, x=0, j, scor=0, k, viteza=0;
	long max=nrows*ncols;
	long rowmax[max];
	long colmax[max];
	long lungime;
	int obstacol1[21], obstacol2[21];
	int nfds, sel;
	char c;
	fd_set read_descriptors;
	struct timeval timeout;
	nfds=1;
	FD_ZERO(&read_descriptors);
	FD_SET(0, &read_descriptors);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	clear();
	for(i=1;i<nrows;i++)
		{
		move(i, 0);
		addch('x');
		move(i, ncols-1);
		addch('x');
		}
	for(i=0;i<ncols;i++)
		{
		move(1, i);
		addch('x');
		move(nrows-1, i);
		addch('x');
		}
	move(row, col);
	addch('@');
	rowmax[1]=row;
	colmax[1]=col;
	move(row, col+1);
	addch('o');
	rowmax[2]=row;
	colmax[2]=col+1;
	move(row, col+2);
	addch('o');
	rowmax[3]=row;
	colmax[3]=col+2;
	move(row, col+3);
	addch('o');
	rowmax[4]=row;
	colmax[4]=col+3;
	move(row, col+4);
	addch('o');
	rowmax[5]=row;
	rowmax[5]=col+4;
	lungime=5;
	for(i=1;i<=obs;i++)
		{
		obstacol1[i]=generare(nrows-1);
		obstacol2[i]=generare(ncols-1);
		if(obstacol1[i]==row)
			k=0;
		if(obstacol1[i]<=1 || obstacol2[i]<=0)
			k=0;
		for(j=1;j<=lungime;j++)
			if(obstacol1[i]==rowmax[j] && obstacol2[i]==colmax[j])
				k=0;
		for(j=1;j<i;j++)
			if(obstacol1[i]==obstacol1[j] && obstacol2[i]==obstacol2[j])
				k=0;
		while(k==0)
			{
			k=1;
			obstacol1[i]=generare(nrows-1);
			obstacol2[i]=generare(ncols-1);
			if(obstacol1[i]==row)
				k=0;
			if(obstacol1[i]<=1 || obstacol2[i]<=1)
				k=0;
			for(j=1;j<=lungime;j++)
				if(obstacol1[i]==rowmax[j] && obstacol2[i]==colmax[j])
					k=0;
			for(j=1;j<i;j++)
				if(obstacol1[i]==obstacol1[j] && obstacol2[i]==obstacol2[j])
					k=0;
			}
		move(obstacol1[i], obstacol2[i]);
		addch('#');
		}
	move(0, 58);
	addstr("Obstacole Generate: ");
	move(0, 78);
	printw("%d", obs);
	refresh();
	while (FOREVER && die) {
		move(0,0);
		addstr("Scor: ");
		move(0,6);
		printw("%d", scor);
		if(hrana==0)
			{
			hranarow=generare(nrows-2);
			hranacol=generare(ncols-2);
			if(hranarow<=1 || hranacol<=0)
				ok=0;
			for(i=1;i<=lungime;i++)
				if(hranarow==rowmax[i] && hranacol==colmax[i])
					ok=0;
			for(i=1;i<=obs;i++)	
				if(hranarow==obstacol1[i] && hranacol==obstacol2[i])
					ok=0;			
			}
		while(ok==0)
			{
			ok=1;
			hranarow=generare(nrows-2);
			hranacol=generare(ncols-2);
			if(hranarow<=1 || hranacol<=1)
				ok=0;
			for(i=1;i<=lungime;i++)
				if(hranarow==rowmax[i] && hranacol==colmax[i])
					ok=0;
			for(i=1;i<=obs;i++)	
				if(hranarow==obstacol1[i] && hranacol==obstacol2[i])
					ok=0;
			}
		move(hranarow, hranacol);
		addch('*');
		hrana=1;
		refresh();
		miscare=0;
		sel = select(nfds, &read_descriptors, NULL, NULL, &timeout);
		if(sel==SELECT_EVENT)
			{
			c = getchar();
	
			if (tolower(c) == 'q') {
				break;
			}	
			switch (tolower(c)) {
			case 'a':
				new_row = row;
				if (col > 1)
					{
					new_col = col - 1;
					miscare=1;
					}
				if(new_row==rowmax[2] && new_col==colmax[2])
					miscare=0;
				if(col==1) die=0;
				break;
			
			case 'd':
				new_row = row;
				if (col + 1 < ncols-1)
					{
					miscare=1;
					new_col = col + 1;
					}
				if(new_row==rowmax[2] && new_col==colmax[2])
					miscare=0;
				if(col+1==ncols-1) die=0;
				break;
			
			case 'w':
				if (row > 2)
					{
					miscare=1;
					new_row = row - 1;
					}
				new_col = col;
				if(new_row==rowmax[2] && new_col==colmax[2])
					miscare=0;
				if(row==2) die=0;
				break;
	
			case 's':
				if (row + 1 < nrows-1)
					{
					miscare=1;
					new_row = row + 1;
					}
				new_col = col;
				if(new_row==rowmax[2] && new_col==colmax[2])
					miscare=0;
				if(row+1==nrows-1) die=0;
				break;
			}
			}
		if(sel==SELECT_NO_EVENT)
			{
			if(rowmax[1]==rowmax[2] && colmax[1]==colmax[2]+1);
				{
				new_row = row;
				miscare=1;
				new_col = col + 1;
				if(col+1==ncols-1) die=0;
				}
			if(rowmax[1]==rowmax[2] && colmax[1]+1==colmax[2])
				{
				new_row = row;
				new_col = col - 1;
				miscare=1;
				if(col==1) die=0;
				}
			if(rowmax[1]+1==rowmax[2] && colmax[1]==colmax[2])
				{
				miscare=1;
				new_row = row - 1;
				new_col = col;
				if(row==2) die=0;
				}
			if(rowmax[1]==rowmax[2]+1 && colmax[1]==colmax[2])
				{
				miscare=1;
				new_row = row + 1;
				new_col = col;
				if(row+1==nrows-1) die=0;
				}
			}
		if(miscare)
			for(i=0;i<=x;i++)
				if(rowmax[lungime]==digerarerow[i] && colmax[lungime]==digerarecol[i])
					{
					lungime++;
					for(j=i;j<x;j++)
						{
						digerarerow[j]=digerarerow[j+1];
						digerarecol[j]=digerarecol[j+1];
						}
					x--;
					}
		for(i=4;i<lungime;i++)
			if(new_row==rowmax[i] && new_col==colmax[i])
				die=0;
		if(die==0) miscare=0;
		if(miscare)
			{
			for(i=1;i<=lungime;i++)
				{
				move(rowmax[i], colmax[i]);
				addch(' ');
				}
			for(i=1;i<=lungime;i++)
				{
				aux=new_row;
				new_row=rowmax[i];
				rowmax[i]=aux;
				aux=new_col;
				new_col=colmax[i];
				colmax[i]=aux;			
				}
			for(i=1;i<=lungime;i++)
				{
				move(rowmax[i], colmax[i]);
				addch('o');
				for(j=0;j<=x;j++)
					if(rowmax[i]==digerarerow[j] && colmax[i]==digerarecol[j])
						{
						move(rowmax[i], colmax[i]);
						addch('@');
						}
				}
			}
		row=rowmax[1];
		col=colmax[1];
		
		if(miscare)
			{
			move(row,col);
			addch('@');
			}
		if(rowmax[1]==hranarow && colmax[1]==hranacol)
			{
			hrana=0;
			digerarerow[x]=hranarow;
			digerarecol[x]=hranacol;
			x++;
			scor++;
			viteza++;
			}
		for(i=1;i<=obs;i++)
			if(rowmax[1]==obstacol1[i] && colmax[1]==obstacol2[i])
				die=0;
		refresh();
		FD_SET(0, &read_descriptors);
		if(viteza==5)
			if(scor<45)
				{
				milisec=milisec-90000;
				viteza=0;
				}
		timeout.tv_sec=0;
		timeout.tv_usec=milisec;
	}
	if(die==0)
		{
		clear();
		move(12, 30);
		addstr("Game Over");
		move(13, 31);
		addstr("Scor: ");
		move(13, 37);
		printw("%d", scor);
		move(14, 20);
		addstr("Apasati orice tasta pentru a continua");
		refresh();
		getchar();
		}	
}

int main(void)
{
	int row = INIT_ROW, col = INIT_COL;
	int nrows, ncols;
	char c;
	int obs;
	WINDOW *wnd = initscr();
	getmaxyx(wnd, nrows, ncols);
	nrows=23;
	ncols=79;
	clear();
	noecho();
	cbreak();	
	curs_set(0);
	mvaddstr(7, 20, "Apasati [S] pentru a incepe fara obstacole");
	mvaddstr(13, 20, "Apasati [H] pentru ajutor");
	mvaddstr(16, 20, "Apasati [Q] pentru a iesi");
	mvaddstr(10, 20, "Apasati [O] pentru a incepe cu obstacole");
	refresh();
	c=getchar();
	while(FOREVER)
		{
		if(tolower(c)=='q')
			{
			break;
			}
		if(tolower(c)=='s')
			faraobstacole(nrows, ncols, row, col);
		if(tolower(c)=='h')
			ajutor();
		if(tolower(c)=='o')
			{
			obs=generare(15);
			while(obs<8)
				obs=generare(15);
			cuobstacole(nrows, ncols, row, col, obs);
			}
		clear();
		mvaddstr(7, 20, "Apasati [S] pentru a incepe fara obstacole");
		mvaddstr(13, 20, "Apasati [H] pentru ajutor");
		mvaddstr(16, 20, "Apasati [Q] pentru a iesi");
		mvaddstr(10, 20, "Apasati [O] pentru a incepe cu obstacole");
		refresh();
		c=getchar();
		}
	endwin();
	return 0;
}
