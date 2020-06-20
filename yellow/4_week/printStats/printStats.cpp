#include "printStats.h"

void PrintStats(vector<Person> persons) {
    cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;
    cout << "Median age for females = " <<
        ComputeMedianAge(begin(persons),
                partition(begin(persons), end(persons), [](const Person& p) {
                    return p.gender == Gender::FEMALE;
                })) << endl;
    cout << "Median age for males = " <<
        ComputeMedianAge(begin(persons),
                partition(begin(persons), end(persons), [](const Person& p) {
                    return p.gender == Gender::MALE;
                })) << endl;
    cout << "Median age for employed females = " <<
        ComputeMedianAge(begin(persons),
                partition(begin(persons), end(persons), [](const Person& p) {
                    return p.gender == Gender::FEMALE && p.is_employed;
                })) << endl;
    cout << "Median age for unemployed females = " <<
        ComputeMedianAge(begin(persons),
                partition(begin(persons), end(persons), [](const Person& p) {
                    return p.gender == Gender::FEMALE && !p.is_employed;
                })) << endl;
    cout << "Median age for employed males = " <<
        ComputeMedianAge(begin(persons),
                partition(begin(persons), end(persons), [](const Person& p) {
                    return p.gender == Gender::MALE && p.is_employed;
                })) << endl;
    cout << "Median age for unemployed males = " <<
         ComputeMedianAge(begin(persons),
                          partition(begin(persons), end(persons), [](const Person& p) {
                              return p.gender == Gender::MALE && !p.is_employed;
                          })) << endl;
}