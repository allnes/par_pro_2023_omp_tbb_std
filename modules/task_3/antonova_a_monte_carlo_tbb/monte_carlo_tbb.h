// Copyright 2023 Antonova Anastasya
#ifndef MODULES_TASK_3_ANTONOVA_A_MONTE_CARLO_TBB_MONTE_CARLO_TBB_H_
#define MODULES_TASK_3_ANTONOVA_A_MONTE_CARLO_TBB_MONTE_CARLO_TBB_H_

#include <string>
#include <vector>

double seqMonteCarlo(double (*f)(const std::vector<double> &),
                     const std::vector<double> &a, const std::vector<double> &b,
                     int s);

double tbbMonteCarlo(double (*f)(const std::vector<double> &),
                     const std::vector<double> &a, const std::vector<double> &b,
                     int s);

#endif  // MODULES_TASK_3_ANTONOVA_A_MONTE_CARLO_TBB_MONTE_CARLO_TBB_H_
