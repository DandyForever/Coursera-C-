#include <iostream>
#include <map>
#include <vector>

using namespace std;

void cmdNewBus(map<string, vector<string>> &buses, map<string, vector<string>> &stations) {
    string bus;
    cin >> bus;
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string station;
        cin >> station;
        buses[bus].push_back(station);
        stations[station].push_back(bus);
    }
}

void cmdBusesForStop(map<string, vector<string>> &stations) {
    string station;
    cin >> station;
    if (stations.find(station) == stations.end()) {
        cout << "No stop" << endl;
        return;
    }

    for (const auto &bus : stations[station])
        cout << bus << " ";
    cout << endl;
}

void cmdStopsForBus(map<string, vector<string>> &buses, map<string, vector<string>> &stations) {
    string bus;
    cin >> bus;
    if (buses.find(bus) == buses.end()) {
        cout << "No bus" << endl;
        return;
    }

    for (const auto &station : buses[bus]) {
        cout << "Stop " << station << ": ";
        if (stations[station].size() == 1)
            cout << "no interchange";
        for (const auto &bus_ : stations[station]) {
            if (bus != bus_)
                cout << bus_ << " ";
        }
        cout << endl;
    }
}

void cmdAllBuses(map<string, vector<string>> &buses) {
    if (buses.empty()) {
        cout << "No buses" << endl;
        return;
    }

    for (const auto &bus : buses) {
        cout << "Bus " << bus.first << ": ";
        for (const auto &station : bus.second) {
            cout << station << " ";
        }
        cout << endl;
    }
}

int main() {
    int n = 0;
    cin >> n;
    map<string, vector<string>> buses, stations;
    for (int i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "NEW_BUS")
            cmdNewBus(buses, stations);
        else if (cmd == "BUSES_FOR_STOP")
            cmdBusesForStop(stations);
        else if (cmd == "STOPS_FOR_BUS")
            cmdStopsForBus(buses, stations);
        else if (cmd == "ALL_BUSES")
            cmdAllBuses(buses);
    }
    return 0;
}