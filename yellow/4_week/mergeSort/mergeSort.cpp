#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//template <typename RandomIt>
//void MergeSort(RandomIt range_begin, RandomIt range_end) {
//    if (range_end - range_begin < 2)
//        return;
//
//    vector<typename RandomIt::value_type> elements(range_begin, range_end);
//
//    MergeSort(begin(elements), begin(elements) + elements.size() / 2);
//    MergeSort(begin(elements) + elements.size() / 2, end(elements));
//
//    merge(begin(elements), begin(elements) + elements.size() / 2,
//          begin(elements) + elements.size() / 2, end(elements), range_begin);
//}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2)
        return;

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    MergeSort(begin(elements), begin(elements) + elements.size() / 3);
    MergeSort(begin(elements) + elements.size() / 3, end(elements) - elements.size() / 3);
    MergeSort(end(elements) - elements.size() / 3, end(elements));

    vector<typename RandomIt::value_type> tmp;

    merge(begin(elements), begin(elements) + elements.size() / 3,
          begin(elements) + elements.size() / 3, end(elements) - elements.size() / 3, back_inserter(tmp));
    merge(begin(tmp), end(tmp),
          end(elements) - elements.size() / 3, end(elements), range_begin);
}