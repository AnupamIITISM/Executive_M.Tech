#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>

short createSocket()
	{
		short hSocket;
		printf("\nClient: - Creating Socket");
		hSocket = socket(AF_INET, SOCK_STREAM, 0);
		return hSocket;
	}

int connectSocket(int hSocket)
	{
		int iRetval = -1;
		int serverPort = 8080;
		struct sockaddr_in remote = {0};
		
		remote.sin_addr.s_addr = inet_addr("127.0.0.1");
		remote.sin_family  = AF_INET;
		remote.sin_port = htons(serverPort);
		iRetval = connect(hSocket, (struct sockaddr *)&remote,sizeof(struct sockaddr_in));
		return iRetval;
	}

int sendDataToServer(int hSocket, int *number)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket, number, 1*sizeof(int),0);
		return shortRetVal;
	}

int main()
	{
		int hSocket,read_size,numberToServer=0,serverResponse[100];
		struct sockaddr_in server;
		
		hSocket = createSocket();
		if(hSocket==-1)
			{
				printf("\nClient: - Could not create socket");
				return 1;
			}
		printf("\nClient: - Socket created...");
		if(connectSocket(hSocket)<0)
			{
				printf("\nClient: - Connection failed. Exiting...");
				return 1;
			}
		printf("\nClient: - Socket connected successfully...");
		printf("\nClient: - Enter n, for upto n fibonacci terms : ");
		scanf("%d",&numberToServer);
		
		if(numberToServer<0)
			{
				printf("\nServer : - Invalid input!!!");
				return 0;
			}
		if(sendDataToServer(hSocket,&numberToServer)<0)
			{
				printf("\nClient: - Data uplink failed. Exiting...");
				return 1;
			}
		if(recv(hSocket,&serverResponse,(100)*sizeof(int),0)<0)
			{
				printf("\nClient: - Data receiving failed");
				return 1;
			}
		
		printf("\nServer : - ");
		for(int i=0; i <= numberToServer; ++i)
			printf("F(%d) = %d ",i,serverResponse[i]);
		
		printf("\n");
		close(hSocket);
		return 0;
	}

	




	
	



