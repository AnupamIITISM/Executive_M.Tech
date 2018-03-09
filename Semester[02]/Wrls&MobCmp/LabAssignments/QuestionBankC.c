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
		int hSocket,numberToServer,qn=0,n;
		char serverResponse[100]={};
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
		printf("\n**********Question Bank**********");
		printf("\n******enter 1 to 10 to choose from 10 questions******");
		printf("\n[1] What is the capital of India?\n[2] How many states are there in India?\n[3] What is the name of president of India?");
		printf("\n[4] Who was the first president of India?\n[5] What is the national bird of India?\n[6] What is the national animal of India?");
		printf("\n[7] Who wrote Indian national anthem?\n[8] Who is called the father of the nation?\n[9] On which year did India get it's independence?");
		printf("\n[10] What is the national flower of India?");
		printf("\nN:B: Enter '99' to terminate querying Question Bank");
		while(1)
			{
				qn++;
				printf("\nClient : - Question number ? : ");
				scanf("%d",&n);
				numberToServer=n-1;
				if(n==99)
					{
						printf("\nterminating session on client request...");
						if(sendDataUsingSocket(hSocket,&n)<0)
							{
								printf("\nClient : - Data uplink failed.");
								return 1;
							}
						return 0;
					}
				if(qn>3)
					{
						n=99;
						printf("\nterminating session , max question limit per-session(=3) exceeded.");
						if(sendDataUsingSocket(hSocket,&n)<0)
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
				printf("\nServer : - %s",serverResponse);
			}
		close(hSocket);
		return 0;
	}