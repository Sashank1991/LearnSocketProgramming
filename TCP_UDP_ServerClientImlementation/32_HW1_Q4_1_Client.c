#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include   <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>



void error(char *err){
	printf("%s", err);
	exit(1);
}

int main(int argc, char * argv[]){
	if(argc<3){
		error("Please pass correct arguments.\n");
	}
	int socketfd;
	char buffer[255];
	struct sockaddr_in serv_addr;
	struct in_addr ip;
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
	
	if(connect(socketfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
		error("Error on connecting socket.\n");
	}
	
	printf("client is connected to server.\n");

	bzero(buffer,255);

	n = write(socketfd, "Hi, I am sending the message to server for establishing connection.",70);

	if(n<0){
		error("Error on writing to the server.");
	}	

	n= read(socketfd,buffer,255);

	if(n<0){
		error("Error on reading from the server.");
	}

	printf("Reply from Sever: %s \n", buffer);


	return 0;
}

