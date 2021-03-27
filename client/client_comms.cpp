#include "client_comms.h"
#include "../utilities/constants.h"

void ClientSocket::createLocalClientAddr(int portno) {
    this->clientAddr.sin_family = AF_INET;
    this->clientAddr.sin_port = htons(0);  // Any port on local host
    this->clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);   // Local host
}

void ClientSocket::createRemoteServerAddr(char *hostname, int portno) {
    struct hostent *host;
    this->serverAddr.sin_family = AF_INET;
    if ((host = gethostbyname(hostname)) == NULL){
        perror("Unknown host name");
        exit(1);
    }
    this->serverAddr.sin_addr = *(struct in_addr *) (host->h_addr);   // Remote host
    this->serverAddr.sin_port = htons(portno);  // Specified port on remote
}

ClientSocket::ClientSocket(char *hostname, int portno) {
    if ((this->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failed to create client socket");
        exit(1);
    }

    createLocalClientAddr(portno);
    createRemoteServerAddr(hostname, portno);

    if (bind(this->sockfd, (struct sockaddr*) &clientAddr, sizeof(struct sockaddr_in)) < 0) {
        perror("Failed to bind client socket");
        exit(1);
    }

    this->clientLen = sizeof(this->clientAddr);
}

int create_socket(int portno) {

}