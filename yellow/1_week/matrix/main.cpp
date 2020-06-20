#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;


class Matrix {
public:
    Matrix () {
        rows = 0;
        cols = 0;
    }
    Matrix (int num_rows, int num_cols) {
        if (num_cols < 0 || num_rows < 0)
            throw out_of_range("");
        rows = num_rows;
        cols = num_cols;
        if (rows == 0 || cols == 0)
            rows = cols = 0;
        for (int i = 0; i < num_rows; i++) {
            vector <int> item(num_cols);
            data.push_back(item);
        }
    }

    void Reset (int num_rows, int num_cols) {
        if (num_cols < 0 || num_rows < 0)
            throw out_of_range("");
        data.erase(begin (data), end(data));
        rows = num_rows;
        cols = num_cols;
        if (rows == 0 || cols == 0)
            rows = cols = 0;
        for (int i = 0; i < rows; i++) {
            vector <int> item(cols);
            data.push_back(item);
        }
    }

    int At (int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range ("");
        }
        return data[row][col];
    }

    int& At (int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range ("");
        }
        return data[row][col];
    }

    int GetNumRows () const {
        return rows;
    }

    int GetNumColumns () const {
        return cols;
    }

private:
    int rows;
    int cols;
    vector <vector <int>> data;
};

istream& operator>> (istream& input, Matrix& matrix) {
    int rows = 0, cols = 0;
    input >> rows >> cols;
    Matrix tmp(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int cur = 0;
            input >> cur;
            tmp.At(i, j) = cur;
        }
    }
    matrix = tmp;
    return input;
}

ostream& operator<< (ostream& output, const Matrix& matrix) {
    output << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (int i = 0; i < matrix.GetNumRows(); i++) {
        for (int j = 0; j < matrix.GetNumColumns(); j++) {
            output << matrix.At(i, j) << " ";
        }
        output << endl;
    }
    return output;
}

bool operator== (const Matrix& lv, const Matrix& rv) {
    if (lv.GetNumColumns() != rv.GetNumColumns() || lv.GetNumRows() != rv.GetNumRows())
        return false;
    for (int i = 0; i < lv.GetNumRows(); i++) {
        for (int j = 0; j < lv.GetNumColumns(); j++) {
            if (lv.At(i, j) != rv.At(i, j))
                return false;
        }
    }
    return true;
}

Matrix operator+ (const Matrix& lv, const Matrix& rv) {
    if (lv.GetNumRows() != rv.GetNumRows()) {
        throw invalid_argument("Mismatched number of rows");
    }

    if (lv.GetNumColumns() != rv.GetNumColumns()) {
        throw invalid_argument("Mismatched number of columns");
    }

    Matrix tmp(lv.GetNumRows(), lv.GetNumColumns());

    for (int i = 0; i < lv.GetNumRows(); i++) {
        for (int j = 0; j < rv.GetNumColumns(); j++) {
            tmp.At(i, j) = lv.At(i, j) + rv.At(i, j);
        }
    }

    return tmp;
}