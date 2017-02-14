/* 
Name	:Sashank Malladi
SJSU ID :010466651
Class Id: 34

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
extern int errno;

int errexit(const char *format, ...);
int TCPdaytimed(int fd);

int passiveTCP(int service, int qlen);

#define QLEN 5

int main(int argc, char *argv[])

{

		struct sockaddr_in fsin;

		char *service = "daytime";

		int msock, ssock;

		int pid, port=12009;
		socklen_t alen;
		switch (argc) {

			case 1:

			break;

			case 2:

			port = atoi(argv[1]);

			break;

			default:

			errexit("usage: TCPdaytimed [port]\n");

		}

		msock = passiveTCP(port, QLEN);
		alen= sizeof(fsin);
		   while (1) {
		     ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		
		      if (ssock < 0) {
			 printf("error occured while accepting");
			 exit(1);
		      }
		      
		      /* Create child process */
		      pid = fork();
		
		      if (pid < 0) {
			 printf("error occured while creating child process");
			 exit(1);
		      }
		      
		      if (pid == 0) {
			 close(msock);
			 TCPdaytimed(ssock);
			 exit(0);
		      }
		      else {
			 close(ssock);
		      }
		
		   }

}

int TCPdaytimed(int fd)

{
	char *pts; /* pointer to time string */

	time_t now; /* current time */

	char *ctime();

	(void) time(&now);

	pts = ctime(&now);
	int writeError;
	writeError=write(fd, pts, strlen(pts));
	if(writeError<0){
	      printf("ERROR writing to socket");
	      exit(1);
	}
	return 0;
}



int passiveTCP( port, qlen )
{
	int sockfd;
	   struct sockaddr_in servaddr;
	   sockfd=socket(AF_INET,SOCK_STREAM,0);
	   bzero(&servaddr,sizeof(servaddr));
	   servaddr.sin_family = AF_INET;
	   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	   servaddr.sin_port=htons(port);
	   bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	   listen(sockfd,qlen);
		return sockfd;
}

int errexit(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}
