#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<signal.h>
#include<ctype.h>          
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>

#define LENGTH 512 

void error(const char *msg)
	{
		perror(msg);
		exit(1);
	}

int main(int argc, char *argv[])
{
	int sockfd,PORT; 
	int nsockfd;
	char revbuf[LENGTH],*filename; 
	struct sockaddr_in remote_addr;
	if(argc < 5)
			{
				fprintf(stderr,"\nUsage :  %s <hostname> <port_no> <get> <filename>", argv[0]);
				exit(0);
			}
	PORT = atoi(argv[2]);
	filename = argv[4];
	if(strcmp(argv[1],"localhost"))
		{
			fprintf(stderr, "ERROR: Failed to connect to the server try with localhost");
			exit(1);
		}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
			exit(1);
		}
	remote_addr.sin_family = AF_INET; 
	remote_addr.sin_port = htons(PORT); 
	inet_pton(AF_INET, "127.0.0.1", &remote_addr.sin_addr); 
	bzero(&(remote_addr.sin_zero), 8);
	if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
		{
			fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
			exit(1);
		}
	else 
		printf("Client : Connected to server at port %d...ok!\n", PORT);
	//if(strcmp(filename,"FileS/output.txt"))
		//error("\nERROR : File is not available in server");
	char *fr_name="/home/nitish89/FileC/output.txt";
	printf("\nfile path %s",fr_name);
	//strcat(fr_name,filename);
	//printf("\nfile path %s",fr_name);
	FILE *fr = fopen(fr_name, "a");
	if(fr == NULL)
		printf("Error : File %s Cannot be opened.\n", fr_name);
	else
	{
		bzero(revbuf, LENGTH); 
		int fr_block_sz = 0;
	    while((fr_block_sz = recv(sockfd, revbuf, LENGTH, 0)) > 0)
	    {
			int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
	        if(write_sz < fr_block_sz)
			{
	            error("Error : File write failed.\n");
	        }
			bzero(revbuf, LENGTH);
			if (fr_block_sz == 0 || fr_block_sz != 512) 
			{
				break;
			}
		}
		if(fr_block_sz < 0)
        {
			if (errno == EAGAIN)
			{
				printf("recv() timed out.\n");
			}
			else
			{
				fprintf(stderr, "recv() failed due to errno = %d\n", errno);
			}
		}
	    printf("Client : File Download completed from server\n");
		fclose(fr);
	}
	close (sockfd);
	printf("Client : Connection lost.\n");
	return (0);
}