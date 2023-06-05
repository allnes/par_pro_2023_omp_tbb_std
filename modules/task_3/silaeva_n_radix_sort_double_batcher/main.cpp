// Copyright 2023 Silaeva Natalya

#include <gtest/gtest.h>
#include<iostream>
#include "tbb/tbb.h"
#include "./radix_sort_double_batcher.h"

TEST(radix_sort_double_batcher_seq, test_sort_int_10) {
    std::vector<double> vec = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vec = radix_sort_tbb(vec, 0);
    std::vector<double> vec_true = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(vec, vec_true);
}

TEST(radix_sort_double_batcher_seq, test_sort_10_1) {
    std::vector<double> vec = {10.2, 9.5, 8.7, 7.4, 6.5,
                            5.1, 4.2, 3.9, 2.1, 1.1};
    vec = radix_sort_tbb(vec, 1);
    std::vector<double> vec_true = {1.1, 2.1, 3.9, 4.2, 5.1,
                                6.5, 7.4, 8.7, 9.5, 10.2};
    ASSERT_EQ(vec, vec_true);
}

TEST(radix_sort_double_batcher_seq, test_sort_int_and_double) {
    std::vector<double> vec = {10, 9.5, 8, 7.4, 6.5,
                            5, 4.2, 3.9, 2, 1.1};
    vec = radix_sort_tbb(vec, 1);
    std::vector<double> vec_true = {1.1, 2, 3.9, 4.2, 5,
                                6.5, 7.4, 8, 9.5, 10};
    ASSERT_EQ(vec, vec_true);
}

TEST(radix_sort_double_batcher_seq, test_sort_10_2) {
    std::vector<double> vec = {10.26, 9.5, 8.73, 7.43, 6.5,
                            5.15, 4.28, 3.9, 2.1, 1.1};
    vec = radix_sort_tbb(vec, 2);
    std::vector<double> vec_true = {1.1, 2.1, 3.9, 4.28, 5.15,
                                6.5, 7.43, 8.73, 9.5, 10.26};
    ASSERT_EQ(vec, vec_true);
}

TEST(radix_sort_double_batcher_tbb, test_sort_random_100) {
    std::vector<double> vec = get_random_double_vector(100);
    vec = radix_sort_tbb(vec, 3);
    bool is_sorting = check_sort(vec);
    ASSERT_TRUE(is_sorting);
}

TEST(radix_sort_double_batcher_seq, test_sort_random_1000) {
    std::vector<double> vec = get_random_double_vector(1000);
    vec = radix_sort_tbb(vec, 3);
    bool is_sorting = check_sort(vec);
    ASSERT_TRUE(is_sorting);
}

TEST(radix_sort_double_batcher_seq, test_sort_random_all) {
    std::vector<double> vec = get_random_double_vector(1000);
    vec = radix_sort_tbb(vec, 3);
    bool is_sorting = check_sort(vec);
    ASSERT_TRUE(is_sorting);
}

int main(int argc, char **argv) {
    tbb::task_scheduler_init init(tbb::task_scheduler_init::automatic);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
