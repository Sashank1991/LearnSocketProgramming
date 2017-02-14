#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include  <netinet/in.h>
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
	int socketfd,length;
	char buffer[255];
	struct sockaddr_in serv_addr, cli_addr;
	struct in_addr ip;
	struct hostent *server;
	int n;
	socketfd = socket(AF_INET, SOCK_DGRAM,0);
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
	length = sizeof(struct sockaddr_in);
	n = sendto(socketfd,"Hi, I am sending the message to server for establishing connection.",70,0,(struct sockaddr *) &serv_addr,length);

	if(n<0){
		error("Error on writing to the server.");
	}	

	n= recvfrom(socketfd,buffer,255,0,(struct sockaddr *) &cli_addr,&length);

	if(n<0){
		error("Error on reading from the server.");
	}

	printf("Reply from Sever: %s \n", buffer);

	return 0;
}

