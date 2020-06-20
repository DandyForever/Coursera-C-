#include "query.h"

istream& operator >> (istream& is, Query& q) {
    string type;
    is >> type;
    if (type == "NEW_BUS") {
        string bus_name;
        is >> bus_name;
        int num_stops = 0;
        is >> num_stops;
        vector <string> stops(num_stops);
        for (int i = 0; i < num_stops; i++) {
            is >> stops[i];
        }
        q = {QueryType::NewBus, bus_name, "", stops};
    } else if (type == "BUSES_FOR_STOP") {
        string stop_name;
        is >> stop_name;
        q = {QueryType::BusesForStop, "", stop_name, {}};
    } else if (type == "STOPS_FOR_BUS") {
        string bus_name;
        is >> bus_name;
        q = {QueryType::StopsForBus, bus_name, "", {}};
    } else if (type == "ALL_BUSES") {
        q = {QueryType::AllBuses, "", "", {}};
    }
    return is;
}
