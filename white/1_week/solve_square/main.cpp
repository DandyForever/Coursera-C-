#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;
    if (a == 0) {
        if (b != 0) {
            double root = -c / b;
            cout << root;
        }
        return 0;
    }
    double d = b * b - 4 * a * c;
    if (abs(d) < 1e-6){
        double root = -b / 2 / a;
        cout << root;
        return 0;
    }
    if (d > 0) {
        d = sqrt(d);
        double root1 = (-b - d) / 2 / a;
        double root2 = (-b + d) / 2 / a;
        cout << root1 << " " << root2;
    }
    return 0;
}