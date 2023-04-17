// Copyright 2023 Bushmakin Maksim
#include <gtest/gtest.h>
#include "./shellbatcher.h"

TEST(ShellBatcherTBB, Test_1_EmptyArray) {
    std::size_t vecLength = 0;
    std::vector<int> emptyVec(vecLength);

    shellsortTBB(&emptyVec);

    EXPECT_EQ(emptyVec.size(), 0);
}

TEST(ShellBatcherTBB, Test_2_OneElementArray) {
    std::size_t vecLength = 1;
    std::vector<int> oneElementVec({ 10 });

    shellsortTBB(&oneElementVec);

    EXPECT_EQ(oneElementVec.size(), 1);
    EXPECT_EQ(oneElementVec[0], 10);
}

TEST(ShellBatcherTBB, Test_3_RandomVec_15elements) {
    std::size_t vecLength = 15;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortTBB(&vec);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
}

TEST(ShellBatcherTBB, Test_4_RandomVec_100elements) {
    std::size_t vecLength = 100;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortTBB(&vec);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
}

TEST(ShellBatcherTBB, Test_5_RandomVec_4000elements) {
    std::size_t vecLength = 4000;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortTBB(&vec);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
}

/* TEST(ShellBatcherTBB, Test_6_RandomVec_1000000elements) {
    std::size_t vecLength = 1000000;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    auto t_tbb_1 = tbb::tick_count::now();
    shellsortTBB(&vec);
    auto t_tbb_2 = tbb::tick_count::now();

    auto t_seq_1 = tbb::tick_count::now();
    std::sort(vecCorrect.begin(), vecCorrect.end());
    auto t_seq_2 = tbb::tick_count::now();

    std::cout << "Sequential time: " << (t_seq_2 - t_seq_1).seconds() << "s\n";
    std::cout << "TBB time:        " << (t_tbb_2 - t_tbb_1).seconds() << "s\n";

    EXPECT_EQ(vec, vecCorrect);
} */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
