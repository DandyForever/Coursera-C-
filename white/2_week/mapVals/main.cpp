set<string> BuildMapValuesSet(const map<int, string>& m) {
    set <string> p;
    for (auto v : m) {
        p.insert (v.second);
    }
    return p;
}