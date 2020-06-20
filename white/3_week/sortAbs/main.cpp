#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n = 0;
    vector <int> arr;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int el = 0;
        cin >> el;
        arr.push_back(el);
    }
    sort (begin(arr), end(arr), [](int x, int y)
          {
                return (abs(x) < abs(y));
          }
    );
    for (auto item : arr)
        cout << item << " ";
    return 0;
}