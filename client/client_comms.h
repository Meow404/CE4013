#ifndef _CLIENT_COMMS_H_
#define _CLIENT_COMMS_H_

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "../utilities/constants.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientSocket {
    SOCKET clientSocket;
    int clientLen, serverLen;
    struct sockaddr_in clientAddr, serverAddr;
    char buffer[MAX_BUFFSIZE];

    void createLocalClientAddr(char *portno);
    void createRemoteServerAddr(char *hostname, char *portno);

    public:
    ClientSocket(char *hostname, char *portno);
    int sendMsg(char *msg, int len, double failureRate);
    int recvMsg(char *buffer, int len, int timeout);
};

#endif
