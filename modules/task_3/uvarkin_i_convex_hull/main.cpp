// Copyright 2023 Ilya Uvarkin
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_3/uvarkin_i_convex_hull/convex_hull.h"

TEST(uvarkin_min_hull_convex, test1) {
  std::vector<std::vector<int>> matrix = {{1, 0, 1}, {0, 0, 1}, {0, 1, 0}};

  auto converter = Converter();
  auto pointsAct = converter.convertMatrixToSTDVector(matrix, 3, 3);

  std::vector<Vector> pointExp = {
      Vector{0, 2},
      Vector{2, 2},
      Vector{2, 1},
      Vector{1, 0},
  };

  std::sort(pointsAct.begin(), pointsAct.end(), [&](Vector a, Vector b) {
      return a.x > b.x || ( a.x == b.x && a.y > b.y);
  });

  std::sort(pointExp.begin(), pointExp.end(), [&](Vector a, Vector b) {
      return a.x > b.x || ( a.x == b.x && a.y > b.y);
  });

  ASSERT_EQ(converter.convertVectorToString(pointExp),
            converter.convertVectorToString(pointsAct));
}

TEST(uvarkin_min_hull_convex, test2) {
  std::vector<std::vector<int>> matrix = {{0, 0, 1}, {0, 0, 1}, {1, 1, 0}};

  auto converter = Converter();
  auto points = converter.convertMatrixToSTDVector(matrix, 3, 3);

  auto MinConvexHull = convex_hull();
  auto firstPointAct = MinConvexHull.getFirstPoint(points);

  Vector firstPointExp = Vector{0, 0};

  ASSERT_EQ(firstPointAct, firstPointExp);
}

TEST(uvarkin_min_hull_convex, test3) {
  std::vector<std::vector<int>> matrix = {{1, 0, 1}, {0, 0, 1}, {1, 1, 0}};

  auto converter = Converter();
  auto points = converter.convertMatrixToSTDVector(matrix, 3, 3);

  auto MinConvexHull = convex_hull();
  auto firstPoint = MinConvexHull.getFirstPoint(points);
  auto sortPointAct = MinConvexHull.sortPointByPolarAngle(points, firstPoint);

  std::vector<Vector> sortPointExp = {
      Vector{0, 0}, Vector{1, 0}, Vector{2, 1}, Vector{2, 2}, Vector{0, 2},
  };

  ASSERT_EQ(sortPointAct, sortPointExp);
}

TEST(uvarkin_min_hull_convex, test4) {
  std::vector<std::vector<int>> matrix = {
      {1, 0, 1, 0, 1},
      {0, 1, 1, 1, 1},
      {0, 1, 0, 1, 0},
      {0, 1, 1, 0, 0},
      {1, 1, 0, 0, 0},
  };

  auto converter = Converter();
  auto points = converter.convertMatrixToSTDVector(matrix, 5, 5);
  std::sort(points.begin(), points.end(), [&](Vector a, Vector b) {
      return a.x > b.x || ( a.x == b.x && a.y > b.y);
  });

  auto MinConvexHull = convex_hull();
  auto firstPoint = MinConvexHull.getFirstPoint(points);
  auto sortPoints = MinConvexHull.sortPointByPolarAngle(points, firstPoint);
  auto hullAct = MinConvexHull.deletePointNotIncludeToMCH(sortPoints);

  std::vector<std::vector<int>> matrixHull = {
      {1, 0, 1, 0, 1},
      {0, 0, 0, 0, 1},
      {0, 0, 0, 1, 0},
      {0, 0, 1, 0, 0},
      {1, 1, 0, 0, 0},
  };

  std::vector<Vector> hullPoints =
      converter.convertMatrixToSTDVector(matrixHull, 5, 5);
  auto hullExp = MinConvexHull.sortPointByPolarAngle(hullPoints, firstPoint);

  ASSERT_EQ(hullAct, hullExp);
}

TEST(uvarkin_min_hull_convex, test5) {
  std::vector<std::vector<int>> matrix = {
      {1, 1, 1, 0, 1},
      {0, 1, 1, 1, 1},
      {1, 1, 1, 1, 0},
      {0, 1, 1, 0, 0},
      {1, 1, 0, 0, 0},
  };

  auto converter = Converter();
  auto points = converter.convertMatrixToSTDVector(matrix, 5, 5);

  auto MinConvexHull = convex_hull();

  std::sort(points.begin(), points.end(), [&](Vector a, Vector b) {
      return a.x > b.x || ( a.x == b.x && a.y > b.y);
  });

  auto hullAct = MinConvexHull.getMinConvexHull(points);

  std::vector<std::vector<int>> matrixHull = {
      {1, 1, 1, 0, 1},
      {0, 0, 0, 0, 1},
      {1, 0, 0, 1, 0},
      {0, 0, 1, 0, 0},
      {1, 1, 0, 0, 0},
  };

  std::vector<Vector> hullPoints =
      converter.convertMatrixToSTDVector(matrixHull, 5, 5);

  auto hullExp = MinConvexHull.sortPointByPolarAngle(
      hullPoints, MinConvexHull.getFirstPoint(hullPoints));

  std::sort(hullAct.begin(), hullAct.end(), [&](Vector a, Vector b) {
      return a.x > b.x || ( a.x == b.x && a.y > b.y);
  });

  std::sort(hullExp.begin(), hullExp.end(), [&](Vector a, Vector b) {
      return a.x > b.x || ( a.x == b.x && a.y > b.y);
  });

  ASSERT_EQ(hullAct, hullExp);
}
