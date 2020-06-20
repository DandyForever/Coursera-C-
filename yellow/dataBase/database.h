#pragma once
#include "date.h"

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <utility>
#include <set>

using namespace std;

class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& stream) const;

    vector<pair<Date, string>> FindIf(const function<bool(const Date&, const string&)> predicate) const;
    int RemoveIf(const function<bool(const Date&, const string&)> predicate);

    string Last(const Date& date) const;

private:
    map<Date, pair<set<string>, vector<set<string>::iterator>>> mapDBevents_;
};

ostream& operator<< (ostream& stream, const pair<Date, string>& p);