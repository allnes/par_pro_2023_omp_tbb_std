// Copyright 2023 Tarasova Anastasiya
#ifndef MODULES_TASK_2_TARASOVA_A_INTEGRAL_RECTANGLE_INTEGRAL_OMP_H_
#define MODULES_TASK_2_TARASOVA_A_INTEGRAL_RECTANGLE_INTEGRAL_OMP_H_

#include <vector>

double getParallel(const double& a1, const double& a2, const double& a3,
const double& b1, const double& b2, const double& b3, const double& h, double (*f)(double, double, double));
double getSequential(const double& a1, const double& a2, const double& a3,
const double& b1, const double& b2, const double& b3, const double& h, double (*f)(double, double, double));

#endif  // MODULES_TASK_2_TARASOVA_A_INTEGRAL_RECTANGLE_INTEGRAL_OMP_H_
