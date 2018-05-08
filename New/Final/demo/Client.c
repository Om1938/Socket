#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>

main()
{
	FILE *fp;
    
	struct sockaddr_in serveraddr;
	int clientsock,length;
	char filename[20],filedata[300];

	char username[20],password[20],flag[20];

	bzero((char*)&serveraddr,sizeof(serveraddr));

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=2000;
	serveraddr.sin_addr.s_addr=inet_addr("192.168.0.107");

	clientsock=socket(AF_INET,SOCK_STREAM,0);

	if(connect(clientsock,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
	{
    		printf("\nError:Cannot connect...");
    		exit(0);
	}

	printf("Authentication needed\n\n");
	
	printf("Enter the username\n");
	gets(username);

	printf("Enter the password\n");
	gets(password);

	write(clientsock,username,sizeof(username));
	write(clientsock,password,sizeof(password));

	printf("Validating the credential....\n");
	
	read(clientsock,flag,sizeof(flag));

	if(strcmp(flag,"True")==0)
	{
		printf("Enter the name of the file : ");
		scanf("%s",filename);

		fp = fopen(filename,"a+");
		length=strlen(filename);

		write(clientsock,filename,length);

		read(clientsock,filedata,300);

		printf("\nThe contents of the file: \n\n");
		printf("%s",filedata);
		fprintf(fp,"%s",filedata);
	}
	else
	{
		printf("File transmission failed\n");
		printf("Exiting......\n");
	}

	close(clientsock);
}

