#include <iostream>
#include <string>

#include "client_main.h"

using namespace std;

int main(int argc, char *argv[]) {
    char *hostname, *portno;
    int res = -1;
    int reqId = 0;
    string promptMessage = "\nCOMMANDS\n"    \
                           "[1] Query Facility Availability\n"    \
                           "[2] Book Facility\n"    \
                           "[3] Shift Booking Time\n"    \
                           "[4] Monitor Facility Availability\n"    \
                           "[5] Cancel Booking\n"    \
                           "[6] Extend Booking Period\n"    \
                           "[7] Exit\n"   \
                           "Input Command: ";
    int command;
    char buffer[MAX_BUFFSIZE];

    if (argc < 3) {
        cout << "Usage: ./Client [SERVER_ADDRESS] [PORT]" << endl;
        exit(1);
    }

    hostname = argv[1];
    portno = argv[2];
    cout << hostname << " " << portno << endl;
    ClientSocket clientSock(hostname, portno);

    while (command != EXIT) {
        cout << promptMessage;
        cin >> command;
        if (command < 1 || command > 7 || cin.fail()) {
            cerr << "ERROR: Invalid Command!";
            continue;
        }

        vector<char> requestMsg, payload;
        switch (command) {
            case QUERY:
                craftQueryReq(payload);
                // send sizeof(requestMsg)/sizeof(unsigned char)
                break;
            case NEW_BOOK:
                craftNewBookingReq(payload);
                break;
            case MOD_BOOK:
                craftModBookingReq(payload);
                break;
            case NEW_MONITOR:
                craftNewMonitorReq(payload);
                break;
            case CANCEL_BOOK:
                craftCancelBookingReq(payload);
                break;
            case MOD_MONITOR:
                craftModMonitorReq(payload);
                break;
            case EXIT:
                exit(1);
            default:
                cerr << "ERROR: Unknown Command";
                break;
        }
        if (payload.size() == 0) continue;

        // requestMsg.push_back(0); // Request message type
        // requestMsg.push_back(reqId);
        char marshalledCommand[4];
        marshalInt(command, marshalledCommand);
        // cout << "COMMAND: " << unmarshalInt(marshalledCommand) << endl;
        requestMsg.insert(requestMsg.end(), &marshalledCommand[0], &marshalledCommand[4]);
        // Do we really need client to send IP and port?
        // requestMsg.insert(requestMsg.end(), &hostname[0], &hostname[sizeof(hostname)/sizeof(char)]);
        // requestMsg.push_back(portno);
        requestMsg.insert(requestMsg.end(), payload.begin(), payload.end());

        res = clientSock.sendMsg(requestMsg.data(), requestMsg.size());
        if (res < 0) {
            cerr << "ERROR: Failed to send request.\n";
            continue;
        }

        res == 0;
        res = clientSock.recvMsg(buffer, MAX_BUFFSIZE);
        if (res <= 0) {
            cerr << "ERROR: Error receiving response\n";
            continue;
        }
        // cout << "SIZE RECEIVED: " << res << endl;
        handleResponse(command, buffer);

        reqId++;
    }
}
