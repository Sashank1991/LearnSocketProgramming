#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include   <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>


void error(char *err){
	printf("%s", err);
	exit(1);
}

int main(int argc, char * argv[]){

	clock_t start, end;
	double cpu_time_used;
	if(argc<3){
		error("Please pass correct arguments.\n");
	}
	int socketfd;
	char buffer[255];
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int n;
	socketfd = socket(AF_INET, SOCK_STREAM,0);
	if(socketfd<0){
		error("Error in creating a socket.\n");
	}
	server= gethostbyname(argv[1]);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	//portNo=atoi("8000");

	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(atoi(argv[2]));
	
	bcopy((char *) server->h_addr,(char *) &serv_addr.sin_addr.s_addr, server->h_length);
	
	bzero(buffer,255);
	if(connect(socketfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
		error("Error on connecting socket.\n");
	}
	while(1){

	char data[50];
	printf("enter data for sending to server.");
	scanf("%s",data);
	start = clock();
         n = write(socketfd, data,sizeof(data));
	if(n<0){
		error("Error on sending to the server.");
	}
	 n = read(socketfd, buffer,sizeof(buffer));
	if(n<0){
		error("Error on receiving the server.");
	}
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%s \n",buffer);
        printf("time taken: %lf \n",cpu_time_used);
        }
	return 0;
}

