// Copyright 2023 Makarov Danila
#ifndef MODULES_TASK_2_MAKAROV_D_SOBEL_OMP_SOBEL_H_
#define MODULES_TASK_2_MAKAROV_D_SOBEL_OMP_SOBEL_H_

#include <omp.h>
#include <vector>
#include <cmath>

using Matrix = std::vector<std::vector<int>>;

const Matrix Kernel_x = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
const Matrix Kernel_y = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

Matrix createMatrix(size_t width, size_t height, int val);
Matrix SobelSeq(const Matrix& input);
Matrix SobelOMP(const Matrix& input);
double clamp(double min, double max, double value);
void printMatrix(const Matrix& m);

#endif  // MODULES_TASK_2_MAKAROV_D_SOBEL_OMP_SOBEL_H_
