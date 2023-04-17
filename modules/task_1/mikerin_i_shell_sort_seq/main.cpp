// Copyright 2023 Mikerin Ilya
#include <gtest/gtest.h>
#include <vector>
#include "ShellSort.h"


TEST(Sequential_Merge, Test_Merge_Sort) {
    std::vector<double> vec = {1, 4, 6, 3, 5, 2};
    std::vector<double> result = {1, 2, 3, 4, 5, 6};

    MergeSort(vec, 0, vec.size()-1);

    ASSERT_EQ(vec, result);
}

TEST(Sequential_Merge, Test_Merge_Sort_rand) {
    std::vector<double> vec = getRandomVector(100);
    bool nice = true;

    MergeSort(vec, 0, vec.size()-1);

    for (int i =0; i< vec.size()-1; i++) {
        if ( vec.at(i) > vec.at(i+1) ) nice = false;
    }

    ASSERT_TRUE(nice);
}

TEST(Sequential_Shell, Test_Shell_Sort) {
    std::vector<double> vec = {1, 4, 6, 3, 5, 2};
    std::vector<double> result = {1, 2, 3, 4, 5, 6};

    ShellSort(vec);

    ASSERT_EQ(vec, result);
}

TEST(Sequential_Shell, Test_Shell_Sort_Empty) {
    std::vector<double> vec = {};
    std::vector<double> result = {};

    ShellSort(vec);

    ASSERT_EQ(vec, result);
}

TEST(Sequential_Shell, Test_Shell_Sort_rand) {
    bool nice = true;

    std::vector<double> vec = getRandomVector(100);

    ShellSort(vec);

    for (int i =0; i< vec.size()-1; i++) {
        if (vec.at(i) > vec.at(i+1)) nice = false;
    }

    ASSERT_TRUE(nice);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
