#include <iostream>
#include <string>

#include "response_handler.h"
#include "proxy.h"

using namespace std;

void handleQueryRes(char buffer[MAX_BUFFSIZE]) {
    int ind = 0, resCode;

    resCode = getInt(buffer, &ind);
    if (resCode == 0) {
        int numFreeSlots = getInt(buffer, &ind);
        struct daytime::duration resDuration;
        resDuration.startDay = daytime::day::MONDAY;
        resDuration.endDay = daytime::day::MONDAY;
        cout << "UNAVAILABLE SLOTS:" << endl;
        for (int i = 0; i < numFreeSlots; i++) {
            getDurationTimeOnly(buffer, &ind, &resDuration);
            cout << daytime::getDayStr(resDuration.startDay) << " ";
            printf("%02d:%02d - %02d:%02d\n",
                    resDuration.startTime.hour, resDuration.startTime.minute,
                    resDuration.endTime.hour, resDuration.endTime.minute);
        }
    } else if (resCode == 1) {
        cout << "\nQUERY FAILED: No facility by that name exists." << endl;
    } else if (resCode == 2) {
        cout << "\nQUERY FAILED: Query Range Out Of Bounds" << endl;
    } else {
        cout << "\nUnknown Response Code " << resCode << endl;
    }
}

void handleNewBookingRes(char buffer[MAX_BUFFSIZE]) {
    int ind = 0, resCode;

    resCode = getInt(buffer, &ind);
    if (resCode == 0) {
        cout << "\nBOOKING SUCCESSFUL!" << endl;
        cout << "Confirmation ID: " << getString(buffer, &ind) << endl;
    } else if (resCode == 1) {
        cout << "\nBOOKING FAILED: No facility by that name exists." << endl;
    } else if (resCode == 2) {
        cout << "\nBOOKING FAILED: Facility is unavailable." << endl;
    } else if (resCode == 3) {
        cout << "\nBOOKING FAILED: Invalid time values." << endl;
    } else {
        cout << "\nUnknown Response Code " << resCode << endl;
    }
}

void handleModBookingRes(char buffer[MAX_BUFFSIZE]);
void handleNewMonitorRes(char buffer[MAX_BUFFSIZE]);
void handleCancelBookingRes(char buffer[MAX_BUFFSIZE]);
void handleModMonitorRes(char buffer[MAX_BUFFSIZE]);

void handleResponse(int command, char buffer[MAX_BUFFSIZE]) {
    switch (command) {
        case QUERY:
            handleQueryRes(buffer);
            break;
        case NEW_BOOK:
            handleNewBookingRes(buffer);
            break;
        // case MOD_BOOK:
        //     handleModBookingRes(buffer);
        //     break;
        // case NEW_MONITOR:
        //     handleNewMonitorRes(buffer);
        //     break;
        // case CANCEL_BOOK:
        //     handleCancelBookingRes(buffer);
        //     break;
        // case MOD_MONITOR:
        //     handleModMonitorRes(buffer);
        //     break;
        default:
            std::cerr << "ERROR: Unknown response" << std::endl;
            break;
    }
}
