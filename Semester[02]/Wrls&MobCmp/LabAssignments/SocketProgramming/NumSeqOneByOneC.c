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
		int hSocket,read_size,numberToServer,serverResponse,n=0,i=1;
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
		printf("\nClient : - Enter numbers in sequence : ");
		while(i<=5)
			{
				if(i==1) printf("\nClient : - Enter the %d-st number : ",i);
				else if(i==2) printf("\nClient : - Enter the %d-nd number : ",i);
				else if(i==3) printf("\nClient : - Enter the %d-rd number : ",i);
				else printf("\nClient : - Enter the %d-th number : ",i);
				scanf("%d",&n); numberToServer = n;
				if( sendDataUsingSocket(hSocket,&numberToServer)<0)
					{
						printf("\nClient : - Data uplink failed.");
						return 1;
					}
				if(recv(hSocket,&serverResponse,1*sizeof(int),0)<0)
					{
						printf("\nClient : - Data downlink failed.");
						return 1;
					}
				printf("\nServer : - %d",serverResponse);
				i++;
			}
		close(hSocket);
		return 0;
	}