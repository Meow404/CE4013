#ifndef UDPSERVER
#define UDPSERVER

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

using namespace std;

class udpServer
{
    int socketFd, clientLen;
    struct sockaddr_in serverAddress, clientAddress;

    public:
    udpServer(int port);
    char *udpServer::recieveMessage();
    void udpServer::sendMessage(const char *buffer, int bufferSize);
    string udpServer::getClientIP();
}

#endif
