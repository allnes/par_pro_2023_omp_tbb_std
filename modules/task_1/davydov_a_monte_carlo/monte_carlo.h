// Copyright 2023 Davydov Andrey
#ifndef MODULES_TASK_1_DAVYDOV_A_MONTE_CARLO_MONTE_CARLO_H_
#define MODULES_TASK_1_DAVYDOV_A_MONTE_CARLO_MONTE_CARLO_H_

#include <vector>

double funcSum(const std::vector<double>& arguments);
double funcSub(const std::vector<double>& arguments);
double funcMultiply(const std::vector<double>& arguments);

double sequentialMonteCarlo(
    double (&f)(const std::vector<double>&),
    std::vector<double> a,
    std::vector<double> b,
    int n
);

#endif  // MODULES_TASK_1_DAVYDOV_A_MONTE_CARLO_MONTE_CARLO_H_
