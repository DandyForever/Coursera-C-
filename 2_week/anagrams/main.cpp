#include <iostream>
#include <map>
using namespace std;

bool isAnagram(const string & s1, const string & s2) {
    map <char, int> lets1, lets2;
    for (auto c : s1) {
        lets1[c]++;
    }
    for (auto c : s2) {
        lets2[c]++;
    }
    return (lets1 == lets2);
}

int main() {
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        bool result = isAnagram(s1, s2);
        if (result) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
    return 0;
}