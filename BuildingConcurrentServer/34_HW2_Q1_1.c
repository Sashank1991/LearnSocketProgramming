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


void processChild (int sock) {
 while(1){  
 int n;
   char buffer[1024];
   bzero(buffer,1024);
   n = read(sock,buffer,1024);
   if (n < 0) {
      printf("ERROR reading from socket");
	
      exit(1);
   }
   printf("%s\n",buffer);
   fflush(stdout);
   n = write(sock,"I got your message \n",20);
   if (n < 0) {
      printf("ERROR writing to socket");
      exit(1);
   }
 }	
}


int main(int argc, char**argv)
{
   int sockfd,newSocketfd,pid;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t addrlen;

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
  
   addrlen = sizeof(cliaddr);

   while (1) {
      newSocketfd = accept(sockfd, (struct sockaddr *) &cliaddr, &addrlen);
		
      if (newSocketfd < 0) {
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
         close(sockfd);
         processChild(newSocketfd);
         exit(0);
      }
      else {
         close(newSocketfd);
      }
		
   }
   
}

