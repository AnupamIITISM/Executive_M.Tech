/**
*
*@n1t1shb
*
**/
#include<stdio.h>
#include<sys/types.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<unistd.h> 

void error(char *msg)
	{
		perror(msg);
		exit(1);
	}

int main(int argc, char *argv[])
	{
		int sockfd, newsockfd, portno, clilen,i,id,number,total = 10,remain[100],extra[100],n;
		char buffer[256];
		struct sockaddr_in serv_addr, cli_addr;
		if(argc<2) 
			{
				fprintf(stderr,"\nServer :  Provide port no. Usage: %s <port_no> {e.g. %s 2222}",argv[0],argv[0]);
				exit(1);
			}
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) error("\nServer :  Couldn't create socket.");
		bzero((char *) &serv_addr, sizeof(serv_addr));
		portno = atoi(argv[1]);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);
		if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0) error("\nSocket binding failed.");
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if(newsockfd<0) error("\nServer :  Incoming client connection rejected.");
		for(i=0;i<100;i++)
			{
				remain[i] = i%10;extra[i] = 0;
			}
		while(1)
			{
				bzero(buffer,256);
				n = read(newsockfd,buffer,255);
				if (n < 0) error("\nServer :  Couldn't read from socket ");
				id = atoi(buffer);
				if(id==-1) error("\nServer :  ");
				id = id%100;
				bzero(buffer,256);
				strcpy(buffer,"EmpID Recieved");
				n = write(newsockfd,buffer,18);
				if(n<0) error("\nServer :  Couldn't write to socket.");
				bzero(buffer,256);
				n = read(newsockfd,buffer,255);
				if (n < 0) error("\nServer :  Couldn't read from socket ");
				number = atoi(buffer);
				bzero(buffer,256);
				if(number>remain[id])
					{
						extra[id] = extra[id] + (number - remain[id]);
						sprintf(buffer,"%d",(number - remain[id]));
						strcat(buffer," of the leaves requested are not available. Total Leave for all employees = 10. Confirming all available leaves. Current balance leaves = 0");
					}
				else
					{
						remain[id]-=number;
						sprintf(buffer,"%d",(remain[id]));
						strcat(buffer," leaves are still remaining. Total leave for all employees = 10. All applied leaves are confirmed.");
					}
				n = write(newsockfd,buffer,strlen(buffer));
				if (n < 0) error("\nServer :  Couldn't write to the socket");
			}
		return 0; 
}
