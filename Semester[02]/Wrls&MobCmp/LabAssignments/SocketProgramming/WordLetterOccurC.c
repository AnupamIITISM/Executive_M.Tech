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
int sendUsingSocket(int hSocket, int *number)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket, number, 1*sizeof(int), 0);
		return shortRetVal;
	}
int sendWordDataUsingSocket(int hSocket,char *s, int len)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket,s,len,0);
		return shortRetVal;
	}
	
int main()
	{
		int hSocket,numberToServer,numberFromServer=0;
		char letterFromServer,wordToServer[25];
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
		printf("\nN:B: Enter '0' to terminate connection.");
		while(1)
			{
				printf("\nClient : - Enter the word(enter 'X'/'x' to terminate) : ");
				scanf("%s",wordToServer);
				if(!(strcmp(wordToServer,"X"))||!(strcmp(wordToServer,"x")))
					{
						printf("\nClient : - Session termination has been requested. Closing session.");
						if(sendWordDataUsingSocket(hSocket,wordToServer,25)<0)
							{
								printf("\nClient : - Data uplink failed.");
								return 1;
							}
						return 0;
					}
				if(sendWordDataUsingSocket(hSocket,wordToServer,25)<0)
					{
						printf("\nClient : - Data uplink failed.");
						return 1;
					}
				printf("\nClient : - Enter the occurence count : ");
				scanf("%d",&numberToServer);
				if(sendUsingSocket(hSocket, &numberToServer)<0)
					{
						printf("\nClient :- Data uplink failed\n");
						return 1;
					}
				if(recv(hSocket,&letterFromServer,1*sizeof(char),0)<0)
					{
						printf("\nClient : - Data downlink failed.");
						return 1;
					}
				if(recv(hSocket,&numberFromServer,1*sizeof(int),0)<0)
					{
						printf("\nClient : - Data downlink failed.");
						return 1;
					}
				{
					if(numberFromServer==numberToServer)
						printf("\nServer : - In the word %s the letter occuring %d times is : %c",wordToServer,numberFromServer,letterFromServer);
					else
						{
							printf("\nServer : - In the word %s the no letter occurs the suggested %d times..",wordToServer,numberToServer);
							printf("\n\tHence showing the letter having maximum occurence(=%d) : %c",numberFromServer,letterFromServer);
						}	
				}
			}
		close(hSocket);
		return 0;
	}