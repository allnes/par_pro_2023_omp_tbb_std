// Copyright 2023 Kochetov Maksim
#include <gtest/gtest.h>
#include "./shell_batcher.h"

TEST(Shell_batcher_OMP, Test1Empty) {
    std::size_t vecLength = 0;
    std::vector<int> emptyVec(vecLength);
    ShellsortParallel(&emptyVec);
    EXPECT_EQ(emptyVec.size(), 0);
}

TEST(Shell_batcher_OMP, Test2One) {
    std::size_t vecLength = 1;
    std::vector<int> oneElementVec({ 5 });
    ShellsortParallel(&oneElementVec);
    EXPECT_EQ(oneElementVec.size(), 1);
    EXPECT_EQ(oneElementVec[0], 5);
}

TEST(Shell_batcher_OMP, Test3Random30) {
    std::size_t vecLength = 30;
    std::vector<int> vec = GetRandomVec(vecLength);
    std::vector<int> rightAnswer(vec);
    std::sort(rightAnswer.begin(), rightAnswer.end());
    ShellsortParallel(&vec);
    EXPECT_EQ(vec, rightAnswer);
}

TEST(Shell_batcher_OMP, Test4Random100) {
    std::size_t vecLength = 100;
    std::vector<int> vec = GetRandomVec(vecLength);
    std::vector<int> rightAnswer(vec);
    std::sort(rightAnswer.begin(), rightAnswer.end());
    ShellsortParallel(&vec);
    EXPECT_EQ(vec, rightAnswer);
}

TEST(Shell_batcher_OMP, Test5Random3000) {
    std::size_t vecLength = 3000;
    std::vector<int> vec = GetRandomVec(vecLength);
    std::vector<int> rightAnswer(vec);
    std::sort(rightAnswer.begin(), rightAnswer.end());
    ShellsortParallel(&vec);
    EXPECT_EQ(vec, rightAnswer);
}

/* TEST(Shell_batcher_OMP, Test6Random500000) {
    std::size_t vecLength = 500000;
    std::vector<int> vec = GetRandomVec(vecLength);
    std::vector<int> rightAnswer(vec);

    double tSeq_1 = omp_get_wtime();
    std::sort(rightAnswer.begin(), rightAnswer.end());
    double tSeq_2 = omp_get_wtime();

    double tOmp_1 = omp_get_wtime();
    ShellsortParallel(&vec);
    double tOmp_2 = omp_get_wtime();

    std::cout << "std::sort time:    " << (tSeq_2 - tSeq_1) << "s\n";
    std::cout << "Shellbatcher time: " << (tOmp_2 - tOmp_1) << "s\n";

    EXPECT_EQ(vec, rightAnswer);
} */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
