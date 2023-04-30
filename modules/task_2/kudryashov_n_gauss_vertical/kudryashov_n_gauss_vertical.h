  // Copyright 2023 Kudryashov Nikita
#pragma once
#define _USE_MATH_DEFINES
#include<omp.h>
#include <vector>
#include <ctime>
#include<cmath>

int clamp(int value, int min, int max);
std::vector<std::vector<double>> createKernel();
int calcNewPixelColor(std::vector<std::vector<int>> image, int height,
  int width, int y, int x, std::vector<std::vector<double>> kernel);
std::vector<std::vector<int>> gauss_filter_sequence(
  const std::vector<std::vector<int>>& image, int height, int width);
std::vector<std::vector<int>> gauss_filter_parallel(
    const std::vector<std::vector<int>>& image, int height, int width);
