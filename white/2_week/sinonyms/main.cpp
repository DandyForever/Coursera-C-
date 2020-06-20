#include <iostream>
#include <map>
#include <set>

using namespace std;

void cmdAdd(map<string, set<string>> &dict) {
    string w1, w2;
    cin >> w1 >> w2;
    dict[w1].insert(w2);
    dict[w2].insert(w1);
}

void cmdCount(map<string, set<string>> &dict) {
    string word;
    cin >> word;
    cout << dict[word].size() << endl;
}

void cmdCheck(map<string, set<string>> &dict) {
    string w1, w2;
    cin >> w1 >> w2;
    if (dict[w1].count(w2) == 1)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

int main() {
    int n = 0;
    cin >> n;
    map<string, set<string>> dict;
    for (int i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "ADD")
            cmdAdd(dict);
        else if (cmd == "COUNT")
            cmdCount(dict);
        else if (cmd == "CHECK")
            cmdCheck(dict);
    }
    return 0;
}