#include "../../../tools/test_runner.h"
#include <string_view>
#include <vector>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        string_view src = string_view(*data_forward_.insert(string(source)).first);
        string_view tgt = string_view(*data_backward_.insert(string(target)).first);
        forward_[src] = tgt;
        backward_[tgt] = src;
    }
    string_view TranslateForward(string_view source) const {
        auto temp_it = data_forward_.find(string(source));
        if (temp_it == end(data_forward_) || !forward_.count(*temp_it)) return "";
        return forward_.at(*temp_it);
    }
    string_view TranslateBackward(string_view target) const {
        auto temp_it = data_backward_.find(string(target));
        if (temp_it == end(data_backward_) || !backward_.count(*temp_it)) return "";
        return backward_.at(*temp_it);
    }

private:
    set<string> data_forward_;
    set<string> data_backward_;
    map<string_view, string_view> forward_;
    map<string_view, string_view> backward_;
};

void TestSimple() {
    Translator translator;
    {
        string okno = "okno";
        translator.Add(okno, string("dick"));
        translator.Add(okno, string("window"));
        translator.Add(string("stol"), string("table"));
//        translator.Add(string("huy"), string("huy"));
//        translator.Add(string("huy1"), string("huy"));

    }
//    ASSERT_EQUAL(translator.TranslateForward("huy"), string("huy"));
    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("dick"), "okno");
    ASSERT_EQUAL(translator.TranslateForward("dick"), "");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateForward("stol"), "table");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}