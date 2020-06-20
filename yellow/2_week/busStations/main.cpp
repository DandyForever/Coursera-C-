#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

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

struct BusesForStopResponse {
    vector <string> response;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    for (const auto& item : r.response) {
        os << item << " ";
    }
    return os;
}

struct StopsForBusResponse {
    string alternative;
    vector <string> stops;
    map <string, vector <string>> response;
};

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

struct AllBusesResponse {
    string alternative;
    map <string, vector <string>> response;
};

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

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_[bus].insert(end(buses_[bus]), begin(stops), end(stops));
        for (const auto& stop : stops) {
            stops_[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (!stops_.count(stop))
            return {{"No stop"}};

        vector <string> response;
        for (const auto& bus : stops_.at(stop)) {
            response.push_back(bus);
        }
        return {response};
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if (!buses_.count(bus))
            return {"No bus", {}, {}};

        map <string, vector <string>> stop_response;
        for (const auto& item : buses_.at(bus)) {
            if (stops_.at(item).size() == 1)
                stop_response[item] = {"no interchange"};
            else {
                for (const auto& b : stops_.at(item)) {
                    if (b != bus)
                        stop_response[item].push_back(b);
                }
            }
        }
        return {"", buses_.at(bus), stop_response};
    }

    AllBusesResponse GetAllBuses() const {
        if (buses_.empty())
            return {"No buses", {}};
        return {"", buses_};
    }

private:
    map <string, vector <string>> buses_;
    map <string, vector <string>> stops_;
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}