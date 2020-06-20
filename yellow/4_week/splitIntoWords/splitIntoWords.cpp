//#include "splitIntoWords.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector <string> tmp;
    auto it_b = begin(s);
    auto it_e = begin(s);
    while (it_e != end(s)) {
        it_e = find (it_b, end(s), ' ');
        tmp.emplace_back(it_b, it_e);
        if (it_e == end(s))
            break;
        it_e++;
        it_b = it_e;
    }
    return tmp;
}