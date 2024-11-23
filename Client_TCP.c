#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<poll.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX 2048
#define clients

int main(int argc,char * argv[]){
	int sockfd = 0;
	struct sockaddr_in server;
	char buffer[MAX];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(8085);
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));

	while(1){
		char message[MAX];
		fgets(message, MAX, stdin);
		send(sockfd,message,strlen(message),0);
		int v = read(sockfd,buffer,MAX);
		printf("%s",buffer);
	}
	close(sockfd);
	return 0;
}
