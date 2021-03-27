#ifndef UDPSERVER
#define UDPSERVER

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>

using namespace std;

class udpServer
{
    int socketFd, clientLen;
    struct sockaddr_in serverAddress, clientAddress;

    public:
    udpServer(int port);
    char* recieveMessage();
    void sendMessage(const char *buffer, int bufferSize);
    string getClientIP();
};

#endif
