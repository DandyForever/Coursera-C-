#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector (const vector <int>& v) {
    for (const auto& item : v) {
        cout << item << ' ';
    }
    cout << endl;
}

void PrintPermutations (const int n) {
    vector <int> permutation(n);
    for (int i = 0; i < n; i++) {
        permutation[i] = n - i;
    }
    do {
        PrintVector (permutation);
    } while (prev_permutation(begin(permutation), end(permutation)));
}

int main() {
    int n = 0;
    cin >> n;
    PrintPermutations(n);
    return 0;
}