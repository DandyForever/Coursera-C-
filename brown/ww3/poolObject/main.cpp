#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        auto temp = TryAllocate();
        if (temp == nullptr) {
            temp = new T;
            relevant_.insert(temp);
        }
        return temp;
    }
    T* TryAllocate() {
        if (!released_.empty()) {
            auto temp = released_.front();
            released_.pop();
            relevant_.insert(temp);
            return temp;
        }
        return nullptr;
    }

    void Deallocate(T* object) {
        if (relevant_.count(object)) {
            relevant_.erase(object);
            released_.push(object);
        } else
            throw invalid_argument("object is not relevant");
    }

    ~ObjectPool() {
        for (auto item : relevant_)
            delete item;
        while (!released_.empty()) {
            delete released_.front();
            released_.pop();
        }
    }

private:
    set<T*> relevant_;
    queue<T*> released_;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    try {
        pool.Deallocate(p1);
    } catch (invalid_argument ex) {

    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}