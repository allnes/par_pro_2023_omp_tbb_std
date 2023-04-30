// Copyright 2023 Sigachev Anton
#include <gtest/gtest.h>
#include "./sort.h"

bool test(int size) {
    std::vector<int> vec_seq = getRandomVector(size);
    std::vector<int> vec_par = vec_seq;

    volatile double start_seq = omp_get_wtime();
    ShellSortSequantial(&vec_seq);
    volatile double end_seq = omp_get_wtime();

    volatile double start_par = omp_get_wtime();
    ShellSortParallel(&vec_par);
    volatile double end_par = omp_get_wtime();

    double seq_time = end_seq - start_seq;
    double par_time = end_par - start_par;
    std::cout << "Effective: " << seq_time / par_time << '\n';

    return vec_seq == vec_par && checkSort(vec_par);
}

TEST(ShellSort, test_size_101) {
    ASSERT_TRUE(test(101));
}

TEST(ShellSort, test_size_503) {
    ASSERT_TRUE(test(503));
}

TEST(ShellSort, test_size_1021) {
    ASSERT_TRUE(test(1021));
}

TEST(ShellSort, test_size_2322) {
    ASSERT_TRUE(test(2322));
}

TEST(ShellSort, test_size_12323) {
    ASSERT_TRUE(test(12323));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
