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
		printf("\nClient : - Creating Socket.");
		hSocket = socket(AF_INET, SOCK_STREAM, 0);
		return hSocket;
	}
int connectSocket(int hSocket)
	{
		int iRetval = -1, serverPort = 8080;
		struct sockaddr_in remote = {0};
		remote.sin_addr.s_addr=inet_addr("127.0.0.1");
		remote.sin_family = AF_INET;
		remote.sin_port = htons(serverPort);
		iRetval = connect(hSocket,(struct sockaddr *)&remote,sizeof(struct sockaddr_in));
		return iRetval;
	}
int sendDataUsingSocket(int hSocket, int *number)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket, number, 2*sizeof(int), 0);
		return shortRetVal;
	}
int main()
	{
		int hSocket,read_size,numberToServer[2],serverResponse[4];
		struct sockaddr_in server;
		hSocket = createSocket();
		if(hSocket==-1)
			{
				printf("\nClient : - Could not create socket.");
				return 1;
			}
		printf("\nClient : - Socket created.");
		if(connectSocket(hSocket)<0)
			{
				printf("\nClient : - Connection to socket failed.");
				return 1;
			}
		printf("\nClient : - Successfully connected to socket");
		printf("\nClient : - Enter the 1st  number ");
		scanf("%d",&numberToServer[0]);
		printf("\nClient : - Enter the 2nd  number ");
		scanf("%d",&numberToServer[1]);
		if(sendDataUsingSocket(hSocket,numberToServer)<0)
			{
				printf("Send failed\n");
				return 1;
			}
		if(recv(hSocket,&serverResponse,(4)*sizeof(int),0)<0)
			{
				printf("\nClient : - Data downlink from server failed.");
				return 1;
			}
		printf("\nServer : - ");
		printf("\nAddition = %d ",serverResponse[0]);
		printf("\nSubtraction = %d ",serverResponse[1]);
		printf("\nMultiplication = %d ",serverResponse[2]);
		printf("\nDivision = %d ",serverResponse[3]);	
		close(hSocket);
		return 0;
	}