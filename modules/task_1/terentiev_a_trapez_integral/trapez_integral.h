// Copyright 2023 Terentiev Alexander
#ifndef MODULES_TASK_1_TERENTIEV_A_TRAPEZ_INTEGRAL_TRAPEZ_INTEGRAL_H_
#define MODULES_TASK_1_TERENTIEV_A_TRAPEZ_INTEGRAL_TRAPEZ_INTEGRAL_H_

#include <cmath>
#include <iostream>


const double MaxError = 0.01;
const double Steps = 100;

double Func1(double x, double y, double z);

double Func2(double x, double y, double z);

bool Testing(double fromX, double fromY, double fromZ, double toX, double toY,
             double toZ, double (*integrateFunc)(double, double, double),
             double trueRes);

bool Compare(double a, double b);

double TrapezIntegral3D(double fromX, double fromY, double fromZ, double toX,
                        double toY, double toZ, int steps,
                        double (*func)(double, double, double));

#endif  // MODULES_TASK_1_TERENTIEV_A_TRAPEZ_INTEGRAL_TRAPEZ_INTEGRAL_H_
