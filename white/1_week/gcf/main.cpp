#include <iostream>
using namespace std;

int gcf (int a, int b) {
    if (a < b){
        if (b % a == 0) return a;
        else return gcf(a, b % a);
    }
    else{
        if (a % b == 0) return b;
        else return gcf(b, a % b);
    }
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << gcf(a, b);
    return 0;
}