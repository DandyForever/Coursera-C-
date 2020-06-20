#include <algorithm>

using namespace std;

string to_string (int value) {
    if (value == 0)
        return string("0");
    string str;
    int copy = value;
    if (value < 0)
        value = -value;
    while (value > 0) {
        str.push_back(value % 10 + '0');
        value /= 10;
    }
    if (copy < 0) {
        str.push_back('-');
    }
    reverse(begin (str), end(str));
    return str;
}
