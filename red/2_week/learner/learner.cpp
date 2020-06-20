#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        int known = dict.size();
        for (const auto& word : words) {
            dict.insert(word);
        }
        return dict.size() - known;
    }

    vector<string> KnownWords() {
        vector<string> state(dict.begin(), dict.end());
        return state;
    }
};