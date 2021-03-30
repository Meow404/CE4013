#ifndef UDPSERVER
#define UDPSERVER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>

#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#define AT_MOST_ONCE true
#define AT_LEAST_ONCE false
#define BUFFER_SIZE 4096

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
    int clientLen, timeout, port;
    SOCKET socketFd;
    WSADATA wsa;
    bool atMostOnce, atLeastOnce;
    struct sockaddr_in serverAddress, clientAddress;
    vector<request_reply> replies;
    double failureRate;

    public:
    udpServer(int port, bool invocation, double failureRate = 0.0);
    int recieveMessage(char* buffer,  int bufferSize, int timeout = 0);
    void sendMessage(const char* buffer, int bufferSize);
    void sendMessageToClient(const char* buffer, int bufferSize, sockaddr_in clientAddress);
    void addReply(int reqId, char* buffer, int bufferSize);
    bool resendReply(int reqId);
    string getClientIP();
    int getClientPort();
    struct sockaddr_in getClientSocketAddress();
};

#endif
