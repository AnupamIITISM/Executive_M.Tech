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
		int hSocket,numberToServer;
		char serverResponse[100]={};
		struct sockaddr_in server;
		hSocket = createSocket();
		if(hSocket == -1)
			{
				printf("\nClient : - Could not create socket.");
				return 1;
			}
		printf("\nClient : - Socket created.");
		if(connectToSocket(hSocket) < 0 )
			{
				printf("\nClient : - Connection to socket failed.");
				return 1;
			}
		printf("\nClient : - Connection to socket successful.");
		printf("\n******Query Students Database with 10 students record******");
		printf("\n******w.r.t. roll numbers, unique for each student(0-9)******");
		printf("\nN:B: Enter '99' against roll number to terminate querying");
		while(1)
			{
				printf("\nClient : - Enter any roll number : ");
				scanf("%d",&numberToServer);
				if(numberToServer==99)
					{
						printf("\nterminating querying student database...");
						if(sendDataUsingSocket(hSocket,&numberToServer)<0)
							{
								printf("\nClient : - Data uplink failed.");
								return 1;
							}
						return 0;
					}
				if(sendDataUsingSocket(hSocket,&numberToServer)<0)
					{
						printf("\nClient : - Data uplink failed.");
						return 1;
					}
				if(recv(hSocket,serverResponse,200,0)<0)
					{
						printf("\nClient : - Data downlink failed.");
						return 1;
					}
				printf("\nServer : - Corresponding student details :\n");
				printf("%s",serverResponse);
			}
		close(hSocket);
		return 0;
	}
