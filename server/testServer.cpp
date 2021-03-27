#include "udpServer.h"
#include "iostream"

using namespace std;

// Driver code
int main() {
    char* message;
    udpServer server(8080);
    message = server.recieveMessage(message, 1024);
    cout << "Sending : " << message << endl;
    server.sendMessage(message, 1024);
    return 0;
}