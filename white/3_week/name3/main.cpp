#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>

using namespace std;

string FindNameByYear(const map<int, string>& names, int year) {
    string name;

    for (const auto& item : names) {
        if (item.first <= year) {
            name = item.second;
        } else {
            break;
        }
    }
    return name;
}

string FindAllNamesByYear(const map<int, string>& names, int year) {
    string name;
    vector <string> line;

    for (const auto& item : names) {
        if (item.first <= year) {
            name = item.second;
            if (line.empty() || line[line.size() - 1] != item.second)
                line.push_back(item.second);
        } else
            break;
    }

    if (name.empty())
        return name;
    if (line.size() == 1)
        return name;
    name += " (";
    for (int i = line.size() - 2; i >= 0; i--) {
        if (i == 0) {
            name += line[i] + ")";
        } else {
            name += line[i] + ", ";
        }
    }
    return name;
}

class Person {
public:
    Person (const string & name, const string & last_name, int year) {
        first_names[year] = name;
        last_names[year] = last_name;
    }
    void ChangeFirstName(int year, const string& first_name) {
        for (const auto& item : first_names) {
            if (item.first > year)
                return;
            else
                break;
        }
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        for (const auto& item : last_names) {
            if (item.first > year)
                return;
            else
                break;
        }
        last_names[year] = last_name;
    }
    string GetFullName(int year) const {
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);

        if (first_name.empty() || last_name.empty()) {
            return "No person";

        } else {
            return first_name + " " + last_name;
        }
    }

    string GetFullNameWithHistory(int year) const {
        const string first_name = FindAllNamesByYear(first_names, year);
        const string last_name = FindAllNamesByYear(last_names, year);

        if (first_name.empty() && last_name.empty()) {
            return "No person";

        } else {
            return first_name + " " + last_name;
        }
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;
};

int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}
