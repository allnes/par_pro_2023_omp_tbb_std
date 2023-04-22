// Copyright 2023 Smirnov Andrew
#include "../../../modules/task_3/smirnov_a_gaussian_image_filter_tbb/gaussian_image_filter_tbb.h"
#include "tbb/tbb.h"

vector<intensityType> genImage(int rows, int columns) {
  std::random_device dev;
  std::mt19937 gen(dev());
  vector<intensityType> image(rows * columns);
  for (size_t i = 0; i < rows * columns; ++i) {
    image[i] = gen() % 256;
  }
  return image;
}

vector<intensityType> gaussianFilterTBBParallel(const vector<intensityType>& image, int rows, int columns) {
  if (image.size() != rows * columns)
    throw std::string("Error with values rows or columns");
  vector<intensityType> resultImage(rows * columns, 0);
  char radius = kernelSize / 2;
  tbb::parallel_for(tbb::blocked_range<int>(0, rows), [&](const tbb::blocked_range<int>& r) {
    for (int i = r.begin(); i < r.end(); ++i) {
      for (int j = 0; j < columns; ++j) {
        int curPixIntens = 0;
        char gausMatrixIndex = 0;
        for (int xKernel = -radius; xKernel <= radius; ++xKernel) {
          for (int yKernel = -radius; yKernel <= radius; ++yKernel) {
            int neighboorPixelX = max(0, min(i + xKernel, rows - 1));
            int neighboorPixelY = max(0, min(j + yKernel, columns - 1));
            curPixIntens += image[neighboorPixelX * columns + neighboorPixelY]
              * kernel[gausMatrixIndex];
            gausMatrixIndex++;
          }
        }
        resultImage[i * columns + j] = curPixIntens / kernelSum;
      }
    }
  });

  return resultImage;
}
