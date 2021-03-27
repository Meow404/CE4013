#include "udpServer.h"
#include "iostream"

using namespace std;

// Driver code
int main() {
    char* message;
    udpServer server(8080);
    message = server.recieveMessage();
    cout << "Sending : " << message << endl;
    server.sendMessage(message, sizeof(message));
    return 0;
}