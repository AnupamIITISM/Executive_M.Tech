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
#include<math.h>

int factors,pf[100];
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
void primeFactors(int n)
	{
		int i,j,k=0,isPrime;
		for(i=2;i<=n;i++)
			{
                if(n%i==0)
					{
                        isPrime = 1;
						for(j=2;j<=i/2;j++)
							{
								if(i%j==0)
									{
										isPrime = 0;
										break;
									}
							}
						if(isPrime==1)
							{
								pf[k]=i;
								k++;
							}
					}
			}
		factors=k;
    }

int main()
	{
		int socket_desc, client_sock, c, numberFromClient,serverResponse[100],i;
		struct sockaddr_in client;
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
				if(recv(client_sock, &numberFromClient, 1*sizeof(int), 0) < 0 )
					{
						printf("\nServer : - Data uplink from client failed.");
						return 0;
					}
				printf("\nServer : - The number send by client is :%d",numberFromClient);
				if(numberFromClient==0)
					{
						printf("\nServer : - Connection termination requested. Closing Session.");
						close(client_sock);
						return 0;
					}
				primeFactors(numberFromClient);
				for(i=0;i<factors;i++)
					serverResponse[i] = pf[i];
				printf("\nServer : - Prime factors for the numbers : ");
				for(i=0;i<factors;i++)
					printf("%d  ",serverResponse[i]);
				if(send(client_sock,&factors,1*sizeof(int),0)<0)
					{
						printf("\nServer : - Data downlink failed.");
						return 1;
					}
				if(send(client_sock,serverResponse,100,0)<0)
					{
						printf("\nServer : - Data downlink failed.");
						return 1;
					}
				
			}
	}