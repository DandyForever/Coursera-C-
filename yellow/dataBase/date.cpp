#include "date.h"

#include <iomanip>
#include <tuple>
#include <sstream>

// Constructor
Date::Date(const int& year, const int& month, const int& day) : year_(year), month_(month), day_(day) {};

// Getters
int Date::GetYear() const {
    return year_;
}

int Date::GetMonth() const {
    return month_;
}

int Date::GetDay() const {
    return day_;
}

string Date::ToString() const {
    stringstream ss;
    ss << *this;
    return ss.str();
}

// Creating Date object from an input stream
Date ParseDate(istream& input) {
    int year, month, day;
    input >> year;
    input.ignore(1);
    input >> month;
    input.ignore(1);
    input >> day;

    return Date(year, month, day);
}

// Equatation operators
bool operator< (const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) < make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<= (const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <= make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator> (const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) > make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>= (const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >= make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator== (const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) == make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator!= (const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) != make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

// Operator << to give Date object to output stream
ostream& operator<< (ostream& stream, const Date& date) {
    stream << setfill('0') << setw(4) << date.GetYear()
           << '-' << setfill('0') << setw(2) << date.GetMonth()
           << '-' << setfill('0') << setw(2) << date.GetDay();

    return stream;
}