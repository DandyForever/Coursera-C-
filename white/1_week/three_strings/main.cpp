#include <iostream>
using namespace std;

int main() {
    string fst, snd, trd;
    cin >> fst >> snd >> trd;
    if (fst < snd && fst < trd) cout << fst;
    else if (snd < trd) cout << snd;
    else cout << trd;
    return 0;
}