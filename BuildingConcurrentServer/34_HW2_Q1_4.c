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
#include <pthread.h> 
#include <unistd.h> 

void *connection_handler(void *sock_desc)
{
 while(1){
  int sock = *(int*) sock_desc;
   int n;
   char buffer[1024];
   bzero(buffer,1024);
   n = read(sock,buffer,1024);
   
   if (n < 0) {
      printf("ERROR reading from socket");
      exit(1);
   }
   
   printf("%s\n",buffer);
   n = write(sock,"I got your message \n",20);
   
   if (n < 0) {
      printf("ERROR writing to socket");
      exit(1);
   }
  }
    return 0;
} 


int main(int argc, char**argv)
{
   int sockfd,newSocketfd;
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
   pthread_t thread_id;	

    while( newSocketfd = accept(sockfd,(struct sockaddr *) &cliaddr, & addrlen ))
    {
      if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &newSocketfd) < 0)
        {
            perror("could not create thread");
            return 1;
        }
    }
     
    if (newSocketfd < 0)
    {
        printf("accept failed");
        return 1;
    }
     
    return 0;

}
