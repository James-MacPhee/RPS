#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define port 6012

int main(){

   char answer2[1];
   char words[1024];
   struct sockaddr_in address;
   int sock = socket(AF_INET, SOCK_STREAM, 0);
   memset(words, '0' ,sizeof(words));
   address.sin_family = AF_INET;
   address.sin_port = htons(port);
   address.sin_addr.s_addr = inet_addr("127.0.0.1");
   connect(sock, (struct sockaddr *)&address, sizeof(address));

   while(strcmp(answer2,"q")){
      printf("Welcome to Rock-Paper-Scissors!\nPlease make your choice: [R]ock, [P]aper, [S]cissors, or [q]uit: ");
      scanf("%1s",answer2);
      if(!strcmp(answer2,"q")){
         break;
      }
      while(!strcmp(answer2,"R")&&!strcmp(answer2,"P")&&!strcmp(answer2,"S")&&!strcmp(answer2,"q")){
         printf("Incorrect input. Please make your choice: [R]ock, [P]aper, [S]cissors, or [q]uit: ");
         scanf("%1s", answer2);
      }
      write(sock, answer2, 1);
      read(sock, words, strlen(words));
      fputs(words,stdout);
   }
   printf("Thanks for playing!\n");
   return 0;
}
