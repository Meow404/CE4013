#ifndef UDPSERVER
#define UDPSERVER

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <WinSock2.h>

// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;

class udpServer
{
    int clientLen;
    SOCKET socketFd;
    WSADATA wsa;
    struct sockaddr_in serverAddress, clientAddress;

    public:
    udpServer(int port);
    int recieveMessage(char* buffer,  int bufferSize, int timeout = 0);
    void sendMessage(const char* buffer, int bufferSize);
    string getClientIP();
};

#endif
