/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
     int sock, newSock, port, n;
     char input[256];
     socklen_t clilen;
     struct sockaddr_in address, client;
     if(argc < 2){
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sock = socket(AF_INET, SOCK_STREAM, 0);
     if(sock < 0) fprintf(stderr,"ERROR opening socket");
     bzero((char *) &address, sizeof(address));
     port = atoi(argv[1]);
     address.sin_family = AF_INET;
     address.sin_addr.s_addr = INADDR_ANY;
     address.sin_port = htons(port);
     if(bind(sock, (struct sockaddr *) &address,sizeof(address)) < 0) fprintf(stderr,"ERROR on binding");
     listen(sock,5);
     clilen = sizeof(client);
     newSock = accept(sock,(struct sockaddr *) &client,&clilen);
     if (newSock < 0) fprintf(stderr,"ERROR on accept");
     bzero(input,256);
     n = read(newSock,input,255);
     if (n < 0) fprintf(stderr,"ERROR reading from socket");
     do{
       if ((strcmp(input,"q\n") + 113 == 0) || (strcmp(input,"q\n") == 0))  break;
			 printf("Here is client's choice: %s\n",input);
			 if (strcmp(input,"R\n") == 0){
					 printf("Here is the EMPIRE's choice: PAPER\n");
					 printf("YOU LOSE.\n");
					 n = write(newSock,"User Choice = Rock, EMPIRE CHOICE = PAPER, YOU LOSE.",52);
			 }
			 else if (strcmp(input,"P\n") == 0){
					 printf("Here is the EMPIRE's choice: SCISSORS\n");
					 printf("YOU LOSE.\n");
					 n = write(newSock,"User Choice = Paper, EMPIRE CHOICE = SCISSORS, YOU LOSE.",56);
			 }
			 else{
            printf("Here is the EMPIRE's choice: ROCK\n");
            printf("YOU LOSE.\n");
            n = write(newSock,"User Choice = Scissors, EMPIRE CHOICE = ROCK, YOU LOSE.",55);
			 }
	    if (n < 0) fprintf(stderr,"ERROR writing to socket");
       bzero(input,256);
		 n = read(newSock,input,255);
		 }while(strcmp(input,"q\n") != 0);
     close(newSock);
     close(sock);
     return 0;
}
