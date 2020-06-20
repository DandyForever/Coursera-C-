#include <iostream>
#include <map>
#include <vector>

using namespace std;

void cmdHandler (map <vector <string>, int> & buses, int & count) {
    int n = 0;
    cin >> n;
    vector <string> bus;
    for (int i = 0; i < n; i++) {
        string stop;
        cin >> stop;
        bus.push_back(stop);
    }
    if (buses.find(bus) == buses.end()) {
        cout << "New bus " << count << endl;
        buses[bus] = count++;
    } else {
        cout << "Already exists for " << buses[bus] << endl;
    }
}

int main() {
    int n = 0;
    cin >> n;
    map <vector <string>, int> buses;
    int count = 1;
    for (int i = 0; i < n; i++) {
        cmdHandler (buses, count);
    }
    return 0;
}