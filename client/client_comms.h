#ifndef _CLIENT_COMMS_H_
#define _CLIENT_COMMS_H_

#include <winsock.h>

class ClientSocket {
    int sockfd, clientLen;
    struct sockaddr_in clientAddr, serverAddr;

    void createLocalClientAddr(int portno);
    void createRemoteServerAddr(char *hostname, int portno);

    public:
    ClientSocket(char *hostname, int portno);
};

#endif
