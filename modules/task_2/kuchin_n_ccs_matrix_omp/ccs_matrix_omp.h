// Copyright 2023 Kuchin Nikita
#ifndef MODULES_TASK_2_KUCHIN_N_CCS_MATRIX_OMP_CCS_MATRIX_OMP_H_
#define MODULES_TASK_2_KUCHIN_N_CCS_MATRIX_OMP_CCS_MATRIX_OMP_H_

#include <vector>
struct SparceMatrix {
    int n;
    std::vector<double> data;
    std::vector<int> row_id;
    std::vector<int> col_ptr;
};

SparceMatrix transport(SparceMatrix A);
SparceMatrix multiply(SparceMatrix A, SparceMatrix B);
SparceMatrix parmultiply(SparceMatrix A, SparceMatrix B);
#endif  // MODULES_TASK_2_KUCHIN_N_CCS_MATRIX_OMP_CCS_MATRIX_OMP_H_
