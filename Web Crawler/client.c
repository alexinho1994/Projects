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
#include <errno.h>
#include <arpa/inet.h>  

#define SMTP_PORT 25
#define BUFLEN 4096
#define MAXLEN 500

void error(char *msg)
{
    perror(msg);
    exit(0);
}

ssize_t Readline(int sockd, void *vptr, size_t maxlen) {
    ssize_t n, rc;
    char    c, *buffer;

    buffer = vptr;

    for ( n = 1; n < maxlen; n++ ) {	
	if ( (rc = read(sockd, &c, 1)) == 1 ) {
	    *buffer++ = c;
	    if ( c == '\n' )
		break;
	}
	else if ( rc == 0 ) {
	    if ( n == 1 )
		return 0;
	    else
		break;
	}
	else {
	    if ( errno == EINTR )
		continue;
	    return -1;
	}
    }

    *buffer = 0;
    return n;
}


int main(int argc, char *argv[])
{
    int sockfd, n,portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    fd_set read_fds, temp_fds;
    char adresa[20];

    char buffer[BUFLEN] = "";
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

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

     if(strcmp(argv[1], "-a")==0)
	strcpy(adresa, argv[2]);
     else
	if(strcmp(argv[2], "-a")==0)
		strcpy(adresa, argv[3]);
	else  
		if(strcmp(argv[3], "-a")==0)
			strcpy(adresa, argv[4]);
		else 
			if(strcmp(argv[4], "-a")==0)
				strcpy(adresa, argv[5]);
			else 
				if(strcmp(argv[5], "-a")==0)
					strcpy(adresa, argv[6]);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    inet_aton(argv[1], &serv_addr.sin_addr);
    
    
    if (connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");    
    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);
    int quit=0;
    do{
	temp_fds = read_fds;
    	memset(buffer, 0 , BUFLEN);
		if(select(sockfd + 1, &temp_fds, NULL, NULL, NULL) >= 0){
				n = read(sockfd, buffer, BUFLEN);
				if(n <= 0)
					error("ERROR Connection closed\n");
				else
				{
					if(strcmp(buffer, "Serverul se va inchide!")==0)
						quit=1;
					else
					{
					int port = 80;
	  				int sockfd2;
	  				int m;
	 				struct sockaddr_in servaddr;
	  				char server_ip[20];
	  				char sendbuf[MAXLEN]; 
	  				char recvbuf[MAXLEN];
					char *pagina=strtok(buffer, "/"); 
					char *page=strtok(NULL, " \n\0");
					struct hostent *site = gethostbyname(pagina);
					struct in_addr** list_ip = (struct in_addr**) site->h_addr_list;
	  				int i = 0;

					strcpy(server_ip, inet_ntoa(*list_ip[i]));
					sockfd2 = socket(AF_INET, SOCK_STREAM, 0);

					memset(&servaddr, 0, sizeof(servaddr));
	  				servaddr.sin_family = AF_INET;
	  				servaddr.sin_port = htons(port);

					if (inet_aton(server_ip, &servaddr.sin_addr) <= 0 ) {
	    					printf("Adresa IP invalida.\n");
	    					exit(-1);
	  				}

					if (connect(sockfd2, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
	   					 printf("Eroare la conectare\n");
	   					 exit(-1);
	  					}
					
					strcpy(sendbuf,"GET /");
					strcat(sendbuf, page);
	  				strcat(sendbuf," HTTP/1.1\nHost: ");
					strcat(sendbuf, pagina);
					strcat(sendbuf, "\n\n");

					send(sockfd2, sendbuf, sizeof(sendbuf),0 );

					char buff[MAXLEN];
	  				memset(buff, 0, MAXLEN);
	 
	 				m = recv(sockfd2, buff, sizeof(buff), 0);
	  				char* c = strtok(buff," \n");
	 

	  				fprintf(stderr, "%s\n",buff+strlen(c)+1);
					

					while(1){
						memset(buff, 0, MAXLEN);
	   					Readline(sockfd2, buff, MAXLEN -1);
	    					if ((strstr(buff, "</html") != 0) || (strstr(buff, "</HTML") != 0)) {
							fprintf(stderr, "%s",buff);
							write(sockfd, buff, MAXLEN);
							quit=1;
	      						break;
	    					}

	   				fprintf(stderr, "%s",buff);
					write(sockfd, buff, MAXLEN);
					}
					}
	  				
				}	
				fprintf(stderr, "%s\n", buffer);
		}
    }while (quit==0);
    close(sockfd);
    return 0;
}


