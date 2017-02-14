#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<sys/socket.h>

#include<arpa/inet.h>

 

int main(int argc, char * argv[])

{

   struct sockaddr_in6 server;

   int sock;

   char recvbuf[1000];

   int recvsize;

   struct in6_addr serveraddr;

 

   sock = socket(AF_INET6, SOCK_STREAM, 0);

   if(sock<0)

   {

            puts("socket creation error");

            exit(1);

   }

   puts("socket created");

 

   //server.sin6_addr.s6_addr = inet_pton("2003::1");

   server.sin6_family = AF_INET6;

   server.sin6_port = htons(atoi(argv[1]));

   inet_pton(AF_INET6, "::1", (void *)&server.sin6_addr);

 

   if(connect(sock, (struct sockaddr *)&server, sizeof(server))<0)

   {

            puts("connect failed");

            exit(1);

   }

   puts("connected");

 

   while((recvsize = recv(sock, recvbuf, 1000,0))>0)

   {

            recvbuf[recvsize] = '\0';

            printf("%s",recvbuf);

   }

   if(recvsize<0)

   {

            puts("recv error");

            exit(1);

   }

close(sock);

}
