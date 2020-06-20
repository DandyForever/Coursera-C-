#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

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

//class Person {
//public:
//    void ChangeFirstName(int year, const string& first_name) {
//        Name record = {first_name, "", year};
//        string nearFirst;
//        for (auto & item : history) {
//            if (item.year < year) {
//                record.last = item.last;
//                nearFirst = item.first;
//            }
//            if (item.year == year) {
//                nearFirst = item.first;
//                item.first = first_name;
//                record.year = -1;
//            }
//            if (item.year > year && item.first == nearFirst) {
//                item.first = first_name;
//            }
//        }
//        if (record.year == -1)
//            return;
//        history.push_back(record);
//        sort (begin(history), end(history), [](const Name& x, const Name& y) {
//            return (x.year < y.year);
//        });
//        //printHistory();
//    }
//    void ChangeLastName(int year, const string& last_name) {
//        string nearLast;
//        Name record = {"", last_name, year};
//        for (auto & item : history) {
//            if (item.year < year) {
//                record.first = item.first;
//                nearLast = item.last;
//            }
//            if (item.year == year) {
//                nearLast = item.last;
//                item.last = last_name;
//                record.year = -1;
//            }
//            if (item.year > year && item.last == nearLast) {
//                item.last = last_name;
//            }
//        }
//        if (record.year == -1)
//            return;
//        history.push_back(record);
//        sort (begin (history), end(history), [](const Name& x, const Name& y) {
//            return (x.year < y.year);
//        });
//        //printHistory();
//    }
//    string GetFullName(int year) {
//        Name record = {"", "", -1};
//        for (const auto& item : history) {
//            if (item.year <= year) {
//                //cout << item.year << ' ' << year << endl;
//                record = item;
//            }
//        }
//        if (record.first.empty() && record.last.empty())
//            return "Incognito";
//        else if (record.first.empty())
//            return record.last + " with unknown first name";
//        else if (record.last.empty())
//            return record.first + " with unknown last name";
//        else return record.first + " " + record.last;
//    }
//private:
//    struct Name {
//        string first;
//        string last;
//        int year;
//    };
//    vector <Name> history;
//    void printHistory () {
//        cout << "start_print_history" << endl;
//        for (const auto& item : history) {
//            cout << item.year << " " << item.first << " " << item.last << endl;
//        }
//        cout << "end_print_history" << endl;
//    }
//};

void TestIncognito () {
    {
        Person p;
        AssertEqual(p.GetFullName(1), "Incognito", "Empty Person");
    }
    {
        Person p;
        p.ChangeFirstName(2000, "Ivan");
        AssertEqual(p.GetFullName(1), "Incognito", "Before changing first name");
    }
    {
        Person p;
        p.ChangeLastName(2000, "Ivanov");
        AssertEqual(p.GetFullName(1), "Incognito", "Before changing last name");
    }
    {
        Person p;
        p.ChangeFirstName(2000, "Ivan");
        p.ChangeLastName(2000, "Ivanov");
        AssertEqual(p.GetFullName(1), "Incognito", "Before changing name");
    }
};

void TestUnknownFirstName () {
    {
        Person p;
        p.ChangeLastName(2000, "Ivanov");
        AssertEqual(p.GetFullName(2000), "Ivanov with unknown first name",
                "Last name changed this year");
    }
    {
        Person p;
        p.ChangeLastName(2000, "Ivanov");
        AssertEqual(p.GetFullName(2001), "Ivanov with unknown first name",
                "Last name changed year before");
    }
    {
        Person p;
        p.ChangeLastName(2000, "Ivanov");
        p.ChangeLastName(3000, "Sidorov");
        AssertEqual(p.GetFullName(2000), "Ivanov with unknown first name",
                "Two changes, the year of first change");
        AssertEqual(p.GetFullName(2001), "Ivanov with unknown first name",
                "Two changes, the year between changes");
        AssertEqual(p.GetFullName(3000), "Sidorov with unknown first name",
                "Two changes, the year of second change");
        AssertEqual(p.GetFullName(3001), "Sidorov with unknown first name",
                "Two changes, the year after changes");
    }
}

void TestUnknownLastName () {
    {
        Person p;
        p.ChangeFirstName(2000, "Ivan");
        AssertEqual(p.GetFullName(2000), "Ivan with unknown last name",
                    "First name changed this year");
    }
    {
        Person p;
        p.ChangeFirstName(2000, "Ivan");
        AssertEqual(p.GetFullName(2001), "Ivan with unknown last name",
                    "First name changed year before");
    }
    {
        Person p;
        p.ChangeFirstName(2000, "Ivan");
        p.ChangeFirstName(3000, "Sidor");
        AssertEqual(p.GetFullName(2000), "Ivan with unknown last name",
                    "Two changes, the year of first change");
        AssertEqual(p.GetFullName(2001), "Ivan with unknown last name",
                    "Two changes, the year between changes");
        AssertEqual(p.GetFullName(3000), "Sidor with unknown last name",
                    "Two changes, the year of second change");
        AssertEqual(p.GetFullName(3001), "Sidor with unknown last name",
                    "Two changes, the year after changes");
    }
}

void TestName () {
    {
        Person p;
        p.ChangeFirstName(2000, "Ivan");
        p.ChangeLastName(2000, "Ivanov");
        AssertEqual(p.GetFullName(2000), "Ivan Ivanov", "Change name this year");
        AssertEqual(p.GetFullName(2000), "Ivan Ivanov", "Check GetFullName is const method");
        AssertEqual(p.GetFullName(2001), "Ivan Ivanov", "Change name the year after");
        p.ChangeFirstName(2001, "Boris");
        AssertEqual(p.GetFullName(2001), "Boris Ivanov", "Change first name second time");
        p.ChangeLastName(2001, "Petrov");
        AssertEqual(p.GetFullName(2001), "Boris Petrov", "Change name second time");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestIncognito, "TestIncognito");
    runner.RunTest(TestUnknownFirstName, "TestUnknownFirstName");
    runner.RunTest(TestUnknownLastName, "TestUnknownLastName");
    runner.RunTest(TestName, "TestName");
    return 0;
}