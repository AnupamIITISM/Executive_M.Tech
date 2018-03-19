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
	printf("\nClient : Creating Socket");
	hSocket = socket(AF_INET, SOCK_STREAM, 0);
	return hSocket;
}
int connectToSocket(int hSocket){
	int iRetval = -1,serverPort = 8080;
	struct sockaddr_in remote = {0};
	remote.sin_addr.s_addr = inet_addr("127.0.0.1");
	remote.sin_family  = AF_INET;
	remote.sin_port = htons(serverPort);
	iRetval = connect(hSocket, (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
	return iRetval;
}
int sendDataUsingSocket(int hSocket,char *n,int len){
	int shortRetVal = -1;
	shortRetVal = send(hSocket,n,len,0);
	return shortRetVal;
}
int sendIntUsingSocket(int hSocket, int *number){
		int shortRetVal = -1;
		shortRetVal = send(hSocket, number, 1*sizeof(int), 0);
		return shortRetVal;
	}

int main(){
	int hSocket,choice,pos;
	int i,j,keylen,msglen;
	char input[100],data[130],key[30],temp[30],quot[100],rem[30],key1[30],serverResponse[200];
	hSocket = createSocket();
	if(hSocket == -1){
		printf("\nClient : - Could not create socket.");
		return 1;
	}
	if(connectToSocket(hSocket)<0){
		printf("\nClient : - Connection to socket failed.");
		return 1;
	}
	printf("\nEnter Data: ");	gets(input);
	printf("Enter Key: ");	gets(key);
	keylen=strlen(key);	msglen=strlen(input);
	strcpy(key1,key);
	for (i=0;i<keylen-1;i++) input[msglen+i]='0';
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
	/*printf("\nFinal data is: ");
	for (i=0;i<msglen;i++) printf("%c",input[i]);
	for (i=0;i<keylen-1;i++) printf("%c",rem[i]);*/
	printf("\nError Less final data to be transmitted is[data+reminder]: ");
	for (i=0;i<msglen;i++) data[i]=input[i];
	for (i=msglen,j=0;i<msglen+keylen-1;i++,j++) data[i]=rem[j];
	for (i=0;i<msglen+keylen-1;i++) printf("%c",data[i]);
	if(sendIntUsingSocket(hSocket,&keylen)<0){
		printf("\nClient : key length transmittion failed.");
		return 1;
	}
	if(sendIntUsingSocket(hSocket,&msglen)<0){
		printf("\nClient : message length transmittion failed.");
		return 1;
	}
	if(sendDataUsingSocket(hSocket,key1,30)<0){
		printf("\nClient : divisor transmittion failed.");
		return 1;
	}
	printf("\nClient : Want to send incorrect data ? (1- YES, 0- NO) : "); scanf("%d",&choice);
	if(choice==1){
		printf("\nClient : Error in which bit position ? : "); scanf("%d",&pos);
		data[pos]=(data[pos]=='0')?'1':'0';

		//if(data[pos]=='1') data[pos]='0';
		//else data[pos]='1';
		printf("\nError filled final data to be transmitted is: ");
		for (i=0;i<msglen+keylen-1;i++) printf("%c",data[i]);
	}
	if(sendDataUsingSocket(hSocket,data,130)<0){
		printf("\nClient : Data transmission failed.");
		return 1;
	}
	if(recv(hSocket,serverResponse,200,0)<0){
		printf("\nClient : Data reception failed.");
		return 1;
	}
	printf("\n[Reply From Server] : %s",serverResponse);
	return 0;
}