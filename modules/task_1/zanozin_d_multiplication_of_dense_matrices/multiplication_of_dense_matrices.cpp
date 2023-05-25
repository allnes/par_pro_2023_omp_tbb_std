// Copyright 2023 Zanozin Danila
#include "../../../modules/task_1/zanozin_d_multiplication_of_dense_matrices/multiplication_of_dense_matrices.h"

#include <omp.h>

#include <iostream>
#include <random>
#include <string>
#include <vector>

matrix RandomMat(const int n) {
  std::mt19937 generator;
  std::random_device device;
  generator.seed(device());
  std::uniform_real_distribution<double> distribution(0, 100);

  matrix res(n, std::vector<double>(n, 0));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) res[i][j] = distribution(generator);

  return res;
}

matrix NaiveMult(const matrix &A, const matrix &B) {
  if (A[0].size() != B.size())
    throw std::invalid_argument("Different values for col and row");

  size_t n = A[0].size();
  size_t m = A.size();
  size_t l = B[0].size();
  matrix res(m, std::vector<double>(l, 0));

  for (size_t i = 0; i < m; i++)
    for (size_t j = 0; j < l; j++)
      for (size_t k = 0; k < n; k++) res[i][j] += A[i][k] * B[k][j];

  return res;
}

bool IsNear(const double &a, const double &b) {
  return std::fabs(a - b) < 0.00001;
}

bool CompareMatrices(const matrix &A, const matrix &B) {
  if (A[0].size() != B[0].size() || A.size() != B.size()) return false;

  bool tmp = true;
  for (size_t i = 0; i < A.size(); i++) {
    if (tmp == false) break;
    for (size_t j = 0; j < A[0].size(); j++)
      if (!IsNear(A[i][j], B[i][j])) {
        tmp = false;
        break;
      }
  }

  return tmp;
}

matrix BlockMult(const matrix &A, const matrix &B, const int &blockSize) {
  if (A[0].size() != B.size())
    throw std::invalid_argument("Different values for col and row");
  int tmp = blockSize;
  if (tmp > static_cast<int>(A.size()))
    throw std::invalid_argument("Wrong blockSize");

  int n = A[0].size();
  int jjMin, kkMin;
  matrix res(n, std::vector<double>(n, 0));

  for (int jj = 0; jj < n; jj += blockSize) {
    jjMin = std::min(jj + blockSize, n);
    for (int kk = 0; kk < n; kk += blockSize) {
      kkMin = std::min(kk + blockSize, n);
      for (int i = 0; i < n; i++) {
        for (int k = kk; k < kkMin; k++) {
          for (int j = jj; j < jjMin; j++) {
            res[i][j] += A[i][k] * B[k][j];
          }
        }
      }
    }
  }

  return res;
}
