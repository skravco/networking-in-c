#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MSG_SIZE 1024
#define PORT 12345 // Desired port

int main() {
    int sockfd;
    char buffer[MAX_MSG_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // Fill server information
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP server listening on port %d...\n", PORT);

    // Receive message from client
    int len = recvfrom(sockfd, (char *)buffer, MAX_MSG_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
    buffer[len] = '\0';
    printf("Message from client: %s\n", buffer);

    // Close the socket
    close(sockfd);

    return 0;
}

