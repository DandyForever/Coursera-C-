#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T> T Sqr (T val);
template <typename T> vector<T> Sqr (const vector<T>& v);
template <typename Ft, typename Sd> pair<Ft, Sd> Sqr (const pair <Ft, Sd>& p);
template <typename K, typename V> map <K, V> Sqr (const map <K, V>& m);

template <typename T>
T Sqr (T val) {
    return (val * val);
}

template <typename T>
vector<T> Sqr (const vector<T>& v) {
    vector <T> tmp;
    for (const auto& item : v) {
        tmp.push_back(Sqr(item));
    }
    return tmp;
}

template <typename Ft, typename Sd>
pair<Ft, Sd> Sqr (const pair <Ft, Sd>& p) {
    return make_pair(Sqr(p.first), Sqr(p.second));
}

template <typename K, typename V>
map <K, V> Sqr (const map <K, V>& m) {
    map <K, V> tmp;
    for (const auto& item : m) {
        tmp[item.first] = Sqr(item.second);
    }
    return tmp;
}
