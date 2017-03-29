#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


int checksum (char* msg, int n){
  int res = 0;
  int i, j;
  for (i = 0; i < n; ++i){
	char parity = 0;
	for (j=0; j<8; j++)
		parity ^= (msg[i] >> j) & 1;
		
  	res = res ^ parity;
  }
  return res;
}

void simply(msg r)
{
	recv_message(&r);
	printf("%s\n", r.payload);
	strcpy(r.payload, "Hello");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	printf("%s\n", r.payload);
	recv_message(&r);
	printf("%s\n", r.payload);
	recv_message(&r);
	printf("%s\n", r.payload);
	strcpy(r.payload, "YEY");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	strcpy(r.payload, "OK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	printf("%s\n", r.payload);
	int interval1=0;
	int interval2=999;
	while(strcmp(r.payload, "success\n") !=0)
		{
		int nr=(interval1+interval2)/2;
		sprintf(r.payload, "%d", nr);
		printf("%s\n", r.payload);
		r.len=strlen(r.payload)+1;
		send_message(&r);
		recv_message(&r);
		printf("%s\n", r.payload);
		if(strcmp(r.payload, "bigger\n")==0)
			interval1=nr+1;
		if(strcmp(r.payload, "smaller\n")==0)
			interval2=nr-1;	
		}
	recv_message(&r);
	printf("%s\n", r.payload);
	strcpy(r.payload, "exit");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	printf("%s\n", r. payload);
}


void ack(msg r)
{
	recv_message(&r);
	printf("%s\n", r.payload);
	strcpy(r.payload, "ACK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	strcpy(r.payload, "Hello");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	recv_message(&r);
	printf("%s\n", r.payload);
	strcpy(r.payload, "ACK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	printf("%s\n", r.payload);
	strcpy(r.payload, "ACK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	printf("%s\n", r.payload);
	strcpy(r.payload, "ACK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	strcpy(r.payload, "YEY");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	strcpy(r.payload, "OK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	recv_message(&r);
	printf("%s\n", r.payload);
	strcpy(r.payload, "ACK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	int interval1=0;
	int interval2=999;
	while(strcmp(r.payload, "success\n") !=0)
		{
		int nr=(interval1+interval2)/2;
		sprintf(r.payload, "%d", nr);
		printf("%s\n", r.payload);
		r.len=strlen(r.payload)+1;
		send_message(&r);
		recv_message(&r);
		recv_message(&r);
		printf("%s\n", r.payload);
		if(strcmp(r.payload, "success\n") ==0) 
			break;
		if(strcmp(r.payload, "bigger\n")==0)
			interval1=nr+1;
		if(strcmp(r.payload, "smaller\n")==0)
			interval2=nr-1;	
		strcpy(r.payload, "ACK");
		r.len=strlen(r.payload)+1;
		send_message(&r);
		}
	strcpy(r.payload, "ACK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	printf("%s\n", r.payload);
	strcpy(r.payload, "ACK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	strcpy(r.payload, "exit");
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	printf("%s\n", r. payload);
}

void recive_parity(msg r)
{
	int p1, p2;
	do
		{
		recv_message(&r);
		printf("%s\n", r.payload);
		p1=checksum(r.payload+1, strlen(r.payload));
		p2=r.payload[0];
		printf("%d %d\n", p1, p2);
		if(p1==p2) 
			break;
		strcpy(r.payload, "NACK");
		r.len=strlen(r.payload)+1;
		send_message(&r);
		}
		while(p1!=p2);
	
}

int numar(msg r)
{
	int p1, p2;
	do
		{
		recv_message(&r);
		printf("%s\n", r.payload);
		p1=checksum(r.payload+1, strlen(r.payload));
		p2=r.payload[0];
		printf("%d %d\n", p1, p2);
		if(p1==p2) 
			break;
		strcpy(r.payload, "NACK");
		r.len=strlen(r.payload)+1;
		send_message(&r);
		}
		while(p1!=p2);
	if(r.payload[1]=='s' && r.payload[2]=='u')
		return 0;
	
	if(r.payload[1]=='s' && r.payload[2]=='m')
		return -1;
	if(r.payload[1]=='b')
		return 1;
	return 2;
}


void send_ack(msg r)
{
	strcpy(r.payload, "ACK");
	r.len=strlen(r.payload)+1;
	send_message(&r);
}

void send_msg(msg r, char * x)
{
	sprintf(r.payload, "%d", checksum(x, strlen(x)+1));
	strcat(r.payload, x);
	r.payload[strlen(r.payload)]='\0';
	r.len=strlen(r.payload)+1;
	send_message(&r);
	recv_message(&r);
	printf("%s\n", r.payload);
	while(r.len!=4)
		{
		sprintf(r.payload, "%d", checksum(x, strlen(x)+1));
		strcat(r.payload, x);
		r.len=strlen(r.payload)+1;
		send_message(&r);
		recv_message(&r);
		printf("%s\n", r.payload);
		}
}

void parity(msg r)
{
	recive_parity(r);
	send_ack(r);
	send_msg(r, "Hello");
	recive_parity(r);
	send_ack(r);
	recive_parity(r);
	send_ack(r);
	recive_parity(r);
	send_ack(r);
	send_msg(r, "YEY");
	send_msg(r, "OK");
	recive_parity(r);
	send_ack(r);
	int interval1=0;
	int interval2=999;
	int cond=5;
	while(cond!=0)
		{
		int nr=(interval1+interval2)/2;
		char x[5];
		sprintf(x, "%d", nr);
		printf("%d\n", nr);
		send_msg(r, x);
		cond=numar(r);
		send_ack(r);
		if(cond==1)
			interval1=nr+1;
			else if(cond==-1)
				interval2=nr-1;
				else break;
		}
	recive_parity(r);		
	send_ack(r);
	send_msg(r, "exit");
}


int main(int argc,char** argv)
{
	msg r;
	printf("[RECEIVER] Starting.\n");
	init(HOST, PORT);
	if(argc==2)
		{
		if(strcmp(argv[1], "ack")==0)
			{
			ack(r);	
			}
		if(strcmp(argv[1], "parity") == 0)
			{
			parity(r);
			}
		}	
	if (argc==1)
		{
		simply(r);
		}

	printf("[RECEIVER] Finished receiving..\n");
	return 0;
}
