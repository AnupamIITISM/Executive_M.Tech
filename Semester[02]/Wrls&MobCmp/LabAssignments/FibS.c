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
		printf("\nServer: - Creating Socket\n");
		hSocket = socket(AF_INET, SOCK_STREAM, 0);
		return hSocket;
	}
int bindSocket(int hSocket)
	{
	 
		int iRetval=-1;
		int ClientPort = 8080;
		struct sockaddr_in  remote={0};
		
		remote.sin_family = AF_INET;
		remote.sin_addr.s_addr = htonl(INADDR_ANY);
		remote.sin_port = htons(ClientPort);
		iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
		
		return iRetval;
	}

void fibonacci(int num,int ans[])
	{
		int i;
		ans[0]=0;ans[1]=1;
		for(i=2;i<=num;++i)
			ans[i]=ans[i-1]+ans[i-2];
	}

int main()
	{
		int socket_desc,client_sock,c,read_size,numberFromClient=0,fibonacciNumber[100],opt=1;
		struct sockaddr_in server, client;
		socket_desc=createSocket();
		if(socket_desc == -1)
			{
				printf("\nServer: - Could not create socket");
				return 1;
			}
		printf("\nServer: - Socket created");
		/*if (setsockopt(socket_desc,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)))
			{
				perror("setsockopt");
				return 1;
			}*/
		if(bindSocket(socket_desc)<0)
			printf("\nServer: - Bind failed");
		printf("\nServer: - Binding done");
		
		listen(socket_desc,3);
		printf("\nServer: - Waiting for connections...");
		c = sizeof(struct sockaddr_in);
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if(client_sock<0)
			{
				printf("\nServer: - Connnection not accepted");
				return 1;
			}
		printf("\nServer: - Connnection accepted");
		if(recv(client_sock, &numberFromClient, 1*sizeof(int), 0) < 0 )
			{
				printf("\nServer: - Data receiving Failed\n");
				return 0;
			}

		printf("\nServer: - The number send by client is :%d\n",numberFromClient);
		fibonacci(numberFromClient, fibonacciNumber);
		
		if(send(client_sock, fibonacciNumber, sizeof(fibonacciNumber)/sizeof(int), 0 ) < 0 )
		{
			printf("\nServer: - Send data to Client failed\n");
			return 1;
		}
		close(client_sock);
		return 0;
	}
	






















