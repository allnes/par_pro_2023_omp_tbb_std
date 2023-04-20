// Copyright 2023 Anastasya Antonova
#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../../modules/task_1/antonova_a_monte_carlo_seq/monte_carlo_seq.h"

double test_func1(const std::vector<double>& x) { return 1; }

double test_func2(const std::vector<double>& x) { return x[0]; }

double test_func3(const std::vector<double>& x) { return x[0] + x[1]; }

TEST(MonteCarlo_test_seq, test_different_sized_borders) {
  std::vector<double> left;
  std::vector<double> right;
  ASSERT_ANY_THROW(MonteCarloSeq(test_func3, left, right, 1000));
}

TEST(MonteCarlo_test_seq, test_empty_borders) {
  std::vector<double> left;
  std::vector<double> right;
  ASSERT_ANY_THROW(MonteCarloSeq(test_func3, left, right, 1000));
}

TEST(MonteCarlo_test_seq, test_1) {
  std::vector<double> left = {0.0};
  std::vector<double> right = {5.0};
  const uint64_t steps = 1000;

  double res = MonteCarloSeq(test_func1, left, right, steps);

  ASSERT_NEAR(res, 5, 0.1);
}

TEST(MonteCarlo_test_seq, test_2) {
  std::vector<double> left = {0.0};
  std::vector<double> right = {2.0};
  const uint64_t steps = 4000;

  double res = MonteCarloSeq(test_func2, left, right, steps);

  ASSERT_NEAR(res, 2, 0.1);
}

TEST(MonteCarlo_test_seq, test_3) {
  std::vector<double> left = {0.0, 0.0};
  std::vector<double> right = {2.0, 2.0};
  const uint64_t steps = 8000;

  double res = MonteCarloSeq(test_func3, left, right, steps);

  ASSERT_NEAR(res, 8.0, 0.1);
}
