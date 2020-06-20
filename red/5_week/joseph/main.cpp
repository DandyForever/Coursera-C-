#include "../../../tools/test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std;

template <typename RandomIt>
void update (vector<typename RandomIt::value_type>& pool, set<int>& indexes) {
    vector<typename RandomIt::value_type> temp;
    for (int i = 0; i < pool.size(); i++) {
        if (!indexes.count (i))
            temp.push_back(move(pool[i]));
    }
//    pool = temp;
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    vector<typename RandomIt::value_type> pool;
    set<int> indexes;
    if (step_size == 1) return;
    for (size_t i = 0; i < last - first; i++) {
        pool.push_back(move(*(first + i)));
    }
    size_t cur_pos = 0;
    size_t pool_size = pool.size(), count = 0;
    while (pool_size) {
        *(first++) = move(pool[cur_pos]);
        count++;
        indexes.insert(cur_pos);
        if (cur_pos + step_size >= pool_size) {
            size_t curr = 0, curr_size = 0;
            while (curr_size < pool_size) {
                if (!indexes.count(curr_size))
                    pool[curr++] = move(pool[curr_size]);
                curr_size++;
            }
            indexes.clear();
            cur_pos -= pool_size;
            pool_size -= count;
            count = 0;
        }
//            update(pool, indexes);
        if (pool_size == 0) {
            break;
        }
        cur_pos = (cur_pos + step_size) % pool_size;
    }
}

vector<int> MakeTestVector() {
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}

struct NoncopyableInt {
    int value;
    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});

    ASSERT_EQUAL(numbers, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}