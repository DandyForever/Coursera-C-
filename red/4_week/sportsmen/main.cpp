#include <iostream>
#include <list>
#include <map>

using namespace std;

class SportsmenOrderManager {
public:
    void add (int current, int next) {
        if (!mapping_.count(next)) {
            order_.push_back(current);
            mapping_[current] = prev(order_.end());
            return;
        }
        order_.insert(mapping_[next], current);
        mapping_[current] = prev(mapping_[next]);
    }

    void print () {
        for (auto item : order_) {
            cout << item << '\n';
        }
    }
private:
    list <int> order_;
    map <int, list<int>::iterator> mapping_;
};

int main() {
    int n = 0;
    cin >> n;
    SportsmenOrderManager manager;
    for (int i = 0; i < n; i++) {
        int cur = 0, next = 0;
        cin >> cur >> next;
        manager.add(cur, next);
    }
    manager.print();
    return 0;
}