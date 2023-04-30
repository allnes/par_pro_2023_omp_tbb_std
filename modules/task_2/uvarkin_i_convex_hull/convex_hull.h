// Copyright 2023 Ilya Uvarkin
#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <string>

class Vector {
 public:
  int x, y;

  explicit Vector(int _x = 0, int _y = 0);
  Vector operator+(Vector const &vector) const;
  Vector operator-(Vector const &vector) const;

  friend std::ostream &operator<<(std::ostream &out, const Vector &vector);
  friend bool operator==(const Vector &vector1, const Vector &vector2);
};

int crossProduct(const Vector &a, const Vector &b);

class convex_hull {
 public:
  std::vector<Vector> getMinConvexHull(const std::vector<Vector> &points);
  Vector getFirstPoint(const std::vector<Vector> &points);
  std::vector<Vector> sortPointByPolarAngle(std::vector<Vector> points, Vector firstPoint);
  std::vector<Vector> deletePointNotIncludeToMCH(const std::vector<Vector> &points);
};

class Converter {
 public:
  std::vector<Vector> convertMatrixToSTDVector(std::vector<std::vector<int>> matrix, int width, int height);
  std::vector<std::vector<int>> convertSTDVectorToMatrix(const std::vector<Vector> &vector, int width, int height);
  std::string convertVectorToString(const std::vector<Vector> &vector);
};
