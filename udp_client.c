#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MSG_SIZE 1024

int main() {
    int sockfd;
    char buffer[MAX_MSG_SIZE];
    struct sockaddr_in server_addr;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // server information
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // desired port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // server's IP address

    // Prompt user to enter message
    printf("Enter message to send: ");
    fgets(buffer, MAX_MSG_SIZE, stdin);

    // Send message to server
    if (sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to server.\n");

    // Close the socket
    close(sockfd);

    return 0;
}

