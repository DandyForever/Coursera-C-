#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
//    pair<RandomIt, RandomIt> ans(range_begin, range_end);
//    for (int i = 0; i < prefix.size(); i++) {
//        ans = equal_range(ans.first, ans.second, string{prefix[i]}, [i](const typename RandomIt::value_type& el1,
//                const typename RandomIt::value_type& el2) {
//            return el1[i] < el2[i];
//        });
//    }
//    return ans;
    return equal_range(range_begin, range_end, prefix, [prefix](const typename RandomIt::value_type& el1,
            const typename RandomIt::value_type& el2) {
        string s1;
        for (int i = 0; i < min(prefix.size(), el1.size()); i++)
            s1.push_back(el1[i]);
        string s2;
        for (int i = 0; i < min(prefix.size(), el2.size()); i++)
            s2.push_back(el2[i]);
        return s1 < s2;
    });
}