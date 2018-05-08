#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

printf("ClientProgram");

int main(int argc, char *argv[]){

	struct sockaddr_in servaddr,cliaddr;
	printf("Enter the port");
	scanf("%d",&cport);
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd<0)
	{
		printf("Error....\n");
		exit(0);
	}

	else
		printf("Socket is created\n");
		servaddr.sin_family=AF_INET;
		servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
		servaddr.sin_port=htons(cport);
		if(connect(sockfd(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
			printf("Error in connection\n");
		else
			printf("connected\n");
                	printf("Enter the existing file name\t");
			scanf("%s",name);

}

