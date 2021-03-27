#include "udpServer.h"

using namespace std;

// Driver code
int main() {
    char* message;
    udpServer s(8080);
    message = s.recieveMessage();
    s.sendMessage(message, sizeof(message));
    return 0;
}