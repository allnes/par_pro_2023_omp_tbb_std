// Copyright 2023 Popov Andrey
#include <omp.h>

#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../../../modules/task_2/Popov_fox_omp2/Popov_fox_omp2.h"

Matrix Multipli(const Matrix& X, const Matrix& Y) {
  if (X[0].size() != Y.size()) throw "Incorrect size";
  int n = X.size();
  int m = Y[0].size();
  Matrix C(n, std::vector<double>(n, 0));
  int size = Y.size();
  for (int k = 0; k < n; k++) {
    for (int l = 0; l < m; l++) {
      for (int g = 0; g < size; g++) {
        C[k][l] += X[k][g] * Y[g][l];
      }
    }
  }
  return C;
}

bool Square(const Matrix& X) {
  if (X.size() != X[0].size()) return false;
  return true;
}

bool isMultiplied(const Matrix& X, const Matrix& Y) {
  if (X[0].size() != Y.size()) return false;
  return true;
}

Matrix MultiplyFox(const Matrix& X, const Matrix& Y, const int& numThreads) {
  if (!Square(X) || !Square(Y)) throw("Matrix isn't square");
  if (!isMultiplied(X, Y)) throw("Incorrect size of matrix");
  int n = X.size();
  int q = std::sqrt(numThreads);
  int blockSize = n / q;
  int nOld = n;
  Matrix X2 = X;
  Matrix Y2 = Y;

  while (n % q != 0) {
    X2.push_back(std::vector<double>(n, 0));
    Y2.push_back(std::vector<double>(n, 0));
    n++;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - nOld; ++j) {
      X2[i].push_back(0);
      Y2[i].push_back(0);
    }
  }

  Matrix res(n, std::vector<double>(n));
  blockSize = n / q;
#pragma omp parallel num_threads(q* q)
  {
    int i_thread = omp_get_thread_num() / q;
    int j_thread = omp_get_thread_num() % q;
    int h1 = i_thread * blockSize;
    int h2 = j_thread * blockSize;
    Matrix blockA(blockSize), blockB(blockSize);
    Matrix blockC(blockSize, std::vector<double>(blockSize, 0));

    for (int t = 0; t < q; ++t) {
      int s = ((i_thread + t) % q) * blockSize;
      for (int k = 0; k < blockSize; ++k) {
        blockA[k] = std::vector<double>(X2[h1 + k].begin() + s,
                                        X2[h1 + k].begin() + s + blockSize);
        blockB[k] = std::vector<double>(Y2[s + k].begin() + h2,
                                        Y2[s + k].begin() + (h2 + blockSize));
      }
      for (int k = 0; k < blockSize; k++) {
        for (int l = 0; l < blockSize; l++) {
          for (int g = 0; g < blockSize; g++)
            blockC[k][l] += blockA[k][g] * blockB[g][l];
        }
      }
    }

    for (int k = 0; k < blockSize; k++) {
      for (int l = 0; l < blockSize; l++) {
        res[k + h1][l + h2] = blockC[k][l];
      }
    }
    if (n != nOld) {
#pragma omp parallel for
      for (int k = 0; k < nOld; k++) {
        res[k].resize(nOld);
      }
    }
  }
  res.resize(nOld);
  return res;
}

Matrix randM(const int& size) {
  if (size <= 0) {
    throw "Wrong size matrix";
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1000.0);
  Matrix matr(size, std::vector<double>(size));
  for (int k = 0; k < size; k++) {
    for (int l = 0; l < size; l++) {
      matr[k][l] = dis(gen);
    }
  }
  return matr;
}
