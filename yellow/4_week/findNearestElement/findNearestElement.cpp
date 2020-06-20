#include <set>
#include <cmath>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    auto lb = numbers.lower_bound(border);
    if (lb == begin(numbers))
        return lb;
    if (lb == end(numbers))
        return prev(lb);
    auto ub = prev(lb);

    if (border - *ub <= *lb - border)
        return ub;
    else
        return lb;
}