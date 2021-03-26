#include "booking.h"
#include "daytime.h"
#include "facility.h"
#include "iostream"

int main()
{

    facility facility("Lecture Theatre", facilityType::LECTURE_THEATRE);
    facility.printBookings();
    for (daytime::day i = daytime::MONDAY; i < 7; i = static_cast<daytime::day>(i + 1))
        facility.printAvailability(i);

    daytime::duration d = {daytime::MONDAY, {3, 30}, daytime::TUEDAY, {4, 50}};
    std::string cid = facility.addBooking("192.168.1.45", d);

    facility.printBookings();
    for (daytime::day i = daytime::MONDAY; i < 7; i = static_cast<daytime::day>(i + 1))
        facility.printAvailability(i);
    
    std::cout << "EXTEND =====================================" << std::endl;
    facility.extendBooking("192.168.1.45", cid, 1, 2, 3);

    facility.printBookings();
    for (daytime::day i = daytime::MONDAY; i < 7; i = static_cast<daytime::day>(i + 1))
        facility.printAvailability(i);
    
    std::cout << "CHANGE =====================================" << std::endl;
    facility.changeBooking("192.168.1.45", cid, 1, 2, 3);

    facility.printBookings();
    for (daytime::day i = daytime::MONDAY; i < 7; i = static_cast<daytime::day>(i + 1))
        facility.printAvailability(i);

    // for (int i = 0; i < 1000000000; i++)
    //     ;

    // d = {daytime::TUEDAY, {5, 30}, daytime::THURSDAY, {23, 50}};
    // facility.addBooking("192.168.1.45", d);

    // facility.printBookings();

    // for (int i = 0; i < 1000000000; i++)
    //     ;

    // d = {daytime::TUEDAY, {2, 30}, daytime::THURSDAY, {10, 50}};
    // facility.addBooking("192.168.1.45", d);

    // facility.printBookings();

    // for (int i = 0; i < 1000000000; i++)
    //     ;

    // d = {daytime::MONDAY, {2, 30}, daytime::MONDAY, {3, 15}};
    // facility.addBooking("192.168.1.45", d);

    // facility.printBookings();

    // for (int i = 0; i < 1000000000; i++)
    //     ;

    // d = {daytime::SUNDAY, {2, 30}, daytime::MONDAY, {2, 15}};
    // facility.addBooking("192.168.1.45", d);

    // facility.printBookings();

    // std::cout << "==========================" << std::endl;

    // for (daytime::day i = daytime::MONDAY; i < 7; i = static_cast<daytime::day>(i + 1))
    //     facility.printAvailability(i);
}