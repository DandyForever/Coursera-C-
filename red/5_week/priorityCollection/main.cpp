#include "../../../tools/test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <map>
#include <utility>
#include <vector>
#include <list>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = typename vector<T>::iterator;

    PriorityCollection(){
        data_.reserve(1e8);
    }

    Id Add(T object) {
        data_.push_back(move(object));
        priority_[0].insert(prev(data_.end()));
        mapping_[prev(data_.end())] = 0;
        return prev(data_.end());
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        size_t size = distance(range_begin, range_end);
        for (auto it = range_begin; it != range_end; it++)
            data_.push_back(move(*it));
        for (auto it = data_.end() - size; it != data_.end(); it++) {
            *ids_begin = it;
            ids_begin++;
            priority_[0].insert(it);
            mapping_[it] = 0;
        }
    }

    bool IsValid(Id id) const {
        return (id >= data_.begin()) && (id < data_.end()) && (!invalid_.count(id));
    }

    const T& Get(Id id) const {
        return *id;
    }

    void Promote(Id id) {
        int current_priority = mapping_[id];
        mapping_[id]++;
        priority_[current_priority].erase(id);
        if (priority_[current_priority].empty())
            priority_.erase(current_priority);
        priority_[++current_priority].insert(id);
        max_priority_ = current_priority > max_priority_ ? current_priority : max_priority_;
    }

    pair<const T&, int> GetMax() const {
        return {*(*prev(end(priority_.at(max_priority_)))), max_priority_};
    }

    pair<T, int> PopMax() {
        auto id = *prev(priority_[max_priority_].end());
        int mp = max_priority_;
        priority_[max_priority_].erase(id);
        invalid_.insert(id);
        if (priority_[max_priority_].empty()) {
            priority_.erase(max_priority_);
            if (max_priority_)
                max_priority_ = prev(priority_.end())->first;
        }
        return {move(*id), mp};
    }

private:
    vector<T> data_;
    map<int, set<Id>> priority_;
    map<Id, int> mapping_;
    set<Id> invalid_;
    int max_priority_ = 0;
};


class StringNonCopyable : public string {
public:
    using string::string;
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
        ASSERT(strings.IsValid(red_id));
        const auto jtem = strings.GetMax();
        ASSERT_EQUAL(jtem.first, "red");
        ASSERT_EQUAL(jtem.second, 2);
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);

        ASSERT(!strings.IsValid(red_id));
    }
    {
        ASSERT(strings.IsValid(yellow_id));
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
        ASSERT(!strings.IsValid(yellow_id));
    }
    {
        ASSERT(strings.IsValid(white_id));
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
        ASSERT(!strings.IsValid(white_id));
    }
}

void TestNoCopy2() {
    PriorityCollection<StringNonCopyable> strings;
    vector<StringNonCopyable> tested;
    tested.push_back("white");
    tested.push_back("yellow");
    tested.push_back("red");
    vector<vector<StringNonCopyable>::iterator> ids(3);
    strings.Add(make_move_iterator(begin(tested)), make_move_iterator(end(tested)), begin(ids));
    const auto white_id = ids[0];
    const auto yellow_id = ids[1];
    const auto red_id = ids[2];

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        ASSERT(strings.IsValid(red_id));
        const auto jtem = strings.GetMax();
        ASSERT_EQUAL(jtem.first, "red");
        ASSERT_EQUAL(jtem.second, 2);
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);

        ASSERT(!strings.IsValid(red_id));
    }
    {
        ASSERT(strings.IsValid(yellow_id));
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
        ASSERT(!strings.IsValid(yellow_id));
    }
    {
        ASSERT(strings.IsValid(white_id));
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
        ASSERT(!strings.IsValid(white_id));
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    RUN_TEST(tr, TestNoCopy2);

//    vector<int> test(3);
//    test[0] = 1;
//    test[1] = 2;
//    test[2] = 3;
//    set<vector<int>::iterator> its;
//    its.insert(begin(test));
//    its.insert(begin(test) + 1);
//    its.insert(begin(test) + 2);
//    for (auto item : its) {
//        cout << *item << " ";
//    }
    return 0;
}