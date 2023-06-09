// Copyright 2023 Bochkarev Vladimir

#ifndef MODULES_TASK_4_BOCHKAREV_V_INTEGRAL_TR_INTEGRAL_H_
#define MODULES_TASK_4_BOCHKAREV_V_INTEGRAL_TR_INTEGRAL_H_

#include <functional>
#include <iostream>
#include "../../../3rdparty/unapproved/unapproved.h"

double integral3D(double a, double b, double c, double d, double e,
double f, int n, const std::function<double(double, double, double)> &fun);
void calc(double a, double c, double e,
const double hx, const double hy, const double hz,
int n, int begin, int end, std::promise<double> &&pr,
const std::function<double(double, double, double)> &fun);
double calc_seq(double a, double c, double e,
const double hx, const double hy, const double hz,
int n, int begin, int end,
const std::function<double(double, double, double)> &fun);

#endif  // MODULES_TASK_4_BOCHKAREV_V_INTEGRAL_TR_INTEGRAL_H_
