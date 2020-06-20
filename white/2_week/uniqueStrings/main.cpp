#include <iostream>
#include <set>

using namespace std;

int main() {
    set <string> unique;
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        unique.insert(str);
    }
    cout << unique.size() << endl;
    return 0;
}