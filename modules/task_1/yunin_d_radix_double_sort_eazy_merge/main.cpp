// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../../../modules/task_1/yunin_d_radix_double_sort_eazy_merge/yunin_d_radix_double_sort_eazy_merge.h"

TEST(Sequential, Test_Sort_With_20_Random_Elements) {
    int size = 20;
    int halfSize = size / 2;
    std::vector<double> vec1 = randomVec(size, -10, 10);
    std::vector<double> firstPart, secondPart;
    for (int i = 0; i < halfSize; i++) {
        firstPart.push_back(vec1[i]);
        secondPart.push_back(vec1[i + halfSize]);
    }
    std::vector<double> result;
    result = radixSort(firstPart, secondPart);
    std::sort(vec1.begin(), vec1.end());
    // printVector(vec1);
    // printVector(result);
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}

TEST(Sequential, Test_Sort_With_30_Only_Positive_Elements) {
    int size = 30;
    int halfSize = size / 2;
    std::vector<double> vec1 = randomVec(size, 1, 30);
    std::vector<double> firstPart, secondPart;
    for (int i = 0; i < halfSize; i++) {
        firstPart.push_back(vec1[i]);
        secondPart.push_back(vec1[i + halfSize]);
    }
    std::vector<double> result;
    result = radixSort(firstPart, secondPart);
    std::sort(vec1.begin(), vec1.end());
    // printVector(vec1);
    // printVector(result);
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}

TEST(Sequential, Test_Sort_With_30_Only_Negative_Elements) {
    int size = 30;
    int halfSize = size / 2;
    std::vector<double> vec1 = randomVec(size, -50, -1);
    std::vector<double> firstPart, secondPart;
    for (int i = 0; i < halfSize; i++) {
        firstPart.push_back(vec1[i]);
        secondPart.push_back(vec1[i + halfSize]);
    }
    std::vector<double> result;
    result = radixSort(firstPart, secondPart);
    std::sort(vec1.begin(), vec1.end());
    // printVector(vec1);
    // printVector(result);
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}

TEST(Sequential, Test_Sort_With_100_Random_Elements) {
    int size = 100;
    int halfSize = size / 2;
    std::vector<double> vec1 = randomVec(size, -10, 10);
    std::vector<double> firstPart, secondPart;
    for (int i = 0; i < halfSize; i++) {
        firstPart.push_back(vec1[i]);
        secondPart.push_back(vec1[i + halfSize]);
    }
    std::vector<double> result;
    result = radixSort(firstPart, secondPart);
    std::sort(vec1.begin(), vec1.end());
    // printVector(vec1);
    // printVector(result);
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}

TEST(Sequential, Test_Sort_With_1000_Random_Elements) {
    int size = 1000;
    int halfSize = size / 2;
    std::vector<double> vec1 = randomVec(size, -100, 100);
    std::vector<double> firstPart, secondPart;
    for (int i = 0; i < halfSize; i++) {
        firstPart.push_back(vec1[i]);
        secondPart.push_back(vec1[i + halfSize]);
    }
    std::vector<double> result;
    result = radixSort(firstPart, secondPart);
    std::sort(vec1.begin(), vec1.end());
    // printVector(vec1);
    // printVector(result);
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i], result[i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
