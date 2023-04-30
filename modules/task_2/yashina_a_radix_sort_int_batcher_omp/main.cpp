// Copyright 2023 Yashina Anastasia
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "./radix_sort_int_batcher_omp.h"

TEST(Radix_Sort_W_Batcher, Test_CorrectSort) {
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    ASSERT_EQ(true, checkSort(vec));
}

TEST(Radix_Sort_W_Batcher, Test_Sort) {
    std::vector<int> vec = { 9, 4, 5, 6, 3, 2, 1, 7, 8 };
    std::vector<int> test_vec = GetRandVector(100);
    radixSort(&test_vec);
    ASSERT_EQ(true, checkSort(test_vec));
}

TEST(Radix_Sort_W_Batcher, Test_RadixSort_w_Batcher) {
    std::vector<int> part1 = GetRandVector(100);
    std::vector<int> part2 = GetRandVector(100);
    radixSort(&part1);
    radixSort(&part2);
    std::vector<int> even = evenBatch(part1, part2);
    std::vector<int> odd = oddBatch(part1, part2);
    std::vector<int> res = EvenOddBatch(even, odd);
    std::vector<int>stl_mege(200);
    std::merge(part1.begin(), part1.end(), part2.begin(), part2.end(), stl_mege.begin());
    ASSERT_EQ(stl_mege, res);
}

TEST(Radix_Sort_W_Batcher, Test_WrangSort) {
    std::vector<int> vec = { 0, 2, 7, 3, 4 };
    ASSERT_EQ(false, checkSort(vec));
}

TEST(Radix_Sort_W_Batcher, Test_Batcher) {
    std::vector<int> part1 = GetRandVector(10);
    std::vector<int> part2 = GetRandVector(10);
    std::sort(part1.begin(), part1.end());
    std::sort(part2.begin(), part2.end());
    std::vector<int> even = evenBatch(part1, part2);
    std::vector<int> odd = oddBatch(part1, part2);
    std::vector<int> res = EvenOddBatch(even, odd);
    std::vector<int>stl_mege(20);
    std::merge(part1.begin(), part1.end(), part2.begin(), part2.end(), stl_mege.begin());
    ASSERT_EQ(stl_mege, res);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
