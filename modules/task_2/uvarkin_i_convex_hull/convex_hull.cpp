// Copyright 2023 Ilya Uvarkin
#include "../../../modules/task_2/uvarkin_i_convex_hull/convex_hull.h"
#include <string>

std::vector<Vector> convex_hull::getMinConvexHull(const std::vector<Vector>& points) {
  auto firstPoint = getFirstPoint(points);
  auto sortPoints = sortPointByPolarAngle(points, firstPoint);
  auto hullPoint = deletePointNotIncludeToMCH(sortPoints);

  return hullPoint;
}

Vector convex_hull::getFirstPoint(const std::vector<Vector> &points) {
  if (points.empty()) {
    return Vector{-1, -1};
  }

  auto firstPoint = points[0];

  for (const auto &point : points) {
    if (point.x < firstPoint.x ||
        (point.x == firstPoint.x && point.y < firstPoint.y)) {
      firstPoint = point;
    }
  }

  return firstPoint;
}

std::vector<Vector> convex_hull::sortPointByPolarAngle(std::vector<Vector> points, Vector firstPoint) {
  std::sort(points.begin(), points.end(), [&](Vector a, Vector b) {
    return a == firstPoint || crossProduct(a - firstPoint, b - firstPoint) > 0;
  });

  return points;
}

std::vector<Vector> convex_hull::deletePointNotIncludeToMCH(const std::vector<Vector> &points) {
  std::vector<Vector> hull;

  for (const auto &point : points) {
    while (hull.size() >= 2) {
      Vector newVector = point - hull.back();
      Vector lastVector = hull.back() - hull[hull.size() - 2];

      if (crossProduct(newVector, lastVector) <= 0) {
        break;
      }

      hull.pop_back();
    }

    hull.push_back(point);
  }

  return hull;
}

std::vector<Vector> Converter::convertMatrixToSTDVector(std::vector<std::vector<int>> matrix, int width, int height) {
  std::vector<Vector> res;
  res.reserve(width * height);

  #pragma omp parallel for default(none) shared(res, matrix, width, height)
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      auto elem = matrix[i][j];

      if (elem != 0) {
        #pragma omp critical
        res.emplace_back(j, height - 1 - i);
      }
    }
  }



  return res;
}

std::vector<std::vector<int>> Converter::convertSTDVectorToMatrix(const std::vector<Vector> &vector,
                                                                  int width, int height) {
  std::vector<std::vector<int>> res;

  res.resize(height);
  for (auto &item : res) {
    item.resize(width);
  }

#pragma omp parallel for default(none) shared(res, vector)
  for (int i = 0; i < vector.size(); ++i) {
    res[vector[i].y][vector[i].x] = 1;
  }

  return res;
}

std::string Converter::convertVectorToString(const std::vector<Vector> &vectors) {
  std::stringstream ss;
  for (auto it = vectors.begin(); it != vectors.end(); it++) {
    if (it != vectors.begin() && it != vectors.end()) {
      ss << ", ";
    }
    ss << *it;
  }

  return ss.str();
}

Vector::Vector(int _x, int _y) {
  x = _x;
  y = _y;
}

int crossProduct(Vector const &a, Vector const &b) {
  return a.x * b.y - b.x * a.y;
}

Vector Vector::operator+(const Vector &vector) const {
  return Vector(x + vector.x, y + vector.y);
}

Vector Vector::operator-(const Vector &vector) const {
  return Vector(x - vector.x, y - vector.y);
}

std::ostream &operator<<(std::ostream &out, const Vector &vector) {
  out << "(" << vector.x << ", " << vector.y << ")";

  return out;
}

bool operator==(const Vector &vector1, const Vector &vector2) {
  return vector1.x == vector2.x && vector1.y == vector2.y;
}

