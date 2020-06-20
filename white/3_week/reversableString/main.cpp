#include <iostream>

using namespace std;

class ReversibleString {
public:
    ReversibleString(){};
    ReversibleString(const string& s) {
        str = s;
    }
    void Reverse() {
        string tmp;
        for (auto c : str) {
            tmp = c + tmp;
        }
        str = tmp;
    }

    string ToString() const {
        return str;
    }
private:
    string str;
};
