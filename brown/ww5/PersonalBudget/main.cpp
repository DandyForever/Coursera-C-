#include <iostream>
#include <ctime>
#include <map>

using namespace std;

struct Date {
    int day_ = 0;
    int month_ = 0;
    int year_ = 0;

    time_t AsTimestamp() const;
    friend istream& operator>>(istream& is, Date& date) {
        char c;
        is >> date.year_ >> c >> date.month_ >> c >> date.day_;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Date& date) {
        os << date.year_ << '-' << date.month_ << '-' << date.day_;
        return os;
    }
    friend bool operator<(const Date& lhs, const Date& rhs) {
        return lhs.AsTimestamp() < rhs.AsTimestamp();
    }
};
time_t Date::AsTimestamp() const {
    std::tm t;
    t.tm_sec   = 0;
    t.tm_min   = 0;
    t.tm_hour  = 0;
    t.tm_mday  = day_;
    t.tm_mon   = month_ - 1;
    t.tm_year  = year_ - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
}
int ComputeDaysDiff(const Date& date_to, const Date& date_from);

class Budget {
public:
    Budget() {
        for (time_t date = min_date_.AsTimestamp(); date <= max_date_.AsTimestamp(); date += SECONDS_IN_DAY) {
            income_[date] = 0.;
            outcome_[date] = 0.;
        }
    }

    double ComputeIncome(const Date& from, const Date& to) {
        double income = 0.;
        auto it = income_.find(from.AsTimestamp());
        auto last = income_.find(to.AsTimestamp());
        for (; it != next(last); it++) {
            income += it->second;
        }
        double outcome = 0.;
        it = outcome_.find(from.AsTimestamp());
        last = outcome_.find(to.AsTimestamp());
        for (; it != next(last); it++) {
            outcome += it->second;
        }
        return income - outcome;
    }

    void Earn(const Date& from, const Date& to, int income) {
        double income_day = 1. * income / (ComputeDaysDiff(to, from) + 1.);
        auto it = income_.find(from.AsTimestamp());
        auto last = income_.find(to.AsTimestamp());
        for (; it != next(last); it++) {
            it->second += income_day;
        }
    }

    void PayTax(const Date& from, const Date& to, double percentage) {
        auto it = income_.find(from.AsTimestamp());
        auto last = income_.find(to.AsTimestamp());
        for (; it != next(last); it++) {
            it->second *= percentage;
        }
    }

    void Spend(const Date& from, const Date& to, int outcome) {
        double outcome_day = 1. * outcome / (ComputeDaysDiff(to, from) + 1.);
        auto it = outcome_.find(from.AsTimestamp());
        auto last = outcome_.find(to.AsTimestamp());
        for (; it != next(last); it++) {
            it->second += outcome_day;
        }
    }

    static const int SECONDS_IN_DAY = 60 * 60 * 24;
private:
    map<time_t, double> income_;
    map<time_t, double> outcome_;
    const Date min_date_{01, 01, 2000};
    const Date max_date_{31, 12, 2099};
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    return (timestamp_to - timestamp_from) / Budget::SECONDS_IN_DAY;
}

int main() {
    int n = 0;
    cin >> n;
    Budget budget;
    for (int i = 0; i < n; i++) {
        string query; Date from, to;
        cin >> query >> from >> to;
        if (query == "ComputeIncome") {
            cout.precision(25);
            cout << budget.ComputeIncome(from, to) << '\n';
        } else if (query == "Earn") {
            int value = 0;
            cin >> value;
            budget.Earn(from, to, value);
        } else if (query == "PayTax") {
            int tax = 0;
            cin >> tax;
            budget.PayTax(from, to, 1. - 1. * tax/100);
        } else if (query == "Spend") {
            int value = 0;
            cin >> value;
            budget.Spend(from, to, value);
        }
    }
    return 0;
}
