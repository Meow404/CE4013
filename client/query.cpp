#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "query.h"

/** Request Format:
 *  <facility name size><facility name><list of days>
 */
void craftQueryReq(std::vector<char> &payload) {
    std::string daytimePrompt =
    "[DAY] -> 0 = Mon, 1 = Tues, 2 = Wed, 3 = Thurs, 4 = Fri, 5 = Sat, 6 = Sun\n"  \
    "Input multiple days as [DAY] [DAY] [DAY] (\"0 1 2\" for \"Mon Tues Wed\"\n)" \
    "Days To Check: ";
    std::string daysStr;
    std::string facilityName;  // Unknown size so use string instead of char array
    std::vector<int> days;

    std::cout << "Facility Name: ";
    std::cin.ignore();
    std::getline(std::cin, facilityName);
    std::cout << daytimePrompt;
    std::getline(std::cin, daysStr);
    std::istringstream stm(daysStr);
    int temp;
    while (stm >> temp) {
        days.push_back(temp);
    }

    if (facilityName.empty() || days.empty()) {
        std::cout << "No facility name or days specified";
    }
    
    payload.push_back(facilityName.length());
    std::copy(facilityName.begin(), facilityName.end(), std::back_inserter(payload));
    
    for (std::vector<int>::iterator it = days.begin(); it != days.end(); ++it) {
        char marshalledInt[4];
        marshalInt(*it, marshalledInt);
        payload.insert(payload.end(), &marshalledInt[0], &marshalledInt[2]);
    }
}
