#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

#define BUFLEN 4096

typedef struct upload
{
	int n;
	char *fisier;
	char *username;
	struct upload *next;
}uploads;

typedef struct download
{
	int n;
	char *dest;
	struct download *next;
}downloads;

void adaugaupload(uploads **cap, int n, char* fisier, char* username)
{
	uploads *nou, *curent;
	nou=(uploads*) malloc (sizeof(uploads));
	nou->n=n;
	nou->fisier=(char*) malloc (25* sizeof(char));
	strcpy(nou->fisier, fisier);
	nou->username=(char*) malloc (25* sizeof(char));
	strcpy(nou->username, username);
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

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	fd_set read_fds, temp_fds;

    char buffer[BUFLEN] = ""; 
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &serv_addr.sin_addr);
    
    
    if (connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0) 
        error("Eroare la conectare");    
    FD_ZERO(&read_fds);
    FD_SET(0, &read_fds);
    FD_SET(sockfd, &read_fds);

    uploads *uploadlist;
    uploadlist=NULL;
    downloads *downloadlist;
    downloadlist = NULL;

    FILE *clientlog;
    char* fisierclient = (char*) malloc (30 * sizeof(char));
    sprintf(fisierclient, "%s%d%s", "client-", getpid(), ".log");
    clientlog=fopen(fisierclient, "w"); 

    int logat=0;
    int login=0;
    char* username=(char*) malloc (25 * sizeof(char));
    char* username2=(char*) malloc (25 * sizeof(char));
    strcpy(username, "$");
    int quit=0;

    do{
		temp_fds = read_fds;
    	        memset(buffer, 0 , BUFLEN);
		if(select(sockfd + 1, &temp_fds, NULL, NULL, NULL) >= 0){
			if(FD_ISSET(0, &temp_fds)){
				read(0, buffer, BUFLEN);
				char *comanda=(char*) malloc (BUFLEN * sizeof(char));
				strcpy(comanda, buffer);
				char *cmd=strtok(comanda, " ");
				
				if(strcmp(cmd, "login")==0){
					if(logat==1){
						fprintf(clientlog, "%s\n", "-2 Sesiune deja deschisa");
						printf("%s\n", "-2 Sesiune deja deschisa");
					}
					else{
						login=1;
						username2=strtok(NULL, " ");
						char*password=strtok(NULL, " ");
						fprintf(clientlog, "%s %s\n", username, buffer);
						n = write(sockfd, buffer, BUFLEN);
					}
				}
				else
					login = 0;
				
				if(strcmp(cmd, "logout\n")==0){
					if(logat==0){
						fprintf(clientlog, "%s\n", "-1 Clientul nu e autentificat");
						printf("%s\n", "-1 Clientul nu e autentificat");
					}
					else{
						fprintf(clientlog, "%s %s\n", username, buffer);
						n = write(sockfd, buffer, BUFLEN);
						logat=0;
						strcpy(username, "$");
					}
				}
				
				if(strcmp(cmd, "getuserlist\n")==0)
					if(logat==1){
						fprintf(clientlog, "%s %s\n", username, buffer);
						n=write(sockfd, buffer, BUFLEN);
					}
					else{
						fprintf(clientlog, "%s\n", "-1 Clientul nu e autentificat");
						printf("%s\n", "-1 Clientul nu e autentificat");
					}	
				if(strcmp(cmd, "getfilelist")==0)
					if(logat==1){
						fprintf(clientlog, "%s %s\n", username, buffer);
						n=write(sockfd, buffer, BUFLEN);
					}
					else{
						fprintf(clientlog, "%s\n", "-1 Clientul nu e autentificat");
						printf("%s\n", "-1 Clientul nu e autentificat");
					}
				if(strcmp(cmd, "share")==0 || strcmp(cmd, "unshare")==0)
					if(logat==1)
					{
						fprintf(clientlog, "%s %s\n", username, buffer);
						strcat(buffer, username);
						n=write(sockfd, buffer, BUFLEN);
					}
					else
					{
						fprintf(clientlog, "%s\n", "-1 Clientul nu e autentificat");
						printf("%s\n", "-1 Clientul nu e autentificat");
					}
				if(strcmp(cmd, "upload")==0)
					if(logat==1)
					{
						char* fisier=strtok(NULL, " \n");
						DIR *dir;
						int ok=0;
						struct dirent *dp;
						dir = opendir(".");
						for(dp=readdir(dir); dp!=NULL; dp=readdir(dir))
						{
							if(strcmp(dp->d_name, fisier)==0)
								ok=1;
						}
						if(ok==0)
						{
							fprintf(clientlog, "%s\n", "-4 Fisier inexistent");
							printf("%s\n", "-4 Fisier inexistent");
						}
					}
					else
					{
						fprintf(clientlog, "%s\n", "-1 Clientul nu e autentificat");
						printf("%s\n", "-1 Clientul nu e autentificat");
					}
				if(strcmp(cmd, "delete")==0)
					if(logat==1)
					{
						fprintf(clientlog, "%s %s\n", username, buffer);
						strcat(buffer, username);
						n=write(sockfd, buffer, BUFLEN);
					}
					else
					{
						fprintf(clientlog, "%s\n", "-1 Clientul nu e autentificat");
						printf("%s\n", "-1 Clientul nu e autentificat");
					}
				if(strcmp(cmd, "quit\n")==0)
					quit=1;
			}
			else if(FD_ISSET(sockfd, &temp_fds)){
				n = read(sockfd, buffer, BUFLEN);
				if(n <= 0)
					error("Conexiune inchisa\n");
				if(strcmp(buffer, "Serverul se va inchide!")==0)
					quit=1;
				if(login==1)
					if(strcmp(buffer, "Success")==0)
					{
						logat=1;
						strcpy(username, username2);
						strcat(username, ">");
					}
				fprintf(clientlog, "%s\n", buffer);
				printf("%s\n", buffer);
			}
		}
    }while (quit==0 || uploadlist!=NULL || downloadlist!=NULL);
    fclose(clientlog);
    close(sockfd);
    return 0;
}


