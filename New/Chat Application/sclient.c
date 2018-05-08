#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


#define  BUFLEN                   1024                 /* buffer length */

int main(int argc, char **argv)
{
        int n;
        int sd, port;
	char test='y';
        char buf[BUFLEN];
	char buf1[BUFLEN];
        
       struct sockaddr_in server;
     
       port=atoi(argv[1]);

	printf("Do you want to establish the connection?(y/n)\n");
	scanf("%c",&test);
	getchar();

	while(test!='n')
	{

        /* create a stream socket */
        if(( sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                fprintf(stderr, "can't create a socket\n");
                exit(1);
        }

       // bzero((char *)&server, sizeof(struct sockaddr_in));
        server.sin_family = AF_INET;
        server.sin_port = port;
        server.sin_addr.s_addr = inet_addr("192.168.0.107");

        /* connecting to the server */
        if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't connect\n");
                exit(1);
        }


		printf("Enter the message to be echoed: ");       
        	gets(buf);                /* get user's text */
	

	        write(sd, buf, BUFLEN);        /* send it out */
        	printf("Sent by Server:\n**************\n");
       
        	n = read(sd, buf1, sizeof(buf1));
        	puts(buf1);


		printf("Do you want to continue?(y/n)\n");       
        	scanf("%c",&test);
		getchar();
		close(sd);

	}
         
      
       close(sd);
       return(0); 
}

