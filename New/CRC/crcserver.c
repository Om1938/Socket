#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>



void strrev(char * text){
	//not implemented in gcc so had to include||not a part of solution offcourse
	int l;
	int r;
	char temp;

	for(r=strlen(text)-1,l=0;r>l;l++,r--)
	{
		temp=text[l];
		text[l]=text[r];
		text[r]=temp;
	}
}


void XOR(char * i1,char *i2){
    int i;


    for(i=0;i<strlen(i2);i++){
        if(i1[i]==i2[i]){
            i1[i]='0';
        }
        else{
            i1[i]='1';
        }
    }
}


char * remainder(char * b,char *size){
	char *remainder;	

	remainder = strdup(b);

	

	while(strlen(remainder)!=strlen(size)-1){
	
	if(remainder[0]=='1')
		XOR(remainder,size);
	strrev(remainder);
	remainder[strlen(remainder)-1]='\0';
	strrev(remainder);
	}
	
	return remainder;

}



int main(int argc, char **argv)
{
        int n;
	int yes=1;
        int sd, new_sd, client_len, port;
        struct sockaddr_in server, client;
        

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
        int p;
        int b[100];
        int size[100];
	int message[100];
	
        
        
        
                client_len = sizeof(client);

                if((new_sd = accept(sd, (struct sockaddr *) &client, &client_len)) == -1)
                {
                        fprintf(stderr, "can't accept client \n");
                        exit(1);
                }
                p=read(new_sd,size,sizeof(size));
                
                n = read(new_sd,b,sizeof(b));
               
                
                
            sprintf(message,"%d", atoi(remainder(b,size))  );
    	if(atoi(message)==0)
      		printf("\n\nNO ERROR IN TRANSMISSION\n\n");
    	else
      		printf("\n\nERROR DETECTED");

 		close(new_sd);
        

        close(sd);
        return(0);
}


