#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define port 6012

int main(){

  char words[1025];
  char input[1];
  char pick[2];
  pick[1]='\0';
  socklen_t clilen;
  struct sockaddr_in address, client;
  clilen = sizeof(client);
  int Sock = socket(AF_INET, SOCK_STREAM, 0);
  memset(&address, '0', sizeof(address));
  memset(words, '0', sizeof(words));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_port = htons(port);
  bind(Sock, (struct sockaddr*)&address,sizeof(address));
  listen(Sock, 5);

  int newSock = accept(Sock, (struct sockaddr*)&client,&clilen);
  while(1){
      int n=read(newSock, input, 1);
      if(n<0) printf("ERROR");
      if(!strcmp(input,"q")){
         printf("Client has decided to quit.\nThanks for playing. Goodbye.");
         break;
      }
      int num = rand()%3;
      if(num==0){pick[0]='R';}
      else if(num==1){pick[0]='P';}
      else{pick[0]='S';}

      if(strcmp(pick,input)==0){
         strcpy(words, "YOU TIE");
         printf("%s",input);
      }
      else if(strcmp(pick,input)>0){
         strcpy(words, "YOU WIN");
         printf("%s",input);
      }
      else{
         strcpy(words, "YOU LOSE");
         printf("%s",input);
      }
      write(newSock, words, strlen(words));
   }
   close(newSock);
   close(Sock);
   return 0;
}
