vector <string> PalindromFilter (vector <string> words, int minLength) {
    vector <string> filtered;
    for (auto word : words) {
        if (word.size() >= minLength){
            bool flag = true;
            for (int i = 0; i < word.size() / 2; i++) {
                if (word[i] != word[word.size() - i - 1]) flag = false;
            }
            if (flag) filtered.push_back(word);
        }
    }
    return filtered;
}