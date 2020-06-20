#include "database.h"

#include <algorithm>
#include <string>
#include <iostream>

void Database::Add(const Date& date, const string& event) {

    if (mapDBevents_.count(date) > 0) {
        auto insert_result = mapDBevents_[date].first.insert(event);
        if (insert_result.second) {
            mapDBevents_[date].second.push_back(insert_result.first);
        }
    }
    else {
        auto insert_result = mapDBevents_[date].first.insert(event);
        mapDBevents_[date].second.push_back(insert_result.first);
    }
}

void Database::Print(ostream& stream) const {
    for (const auto& entry : mapDBevents_) {
        for (const auto& it : entry.second.second) {
            stream << entry.first << " " << *it << endl;
        }
    }
}

vector<pair<Date, string>> Database::FindIf(const function<bool(const Date&, const string&)> predicate) const {
    vector<pair<Date, string>> result;

    for (const auto& entry : mapDBevents_) {
        for (auto& it : entry.second.second) {
            if (predicate(entry.first, *it)) {
                result.push_back(make_pair(entry.first, *it));
            }
        }
    }

    return result;
}

int Database::RemoveIf(const function<bool(const Date&, const string&)> predicate) {
    int counter = 0;

    for (auto date_it = mapDBevents_.begin(); date_it != mapDBevents_.end(); ) {
        for (auto event_it = (*date_it).second.second.begin(); event_it != (*date_it).second.second.end(); ) {
            if (predicate((*date_it).first, *(*event_it))) {
                mapDBevents_[(*date_it).first].first.erase(*(*event_it));
                event_it = mapDBevents_[(*date_it).first].second.erase(event_it);

                counter++;
            }
            else {
                event_it++;
            }
        }

        if (mapDBevents_[(*date_it).first].first.size() == 0) {
            date_it = mapDBevents_.erase(date_it);
        }
        else {
            date_it++;
        }
    }

    return counter;
}

string Database::Last(const Date& date) const {
    auto it = mapDBevents_.upper_bound(date);

    if (it != mapDBevents_.begin()) {
        return (*prev(it)).first.ToString() + " " + *(*prev(it)).second.second.back();
    }
    else {
        return "No entries";
    }
}

ostream& operator<< (ostream& stream, const pair<Date, string>& p) {
    stream << p.first << " " << p.second;

    return stream;
}