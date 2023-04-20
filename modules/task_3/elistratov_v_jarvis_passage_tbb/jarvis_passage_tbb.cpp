// Copyright 2023 Elistratov Vladimir
#include "../../../modules/task_3/elistratov_v_jarvis_passage_tbb/jarvis_passage_tbb.h"

#include <random>

std::vector<Point> getRandomCombinationPoints(int size) {
  if (size <= 0) {
    throw -1;
  }
  std::random_device random;
  std::mt19937 generate(random());
  std::vector<Point> points(size);
  for (int i = 0; i < size; i++) {
    int x = generate() % 8000;
    int y = generate() % 8000;
    points[i] = Point(x, y);
  }
  return points;
}

Point searchStartPoint(const std::vector<Point>& points) {
  Point startPoint = points[0];
  for (size_t i = 1; i < points.size(); i++) {
    if (points[i] < startPoint) startPoint = points[i];
  }
  return startPoint;
}

int getDir(const Point& cur, const Point& next, const Point& tmp) {
  return (tmp.first - cur.first) * (next.second - cur.second) -
         (tmp.second - cur.second) * (next.first - cur.first);
}

bool checkDistance(const Point& cur, const Point& next, const Point& tmp) {
  int distNextCur = (next.first - cur.first) * (next.first - cur.first) +
                    (next.second - cur.second) * (next.second - cur.second);
  int distTmpCur = (tmp.first - cur.first) * (tmp.first - cur.first) +
                   (tmp.second - cur.second) * (tmp.second - cur.second);
  if (distNextCur < distTmpCur) {
    return true;
  }
  return false;
}

std::vector<Point> sequentinalJarvis(const std::vector<Point>& points) {
  size_t numberOfPoints = points.size();
  if (numberOfPoints == 0) {
    throw -1;
  }
  if (numberOfPoints < 2) {
    return points;
  }
  Point start = searchStartPoint(points);
  std::vector<Point> result;
  result.push_back(start);
  Point currentPoint = start;
  Point nextPoint;
  do {
    if (currentPoint == points[0]) {
      nextPoint = points[1];
    } else {
      nextPoint = points[0];
    }
    for (size_t i = 0; i < numberOfPoints; i++) {
      int direction = getDir(currentPoint, nextPoint, points[i]);
      if (direction > 0) {
        nextPoint = points[i];
      } else if (direction == 0) {
        if (checkDistance(currentPoint, nextPoint, points[i])) {
          nextPoint = points[i];
        }
      }
    }
    currentPoint = nextPoint;
    result.push_back(nextPoint);
  } while (currentPoint != start);
  result.pop_back();
  return result;
}

std::vector<Point> tbbJarvis(const std::vector<Point>& points) {
  int numberOfPoints = static_cast<int>(points.size());
  if (numberOfPoints == 0) {
    throw -1;
  }
  if (numberOfPoints < 2) {
    return points;
  }
  Point start = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(1, numberOfPoints), points[0],
      [&points](tbb::blocked_range<size_t>& r, Point localStart) -> Point {
        auto begin = r.begin(), end = r.end();
        for (auto i = begin; i != end; i++) {
          if (points[i] < localStart) localStart = points[i];
        }
        return localStart;
      },
      [](const Point& localStart, const Point& start) -> Point {
        return localStart < start ? localStart : start;
      });
  std::vector<Point> result;
  result.push_back(start);
  Point currentPoint = start;
  Point nextPoint;
  do {
    if (currentPoint == points[0]) {
      nextPoint = points[1];
    } else {
      nextPoint = points[0];
    }
    currentPoint = tbb::parallel_reduce(
        tbb::blocked_range<size_t>(0, numberOfPoints), nextPoint,
        [&currentPoint, &points](tbb::blocked_range<size_t>& r,
                                 Point localNext) -> Point {
          auto begin = r.begin(), end = r.end();
          for (auto i = begin; i != end; i++) {
            int direction = getDir(currentPoint, localNext, points[i]);
            if (direction > 0) {
              localNext = points[i];
            } else if (direction == 0) {
              if (checkDistance(currentPoint, localNext, points[i])) {
                localNext = points[i];
              }
            }
          }
          return localNext;
        },
        [&currentPoint](const Point& nextPoint,
                        const Point& localNext) -> Point {
          int direction = getDir(currentPoint, nextPoint, localNext);
          if (direction > 0) {
            return localNext;
          } else if (direction == 0) {
            if (checkDistance(currentPoint, nextPoint, localNext)) {
              return localNext;
            }
          }
          return nextPoint;
        });
    nextPoint = currentPoint;
    result.push_back(nextPoint);
  } while (currentPoint != start);
  result.pop_back();
  return result;
}
