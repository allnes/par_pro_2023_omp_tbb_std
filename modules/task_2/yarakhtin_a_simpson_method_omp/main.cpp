// Copyright 2023 Yarakhtin Anton
#include <gtest/gtest.h>
#include <cmath>
#include "./simpson_method_omp.h"

constexpr double epsilon = 0.001;

double func_0(const std::vector<double>& args) {
    return 1;
}

double func_1(const std::vector<double>& args) {
    return 2 * args[0] * args[0] + args[0];
}

double func_2(const std::vector<double>& args) {
    return args[0] * args[1] * sqrt(100 * args[1]);
}

double func_3(const std::vector<double>& args) {
    double result = 1.;
    for (double arg : args) {
        result *= arg;
    }
    return result;
}

double func_4(const std::vector<double>& args) {
    double result = 1.;
    for (double arg : args) {
        result += log(arg) * sqrt(arg);
    }
    return result;
}

TEST(Simpson_Method, Simple_Test) {
    std::vector<std::tuple<double, double, int>> scopes = {
        {1, 2, 6}
    };
    ASSERT_NEAR(1, simpson_method_omp(scopes, func_0), epsilon);
}

TEST(Simpson_Method, Test_One_Arg) {
    std::vector<std::tuple<double, double, int>> scopes = {
        {0, 9, 10}
    };
    ASSERT_NEAR(simpson_method(scopes, func_1), simpson_method_omp(scopes, func_1), epsilon);
}

TEST(Simpson_Method, Test_Two_Args) {
    std::vector<std::tuple<double, double, int>> scopes = {
        {2, 3, 10}, {3, 4, 10}
    };
    ASSERT_NEAR(simpson_method(scopes, func_2), simpson_method_omp(scopes, func_2), epsilon);
}

TEST(Simpson_Method, Test_Multiple_Args) {
    std::vector<std::tuple<double, double, int>> scopes = {
        {0.1, 0.4, 10}, {2, 3, 10}, {-0.8, -0.3, 10}
    };
    ASSERT_NEAR(simpson_method(scopes, func_3), simpson_method_omp(scopes, func_3), epsilon);
}

TEST(Simpson_Method, Test_Different_Partion) {
    std::vector<std::tuple<double, double, int>> scopes = {
        {2, 3, 7}, {6, 7, 2}, {1, 2, 4}
    };
    ASSERT_NEAR(simpson_method(scopes, func_4), simpson_method_omp(scopes, func_4), epsilon);
}

TEST(Simpson_Method, Test_Big_Partion) {
    std::vector<std::tuple<double, double, int>> scopes = {
        {2, 5, 500}, {3, 7, 500}
    };
    ASSERT_NEAR(simpson_method(scopes, func_2), simpson_method_omp(scopes, func_2), epsilon);
}
