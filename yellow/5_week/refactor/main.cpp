#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    explicit Person (const string& name, const string& type):
        Name (name),
        Type (type)
    {}

    virtual void Walk (const string& destination) const {
        cout << Type << ": " << Name << " walks to: " << destination << endl;
    }

    string GetName () const {
        return Name;
    }

    string GetType () const {
        return Type;
    }

protected:
    string Name;
    const string Type;
};

class Student: public Person{
public:

    explicit Student(const string& name, const string& favouriteSong) :
        Person(name, "Student"),
        FavouriteSong(favouriteSong)
    {}

    void Learn() const {
        cout << Person::Type << ": " << Name << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << Person::Type << ": " << Name << " sings a song: " << FavouriteSong << endl;
    }

private:
    string FavouriteSong;
};


class Teacher: public Person {
public:
    explicit Teacher(const string& name, const string& subject):
        Person(name, "Teacher"),
        Subject(subject)
    {}

    void Teach() const {
        cout << Person::Type << ": " << Name << " teaches: " << Subject << endl;
    }

private:
    string Subject;
};


class Policeman: public Person {
public:
    explicit Policeman(const string& name):
        Person (name, "Policeman")
    {}

    void Check (const Person& p) {
        cout << Person::Type << ": " << Name << " checks " << p.GetType() << ". " <<
        p.GetType() << "\'s name is: " << p.GetName() << endl;
    }
};

void VisitPlaces (const Person& p, const vector<string>& places) {
    for (const auto& place : places) {
        p.Walk(place);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
