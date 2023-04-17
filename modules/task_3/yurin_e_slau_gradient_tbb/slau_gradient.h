// Copyright 2023 Yurin Evgeny

#ifndef MODULES_TASK_3_YURIN_E_SLAU_GRADIENT_TBB_SLAU_GRADIENT_H_
#define MODULES_TASK_3_YURIN_E_SLAU_GRADIENT_TBB_SLAU_GRADIENT_H_

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <random>

const double EPS = 1.0e-6;

using dvec = std::vector<double>;
using dmat = std::vector<dvec>;

dmat generateMatrix(int size, unsigned int seed);

dvec generateVector(int size, unsigned int seed);

double scalarProduct(const dvec &a, const dvec &b);

dvec matrix_vec(const dmat &a, const dvec &b);

dvec vec_vec_comb(double firstScalar, const dvec& firstVector, double secondScalar, const dvec& secondVector);

dvec solve(const dmat &matrix, const dvec& vector);

dvec matrix_vec_parallel(const dmat &a, const dvec &b);

dvec solve_parallel(const dmat &matrix, const dvec& vector);

#endif  // MODULES_TASK_3_YURIN_E_SLAU_GRADIENT_TBB_SLAU_GRADIENT_H_
