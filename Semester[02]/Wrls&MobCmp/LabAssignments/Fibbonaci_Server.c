#include<stdio.h>
#include<string.h> 
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h> 
int fib(int);

int main(int argc , char *argv[])
{
 int socket_desc,client_sock,c,f,read_size;
 struct sockaddr_in server , client;
 int message,i;

 socket_desc = socket(AF_INET , SOCK_STREAM , 0);
 if (socket_desc == -1)
 {
 printf("Could not create socket");
 }
 puts("Socket created");

 server.sin_family = AF_INET;
 server.sin_addr.s_addr = INADDR_ANY;
 server.sin_port = htons( 8880 );

 if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
 {
 perror("bind failed. Error");
 return 1;
 }
 puts("bind done");

 listen(socket_desc , 3);
 
 puts("Waiting for incoming connections...");
 c = sizeof(struct sockaddr_in);

 client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
 if (client_sock < 0)
 {
 perror("accept failed");
 return 1;
 }
 puts("Connection accepted");
 
 while( (read_size = recv(client_sock ,&message , 1*sizeof(int), 0)) > 0 )
 {
 puts("\nServer:The number sent by client is: ");
 printf("%d",message);
 f=fib(message); 
 write(client_sock , &f, 1*sizeof(int));
 }
 
 if(read_size == 0)
 {
 puts("Client disconnected");
 }
 else if(read_size == -1)
 {
 perror("recv failed");
 }
 
 return 0;
}
 
int fib(int c)
{
    int  fib1 = 0, fib2 = 1, fib3, limit, count = 0;
    limit=c;
    count = 2;
    while(count<limit)
    {
        fib3 = fib1 + fib2;
        count++;
        fib1 = fib2;
        fib2 = fib3;
    }
    return fib3;
}