#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    for (const auto& item : r.response) {
        os << item << " ";
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.alternative.empty()) {
        for (const auto& item : r.stops) {
            os << "Stop " << item << ": ";
            for (const auto& bus : r.response.at(item)) {
                os << bus << " ";
            }
            os << endl;
        }
    } else
        os << r.alternative;
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.alternative.empty()) {
        for (const auto& bus : r.response) {
            os << "Bus " << bus.first << ": ";
            for (const auto& stop : bus.second) {
                os << stop << ' ';
            }
            os << endl;
        }
    } else
        os << r.alternative;
    return os;
}
