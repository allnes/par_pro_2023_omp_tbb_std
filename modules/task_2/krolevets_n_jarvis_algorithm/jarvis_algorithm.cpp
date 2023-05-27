// Copyright 2023 me
#include "../../../modules/task_2/krolevets_n_jarvis_algorithm/jarvis_algorithm.h"

point_orientation orientation(Point p, Point q, Point r) {
  int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (val == 0) return point_orientation::colliniar;
  return (val > 0) ? point_orientation::clockwise
                   : point_orientation::counterclockwsise;
}

double dist2(Point a, Point b) {
  int dx = b.x - a.x;
  int dy = b.y - a.y;
  return dx * dx + dy * dy;
}

std::vector<Point> get_convex_hull_omp(const std::vector<Point>& points) {
  int n = points.size();
  if (n < 3)
    return std::vector<Point>();
  else if (n == 3)
    return std::vector<Point>(points);

  std::set<Point> hull;

  int start = 0;
  for (int i = 1; i < n; i++) {
    if (points[i] < points[start]) {
      start = i;
    }
  }
  int current = start;
  int next;
  std::vector<int> to_push_by_each_thread;
#pragma omp parallel shared(start, next, current, n)
  {
    while (true) {
#pragma omp single
      { next = (current + 1) % n; }
      int private_next = next;
      bool was_used = false;
#pragma omp for
      for (int i = 0; i < n; ++i) {
        if (orientation(points[current], points[private_next], points[i]) ==
            point_orientation::counterclockwsise) {
          private_next = i;
          was_used = true;
        }
      }
#pragma omp critical
      {
        if (was_used) {
          to_push_by_each_thread.push_back(private_next);
        }
      }
#pragma omp barrier
#pragma omp single
      {
        for (int i = 0; i < to_push_by_each_thread.size(); ++i) {
          if (orientation(points[current], points[next],
                          points[to_push_by_each_thread[i]]) ==
                  point_orientation::counterclockwsise ||
              orientation(points[current], points[next],
                          points[to_push_by_each_thread[i]]) ==
                      point_orientation::colliniar &&
                  dist2(points[current], points[next]) <
                      dist2(points[current],
                            points[to_push_by_each_thread[i]])) {
            next = to_push_by_each_thread[i];
          }
        }
        to_push_by_each_thread.clear();
        for (int i = 0; i < n; i++) {
          if (orientation(points[current], points[next], points[i]) ==
              point_orientation::colliniar) {
            hull.insert(points[i]);
          }
        }
        current = next;
      }
      if (next == start) {
        break;
      }
#pragma omp barrier
    }
  }
  return std::vector<Point>(hull.begin(), hull.end());
}

std::vector<Point> get_convex_hull(const std::vector<Point>& points) {
  int n = points.size();
  if (n < 3)
    return std::vector<Point>();
  else if (n == 3)
    return std::vector<Point>(points);

  std::set<Point> hull;

  int start = 0;
  for (int i = 1; i < n; i++) {
    if (points[i] < points[start]) {
      start = i;
    }
  }

  int to_push = start;
  int next;
  while (true) {
    next = (to_push + 1) % n;
    for (int i = 0; i < n; i++) {
      if (orientation(points[to_push], points[next], points[i]) ==
              point_orientation::counterclockwsise ||
          orientation(points[to_push], points[next], points[i]) ==
                  point_orientation::colliniar &&
              dist2(points[to_push], points[next]) <
                  dist2(points[to_push], points[i])) {
        next = i;
      }
    }
    for (int i = 0; i < n; i++) {
      if (orientation(points[to_push], points[next], points[i]) ==
          point_orientation::colliniar) {
        hull.insert(points[i]);
      }
    }
    to_push = next;
    if (start == next) {
      break;
    }
  }

  return std::vector<Point>(hull.begin(), hull.end());
}
