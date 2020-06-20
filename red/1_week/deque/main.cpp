#include <iostream>
#include "../../../tools/test_runner.h"
#include "Deque.cpp"

void TestDeque () {
    Deque<int> d;
    ASSERT(d.Empty());
    d.PushBack(1);
    d.PushFront(-5);
    ASSERT_EQUAL(d[0], -5);
    ASSERT_EQUAL(d[1], 1);
    ASSERT_EQUAL(d.Size(), 2);
    ASSERT_EQUAL(d.At(1), 1);
    ASSERT_EQUAL(d.At(0), -5);
    try {
        d.At(2);
    } catch (out_of_range& ex) {
        ASSERT(1);
    }
    ASSERT_EQUAL(d.Front(), -5);
    ASSERT_EQUAL(d.Back(), 1);
    d.At(0) = -6;
    d.At(1) = 2;
    ASSERT_EQUAL(d[0], -6);
    ASSERT_EQUAL(d[1], 2);
    d.PushFront(-3);
    d.PushBack(5);
    ASSERT_EQUAL(d.Size(), 4);
    ASSERT_EQUAL(d[0], -3);
    ASSERT_EQUAL(d[1], -6);
    ASSERT_EQUAL(d[2], 2);
    ASSERT_EQUAL(d[3], 5);
    d[4] = 0;
    ASSERT_EQUAL(d.Size(), 4);
    ASSERT_EQUAL(d[0], -3);
    ASSERT_EQUAL(d[1], -6);
    ASSERT_EQUAL(d[2], 2);
    ASSERT_EQUAL(d[3], 5);
    ASSERT_EQUAL(d[4], 0);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestDeque);
    return 0;
}