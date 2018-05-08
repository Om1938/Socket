#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <netdb.h>


#define N strlen(gen)

#define PORT 20000 
#define BACKLOG 5
#define LENGTH 512 

char test[100]="1111100001000000",cs[28],gen[]="11000000000000101";
char test2[10];
int a,e,c;
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void xor(){
    for(c = 1;c < N; c++)
    cs[c] = (( cs[c] == gen[c])?'0':'1');
}
 
void crc(){
    for(e=0;e<N;e++)
        cs[e]=test[e];
    do{
        if(cs[0]=='1')
            xor();
        for(c=0;c<N-1;c++)
            cs[c]=cs[c+1];
        cs[c]=test[e++];
    }while(e<=a+N-1);
}
 

int main ()
{
	
	FILE *bits = NULL;
	FILE *ed=NULL;
	bits = fopen("/home/d1/Documents/305/EDC/CRC/Bits.txt", "r");
	ed = fopen("/home/d1/Documents/305/EDC/CRC/ed.txt", "r");
	
	int sockfd; 
	int nsockfd; 
	int num;
	int sin_size; 
	struct sockaddr_in addr_local; 
	struct sockaddr_in addr_remote; 
	char revbuf[LENGTH];

	
		

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor. (errno = %d)\n", errno);
		exit(1);
	}
	else 
		printf("[Server] Obtaining socket descriptor successfully.\n");

	
	addr_local.sin_family = AF_INET; 
	addr_local.sin_port = htons(PORT); 
	addr_local.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(addr_local.sin_zero), 8); 

	if( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
	{
		fprintf(stderr, "ERROR: Failed to bind Port. (errno = %d)\n", errno);
		exit(1);
	}
	else 
		printf("[Server] Binded tcp port %d in addr 127.0.0.1 sucessfully.\n",PORT);

	
	if(listen(sockfd,BACKLOG) == -1)
	{
		fprintf(stderr, "ERROR: Failed to listen Port. (errno = %d)\n", errno);
		exit(1);
	}
	else
		printf ("[Server] Listening the port %d successfully.\n", PORT);

	int success = 0;
	while(success == 0)
	{
		sin_size = sizeof(struct sockaddr_in);

	
		if ((nsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, &sin_size)) == -1) 
		{
		    fprintf(stderr, "ERROR: Obtaining new Socket Despcritor. (errno = %d)\n", errno);
			exit(1);
		}
		else 
			printf("[Server] Server has got connected from %s.\n", inet_ntoa(addr_remote.sin_addr));

		//Recieving file from client

		char* fr_name = "/home/d1/Documents/305/EDC/CRC/Bitsx.txt";
		FILE *fr = fopen(fr_name, "w");
		if(fr == NULL)
			printf("File %s Cannot be opened file on server.\n", fr_name);
		else
		{
			bzero(revbuf, LENGTH); 
			int fr_block_sz = 0;
			while((fr_block_sz = recv(nsockfd, revbuf, LENGTH, 0)) > 0) 
			{
			    int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
				if(write_sz < fr_block_sz)
			    {
			        error("File write failed on server.\n");
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
					exit(1);
	            }
        	}
			printf("Input file  received from client!\n");

			FILE *readInput = NULL;
			readInput = fopen("/home/d1/Documents/305/EDC/CRC/Bitsx.txt", "r");
			
			
			//char fileread[100]
  			//fgets(test,sizeof(test),readInput);
	
                        fscanf(readInput,"%s",test2);
			printf("\nInput string: %s",test);
                        printf("\nGenerator polynomial CRC-16 : %s",gen);
			a=strlen(test);
    			for(e=a;e<a+N-1;e++)
        			test[e]='0';
   
    			printf("\nModified data is : %s",test);
   
                        crc();
			fclose(fr); 
	}
}
		   
}
