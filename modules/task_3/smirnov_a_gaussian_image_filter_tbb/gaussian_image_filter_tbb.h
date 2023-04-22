// Copyright 2023 Smirnov Andrew
#ifndef MODULES_TASK_3_SMIRNOV_A_GAUSSIAN_IMAGE_FILTER_TBB_GAUSSIAN_IMAGE_FILTER_TBB_H_
#define MODULES_TASK_3_SMIRNOV_A_GAUSSIAN_IMAGE_FILTER_TBB_GAUSSIAN_IMAGE_FILTER_TBB_H_

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <tbb/tbb.h>

using std::vector;
using intensityType = unsigned char;

const vector<intensityType> kernel{ 1, 2, 1, 2, 4, 2, 1, 2, 1 };
const intensityType kernelSum = 16;
const intensityType kernelSize = 3;

vector<intensityType> genImage(int rows, int columns);
vector<intensityType> gaussianFilterTBBParallel(const vector<intensityType>& image, int rows, int columns);

#endif  // MODULES_TASK_3_SMIRNOV_A_GAUSSIAN_IMAGE_FILTER_TBB_GAUSSIAN_IMAGE_FILTER_TBB_H_
