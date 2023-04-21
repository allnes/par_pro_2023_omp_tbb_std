// Copyright 2023 Popov Andrey
#ifndef MODULES_TASK_2_POPOV_FOX_OMP2_POPOV_FOX_OMP2_H_
#define MODULES_TASK_2_POPOV_FOX_OMP2_POPOV_FOX_OMP2_H_

#include <string>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

bool Square(const Matrix& X);
bool isMultiplied(const Matrix& X, const Matrix& Y);
Matrix Multipli(const Matrix& X, const Matrix& Y);
Matrix MultiplyFox(const Matrix& X, const Matrix& Y, const int& numThreads);
Matrix randM(const int& size);

#endif  //  MODULES_TASK_2_POPOV_FOX_OMP2_POPOV_FOX_OMP2_H_
