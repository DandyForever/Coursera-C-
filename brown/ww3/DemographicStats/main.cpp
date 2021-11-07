#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <map>
#include <set>
#include <cassert>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
            : first(begin)
            , last(end)
    {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

private:
    Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
    return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
    string name;
    int age, income;
    bool is_male;
};

class Demographic {
public:
    Demographic(int person_number): number_people(person_number),
    ages(person_number, 0), incomes(person_number, 0), top_incomes(person_number + 1, 0) {}
    void AddPerson(const Person& person) {
        ages[current_people] = person.age;
        incomes[current_people] = person.income;
        current_people++;
        if (current_people == number_people) {
            std::sort(ages.begin(), ages.end());
            std::sort(incomes.begin(), incomes.end());
            for (int i = 1; i <= number_people; i++)
                top_incomes[i] = top_incomes[i - 1] + incomes[number_people - i];
        }
        if (person.is_male) {
            male_names[++male_names_map[person.name]].insert(person.name);
            return;
        }
        female_names[++female_names_map[person.name]].insert(person.name);
    }

    int GetAdults(int adult_age) {
        return ages.end() - std::lower_bound(ages.begin(), ages.end(), adult_age);
    }

    int GetTopIncome(int people_number) {
        if (people_number > number_people)
            return top_incomes[number_people];
        return top_incomes[people_number];
    }

    string GetTopName(bool is_male) {
        if (is_male) {
            return *male_names.rbegin()->second.begin();
        }
        return *female_names.rbegin()->second.begin();;
    }

    bool IsPeopleExist(bool is_male) {
        if (is_male)
            return male_names.empty();
        return female_names.empty();
    }
private:
    unordered_map<string, int> female_names_map;
    unordered_map<string, int> male_names_map;
    map<int, set<string>> male_names;
    map<int, set<string>> female_names;
    vector<int> ages;
    vector<int> incomes;
    vector<int> top_incomes;
    int number_people;
    int current_people = 0;
};

Demographic ReadPeople(istream& input) {
    int count;
    input >> count;

    Demographic demographic(count);
    for (int i = 0; i < count; i++) {
        Person p;
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
        demographic.AddPerson(p);
    }

    return demographic;
}

int main() {
    Demographic stats = ReadPeople(cin);

    for (string command; cin >> command; ) {
        if (command == "AGE") {
            int adult_age;
            cin >> adult_age;
            cout << "There are " << stats.GetAdults(adult_age)
                 << " adult people for maturity age " << adult_age << '\n';
        } else if (command == "WEALTHY") {
            int count;
            cin >> count;
            cout << "Top-" << count << " people have total income " << stats.GetTopIncome(count) << '\n';
        } else if (command == "POPULAR_NAME") {
            char gender;
            cin >> gender;
            if (stats.IsPeopleExist(gender == 'M')) {
                cout << "No people of gender " << gender << '\n';
            } else {
                cout << "Most popular name among people of gender " << gender << " is "
                     << stats.GetTopName(gender == 'M') << '\n';
            }
        }
    }
}