#include <string>
#include <vector>
#include <iostream>

using namespace std;
#define MAKE(name) name

#define CREATE(line) CREATE_(line)
#define CREATE_(line) MAKE(name ## line)

#define UNIQ_ID CREATE(__LINE__)

int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
//    cout << UNIQ_ID;
}