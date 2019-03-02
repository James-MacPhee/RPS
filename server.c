/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     do {
       if ((strcmp(buffer,"q\n") + 113 == 0) || (strcmp(buffer,"q\n") == 0))  break;
			 printf("Here is client's choice: %s\n",buffer);
			 if (strcmp(buffer,"R\n") == 0)	{
					 printf("Here is the EMPIRE's choice: PAPER\n");
					 printf("YOU LOSE.\n");
					 n = write(newsockfd,"User Choice = Rock, EMPIRE CHOICE = PAPER, YOU LOSE.",52);
			 }
			 else if (strcmp(buffer,"P\n") == 0)	{
					 printf("Here is the EMPIRE's choice: SCISSORS\n");
					 printf("YOU LOSE.\n");
					 n = write(newsockfd,"User Choice = Paper, EMPIRE CHOICE = SCISSORS, YOU LOSE.",56);
			 }
			 else {
         printf("Here is the EMPIRE's choice: ROCK\n");
         printf("YOU LOSE.\n");
         n = write(newsockfd,"User Choice = Scissors, EMPIRE CHOICE = ROCK, YOU LOSE.",55);
			 }
	     if (n < 0) error("ERROR writing to socket");
       bzero(buffer,256);
			 n = read(newsockfd,buffer,255);
		 } while(strcmp(buffer,"q\n") != 0);

     close(newsockfd);
     close(sockfd);
     return 0;
}
