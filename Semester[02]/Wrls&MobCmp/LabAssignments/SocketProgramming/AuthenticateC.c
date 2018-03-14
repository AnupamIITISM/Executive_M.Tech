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
		printf("\nClient : - Creating Socket");
		hSocket = socket(AF_INET, SOCK_STREAM, 0);
		return hSocket;
	}
int connectSocket(int hSocket)
	{
		int iRetval=-1,serverPort=8080;
		struct sockaddr_in remote = {0};
		remote.sin_addr.s_addr = inet_addr("127.0.0.1");
		remote.sin_family  = AF_INET;
		remote.sin_port = htons(serverPort);
		iRetval = connect(hSocket, (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
		return iRetval;
	}
int sendDataUsingSocket(int hSocket, char *message, int len)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket, message, len, 0);
		return shortRetVal;
	}

int main()
	{
		int hSocket,read_size;
		struct sockaddr_in server;
		char sendToServer[100]={0},serverReply[200]={0}, *invalid="Wrong Password!!!";
		hSocket=createSocket();
		if(hSocket == -1)
			{
				printf("\nClient : - Could not create socket. Exiting.");
				return 1;
			}
		printf("\nClient : - Socket created successfully.");
		if(connectSocket(hSocket) < 0 )
			{
				printf("\nClient : - Establishing connection to socket failed.");
				return 1;
			}
		printf("\nClient : - Successfully connected with socket.");
		printf("\nClient : - Enter password to authenticate : ");
		scanf("%s",sendToServer);
		if(sendDataUsingSocket(hSocket,sendToServer,strlen(sendToServer))<0)
			{
				printf("\nClient : - Data uplink from client failed. Exiting.");
				return 1;
			}
		if(recv(hSocket,serverReply,200,0)<0)
			{
				printf("\nClient : - Data downlink from server failed.");
				return 1;
			}
		printf("\n\nSever : - %s", serverReply);
		if(strcmp(serverReply,invalid)==0)
			return 1;
		memset(sendToServer,'\0',sizeof(sendToServer));
		memset(serverReply,'\0',sizeof(serverReply));
		printf("\nChat with server");
		printf("\nClient : - Enter message : ");
		scanf("%s",sendToServer);
		if(sendDataUsingSocket(hSocket,sendToServer,strlen(sendToServer))<0)
			{
				printf("\nClient : - Data uplink from client failed. Exiting.");
				return 1;
			}
		if(recv(hSocket,serverReply,200,0)<0)
			{
				printf("\nClient : - Data downlink from server failed. Exiting.");
					return 1;
			}
		printf("\nServer : - %s",serverReply);
		close(hSocket);		
		return 0;
	}