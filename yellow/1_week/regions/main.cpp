#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

bool operator< (const Region& lv, const Region& rv) {
    return tie(lv.names, lv.parent_std_name, lv.population, lv.std_name) <
    tie(rv.names, rv.parent_std_name, rv.population, rv.std_name);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
    int num = 0;
    map<Region, int> tmp;
    for (const auto& item : regions) {
        num = max(num, ++tmp[item]);
    }
    return num;
}
