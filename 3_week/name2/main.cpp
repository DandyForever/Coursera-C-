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
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }
    string GetFullName(int year) {
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);

        if (first_name.empty() && last_name.empty()) {
            return "Incognito";

        } else if (first_name.empty()) {
            return last_name + " with unknown first name";

        } else if (last_name.empty()) {
            return first_name + " with unknown last name";

        } else {
            return first_name + " " + last_name;
        }
    }

    string GetFullNameWithHistory(int year) {
        const string first_name = FindAllNamesByYear(first_names, year);
        const string last_name = FindAllNamesByYear(last_names, year);

        if (first_name.empty() && last_name.empty()) {
            return "Incognito";

        } else if (first_name.empty()) {
            return last_name + " with unknown first name";

        } else if (last_name.empty()) {
            return first_name + " with unknown last name";

        } else {
            return first_name + " " + last_name;
        }
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}
