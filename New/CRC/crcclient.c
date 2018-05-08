#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

void strrev(char * text){//not implemented in gcc so had to include||not a part of solution offcourse
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

void append(char *input,char *divisor){
	int i;
 	int l;

	l = strlen(input);

	for(i=0;i<strlen(divisor)-1;i++){
		input[l+i]='0';
	}	
	
	input[l+i]='\0';
}

char * remainder(char * input,char *divisor){
	char *remainder;	

	remainder = strdup(input);

	

	while(strlen(remainder)!=strlen(divisor)-1){
	
	if(remainder[0]=='1')
		XOR(remainder,divisor);
	strrev(remainder);
	remainder[strlen(remainder)-1]='\0';
	strrev(remainder);
	}
	
	return remainder;

}



int main(int argc, char **argv)
{
       
        int sd, port;
        
       char input[100],divisor[100];
	
	char message[100];
        
       struct sockaddr_in server;
     
       port=atoi(argv[1]);

        
        if(( sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                fprintf(stderr, "can't create a socket\n");
                exit(1);
        }

       
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

       printf("Enter the input : \n");
	scanf("%s",input);
	
	printf("Enter the divisor : \n");
	scanf("%s",divisor);
	m=strlen(divisor);
	append(input,divisor);
	sprintf(message,"%d", atoi(input)+atoi(remainder(input,divisor))  );
	printf("%s\n",message);	
        write(sd,divisor,sizeof(divisor));
         
        write(sd,message,sizeof(message));
        
        
      
       close(sd);
       return(0); 
}

