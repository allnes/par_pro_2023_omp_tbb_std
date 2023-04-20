// Copyright 2023 Anastasya Antonova
#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../../modules/task_2/antonova_a_monte_carlo_omp/monte_carlo_omp.h"

double test_func1(const std::vector<double>& x) { return 1; }

double test_func2(const std::vector<double>& x) { return x[0]; }

double test_func3(const std::vector<double>& x) { return x[0] + x[1]; }

double test_func4(const std::vector<double>& x) {
  double res = 0;
  res += cos(x[0] * x[1]) + sin(x[0] + x[1]) * 5 + x[0] - sqrt(abs(x[1]));
  return res;
}

TEST(MonteCarlo_test_omp, test_different_sized_borders) {
  std::vector<double> left;
  std::vector<double> right;
  const int thread_num = 4;
  ASSERT_ANY_THROW(MonteCarloOmp(test_func3, left, right, 1000, thread_num));
}

TEST(MonteCarlo_test_omp, test_empty_borders) {
  std::vector<double> left;
  std::vector<double> right;
  const int thread_num = 4;
  ASSERT_ANY_THROW(MonteCarloOmp(test_func3, left, right, 1000, thread_num));
}

TEST(MonteCarlo_test_omp, test_1) {
  std::vector<double> left = {0.0};
  std::vector<double> right = {5.0};
  const uint64_t steps = 10000;
  const int thread_num = 4;

  double res_omp = 0.0;
  ASSERT_NO_THROW(
      res_omp = MonteCarloOmp(test_func1, left, right, steps, thread_num));
  double res_seq = 0.0;
  ASSERT_NO_THROW(
      res_seq = MonteCarloSeq(test_func1, left, right, steps * thread_num));
  std::cout << res_omp << " " << res_seq << "\n";
  ASSERT_NEAR(res_omp, 5, 0.01);
}

TEST(MonteCarlo_test_omp, test_2) {
  std::vector<double> left = {0.0};
  std::vector<double> right = {2.0};
  const uint64_t steps = 1000;

  double res_omp = 0.0;
  ASSERT_NO_THROW(res_omp = MonteCarloOmp(test_func2, left, right, steps, 1));
  double res_seq = 0.0;
  ASSERT_NO_THROW(res_seq = MonteCarloSeq(test_func2, left, right, steps * 1));
  std::cout << res_omp << " " << res_seq << "\n";
}

TEST(MonteCarlo_test_omp, test_3) {
  std::vector<double> left = {0.0, 0.0};
  std::vector<double> right = {2.0, 2.0};
  const uint64_t steps = 10000;
  const int thread_num = 4;

  double res_omp = 0.0;
  ASSERT_NO_THROW(
      res_omp = MonteCarloOmp(test_func3, left, right, steps, thread_num));
  double res_seq = 0.0;
  ASSERT_NO_THROW(
      res_seq = MonteCarloSeq(test_func3, left, right, steps * thread_num));

  std::cout << res_omp << " " << res_seq << "\n";
}
