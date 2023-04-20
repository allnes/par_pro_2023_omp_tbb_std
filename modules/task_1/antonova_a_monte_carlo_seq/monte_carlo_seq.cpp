// Copyright 2023 Anastasya Antonova

#include "../../../modules/task_1/antonova_a_monte_carlo_seq/monte_carlo_seq.h"

#include <iostream>

double MonteCarloSeq(double (*func)(const std::vector<double>&),
                     const std::vector<double>& left,
                     const std::vector<double>& right, uint64_t steps,
                     int seed) {
  // CHECK DIMENSIONS
  if (left.size() != right.size())
    throw "Different sizes of left and right borders";
  if (left.empty()) throw "Empty borders";

  double res = 0.0;
  size_t dimension = left.size();

  std::mt19937 gen;
  gen.seed(seed);
  std::vector<std::uniform_real_distribution<double>> realdistr(dimension);
  for (size_t i = 0; i < dimension; i++)
    realdistr[i] = std::uniform_real_distribution<double>(left[i], right[i]);

  std::vector<double> pnt(dimension);
  for (uint64_t i = 0; i < steps; ++i) {
    for (size_t k = 0; k < dimension; ++k) {
      pnt[k] = realdistr[k](gen);
    }
    res += func(pnt);
  }
  double S = 1;
  for (size_t k = 0; k < dimension; ++k) {
    S *= right[k] - left[k];
  }
  res = S * res / steps;
  return res;
}
