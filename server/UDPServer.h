#ifndef UDPSERVER
#define UDPSERVER

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

class udpServer{
    int socketFd, clientLen;
    struct sockaddr_in serverAddress, clientAddress;


    public:
    udpServer(int port);
    char* recieveMessage();
    void sendMessage(const char* buffer, int bufferSize);
    string getClientIP();
};

#endif