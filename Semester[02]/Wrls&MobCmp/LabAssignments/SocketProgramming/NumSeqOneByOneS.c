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
		int socket_desc, client_sock, c, read_size,numberFromClient = 0,i=1;
		struct sockaddr_in server, client;
		int serverResponse[5] = {3,3,7,15,27};
		socket_desc  = createSocket();
		if(socket_desc == -1)
			{
				printf("\nServer : - Socket creation failed.");
				return 1;
			}
		printf("\nServer : - Socket created successfully.");
		if(bindCreatedSocket(socket_desc)<0)
			{
				printf("\nServer : - binding failed.");
				return 1;
			}
		printf("\nServer : - binding successful.");
		listen(socket_desc, 3);
		printf("\nServer : - Waiting for connections...");
		c = sizeof(struct sockaddr_in);
		client_sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);
		if(client_sock<0)
			{
				printf("\nServer : - Connection request from client rejected.");
				return 1;
			}
		printf("\nServer : - Connection request from client accepted\n");
		while(i<=5)
			{
				if(recv(client_sock,&numberFromClient,1*sizeof(int),0)<0)
					{
						printf("\nServer : - Data uplink failed.");
						return 1;
					}
				printf("\nServer : - The number send by client is :%d",numberFromClient);
				if(send(client_sock,&serverResponse[numberFromClient],1*sizeof(int),0)<0)
					{
						printf("\nServer : - Data downlink failed.");
						return 1;
					}
				i++;
			}
		close(client_sock);
		return 0;
	}