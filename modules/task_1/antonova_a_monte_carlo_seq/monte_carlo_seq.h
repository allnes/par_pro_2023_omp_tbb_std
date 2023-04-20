// Copyright 2023 Anastasya Antonova
#ifndef MODULES_TASK_1_ANTONOVA_A_MONTE_CARLO_SEQ_MONTE_CARLO_SEQ_H_
#define MODULES_TASK_1_ANTONOVA_A_MONTE_CARLO_SEQ_MONTE_CARLO_SEQ_H_
#include <random>
#include <vector>

double MonteCarloSeq(double (*func)(const std::vector<double>&),
                     const std::vector<double>& left,
                     const std::vector<double>& right, uint64_t steps,
                     int seed = 0);
#endif  // MODULES_TASK_1_ANTONOVA_A_MONTE_CARLO_SEQ_MONTE_CARLO_SEQ_H_
