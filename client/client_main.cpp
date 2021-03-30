#include <iostream>
#include <string>
#include <deque>

#include "client_main.h"

using namespace std;

int main(int argc, char *argv[]) {
    char *hostname, *portno;
    int res = -1;
    int reqId = 0;
    string promptMessage = "\nCOMMANDS\n"    \
                           "[1] Get Facility Names\n"
                           "[2] Query Facility Availability\n"    \
                           "[3] Book Facility\n"    \
                           "[4] Shift Booking Time\n"    \
                           "[5] Extend Booking Period\n"    \
                           "[6] Cancel Booking\n"    \
                           "[7] Monitor Facility Availability\n"    \
                           "[8] Exit\n"   \
                           "Input Command: ";
    int command;
    char buffer[MAX_BUFFSIZE];
    char marshalledMsgType[4];
    marshalInt(0, marshalledMsgType);

    if (argc != 3) {
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
        if (command < 1 || command > 8 || cin.fail() || !cin.good()) {
            cerr << "ERROR: Invalid Command!\n";
            break;
        }

        vector<char> requestMsg, payload;
        deque<int> queryDays;
        int day;
        string facilityName;
        // Monitor expiry tracker
        switch (command) {
            case GET_FAC:
                break;
            case QUERY:
                getQueryInput(facilityName, queryDays);
                nextQuery:
                requestMsg.clear();
                payload.clear();
                day = queryDays.front();
                craftQueryReq(payload, facilityName, day);
                queryDays.pop_front();
                break;
            case NEW_BOOK:
                craftNewBookingReq(payload);
                break;
            case SHIFT_BOOK:
                craftShiftBookingReq(payload);
                break;
            case EXTEND_BOOK:
                craftExtendBookingReq(payload);
                break;
            case CANCEL_BOOK:
                craftCancelBookingReq(payload);
                break;
            case NEW_MONITOR:
                craftNewMonitorReq(payload);
                break;
            case EXIT:
                exit(1);
            default:
                cerr << "ERROR: Unknown Command";
                break;
        }
        if (payload.empty()) continue;

        requestMsg.insert(requestMsg.end(), &marshalledMsgType[0], &marshalledMsgType[4]); // Request type message
        char marshalledReqId[4];
        marshalInt(reqId, marshalledReqId);
        requestMsg.insert(requestMsg.end(), &marshalledReqId[0], &marshalledReqId[4]);

        char marshalledCommand[4];
        marshalInt(command, marshalledCommand);
        requestMsg.insert(requestMsg.end(), &marshalledCommand[0], &marshalledCommand[4]);
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
        if (command == QUERY) {
            handleQueryRes(day, buffer);
        } else {
            handleResponse(command, buffer);
        }
        if (!queryDays.empty()) {
            reqId++;
            goto nextQuery;
        }

        reqId++;
    }
}
