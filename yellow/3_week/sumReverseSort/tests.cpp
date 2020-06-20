#include "tests.h"

void TestSum () {
    AssertEqual(Sum(-1, 1), 0, "-1 + 1 = 0");
}

void TestReverse () {
    AssertEqual(Reverse("mama"), "amam", "mama -> amam");
}

void TestSort () {
    vector <int> v = {2, 3, 5, 1, 4};
    Sort(v);
    vector <int> vSorted = {1, 2, 3, 4, 5};
    AssertEqual(v, vSorted, "sorting");
}

void TestAll () {
    TestRunner tr;
    tr.RunTest(TestSum, "TestSum");
    tr.RunTest(TestReverse, "TestReverse");
    tr.RunTest(TestSort, "TestSort");
}