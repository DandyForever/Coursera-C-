#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    return equal_range(range_begin, range_end, string{prefix}, [](const typename RandomIt::value_type& el1,
            const typename RandomIt::value_type& el2) {
        return el1[0] < el2[0];
    });
}