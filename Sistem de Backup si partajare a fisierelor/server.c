#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <netdb.h>
#include <fcntl.h>

#define MAX_CLIENTS	25
#define BUFLEN 4096

typedef struct sharedfile
{
	char* nume;
	char* user;
	struct sharedfile *next;
}sharedfiles;

typedef struct upload
{
	char *dest;
	int i;
	struct upload *next;
}uploads;

typedef struct download
{
	char *sursa;
	int i;
	struct download *next;
}downloads;

void adaugaupload(uploads **cap, char* dest)
{
	uploads *nou, *curent;
	nou=(uploads*) malloc (sizeof(uploads));
	nou->dest = (char *) malloc (50*sizeof(char));
	strcpy(nou->dest, dest);
	nou->i=open(dest, O_WRONLY);;
	nou->next=NULL;
	curent = *cap;
	if(*cap==NULL)
		*cap=nou;
	else
	{
		while(curent->next!=NULL)
			curent=curent->next;
		curent->next=nou;
	}
}

int parcurgeUpload(uploads **cap, char* fisier)
{
	uploads *curent;
	curent=*cap;
	if(curent==NULL)
		return 1;
	while(curent!=NULL)
		if(strcmp(curent->dest, fisier)==0)
			return 0;
		else curent=curent->next;
	return 1;
}

int parcurgeDownload(downloads **cap, char* fisier)
{
	downloads *curent;
	curent=*cap;
	if(curent==NULL)
		return 1;
	while(curent!=NULL)
		if(strcmp(curent->sursa, fisier)==0)
			return 0;
		else curent=curent->next;
	return 1;
}

