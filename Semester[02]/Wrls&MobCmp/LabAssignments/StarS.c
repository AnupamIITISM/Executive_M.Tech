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
		printf("\nServer : - Creating Socket.");
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
		int socket_desc, client_sock, c, read_size,numberFromClient = 0;
		struct sockaddr_in server, client;
		char serverResponse[100];
		socket_desc  = createSocket();
		if(socket_desc == -1)
			{
				printf("\nServer : - Socket creation failed.");
				return 1;
			}
		printf("\nServer : - Socket created.");
		if(bindCreatedSocket(socket_desc) <0 )
			{
				printf("\nServer : - Socket binding failed.");
				return 1;
			}
		printf("\nServer : - Socket binding successful.");
		listen(socket_desc, 3);
		printf("\nServer : - Waiting for connections...");
		c = sizeof(struct sockaddr_in);
		client_sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);
		if (client_sock<0)
			{
				printf("\nServer : - Client connection request rejected.");
				return 1;
			}
		printf("\nServer : - Client connection request accepted.");
		if(recv(client_sock,&numberFromClient,1*sizeof(int),0)<0)
			{
				printf("\nServer : - Data uplink failed.");
				return 0;
			}
		printf("\nServer : - The number send by client is :%d",numberFromClient);
		int sum = (numberFromClient * (numberFromClient + 1 )) /2;
		for(int i=0; i < sum; ++i) serverResponse[i] = '*';
		if(send(client_sock, serverResponse, sizeof(serverResponse)/sizeof(char),0)<0)
			{
				printf("\nServer : - Data donwlink failed.");
				return 1;
			}
		close(client_sock);
		return 0;
	}