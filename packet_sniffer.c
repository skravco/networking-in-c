#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ether.h>  
#include <arpa/inet.h>

int main() {
    // Create a raw socket to capture packets
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read packet into buffer
        char buffer[65536];
        memset(buffer, 0, sizeof(buffer));
        int data_size = recv(sockfd, buffer, sizeof(buffer), 0);
        if (data_size < 0) {
            perror("recv failed");
            exit(EXIT_FAILURE);
        }

        // Parse IP header
        struct iphdr *ip_header = (struct iphdr *)(buffer + sizeof(struct ethhdr));
        // Extract source and destination IP addresses
        char source_ip[INET_ADDRSTRLEN];
        char dest_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->saddr), source_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip_header->daddr), dest_ip, INET_ADDRSTRLEN);

        // Parse TCP header
        struct tcphdr *tcp_header = (struct tcphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));
        // Extract source and destination ports
        unsigned short source_port = ntohs(tcp_header->source);
        unsigned short dest_port = ntohs(tcp_header->dest);

        // Print extracted information
        printf("Source IP: %s\n", source_ip);
        printf("Destination IP: %s\n", dest_ip);
        printf("Source Port: %u\n", source_port);
        printf("Destination Port: %u\n", dest_port);
    }

    // Close the socket
    close(sockfd);

    return 0;
}

