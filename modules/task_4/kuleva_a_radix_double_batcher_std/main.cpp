// Copyright 2023 Kuleva Anna
#include <gtest/gtest.h>
#include "./radix_double_batcher_std.h"


void test(const std::vector<double>& expected, const std::vector<double>& sorted) {
    ASSERT_EQ(expected.size(), sorted.size());
    for (int i = 0; i < expected.size(); i++) {
        ASSERT_DOUBLE_EQ(expected[i], sorted[i]);
    }
}

TEST(ParallelSTD, OnlyPositiveEvenSize) {
    std::vector<double> input = { 0.1, 0.0111, 1, 19, 120, 0.2, 0.00009, 2 };
    std::vector<double> sorted = radixBatcherSort(input);
    std::vector<double> expected = { 0.00009, 0.0111, 0.1, 0.2, 1, 2, 19, 120 };
    test(expected, sorted);
}

TEST(ParallelSTD, OnlyPositiveOddSize) {
    std::vector<double> input = { 0.1, 0.0111, 1, 19, 120, 0.2, 0.00009, 2, 17 };
    std::vector<double> sorted = radixBatcherSort(input);
    std::vector<double> expected = { 0.00009, 0.0111, 0.1, 0.2, 1, 2, 17, 19, 120 };
    test(expected, sorted);
}

TEST(ParallelSTD, OnlyNegativeEvenSize) {
    std::vector<double> input = { -0.1, -0.0111, -1, -19, -120, -0.2, -0.00009, -2 };
    std::vector<double> sorted = radixBatcherSort(input);
    std::vector<double> expected = { -120, -19, -2, -1, -0.2, -0.1, -0.0111, -0.00009 };
    test(expected, sorted);
}

TEST(ParallelSTD, OnlyNegativeOddSize) {
    std::vector<double> input = { -0.1, -0.0111, -1, -19, -120, -0.2, -0.00009, -2, -17 };
    std::vector<double> sorted = radixBatcherSort(input);
    std::vector<double> expected = { -120, -19, -17, -2, -1, -0.2, -0.1, -0.0111, -0.00009 };
    test(expected, sorted);
}

TEST(ParallelSTD, PositiveAndNegativeEvenSize) {
    std::vector<double> input = { -0.1, 0.0111, 1, -19, 120, -0.2, -0.00009, -2 };
    std::vector<double> sorted = radixBatcherSort(input);
    std::vector<double> expected = { -19, -2, -0.2, -0.1, -0.00009, 0.0111, 1, 120 };
    test(expected, sorted);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
