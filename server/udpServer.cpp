#include "udpServer.h"

using namespace std;

udpServer::udpServer(int port)
{
    // Creating socket file descriptor
    if ((socketFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("SOCKET CREATION FAILED");
        exit(EXIT_FAILURE);
    }

    // Filling server information
    serverAddress.sin_family = AF_INET; // IPv4
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Bind the socket with the server address
    if (bind(socketFd, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    clientLen = sizeof(clientAddress);
}
char *udpServer::recieveMessage()
{
    char buffer[1024];
    int n = recvfrom(socketFd, (char *)buffer, 1024, 0, (struct sockaddr *)&clientAddress, (socklen_t *)&clientLen);

    cout << "Client : " << getClientIP() << " Message : " << buffer;
    return buffer;
}
void udpServer::sendMessage(const char *buffer, int bufferSize)
{
    sendto(socketFd, buffer, bufferSize, 0, (const struct sockaddr *)&clientAddress, clientLen);
}
string udpServer::getClientIP()
{
    char ip[16];
    inet_ntop(AF_INET, &clientAddress, ip, 16);
    return (string) ip;
}
