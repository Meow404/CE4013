#include <iostream>
#include <string>

#include "response_handler.h"
#include "proxy.h"

using namespace std;

void handleQueryRes(int day, char buffer[MAX_BUFFSIZE]) {
    int ind = 0, resCode;

    resCode = getInt(buffer, &ind);
    if (resCode == 0) {
        int numFreeSlots = getInt(buffer, &ind);
        struct daytime::duration resDuration;
        resDuration.startDay = daytime::getDay(day);
        resDuration.endDay = daytime::getDay(day);
        cout << endl << daytime::getDayStr(resDuration.startDay) << " Availability:" << endl;
        for (int i = 0; i < numFreeSlots; i++) {
            getDurationTimeOnly(buffer, &ind, &resDuration);
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

void handleShiftBookingRes(char buffer[MAX_BUFFSIZE]) {
    int ind = 0, resCode;

    resCode = getInt(buffer, &ind);
    if (resCode == 0) {
        cout << "\nBOOKING SHIFT SUCCESSFUL!" << endl;
        cout << "New Confirmation ID: " << getString(buffer, &ind) << endl;
    } else if (resCode == 1) {
        cout << "\nBOOKING SHIFT FAILED: No such confirmation ID." << endl;
    } else if (resCode == 2) {
        cout << "\nBOOKING SHIFT FAILED: Facility is unavailable." << endl;
    } else if (resCode == 3) {
        cout << "\nBOOKING FAILED FAILED: Invalid time values." << endl;
    } else {
        cout << "\nUnknown Response Code " << resCode << endl;
    }
}

void handleNewMonitorRes(char buffer[MAX_BUFFSIZE]) {
    int ind = 0, resCode;

    resCode = getInt(buffer, &ind);
    if (resCode == 0) {
        cout << "\nMONITORING SUCCESSFUL!" << endl;
    } else if (resCode == 1) {
        cout << "\nMONITORING FAILED: No such facility." << endl;
    } else if (resCode == 2) {
        cout << "\nMONITORING FAILED: Invalid time values." << endl;
    } else {
        cout << "\nUnknown Response Code " << resCode << endl;
    }
}

void handleCancelBookingRes(char buffer[MAX_BUFFSIZE]) {
    int ind = 0, resCode;

    resCode = getInt(buffer, &ind);
    if (resCode == 0) {
        cout << "\nBOOKING SUCCESSFULLY CANCELLED" << endl;
    } else if (resCode == 1) {
        cout << "\nBOOKING CANCEL FAILED: No such confirmation ID." << endl;
    } else {
        cout << "\nUnknown Response Code " << resCode << endl;
    }
}

void handleExtendBookingRes(char buffer[MAX_BUFFSIZE]) {
    int ind = 0, resCode;

    resCode = getInt(buffer, &ind);
    if (resCode == 0) {
        cout << "\nBOOKING EXTEND SUCCESSFUL!" << endl;
        cout << "Confirmation ID: " << getString(buffer, &ind) << endl;
    } else if (resCode == 1) {
        cout << "\nBOOKING EXTEND FAILED: No such confirmation ID." << endl;
    } else if (resCode == 2) {
        cout << "\nBOOKING EXTEND FAILED: Facility is unavailable." << endl;
    } else if (resCode == 3) {
        cout << "\nBOOKING EXTEND FAILED: Invalid time values." << endl;
    } else {
        cout << "\nUnknown Response Code " << resCode << endl;
    }
}

void handleResponse(int command, char buffer[MAX_BUFFSIZE]) {
    switch (command) {
        case GET_FAC:
            break;
        case NEW_BOOK:
            handleNewBookingRes(buffer);
            break;
        case SHIFT_BOOK:
            handleShiftBookingRes(buffer);
            break;
        case NEW_MONITOR:
            handleNewMonitorRes(buffer);
            break;
        case CANCEL_BOOK:
            handleCancelBookingRes(buffer);
            break;
        case EXTEND_BOOK:
            handleExtendBookingRes(buffer);
            break;
        default:
            std::cerr << "ERROR: Unknown response" << std::endl;
            break;
    }
}
