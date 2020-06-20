#include <string>
#include <list>
#include "../../../tools/test_runner.h"
using namespace std;

class Editor {
public:
    Editor():
    cursor_(state_.end())
    {}
    void Left() {
        if (cursor_ != state_.begin())
            cursor_ = prev(cursor_);
    }
    void Right() {
        if (cursor_ != state_.end())
            cursor_ = next(cursor_);
    }
    void Insert(char token) {
        state_.insert(cursor_, token);
    }
    void Cut(size_t tokens = 1) {
        if (!buffer_.empty())
            buffer_.erase(begin(buffer_));
        auto cursor_copy_ = next(cursor_, min(tokens, static_cast<size_t>(distance(cursor_, state_.end()))));
        buffer_.splice(buffer_.begin(), state_, cursor_,
                cursor_copy_);
        cursor_ = cursor_copy_;
    }
    void Copy(size_t tokens = 1) {
        if (!buffer_.empty())
            buffer_.erase(begin(buffer_));

        auto item = cursor_;
        int num = 0;
        while (num != tokens && item != state_.end()) {
            buffer_.push_back(*item);
            num++;
            item = next(item);
        }
    }
    void Paste() {
        auto item = buffer_.begin();
        while (item != buffer_.end()) {
            Insert(*item);
            item = next(item);
        }
    }
    string GetText() const {
        ostringstream ss;
        auto item = begin(state_);
        while (item != end(state_)) {
            ss << *item;
            item = next(item);
        }
        return ss.str();
    }

    string GetBuffer() const {
        ostringstream ss;
        auto item = begin(buffer_);
        while (item != end(buffer_)) {
            ss << *item;
            item = next(item);
        }
        return ss.str();
    }

    char GetCursor() const { return cursor_ != state_.end() ? *cursor_ : *prev(cursor_); }

private:
    list<char> state_;
    list<char> buffer_;
    list<char>::iterator cursor_;
};

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestCopy () {
    Editor editor;
    TypeText(editor, "abcd");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Copy(4);
    editor.Right();
    editor.Right();
    editor.Right();
    editor.Right();
    editor.Paste();
    editor.Paste();
    editor.Paste();
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcdabcdabcdabcdabcd")
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCopy);
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}