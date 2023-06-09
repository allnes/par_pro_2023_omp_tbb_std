// Copyright 2023 Kryuchkov Vladimir

#ifndef MODULES_TASK_4_KRYUCHKOV_V_FOX_ALGORITHM_STD_FOX_ALGORITHM_H_

#define MODULES_TASK_4_KRYUCHKOV_V_FOX_ALGORITHM_STD_FOX_ALGORITHM_H_
#include <cmath>
#include <vector>

std::vector<std::vector<double>> GetRandomMatrix(const int& n);
std::vector<std::vector<double>> SimpleMultiplication(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B);
std::vector<std::vector<double>> BlockMultiplication(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B);

std::vector<std::vector<double>> FoxParallel(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B);

bool CompareMatrix(const std::vector<std::vector<double>>& A,
                   const std::vector<std::vector<double>>& B);

#endif  // MODULES_TASK_4_KRYUCHKOV_V_FOX_ALGORITHM_STD_FOX_ALGORITHM_H_
