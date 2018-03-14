/**
*
*@n1t1shb
*
**/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<strings.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h> 

void error(char *msg)
	{
		perror(msg);
		exit(0);
	}

int main(int argc, char *argv[])
	{
		int sockfd,portno,n,id;
		struct sockaddr_in serv_addr;
		struct hostent *server;
		char buffer[256];
		if(argc < 3)
			{
				fprintf(stderr,"\nClient :  Correct execution format is %s <hostname> <port_no> {e.g. %s localhost 2222}", argv[0]);
				exit(0);
			}
		portno = atoi(argv[2]);
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd < 0) 
			error("\nClient :  Could not create socket.");
		printf("\nClient :  Socket created.");
		server = gethostbyname(argv[1]);
		if(server == NULL) 
			{
				fprintf(stderr,"\nClient :  Could n't find server as given");
				exit(0);
			}
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
		serv_addr.sin_port = htons(portno);
		if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0) 
			error("\nClient :  Connection to socket failed.");
		printf("\nClient :  Connection to socket successful.");
		while(1)
			{
				printf("\nClient :  Enter the Emp ID(enter -1 to terminate session) : ");bzero(buffer,256);
				fgets(buffer,255,stdin);
				id = atoi(buffer);
				if(id==-1) error("\nClient :  Session termination has been requested");
				n = write(sockfd,buffer,strlen(buffer));
				if(n<0) error("\nClient :  Couldn't write the data input to socket.");
				bzero(buffer,256);
				n = read(sockfd,buffer,255);
				printf("\nClient :  Requesting mumber of leaves ? : ");bzero(buffer,256);
				fgets(buffer,255,stdin);
				n = write(sockfd,buffer,strlen(buffer));
				bzero(buffer,256);
				n = read(sockfd,buffer,255);
				if (n < 0) error("\nClient :  Data downlink from server failed.");
				printf("\nServer : %s\n",buffer);
			}
		return 0;
	}
