#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[]){
    int sock, port, n;
    char input[256];
    struct sockaddr_in address;
    struct hostent *server;
    if(argc<3){
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    port = atoi(argv[2]);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0) fprintf(stderr,"ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL){
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &address, sizeof(address));
    address.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&address.sin_addr.s_addr,server->h_length);
    address.sin_port = htons(port);
    if (connect(sock,(struct sockaddr *) &address,sizeof(address)) < 0)fprintf(stderr,"ERROR connecting");
    printf("Enter Rock<R> Paper<P> or Scissors<S> to play or Quit<q>: ");
    bzero(input,256);
    fgets(input,255,stdin);
    if (strcmp(input,"q\n") == 0){
      n = write(sock,input,strlen(input));
      close(sock);
      return 0;
    }
    else{
      do{
        if((strcmp(input,"R\n") != 0) && (strcmp(input,"P\n") != 0) && (strcmp(input,"S\n") != 0)){
          printf("Incorrect input. Enter Rock<R> Paper<P> or Scissors<S> or Quit<q>: ");
          bzero(input,256);
          fgets(input,255,stdin);
          continue;
        }
        else{
          n = write(sock,input,strlen(input));
          if(n<0) fprintf(stderr,"ERROR writing to socket");
          bzero(input,256);
          n = read(sock,input,255);
          if(n<0) fprintf(stderr,"ERROR reading from socket");
          printf("%s\n",input);
          printf("Enter Rock<R> Paper<P> or Scissors<S> to play or Quit<q>: ");
          bzero(input,256);
          fgets(input,255,stdin);
        }
      }while(strcmp(input,"q\n") != 0);
    }
    close(sock);
    return 0;
}
