#include <iostream>
#include <vector>
using namespace std;


int average (const vector <int> & temps) {
    int sum = 0;
    for (auto item : temps) {
        sum += item;
    }
    return sum / temps.size();
}

vector <int> moreThanAvg (const vector <int> & temps) {
    vector <int> tmp;
    int avg = average(temps);
    for (int i = 0; i < temps.size(); i++) {
        if (temps[i] > avg)
            tmp.push_back(i);
    }
    return tmp;
}

int main() {
    int n = 0;
    cin >> n;
    vector <int> temps(n);
    for (int& item : temps) {
        cin >> item;
    }
    vector <int> newTemps = moreThanAvg(temps);
    cout << newTemps.size() << endl;
    for (auto item: newTemps) {
        cout << item << " ";
    }
    return 0;
}