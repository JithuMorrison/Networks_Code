#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define MAX 2048

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[MAX];
    socklen_t servlen = sizeof(server);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8085);

    while(1) {
        fgets(buffer, MAX, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, servlen);
        int n = recvfrom(sockfd, buffer, MAX, 0, (struct sockaddr *)&server, &servlen);
        printf("Server: %s", buffer);
    }
    close(sockfd);
    return 0;
}
