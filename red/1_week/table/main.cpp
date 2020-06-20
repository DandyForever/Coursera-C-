#include "../../../tools/test_runner.h"

using namespace std;

template <typename T>
class Table {
public:
    Table(size_t rows, size_t cols): rows_(rows), cols_(cols) {
        data_ = makeMatrix(rows, cols);
    }

    vector<T> operator[](int i) const {
        return data_[i];
    }
    vector<T>& operator[](int i) {
        return data_[i];
    }

    pair<size_t, size_t> Size () const {
        return make_pair(rows_, cols_);
    }

    void Resize (size_t rows, size_t cols) {
        auto temp = makeMatrix(rows, cols);
        for (int i = 0; i < std::min(rows_, rows); i++) {
            for (int j = 0; j < std::min(cols_, cols); j++) {
                temp[i][j] = data_[i][j];
            }
        }
        data_ = temp;
        rows_ = rows;
        cols_ = cols;
    }

private:
    size_t rows_;
    size_t cols_;
    vector<vector<T>> data_;

    vector<vector<T>> makeMatrix (size_t rows, size_t cols) {
        vector<vector<T>> temp(rows);
        for (int i = 0; i < rows; i++) {
            vector<T> coltemp(cols);
            temp[i] = coltemp;
        }
        return temp;
    }
};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
    t[2][3] = 50;
    ASSERT_EQUAL(t[2][3], 50);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}