#ifndef _CLIENT_COMMS_H_
#define _CLIENT_COMMS_H_

#include <winsock.h>

class ClientSocket {
    int sockfd, clientLen, serverLen;
    struct sockaddr_in clientAddr, serverAddr;
    char buffer[MAX_BUFFSIZE];

    void createLocalClientAddr(int portno);
    void createRemoteServerAddr(char *hostname, int portno);

    public:
    ClientSocket(char *hostname, int portno);
    int sendMsg(char *msg, int len);
    int recvMsg(char *buffer, int len);
};

#endif
