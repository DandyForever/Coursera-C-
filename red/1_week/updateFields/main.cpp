#include "airline_ticket.h"
#include "../../../tools/test_runner.h"
#include <iostream>
using namespace std;

#define UPDATE_FIELD(ticket, field, values) {   \
    if (values.count(#field)) {                 \
        istringstream str_(values.at(#field));  \
        str_ >> ticket.field;                   \
    }                                           \
}

istream& operator>> (istream& in, Date& date) {
    char c = ' ';
    in >> date.year;
    in >> c;
    in >> date.month;
    in >> c;
    in >> date.day;
    return in;
}

istream& operator>> (istream& in, Time& time) {
    char c = ' ';
    in >> time.hours;
    in >> c;
    in >> time.minutes;
    return in;
}

ostream& operator<< (ostream& out, const Date& date) {
    out << date.year << "-" << date.month << "-" << date.day;
    return out;
}

ostream& operator<< (ostream& out, const Time& time) {
    out << time.hours << ":" << time.minutes;
    return out;
}

bool operator== (const Date& lv, const Date& rv) {
    return make_tuple(lv.year, lv.month, lv.day) == make_tuple(rv.year, rv.month, rv.day);
}

bool operator== (const Time& lv, const Time& rv) {
    return make_pair(lv.hours, lv.minutes) == make_pair(rv.hours, rv.minutes);
}

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
            {"departure_date", "2018-2-28"},
            {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
            {"price", "12550"},
            {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

// updates2 не содержит ключей "departure_date" и "departure_time", поэтому
// значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
    return 0;
}