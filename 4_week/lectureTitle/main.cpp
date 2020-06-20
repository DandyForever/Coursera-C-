#include <iostream>

using namespace std;

struct Specialization {
    string value;
    explicit Specialization(const string & val) {
        value = val;
    }
};

struct Course {
    string value;
    explicit Course(const string & val) {
        value = val;
    }
};

struct Week {
    string value;
    explicit Week(const string & val) {
        value = val;
    }
};


struct LectureTitle {
    string specialization;
    string course;
    string week;
    LectureTitle(const Specialization& specialization1, const Course& course1, const Week& week1){
        specialization = specialization1.value;
        course = course1.value;
        week = week1.value;
    }
};
