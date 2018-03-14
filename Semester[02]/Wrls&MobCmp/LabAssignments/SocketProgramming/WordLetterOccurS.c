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
#include <ctype.h>

int numberToClient;
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
char findOccurence(char *word,int num)
	{
		char c;
		int i,freq[26],occured,flag=0,m=0;
		for(i=0;i<26;i++) freq[i]=0;
		for(i=0;i<strlen(word);i++)
			{
				occured = (int)(toupper(word[i])-'A');
				freq[occured]++;
			}
		for(i=0;i<26;i++)
			{
				if(freq[i]==num)
					{
						c = (char)(65+i);
						numberToClient=num;
						flag = 1;
					}
				else if(freq[i]>freq[m]) m = i;
				else continue;
			}
		if(flag==0)
			{
				c = (char)(65+m);
				numberToClient=freq[m];
			}
		return c;
	}

int main()
	{
		int socket_desc,client_sock,numberFromClient=0,c;
		char letterToClient,wordFromClient[25];
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
				if(recv(client_sock,wordFromClient,25,0)<0)
					{
						printf("\nServer : - Data uplink failed.");
						return 1;
					}
				printf("\nServer : - The word send by client is :%s",wordFromClient);
				if(!(strcmp(wordFromClient,"X"))||!(strcmp(wordFromClient,"x")))
					{
						printf("\nServer : - Connection termination requested. Closing Session.");
						close(client_sock);
						return 0;
					}
				if(recv(client_sock,&numberFromClient,1*sizeof(int),0)<0)
					{
						printf("\nServer : - Data uplink failed.");
						return 1;
					}
				letterToClient = findOccurence(wordFromClient,numberFromClient);
				if(send(client_sock,&letterToClient,1*sizeof(char),0)<0)
					{
						printf("\nServer : - Data downlink failed.");
						return 1;
					}
				
				if(send(client_sock,&numberToClient,1*sizeof(char),0)<0)
					{
						printf("\nServer : - Data downlink failed.");
						return 1;
					}
			}
	}