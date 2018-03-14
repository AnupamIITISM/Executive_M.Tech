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
int connectToSocket(int hSocket)
	{
		int iRetval = -1,serverPort = 8080;
		struct sockaddr_in remote = {0};
		remote.sin_addr.s_addr = inet_addr("127.0.0.1");
		remote.sin_family  = AF_INET;
		remote.sin_port = htons(serverPort);
		iRetval = connect(hSocket, (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
		return iRetval;
	}
int sendDataUsingSocket(int hSocket, int *number)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket, number, 1*sizeof(int), 0);
		return shortRetVal;
	}

int main()
	{
		int hSocket, read_size,numberToServer = 0;
		struct sockaddr_in server;
		char serverResponse[100];
		hSocket = createSocket();
		if(hSocket == -1)
			{
				printf("\nClient : - Socket creation failed.");
				return 1;
			}
		printf("\nClient : - Socket created successfully.");
		if(connectToSocket(hSocket)<0)
			{
				printf("\nClient : - Socket connection Failed.");
				return 1;
			}
		printf("\nClient : - Socket connected successfully.");
		printf("\nClient : - Enter a number : ");
		scanf("%d", &numberToServer);
		if(numberToServer<0)
			{
				printf("\nClient : - Invalid input. Exiting.");
				return 1;
			}
		if(sendDataUsingSocket(hSocket,&numberToServer)<0)
			{
				printf("\nClient : - Data uplink failed.");
				return 1;
			}
		if(recv(hSocket,&serverResponse,(100)*sizeof(char),0)<0)
			{
				printf("\nClient : - Data downlink failed.");
				return 1;
			}
		printf("\nServer : - \n");
		int j = 0,k = 1,t = numberToServer;
		while(numberToServer != 0 )
			{
				for(int i=0; i < numberToServer; ++i)
					printf("%c ",serverResponse[j++]);
				printf("\n");
				for(int j=0; j < k; ++j) printf(" ");
				k++;numberToServer--;
			}
		close(hSocket);
		return 0;
	}