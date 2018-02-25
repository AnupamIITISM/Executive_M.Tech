#include<stdio.h> 
#include<string.h> 
#include<sys/socket.h> 
#include<arpa/inet.h> 
 
int main(int argc , char *argv[])
{
 int sock;
 struct sockaddr_in server;
 int  server_reply;
 int number,i,temp;
 sock = socket(AF_INET , SOCK_STREAM , 0);
 if (sock == -1)
 {
 printf("Could not create socket");
 }
 puts("Socket created");
 
 server.sin_addr.s_addr = inet_addr("127.0.0.1");
 server.sin_family = AF_INET;
 server.sin_port = htons( 8880 );
 
 if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
 {
 perror("connect failed. Error");
 return 1;
 }
 
 puts("Connected\n");
 printf("Client:Enter any number");
 scanf("%d",&number);
 
 if( send(sock , &number, 1*sizeof(int) , 0) < 0)
 {
 puts("Send failed");
 return 1;
 }

 if( recv(sock , &server_reply , 1*sizeof(int), 0) < 0)
 {
 puts("recv failed");
 return;
 }
 puts("\nServer:Fibonacci Term:\n");
 printf("%d\n",server_reply);

 close(sock);
 return 0;
}