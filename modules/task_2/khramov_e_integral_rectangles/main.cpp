// Copyright 2023 Khramov Egor
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../../../modules/task_2/khramov_e_integral_rectangles/khramov_e_integral_rectangles.h"

const double epsilon = 0.001;


IntegralFunction foo1 = [](double x, double y, double z) {
    return 1.0;
};

IntegralFunction foo2 = [](double x, double y, double z) {
    return x * y * z;
};

IntegralFunction foo3 = [](double x, double y, double z) {
    return x * z - y * y * y;
};

IntegralFunction foo4 = [](double x, double y, double z) {
    return 3 * exp(x) - y * z;
};

IntegralFunction foo5 = [](double x, double y, double z) {
    return sin(x) + cos(y) + 3 * z;
};

double a[3] = {1, 1, 1};
double b[3] = {2, 2, 2};
int n[3] = {100, 100, 100};

void testIntegral(IntegralFunction func) {
    double sequential = integrateSequential(func, a, b, n);
    double parallel = integrateParallel(func, a, b, n);
    ASSERT_NEAR(sequential, parallel, epsilon);
}

TEST(Parallel_Operations_OpenMP, Test_Integral) {
    testIntegral(foo1);
}

TEST(Parallel_Operations_OpenMP, Test_Integral_2) {
    testIntegral(foo2);
}


TEST(Parallel_Operations_OpenMP, Test_Integral_3) {
    testIntegral(foo3);
}


TEST(Parallel_Operations_OpenMP, Test_Integral_4) {
    testIntegral(foo4);
}


TEST(Parallel_Operations_OpenMP, Test_Integral_5) {
    testIntegral(foo5);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
