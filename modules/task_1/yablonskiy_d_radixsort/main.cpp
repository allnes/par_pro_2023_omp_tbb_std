// Copyright 2023 Yablonskiy Dmitriy
#include <gtest/gtest.h>
#include <vector>
#include "./radixsort.h"

TEST(RadixSortTest, SortsArray) {
    std::vector<int> arr = { 170, 45, 75, 90, 802, 24, 2, 66 };
    arr = radixSort(arr);
    std::vector<int> expec = { 2, 24, 45, 66, 75, 90, 170, 802 };
    EXPECT_EQ(arr, expec);
}

TEST(RadixSortTest, ArrayOfRightElements) {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    arr = radixSort(arr);
    std::vector<int> expec = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(arr, expec);
}

TEST(RadixSortTest, ArrayOfSameElements) {
    std::vector<int> arr = { 1, 1, 1, 1, 1 };
    arr = radixSort(arr);
    std::vector<int> expec = { 1, 1, 1, 1, 1 };
    EXPECT_EQ(arr, expec);
}

TEST(RadixSortTest, ArrayOfFewSameElements) {
    std::vector<int> arr = { 1, 312, 25, 1, 312 };
    arr = radixSort(arr);
    std::vector<int> expec = { 1, 1, 25, 312, 312 };
    EXPECT_EQ(arr, expec);
}

TEST(RadixSortTest, ArrayOfEmptyElements) {
    std::vector<int> arr = {};
    arr = radixSort(arr);
    std::vector<int> expec = {};
    EXPECT_EQ(arr, expec);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
