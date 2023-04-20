// Copyright 2023 Elistratov Vladimir
#ifndef MODULES_TASK_3_ELISTRATOV_V_JARVIS_PASSAGE_TBB_JARVIS_PASSAGE_TBB_H_
#define MODULES_TASK_3_ELISTRATOV_V_JARVIS_PASSAGE_TBB_JARVIS_PASSAGE_TBB_H_

#include <tbb/tbb.h>

#include <utility>
#include <vector>

using Point = std::pair<int, int>;

std::vector<Point> getRandomCombinationPoints(int size);
Point searchStartPoint(const std::vector<Point>& points);
int getDir(const Point& cur, const Point& next, const Point& tmp);
bool checkDistance(const Point& cur, const Point& next, const Point& tmp);
std::vector<Point> sequentinalJarvis(const std::vector<Point>& points);
std::vector<Point> tbbJarvis(const std::vector<Point>& points);

#endif  // MODULES_TASK_3_ELISTRATOV_V_JARVIS_PASSAGE_TBB_JARVIS_PASSAGE_TBB_H_
