#include "sum_reverse_sort.h"

#include <algorithm>

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    string copy = s;
    reverse(begin(copy), end(copy));
    return copy;
}

void Sort(vector<int>& nums) {
    sort (begin(nums), end(nums));
}