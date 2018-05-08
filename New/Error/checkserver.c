#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>


#define BUFLEN 1024        /* buffer length */

int receiver(int c[10],int k,int scheck)
{
	int checksum,sum=0,i;
     	printf("\n\n****RECEIVER****\n");
     	for(i=0;i<k;i++)
      		sum+=c[i];
      	printf(" RECEIVER SUM IS:%d",sum);
      	sum=sum+scheck;
      	checksum=~sum;
      	printf("\nRECEIVER's CHECKSUM IS:%d",checksum);
      	
	return checksum;
}

int main(int argc, char **argv)
{
        int n;
	int yes=1;
        int sd, new_sd, client_len, port;
        struct sockaddr_in server, client;
        char  buf[BUFLEN];

         port = atoi(argv[1]);
     
        /* create a stream socket */
        if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
		fprintf(stderr,"can't create a socket\n");
                exit(1);
        }

        /* Fill the structure fileds with values */

        server.sin_family = AF_INET;
        server.sin_port = port;
        server.sin_addr.s_addr =INADDR_ANY;
	
       // Reuse the port and address
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		perror("setsockopt");
   		exit(1);
	}

        /* bind an address to the socket */
        if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't bind name to socket\n");
                exit(1);
        }

        /* queue up to 5 connect requests */
        listen(sd,5);

        int m,result,p,j;
        int b[10];
        int size;
        int rcheck;
        
        
	client_len = sizeof(client);

	if((new_sd = accept(sd, (struct sockaddr *) &client, &client_len)) == -1)
        {
		fprintf(stderr, "can't accept client \n");
	        exit(1);
        }

	p = read(new_sd,&size,sizeof(size));
        //size=(int)size;
	// printf("%d\n",size);
        n = read(new_sd,b,sizeof(b));
               
	m=read(new_sd,&rcheck,sizeof(rcheck));
        //printf("%d",rcheck);
	//rcheck=(int)rcheck;
                
	result=receiver(b,size,rcheck);
    	if(result==0)
		printf("\n\nNO ERROR IN TRANSMISSION\n\n");
    	else
      		printf("\n\nERROR DETECTED");



	// write(new_sd, buf,n);
	close(new_sd);    

        close(sd);
        return(0);
}


