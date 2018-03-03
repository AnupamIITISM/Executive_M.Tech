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
int sendDataUsingSocket(int hSocket,int *number)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket, number, 1*sizeof(int), 0);
		return shortRetVal;
	}

int main()
	{
		int hSocket, read_size,numberToServer=0;
		struct sockaddr_in server;
		char serverResponse;
		hSocket = createSocket();
		if(hSocket == -1)
			{
				printf("\nClient : - Could not create socket");
				return 1;
			}
		printf("\nClient : - Socket created");
		if(connectToSocket(hSocket) < 0 )
			{
				printf("\nClient : - Connection to socket failed.");
				return 1;
			}
		printf("\nClient : - Successfully connected to socket");
		printf("\nClient : - Enter marks obtained by a student : ");
		scanf("%d", &numberToServer);
		if(numberToServer < 0 )
			{
				printf("\nClient : - Invalid input");
				return 0;
			}
		if(sendDataUsingSocket(hSocket, &numberToServer) < 0 )
			{
				printf("\nClient : - Data uplink to server failed.");
				return 1;
			}
		if(recv(hSocket,&serverResponse,1*sizeof(char),0)<0)
		{
			printf("\nClient : - Receive failed");
			return 1;
		}
		printf("\nClient : - Grade of student as sent by server is : %c",serverResponse);
		close(hSocket);
		return 0;
	}

	




	
	



