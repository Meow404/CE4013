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
    struct hostent *host;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        //exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    host = gethostbyname("localhost");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr = *(struct in_addr *)(host->h_addr);

    int n, len;

    string message;
    int index = 0;
    cout << "\nEnter Value : ";
    std::getline(std::cin, message);

    while (message.compare("q") != 0)
    {
        if (message.size() < 6 && isNumber(message))
        {
            marshalInt(stoi(message), &hello[index]);
            index += 4;
        }
        else
        {
            marshalInt(message.size(), &hello[index]);
            index += 4;
            marshalString(message, &hello[index]);
            index += message.size();
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
        cout << "Eaiting for message ..." << endl;

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     0, (struct sockaddr *)&servaddr,
                     (socklen_t *)&len);
        cout << "MESSAGE RECIEVED " << n << " bytes" << endl;
        // buffer[n] = '\0';
        // printf("Server : %s\n", buffer);
        int i = 0, num, date[4];
        string message;
        while (i < n)
        {
            cout << buffer[i] << endl;

            switch (buffer[i++])
            {
            case 'd':
            {
                num = unmarshalInt(&buffer[i]);
                cout << num << endl;
                i += 4;
                break;
            }
            case 's':
            {
                num = unmarshalInt(&buffer[i]);
                i += 4;
                cout << num << endl;
                message = unmarshalString(&buffer[i], num);
                i += num;
                cout << message << endl;
                break;
            }
            case 't':
            {

                date[0] = unmarshalInt(&buffer[i]);
                i += 4;
                date[1] = unmarshalInt(&buffer[i]);
                i += 4;
                date[2] = unmarshalInt(&buffer[i]);
                i += 4;
                date[3] = unmarshalInt(&buffer[i]);
                i += 4;
                cout << date[0] << ":" << date[1] << " - " << date[2] << ":" << date[3] << endl;
                break;
            }
            default:
            {
                cout << "Did not recieve valid string";
                i = n;
                break;
            }
            }
        }
    }
    close(sockfd);
    return 0;
}