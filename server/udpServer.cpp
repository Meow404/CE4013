#include "udpServer.h"
#include <stdio.h>
#include <iostream>
#include <ws2tcpip.h>
#include <windows.h>
// #include <arpa/inet.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library

using namespace std;

udpServer::udpServer(int port)
{

    struct sockaddr_in server;
    cout << "Initialising Winsock..." << endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
    }

    // Creating socket file descriptor
    if ((socketFd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
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

    char *ip = inet_ntoa(serverAddress.sin_addr);
    cout << "Server Listening @ " << (string)ip << ":" << port << endl;

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

    int n = recvfrom(socketFd, buffer, bufferSize, 0, (struct sockaddr *)&clientAddress, &clientLen);
    cout << "Client : " << getClientIP() << " # of bytes : " << n << endl;

    return n;
}

void udpServer::sendMessage(const char *buffer, int bufferSize)
{
    cout << "Sending Message to "<< getClientIP() << endl;
    int n = sendto(socketFd, buffer, bufferSize, 0, (const struct sockaddr *)&clientAddress, clientLen);
    if (n < 0)
        cout << "ERROR writing back to socket" << endl;
}

string udpServer::getClientIP()
{
    char *ip = inet_ntoa(clientAddress.sin_addr);
    return (string)ip;
}
