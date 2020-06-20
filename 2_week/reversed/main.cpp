#include <iostream>
#include <vector>
using namespace std;


vector <int> Reversed (const vector <int> & v) {
    vector <int> clon(v.size());
    for (int i = 0; i < v.size(); i++) {
        clon[i] = v[v.size() - i - 1];
    }
    return clon;
}