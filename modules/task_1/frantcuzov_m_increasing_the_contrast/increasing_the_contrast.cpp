// Copyright 2023 Frantcuzov Maksim
#define _USE_MATH_DEFINES
#include <cmath>

#include "../../../modules/task_1/frantcuzov_m_increasing_the_contrast/increasing_the_contrast.h"

std::vector<float> getGaussKernel(int radius, float sigma) {
  int size = 2 * radius + 1;
  std::vector<float> res(size * size);
  float norm = 0;
  for (int x = -radius; x <= radius; x++)
    for (int y = -radius; y <= radius; y++) {
      int k = (x + radius) * size + (y + radius);
      res[k] = 1 / (2 * M_PI * sigma * sigma) *
               std::exp(-(x * x + y * y) / (2 * sigma * sigma));
      norm += res[k];
    }

  for (int i = 0; i < size * size; i++) {
    res[i] /= norm;
  }

  return res;
}

float calcNewPixColor(const int x, const int y, const int width,
                      const int height, const std::vector<float>& kernel,
                      int radius, const std::vector<float>& img) {
  float color = 0;

  for (int i = -radius; i <= radius; i++)
    for (int j = -radius; j <= radius; j++) {
      int k = (i + radius) * (2 * radius + 1) + j + radius;

      // check not in border
      if (x + j >= 0 && x + j < width && y + i >= 0 && y + i < height) {
        int m = (y + i) * width + x + j;
        color += img[m] * kernel[k];
      }

      // check color
    }

  if (color > 255) {
    color = 255;
  }
  return color;
}

std::vector<float> getSequentialOperations(const int width, const int height,
                                           const std::vector<float>& kernel,
                                           const std::vector<float>& img) {
  std::vector<float> res(width * height);
  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++) {
      int m = y * width + x;
      float color = calcNewPixColor(x, y, width, height, kernel, 1, img);
      res[m] = color;
    }

  return res;
}
