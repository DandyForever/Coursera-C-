#include <iostream>
using namespace std;

int main() {
    string str;
    cin >> str;
    bool fst = false;
    for (int i = 0; i < str.length(); i++){
        if (str[i] == 'f') {
            if (fst) {
                cout << i;
                return 0;
            }
            else
                fst = true;
        }
    }
    if (fst) cout << -1;
    else cout << -2;
    return 0;
}