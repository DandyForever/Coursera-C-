#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

const int MINMD = 0;
const int MAXMONTH = 12;
const int MAXDAY = 31;

class Date {
public:
    Date () {
        year = 0;
        month = 1;
        day = 1;
    }
    Date (int year_, int month_, int day_) {
        year = year_;
        month = month_;
        day = day_;
    }

    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }

private:
    int day;
    int month;
    int year;
};

string to_str (int value) {
    if (value == 0)
        return string("0");
    string str;
    int copy = value;
    if (value < 0)
        value = -value;
    while (value > 0) {
        str.push_back(value % 10 + '0');
        value /= 10;
    }
    if (copy < 0) {
        str.push_back('-');
     }
    reverse(begin (str), end(str));
    return str;
}

stringstream& operator >> (stringstream& input, Date& date){
    string dat;
    input >> dat;
    stringstream inp(dat);

    int year = -1;
    if (!(inp >> year) || inp.peek() != '-') {
        throw out_of_range("Wrong date format: " + dat);
    }
    inp.ignore(1);

    int month = 0;
    if (!(inp >> month) || inp.peek() != '-') {
        throw out_of_range("Wrong date format: " + dat);
    }
    inp.ignore(1);

    int day = 0;
    if (!(inp >> day) || !inp.eof()) {
        throw out_of_range("Wrong date format: " + dat);
    }

    if (!(month > MINMD && month <= MAXMONTH)) {
        throw out_of_range("Month value is invalid: " + to_str(month));
    }
    if (!(day > MINMD && day <= MAXDAY)) {
       throw out_of_range ("Day value is invalid: " + to_str(day));
    }

    date = Date(year, month, day);

    return input;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return (lhs.GetDay() < rhs.GetDay());
        } else {
            return (lhs.GetMonth() < rhs.GetMonth());
        }
    } else {
        return (lhs.GetYear() < rhs.GetYear());
    }
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        if (!data[date].count(event)) {
            data[date].insert(event);
        }
    }
    bool DeleteEvent(const Date& date, const string& event) {
        if (data[date].count(event) == 0)
            return false;
        else {
            data[date].erase(event);
            return true;
        }
    }
    int  DeleteDate(const Date& date) {
        int number = data[date].size();
        data[date].erase(begin(data[date]), end(data[date]));
        return number;
    }

    set <string> Find(const Date& date) const {
        if (data.count(date) > 0) {
            return data.at(date);
        } else {
            set <string> empty;
            return empty;
        }
    }

    void Print() const {
        if (data.empty())
            return;
        for (const auto& item : data) {
            for (const auto& event : item.second) {
                cout.fill('0');
                cout << setw(4) << item.first.GetYear() << '-' << setw(2) <<
                item.first.GetMonth() << '-' << setw(2) << item.first.GetDay() <<
                ' ' << event << endl;
            }
        }
    }

private:
    map <Date, set <string>> data;
};

void cmdAdd (stringstream& line, Database& db) {
    Date date;
    try {
        line >> date;
    } catch (out_of_range& ex){
        throw ex;
    }
    string event;
    line >> event;
    db.AddEvent(date, event);
}

void cmdDel (stringstream& line, Database& db) {
    Date date;
    try {
        line >> date;
    } catch (out_of_range& ex){
        throw ex;
    }
    if (line.eof()) {
        cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
    } else {
        string event;
        line >> event;
        if (db.DeleteEvent(date, event)) {
            cout << "Deleted successfully" << endl;
        } else {
            cout << "Event not found" << endl;
        }
    }
}

void cmdFind (stringstream& line, Database& db) {
    Date date;
    try {
        line >> date;
    } catch (out_of_range& ex){
        throw ex;
    }

    set <string> events = db.Find(date);
    if (events.empty())
        return;
    for (const auto& item : events) {
        cout << item << endl;
    }
}

void cmdPrint (Database& db) {
    db.Print();
}

void cmdHandler (const string& cmd, Database& db) {
    stringstream line(cmd);
    string command;
    line >> command;
    if (command == "Add") {
        try {
            cmdAdd (line, db);
        } catch (out_of_range& ex) {
            throw ex;
        }
    } else if (command == "Del") {
        try {
            cmdDel (line, db);
        } catch (out_of_range& ex) {
            throw ex;
        }
    } else if (command == "Find") {
        try {
            cmdFind (line, db);
        } catch (out_of_range& ex) {
            throw ex;
        }
    } else if (command == "Print") {
        cmdPrint (db);
    } else if (!command.empty()){
        throw out_of_range ("Unknown command: " + command);
    }
}

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        try {
            cmdHandler(command, db);
        } catch (out_of_range& ex) {
            cout << ex.what() << endl;
            return 1;
        }
    }

    return 0;
}