#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
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

void Assert(bool b, const string& hint = {}) {
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

bool IsPalindrom (const string& str) {
    for (int i = 0; i < str.length() / 2; i++) {
        if (str[i] != str[str.length() - i - 1]) return false;
    }
    return true;
}

void TestEmpty () {
    Assert(IsPalindrom(""), "Empty string is a palindrom");
    Assert(IsPalindrom("  "), "Space even");
    Assert(IsPalindrom("   "), "Space odd");
    Assert(IsPalindrom(" d "), "Space with 1 letter");
    Assert(!IsPalindrom("  d"), "Space with 1 letter");

}

void TestOneSymbol() {
    Assert(IsPalindrom(" "), "One symbol is a palindrom");
    Assert(IsPalindrom("d"), "One symbol is a palindrom");
}

void TestEven () {
    Assert(IsPalindrom("abba"), "even palindrom");
    Assert(!IsPalindrom("abbb"), "even not palindrom");
    Assert(IsPalindrom("qwertyytrewq"), "long test palindrom");
    Assert(!IsPalindrom("qwertyutrewq"), "long test not palindrom");
}

void TestOdd () {
    Assert(IsPalindrom("mamam"), "odd palindrom");
    Assert(!IsPalindrom("maman"), "odd not palindrom");
    Assert(IsPalindrom("qwert y y trewq"), "long test palindrom");
    Assert(!IsPalindrom("qwert y ytrewq"), "long test palindrom");
    Assert(!IsPalindrom("qwert y utrewq"), "long test not palindrom");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestEmpty, "TestEmpty");
    runner.RunTest(TestOneSymbol, "TestOneSymbol");
    runner.RunTest(TestEven, "TestEven");
    runner.RunTest(TestOdd, "TestOdd");
    return 0;
}