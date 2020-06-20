#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    vector <string> arr;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        arr.push_back(str);
    }
    sort (begin(arr), end(arr), [](string s1, string s2){
        int l1 = 0;
        int l2 = 0;
        while (l1 < s1.length() && l2 < s2.length()) {
            if (tolower(s1[l1]) == tolower(s2[l2])) {
                l1++;
                l2++;
            } else
                return (tolower(s1[l1]) < tolower(s2[l2]));
        }
        return l1 != s1.length();
    });
    for (const auto & s : arr)
        cout << s << " ";
    return 0;
}