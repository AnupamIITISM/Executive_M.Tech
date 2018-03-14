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
#include<stdlib.h>
 
void error(char *msg)
	{
		perror(msg);
		exit(0);
	}
short createSocket()
	{
		short hSocket;
		printf("\nServer : Creating Socket");
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
		char *WordList[20] = {"aglow","balderdash","castellan", "frowzy", "frugal", "larceny","malady","smutty","torpid","torrent","transfix","uncalled","waterproof","worm-eaten","yam","yawn","yell","yuletide","zephyr","zealot"};
		char *MeaningList[20] = {"red-hot","nonsense","governor_of_a_castle","ill-smelling","economical","theft","mental_or_bodily_ illness","obscene","inactive","a_rush_of_water","pierce_through","uninvited","impervious_to_water","gnawed_by_insects","a_kind_of_sweet_potato","Meaning_not_available","Meaning_not_available","Meaning_not_available","Meaning_not_available","Meaning_not_available"};
		//"involuntary_opening_of_the_mouth","a_sharp_outcry","the_christmans_festivals","soft_gentle_breeze","fanatic"}
		char *message={0};
		int socket_desc,client_sock,c,numberFromClient;
		struct sockaddr_in server, client;
		socket_desc=createSocket();
		if(socket_desc == -1) error("\nServer : Could not create socket.");
		printf("\nServer : Socket created.");
		if(bindCreatedSocket(socket_desc)<0) error("\nServer : Binding failed.");
		printf("\nServer : Socket binding done.");
		listen(socket_desc, 3);
		printf("\nServer : Waiting for connections...");
		c = sizeof(struct sockaddr_in);
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if(client_sock<0) error("\nServer : Client connection rejected");
		printf("\nServer : Client connnection accepted.");
		if(recv(client_sock, &numberFromClient, 1*sizeof(int),0)<0) error("\nServer : Data reception from client failed.");
		if(send(client_sock,MeaningList[numberFromClient],200,0)<0) error("\nServer: Send data to Client failed");
		if(numberFromClient>14)
			{
				printf("\nServer : Meaning not in dictionary.");
				/*if(recv(client_sock, message, 100,0)<0)
					{
						printf("\nServer : - Data uplink from client failed.");
						return 1;
					}
				printf("\nServer : new meaning received : %s",message);
				strcpy(MeaningList[numberFromClient],message);
				printf("\nServer : Dictionary updated with new meaning for %s set to %s",WordList[numberFromClient],MeaningList[numberFromClient]);*/
			}
		close(client_sock);
		return 0;
}
	

