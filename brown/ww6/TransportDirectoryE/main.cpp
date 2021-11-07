#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <fstream>
#include "json.h"
#include "router.h"


using namespace std;


class TransportDictionary {
public:
    struct Coordinates {
        double latitude;
        double longitude;
    };

    void AddStation(const string& name, Coordinates coordinates, const map<string, double>& distances) {
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
//            if (!distances_.count({stations[station_index], stations[station_index + 1]})) {
//                distances_[{stations[station_index], stations[station_index + 1]}] =
//                        distances_[{stations[station_index + 1], stations[station_index]}];
//            }
//            if (!distances_.count({stations[station_index + 1], stations[station_index]})) {
//                distances_[{stations[station_index + 1], stations[station_index]}] =
//                        distances_[{stations[station_index], stations[station_index + 1]}];
//            }
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

    void SetWaitingTime(double time) {
        waiting_time_ = time;
    }
    void SetVelocity(double velocity) {
        velocity_ = velocity;
    }

    Graph::DirectedWeightedGraph<double> BuildGraph() {
        Graph::DirectedWeightedGraph<double> graph(stations_.size());
        for (auto& [bus, stations] : buses_stations_) {
            if (buses_types_.at(bus)) {
                for (size_t i = 0; i < stations.size(); i++) {
                    double weight = waiting_time_;
                    double current_weight = 0;
                    Graph::VertexId vertex_from = stations_indexes_[stations[i]];
                    for (size_t j = i + 1; j < stations.size(); j++) {
                        if (i == 0 && j == stations.size() - 1)
                            continue;
                        double w = distances_[{stations[j - 1], stations[j]}] / velocity_ * 60 / 1000;
                        current_weight += w;
                        weight += w;
                        Graph::VertexId vertex_to = stations_indexes_[stations[j]];
                        auto edge = graph.AddEdge({vertex_from, vertex_to, weight});
                        span_info_[edge] = {bus, stations[i], j - i, current_weight};
                    }
                }
            } else {
                for (size_t i = 0; i < stations.size(); i++) {
                    double weight = waiting_time_;
                    double current_weight = 0;
                    Graph::VertexId vertex_from = stations_indexes_[stations[i]];
                    for (size_t j = i + 1; j < stations.size(); j++) {
                        double w = distances_[{stations[j - 1], stations[j]}] / velocity_ * 60 / 1000;
                        current_weight += w;
                        weight += w;
                        Graph::VertexId vertex_to = stations_indexes_[stations[j]];
                        auto edge = graph.AddEdge({vertex_from, vertex_to, weight});
                        span_info_[edge] = {bus, stations[i], j - i, current_weight};
                    }
                }
                for (int i = stations.size() - 1; i > 0; i--) {
                    double weight = waiting_time_;
                    double current_weight = 0;
                    Graph::VertexId vertex_from = stations_indexes_[stations[i]];
                    for (int j = i - 1; j >= 0; j--) {
                        double w = distances_[{stations[j + 1], stations[j]}] / velocity_ * 60 / 1000;
                        current_weight += w;
                        weight += w;
                        Graph::VertexId vertex_to = stations_indexes_[stations[j]];
                        auto edge = graph.AddEdge({vertex_from, vertex_to, weight});
                        size_t span = i - j;
                        span_info_[edge] = {bus, stations[i], span, current_weight};
                    }
                }
            }
        }
        return graph;
    }
    void FillDistances() {
        auto temp = distances_;
        for (auto& [span, distance] : temp) {
            if (!distances_.count({span.second, span.first}))
                distances_[{span.second, span.first}] = distance;
        }
    }

    void FillStationsIndexes() {
        Graph::VertexId index = 0;
        for (auto& [station, coordinates] : stations_) {
            stations_indexes_[station] = index;
            index++;
        }
    }

    Graph::VertexId GetVertexId(const string& station) const {
        return stations_indexes_.at(station);
    }

    double GetVelocity() const {
        return velocity_;
    }

    double GetWaitTime() const {
        return waiting_time_;
    }

    struct EdgeInfo {
        string bus;
        string from;
        size_t span_count;
        double time;
    };

    EdgeInfo GetEdgeInfo(Graph::EdgeId edge) {
        return span_info_[edge];
    }

private:
    map<string, Coordinates> stations_;
    map<string, set<string>> stations_buses_;
    map<string, vector<string>> buses_stations_;
    map<string, set<string>> unique_buses_stations_;
    map<string, bool> buses_types_;
    mutable map<pair<string, string>, double> distances_;

    map<string, Graph::VertexId> stations_indexes_;
    map<Graph::EdgeId, EdgeInfo> span_info_;

    double Distance(Coordinates first, Coordinates second) const {
        double dist = 0.5 - cos((second.latitude - first.latitude) * pi) / 2 +
                        cos(first.latitude * pi) * cos(second.latitude * pi) *
                                (1 - cos((second.longitude - first.longitude) * pi)) / 2;
        return 2 * Radius * asin(sqrt(dist));
    }

    const double pi = 3.1415926535 / 180;
    const double Radius = 6371000;

    double waiting_time_ = 0;
    double velocity_ = 0;
};


void HandleBaseRequest(const vector<Json::Node>& requests, TransportDictionary& dictionary) {
    for (auto& request : requests) {
        auto& request_info = request.AsMap();
        auto& request_type = request_info.at("type").AsString();
        if (request_type == "Stop") {
            auto& name = request_info.at("name").AsString();
            double latitude = request_info.at("latitude").AsDouble(),
                    longitude = request_info.at("longitude").AsDouble();
            auto& distances_raw = request_info.at("road_distances").AsMap();
            map<string, double> distances;
            for (auto& [name_, distance] : distances_raw) {
                distances[name_] = distance.AsDouble();
            }
            dictionary.AddStation(name, {latitude, longitude}, distances);
        } else if (request_type == "Bus") {
            auto& name = request_info.at("name").AsString();
            bool is_circular = request_info.at("is_roundtrip").AsBool();
            auto& stations_raw = request_info.at("stops").AsArray();
            vector<string> stations(stations_raw.size());
            for (int i = 0; i < stations_raw.size(); i++) {
                stations[i] = stations_raw[i].AsString();
            }
            dictionary.AddBus(name, stations, is_circular);
        }
    }
}

void HandleStatRequest(const vector<Json::Node>& requests, TransportDictionary& dictionary) {
    cout << "[";
    Graph::DirectedWeightedGraph graph = dictionary.BuildGraph();
    Graph::Router router(graph);
    for (int request_id = 0; request_id < requests.size(); request_id++) {
        auto& request = requests[request_id];
        cout << "\n  {";
        auto& request_info = request.AsMap();
        auto& request_type = request_info.at("type").AsString();
        long long id = static_cast<long long>(request_info.at("id").AsDouble());
        if (request_type == "Bus") {
            auto& name = request_info.at("name").AsString();
            if (!dictionary.IsBusFound(name)) {
                cout << "\n    \"request_id\": " << id << ",";
                cout << "\n    \"error_message\": \"not found\"";
            } else {
                auto length = dictionary.GetRouteLength(name);
                cout << "\n    \"route_length\": " << length.first << ",";
                cout << "\n    \"request_id\": " << id << ",";
                cout << "\n    \"curvature\": " << length.first / length.second << ",";
                cout << "\n    \"stop_count\": " << dictionary.GetStations(name) << ",";
                cout << "\n    \"unique_stop_count\": " << dictionary.GetUniqueStations(name);
            }
        } else if (request_type == "Stop") {
            auto& name = request_info.at("name").AsString();
            if (!dictionary.IsStationFound(name)) {
                cout << "\n    \"request_id\": " << id << ",";
                cout << "\n    \"error_message\": \"not found\"";
            } else if (!dictionary.IsBuses(name)) {
                cout << "\n    \"buses\": [],";
                cout << "\n    \"request_id\": " << id;
            } else {
                auto& buses = dictionary.GetBuses(name);
                cout << "\n    \"buses\": [";

                for (auto it = buses.begin(); it != buses.end(); it++) {
                    cout << "\n      \"" << *it << "\"";
                    if (it != prev(buses.end()))
                        cout << ',';
                }
                cout << "\n    ],";
                cout << "\n    \"request_id\": " << id;
            }
        } else if (request_type == "Route") {
            auto& from = request_info.at("from").AsString();
            auto& to = request_info.at("to").AsString();
            auto route_exist_ = router.BuildRoute(dictionary.GetVertexId(from), dictionary.GetVertexId(to));
            if (!route_exist_.has_value()) {
                cout << "\n    \"request_id\": " << id << ",";
                cout << "\n    \"error_message\": \"not found\"";
            } else {
                auto route_exist = route_exist_.value();
                cout << "\n    \"request_id\": " << id << ",";
                cout << "\n    \"total_time\": " << route_exist.weight << ",";
                cout << "\n    \"items\": " << "[\n";
                for (int i = 0; i < route_exist.edge_count; i++) {
                    auto edge_info = dictionary.GetEdgeInfo(router.GetRouteEdge(route_exist.id, i));
                    cout << "      {\n";
                    cout << "        \"type\": \"Wait\",\n";
                    cout << "        \"stop_name\": \"" << edge_info.from << "\",\n";
                    cout << "        \"time\": " << dictionary.GetWaitTime() << "\n";
                    cout << "      },\n";
                    cout << "      {\n";
                    cout << "        \"type\": \"Bus\",\n";
                    cout << "        \"bus\": \"" << edge_info.bus << "\",\n";
                    cout << "        \"time\": " << edge_info.time << ",\n";
                    cout << "        \"span_count\": " << edge_info.span_count << "\n";
                    cout << "      }";
                    if (i == route_exist.edge_count - 1)
                        cout << "\n";
                    else
                        cout << ",\n";
                }
                cout << "    ]";
            }
        }
        cout << "\n  }";
        if (request_id != requests.size() - 1)
            cout << ',';
    }
    if (requests.empty())
        cout << "]";
    else
        cout << "\n]";
}

void HandleRouterSettings(map<string, Json::Node> settings, TransportDictionary& dictionary) {
    dictionary.SetWaitingTime(settings.at("bus_wait_time").AsDouble());
    dictionary.SetVelocity(settings.at("bus_velocity").AsDouble());
}

int main() {
//    fstream input("test2.txt");
    auto document = Json::Load(cin);
    auto& root = document.GetRoot();
    auto& queries = root.AsMap();
    TransportDictionary dictionary;
    if (queries.count("base_requests"))
        HandleBaseRequest(queries.at("base_requests").AsArray(), dictionary);
    dictionary.FillDistances();
    dictionary.FillStationsIndexes();
    if (queries.count("routing_settings"))
        HandleRouterSettings(queries.at("routing_settings").AsMap(), dictionary);
    if (queries.count("stat_requests"))
        HandleStatRequest(queries.at("stat_requests").AsArray(), dictionary);
    else
        cout << "[]";
    return 0;
}
