#include "udpServer.h"
#include <stdio.h>
#include <iostream>
// #include <arpa/inet.h>

using namespace std;

/**
 * @brief  Constructor for UDP server
 * @param  port: port of the UDP server
 * @param  invocation: At most once or at least once invocation
 * @param  failureRate: failure rate of server
 * @retval None
 */
udpServer::udpServer(int port, bool invocation, double failureRate)
{

    atMostOnce = invocation;
    atLeastOnce = !invocation;
    this->port = port;
    this->failureRate = failureRate;

    cout << "Initialising Winsock..." << endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
    }

    // Creating socket file descriptor
    if ((socketFd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        perror("SOCKET CREATION FAILED");
        exit(EXIT_FAILURE);
    }

    // Filling server information
    serverAddress.sin_family = AF_INET; // IPv4
    serverAddress.sin_addr.S_un.S_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Bind the socket with the server address
    if (bind(socketFd, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    char *ip = inet_ntoa(serverAddress.sin_addr);
    cout << "Server Listening @ " << (string)ip << ":" << port << endl;

    clientLen = sizeof(clientAddress);
}

/**
 * @brief  Wait for message from socket
 * @param  buffer: buffer to store the message
 * @param  bufferSize: size of the buffer
 * @param  timeout: time before which we stop waiting for a message
 * @retval number of bytes recieved
 */
int udpServer::recieveMessage(char* buffer, int bufferSize, int timeout)
{
    if (timeout != 0)
    {
        struct timeval tv;
        tv.tv_sec = timeout;
        tv.tv_usec = 0;

        setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv));
    }

    int n;
    do
    {
        n = recvfrom(socketFd, buffer, bufferSize, 0, (struct sockaddr *)&clientAddress, &clientLen);
        if (n < 0)
            cout << "ERROR reading from socket. Trying again ..." << endl;
    } while (n == -1);
    cout << "Client : " << getClientIP() << " # of bytes : " << n << endl;

    return n;
}

/**
 * @brief  Send message to client
 * @param  buffer: buffer to store of the message to be sent
 * @param  bufferSize: size of buffer
 * @retval None
 */
void udpServer::sendMessage(const char *buffer, int bufferSize)
{
    srand(time(0));
    if (static_cast <float> (rand()) / RAND_MAX > failureRate)
    {

        cout << "Sending Message to " << getClientIP() << endl;
        int n = sendto(socketFd, buffer, bufferSize, 0, (const struct sockaddr *)&clientAddress, clientLen);
        if (n < 0)
            cout << "ERROR writing back to socket" << endl;
    }
    else
        cout << "[ RETURN FAILURE GENERATED ]" << endl;
}

/**
 * @brief  Send message to a client based on socket address of the client
 * @param  buffer: the buffer to store the message to be sent
 * @param  bufferSize: size of the message of te buffer
 * @param  clientAddress: socket address of the client
 * @retval None
 */
void udpServer::sendMessageToClient(const char *buffer, int bufferSize, sockaddr_in clientAddress)
{
    cout << "Sending Message to " << getClientIP() << endl;
    int n = sendto(socketFd, buffer, bufferSize, 0, (const struct sockaddr *)&clientAddress, clientLen);
    if (n < 0)
        cout << "ERROR writing back to socket" << endl;
}

/**
 * @brief  Get IP Address of the client
 * @retval client IP
 */
string udpServer::getClientIP()
{
    char *ip = inet_ntoa(clientAddress.sin_addr);
    return (string)ip;
}

/**
 * @brief  Add reply buffer based on request ID
 * @param  reqId: ID of request 
 * @param  buffer: buffer that stores the reply
 * @param  bufferSize: size of the buffer to be stored
 * @retval None
 */
void udpServer::addReply(int reqId, char *buffer, int bufferSize)
{

    for (int i = replies.size() - 1; i >= 0; i--)
        if (replies[i].clientIp.compare(getClientIP()) == 0)
        {
            replies[i].reqId = reqId;
            replies[i].replySize = bufferSize;
            replies[i].reply = string(buffer, bufferSize);
            return;
        }
    request_reply req;
    req.clientIp = getClientIP();
    req.reqId = reqId;
    req.replySize = bufferSize;
    req.reply = string(buffer, bufferSize);

    replies.push_back(req);
}

/**
 * @brief  Resend reply for At most once invocation
 * @param  reqId: request ID for the reply
 * @retval true if reply is resent
 */
bool udpServer::resendReply(int reqId)
{
    if (atMostOnce)
    {

        for (int i = replies.size() - 1; i >= 0; i--)
            if (replies[i].clientIp.compare(getClientIP()) == 0 && replies[i].reqId == reqId)
            {
                cout << "Resending reply ... ";
                sendMessage(replies[i].reply.c_str(), replies[i].replySize);
                return true;
            }
    }
    return false;
}

/**
 * @brief  Port of the client
 * @retval client port
 */
int udpServer::getClientPort()
{
    return port;
}

/**
 * @brief  Get socket address of the client
 * @retval socket address of the client
 */
struct sockaddr_in udpServer::getClientSocketAddress()
{
    return clientAddress;
}
