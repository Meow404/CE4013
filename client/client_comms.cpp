#include <iostream>

#include "client_comms.h"

void ClientSocket::createLocalClientAddr(char *portno) {
    this->clientAddr.sin_family = AF_INET;
    this->clientAddr.sin_port = htons(0);  // Any port on local host
    this->clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);   // Local host
}

void ClientSocket::createRemoteServerAddr(char *hostname, char *portno) {
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(atoi(portno));
    this->serverAddr.sin_addr.s_addr = inet_addr(hostname);

    // int iResult = getaddrinfo(hostname, portno, &serverAddr, &result);
    // if (iResult != 0) {
    //     printf("getaddrinfo failed with error: %d\n", iResult);
    //     WSACleanup();
    //     return 1;
    // }
}

ClientSocket::ClientSocket(char *hostname, char *portno) {
    this->clientSocket = INVALID_SOCKET;
    WSADATA wsaData;
    int iResult;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult  != NO_ERROR) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(1);
    }

    clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSocket == INVALID_SOCKET) {
        printf("socket failed with error %d\n", WSAGetLastError());
        exit(1);
    }

    createLocalClientAddr(portno);
    createRemoteServerAddr(hostname, portno);

    this->clientLen = sizeof(this->clientAddr);
    this->serverLen = sizeof(this->serverAddr);
}

int ClientSocket::sendMsg(char *msg, int len) {
    std::cout << "LENGTH SENT: " << len << std::endl;
    int res = sendto(this->clientSocket, msg, len, 0, (struct sockaddr *) &serverAddr, serverLen);
    if (res == SOCKET_ERROR) {
        printf("Error sending message with error code %d", WSAGetLastError());
    }
    std::cout << "MSG SENT: " << msg << std::endl;
    return res;
}

int ClientSocket::recvMsg(char *buffer, int len) {
    int res = recvfrom(this->clientSocket, buffer, len, 0, (struct sockaddr *) &serverAddr, (socklen_t*) &serverLen);
    if (!res) {
        std::cout << "No message received" << std::endl;
    }
    return res;
}
