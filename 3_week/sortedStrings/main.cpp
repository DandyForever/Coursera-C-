#include <algorithm>
#include <vector>

using namespace std;

class SortedStrings {
public:
    void AddString(const string& s) {
        strs.push_back(s);
        sort (begin(strs), end(strs));
    }
    vector<string> GetSortedStrings() {
        return strs;
    }
private:
    vector <string> strs;
};
