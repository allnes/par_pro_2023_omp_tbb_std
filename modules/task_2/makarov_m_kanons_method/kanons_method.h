// Copyright 2023 Makarov Mikhail
#ifndef MODULES_TASK_2_MAKAROV_M_KANONS_METHOD_KANONS_METHOD_H_
#define MODULES_TASK_2_MAKAROV_M_KANONS_METHOD_KANONS_METHOD_H_

#include <omp.h>
#include <vector>
#include <complex>
#include <iostream>
#include <cmath>
#include <utility>
#include <algorithm>
#include <numeric>
#include <random>
#include <stack>
#include <exception>

using Vector = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;

Matrix CreateRandomMatrix(const int n);
Matrix MultUsual(const Matrix &A, const Matrix &B);
Matrix MultBlock(const Matrix &A, const Matrix &B, const int &blockSize);
Matrix CannonAlg(const Matrix &A, const Matrix &B, const int &numThreads);
bool MatricesNear(const Matrix &A, const Matrix &B);
bool ValuesNear(const double &a, const double &b, const double &eps);

#endif  // MODULES_TASK_2_MAKAROV_M_KANONS_METHOD_KANONS_METHOD_H_
