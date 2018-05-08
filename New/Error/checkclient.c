#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


#define  BUFLEN                   1024                 /* buffer length */
int sender(int b[10],int k)
 {
 	int checksum,sum=0,i;
	printf("\n****SENDER****\n");
     
	for(i=0;i<k;i++)
      		sum+=b[i];
      	
	printf("SUM IS: %d",sum);
                     
    	checksum=~sum;
    	printf("\nSENDER's CHECKSUM IS:%d\n",checksum);
    	return checksum;
}

int main(int argc, char **argv)
{
        int n;
        int sd, port;
        char buf[BUFLEN];
	int a[10];
	int scheck;
        
       struct sockaddr_in server;
     
       port=atoi(argv[1]);

        /* create a stream socket */
        if(( sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                fprintf(stderr, "can't create a socket\n");
                exit(1);
        }

       // bzero((char *)&server, sizeof(struct sockaddr_in));
        server.sin_family = AF_INET;
        server.sin_port = port;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        int m,i;

        /* connecting to the server */
        if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't connect\n");
                exit(1);
        }

	printf("\nENTER SIZE OF THE ARRAY:");
     	scanf("%d",&m);

     	printf("\nENTER THE ELEMENTS OF THE ARRAY:");
     	for(i=0;i<m;i++)
    		scanf("%d",&a[i]);

        write(sd,&m,sizeof(m));
        //for(i=0;i<m;i++){               /* get user's text */
        //strcat(buf,a[i]);}

        write(sd,a,sizeof(a));        /* send it out */
        scheck=sender(a,m);
        write(sd,&scheck,sizeof(scheck));
        
        //n = read(sd, buf, sizeof(buf));
        //printf("%s\n",buf); 
      
       close(sd);
       return(0); 
}

