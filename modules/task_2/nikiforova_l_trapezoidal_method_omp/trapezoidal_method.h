// Copyright 2023 Nikiforova Lada
#ifndef MODULES_TASK_2_NIKIFOROVA_L_TRAPEZOIDAL_METHOD_OMP_TRAPEZOIDAL_METHOD_H_
#define MODULES_TASK_2_NIKIFOROVA_L_TRAPEZOIDAL_METHOD_OMP_TRAPEZOIDAL_METHOD_H_

#include <vector>
#include <utility>

double trapezoidalMethod(double (*function)(std::vector<double>),
                std::vector<std::pair<double, double>> boundaries,
                int partition);

#endif  // MODULES_TASK_2_NIKIFOROVA_L_TRAPEZOIDAL_METHOD_OMP_TRAPEZOIDAL_METHOD_H_
