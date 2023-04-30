// Copyright 2023 Yunin Daniil
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../../../modules/task_2/yunin_d_radix_sort/yunin_d_radix_sort.h"

const int numParts = 4;

TEST(ParallelOpenMP, Test_Sort_With_1000000_Random_Elements) {
    int size = 1000000;
    std::vector<double> vec1 = getRandomVector(size, -10, 10);
    std::vector<double> firstPart = vec1;
    std::vector<double> result;

    result = radixSortParallOmp(firstPart, numParts);
    std::sort(vec1.begin(), vec1.end());
     // printVector(vec1);
     // printVector(result);
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}

TEST(ParallelOpenMP, Test_Sort_With_10000_Only_Positive_Elements) {
    int size = 10000;
    std::vector<double> vec1 = getRandomVector(size, 1, 20);
    std::vector<double> firstPart = vec1;
    std::vector<double> result;

    result = radixSortParallOmp(firstPart, numParts);
    std::sort(vec1.begin(), vec1.end());
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}

TEST(ParallelOpenMP, Test_Sort_With_10000_Only_Negative_Elements) {
    int size = 10000;
    std::vector<double> vec1 = getRandomVector(size, -100, -10);
    std::vector<double> firstPart = vec1;
    std::vector<double> result;

    result = radixSortParallOmp(firstPart, numParts);
    std::sort(vec1.begin(), vec1.end());
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}


TEST(ParallelOpenMP, Test_Sort_With_100000_Positive_and_Negative_Elements) {
    int size = 100000;
    std::vector<double> vec1 = getRandomVector(size, -100, 100);
    std::vector<double> firstPart = vec1;
    std::vector<double> result;

    result = radixSortParallOmp(firstPart, numParts);
    std::sort(vec1.begin(), vec1.end());
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}

TEST(ParallelOpenMP, Test_Sort_With_1000000_Elements_But_Vector_Already_Sorted) {
    int size = 1000000;
    std::vector<double> vec1 = getRandomVector(size, -10, 10);
    std::vector<double> firstPart = vec1;
    std::vector<double> result;

    std::sort(vec1.begin(), vec1.end());
    result = radixSortParallOmp(vec1, numParts);
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}

// #include <chrono>
// auto start2 = std::chrono::high_resolution_clock::now();
// result1 = radixSortSeq(secondPart);
// auto stop2 = std::chrono::high_resolution_clock::now();
// auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
// std::cout << "duration_seq: " << duration2.count() << '\n';

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
