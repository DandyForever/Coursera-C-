#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_[bus].insert(end(buses_[bus]), begin(stops), end(stops));
    for (const auto& stop : stops) {
        stops_[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if (!stops_.count(stop))
        return {{"No stop"}};

    vector <string> response;
    for (const auto& bus : stops_.at(stop)) {
        response.push_back(bus);
    }
    return {response};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
    if (buses_.empty())
        return {"No buses", {}};
    return {"", buses_};
}
