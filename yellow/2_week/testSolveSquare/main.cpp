#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>

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

//int GetDistinctRealRootCount(double a, double b, double c) {
//    if (a == 0) {
//        if (b == 0) {
//            return 0;
//        } else
//            return 1;
//    } else {
//        double D = b * b -  a * c;
//        if (abs(D) < 1e-6)
//            return 1;
//        if (D < 0)
//            return 0;
//        return 2;
//    }
//}

void TestLinear () {
    {
        double a = 0, b = 0, c = 1;
        AssertEqual(GetDistinctRealRootCount(a, b, c), 0, "Linear with 0 roots");
    }
    {
        double a = 0, b = 1, c = 1;
        AssertEqual(GetDistinctRealRootCount(a, b, c), 1, "Linear with 1 root");
    }
}

void TestSquare () {
    {
        double a = 1, b = 0, c = -4;
        AssertEqual(GetDistinctRealRootCount(a, b, c), 2, "Square with 2 roots");
    }
    {
        double a = 1, b = 4, c = 4;
        AssertEqual(GetDistinctRealRootCount(a, b, c), 1, "Square with 1 root");
    }
    {
        double a = 1, b = 0, c = 4;
        AssertEqual(GetDistinctRealRootCount(a, b, c), 0, "Square with 0 roots");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestLinear, "TestLinear");
    runner.RunTest(TestSquare, "TestSquare");
    return 0;
}