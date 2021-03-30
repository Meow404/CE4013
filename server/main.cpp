#include "facilityManager.h"
#include "udpServer.h"
#include "commHandler.h"

using namespace std;

int main(int argc, char **argv)
{
    int port = 8080;
    bool invocation = AT_LEAST_ONCE;
    double failureRate = 0.0;
    if (argc > 1)
        port = stoi(argv[1]);

    if (argc > 2 && stoi(argv[2]) == 1)
        invocation = AT_MOST_ONCE;

    if (argc > 3)
        failureRate = stod(argv[3]);

    cout << "=============================================" << endl;
    cout << "~ SERVER CONFIGURATION ~" << endl;
    cout << "PORT : " << port << endl;

    cout << "INVOCATION : ";
    if (invocation)
        cout << "AT MOST ONCE" << endl;
    else
        cout << "AT LEAST ONCE" << endl;
    cout << "FAILURE RATE : " << failureRate << endl;
    cout << "=============================================" << endl << endl;

    facilityManager FM("facilities.txt");
    udpServer server(port, invocation, failureRate);
    commHandler cm(&server, &FM);
    cm.start();
}