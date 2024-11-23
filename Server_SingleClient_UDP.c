#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<poll.h>

#define MAX 2048
#define CLIENTS 10

int main(){
    printf("Starting UDP server...\n");
    int sockfd = 0;
    struct sockaddr_in server;
    socklen_t servlen = sizeof(server);
    char buffer[MAX];
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8085);
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    printf("UDP Server running...\n");

    while(1) {
        int n = recvfrom(sockfd, buffer, MAX, 0, (struct sockaddr *)&server, &servlen);
        printf("Client: %s", buffer);
        fgets(buffer, MAX, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, servlen);
    }
    close(sockfd);
    return 0;
}
