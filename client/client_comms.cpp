#include <iostream>

#include "client_comms.h"

/**
 * @brief  Fill struct for local Client address
 * @param  portno Port number for Client
 * @retval None
 */
void ClientSocket::createLocalClientAddr(char *portno) {
    this->clientAddr.sin_family = AF_INET;
    this->clientAddr.sin_port = htons(0);  // Any port on local host
    this->clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);   // Local host
}

/**
 * @brief  Fill struct for remote Server address
 * @param  hostname Host name of remote Server
 * @param  portno Port number of Server
 * @retval None
 */
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

/**
 * @brief  ClientSocket constructor to create socket
 * @param  hostname Host name of remote Server
 * @param  portno Port number of socket connection
 * @retval None
 */
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

/**
 * @brief  Send message through socket
 * @param  msg Message to send through socket
 * @param  len Length of message to send through socket
 * @param  failureRate Rate of simulated request loss
 * @retval None
 */
int ClientSocket::sendMsg(char *msg, int len, double failureRate) {
    double failVal = ((double) rand()) / ((double) RAND_MAX);
    int res = 0;

    if (failVal > failureRate) {
        int res = sendto(this->clientSocket, msg, len, 0, (struct sockaddr *) &serverAddr, serverLen);
        if (res == SOCKET_ERROR) {
            printf("Error sending message with error code %d", WSAGetLastError());
        }
    } else {
        std::cout << "\nREQUEST MESSAGE LOSS SIMULATED" << std::endl;
    }
    return res;
}

/**
 * @brief  Receive message from socket
 * @param  buffer Buffer to store received message
 * @param  len Length of expected message received
 * @param  timeout Timeout for socket to receive message
 * @retval None
 */
int ClientSocket::recvMsg(char *buffer, int len, int timeout) {
    if (timeout > 0) {
        DWORD dw = timeout;
        setsockopt(this->clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &dw, sizeof(dw));
    }

    int res = recvfrom(this->clientSocket, buffer, len, 0, (struct sockaddr *) &serverAddr, (socklen_t*) &serverLen);
    if (!res) {
        std::cout << "No message received" << std::endl;
    }
    return res;
}