void adaugafisier(sharedfiles **cap, char* name, char* username)
{
	sharedfiles *nou, *curent;
	nou=(sharedfiles*)malloc(sizeof(sharedfiles));
	nou->nume=(char*)malloc(25*sizeof(char));
	nou->user=(char*)malloc(25*sizeof(char));
	strcpy(nou->nume, name);
	strcpy(nou->user, username);
	nou->next=NULL;
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

void stergefisier(sharedfiles **cap, char* name, char* username)
{
	sharedfiles *curent;
	curent= *cap;
	if(strcmp(curent->nume, name)==0)
	{
		curent=curent->next;
		*cap=curent;
	}
	else
	{
		while(curent->next!=NULL && strcmp(curent->next->nume, name))
			curent=curent->next;
		if(curent->next!=NULL)
			curent->next=curent->next->next;
	}
}

int findfile(sharedfiles **cap, char* name, char* username)
{
	sharedfiles *curent;
	curent= *cap;
	while(curent!=NULL)
	{
		if(strcmp(curent->nume, name)==0)
			return 1;
		curent=curent->next;
	}
	return 0;
}

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[BUFLEN];
     char *comanda;
     struct sockaddr_in serv_addr, cli_addr;
     int n, i, j;

     FILE *users, *files;
     users=fopen(argv[2], "r");
     files=fopen(argv[3], "r");

     int nrusr;
     fscanf(users, "%d\n", &nrusr);

     char **usr = (char **) malloc ((nrusr)*sizeof(char*));
     for(i=0;i<nrusr;i++)
		{
		usr[i]=(char*) calloc ((BUFLEN), sizeof(char));
		}
     for(i=0;i<nrusr;i++)
		{
		char* usr2 = (char*) malloc (BUFLEN* sizeof(char));
		fgets(usr[i], BUFLEN, users);
		strcpy(usr2, usr[i]);
		usr2=strtok(usr2, " ");
		struct stat st;
		if(stat(usr2, &st) == -1)
			mkdir(usr2, 0777);
		}

     sharedfiles *list;
     uploads *uploadlist;
     downloads *downloadlist;
     downloadlist=NULL;
     list=NULL;
     uploadlist=NULL;

     int nrfiles;
     fscanf(files, "%d\n", &nrfiles);
     for(i=0;i<nrfiles; i++){
	char* fisier = (char*) malloc (50*sizeof(char));
	fgets(fisier, 50, files);
	char *username=strtok(fisier, ":\n");
	char *name=strtok(NULL, ":\n");
	adaugafisier(&list, name, username);
     }

     int logat[26];
     for(i=0;i<26;i++)
	logat[i]=3;

     fd_set read_fds;	
     fd_set tmp_fds;	
     int fdmax, num;

     FD_ZERO(&read_fds);
     FD_ZERO(&tmp_fds);
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     
     portno = atoi(argv[1]);

     memset((char *) &serv_addr, 0, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;	
     serv_addr.sin_port = htons(portno);
     
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) < 0) 
              error("ERROR on binding");
     
     listen(sockfd, MAX_CLIENTS);

     FD_SET(0, &read_fds);
     FD_SET(sockfd, &read_fds);
     fdmax = sockfd;
     int quit=0;

	while (quit==0 || uploadlist !=NULL || downloadlist!=NULL) 
	{
		tmp_fds = read_fds; 
		if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1) 
			error("ERROR in select");
	
		for(i = 0; i <= fdmax; i++) 
		{
			if (FD_ISSET(i, &tmp_fds)) 
			{
				if (i == sockfd) 
				{
					clilen = sizeof(cli_addr);
					if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) == -1) 
					{
						error("ERROR in accept");
					} 
					else 
					{
						FD_SET(newsockfd, &read_fds);
						if (newsockfd > fdmax) 
						{ 
							fdmax = newsockfd;
						}
					}
					printf("Noua conexiunde la %s, port %d, socket_client %d\n ", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), newsockfd);
				}	
				else {
					memset(buffer, 0, BUFLEN);
					if ((n = read(i, buffer, BUFLEN)) <= 0) 
					{
						if (n == 0) 
						{
							printf("Clientul %d s-a deconectat\n", i);
						} else 
						{
							error("ERROR in recv");
						}
						close(i); 
						FD_CLR(i, &read_fds); 
					} 
					
					else { 
						printf ("Am primit de la clientul %d: %s\n", i, buffer);
						comanda = strtok(buffer, " ");
						if(strcmp(comanda, "login") == 0 && i>0)
						{
							char* username = strtok(NULL, " ");
							char* parola = strtok(NULL, " ");
							int k, ok=0;
							for(k=0;k<nrusr;k++)
							{
								char* cont=(char*) malloc(24*sizeof(char));
								strcpy(cont, usr[k]);
								char* username2=strtok(cont, " ");
								char* parola2 = strtok(NULL, " ");
								if(strcmp(username, username2)==0 && strcmp(parola, parola2)==0)
								{
									ok=1;
									break;
								}
							}
							if(ok==1)
							{
								logat[i]=4;
								strcpy(buffer, "Success");
								write(i, buffer, BUFLEN);
							}
							else
							{
								logat[i]--;
								if(logat[i]==0)
								{
									strcpy(buffer, "-8 Brute-force detectat");
									write(i, buffer, BUFLEN);
									close(i);
									FD_CLR(i, &read_fds);
								}
								else
								{
									strcpy(buffer, "-3 User/parola gresita");
									write(i, buffer, BUFLEN);
								}
							}
							continue;	
						}
						if(strcmp(comanda, "logout\n")==0 && i>0)
						{
							strcpy(buffer, "Success");
							write(i, buffer, BUFLEN);
							logat[i]=3;
							continue;
						}
						if(strcmp(comanda, "getuserlist\n")==0 && i>0)
						{
							int k;
							memset(comanda, 0, 25);
							comanda = (char*) malloc(25 * sizeof(char));
							for(k=0;k<nrusr-1;k++)
							{
								char* cont=(char*) malloc(24*sizeof(char));
								strcpy(cont, usr[k]);
								char* username=strtok(cont, " ");
								char* parola = strtok(NULL, " ");
								sprintf(comanda, "%s\n", username);
								strcat(buffer, comanda);
								memset(comanda, 0, 25);
							}
							char* cont=(char*) malloc(24*sizeof(char));
							strcpy(cont, usr[nrusr-1]);
							char* username=strtok(cont, " ");
							char* parola = strtok(NULL, " ");
							sprintf(comanda, "%s", username);
							strcat(buffer, comanda);
							write(i, buffer, BUFLEN);
							continue;
						}
						if(strcmp(comanda, "getfilelist")==0 && i>0)
						{
							char* username = strtok(NULL, " \n");
							int k, ok=0;
							for(k=0;k<=nrusr-1;k++)
							{
								char* cont=(char*) malloc(24*sizeof(char));
								strcpy(cont, usr[k]);
								char* username2=strtok(cont, " ");
								char* parola = strtok(NULL, " ");
								if(strcmp(username, username2)==0)
									ok=1;
							}
							if(ok==0)
							{
								strcpy(buffer, "-11 Utilizator inexistent");
								write(i, buffer, BUFLEN);
								continue;
							}	
							DIR *dir;
							struct dirent *dp;
							struct stat info;
							char * file_name=(char*) malloc (50*sizeof(char));
							char* director = (char*) malloc (30 * sizeof(char));
							strcpy(director,"./");
							strcat(director, username);
							dir = opendir(director);
							memset(comanda, 0, 250);
							comanda = (char*) malloc(250 * sizeof(char));
							for(dp=readdir(dir); dp!=NULL; dp=readdir(dir))
							{
								if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
								{}
								else
								{
								int size=0;
								
								strcpy(file_name, director);
								strcat(file_name, "/");
								strcat(file_name, dp->d_name);
								if(lstat(file_name, &info) >= 0)
									size=info.st_size;	
								char *priv=(char*) malloc(10*sizeof(char));
								strcpy(file_name, dp->d_name);
								if(findfile(&list, file_name, username))
									strcpy(priv, "SHARED");
								else
									strcpy(priv, "PRIVATE");
								sprintf(comanda, "%s        %d %s      %s\n", file_name, size, "bytes",  priv);
								strcat(buffer, comanda);
								memset(comanda, 0, 250);
								}
							}
							write(i, buffer, BUFLEN);
							closedir(dir);
							continue;
						}
						if(strcmp(comanda, "share")==0 && i>0)
						{
							char *fisier=strtok(NULL, "\n");
							char *username = strtok(NULL, " >\n");
							DIR *dir;
							int ok=0;
							struct dirent *dp;
							dir = opendir(username);
							for(dp=readdir(dir); dp!=NULL; dp=readdir(dir))
							{
								if(strcmp(dp->d_name, fisier)==0)
									ok=1;
							}
							if(ok==0)
							{
								strcpy(buffer, "-4 Fisier inexistent");
								write(i, buffer, BUFLEN);
								continue;
							}
							if(findfile(&list, fisier, username))
							{
								strcpy(buffer, "-6 Fisierul este deja partajat");
								write(i, buffer, BUFLEN);
								continue;
							}
							adaugafisier(&list, fisier, username);
							strcpy(buffer, "200 Fisierul ");
							strcat(buffer, "a fost partajat.\n");
							write(i, buffer, BUFLEN);
							continue;
						}
						if(strcmp(comanda, "unshare")==0 && i>0)
						{
							char *fisier=strtok(NULL, "\n");
							char *username = strtok(NULL, " >\n");
							DIR *dir;
							int ok=0;
							struct dirent *dp;
							dir = opendir(username);
							for(dp=readdir(dir); dp!=NULL; dp=readdir(dir))
							{
								if(strcmp(dp->d_name, fisier)==0)
									ok=1;
							}
							if(ok==0)
							{
								strcpy(buffer, "-4 Fisier inexistent");
								write(i, buffer, BUFLEN);
								continue;
							}
							if(findfile(&list, fisier, username)==0)
							{
								strcpy(buffer, "-7 Fisierul este deja privat");
								write(i, buffer, BUFLEN);
								continue;
							}
							stergefisier(&list, fisier, username);
							strcpy(buffer, "200 Fisierul ");
							strcat(buffer, "a fost setat ca PRIVATE.\n");
							write(i, buffer, BUFLEN);
							continue;
						}
						if(strcmp(comanda, "upload")==0 && i>0)
						{
							char *fisier=(char*) malloc (50*sizeof(char));
							strcpy(fisier, strtok(NULL, " \n"));
							char *username =(char*) malloc (50*sizeof(char));
							strcpy(username, strtok(NULL, " >\n"));
							DIR *dir;
							int ok=0;
							struct dirent *dp;
							dir = opendir(username);
							for(dp=readdir(dir); dp!=NULL; dp=readdir(dir))
							{
								if(strcmp(dp->d_name, fisier)==0)
									ok=1;
							}
							if(ok==1)
							{
								strcpy(buffer, "-9 Fisier existent pe server");
								write(i, buffer, BUFLEN);
								continue;
							}
						continue;
						}
						if(strcmp(comanda, "delete")==0 && i>0)
						{
							char *fisier=(char*) malloc (50*sizeof(char));
							strcpy(fisier, strtok(NULL, "\n"));
							char *username =(char*) malloc (50*sizeof(char));
							strcpy(username, strtok(NULL, " >\n"));
							if(parcurgeUpload(&uploadlist, fisier) && parcurgeDownload(&downloadlist, fisier))
							{
								strcat(username, "/");
								strcat(username, fisier);
								unlink(username);
								strcpy(buffer, "200 Fisier sters");
								write(i, buffer, BUFLEN);
							}
							else
							{
								strcpy(buffer, "-10 Fisier in transfer");
								write(i, buffer, BUFLEN);
							}
							continue;
						}
						if(strcmp(comanda, "quit\n")==0 && i==0)
						{
							for(j=1;j<fdmax+1;j++)
								if(FD_ISSET(j, &read_fds) && j!=sockfd)
								{
									memset(comanda, 0, 100);
									strcpy(comanda, "Serverul se va inchide!");
									write(j, comanda, BUFLEN);
								}
							quit=1;
							continue;
						}
						write(i, "Comanda necunoscuta", BUFLEN);
					
					}
				} 
			}
		}
     }

     fclose(users);
     fclose(files);

     close(sockfd);
   
     return 0; 
}


