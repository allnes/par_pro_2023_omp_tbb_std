// Copyright 2023 Nikolaev Alexander
#ifndef MODULES_TASK_2_NIKOLAEV_A_MULT_SPARSE_MATR_OMP_SPARSE_MATRIX_H_
#define MODULES_TASK_2_NIKOLAEV_A_MULT_SPARSE_MATR_OMP_SPARSE_MATRIX_H_

#include <omp.h>
#include <vector>
#include <complex>
#include <iostream>

typedef std::complex<double> Complex;

struct CCSMatrix {
    int sizeRow;
    int sizeCol;
    int countNZ;
    std::vector<Complex> value;
    std::vector<int> colIndex;
    std::vector<int> rowIndex;
};

void printMatrix(const std::vector<std::vector<Complex>>& Pmatrix);
CCSMatrix GetRandomMatrix(int SizeRow, int SizeCol, int nonZero);
CCSMatrix TransposeMatrix(const CCSMatrix& mtx);
CCSMatrix MatrixtoCCSMatrix(const std::vector<std::vector<Complex>> &matrix);
CCSMatrix GetMultiplicateSequential(const CCSMatrix& A, const CCSMatrix& B);
CCSMatrix GetMultiplicateParallel(const CCSMatrix& A, const CCSMatrix& B);

#endif  // MODULES_TASK_2_NIKOLAEV_A_MULT_SPARSE_MATR_OMP_SPARSE_MATRIX_H_
