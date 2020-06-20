#include <map>
#include<string>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_name_[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_name_[year] = last_name;
    }
    string GetFullName(int year) {
        auto fNameIt = first_name_.lower_bound(year);
        auto lNameIt = last_name_.lower_bound(year);

        string firstName;
        if (!first_name_.empty() && fNameIt == end(first_name_))
            firstName = prev(fNameIt) -> second;
        else if (!first_name_.empty() && fNameIt -> first > year && fNameIt != begin(first_name_))
            firstName = prev(fNameIt) -> second;
        else if (!first_name_.empty() && fNameIt -> first == year)
            firstName = fNameIt -> second;

        string lastName;
        if (!last_name_.empty() && lNameIt == end(last_name_))
            lastName = prev(lNameIt) -> second;
        else if (!last_name_.empty() && lNameIt -> first > year && lNameIt != begin(last_name_))
            lastName = prev(lNameIt) -> second;
        else if (!last_name_.empty() && lNameIt -> first == year)
            lastName = lNameIt -> second;

        if (lastName.empty() && firstName.empty())
            return "Incognito";
        if (lastName.empty())
            return firstName + " with unknown last name";
        if (firstName.empty())
            return lastName + " with unknown first name";
        return firstName + " " + lastName;
    }
private:
    map <int, string> first_name_;
    map <int, string> last_name_;
};
