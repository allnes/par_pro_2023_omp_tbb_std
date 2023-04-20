// Copyright 2023 Raschetnov Alexei

#ifndef MODULES_TASK_3_RASCHETNOV_A_CCS_DOUBLE_MATRIX_CCS_DOUBLE_MATRIX_H_
#define MODULES_TASK_3_RASCHETNOV_A_CCS_DOUBLE_MATRIX_CCS_DOUBLE_MATRIX_H_

#include <vector>
#include <iostream>
#include <cmath>

class SparseMatrix {
    int row;
    int col;
    std::vector<double> values;
    std::vector<int> rows;
    std::vector<int> pointer;
 public:
    SparseMatrix(int row_ = 1, int col_ = 1, const std::vector<double>& values_ = std::vector<double>(),
                 const std::vector<int>& rows_ = std::vector<int>(),
                 const std::vector<int>& pointer_ = std::vector<int>()): row(row_),
                 col(col_), values(values_), rows(rows_),
                 pointer(pointer_) {}
    SparseMatrix& transpose();
    void print();
    SparseMatrix multiply(const SparseMatrix& matrix);
    bool operator==(const SparseMatrix& matrix) const;
    bool is_empty();
};

// std::vector<double> sort_vec(std::vector<std::pair<int, double>>& vec);

#endif  // MODULES_TASK_3_RASCHETNOV_A_CCS_DOUBLE_MATRIX_CCS_DOUBLE_MATRIX_H_
