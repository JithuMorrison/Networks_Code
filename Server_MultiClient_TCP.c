#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<poll.h>

#define MAX 2048
#define CLIENTS 10

int main(){
  printf("Starting server...\n");	
  int sockfd,newsockfd,inc = 0;
  int csock[CLIENTS];
  struct sockaddr_in server,client;
  socklen_t clilen = sizeof(client);
  char buffer[MAX];

  sockfd = socket(AF_INET,SOCK_STREAM,0);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(8085);
  bind(sockfd,(struct sockaddr *)&server,sizeof(server));
  listen(sockfd,5);

  struct pollfd fds[CLIENTS+2];
  fds[0].fd = sockfd;
  fds[0].events = POLLIN;
  fds[1].fd = fileno(stdin);
  fds[1].events = POLLIN;
  for(int i = 2; i < CLIENTS+2; i++){
    fds[i].fd = -1;
  }
  int pol;
  printf("Server running...\n");
  
  while(1){
    pol = poll(fds,inc+2,3000);
    if(pol>0){
      if(fds[0].revents & POLLIN){
        newsockfd = accept(sockfd,(struct sockaddr *)&client,&clilen);
        if(newsockfd>=0){
          fds[inc+2].fd = newsockfd;
          fds[inc+2].events = POLLIN;
          csock[inc] = newsockfd;
          printf("Client Connected\n");
          inc++;
        }
        continue;
      }
      for(int i = 2; i < CLIENTS+2; i++){
        if(fds[i].fd != -1 && (fds[i].revents & POLLIN)){
          int r = read(fds[i].fd,buffer,MAX);
          if(r>0){
            printf("%s",buffer);
          }
          else if(r==0){
            close(fds[i].fd);
            fds[i].fd = -1;
            printf("Client disconnected\n");
          }
        }
      }
      if(fds[1].revents & POLLIN){
        char message[MAX];
        fgets(message,MAX,stdin);
        for(int i = 0; i < inc; i++){
          if(csock[i]!=-1){
            write(csock[i],message,strlen(message));
          }
        }
      }
    }
  }
  close(sockfd);
  return 0;
}
