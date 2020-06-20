#include <iostream>
#include <cmath>
#include <sstream>
#include <set>
#include <vector>
#include <map>

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

class Rational {
public:
    Rational() {
        num = 0;
        den = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0)
            throw invalid_argument("Invalid argument");
        if (numerator == 0) {
            num = 0;
            den = 1;
        } else {
            int p = gcf(abs(numerator), abs(denominator));
            num = numerator / p;
            den = denominator / p;
            if (den < 0) {
                num = -num;
                den = -den;
            }
        }
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return den;
    }
private:
    int num;
    int den;
};

bool operator== (const Rational& lv, const Rational& rv) {
    return (lv.Denominator() == rv.Denominator() && lv.Numerator() == rv.Numerator());
}

Rational operator+ (const Rational& lv, const Rational& rv) {
    return {lv.Denominator() * rv.Numerator() + lv.Numerator() * rv.Denominator(),
            lv.Denominator() * rv.Denominator()};
}

Rational operator- (const Rational& lv, const Rational& rv) {
    return {lv.Numerator() * rv.Denominator() - rv.Numerator() * lv.Denominator(),
            lv.Denominator() * rv.Denominator()};
}

Rational operator* (const Rational& lv, const Rational& rv) {
    return {lv.Numerator() * rv.Numerator(),
            lv.Denominator() * rv.Denominator()};
}

Rational operator/ (const Rational& lv, const Rational& rv) {
    if (rv.Numerator() == 0)
        throw domain_error("Division by zero");
    return {lv.Numerator() * rv.Denominator(),
            lv.Denominator() * rv.Numerator()};
}

istream& operator>> (istream& inp, Rational& item) {
    int num = item.Numerator(), den = item.Denominator();
    inp >> num;
    inp.ignore(1);
    inp >> den;
    item = Rational(num, den);
    return inp;
}

ostream& operator<< (ostream& out, const Rational& item) {
    out << item.Numerator() << "/" << item.Denominator();
    return out;
}

bool operator< (const Rational& lv, const Rational& rv) {
    return (lv.Numerator() * rv.Denominator() < lv.Denominator() * rv.Numerator());
}

int main () {
    Rational x, y;
    char operation = ' ';
    try {
        cin >> x >> operation >> y;
    } catch (invalid_argument& ex) {
        cout << ex.what() << endl;
        return 0;
    }
    try {
        if (operation == '+')
            cout << x + y;
        else if (operation == '-')
            cout << x - y;
        else if (operation == '*')
            cout << x * y;
        else if (operation == '/')
            cout << x / y;
    } catch (domain_error& ex) {
        cout << ex.what() << endl;
    }
    return 0;
}