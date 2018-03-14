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
		printf("\nServer : - Creating Socket.");
		hSocket = socket(AF_INET, SOCK_STREAM, 0);
		return hSocket;
	}
int bindCreatedSocket(int hSocket)
	{
	 	int iRetval=-1,ClientPort = 8080;
		struct sockaddr_in  remote={0};
		remote.sin_family = AF_INET;
		remote.sin_addr.s_addr = htonl(INADDR_ANY);
		remote.sin_port = htons(ClientPort);
		iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
		return iRetval;
	}

int main()
	{
		int socket_desc, client_sock, c, numberFromClient,i=1;
		struct sockaddr_in client;
		char serverResponse[100]={};
		char* sdb[10];
		sdb[0] = "New_Delhi";
		sdb[1] = "Twenty_Nine";
		sdb[2] = "Ram_Nath_Kovind";
		sdb[3] = "Rajendra_Prasad";
		sdb[4] = "Indian_Peafowl";
		sdb[5] = "Bengal_Tiger" ;
		sdb[6] = "Rabindranath_Tagore"; 
		sdb[7] = "Mahatma_Gandhi";
		sdb[8] = "1947";
		sdb[9] = "Lotus";
		socket_desc  = createSocket();
		if(socket_desc == -1)
			{
				printf("\nServer : - Socket creation failed.");
				return 1;
			}
		printf("\nServer : - Socket created successfully.");
		if(bindCreatedSocket(socket_desc)<0)
			{
				printf("\nServer : - binding failed.");
				return 1;
			}
		printf("\nServer : - binding successful.");
		listen(socket_desc, 3);
		printf("\nServer : - Waiting for connections...");
		c = sizeof(struct sockaddr_in);
		client_sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);
		if(client_sock<0)
			{
				printf("\nServer : - Connection request from client rejected.");
				return 1;
			}
		printf("\nServer : - Connection request from client accepted\n");
		while(1)
			{
				if(recv(client_sock,&numberFromClient,1*sizeof(int),0)<0)
					{
						printf("\nServer : - Data uplink failed.");
						return 1;
					}
				printf("\nServer : - The number send by client is :%d",numberFromClient);
				if(numberFromClient==99)
					{
						printf("\nServer : - Connection termination requested. Closing Session.");
						close(client_sock);
						return 0;
					}
				if((numberFromClient<0)||(numberFromClient>9))
					strcpy(serverResponse,"Try_Again...................");
				else strcpy(serverResponse,sdb[numberFromClient]);
				if(send(client_sock,serverResponse,strlen(serverResponse),0)<0)
					{
						printf("\nServer : - Data downlink failed.");
						return 1;
					}
				
			}
	}