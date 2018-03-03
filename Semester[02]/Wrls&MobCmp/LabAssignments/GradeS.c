/**
*
*@n1t1shb
*
**/
#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>

short createSocket()
	{
		short hSocket;
		printf("\nServer : - Creating Socket");
		hSocket = socket(AF_INET, SOCK_STREAM, 0);
		return hSocket;
	}
int bindCreatedSocket(int hSocket)
	{
		int iRetval=-1,ClientPort = 8080;
		struct sockaddr_in  remote={0};
		remote.sin_family = AF_INET;
		remote.sin_addr.s_addr = htonl(INADDR_ANY);
		remote.sin_port = htons(ClientPort);
		iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
		return iRetval;
	}

int main()
	{
		int socket_desc,client_sock,c,read_size,numberFromClient=0;
		struct sockaddr_in server, client;
		char grade;
		socket_desc=createSocket();
		if(socket_desc == -1)
			{
				printf("\nServer : - Could not create socket");
				return 1;
			}
		printf("\nServer : - Socket created");
		if(bindCreatedSocket(socket_desc) <0 )
			{
				printf("\nServer : - binding failed");
			}
		printf("\nServer : - binding done");
		listen(socket_desc, 3);
		printf("\nServer : - Waiting for connections...");
		c = sizeof(struct sockaddr_in);
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0)
			{
				printf("\nServer : - Connection from client rejected.");
				return 1;
			}
		printf("\nServer : - Connnection from client accepted");
		if(recv(client_sock, &numberFromClient, 1*sizeof(int), 0) < 0 )
			{
				printf("\nServer : - Data uplink from client failed");
				return 0;
			}
		printf("\nServer : - Marks send by client is :%d",numberFromClient);
		
		if(numberFromClient >=85 && numberFromClient <= 100)
			grade = 'A';
		else if(numberFromClient >= 70 && numberFromClient < 85)
			grade = 'B';
		else if(numberFromClient >=60 && numberFromClient < 70)
			grade = 'C';
		else if(numberFromClient >=50 && numberFromClient <60)
			grade = 'D';
		else grade = 'F';
		
		if(send(client_sock, &grade,1*sizeof(char),0)<0)
			{
				printf("\nServer : - Send Failed.");
				return 1;
			}
		close(client_sock);
		return 0;
	}
	

