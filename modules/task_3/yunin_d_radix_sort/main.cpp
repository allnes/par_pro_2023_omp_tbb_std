// Copyright 2023 Yunin Daniil
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_3/yunin_d_radix_sort/yunin_d_radix_sort.h"

const int numParts = 4;

TEST(Parallel_Operations_TBB, Test_Sum_2) {
    ASSERT_EQ(1, 1);
}

TEST(Parallel_Operations_TBB, Test_Sort_With_1000000_Random_Elements) {
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
//TEST(Parallel_Operations_TBB, Test_Sum_3) {
//    ASSERT_EQ(1, 1);
//}
//
//TEST(Parallel_Operations_TBB, Test_Sum_2) {
//    ASSERT_EQ(1, 1);
//}

//TEST(Parallel_Operations_TBB, Test_Sum) {
//    std::vector<int> vec = getRandomVector(100);
//    int sequential_sum = getSequentialOperations(vec, "+");
//    int parallel_sum = getParallelOperations(vec, "+");
//    ASSERT_EQ(sequential_sum, parallel_sum);
//}
//
//TEST(Parallel_Operations_TBB, Test_Diff) {
//    std::vector<int> vec = getRandomVector(100);
//    int sequential_diff = getSequentialOperations(vec, "-");
//    int parallel_diff = getParallelOperations(vec, "-");
//    ASSERT_EQ(sequential_diff, parallel_diff);
//}
//
//TEST(Parallel_Operations_TBB, Test_Diff_2) {
//    std::vector<int> vec = getRandomVector(50);
//    int sequential_diff = getSequentialOperations(vec, "-");
//    int parallel_diff = getParallelOperations(vec, "-");
//    ASSERT_EQ(sequential_diff, parallel_diff);
//}
//
//TEST(Parallel_Operations_TBB, Test_Mult) {
//    std::vector<int> vec = getRandomVector(10);
//    int sequential_mult = getSequentialOperations(vec, "*");
//    int parallel_mult = getParallelOperations(vec, "*");
//    ASSERT_EQ(sequential_mult, parallel_mult);
//}
//
//TEST(Parallel_Operations_TBB, Test_Mult_2) {
//    std::vector<int> vec = getRandomVector(5);
//    int sequential_mult = getSequentialOperations(vec, "*");
//    int parallel_mult = getParallelOperations(vec, "*");
//    ASSERT_EQ(sequential_mult, parallel_mult);
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
