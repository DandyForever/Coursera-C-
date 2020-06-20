#include <iostream>
#include <vector>
#include <algorithm>

using  namespace std;


class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
      Name record = {first_name, "", year};
      string nearFirst;
      for (auto & item : history) {
          if (item.year < year) {
              record.last = item.last;
              nearFirst = item.first;
          }
          if (item.year == year) {
              nearFirst = item.first;
              item.first = first_name;
              record.year = -1;
          }
          if (item.year > year && item.first == nearFirst) {
              item.first = first_name;
          }
      }
      if (record.year == -1)
          return;
      history.push_back(record);
      sort (begin(history), end(history), [](const Name& x, const Name& y) {
         return (x.year < y.year);
      });
      //printHistory();
  }
  void ChangeLastName(int year, const string& last_name) {
      string nearLast;
      Name record = {"", last_name, year};
      for (auto & item : history) {
          if (item.year < year) {
              record.first = item.first;
              nearLast = item.last;
          }
          if (item.year == year) {
              nearLast = item.last;
              item.last = last_name;
              record.year = -1;
          }
          if (item.year > year && item.last == nearLast) {
              item.last = last_name;
          }
      }
      if (record.year == -1)
          return;
      history.push_back(record);
      sort (begin (history), end(history), [](const Name& x, const Name& y) {
          return (x.year < y.year);
      });
      //printHistory();
  }
  string GetFullName(int year) {
    Name record = {"", "", -1};
    for (const auto& item : history) {
        if (item.year <= year) {
            //cout << item.year << ' ' << year << endl;
            record = item;
        }
    }
    if (record.first.empty() && record.last.empty())
        return "Incognito";
    else if (record.first.empty())
        return record.last + " with unknown first name";
    else if (record.last.empty())
        return record.first + " with unknown last name";
    else return record.first + " " + record.last;
  }
private:
    struct Name {
      string first;
      string last;
      int year;
    };
    vector <Name> history;
    void printHistory () {
        cout << "start_print_history" << endl;
        for (const auto& item : history) {
            cout << item.year << " " << item.first << " " << item.last << endl;
        }
        cout << "end_print_history" << endl;
    }
};
