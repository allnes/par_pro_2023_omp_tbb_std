// Copyright 2023 Popov Andrey
#include "../../../modules/task_3/popov_fox_tbb/popov_fox_tbb.h"

#include <gtest/internal/gtest-port.h>
#include <omp.h>
#include <tbb/task_arena.h>
#include <tbb/tbb.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

Matrix OneMult(const Matrix& X, const Matrix& Y) {
  if (X[0].size() != Y.size()) throw "Different size";
  int n = X.size();
  int m = Y[0].size();
  Matrix C(n, std::vector<double>(n, 0));
  int size = Y.size();
  for (int k = 0; k < n; k++) {
    for (int l = 0; l < m; l++) {
      for (int z = 0; z < size; z++) {
        C[k][l] += X[k][z] * Y[z][l];
      }
    }
  }
  return C;
}

bool square(const Matrix& X) {
  if (X.size() != X[0].size()) return false;
  return true;
}

bool isMultiply(const Matrix& X, const Matrix& Y) {
  if (X[0].size() != Y.size()) return false;
  return true;
}

Matrix foxMultiply(const Matrix& X, const Matrix& Y) {
  if (!square(X) || !square(Y)) throw("Matrix isn't square");
  if (!isMultiply(X, Y)) throw("Incorrect size of matrix");

  tbb::task_arena init;
  auto numThreads = init.automatic;

  int n = X.size();
  int q = std::sqrt(numThreads);
  int block;
  int nOld = n;
  Matrix X2 = X;
  Matrix Y2 = Y;

  while (n % q != 0) {
    X2.push_back(std::vector<double>(n, 0));
    Y2.push_back(std::vector<double>(n, 0));
    n++;
  }
  for (int k = 0; k < n; ++k) {
    for (int l = 0; l < n - nOld; ++l) {
      X2[k].push_back(0);
      Y2[k].push_back(0);
    }
  }

  Matrix res(n, std::vector<double>(n));
  block = n / q;

  tbb::parallel_for(
      tbb::blocked_range2d<size_t>(0, n, block, 0, n, block),
      [&](const tbb::blocked_range2d<size_t>& r) {
        int i_thread = r.rows().begin() / block;
        int j_thread = r.cols().begin() / block;
        int h1 = i_thread * block;
        int h2 = j_thread * block;

        Matrix blockX(block), blockY(block);
        Matrix blockZ(block, std::vector<double>(block, 0));

        for (int z = 0; z < q; ++z) {
          int s = ((i_thread + z) % q) * block;
          for (int k = 0; k < block; ++k) {
            blockX[k] = std::vector<double>(X2[h1 + k].begin() + s,
                                            X2[h1 + k].begin() + s + block);
            blockY[k] = std::vector<double>(Y2[s + k].begin() + h2,
                                            Y2[s + k].begin() + (h2 + block));
          }
          for (int k = 0; k < block; k++) {
            for (int l = 0; l < block; l++) {
              for (int z = 0; z < block; z++)
                blockZ[k][l] += blockX[k][z] * blockY[z][l];
            }
          }
        }

        for (int k = 0; k < block; k++) {
          for (int l = 0; l < block; l++) {
            res[k + h1][l + h2] = blockZ[k][l];
          }
        }
      });

  if (nOld != n) {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n),
                      [&](const tbb::blocked_range<size_t>& r) {
                        for (auto l = r.begin(); l < r.end(); l++) {
                          res[l].resize(nOld);
                        }
                      });
  }
  res.resize(nOld);
  return res;
}

Matrix randM(const int& size) {
  if (size <= 0) {
    throw "Incorrect size of matrix";
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
