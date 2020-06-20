#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    int n = 0, m = 0;
    input >> n >> m;
    int item = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            input >> item;
            if (j == m - 1) {
                cout << setw(10) << item;
            } else {
                cout << setw(10) << item << " ";
                input.ignore(1);
            }
        }
        if (i != n - 1)
            cout << endl;
    }
    return 0;
}