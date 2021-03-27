#include "udpServer.h"
#include "utils.h"
#include <iostream>

using namespace std;

// Driver code
int main() {
    char buffer[1024];
    udpServer server(8080);
    server.recieveMessage(buffer, 1024);
    // int id = unmarshalInt(buffer);
    // cout << id << endl;
    // int size = unmarshalInt(&buffer[4]);
    // cout << size << endl;
    // string message = unmarshalString(&buffer[8], size);
    // std::cout << "Id : " << id << " message : " << message <<std::endl;

    buffer[0] = 'd';
    marshalInt(10, &buffer[1]);
    buffer[5] = 's';
    marshalInt(15, &buffer[6]);
    marshalString("HI FROM SERVER!", &buffer[10]);
    server.sendMessage(buffer, 1024);
    return 0;
}
