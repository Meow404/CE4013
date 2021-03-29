#include <iostream>
#include <string>

#include "response_handler.h"
#include "proxy.h"

void handleQueryRes(char buffer[MAX_BUFFSIZE]);

void handleNewBookingRes(char buffer[MAX_BUFFSIZE]) {
    int ind = 0, resCode;

    resCode = getInt(buffer, &ind);
    if (resCode == 0) {
        std::cout << "BOOKING SUCCESSFUL!" << std::endl;
        std::string confirmID = getString(buffer, &ind);
        std::cout << "Confirmation ID: " << confirmID << std::endl;
    } else if (resCode == 1) {
        std::cout << "BOOKING FAILED: No facility by that name exists." << std::endl;
    } else if (resCode == 2) {
        std::cout << "BOOKING FAILED: Facility is unavailable." << std::endl;
    } else if (resCode == 3) {
        std::cout << "BOOKING FAILED: Invalid time values." << std::endl;
    } else {
        std::cout << "Unknown Response Code " << resCode << std::endl;
    }
}

void handleModBookingRes(char buffer[MAX_BUFFSIZE]);
void handleNewMonitorRes(char buffer[MAX_BUFFSIZE]);
void handleCancelBookingRes(char buffer[MAX_BUFFSIZE]);
void handleModMonitorRes(char buffer[MAX_BUFFSIZE]);

void handleResponse(int command, char buffer[MAX_BUFFSIZE]) {
    switch (command) {
        // case QUERY:
        //     handleQueryRes(buffer);
        //     break;
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
            perror("Unknown response");
            break;
    }
}
