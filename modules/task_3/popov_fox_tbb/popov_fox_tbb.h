// Copyright 2023 Popov Andrey
#ifndef MODULES_TASK_3_POPOV_FOX_TBB_POPOV_FOX_TBB_H_
#define MODULES_TASK_3_POPOV_FOX_TBB_POPOV_FOX_TBB_H_

#include <math.h>

#include <vector>
using Matrix = std::vector<std::vector<double>>;

bool square(const Matrix& X);
bool isMultiply(const Matrix& X, const Matrix& Y);
Matrix OneMult(const Matrix& X, const Matrix& Y);
Matrix foxMultiply(const Matrix& X, const Matrix& Y);
Matrix randM(const int& num);

#endif  // MODULES_TASK_3_POPOV_FOX_TBB_POPOV_FOX_TBB_H_
