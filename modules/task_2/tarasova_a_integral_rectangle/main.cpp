// Copyright 2023 Tarasova Anastasiya
#include <vector>
#include "./integral_omp.h"
#include <gtest/gtest.h>

double f1(double x, double y, double z) {
    return x + y + z;
}

double f2(double x, double y, double z) {
    return x * y * z;
}

double f3(double x, double y, double z) {
    return sin(x) * cos(y) + z;
}

double f4(double x, double y, double z) {
    return exp(x) + y * y * z;
}

double f5(double x, double y, double z) {
    return x * x * x + y * y + z;
}

TEST(Parallel_OpenMP, Test_inegral_1) {
    ASSERT_DOUBLE_EQ(getSequential(0.0, 0.0, 0.0,
        2.0, 2.0, 2.0, 1.0, f1), getParallel(0.0, 0.0, 0.0,
        2.0, 2.0, 2.0, 1.0, f1));
}

TEST(Parallel_OpenMP, Test_inegral_2) {
    ASSERT_DOUBLE_EQ(getSequential(0.0, 1.0, 0.0,
        2.0, 4.0, 3.0, 1.0, f2), getParallel(0.0, 1.0, 0.0,
        2.0, 4.0, 3.0, 1.0, f2));
}

TEST(Parallel_OpenMP, Test_inegral_3) {
    ASSERT_DOUBLE_EQ(getSequential(4.0, 2.0, 1.0,
        6.0, 3.0, 3.0, 1.0, f3), getParallel(4.0, 2.0, 1.0,
        6.0, 3.0, 3.0, 1.0, f3));
}

TEST(Parallel_OpenMP, Test_inegral_4) {
    ASSERT_DOUBLE_EQ(getSequential(0.0, 1.0, 2.0, 2.0,
        3.0, 4.0, 1.0, f4), getParallel(0.0, 1.0, 2.0, 2.0,
        3.0, 4.0, 1.0, f4));
}

TEST(Parallel_OpenMP, Test_inegral_5) {
    ASSERT_DOUBLE_EQ(getSequential(5.0, 3.0, 7.0,
        6.0, 7.0, 8.0, 1.0, f5), getParallel(5.0, 3.0, 7.0,
        6.0, 7.0, 8.0, 1.0, f5));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
