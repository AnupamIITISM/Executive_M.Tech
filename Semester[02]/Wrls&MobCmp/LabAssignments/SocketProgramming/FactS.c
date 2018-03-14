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
		printf("\nServer : - Creating Socket\n");
		hSocket = socket(AF_INET, SOCK_STREAM, 0);
		return hSocket;
	}
int bindCreatedSocket(int hSocket)
	{
		int iRetval=-1,ClientPort=8080;
		struct sockaddr_in  remote={0};
		remote.sin_family = AF_INET;
		remote.sin_addr.s_addr = htonl(INADDR_ANY);
		remote.sin_port = htons(ClientPort);
		iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
		return iRetval;
	}

int main()
	{
		int socket_desc,client_sock,c,read_size,numberFromClient=0,factorial=1;
		struct sockaddr_in server, client;
		socket_desc  = createSocket();
		if(socket_desc == -1)
			{
				printf("\nServer : - Could not create socket");
				return 1;
			}
		printf("\nServer : - Socket created");
		if(bindCreatedSocket(socket_desc)<0)
			{
				printf("\nServer : - Socket binding failed");
				return 1;
			}
		printf("\nServer : - Socket binding done");
		listen(socket_desc,3);
		printf("\nServer : - Waiting for connections...");
		c=sizeof(struct sockaddr_in);
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if(client_sock<0)
			{
				printf("\nServer : - Connection from client rejected.");
				return 1;
			}
		printf("\nServer : - Connnection from client accepted");
		if(recv(client_sock, &numberFromClient, 1*sizeof(int), 0) < 0 )
			{
				printf("\nServer : - Data uplink from client failed.");
				return 0;
			}
		printf("\nServer : - The number send by client is :%d",numberFromClient);
		for(int i=1; i<=numberFromClient; ++i) 
			factorial *= i;
		if(send(client_sock, &factorial, 1 * sizeof(int), 0 ) < 0 )
			{
				printf("\nServer : - Data downlink from server failed.");
				return 1;
			}
		close(client_sock);
		return 0;
	}
	

