#include <iostream>
using namespace std;

void tobin (int n){
    if (n == 1) cout << 1;
    else{
        tobin (n / 2);
        cout << n % 2;
    }
}

int main() {
    int n = 0;
    cin >> n;
    tobin(n);
    return 0;
}