// Copyright 2023 Shaposhnikova Ekaterina
#include <gtest/gtest.h>
#include "./monte_carlo.h"

double func1(double x, double y, double z) {
  return (x * x + 1) * (x * z + 1) * y * y;
}

double func2(double x, double y, double z) {
  return x + y + z;
}

double func3(double x, double y, double z) {
  return  x * z + x * y;
}

double func4(double x, double y, double z) {
  return x * x * x + y + z * z * z;
}

TEST(MonteCarloParal , Test_1) {
  std::vector<double> a{ 0, 0, 0 };
  std::vector<double> b{ 1, 1, 1 };
  ASSERT_NO_THROW(MonteCarloParallel(a, b, 20000, func1));
}

TEST(MonteCarloParal, Test_2) {
  std::vector<double> a{ 0, 0, 0 };
  std::vector<double> b{ 1, 1, 1 };
  double resSeq = MonteCarloSeq(a, b, 20000, func1);
  double resPar = MonteCarloParallel(a, b, 20000, func1);
  ASSERT_NEAR(resPar, resSeq, 1);
}

TEST(MonteCarloParal, Test_3) {
  std::vector<double> a{ 1, 1, 1 };
  std::vector<double> b{ 2, 2, 2 };
  double resSeq = MonteCarloSeq(a, b, 20000, func2);
  double resPar = MonteCarloParallel(a, b, 20000, func2);
  ASSERT_NEAR(resPar, resSeq, 1);
}

TEST(MonteCarloParal, Test_4) {
  std::vector<double> a{ 1, 1, 1 };
  std::vector<double> b{ 2, 2, 2 };
  double resSeq = MonteCarloSeq(a, b, 20000, func3);
  double resPar = MonteCarloParallel(a, b, 20000, func3);
  ASSERT_NEAR(resPar, resSeq, 1);
}

TEST(MonteCarloParal, Test_5) {
  std::vector<double> a{ 1, 1, 1 };
  std::vector<double> b{ 2, 2, 2 };
  ASSERT_NO_THROW(MonteCarloParallel(a, b, 20000, func4));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
