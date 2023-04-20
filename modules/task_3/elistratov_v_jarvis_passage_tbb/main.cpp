// Copyright 2023 Elistratov Vladimir
#include <gtest/gtest.h>

#include <iostream>

#include "../../modules/task_3/elistratov_v_jarvis_passage_tbb/jarvis_passage_tbb.h"

TEST(Tbb_Jarvis, PointsCount_0) {
  std::vector<Point> points(0);
  ASSERT_ANY_THROW(tbbJarvis(points));
}

TEST(Tbb_Jarvis, PointsCount_2500) {
  std::vector<Point> points = getRandomCombinationPoints(2500);
  std::vector<Point> resultSeq = sequentinalJarvis(points);
  std::vector<Point> resultTbb = tbbJarvis(points);
  ASSERT_EQ(resultSeq, resultTbb);
}

TEST(Tbb_Jarvis, PointsCount_5000) {
  std::vector<Point> points = getRandomCombinationPoints(5000);
  std::vector<Point> resultSeq = sequentinalJarvis(points);
  std::vector<Point> resultTbb = tbbJarvis(points);
  ASSERT_EQ(resultSeq, resultTbb);
}

TEST(Tbb_Jarvis, PointsCount_75000) {
  std::vector<Point> points = getRandomCombinationPoints(75000);
  std::vector<Point> resultSeq = sequentinalJarvis(points);
  std::vector<Point> resultTbb = tbbJarvis(points);
  ASSERT_EQ(resultSeq, resultTbb);
}

TEST(Tbb_Jarvis, PointsCount_1000000) {
  std::vector<Point> points = getRandomCombinationPoints(1000000);
  std::vector<Point> resultSeq = sequentinalJarvis(points);
  std::vector<Point> resultTbb = tbbJarvis(points);
  ASSERT_EQ(resultSeq, resultTbb);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  // tbb::task_scheduler_init init(tbb::task_scheduler_init::automatic);
  return RUN_ALL_TESTS();
}
