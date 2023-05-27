// Copyright 2023 me
#ifndef MODULES_TASK_2_KROLEVETS_N_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_
#define MODULES_TASK_2_KROLEVETS_N_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_

#include <omp.h>

#include <algorithm>
#include <atomic>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <utility>
#include <vector>

enum class point_orientation { colliniar, clockwise, counterclockwsise };

struct Point {
  int x = 0;
  int y = 0;

  Point() = default;
  Point(int x, int y) : x(x), y(y) {}
  bool operator>(const Point& other) const {
    return std::make_pair(x, y) > std::make_pair(other.x, other.y);
  }
  bool operator<(const Point& other) const {
    return std::make_pair(x, y) < std::make_pair(other.x, other.y);
  }
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Point& other) const { return !(*this == other); }
};
point_orientation orientation(Point, Point, Point);
std::vector<Point> get_convex_hull(const std::vector<Point>&);
std::vector<Point> get_convex_hull_omp(const std::vector<Point>&);
double dist2(Point, Point);

#endif  // MODULES_TASK_2_KROLEVETS_N_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_"
