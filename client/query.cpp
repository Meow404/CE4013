#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "query.h"

char* craftQueryReq() {
    std::string facilityName;  // Unknown size so use string instead of char array
    std::vector<int> days;

    std::cout << "Facility Name: ";
    std::getline(std::cin, facilityName);
    std::cout << "0 = Mon, 1 = Tues, 2 = Wed, 3 = Thurs, 4 = Fri, 5 = Sat, 6 = Sun" << std::endl;
    std::cout << "Input days with spaces in between (\"0 1 2\" for \"Mon Tues Wed\")" << std::endl;
    std::cout << "Days To Check: ";
    std::string daysStr;
    std::getline(std::cin, daysStr);
    std::istringstream stm(daysStr);
    int temp;
    while (stm >> temp) {
        days.push_back(temp);
    }

    if (facilityName.empty() || days.empty()) {
        std::cout << "No facility name or days specified";
        return "";
    }

    return marshalQueryReq(facilityName, days);
}
