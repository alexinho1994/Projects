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

#define MAX_CLIENTS	10
#define BUFLEN 500

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

     fd_set read_fds;	
     fd_set tmp_fds;	
     int fdmax, num;	
     int nrclienti=0;
     char **ip = (char**) malloc (11 * sizeof(char*));
     for(i=0;i<11;i++)
	{
	ip[i]=(char*) calloc(20, sizeof(char));
	}
     int* port=(int*) malloc (11 * sizeof(int));

     int download = 0;

     FD_ZERO(&read_fds);
     FD_ZERO(&tmp_fds);
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     if(strcmp(argv[1], "-p")==0)
	portno = atoi(argv[2]);
     else
	if(strcmp(argv[2], "-p")==0)
		portno = atoi(argv[3]);
	else  
		if(strcmp(argv[3], "-p")==0)
			portno = atoi(argv[4]);
		else 
			if(strcmp(argv[4], "-p")==0)
				portno = atoi(argv[5]);
			else 
				if(strcmp(argv[5], "-p")==0)
					portno = atoi(argv[6]);
					
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
     int exit=0;
     FILE* fd= fopen("log.html" ,"w");
	while (exit==0) {
		tmp_fds = read_fds; 
		if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1) 
			error("ERROR in select");
	
		for(i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {
			
				if (i == sockfd) {
					
					clilen = sizeof(cli_addr);
					if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) == -1) {
						error("ERROR in accept");
					} 
					else {
						
						FD_SET(newsockfd, &read_fds);
						if (newsockfd > fdmax) { 
							fdmax = newsockfd;
						}
					}
					printf("Noua conexiunde la %s, port %d, socket_client %d\n ", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), newsockfd);
					strcpy(ip[nrclienti], inet_ntoa(cli_addr.sin_addr));
					port[nrclienti]=ntohs(cli_addr.sin_port);
					nrclienti++;
				}
					
				else {
					
					memset(buffer, 0, BUFLEN);
					if ((n = read(i, buffer, BUFLEN)) <= 0) {
						if (n == 0) {
							
							printf("Clientul %d s-a deconectat\n", i);
						} else {
							error("ERROR in recv");
						}
						close(i); 
						FD_CLR(i, &read_fds); 
					} 
					
					else { 
						printf("%s", buffer);
						if(i==0)
							comanda = strtok(buffer, " ");
						else
							comanda = (strtok(buffer, "\0"));
						if(strcmp(comanda, "download")==0 && i==0 && download==0)
						{
							char* pagina=strtok(NULL, " \n");
							if(strstr(pagina, "http://") !=0)
							{
								fprintf(stderr, "ok");
								strcpy(buffer, pagina+7);
							}
							else
								strcpy(buffer, pagina);
							download = 1;
							for(j=4; j< fdmax + 1; j++)
								if(FD_ISSET(j, &read_fds))
								{
									write(j, buffer, BUFLEN);
									break;
								}
							continue;
						}
						if(download==1 && i>0)
						{
							fprintf(fd, "%s", buffer);
							if ((strstr(buffer, "</html") != 0) || (strstr(buffer, "</HTML") != 0))
								exit=1;
							continue;
						}
						if(strcmp(comanda, "status\n")==0 && i==0 && download==0)
						{
							memset(comanda, 0, BUFLEN);
							comanda = (char*) malloc(BUFLEN * sizeof(char));
							for(j = 0 ; j < nrclienti ; j++)
							{
								sprintf(comanda, "%d %s %d\n", j, ip[j], port[j]);
								strcat(buffer, comanda);
								memset(comanda, 0, 100);
							}
							write(i, buffer, BUFLEN);
							continue;
						}
						if(strcmp(comanda, "exit\n")==0 && i==0 && download==0)
						{
							for(j=1;j<fdmax+1;j++)
								if(FD_ISSET(j, &read_fds) && j!=sockfd)
								{
									memset(comanda, 0, 100);
									strcpy(comanda, "Serverul se va inchide!");
									write(j, comanda, BUFLEN);
								}
							exit=1;
							continue;
						}
						if(download==1)
						{
							strcpy(buffer, "Nu mai pot primi comenzi");
							write(i, buffer, BUFLEN);
						}
						if(download==0)
						{
							strcpy(buffer, "Comanda necunoscuta\n");
							write(i, buffer, BUFLEN);
						}
					}
				} 
			}
		}
     }


     close(sockfd);
   fclose(fd);
     return 0; 
}


