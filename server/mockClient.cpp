// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include "utils.h"
#include <iostream>
#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char hello[MAXLINE];
    struct sockaddr_in servaddr;

    marshalInt(1, hello);
    marshalInt(15, &hello[4]);
    marshalString("HI FROM CLIENT!", &hello[8]);
    cout << hello << endl;
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        //exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    sendto(sockfd, (const char *)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *)&servaddr,
           sizeof(servaddr));
    printf("Hello message sent.\n");

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr *)&servaddr,
                 (socklen_t *)&len);
    buffer[n] = '\0';
    // printf("Server : %s\n", buffer);

    int id = unmarshalInt(hello);
    int size = unmarshalInt(&hello[4]);
    string message = unmarshalString(&hello[8], size);
    std::cout << "Id : " << id << " message : " << message <<std::endl;

    close(sockfd);
    return 0;
}