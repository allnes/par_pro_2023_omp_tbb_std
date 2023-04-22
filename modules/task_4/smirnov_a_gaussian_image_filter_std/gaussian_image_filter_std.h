// Copyright 2023 Smirnov Andrew
#ifndef MODULES_TASK_4_SMIRNOV_A_GAUSSIAN_IMAGE_FILTER_STD_GAUSSIAN_IMAGE_FILTER_STD_H_
#define MODULES_TASK_4_SMIRNOV_A_GAUSSIAN_IMAGE_FILTER_STD_GAUSSIAN_IMAGE_FILTER_STD_H_

#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include "../../../3rdparty/unapproved/unapproved.h"

using std::vector;
using intensityType = unsigned char;

const vector<intensityType> kernel{ 1, 2, 1, 2, 4, 2, 1, 2, 1 };
const intensityType kernelSum = 16;
const intensityType kernelSize = 3;

vector<intensityType> genImage(int rows, int columns);
vector<intensityType> gaussianFilterSTDParallel(const vector<intensityType>& image,
  int rows, int columns, int countThreads);

#endif  // MODULES_TASK_4_SMIRNOV_A_GAUSSIAN_IMAGE_FILTER_STD_GAUSSIAN_IMAGE_FILTER_STD_H_
