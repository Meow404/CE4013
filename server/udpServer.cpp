#include "udpServer.h"
#include "iostream"
#include <arpa/inet.h>

using namespace std;

udpServer::udpServer(int port)
{
    // Creating socket file descriptor
    if ((socketFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("SOCKET CREATION FAILED");
        exit(EXIT_FAILURE);
    }

    // Filling server information
    serverAddress.sin_family = AF_INET; // IPv4
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Bind the socket with the server address
    if (bind(socketFd, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    clientLen = sizeof(clientAddress);
}

int udpServer::recieveMessage(char *buffer, int bufferSize, int timeout)
{
    if (timeout != 0)
    {
        struct timeval tv;
        tv.tv_sec = timeout;
        tv.tv_usec = 0;

        setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv));
    }

    int n = recvfrom(socketFd, buffer, bufferSize, 0, (struct sockaddr *)&clientAddress, (socklen_t *)&clientLen);
    cout << "Client : " << getClientIP() << " Message : " << buffer << endl;

    return n;
}

void udpServer::sendMessage(const char *buffer, int bufferSize)
{
    cout << "Sending Message";
    int n = sendto(socketFd, buffer, bufferSize, 0, (const struct sockaddr *)&clientAddress, clientLen);
    if (n<0) cout << "ERROR writing back to socket" << endl;
}

string udpServer::getClientIP()
{
    char ip[16];
    inet_ntop(AF_INET, &clientAddress, ip, 16);
    return (string)ip;
}

