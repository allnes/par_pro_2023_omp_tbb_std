// Copyright 2023 Davydov Andrey
#include <gtest/gtest.h>
#include <omp.h>
#include <vector>
#include <cmath>
#include "./monte_carlo.h"

constexpr double precision = 0.1;

TEST(Sequential_Monte_Carlo, Two_Dims_Sum) {
    std::vector<double> a = { 0.0, 0.0 }, b = { 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcSum, a, b, n);
    double parallel = parallelMonteCarlo(funcSum, a, b, n);

    double error = std::abs(parallel - sequential) / parallel;

    ASSERT_LE(error, precision);
}

TEST(Sequential_Monte_Carlo, Two_Dims_Sub) {
    std::vector<double> a = { 0.0, 0.0 }, b = { 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcSub, a, b, n);
    double parallel = parallelMonteCarlo(funcSub, a, b, n);

    double error = std::abs(parallel - sequential) / parallel;

    ASSERT_LE(error, precision);
}

TEST(Sequential_Monte_Carlo, Two_Dims_Multiple) {
    std::vector<double> a = { 0.0, 0.0 }, b = { 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcMultiply, a, b, n);
    double parallel = parallelMonteCarlo(funcMultiply, a, b, n);

    double error = std::abs(parallel - sequential) / parallel;

    ASSERT_LE(error, precision);
}

TEST(Sequential_Monte_Carlo, Three_Dims_Sum) {
    std::vector<double> a = { 0.0, 0.0, 0.0 }, b = { 13.0, 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcSum, a, b, n);
    double parallel = parallelMonteCarlo(funcSum, a, b, n);

    double error = std::abs(parallel - sequential) / parallel;

    ASSERT_LE(error, precision);
}

TEST(Sequential_Monte_Carlo, Three_Dims_Sub) {
    std::vector<double> a = { 0.0, 0.0, 0.0 }, b = { 13.0, 13.0, 13.0 };
    int n = 100000;

    double sequential = sequentialMonteCarlo(funcSub, a, b, n);
    double parallel = parallelMonteCarlo(funcSub, a, b, n);

    double error = std::abs(parallel - sequential) / parallel;

    ASSERT_LE(error, precision);
}

/**
 * Efficiency test
 * Delete or comment when publishing to the main repository
 * Delete this commentary when publishing to the main repository
*/
// TEST(Sequential_Monte_Carlo, Time_Test) {
//     std::vector<double> a = { 0.0, 0.0, 0.0 }, b = { 13.0, 13.0, 13.0 };
//     int n = 240000000;

//     double start = omp_get_wtime();
//     double sequential = sequentialMonteCarlo(funcSub, a, b, n);
//     double end = omp_get_wtime();
//     std::cout << "Sequential implementation: " << end - start << std::endl;
//     start = omp_get_wtime();
//     double parallel = parallelMonteCarlo(funcSub, a, b, n);
//     end = omp_get_wtime();
//     std::cout << "Parallel implementation: " << end - start << std::endl;

//     double error = std::abs(parallel - sequential) / parallel;

//     ASSERT_LE(error, precision);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
