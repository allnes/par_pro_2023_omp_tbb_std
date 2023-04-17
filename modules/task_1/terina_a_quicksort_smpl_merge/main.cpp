// Copyright 2023 Terina Alina
#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include "../../../modules/task_1/terina_a_quicksort_smpl_merge/qs_smpl_mrg.h"

TEST(Sequentional_version_QS, can_sort_mas_10) {
    int n = 10;
    std::vector<int> vec = getRandomVector(n);
    std::vector<int> Vec1(vec);
    quickSort(0, n - 1, &vec);
    std::sort(Vec1.begin(), Vec1.end());

    EXPECT_EQ(vec, Vec1);
}

TEST(Sequentional_version_QS, can_sort_mas_100) {
    int n = 100;
    std::vector<int> vec = getRandomVector(n);
    std::vector<int> Vec1(vec);
    quickSort(0, n - 1, &vec);
    std::sort(Vec1.begin(), Vec1.end());

    EXPECT_EQ(vec, Vec1);
}
TEST(Sequentional_version_QS, can_sort_mas_300) {
    int n = 300;
    std::vector<int> vec = getRandomVector(n);
    std::vector<int> Vec1(vec);
    quickSort(0, n - 1, &vec);
    std::sort(Vec1.begin(), Vec1.end());

    EXPECT_EQ(vec, Vec1);
}
TEST(Sequentional_version_QS, sort_already_sorted_mas) {
    int n = 300;
    std::vector<int> vec = GetSortedVec(n);
    std::vector<int> Vec1(vec);

    quickSort(0, n - 1, &vec);

    EXPECT_EQ(vec, Vec1);
}

TEST(Sequentional_version_QS, sort_mirror_mas) {
    int n = 300;
    std::vector<int> vec = GetReversedVec(n);
    std::vector<int> Vec1(vec);

    quickSort(0, n - 1, &vec);
    std::reverse(Vec1.begin(), Vec1.end());

    EXPECT_EQ(vec, Vec1);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
