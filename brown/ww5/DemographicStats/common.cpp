void PrintStats(vector<Person> persons) {
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    auto it = partition(persons.begin(), persons.end(), [](Person& p) { return p.gender == Gender::FEMALE; });
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), it) << endl;
    cout << "Median age for males = " << ComputeMedianAge(it, persons.end()) << endl;
    auto it_female = partition(persons.begin(), it, [](Person& p) { return p.is_employed; });
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), it_female) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(it_female, it) << endl;
    auto it_male = partition(it, persons.end(), [](Person& p) { return p.is_employed; });
    cout << "Median age for employed males = " << ComputeMedianAge(it, it_male) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(it_male, persons.end()) << endl;
}
