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
		printf("\nClient :- Creating Socket");
		hSocket = socket(AF_INET, SOCK_STREAM, 0);
		return hSocket;
	}

int connectToSocket(int hSocket)
	{
		int iRetval=-1,serverPort=8080;
		struct sockaddr_in remote = {0};
		remote.sin_addr.s_addr = inet_addr("127.0.0.1");
		remote.sin_family  = AF_INET;
		remote.sin_port = htons(serverPort);
		iRetval = connect(hSocket, (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
		return iRetval;
	}

int sendUsingSocket(int hSocket, int *number)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket, number, 1*sizeof(int), 0);
		return shortRetVal;
	}

int main()
	{
		int hSocket,read_size,numberToServer=0,serverResponse=1;
		struct sockaddr_in server;
		hSocket = createSocket();
		if(hSocket == -1)
			{
				printf("\nClient :- Could not create socket");
				return 1;
			}
		printf("Client :- Socket created\n");
		if(connectToSocket(hSocket) < 0 )
			{
				printf("\nClient :- Connection Failed.");
				return 1;
			}
		printf("\nClient :- Successfully connected to socket");
		printf("\nClient :- Enter a number : ");
		scanf("%d", &numberToServer);
		if(numberToServer < 0 )
			{
				printf("\nClient :- Invalid input\n");
				return 0;
			}
		if(sendUsingSocket(hSocket, &numberToServer)<0)
			{
				printf("\nClient :- Data uplink failed\n");
				return 1;
			}
		if(recv(hSocket,&serverResponse,1*sizeof(int),0)<0)
			{
				printf("\nClient :- Receiving server response failed\n");
				return 1;
			}
		printf("\nClient : - Received reply from server.");
		printf("\nClient : - Factorial of given number as returned by server is : %d",serverResponse);
		close(hSocket);
		return 0;
	} 
