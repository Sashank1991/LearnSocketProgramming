#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void);

int main()
{
   int s;
   int optval;
int buffSize;
int buffSizeLen;
   socklen_t optlen = sizeof(optval);

   /* Create the socket */
   if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket()");
      exit(EXIT_FAILURE);
   }

   /* Check the status for the keepalive option */
   if(getsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
      perror("getsockopt()");
      close(s);
      exit(EXIT_FAILURE);
   }
   printf("Initial Keep Alive option %s\n", (optval ? "ON" : "OFF"));

   /* Set the option active */
   optval = 1;
   optlen = sizeof(optval);
   if(setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
      perror("setsockopt()");
      close(s);
      exit(EXIT_FAILURE);
   }
   printf("Keep alive option is set\n");

   /* Check the status again */
   if(getsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
      perror("getsockopt()");
      close(s);
      exit(EXIT_FAILURE);
   }
   printf("Keep Alive option after setting %s\n", (optval ? "ON" : "OFF"));


   // check value of send buffer value


   if(getsockopt(s, SOL_SOCKET, SO_SNDBUF, &buffSize, &buffSizeLen) < 0) {
      perror("getsockopt()");
      close(s);
      exit(EXIT_FAILURE);
   }
   printf(" Initial buffer size %d\n", buffSize);

   /* Set the option active */
buffSize=2048;
buffSizeLen=sizeof(buffSize);
   if(setsockopt(s, SOL_SOCKET, SO_SNDBUF, &buffSize, buffSizeLen) < 0) {
      perror("setsockopt()");
      close(s);
      exit(EXIT_FAILURE);
   }
   printf("Buffer value is set to 2048 \n");

   /* Check the status again */
   if(getsockopt(s, SOL_SOCKET, SO_SNDBUF, &buffSize, &buffSizeLen) < 0) {
      perror("getsockopt()");
      close(s);
      exit(EXIT_FAILURE);
   }
   printf("buffer size after setting %d\n", buffSize);

   close(s);

   exit(EXIT_SUCCESS);
}
