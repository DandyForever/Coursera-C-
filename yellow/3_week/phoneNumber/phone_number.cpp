#include <sstream>
#include <stdexcept>
#include <iostream>
#include "phone_number.h"

PhoneNumber::PhoneNumber(const string &international_number) {
    stringstream s(international_number);

    if (s.peek() != '+')
        throw invalid_argument ("");

    s.ignore(1);
    getline(s, country_code_, '-');
    if (country_code_.empty())
        throw invalid_argument("");

    getline(s, city_code_, '-');
    if (city_code_.empty())
        throw invalid_argument("");

    getline(s, local_number_);
    if (local_number_.empty())
        throw invalid_argument("");

}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}
string PhoneNumber::GetCityCode() const {
    return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}