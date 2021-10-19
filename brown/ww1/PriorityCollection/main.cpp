#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = int;

  Id Add(T object){
      Id obj_id = id_++;
      data_[obj_id] = {move(object), 0};
      priority_[0].insert(obj_id);
      return obj_id;
  }

  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){
      for (auto it = range_begin; it != range_end; it++){
          Id cur_id = id_++;
          data_[cur_id] = {move(*it), 0};
          priority_[0].insert(cur_id);
          *ids_begin = cur_id;
          ids_begin++;
      }
  }

  bool IsValid(Id id) const{
      return data_.count(id);
  }

  const T& Get(Id id) const{
      return data_.at(id).first;
  }

  void Promote(Id id){
      int& priority = data_[id].second;
      priority_[priority].erase(id);
      if (priority_[priority].empty())
          priority_.erase(priority);
      priority++;
      priority_[priority].insert(id);
  }

  pair<const T&, int> GetMax() const{
      auto id_max = *(priority_.rbegin()->second.rbegin());
      return data_.at(id_max);
  }

  pair<T, int> PopMax(){
      auto id_max = *(priority_.rbegin()->second.rbegin());
      auto data = move(data_[id_max]);
      int priority = data.second;
      priority_[priority].erase(id_max);
      if (priority_[priority].empty())
          priority_.erase(priority);
      data_.erase(id_max);
      return data;
  }

private:
  map<Id, pair<T, int>> data_;
  map<int, set<Id>> priority_;

  int id_ = 0;
};


class StringNonCopyable : public string {
public:
  using string::string;  // РџРѕР·РІРѕР»СЏРµС‚ РёСЃРїРѕР»СЊР·РѕРІР°С‚СЊ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂС‹ СЃС‚СЂРѕРєРё
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto& item = strings.GetMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}