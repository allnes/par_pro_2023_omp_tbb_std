// Copyright 2023 Khramov Egor
#ifndef MODULES_TASK_2_KHRAMOV_E_INTEGRAL_RECTANGLES_KHRAMOV_E_INTEGRAL_RECTANGLES_H_
#define MODULES_TASK_2_KHRAMOV_E_INTEGRAL_RECTANGLES_KHRAMOV_E_INTEGRAL_RECTANGLES_H_

#include <functional>

using IntegralFunction = std::function<double(double x, double y, double z)>;

double getRectangleValue(IntegralFunction f, double x, double y, double z, double* h);

double integrateSequential(IntegralFunction func, double a[3], double b[3], int n[3]);

double integrateParallel(IntegralFunction func, double a[3], double b[3], int n[3]);


#endif  // MODULES_TASK_2_KHRAMOV_E_INTEGRAL_RECTANGLES_KHRAMOV_E_INTEGRAL_RECTANGLES_H_
