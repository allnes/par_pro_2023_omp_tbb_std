//Copyright 2023 Popov Nikita
#ifndef MODULES_TASK_1_POPOV_N_ALG_OF_JARVIS_ALG_OF_JARVIS_H_
#define MODULES_TASK_1_POPOV_N_ALG_OF_JARVIS_ALG_OF_JARVIS_H_

#include <algorithm>
#include <atomic>
#include <cassert>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

struct Point {
  int x = 0;
  int y = 0;

  Point() = default;
  Point(int x, int y) : x(x), y(y) {}
  bool operator>(const Point& second) const {
    return std::make_pair(y, x) > std::make_pair(second.y, second.x);
  }
  bool operator<(const Point& second) const {
    return std::make_pair(y, x) < std::make_pair(second.y, second.x);
  }
  bool operator==(const Point& second) const {
    return y == second.y && x == second.x;
  }
  bool operator!=(const Point& second) const {
    return !(*this == second); }
};
int check_orientation(Point i, Point j, Point k);
std::vector<Point> get_convex_body(const std::vector<Point>& p_arr);

#endif  //MODULES_TASK_1_POPOV_N_ALG_OF_JARVIS_ALG_OF_JARVIS_H_
