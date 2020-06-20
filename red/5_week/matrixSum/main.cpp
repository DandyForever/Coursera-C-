#include "test_runner.h"
#include <vector>
#include <cstdint>
#include <future>

using namespace std;

#define THREAD_NUM 8

int64_t CalculateSingleThread (const vector<vector<int>>& matrix, int row, int num) {
    int64_t result = 0;
    for (int i = row; i < row + num; i++) {
        for (int j = 0; j < matrix.size(); j++) {
            result += matrix[i][j];
        }
    }
    return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    vector<future<int64_t>> futures;
    int number = matrix.size() / THREAD_NUM > 1ull ? matrix.size() / THREAD_NUM : 1ull;
    int curr_row = 0;
    while (curr_row < matrix.size()) {
        int current = number > matrix.size() - curr_row ? matrix.size() - curr_row : number;
        futures.push_back(async([&matrix, current, curr_row](){ return CalculateSingleThread(matrix, curr_row, current); }));
        curr_row += current;
    }
    int64_t result = 0;
    for (auto& item : futures) {
        result += item.get();
    }
    return result;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}