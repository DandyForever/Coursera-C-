#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n = 0;
    int month = 1;
    cin >> n;
    vector <vector <string>> concerns(32);
    for (int i = 0; i < n; i++){
        string cur;
        cin >> cur;
        if (cur == "ADD") {
            int day = 0;
            cin >> day;
            string concern;
            cin >> concern;
            concerns[day].push_back(concern);
        } else if (cur == "DUMP") {
            int day = 0;
            cin >> day;
            cout << concerns[day].size() << " ";
            for (auto item : concerns[day]) {
                cout << item << " ";
            }
            cout << endl;
        } else if (cur == "NEXT") {
            if (month == 1) {
                month++;
                concerns[28].insert(end(concerns[28]), begin(concerns[29]), end(concerns[29]));
                concerns[28].insert(end(concerns[28]), begin(concerns[30]), end(concerns[30]));
                concerns[28].insert(end(concerns[28]), begin(concerns[31]), end(concerns[31]));
                concerns.resize(29);
            } else if (month == 2 || month == 4 || month == 6 || month == 9 || month == 11) {
                month++;
                concerns.resize(32);
            } else if (month == 7 || month == 12) {
                month = (month + 1) % 12;
            } else{
                month++;
                concerns[30].insert(end(concerns[30]), begin(concerns[31]), end(concerns[31]));
                concerns.resize(31);
            }
        }
    }
    return 0;
}