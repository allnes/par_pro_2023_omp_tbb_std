// // Copyright 2023 Mukhin Vadim

#include "../../../modules/task_1/mukhin_v_focs_algoritm/focs_algoritm.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

std::vector<std::vector<double>> GetRandomMatrix(const int& size) {
  if (size <= 0) {
    throw "Wrong size matrix";
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1000.0);

  std::vector<std::vector<double>> res(size, std::vector<double>(size));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      res[i][j] = dis(gen);
    }
  }
  return res;
}

std::vector<std::vector<double>> SimpleMultiplication(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {
  if (A.size() != B.size()) {
    throw "Different size";
  }
  if (A.size() <= 0 || B.size() <= 0) {
    throw "Size of matrix must be > 0";
  }

  size_t n = A.size();
  size_t m = B[0].size();
  std::vector<std::vector<double>> C(n, std::vector<double>(n, 0));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      for (size_t k = 0; k < B.size(); ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return C;
}

std::vector<std::vector<double>> BlockMultiplication(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {
  if (A.size() != B.size()) {
    throw "Different size";
  }
  if (A.size() <= 0 || B.size() <= 0) {
    throw "Size of matrix must be > 0";
  }

  size_t n = A.size();
  size_t q = n / std::sqrt(n);
  size_t BlockSize = n / q;
  std::vector<std::vector<double>> C(n, std::vector<double>(n, 0));
  size_t EndA, EndB;
  for (size_t a = 0; a < n; a += BlockSize) {
    EndA = std::min(a + BlockSize, n);
    for (size_t b = 0; b < n; b += BlockSize) {
      EndB = std::min(b + BlockSize, n);
      for (size_t i = 0; i < n; i++) {
        for (size_t j = a; j < EndA; j++) {
          for (size_t k = b; k < EndB; k++) {
            C[i][j] += A[i][k] * B[k][j];
          }
        }
      }
    }
  }
  return C;
}

bool CompareMatrix(const std::vector<std::vector<double>>& A,
                   const std::vector<std::vector<double>>& B) {
  if (A.size() != B.size()) {
    throw "Different size";
  }
  if (A.size() <= 0 || B.size() <= 0) {
    throw "Size of matrix must be > 0";
  }

  bool eq = true;
  for (size_t i = 0; i < A.size(); i++) {
    for (size_t j = 0; j < A[0].size(); j++)
      if (std::fabs(A[i][j] - B[i][j]) >
          std::numeric_limits<double>::epsilon() * std::max(A[i][j], B[i][j]) *
              100)
        eq = false;
  }
  return eq;
}
