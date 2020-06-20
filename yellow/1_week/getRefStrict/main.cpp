#include <iostream>
#include <map>

using namespace std;

template <typename K, typename V>
V& GetRefStrict (map <K, V>& m, K key) {
    if (!m.count(key))
        throw runtime_error("");
    return m.at(key);
}
