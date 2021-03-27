#include <iostream>
#include <string>

#include "client_main.h"

using namespace std;
using namespace requests;

int main(int argc, char *argv[]) {
    char *hostname;
    int portno;
    int res = -1;
    int reqId = 0;
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
    char buffer[MAX_BUFFSIZE];

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

        vector<char> requestMsg, payload;
        switch (command) {
            case request::QUERY:
                payload = craftQueryReq();
                // cout << payload.data() << endl;
                // send sizeof(requestMsg)/sizeof(unsigned char)
                break;
            case request::NEW_BOOK:
                payload = craftNewBookingReq();
                break;
            case request::MOD_BOOK:
                payload = craftModBookingReq();
                break;
            case request::NEW_MONITOR:
                payload = craftNewMonitorReq();
                break;
            case request::CANCEL_BOOK:
                payload = craftCancelBookingReq();
                break;
            case request::MOD_MONITOR:
                payload = craftModMonitorReq();
                break;
            default:
                perror("Unknown Command");
                break;
        }

        requestMsg.push_back(command);
        requestMsg.push_back(reqId);
        // Do we really need client to send IP and port?
        requestMsg.insert(requestMsg.end(), &hostname[0], &hostname[sizeof(hostname)/sizeof(char)]);
        requestMsg.push_back(portno);
        requestMsg.insert(requestMsg.end(), payload.begin(), payload.end());

        while (res < 0) {
            res = clientSock.sendMsg(requestMsg.data(), requestMsg.size());
        }
        res = 0;

        while (!res) {
            res = clientSock.recvMsg(buffer, MAX_BUFFSIZE);
        }
        handleResponse(command, buffer);

        reqId++;
    }
}
