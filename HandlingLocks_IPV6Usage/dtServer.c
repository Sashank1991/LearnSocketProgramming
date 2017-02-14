#include <stdio.h>
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
	if(argc<2){
		error("Please pass port number.\n");
	}

	int socketfd,newSocketfd,portNo,cliLen;
	char buffer[255];
	struct sockaddr_in6 serv_addr, cli_addr;
	int n;
	socketfd = socket(AF_INET6, SOCK_STREAM,0);
	if(socketfd<0){
		error("Error in creating a socket.\n");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	//portNo=atoi("8000");

	serv_addr.sin6_family= AF_INET6;;
	serv_addr.sin6_addr  = in6addr_any;;
	serv_addr.sin6_port =htons(atoi(argv[1]));

	if(bind(socketfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) <0){
		error("Error on binding socket.\n");
	}

	listen(socketfd,5);
    	printf("Server is on and started listing to client.\n");
	cliLen = sizeof(cli_addr);
	newSocketfd = accept(socketfd,(struct sockaddr *) &cli_addr, (socklen_t*) &cliLen );
	if(newSocketfd<0){
		error("Error on accepting to client.");
	}
	bzero(buffer,255);

	time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "%c", tm);
	n = write(newSocketfd, s,64);

	if(n<0){
		error("Error on writing to the client.");
	}
	return 0;
}
