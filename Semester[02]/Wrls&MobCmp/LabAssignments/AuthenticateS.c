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
		hSocket=socket(AF_INET,SOCK_STREAM,0);
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
		int socket_desc, client_sock, c, read_size;
		struct sockaddr_in server, client;
		char client_message[200]={0}, message[100] = {0}, msg[100] = {0};
		const char *pMessage = "nitish";
		socket_desc=createSocket();
		if(socket_desc==-1)
			{
				printf("\nServer : - Could not create socket. Exiting.");
				return 1;
			}
		printf("\nServer : - Socket created.");
		if(bindCreatedSocket(socket_desc)<0)
			{
				printf("\nServer : - socket binding failed.");
			}
		printf("\nServer : - socket binding done.");
		listen(socket_desc, 3);
		printf("\nServer : - Waiting for connections...");
		c = sizeof(struct sockaddr_in);
		client_sock=accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);
		if(client_sock < 0)
			{
				printf("\nServer : - Connection request from client rejected. Exiting.");
				return 1;
			}
		printf("\nServer : - Connnection request from client accepted.");
		memset(client_message, '\0', sizeof client_message);
		memset(message, '\0', sizeof message);
		if(recv(client_sock,client_message,200,0)<0)
			{
				printf("\nServer : - Data uplink from client failed.");
				return 1;
			}
		printf("\nServer : - Password sent from client : %s",client_message);
		if(strcmp(pMessage,client_message)==0)
			strcpy(message,"Correct Password. Authenticated sucessfully..");
		else
			strcpy(message,"Wrong Password!!!");
		if(send(client_sock,message,strlen(message),0)<0)
			{
				printf("\nServer : - Data downlink from server failed.");
				return 1;
			}
		if(strcmp(message,"Wrong Password!!!")==0)
			{
				printf("\nAuthentication failed. Exiting..");
				return 1;
			}
		memset(client_message, '\0', sizeof client_message);
		memset(message, '\0', sizeof message);
		printf("\nChat with client");
		if(recv(client_sock,client_message,200,0)<0)
			{
				printf("\nServer : - Data uplink from client failed.");
				return 1;
			}
		printf("\nClient : - %s",client_message);
		strcpy(message,"Hello there.");
		if(send(client_sock,message,strlen(message),0)<0)
			{
				printf("\nServer : - Data downlink from server failed.");
				return 1;
			}
		printf("\nServer : - %s",message);
		close(client_sock);
		return 0;
	}