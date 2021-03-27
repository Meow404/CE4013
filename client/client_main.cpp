#include <iostream>
#include <string>

#include "client_main.h"

using namespace std;
using namespace requests;

int main() {
    string promptMessage = "\nCOMMANDS\n"    \
                           "[1] Query Facility Availability\n"    \
                           "[2] Book Facility\n"    \
                           "[3] Modify Booking Time\n"    \
                           "[4] Monitor Facility Availability\n"    \
                           "[5] Cancel Booking\n"    \
                           "[6] Modify Monitor Duration\n"    \
                           "[7] Exit\n"   \
                           "Input Command: ";
    int init_sockfd, comm_sockfd, portno;
    int command;

    while (command != request::EXIT) {
        cout << promptMessage << endl;
        cin >> command;
        if (command < 1 || command > 7 || cin.fail()) {
            cout << "Invalid Command!\n";
            continue;
        }

        switch (command) {
            case request::QUERY:
                craftQueryReq();
                break;
            case request::NEW_BOOK:
                craftNewBookingReq();
                break;
            case request::MOD_BOOK:
                craftModBookingReq();
                break;
            case request::NEW_MONITOR:
                craftNewMonitorReq();
                break;
            case request::CANCEL_BOOK:
                craftCancelBookingReq();
                break;
            case request::MOD_MONITOR:
                craftModMonitorReq();
                break;
            default:
                cout << "Unknown Command" << endl;
                break;
        }
    }
}
