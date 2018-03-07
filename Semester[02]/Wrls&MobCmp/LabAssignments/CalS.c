/**
*
*@n1t1shb
*
**/
#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<arpa/inet.h>
#include<unistd.h>

short createSocket()
	{
		short hSocket;
		printf("Creating Socket\n");
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
void calculator(int m, int n,int ans[])
	{
		ans[0] = m + n;
		ans[1] = m - n;
		ans[2] = m * n;
		if( n == 0 ) ans[3] = INT_MAX;
		else ans[3] = m/n;
	}

int main()
{
	int socket_desc,client_sock,c,read_size,numberFromClient[2]={0},answer[100];
	struct sockaddr_in server, client;
	socket_desc  = createSocket();
	if(socket_desc == -1)
		{
			printf("\nServer : - Could not create socket.");
			return 1;
		}
	printf("\nServer : - Socket created.");
	if(bindCreatedSocket(socket_desc) <0 )
		{
			printf("\nServer : - binding failed");
		}
	printf("\nServer : - binding done. ");
	listen(socket_desc, 3);
	printf("\nServer : - Waiting for connections...");
	c = sizeof(struct sockaddr_in);
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
		{
			printf("\nServer : - Incoming connection from client rejected.");
			return 1;
		}
	printf("\nServer : - Incoming connection from client accepted.");
	if(recv(client_sock, &numberFromClient, 2*sizeof(int), 0) < 0 )
		{
			printf("\nServer : - Reception of data sent by client Failed.");
			return 1;
		}
	calculator(numberFromClient[0],numberFromClient[1],answer);
	if(send(client_sock, answer, sizeof(answer)/sizeof(int), 0 ) < 0 )
		{
			printf("\nServer : - Data downlink to client failed.");
			return 1;
		}
	close(client_sock);
	return 0;
}