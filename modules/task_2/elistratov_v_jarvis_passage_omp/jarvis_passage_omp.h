// Copyright 2023 Elistratov Vladimir
#ifndef MODULES_TASK_2_ELISTRATOV_V_JARVIS_PASSAGE_OMP_JARVIS_PASSAGE_OMP_H_
#define MODULES_TASK_2_ELISTRATOV_V_JARVIS_PASSAGE_OMP_JARVIS_PASSAGE_OMP_H_

#include <omp.h>

#include <utility>
#include <vector>

using Point = std::pair<int, int>;

std::vector<Point> getRandomCombinationPoints(int size);
Point searchStartPoint(const std::vector<Point>& points);
int getDir(const Point& cur, const Point& next, const Point& tmp);
bool checkDistance(const Point& cur, const Point& next, const Point& tmp);
std::vector<Point> sequentinalJarvis(const std::vector<Point>& points);
std::vector<Point> openmpJarvis(const std::vector<Point>& points);

#endif  // MODULES_TASK_2_ELISTRATOV_V_JARVIS_PASSAGE_OMP_JARVIS_PASSAGE_OMP_H_
