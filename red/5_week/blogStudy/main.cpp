#include "../../../tools/test_runner.h"
#include "../../../tools/profile.h"

#include <map>
#include <string>
#include <future>
using namespace std;

#define THREAD_NUM 16

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
      for (auto& item : other.word_frequences) {
          word_frequences[item.first] += item.second;
      }
  }
};

vector<string> SplitIntoWordsView(const string& s) {
    string_view str = s;
    vector<string> result(20);
    while(true) { size_t space = str.find(' '); result.push_back(string(str.substr(0, space)));
        if (space == str.npos) { break; } else { str.remove_prefix(space + 1); }
    }
    return result;
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats result;
    for (auto& word : SplitIntoWordsView(line)) {
        if (key_words.count(word)) {
            result.word_frequences[word]++;
        }
    }
    return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  vector<future<Stats>> futures;
  vector<string> lines;
    for (string line; getline(input, line); ) {
      lines.push_back(move(line));
    }
    int number = lines.size() / THREAD_NUM > 1 ? lines.size() / THREAD_NUM : 1;
    int curr_line = 0;
    int current = 0;
    vector<stringstream> ss(THREAD_NUM + 1);
    for (auto& line : lines) {
        line.push_back('\n');
        ss[current] << line;
        curr_line++;
        if (curr_line == number) {
            futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(ss[current++])));
            curr_line = 0;
        }
    }
    if (curr_line) {
        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(ss[current])));
    }
    Stats result;
  for (auto& item : futures) {
      result += item.get();
  }
  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  vector<string> testing({
                            "this new yangle service really rocks\n",
                            "It sucks when yangle isn't available\n",
                            "10 reasons why yangle is the best IT company\n",
                            "yangle rocks others suck\n",
                            "Goondex really sucks, but yangle rocks. Use yangle\n"
                          });
  for (int i = 0; i < 1000000; i++) {
      for (auto& item : testing) {
          ss << item;
      }
  }

    {   LOG_DURATION("multythreading");
        const auto stats = ExploreKeyWords(key_words, ss);
        const map<string, int> expected = {
                {"yangle", 6000000},
                {"rocks", 2000000},
                {"sucks", 1000000}
        };
        ASSERT_EQUAL(stats.word_frequences, expected);
    }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}