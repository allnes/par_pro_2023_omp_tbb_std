// Copyright 2023 Pikin Ilya
#ifndef MODULES_TASK_1_PIKIN_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_
#define MODULES_TASK_1_PIKIN_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_

#include <set>
#include <ctime>
#include <vector>
#include <string>
#include <random>
#include <complex>
#include <iostream>

const double EPSILON = 0.00001;

class CRSMatrix {
 public:
  int n;
  int nz;

  std::vector<std::complex<double>> value;
  std::vector<int> column;
  std::vector<int> rowIndex;

  CRSMatrix() : n(0), nz(0) {}
  CRSMatrix(const CRSMatrix&) = default;
  explicit CRSMatrix(const std::vector<std::vector<std::complex<double>>>& M);
  CRSMatrix(int n, int nz, const std::vector<std::complex<double>>& v,
            const std::vector<int>& c, const std::vector<int>& rI);

  CRSMatrix& operator=(const CRSMatrix&) = default;
  bool operator==(const CRSMatrix& M) const;

  void printData();
  void printAsMatrix();
};

CRSMatrix getTransposed(const CRSMatrix& A);
CRSMatrix getProductSeq(const CRSMatrix& A, const CRSMatrix& B);
CRSMatrix getRandCRSMatrix(int n, int cntInRow);

#endif  // MODULES_TASK_1_PIKIN_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_
