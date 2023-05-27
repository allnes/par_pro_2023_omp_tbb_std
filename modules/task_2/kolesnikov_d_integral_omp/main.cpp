// Copyright 2023 Kolesnikov Denis
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "../../../modules/task_2/kolesnikov_d_integral_omp/integral.h"

double f1(std::vector<double> par) {
  double x = par[0];
  return (x);
}
double f2(std::vector<double> par) {
  double x = par[0];
  double y = par[1];
  return (x*y + y*x);
}
double f3(std::vector<double> par) {
  double x = par[0];
  double y = par[1];
  double z = par[2];
  return (x*y*z);
}
double f4(std::vector<double> par) {
  double x = par[0];
  double y = par[1];
  double z = par[2];
  return (x*x+z*z);
}
double f5(std::vector<double> par) {
  double x = par[0];
  double y = par[1];
  double z = par[2];
  return (x + 2*(y+z));
}

TEST(Omp, test_1) {
  std::vector<std::pair<double, double>> bounds(3);
  bounds[0] = {0, 5};
  bounds[1] = {0, 5};
  bounds[2] = {0, 5};
  double res = 312.5;
  double tolerance = 0.05;

  double calc_res = integral(f1, bounds, 50);
  ASSERT_NEAR(calc_res, res, tolerance);
}

TEST(Omp, test_2) {
  std::vector<std::pair<double, double>> bounds(3);
  bounds[0] = {0, 5};
  bounds[1] = {0, 1};
  bounds[2] = {0, 1};
  double res = 12.5;
  double tolerance = 0.01;

  double calc_res = integral(f2, bounds, 50);
  ASSERT_NEAR(calc_res, res,  tolerance);
}

TEST(Omp, test_3) {
  std::vector<std::pair<double, double>> bounds(3);
  bounds[0] = {0, 5};
  bounds[1] = {1, 3};
  bounds[2] = {1, 3};
  double res = 200;
  double tolerance = 0.5;

  double calc_res = integral(f3, bounds, 50);
  ASSERT_NEAR(calc_res, res, tolerance);
}

TEST(Omp, test_4) {
  std::vector<std::pair<double, double>> bounds(3);
  bounds[0] = {0, 5};
  bounds[1] = {0, 5};
  bounds[2] = {0, 5};
  double res = 6250/3;
  double tolerance = 0.5;

  double calc_res = integral(f4, bounds, 100);
  ASSERT_NEAR(calc_res, res, tolerance);
}



TEST(Omp, test_5) {
  std::vector<std::pair<double, double>> bounds(3);
  bounds[0] = {0, 3};
  bounds[1] = {0, 2};
  bounds[2] = {1, 3};
  double res = 90;
  double tolerance = 0.001;

  double calc_res = integral(f5, bounds, 100);
  ASSERT_NEAR(calc_res, res, tolerance);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

