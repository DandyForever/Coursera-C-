#pragma once
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    vector <T> tmp;
    for (auto it = begin(elements); it != end(elements); it++) {
        if (*it > border)
            tmp.push_back(*it);
    }
    return tmp;
}