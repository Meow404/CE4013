#ifndef UDPSERVER
#define UDPSERVER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#define AT_MOST_ONCE true
#define AT_LEAST_ONCE false
#define BUFFER_SIZE 1024

// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;

struct request_reply{
    string clientIp;
    int reqId;
    int replySize;
    string reply;
};

class udpServer
{
    int clientLen, timeout;
    SOCKET socketFd;
    WSADATA wsa;
    bool atMostOnce, atLeastOnce;
    struct sockaddr_in serverAddress, clientAddress;
    vector<request_reply> replies;

    public:
    udpServer(int port, bool invocation);
    int recieveMessage(char* buffer,  int bufferSize, int timeout = 0);
    void sendMessage(const char* buffer, int bufferSize);
    void addReply(int reqId, char* buffer, int bufferSize);
    bool resendReply(int reqId);
    string getClientIP();
};

#endif
