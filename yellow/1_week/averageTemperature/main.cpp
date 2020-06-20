#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    vector <int64_t> temps(n);
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        int cur = 0;
        cin >> cur;
        sum += cur;
        temps[i] = cur;
    }
    sum = sum / static_cast<int64_t>(temps.size());
    int num = 0;
    for (int i = 0; i < n; i++) {
        if (temps[i] > sum)
            num++;
    }
    cout << num << endl;
    for (int i = 0; i < n; i++) {
        if (temps[i] > sum)
            cout << i << " ";
    }
    return 0;
}