#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    if (input) {
        string line;
        while (getline(input, line)) {
            cout << line << endl;
//            output << line << endl;
        }
    } else {
        cout << "error" << endl;
    }
    return 0;
}