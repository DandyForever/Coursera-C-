#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <math.h>


using namespace std;


class TransportDictionary {
public:
    struct Coordinates {
        double latitude;
        double longitude;
    };

    void AddStation(const string& name, Coordinates coordinates, const vector<pair<string, double>>& distances) {
        stations_[name] = coordinates;
        for (auto& [station, distance] : distances) {
            distances_[{name, station}] = distance;
        }
    }
    void AddBus(const string& name, const vector<string>& stations, bool is_circular) {
        buses_stations_[name] = stations;
        set<string> unique_stations(stations.begin(), stations.end());
        unique_buses_stations_[name] = unique_stations;
        buses_types_[name] = is_circular;
        for (auto& station : stations) {
            stations_buses_[station].insert(name);
        }
    }
    bool IsBusFound(const string& name) const {
        return buses_stations_.count(name);
    }
    bool IsStationFound(const string& name) const {
        return stations_.count(name);
    }
    bool IsBuses(const string& name) const {
        return stations_buses_.count(name);
    }
    int GetStations(const string& name) const {
        auto& stations = buses_stations_.at(name);
        if (buses_types_.at(name))
            return stations.size();
        return stations.size() * 2 - 1;
    }
    const set<string>& GetBuses(const string& name) const {
        return stations_buses_.at(name);
    }
    int GetUniqueStations(const string& name) const {
        return unique_buses_stations_.at(name).size();
    }
    pair<double, double> GetRouteLength(const string& name) const {
        double length = 0;
        double length_circular = 0;
        auto& stations = buses_stations_.at(name);
        for (int station_index = 0; station_index < stations.size() - 1; station_index++) {
            if (!distances_.count({stations[station_index], stations[station_index + 1]})) {
                distances_[{stations[station_index], stations[station_index + 1]}] =
                        distances_[{stations[station_index + 1], stations[station_index]}];
            }
            if (!distances_.count({stations[station_index + 1], stations[station_index]})) {
                distances_[{stations[station_index + 1], stations[station_index]}] =
                        distances_[{stations[station_index], stations[station_index + 1]}];
            }
            double distance = distances_.at({stations[station_index], stations[station_index + 1]});
            length += distance;
            length_circular += distance;
            length_circular += distances_.at({stations[station_index + 1], stations[station_index]});
        }
        double shortest_length = GetShortestRouteLength(name);
        if (buses_types_.at(name))
            return {length, shortest_length};
        return {length_circular, shortest_length};
    }
    double GetShortestRouteLength(const string& name) const {
        double result = 0;
        auto& stations = buses_stations_.at(name);
        for (int station_index = 0; station_index < stations.size() - 1; station_index++) {
            result += Distance(stations_.at(stations[station_index]), stations_.at(stations[station_index + 1]));
        }
        if (buses_types_.at(name))
            return result;
        return result * 2;
    }
private:
    map<string, Coordinates> stations_;
    map<string, set<string>> stations_buses_;
    map<string, vector<string>> buses_stations_;
    map<string, set<string>> unique_buses_stations_;
    map<string, bool> buses_types_;
    mutable map<pair<string, string>, double> distances_;

    double Distance(Coordinates first, Coordinates second) const {
        double dist = 0.5 - cos((second.latitude - first.latitude) * pi) / 2 +
                        cos(first.latitude * pi) * cos(second.latitude * pi) *
                                (1 - cos((second.longitude - first.longitude) * pi)) / 2;
        return 2 * Radius * asin(sqrt(dist));
    }

    const double pi = 3.1415926535 / 180;
    const double Radius = 6371000;
};

string read_until_separator(char separator, istream& input = cin) {
    char c;
    string result;
    input >> c;
    while (c != separator) {
        result.push_back(c);
        while (input.peek() == ' ') {
            result.push_back(' ');
            input.ignore();
        }
        input >> c;
    }
    return result;
}

void SkipSpacesFront(istream &input = cin) {
    while (cin.peek() == ' ')
        cin.ignore();
}


void SkipSpacesBack(string &station) {
    while (station.back() == ' ')
        station.pop_back();
}

int main() {
    int update_query_number = 0;
    cin >> update_query_number;
    string query_string;
    TransportDictionary dictionary;
    for (int i = 0; i < update_query_number; i++) {
        cin >> query_string;
        if (query_string == "Stop") {
            SkipSpacesFront();
            string station = read_until_separator(':');
            SkipSpacesBack(station);
            double latitude, longitude;
            cin >> latitude;
            cin.ignore();
            cin >> longitude;
            vector<pair<string, double>> distances;
            if (cin.peek() == ',') {
                cin.ignore();
                SkipSpacesFront();
                string stations_distances;
                getline(cin, stations_distances);
                stations_distances.push_back(',');
                stringstream distances_stream(stations_distances);
                while (distances_stream.peek() != EOF) {
                    SkipSpacesFront(distances_stream);
                    double distance = 0;
                    string station_;
                    distances_stream >> distance;
                    distances_stream.ignore();
                    distances_stream >> station_;
                    SkipSpacesFront(distances_stream);
                    station_ = read_until_separator(',', distances_stream);
                    distances.emplace_back(station_, distance);
                }
            }
            dictionary.AddStation(station, {latitude, longitude}, distances);
        } else if (query_string == "Bus") {
            SkipSpacesFront();
            string bus_name = read_until_separator(':');
            string route_stations;
            getline(cin, route_stations);
            bool is_circular = route_stations.find('>') != string::npos;
            char separator = is_circular ? '>' : '-';
            route_stations.push_back(separator);
            stringstream stations_stream(route_stations);
            vector<string> stations;
            while (stations_stream.peek() != EOF) {
                SkipSpacesFront(stations_stream);
                string station = read_until_separator(separator, stations_stream);
                SkipSpacesBack(station);
                stations.push_back(station);
            }
            dictionary.AddBus(bus_name, stations, is_circular);
        }
    }
    int query_number = 0;
    cin >> query_number;
    for (int i = 0; i < query_number; i++) {
        cin >> query_string;
        if (query_string == "Bus") {
            string bus_name;
            SkipSpacesFront();
            getline(cin, bus_name);
            if (!dictionary.IsBusFound(bus_name))
                cout << "Bus " << bus_name << ": not found" << endl;
            else {
                auto distance = dictionary.GetRouteLength(bus_name);
                cout << "Bus " << bus_name << ": " << dictionary.GetStations(bus_name) << " stops on route, " <<
                        dictionary.GetUniqueStations(bus_name) << " unique stops, " <<
                        distance.first << " route length, " << distance.first / distance.second << " curvature\n";
            }
        } else if (query_string == "Stop") {
            string station_name;
            SkipSpacesFront();
            getline(cin, station_name);
            if (!dictionary.IsStationFound(station_name))
                cout << "Stop " << station_name << ": not found" << endl;
            else if (!dictionary.IsBuses(station_name))
                cout << "Stop " << station_name << ": no buses" << endl;
            else {
                auto& buses = dictionary.GetBuses(station_name);
                cout << "Stop " << station_name << ": buses";
                for (auto &bus_name: buses) {
                    cout << " " << bus_name;
                }
                cout << endl;
            }
        }
    }
    return 0;
}
