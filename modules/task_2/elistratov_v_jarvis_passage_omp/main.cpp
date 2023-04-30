// Copyright 2023 Elistratov Vladimir
#include <gtest/gtest.h>

#include <iostream>

#include "../../modules/task_2/elistratov_v_jarvis_passage_omp/jarvis_passage_omp.h"

TEST(Omp_Jarvis, PointsCount_0) {
  std::vector<Point> points(0);
  ASSERT_ANY_THROW(openmpJarvis(points));
}

TEST(Omp_Jarvis, PointsCount_2500) {
  std::vector<Point> points = getRandomCombinationPoints(2500);
  std::vector<Point> resultSeq = sequentinalJarvis(points);
  std::vector<Point> resultOmp = openmpJarvis(points);
  ASSERT_EQ(resultSeq, resultOmp);
}

TEST(Omp_Jarvis, PointsCount_5000) {
  std::vector<Point> points = getRandomCombinationPoints(5000);
  std::vector<Point> resultSeq = sequentinalJarvis(points);
  std::vector<Point> resultOmp = openmpJarvis(points);
  ASSERT_EQ(resultSeq, resultOmp);
}

TEST(Omp_Jarvis, PointsCount_75000) {
  std::vector<Point> points = getRandomCombinationPoints(75000);
  std::vector<Point> resultSeq = sequentinalJarvis(points);
  std::vector<Point> resultOmp = openmpJarvis(points);
  ASSERT_EQ(resultSeq, resultOmp);
}

TEST(Omp_Jarvis, PointsCount_1000000) {
  std::vector<Point> points = getRandomCombinationPoints(1000000);
  std::vector<Point> resultSeq = sequentinalJarvis(points);
  std::vector<Point> resultOmp = openmpJarvis(points);
  ASSERT_EQ(resultSeq, resultOmp);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
