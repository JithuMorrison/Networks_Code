#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<poll.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX 2048
#define clients

int main(int argc,char * argv[]){
    printf("Starting server...\n");	
	int sockfd,newsockfd = 0;
	struct sockaddr_in server,client;
    socklen_t clilen = sizeof(client);
	char buffer[MAX];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8085);
	bind(sockfd,(struct sockaddr *)&server,sizeof(server));
    listen(sockfd,5);
    newsockfd = accept(sockfd,(struct sockaddr *)&client,&clilen);
    printf("Client Connected...\n");

	while(1){
        int v = read(newsockfd,buffer,MAX);
		printf("%s",buffer);
		char message[MAX];
		fgets(message, MAX, stdin);
		send(newsockfd,message,strlen(message),0);
	}
    close(newsockfd);
	close(sockfd);
	return 0;
}
