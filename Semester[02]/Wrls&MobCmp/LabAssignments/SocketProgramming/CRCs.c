/**
*
*@n1t1shb
*
**/
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

short createSocket(){
	short hSocket;
	printf("\nServer : Creating Socket\n");
	hSocket=socket(AF_INET,SOCK_STREAM,0);
	return hSocket;
}
int bindCreatedSocket(int hSocket){
	int iRetval=-1,ClientPort = 8080;
	struct sockaddr_in  remote={0};	 
	remote.sin_family = AF_INET;
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(ClientPort);
	iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
return iRetval;
}

int main(){
	int socket_desc, client_sock,con,flag=0;
	int i,j,keylen,msglen;
	char input[130],key[30],temp[30],quot[100],rem[30],key1[30];
	char *message;
	struct sockaddr_in client;
	socket_desc=createSocket();
	if(socket_desc==-1){
		printf("\nServer : Could not create socket. Exiting.");
		return 1;
	}
	if(bindCreatedSocket(socket_desc)<0){
		printf("\nServer : socket binding failed.");
	}
	listen(socket_desc, 3);
	printf("\nServer : Waiting for connections...");
	con = sizeof(struct sockaddr_in);
	client_sock=accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&con);
	if(client_sock<0){
		printf("\nServer : Connection request from client rejected. Exiting.");
		return 1;
	}
	printf("\nServer : Connnection request from client accepted.");
	if(recv(client_sock, &keylen, 1*sizeof(int), 0) < 0 ){
		printf("\nServer : Data uplink from client failed.");
		return 0;
	}
	printf("\nReceived key length : %d",keylen);
	if(recv(client_sock, &msglen, 1*sizeof(int), 0) < 0 ){
		printf("\nServer : Data reception failed.");
		return 0;
	}
	printf("\nReceived original message length : %d",msglen);
	if(recv(client_sock,key,30,0)<0){
		printf("\nServer : Data reception failed.");
		return 1;
	}
	printf("\nReceived key : ");
	for (i=0;i<keylen;i++) printf("%c",key[i]);
	if(recv(client_sock,input,130,0)<0){
		printf("\nServer : Data reception failed.");
		return 1;
	}
	printf("\nReceived message : ");
	for (i=0;i<msglen+keylen-1;i++) printf("%c",input[i]);
	printf("\nHence received original message : ");
	for (i=0;i<msglen-1;i++) printf("%c",input[i]);	
	strcpy(key1,key);
	for (i=0;i<keylen;i++)	 temp[i]=input[i];
	for (i=0;i<msglen;i++){
		quot[i]=temp[0];
		if(quot[i]=='0')
			for (j=0;j<keylen;j++) key[j]='0'; 
		else
			for (j=0;j<keylen;j++) key[j]=key1[j];
		for (j=keylen-1;j>0;j--){
			if(temp[j]==key[j]) rem[j-1]='0'; 
			else rem[j-1]='1';
		}
		rem[keylen-1]=input[i+keylen];
		strcpy(temp,rem);
	}
	strcpy(rem,temp);
	printf("\nQuotient is ");
	for (i=0;i<msglen;i++) printf("%c",quot[i]);
	printf("\nRemainder is "); 
	for (i=0;i<keylen-1;i++) printf("%c",rem[i]);
	for (i=0;i<keylen-1;i++){
		flag=(rem[i]=='1')?1:0;
		if(flag==1) break;
	}
	if(flag==1) strcpy(message,"Bad_Data");
	else strcpy(message,"Good_Data");
	if(send(client_sock,message,200,0)<0){
		printf("\nServer : Data downlink from server failed.");
		return 1;
	}
	close(client_sock);
	return 0;
}