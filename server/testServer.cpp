#include "udpServer.h"
#include "utils.h"
#include <iostream>

using namespace std;

// Driver code
int main() {
    char buffer[1024];
    udpServer server(8080);
    server.recieveMessage(buffer, 1024);
    int id = unmarshalInt(buffer);
    cout << id << endl;
    int size = unmarshalInt(&buffer[4]);
    cout << size << endl;
    string message = unmarshalString(&buffer[8], size);
    std::cout << "Id : " << id << " message : " << message <<std::endl;

    marshalInt(10, buffer);
    marshalInt(15, &buffer[4]);
    marshalString("HI FROM SERVER!", &buffer[8]);
    int num = unmarshalInt(buffer);
    cout << num << endl;
    num = unmarshalInt(&buffer[4]);
    cout << num << endl;
    message = unmarshalString(&buffer[8], num);
    cout << message << endl;
    cout << buffer << endl;
    server.sendMessage(buffer, 1024);
    return 0;
}
