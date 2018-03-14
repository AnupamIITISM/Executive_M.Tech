/**
*
*@n1t1shb
*
**/
#include<sys/socket.h>
#include<stdio.h>
#include<time.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<string.h>

void error(char *msg)
	{
		perror(msg);
		exit(0);
	}
short createSocket()
	{
		short hSocket;
		printf("\nClient : Creating Socket.");
		hSocket = socket(AF_INET, SOCK_STREAM, 0);
		return hSocket;
	}
int connectSocket(int hSocket)
	{
		int iRetval = -1,serverPort = 8080;
		struct sockaddr_in remote = {0};
		remote.sin_addr.s_addr = inet_addr("127.0.0.1");
		remote.sin_family  = AF_INET;remote.sin_port = htons(serverPort);
		iRetval = connect(hSocket, (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
		return iRetval;
	}
int sendUsingSocket(int hSocket, int *number)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket, number,1*sizeof(int), 0);
		return shortRetVal;
	}
int sendDataUsingSocket(int hSocket, char *message, int len)
	{
		int shortRetVal = -1;
		shortRetVal = send(hSocket, message, len, 0);
		return shortRetVal;
	}
	
int main()
	{
		int hSocket,n;
		char *WordList[20] = {"aglow","balderdash","castellan", "frowzy", "frugal", "larceny","malady","smutty","torpid","torrent","transfix","uncalled","waterproof","worm-eaten","yam","yawn","yell","yuletide","zephyr","zealot"};
		char *meaning,means[100];
		hSocket = createSocket();
		if(hSocket == -1) error("\nClient : Could not create socket.");
		printf("\nClient : Socket created successfully.");
		if(connectSocket(hSocket)<0) error("\nClient : Could not connect to socket.");
		printf("\nClient : Successfully connected with socket");
		printf("\n=====*****20 Words in Client, 15 words in Server Dictionary*****=====");
		printf("\n 1.aglow\t 2.balderdash\t 3.castellan\t 4.frowzy\t 5.frugal\n 6.larceny\t 7.malady\t 8.smutty\t 9.torpid\t10.torrent");
		printf("\n11.transfix\t12.uncalled\t13.waterproof\t14.worm-eaten\t15.yam\n16.yawn\t\t17.yell\t\t18.yuletide\t19.zephyr\t20.zealot");
		srand(time(0));n=rand()%20;
		printf("\nClient : Random word selected : %s",WordList[n]); 
		if(sendUsingSocket(hSocket,&n)<0) error("\nClient : Could not send data using socket.");
		if(recv(hSocket,meaning,500,0)<0) error("\nClient : Could not receive data using socket.");
		printf("\nServer : %s",meaning);
		if(n>14)
			{
				printf("\nClient : Enter meaning of the word :");scanf("%s",means);
				if(sendDataUsingSocket(hSocket,means,100)<0)
					{
						printf("\nClient : - Data uplink from client failed. Exiting.");
						return 1;
					}
				printf("\nClient : New meaning is send to be updated in the dictionary.");
			}
		close(hSocket);
		return 0;
	}