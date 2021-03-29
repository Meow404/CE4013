#include "booking.h"
#include "daytime.h"
#include "facility.h"
#include "iostream"
#include "facilityManager.h"
#include "udpServer.h"
#include "commHandler.h"
#include <fstream>
#include <sstream>
#include "vector"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    facilityManager FM("facilities.txt");
    udpServer server(8080, AT_MOST_ONCE);
    commHandler cm(&server, &FM);
    cm.start();
}