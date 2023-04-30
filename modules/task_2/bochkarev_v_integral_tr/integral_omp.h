// Copyright 2023 Bochkarev Vladimir

#ifndef MODULES_TASK_2_BOCHKAREV_V_INTEGRAL_TR_INTEGRAL_OMP_H_
#define MODULES_TASK_2_BOCHKAREV_V_INTEGRAL_TR_INTEGRAL_OMP_H_

#include <omp.h>
#include <functional>
#include <iostream>

double integral3D(double a, double b, double c, double d, double e,
double f, int n, const std::function<double(double, double, double)> &fun);

#endif  // MODULES_TASK_2_BOCHKAREV_V_INTEGRAL_TR_INTEGRAL_OMP_H_
