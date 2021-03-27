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

bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
 
    return true;
}

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char hello[MAXLINE] = "Client Open For Buisness";
    struct sockaddr_in servaddr;

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

    string message;
    int index = 0;
    cout << "\nEnter Value : ";
    std::getline(std::cin, message);

    while(message.compare("q") != 0){
        if (isNumber(message)){
            marshalInt(stoi(message), &hello[index]);
            index+=4;
        }
        else{
            marshalInt(message.size(), &hello[index]);
            index+=4;
            marshalString(message, &hello[index]);
            index+=message.size();
        }
        cout << "\nEnter Value : ";
        std::getline(std::cin, message);
    }

    sendto(sockfd, (const char *)hello, index,
           MSG_CONFIRM, (const struct sockaddr *)&servaddr,
           sizeof(servaddr));
    printf("Hello message sent.\n");

    while (true)
    {

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&servaddr,
                     (socklen_t *)&len);
        // buffer[n] = '\0';
        // printf("Server : %s\n", buffer);
        int i = 0, num;
        string message;
        while (i < n)
        {
            cout << buffer[i] << endl;

            switch (buffer[i++])
            {
            case 'd':
                num = unmarshalInt(&buffer[i]);
                cout << num << endl;
                i += 4;
                break;
            case 's':
                num = unmarshalInt(&buffer[i]);
                i += 4;
                message = unmarshalString(&buffer[i], num);
                i += num;
                cout << message << endl;
                break;
            default:
                cout << "Did not recieve valid string";
                break;
            }
        }
    }
    close(sockfd);
    return 0;
}