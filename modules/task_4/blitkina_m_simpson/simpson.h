// Copyright 2023 Blitkina Maria
#ifndef MODULES_TASK_4_BLITKINA_M_SIMPSON_SIMPSON_H_
#define MODULES_TASK_4_BLITKINA_M_SIMPSON_SIMPSON_H_
#include <vector>
#include <functional>
#include <utility>

using std::size_t;

double calcIntegral(const std::vector<std::pair<double, double>>& scope,
        std::function<double(const std::vector<double>)> f,
        int accurancy = 200, size_t level = 0,
        std::vector<double> fix_var = {});

#endif  // MODULES_TASK_4_BLITKINA_M_SIMPSON_SIMPSON_H_
