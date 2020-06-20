#include "tests.h"

void Test () {
    {
        PhoneNumber p("+7-495-111-22-33");
        AssertEqual(p.GetCountryCode(), "7", "Test 1 country code");
        AssertEqual(p.GetCityCode(), "495", "Test 1 city code");
        AssertEqual(p.GetLocalNumber(), "111-22-33", "Test 1 local number");
        AssertEqual(p.GetInternationalNumber(), "+7-495-111-22-33", "Test 1 international number");
    }
    {
        try {
            PhoneNumber p("1-2-333");
            Assert(false, "no +");
        } catch (invalid_argument& e) {
        }
    }
    {
        try {
            PhoneNumber p("+7-1233");
            Assert(false, "no local number");
        } catch (invalid_argument& e) {
        }
    }
}

void TestAll () {
    TestRunner tr;
    tr.RunTest(Test, "Test");
}