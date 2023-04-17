// Copyright 2023 Makarov Danila
#include <iomanip>
#include <iostream>

#include "../../../modules/task_1/makarov_d_sobel/sobel.h"

Matrix createMatrix(size_t width, size_t height, int value) {
  if (width <= 0 || height <= 0) throw("Size is not correct");

  Matrix result(width, std::vector<int>(height, value));
  return result;
}

Matrix SobelSeq(const Matrix& input) {
  if (input.size() <= 0 || input[0].size() <= 0) throw("Size is not correct");

  Matrix result = input;
  size_t width = input.size() - 1, height = input[0].size() - 1;

  for (size_t i = 1; i < width; i++) {
    for (size_t j = 1; j < height; j++) {
      double x = 0, y = 0;
      for (size_t w = 0; w < 3; w++) {
        for (size_t h = 0; h < 3; h++) {
          x += input[i + w - 1][j + h - 1] * Kernel_x[w][h];
          y += input[i + w - 1][j + h - 1] * Kernel_y[w][h];
        }
      }
      double k = sqrt(x * x + y * y);
      result[i][j] = clamp(0, 255, k);
    }
  }
  return result;
}

double clamp(double min, double max, double value) {
  double result;
  if (value > 255)
    result = 255;
  else if (value < 0)
    result = 0;
  else
    result = value;
  return result;
}

void printMatrix(const Matrix& matrix) {
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[i].size(); j++)
      std::cout << std::setw(4) << matrix[i][j];
    std::cout << std::endl;
  }
}
