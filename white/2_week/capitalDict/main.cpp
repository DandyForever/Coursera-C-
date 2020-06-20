#include <iostream>
#include <map>

using namespace std;

void cmdChangeCapital(map<string, string> &world) {
    string country, capital;
    cin >> country >> capital;
    if (world.find(country) == world.end()) {
        world[country] = capital;
        cout << "Introduce new country " << country << " with capital " << capital << endl;
    } else if (world[country] == capital)
        cout << "Country " << country << " hasn't changed its capital" << endl;
    else {
        cout << "Country " << country << " has changed its capital from " << world[country] << " to " << capital
             << endl;
        world[country] = capital;
    }
}

void cmdRename(map<string, string> &world) {
    string oldName, newName;
    cin >> oldName >> newName;
    if (oldName == newName || world.find(newName) != world.end() || world.find(oldName) == world.end())
        cout << "Incorrect rename, skip" << endl;
    else {
        world[newName] = world[oldName];
        world.erase(oldName);
        cout << "Country " << oldName << " with capital " << world[newName] << " has been renamed to " << newName
             << endl;
    }
}

void cmdAbout(map<string, string> &world) {
    string country;
    cin >> country;
    if (world.find(country) == world.end())
        cout << "Country " << country << " doesn't exist" << endl;
    else
        cout << "Country " << country << " has capital " << world[country] << endl;
}

void cmdDump(const map<string, string> &world) {
    if (world.empty())
        cout << "There are no countries in the world" << endl;
    else {
        for (auto record : world) {
            cout << record.first << "/" << record.second << " ";
        }
        cout << endl;
    }
}

int main() {
    int n = 0;
    cin >> n;

    map<string, string> world;
    for (int i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "CHANGE_CAPITAL")
            cmdChangeCapital(world);
        else if (cmd == "RENAME")
            cmdRename(world);
        else if (cmd == "ABOUT")
            cmdAbout(world);
        else if (cmd == "DUMP")
            cmdDump(world);
    }
    return 0;
}