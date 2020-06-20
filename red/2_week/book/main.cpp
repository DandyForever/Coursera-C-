#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
            : pages_(MAX_PAGE_NUMBER_, 0) {}

    void Read(int user_id, int page_count) {
        if (progress_.count(user_id))
            pages_[progress_[user_id]]--;
        progress_[user_id] = page_count;
        pages_[progress_[user_id]]++;
    }

    double Cheer(int user_id) const {
        if (!progress_.count(user_id))
            return 0.;
        if (progress_.size() == 1)
            return 1.;
        int count = 0, state = progress_.at(user_id);
        for (int i = 0; i < state; i++)
            count += pages_[i];
        return 1.0 * count / (progress_.size() - 1);
    }

private:
    static const int MAX_PAGE_NUMBER_ = 1000;

    map<int, int> progress_;
    vector<int> pages_;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}