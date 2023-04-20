// Copyright 2023 Antonova Anastasya
#include "../../../modules/task_3/antonova_a_monte_carlo_tbb/monte_carlo_tbb.h"

#include <tbb/tbb.h>

#include <algorithm>
#include <ctime>
#include <functional>
#include <random>
#include <string>
#include <vector>

double seqMonteCarlo(double (*f)(const std::vector<double> &),
                     const std::vector<double> &a, const std::vector<double> &b,
                     int steps) {
  if (steps <= 0) throw "integral is negative";
  double res = 0.0;
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));

  int mult = a.size();
  double S = 1;
  for (int i = 0; i < mult; i++) S *= (b[i] - a[i]);

  std::vector<std::uniform_real_distribution<double>> r(mult);
  std::vector<double> r1(mult);
  for (int i = 0; i < mult; i++)
    r[i] = std::uniform_real_distribution<double>(a[i], b[i]);

  for (int i = 0; i < steps; ++i) {
    for (int j = 0; j < mult; ++j) r1[j] = r[j](gen);
    res += f(r1);
  }

  res *= S / steps;
  return res;
}

double tbbMonteCarlo(double (*f)(const std::vector<double> &),
                     const std::vector<double> &a, const std::vector<double> &b,
                     int steps) {
  if (steps <= 0) throw "integral is negative";
  double res = 0.0;
  int mult = a.size();
  std::vector<std::uniform_real_distribution<double>> r(mult);
  for (int i = 0; i < mult; i++)
    r[i] = std::uniform_real_distribution<double>(a[i], b[i]);

  res = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, steps), 0.0,
      [&](tbb::blocked_range<size_t> range, double running_total) {
        std::mt19937 gen;
        gen.seed(static_cast<unsigned int>(time(0)));
        std::vector<double> r1(mult);
        for (size_t i = range.begin(); i != range.end(); ++i) {
          for (int j = 0; j < mult; ++j) r1[j] = r[j](gen);
          running_total += f(r1);
        }

        return running_total;
      },
      std::plus<double>());

  double S = 1;
  for (int i = 0; i < mult; i++) S *= (b[i] - a[i]);
  res *= S / steps;

  return res;
}
