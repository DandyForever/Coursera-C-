#pragma once

#include <vector>
#include <map>
#include <iostream>

using namespace std;

struct BusesForStopResponse {
    vector <string> response;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    string alternative;
    vector <string> stops;
    map <string, vector <string>> response;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    string alternative;
    map <string, vector <string>> response;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);