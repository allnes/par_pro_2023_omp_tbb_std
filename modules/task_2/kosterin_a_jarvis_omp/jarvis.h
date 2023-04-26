// Copyright 2023 Kosterin Alexey
#ifndef MODULES_TASK_1_KOSTERIN_A_JARVIS_OMP_JARVIS_H_
#define MODULES_TASK_1_KOSTERIN_A_JARVIS_OMP_JARVIS_H_
#include <omp.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

struct SPoint {
  int x = 0;
  int y = 0;
  explicit SPoint(int _x = 0, int _y = 0) {
    x = _x;
    y = _y;
  }
};

struct SVector {
  int x, y;

  explicit SVector(SPoint a, SPoint b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
};

int Cross(SVector a, SVector b);
std::vector<SPoint> CreateArray(int size);
void Swap(SPoint &arr1, SPoint &arr2);
std::vector<SPoint> DoJarvisSeq(std::vector<SPoint> arr, int size);
int Direction(const SPoint& cur, const SPoint& next, const SPoint& tmp);
bool checkDistance(const SPoint& cur, const SPoint& next, const SPoint& tmp);
bool ChekJarvis(std::vector<SPoint> jarArr);
std::vector<SPoint> ompJarvis(const std::vector<SPoint>& points);

#endif  // MODULES_TASK_1_KOSTERIN_A_JARVIS_OMP_JARVIS_H_
