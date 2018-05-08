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
        char buf[BUFLEN];
        int data[4][4];
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


        /* connecting to the server */
        if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't connect\n");
                exit(1);
        }
        int i=0,j=0;  
        int rowp[4];
        int colp[4]; 
        int sum=0;
        printf("Enter the data in form of matrix: ");       
        for(i=0;i<4;i++){
         for(j=0;j<4;j++)
         scanf("%d",&data[i][j]);  

        }

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
       int error=0,er,ec;
      printf("for 1 bit error-press 1 \n");
       scanf("%d",&error);

     printf("matrix with parity values:\n");
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
       if(error==1){
       printf("Enter the row and col of bit to be altered\n");
        scanf("%d %d",&er,&ec);
      data[er][ec]=!data[er][ec];
      write(sd, data, sizeof(data));
      }
     

       else{                
        write(sd, data, sizeof(data)); }
        write(sd, rowp, sizeof(rowp));   
       write(sd, colp, sizeof(colp));          
       // printf("Echoed Messege:\n**************\n");
       
      //  n = read(sd, buf, sizeof(buf));
        //printf("%s\n",buf); 
      
       close(sd);
       return(0); 
}

