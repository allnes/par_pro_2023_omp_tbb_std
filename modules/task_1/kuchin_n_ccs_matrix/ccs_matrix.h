// Copyright 2023 Kuchin Nikita
#ifndef MODULES_TASK_1_KUCHIN_N_CCS_MATRIX_CCS_MATRIX_H_
#define MODULES_TASK_1_KUCHIN_N_CCS_MATRIX_CCS_MATRIX_H_

#include <vector>
struct SparceMatrix {
    int n;
    std::vector<double> data;
    std::vector<int> row_id;
    std::vector<int> col_ptr;
};

SparceMatrix transport(SparceMatrix A);
SparceMatrix multiply(SparceMatrix A, SparceMatrix B);
#endif  // MODULES_TASK_1_KUCHIN_N_CCS_MATRIX_CCS_MATRIX_H_
