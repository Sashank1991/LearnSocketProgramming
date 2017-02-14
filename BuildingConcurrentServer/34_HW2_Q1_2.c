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
#include <unistd.h>
int main(int argc, char**argv)
{
   int sockfd;
   struct sockaddr_in servaddr,cliaddr;
   fd_set active_fd_set, read_fd_set;
   socklen_t addrlen;
   int maxSock;

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
  

  /* Initialize the set of active sockets. */
  FD_ZERO (&active_fd_set);
  FD_SET (sockfd, &active_fd_set);
  maxSock=sockfd;
  while (1)
    {
      read_fd_set = active_fd_set;
	
      if (select (maxSock+1, &read_fd_set, NULL, NULL, NULL) < 0)
        {
          printf("Select Error");
          exit (1);
        }
	int i;
	
      for (i = 0; i <= maxSock; i++){
        
	if (FD_ISSET (i, &read_fd_set))
          {
            if (i == sockfd)
              {
                int newSocketfd;
   		addrlen = sizeof(cliaddr);
                newSocketfd = accept(sockfd,(struct sockaddr *) &cliaddr, & addrlen );
                if (newSocketfd < 0)
                  {
         		 printf("accept Error");
          		exit (1);
                  }
                FD_SET (newSocketfd, &active_fd_set);
                if(newSocketfd > maxSock){
		    maxSock=newSocketfd;
		}
              }

            else
              {
		char buffer[1024];
		int nbytes;
		  nbytes = read (i, buffer, 1024);
		  if (nbytes < 0)
		    {
		      /* Read error. */
		      printf("Error receiving data from client.");
		      exit (EXIT_FAILURE);
		    }
		  else if(nbytes ==0){
		    close (i);
	            FD_CLR (i, &active_fd_set);
		    }
		  else
		    {
		      /* Data read. */
		     printf("%s \n",buffer);
		      fflush(stdout);
		     int writeError;
		      writeError=write (i, "Thank you for the message. \n", 30);
			     if (writeError < 0)
			    {
			      /* Read error. */
			      printf("Error sending data to client.");
			      exit (EXIT_FAILURE);
			    }
		    }
              }
          }
	}
    }
  close(sockfd);
}
