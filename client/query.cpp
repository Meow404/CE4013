#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "query.h"

/** Request Format:
 *  <facility name size><facility name><list of days>
 */
void craftQueryReq(std::vector<char> &payload) {
    std::string dayPrompt =
    "\n[DAY] -> 0 = Mon, 1 = Tues, 2 = Wed, 3 = Thurs, 4 = Fri, 5 = Sat, 6 = Sun\n"  \
    "Input multiple days as [DAY] [DAY] [DAY] (\"0 1 2\" for \"Mon Tues Wed\")\n\n" \
    "Days To Check: ";
    std::string daysStr;
    std::string facilityName;  // Unknown size so use string instead of char array
    std::vector<int> days;

    std::cout << "\nFacility Name: ";
    std::cin.ignore();
    std::getline(std::cin, facilityName);
    std::cout << dayPrompt;
    std::getline(std::cin, daysStr);
    std::istringstream stm(daysStr);
    int temp;
    while (stm >> temp) {
        if (temp < 0 || temp > 7) {
            std::cerr << "ERROR: Invalid Day Beyond Range 0-6" << std::endl;
        }
        days.push_back(temp);
    }

    if (facilityName.empty() || days.empty()) {
        std::cerr << "ERROR: No facility name or days specified\n";
    }
    
    char facNameSize[4];
    marshalInt(facilityName.length(), facNameSize);
    payload.insert(payload.end(), &facNameSize[0], &facNameSize[4]);
    std::copy(facilityName.begin(), facilityName.end(), std::back_inserter(payload));
    
    for (std::vector<int>::iterator it = days.begin(); it != days.end(); ++it) {
        char marshalledInt[4];
        marshalInt(*it, marshalledInt);
        payload.insert(payload.end(), &marshalledInt[0], &marshalledInt[4]);
    }
}
