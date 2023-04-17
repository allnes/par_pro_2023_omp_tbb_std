// Copyright 2023 Davydov Andrey
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "./monte_carlo.h"


constexpr double precision = 0.01;

TEST(Sequential_Monte_Carlo, Two_Dims_Sum) {
    std::vector<double> a = { 0.0, 0.0 }, b = { 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcSum, a, b, n);
    double expected = 2197.0;

    double error = std::abs(expected - sequential) / sequential;

    ASSERT_LE(error, precision);
}

TEST(Sequential_Monte_Carlo, Two_Dims_Sub) {
    std::vector<double> a = { 0.0, 0.0 }, b = { 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcSub, a, b, n);
    double expected = -2197.0;

    double error = std::abs(expected - sequential) / sequential;

    ASSERT_LE(error, precision);
}

TEST(Sequential_Monte_Carlo, Two_Dims_Multiple) {
    std::vector<double> a = { 0.0, 0.0 }, b = { 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcMultiply, a, b, n);
    double expected = 28561.0 / 4.0;

    double error = std::abs(expected - sequential) / sequential;

    ASSERT_LE(error, precision);
}

TEST(Sequential_Monte_Carlo, Three_Dims_Sum) {
    std::vector<double> a = { 0.0, 0.0, 0.0 }, b = { 13.0, 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcSum, a, b, n);
    double expected = 42841.5;

    double error = std::abs(expected - sequential) / sequential;

    ASSERT_LE(error, precision);
}

TEST(Sequential_Monte_Carlo, Three_Dims_Sub) {
    std::vector<double> a = { 0.0, 0.0, 0.0 }, b = { 13.0, 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcSub, a, b, n);
    double expected = -42841.5;

    double error = std::abs(expected - sequential) / sequential;

    ASSERT_LE(error, precision);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
