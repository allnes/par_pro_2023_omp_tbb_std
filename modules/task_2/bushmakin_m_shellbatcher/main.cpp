// Copyright 2023 Bushmakin Maksim
#include <gtest/gtest.h>
#include "./shellbatcher.h"

TEST(ShellBatcherOMP, Test_1_EmptyArray) {
    std::size_t vecLength = 0;
    std::vector<int> emptyVec(vecLength);

    shellsortOpenMP(&emptyVec);

    EXPECT_EQ(emptyVec.size(), 0);
}

TEST(ShellBatcherOMP, Test_2_OneElementArray) {
    std::size_t vecLength = 1;
    std::vector<int> oneElementVec({ 10 });

    shellsortOpenMP(&oneElementVec);

    EXPECT_EQ(oneElementVec.size(), 1);
    EXPECT_EQ(oneElementVec[0], 10);
}

TEST(ShellBatcherOMP, Test_3_RandomVec_15elements) {
    std::size_t vecLength = 15;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortOpenMP(&vec);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
}

TEST(ShellBatcherOMP, Test_4_RandomVec_100elements) {
    std::size_t vecLength = 100;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortOpenMP(&vec);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
}

TEST(ShellBatcherOMP, Test_5_RandomVec_4000elements) {
    std::size_t vecLength = 4000;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortOpenMP(&vec);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
}

/* TEST(ShellBatcherOMP, Test_6_RandomVec_1000000elements) {
    std::size_t vecLength = 1000000;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    double t_omp_1 = omp_get_wtime();
    shellsortOpenMP(&vec);
    double t_omp_2 = omp_get_wtime();

    double t_seq_1 = omp_get_wtime();
    std::sort(vecCorrect.begin(), vecCorrect.end());
    double t_seq_2 = omp_get_wtime();

    std::cout << "Sequential time: " << (t_seq_2 - t_seq_1) << "s\n";
    std::cout << "OMP time:        " << (t_omp_2 - t_omp_1) << "s\n";

    EXPECT_EQ(vec, vecCorrect);
} */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
