#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define port 6012

int main(){

  char words[1025];
  char input[1];
  char pick;
  struct sockaddr_in address;
  int listenSock = socket(AF_INET, SOCK_STREAM, 0);
  memset(&address, '0', sizeof(address));
  memset(words, '0', sizeof(words));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_port = htons(port);
  bind(listenSock, (struct sockaddr*)&address,sizeof(address));
  listen(listenSock, 10);

  //int connSock = accept(listenSock, (struct sockaddr*)NULL ,NULL);
  int connSock = accept(listenSock, (struct sockaddr*)NULL ,NULL);
  while(1){
      read(listenSock, input, 1);
      if(input[0]=='q'){
         printf("Client has decided to quit.\nThanks for playing. Goodbye.");
         break;
      }
      int num = rand()%3;
      if(num==0){pick='R';}
      else if(num==1){pick='P';}
      else{pick='S';}

      if(pick==input[0]){
         strcpy(words, "Opponent chose . You chose BLANK. You Tie! Play Again?");
         printf("%s",input);
      }
      else if(pick>input[0]){
         strcpy(words, "FUCKYOU");
         printf("%s",input);
      }
      else{
         strcpy(words, "Opponent chose BLANK. You chose BLANK. You Win!! Play Again?");
         printf("Opponent chose BLANK. You chose BLANK. You Lose.");
      }
      write(connSock, words, strlen(words));
   }
   close(connSock);
   return 0;
}
