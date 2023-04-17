// Copyright 2023 Elistratov Vladimir
#include "../../../modules/task_1/elistratov_v_jarvis_passage/jarvis_passage.h"

int orientation(Point p, Point q, Point r) {
  int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (val == 0) return 0;    // Collinear
  return (val > 0) ? 1 : 2;  // Clockwise or Counterclockwise
}

std::vector<Point> get_convex_hull(const std::vector<Point>& points) {
  int n = points.size();
  if (n < 3) return std::vector<Point>();

  std::vector<Point> hull;

  int l = 0;
  for (int i = 1; i < n; i++) {
    if (points[i].x < points[l].x) {
      l = i;
    }
  }

  int p = l;
  int q;
  do {
    hull.push_back(points[p]);
    q = (p + 1) % n;
    for (int i = 0; i < n; i++) {
      if (orientation(points[p], points[i], points[q]) == 2) {
        q = i;
      }
    }

    p = q;
  } while (p != l);
  return hull;
}
