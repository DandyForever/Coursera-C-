#include <iostream>

using namespace std;

int main() {
    int n = 0;
    int64_t r = 0;
    cin >> n >> r;
    uint64_t sum = 0;
    for (int i = 0; i < n; i++) {
        uint64_t w = 0, h = 0, d = 0;
        cin >> w >> h >> d;
        sum += w * h * d * r;
    }
    cout << sum << endl;
    return 0;
}