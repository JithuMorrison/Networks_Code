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
    int sockfd, inc = 0;
    struct sockaddr_in server, client[CLIENTS];
    socklen_t clilen = sizeof(struct sockaddr_in);
    char buffer[MAX];
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8085);
    
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    struct pollfd fds[2];
    fds[0].fd = sockfd;
    fds[0].events = POLLIN;
    fds[1].fd = fileno(stdin);
    fds[1].events = POLLIN;
    printf("UDP Server running...\n");

    while (1) {
        int pol = poll(fds, 2, 3000);
        if (pol > 0) {
            if (fds[0].revents & POLLIN) {
                struct sockaddr_in client_addr;
                int r = recvfrom(sockfd, buffer, MAX, 0, (struct sockaddr *)&client_addr, &clilen);
                if (r > 0) {
                    printf("%s", buffer);
                    int known_client = 0;
                    for (int i = 0; i < inc; i++) {
                        if (client[i].sin_addr.s_addr == client_addr.sin_addr.s_addr && client[i].sin_port == client_addr.sin_port) 
                        {
                            known_client = 1;
                            break;
                        }
                    }
                    if (!known_client && inc < CLIENTS) {
                        client[inc++] = client_addr;
                        printf("New client added\n");
                    }
                }
            }
            if (fds[1].revents & POLLIN) {
                char message[MAX];
                fgets(message, MAX, stdin);
                for (int i = 0; i < inc; i++) {
                    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&client[i], clilen);
                }
            }
        }
    }
    close(sockfd);
    return 0;
}
