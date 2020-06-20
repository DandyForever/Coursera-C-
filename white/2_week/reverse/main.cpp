#include <iostream>

void swap (int & x, int & y) {
    int tmp = x;
    x = y;
    y = tmp;
}

void Reverse (vector <int> & v) {
    for (int i = 0; i < v.size() / 2; i++) {
        swap (v[i], v[v.size() - i - 1]);
    }
}