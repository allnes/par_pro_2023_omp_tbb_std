// Copyright 2023 Bochkarev Vladimir
#include <gtest/gtest.h>
#include "./integral_omp.h"

double f1(double x, double y, double z) {
    return x*x+y*y+z*z;
}

double f2(double x, double y, double z) {
    return x*y*z;
}

double f3(double x, double y, double z) {
    return x*x*x;
}

double f4(double x, double y, double z) {
    return x;
}

TEST(Par, Test1) {
    double (*fun)(double, double, double);
    fun = f1;
    double a = 0, b = 3;
    double c = 0, d = 2;
    double e = 0, f = 1;
    double ans = 28;
    double res = integral3D(a, b, c, d, e, f, 100, fun);
    ASSERT_NEAR(ans, res, 0.0014);
}

TEST(Par, Test2) {
    double (*fun)(double, double, double);
    fun = f2;
    double a = 1, b = 2;
    double c = 2, d = 3;
    double e = 3, f = 4;
    double ans = 13.125;
    double res = integral3D(a, b, c, d, e, f, 100, fun);
    ASSERT_NEAR(ans, res, 0.0003);
}

TEST(Par, Test3) {
    double (*fun)(double, double, double);
    fun = f3;
    double a = 0, b = 1;
    double c = 0, d = 1;
    double e = 0, f = 1;
    double ans = 0.25;
    double res = integral3D(a, b, c, d, e, f, 100, fun);
    ASSERT_NEAR(ans, res, 0.0003);
}

TEST(Par, Test4) {
    double (*fun)(double, double, double);
    fun = f4;
    double a = 0, b = 1;
    double c = 0, d = 1;
    double e = 0, f = 1;
    double ans = 0.5;
    double res = integral3D(a, b, c, d, e, f, 100, fun);
    ASSERT_NEAR(ans, res, 0.0003);
}

TEST(Par, Test5) {
    double (*fun)(double, double, double);
    fun = f4;
    double a = 0, b = 5;
    double c = 0, d = 5;
    double e = 0, f = 5;
    double ans = 312.5;
    double res = integral3D(a, b, c, d, e, f, 100, fun);
    ASSERT_NEAR(ans, res, 0.0075);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
