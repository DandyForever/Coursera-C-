#include <iostream>
#include <set>
#include <map>

using namespace std;

void cmdHandler (map <set <string>, int> & buses, int & count) {
    int n = 0;
    cin >> n;
    set <string> bus;
    for (int i = 0; i < n; i++) {
        string st;
        cin >> st;
        bus.insert(st);
    }
    if (buses.find(bus) == buses.end()) {
        cout << "New bus " << count << endl;
        buses[bus] = count++;
    } else
        cout << "Already exists for " << buses[bus] << endl;
}

int main() {
    int n = 0;
    cin >> n;
    map <set <string>, int> buses;
    int count = 1;
    for (int i = 0; i < n; i++) {
        cmdHandler(buses, count);
    }
    return 0;
}