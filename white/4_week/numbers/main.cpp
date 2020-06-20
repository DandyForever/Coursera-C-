#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    if (input) {
        double x = 0;
        input >> x;
        cout << fixed << setprecision(3);
        while (input) {
            cout << x << endl;
            input >> x;
        }
    }
    return 0;
}