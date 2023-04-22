// Copyright 2023 Smirnov Andrew
#include "../../../modules/task_4/smirnov_a_gaussian_image_filter_std/gaussian_image_filter_std.h"

vector<intensityType> genImage(int rows, int columns) {
  std::random_device dev;
  std::mt19937 gen(dev());
  vector<intensityType> image(rows * columns);
  for (size_t i = 0; i < rows * columns; ++i) {
    image[i] = gen() % 256;
  }
  return image;
}

vector<intensityType> gaussianFilterSTDParallel(const vector<intensityType>& image,
  int rows, int columns, int countThreads) {
  if (image.size() != rows * columns)
    throw std::string("Error with values rows or columns");
  vector<intensityType> resultImage(rows * columns, 0.0);
  char radius = kernelSize / 2;
  int dataPerThread = rows / countThreads;
  int realCountThreads = dataPerThread > 0 ? countThreads : 1;
  vector<std::thread> threads(realCountThreads);
  int remainder = rows % countThreads;

  int startRow = 0;
  int endRow = dataPerThread + remainder;
  for (int iThread = 0; iThread < realCountThreads; ++iThread) {
    threads[iThread] = std::thread([&](int startRow, int endRow) {
        for (int i = startRow; i < endRow; ++i) {
          for (int j = 0; j < columns; ++j) {
            int curPixIntens = 0;
            char gausMatrixIndex = 0;
            for (int xKernel = -radius; xKernel <= radius; ++xKernel) {
              for (int yKernel = -radius; yKernel <= radius; ++yKernel) {
                int neighboorPixelX = std::max(0, std::min(i + xKernel, rows - 1));
                int neighboorPixelY = std::max(0, std::min(j + yKernel, columns - 1));
                curPixIntens += image[neighboorPixelX * columns + neighboorPixelY]
                  * kernel[gausMatrixIndex];
                gausMatrixIndex++;
              }
            }
            resultImage[i * columns + j] = curPixIntens / kernelSum;
          }
        }
      }, startRow, endRow);
    startRow = endRow;
    endRow = endRow + dataPerThread;
  }
  for (int iThread = 0; iThread < realCountThreads; ++iThread) {
    threads[iThread].join();
  }
  return resultImage;
}
