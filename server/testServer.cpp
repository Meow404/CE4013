#include "udpServer.h"
#include "utils.h"
#include <iostream>

using namespace std;

// Driver code
int main() {
    char message[1024], buffer[1024];
    udpServer server(8080);
    server.recieveMessage(buffer, 1024);
    int id = unmarshalInt(buffer);
    int size = unmarshalInt(buffer[4]);
    string message = unmarshalString(buffer[8], size);
    std::cout << "Id : " << id << " message : " << message <<std::endl;

    marshalInt(1, buffer);
    marshalInt(15, buffer[4]);
    marshalString("HI FROM SERVER!", buffer[8]);
    server.sendMessage(message, 1024);
    return 0;
}
