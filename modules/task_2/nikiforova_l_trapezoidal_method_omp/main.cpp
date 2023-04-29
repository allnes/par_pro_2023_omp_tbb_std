// Copyright 2023 Nikiforova Lada
#include <gtest/gtest.h>
#include <omp.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "../../../modules/task_2/nikiforova_l_trapezoidal_method_omp/trapezoidal_method.h"


double f1(std::vector<double> prm) {
    double x = prm[0];
    double y = prm[1];
    return (4 * x * x + 2 * y * y * y);
}
double f2(std::vector<double> prm) {
    double x = prm[0];
    double y = prm[1];
    return (sin(x+y));
}
double f3(std::vector<double> prm) {
    double x = prm[0];
    double y = prm[1];
    double z = prm[2];
    return ((x+y)*(x+y)+2*z*z);
}
double f4(std::vector<double> prm) {
    double x = prm[0];
    double y = prm[1];
    double z = prm[2];
    return (x*x*z*sin(x*y*z));
}

double f5(std::vector<double> prm) {
    double x = prm[0];
    double y = prm[1];
    double z = prm[2];
    return (sqrt(x+z) + 2 * y * y);
}


TEST(Trapezoidal_Rule_omp, Test1) {
    int n = 2;
    int p = 10;
    std::vector<std::pair<double, double>> front(n);
    front[0] = { 2, 8 };
    front[1] = { 1, 3 };
    double res = trapezoidalMethod(f1, front, p);
    double a = 1584;

    ASSERT_NEAR(res, a, 257);
}

TEST(Trapezoidal_Rule_omp, Test2) {
    int n = 2;
    int p = 10;
    std::vector<std::pair<double, double>> front(n);
    front[0] = { 0, 3.14 };
    front[1] = { 0 , 3.14/2 };
    double res = trapezoidalMethod(f2, front, p);
    double a = 2;

    ASSERT_NEAR(res, a, 0.5);
}

TEST(Trapezoidal_Rule_omp, Test3) {
    int n = 3;
    std::vector<std::pair<double, double>> front(n);
    int p = 10;
    front[0] = { 0, 1 };
    front[1] = { 2, 6 };
    front[2] = { -5, 4 };
    double result = trapezoidalMethod(f3, front, p);
    double a = 1284;

    ASSERT_NEAR(result, a, 245);
}

TEST(Trapezoidal_Rule_omp, Test4) {
    int n = 3;
    std::vector<std::pair<double, double>> front(n);
    int p = 10;
    front[0] = { 0, 2 };
    front[1] = { 0, 3.14 };
    front[2] = { 0, 1 };
    double result = trapezoidalMethod(f4, front, p);
    double a = 2;
    ASSERT_NEAR(result, a, 0.4);
}

TEST(Trapezoidal_Rule_omp, Test5) {
    int n = 3;
    std::vector<std::pair<double, double>> front(n);
    int p = 10;
    front[0] = { 1, 4 };
    front[1] = { -10, 5 };
    front[2] = { 0, 2 };
    double res = trapezoidalMethod(f5, front, p);
    double a = 4666;

    ASSERT_NEAR(res, a, 610);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
