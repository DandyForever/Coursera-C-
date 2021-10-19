#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

class Database {
public:
  bool Put(const Record& record) {
      auto [it, is_inserted] = data_.insert(
              {record.id, Data {record, {}, {}, {}}}
      );
      if (!is_inserted) {
          return false;
      }
      auto& data = it->second;
      const Record *ptr = &data.record_;
      data.timestamp_it_ = timestamp_info_.insert({record.timestamp, ptr});
      data.karma_it_ = karma_info_.insert({record.karma, ptr});
      data.user_it_ = user_info_.insert({record.user, ptr});
      return true;
  }
  const Record* GetById(const string& id) const {
      if (!data_.count(id))
          return nullptr;
      return &data_.at(id).record_;
  }

  bool Erase(const string& id) {
      if (!data_.count(id))
          return false;
      const auto& data = data_[id];
      timestamp_info_.erase(data.timestamp_it_);
      karma_info_.erase(data.karma_it_);
      user_info_.erase(data.user_it_);
      data_.erase(id);
      return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const {
      auto first = timestamp_info_.lower_bound(low);
      auto last = timestamp_info_.upper_bound(high);
      for (auto it = first; it != last; it++)
          if (!callback(*it->second))
              return;
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const {
      auto first = karma_info_.lower_bound(low);
      auto last = karma_info_.upper_bound(high);
      for (auto it = first; it != last; it++)
          if (!callback(*it->second))
              return;
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const {
      auto first = user_info_.lower_bound(user);
      auto last = user_info_.upper_bound(user);
      for (auto it = first; it != last; it++)
          if (!callback(*it->second))
              return;
  }

private:
  struct Data {
    Record record_;
    multimap<int, const Record*>::iterator timestamp_it_;
    multimap<int, const Record*>::iterator karma_it_;
    multimap<string, const Record*>::iterator user_it_;
  };
    unordered_map<string, Data> data_;
    multimap<int, const Record*> timestamp_info_;
    multimap<int, const Record*> karma_info_;
    multimap<string, const Record*> user_info_;
};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}