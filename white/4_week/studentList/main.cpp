#include <iostream>
#include <vector>

using namespace std;

struct Student {
    string first_name;
    string last_name;
    int day;
    int month;
    int year;
};

int main() {
    int n = 0;
    cin >> n;
    vector <Student> studentList(n);
    for (int i = 0; i < n; i++) {
        cin >> studentList[i].first_name >> studentList[i].last_name >>
        studentList[i].day >> studentList[i].month >>
        studentList[i].year;
    }

    int m = 0;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string cmd;
        cin >> cmd;
        int num = 0;
        cin >> num;
        if (cmd == "name" && num > 0 && num <= n) {
            cout << studentList[num - 1].first_name << " " << studentList[num - 1].last_name << endl;
        } else if (cmd == "date" && num > 0 && num <= n) {
            cout << studentList[num - 1].day << "." << studentList[num - 1].month <<
            "." << studentList[num - 1].year << endl;
        } else {
            cout << "bad request" << endl;
        }
    }
    return 0;
}