#include <iostream>
#include <string>

#include "client_main.h"

using namespace std;
using namespace requests;

int main(int argc, char *argv[]) {
    char *hostname;
    int portno, serverRes;
    string promptMessage = "\nCOMMANDS\n"    \
                           "[1] Query Facility Availability\n"    \
                           "[2] Book Facility\n"    \
                           "[3] Modify Booking Time\n"    \
                           "[4] Monitor Facility Availability\n"    \
                           "[5] Cancel Booking\n"    \
                           "[6] Modify Monitor Duration\n"    \
                           "[7] Exit\n"   \
                           "Input Command: ";
    int command;

    hostname = argv[0];
    portno = atoi(argv[1]);
    ClientSocket clientSock(hostname, portno);

    while (command != request::EXIT) {
        cout << promptMessage << endl;
        cin >> command;
        if (command < 1 || command > 7 || cin.fail()) {
            perror("Invalid Command!");
            continue;
        }

        char *requestMsg;
        switch (command) {
            case request::QUERY:
                requestMsg = craftQueryReq();
                cout << requestMsg << endl;
                // send sizeof(requestMsg)/sizeof(unsigned char)
                break;
            case request::NEW_BOOK:
                requestMsg = craftNewBookingReq();
                break;
            case request::MOD_BOOK:
                requestMsg = craftModBookingReq();
                break;
            case request::NEW_MONITOR:
                requestMsg = craftNewMonitorReq();
                break;
            case request::CANCEL_BOOK:
                requestMsg = craftCancelBookingReq();
                break;
            case request::MOD_MONITOR:
                requestMsg = craftModMonitorReq();
                break;
            default:
                perror("Unknown Command");
                break;
        }
    }
}
