// Copyright 2023 Chernova Anna
#ifndef MODULES_TASK_3_CHERNOVA_A_CCS_MATRIX_MULT_CCS_MATRIX_MULT_H_
#define MODULES_TASK_3_CHERNOVA_A_CCS_MATRIX_MULT_CCS_MATRIX_MULT_H_

#include <complex>
#include <vector>

class MatrixCSS {
  size_t numberRows;
  size_t numberColumns;

  std::vector<std::complex<double>> values;
  std::vector<int> rows;
  std::vector<int> pointer;

  friend std::complex<double> columnMultiplication(const MatrixCSS& tLeft,
                                                   const MatrixCSS& right,
                                                   const size_t n,
                                                   const size_t m);

 public:
  MatrixCSS(size_t numberRows, size_t numberColumns);
  MatrixCSS(const std::vector<std::complex<double>>& v, size_t numberRows,
            size_t numberColumns);
  MatrixCSS(const MatrixCSS& oth);

  void transponse();

  friend const MatrixCSS operator*(const MatrixCSS& left,
                                   const MatrixCSS& right);
  friend bool operator==(const MatrixCSS& left, const MatrixCSS& right);

  friend const MatrixCSS parallelCCSMultiplication(const MatrixCSS& left,
                                                   const MatrixCSS& right);
};

std::vector<std::complex<double>> getRandomVector(size_t numberRows,
                                                  size_t numberColumns);

#endif  // MODULES_TASK_3_CHERNOVA_A_CCS_MATRIX_MULT_CCS_MATRIX_MULT_H_
