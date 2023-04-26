// Copyright 2023 Kryuchkov Vladimir
#include "../../../modules/task_2/kryuchkov_v_fox_algorithm_omp/fox_algorithm.h"

#include <omp.h>

#include <algorithm>
#include <cmath>
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

std::vector<std::vector<double>> FoxParallel(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B, const unsigned& thread) {
  if (A.size() != B.size()) {
    throw "Different size";
  }
  if (A.size() <= 0 || B.size() <= 0) {
    throw "Size of matrix must be > 0";
  }

  size_t n = A.size();
  size_t q = std::sqrt(thread);
  size_t BlockSize = n / q;

  auto A1 = A;
  auto B1 = B;

  auto nold = n;
  while (n % q != 0) {
    A1.push_back(std::vector<double>(n, 0));
    B1.push_back(std::vector<double>(n, 0));
    std::for_each(A1.begin(), A1.end(),
                  [](std::vector<double>& a) { a.push_back(0); });
    std::for_each(B1.begin(), B1.end(),
                  [](std::vector<double>& a) { a.push_back(0); });
    n++;
    BlockSize = n / q;
  }

  std::vector<std::vector<double>> C(n, std::vector<double>(n));
#pragma omp parallel num_threads(q* q)
  {
    std::vector<std::vector<double>> A(BlockSize);
    std::vector<std::vector<double>> B(BlockSize);

    std::vector<std::vector<double>> tmp(BlockSize,
                                         std::vector<double>(BlockSize, 0));
    for (size_t s = 0; s < q; s++) {
      for (size_t k = 0; k < BlockSize; k++) {
        A[k] = std::vector<double>(
            A1[omp_get_thread_num() / q * BlockSize + k].begin() +
                ((omp_get_thread_num() / q + s) % q * BlockSize),
            A1[omp_get_thread_num() / q * BlockSize + k].begin() +
                ((omp_get_thread_num() / q + s) % q * BlockSize + BlockSize));
        B[k] = std::vector<double>(
            B1[(omp_get_thread_num() / q + s) % q * BlockSize + k].begin() +
                (omp_get_thread_num() % q * BlockSize),
            B1[(omp_get_thread_num() / q + s) % q * BlockSize + k].begin() +
                (omp_get_thread_num() % q * BlockSize + BlockSize));
      }
      for (size_t i = 0; i < BlockSize; i++) {
        for (size_t j = 0; j < BlockSize; j++) {
          for (size_t l = 0; l < BlockSize; l++) tmp[i][j] += A[i][l] * B[l][j];
        }
      }
    }

    for (size_t i = 0; i < BlockSize; ++i) {
      for (size_t j = 0; j < BlockSize; ++j) {
        C[i + omp_get_thread_num() / q * BlockSize]
         [j + omp_get_thread_num() % q * BlockSize] = tmp[i][j];
      }
    }
  }

  if (n != nold) {
#pragma omp parallel for
    for (int i = 0; i < static_cast<int>(nold); i++) {
      C[i].resize(nold);
    }
  }
  C.resize(nold);
  return C;
}
