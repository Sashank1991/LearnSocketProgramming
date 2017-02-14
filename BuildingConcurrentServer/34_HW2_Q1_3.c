/* 
Name	:Sashank Malladi
SJSU ID :010466651
Class Id: 34

*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char**argv)
{
   int sockfd,i;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t addrlen;
   int maxSock, maxSock1;
   if (argc != 2)
   {
      fprintf(stderr,"usage %s port\n", argv[0]);
      exit(1);
   }
   int port = atoi(argv[1]);
   sockfd=socket(AF_INET,SOCK_STREAM,0);
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(port);
   bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   listen(sockfd,5);

  fcntl(sockfd, F_SETFL, O_NONBLOCK);
  maxSock=sockfd;
  maxSock1=maxSock;
  while (1)
    {
	maxSock=maxSock1;
      for (i = sockfd; i <= maxSock; i++){
            if (i == sockfd)
              { 
		int newSocketfd;
   		addrlen = sizeof(cliaddr);
                newSocketfd = accept(sockfd,(struct sockaddr *) &cliaddr, & addrlen );
                
		if (newSocketfd < 0)
                  {
 			if(errno !=EAGAIN){
		      /* Read error. */
		      printf("accept error.");
		      exit (EXIT_FAILURE);
			}
                  }
                else{
		printf("cnnecton accepted");
		fflush(stdout);
		  fcntl(newSocketfd, F_SETFL, O_NONBLOCK); 
		}
                if(newSocketfd > maxSock){
		    maxSock1=newSocketfd;
		}
              }

            else
              {
		char buffer[1024];
		int nbytes;
		  nbytes = read (i, buffer, 1024);
		  if (nbytes < 0)
		    {
 			if(errno !=EAGAIN){
		      /* Read error. */
		      printf("Error receiving data from client.");
		      exit (EXIT_FAILURE);
			}
		    }
		  else if(nbytes ==0){
		    close (i);
		    }
		  else
		    {
		      /* Data read. */
		     printf("%s \n",buffer);
		      fflush(stdout);
		      int writeError;
		      writeError=write (i, "Thank you for the message. \n", 30);
			if(writeError <0){
		        /* write error. */
		        printf("Error on sending data to client.");
		        exit (EXIT_FAILURE);
			}
		    }
              }
	}
    }
  close(sockfd);
}
