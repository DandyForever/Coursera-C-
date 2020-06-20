#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(fail_count);
        }
    }

private:
    int fail_count = 0;
};

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

//class Rational {
//public:
//    Rational() {
//        num = 0;
//        den = 1;
//    }
//
//    Rational(int numerator, int denominator) {
//        if (denominator == 0)
//            throw invalid_argument("Invalid argument");
//        if (numerator == 0) {
//            num = 0;
//            den = 1;
//        } else {
//            int p = gcf(abs(numerator), abs(denominator));
//            num = numerator / p;
//            den = denominator / p;
//            if (den < 0) {
//                num = -num;
//                den = -den;
//            }
//        }
//    }
//
//    int Numerator() const {
//        return num;
//    }
//
//    int Denominator() const {
//        return den;
//    }
//private:
//    int num;
//    int den;
//};

void TestDefaultConstructor () {
    {
        Rational r;
        AssertEqual(r.Numerator(), 0, "Numerator should be 0");
        AssertEqual(r.Denominator(), 1, "Denominator should be 1");
        AssertEqual(r.Numerator(), 0, "Numerator is const method");
        AssertEqual(r.Denominator(), 1, "Denominator is const method");
    }
}

void TestSimplifying () {
    {
        Rational r(2, 4);
        AssertEqual(r.Numerator(), 1, "2/4 = 1/2 (numerator)");
        AssertEqual(r.Denominator(), 2, "2/4 = 1/2 (denominator)");
    }
    {
        Rational r(3, 7);
        AssertEqual(r.Numerator(), 3, "3/7 numerator shouldn't be simplifyed");
        AssertEqual(r.Denominator(), 7, "3/7 denominator shouldn't be simplifyed");
    }
    {
        Rational r(0, 5);
        AssertEqual(r.Numerator(), 0, "0/5 should be 0/1 (numerator)");
        AssertEqual(r.Denominator(), 1, "0/5 should be 0/1 (denominator)");
    }
}

void TestNegative () {
    {
        Rational r(-3, 7);
        AssertEqual(r.Numerator(), -3, "-3/7: numerator = -3");
        AssertEqual(r.Denominator(), 7, "-3/7: denominator = 7");
    }
    {
        Rational r(3, -7);
        AssertEqual(r.Numerator(), -3, "3/-7: numerator = -3");
        AssertEqual(r.Denominator(), 7, "3/-7: denominator = 7");
    }
    {
        Rational r(-3, -7);
        AssertEqual(r.Numerator(), 3, "-3/-7: numerator = 3");
        AssertEqual(r.Denominator(), 7, "-3/-7: denominator = 7");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestSimplifying, "TestSimplifying");
    runner.RunTest(TestNegative, "TestNegative");
    return 0;
}