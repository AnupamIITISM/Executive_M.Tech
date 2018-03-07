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
		int socket_desc, client_sock, c, read_size,numberFromClient = -1,i=1;
		struct sockaddr_in server, client;
		char serverResponse[100]={};
		char* sdb[10];
		sdb[0] = "Name=Nitish_Bhattacharjee___Stream=CSE___Year=2nd___Semester=2nd___Centre=Kolkata";
		sdb[1] = "Name=Debjit_Das___Stream=IT___Year=2nd___Semester=2nd___Centre=Malda";
		sdb[2] = "Name=Smaranjit_Maiti___Stream=ECE___Year=3rd___Semester=2nd___Centre=Midnapore";
		sdb[3] = "Name=K_Charan___Stream=CSE___Year=2nd___Semester=2nd___Centre=Vizag";
		sdb[4] = "Name=Sourav_Bhadra___Stream=IT___Year=4th___Semester=2nd___Centre=Beleghata";
		sdb[5] = "Name=Ashish_Sarkar___Stream=CSE___Year=2nd___Semester=2nd___Centre=Agartala" ;
		sdb[6] = "Name=Souvik_Sen___Stream=ECE___Year=3rd___Semester=1st___Centre=Kolkata"; 
		sdb[7] = "Name=Manoj_Bose___Stream=IT___Year=2nd___Semester=2nd___Centre=Jalpaiguri";
		sdb[8] = "Name=Arindam_Raymondal___Stream=ECE___Year=2nd___Semester=2nd___Centre=Alipurduar";
		sdb[9] = "Name=Asit_Mahato___Stream=CSE___Year=2nd___Semester=2nd___Centre=Bankura";
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
				strcpy(serverResponse,sdb[numberFromClient]);
				if(send(client_sock,serverResponse,strlen(serverResponse),0)<0)
					{
						printf("\nServer : - Data downlink failed.");
						return 1;
					}
				
			}
	}