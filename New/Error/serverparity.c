#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>


#define BUFLEN                 1024        /* buffer length */

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
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
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
         int data[4][4];
         int rowpc[4];
         int colpc[4];
         int i=0,j=0,sum=0;
         int rowp[4];
         int colp[4];
       
        
                client_len = sizeof(client);

                if((new_sd = accept(sd, (struct sockaddr *) &client, &client_len)) == -1)
                {
                        fprintf(stderr, "can't accept client \n");
                        exit(1);
                }

                n = read(new_sd,data, sizeof(data));

               n = read(new_sd,rowpc, sizeof(rowpc));
                n = read(new_sd,colpc, sizeof(colpc));

                for(i=0;i<4;i++){
        sum=0;
       for(j=0;j<4;j++){
       sum+=data[i][j];
       }
        if(sum%2==0)
         rowp[i]=0;
        else
         rowp[i]=1;
    
      }

      for(i=0;i<4;i++){
        sum=0;
       for(j=0;j<4;j++){
       sum+=data[j][i];
       }
        if(sum%2==0)
         colp[i]=0;
        else
         colp[i]=1;
    
      }
    int flagr=0;
     int er=0;
     int ec=0;
     int flagc=0;
      for(i=0;i<4;i++){
      if(rowp[i]!=rowpc[i]){
       flagr=1;
       er=i;
       break;
       }
      }

     for(i=0;i<4;i++){
      if(colp[i]!=colpc[i]){
       flagc=1;
        ec=i;
       break;
       }
      }

    printf("matrix with parity values\n");
       for(i=0;i<4;i++){
         for(j=0;j<4;j++){
         printf("%d \t",data[i][j]);}
         printf("%d",rowp[i]);
         printf("\n");  

        } 
for(i=0;i<4;i++){
printf("%d\t",colp[i]);

}
 printf("%d\n",0);


    if(flagr==1 && flagc==1){
     printf("error occured\n");
     printf("caused in bit %d %d\n",er,ec);
     printf("correcting\n");
     data[er][ec]=!data[er][ec];
       }
     else{
     printf("no error\n");
       }
     
    for(i=0;i<4;i++){
         for(j=0;j<4;j++)
         printf("%d \t",data[i][j]);
         printf("\n");  

        }



		//printf("The message  received by client : %s\n",buf); 
                //write(new_sd, buf,n);
 		close(new_sd);
        

        close(sd);
        return(0);
}


