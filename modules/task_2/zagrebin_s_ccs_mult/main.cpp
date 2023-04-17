// Copyright 2023 Zagrebin S.
#include <gtest/gtest.h>
#include <random>
#include "../../../modules/task_2/zagrebin_s_ccs_mult/ccs_mult.h"

TEST(zagrebin_ccs_seq, Test_Fixed) {
    Comp x[] = {0, 0, 3,
               -1, 0, 0};

    Comp y[] = {-3, 0,
               3, 0,
               0, -1};

    CCS m1(2, 3, x);
    CCS m2(3, 2, y);
    CCS m3(2, 2);
    m3 = mult(m1, m2);  // 0 -3 \ 3 0
    Comp ans[] = {3, -3};

    EXPECT_EQ(m3.data.size(), sizeof(ans) / sizeof(Comp));
    for (size_t i = 0; i < m3.data.size(); ++i)
        EXPECT_NEAR(std::abs(m3.data[i].val - ans[i]), 0, 0.0001);
}

TEST(zagrebin_ccs_seq, Test_Zero) {
    Comp x[] = {0, 0, 3,
                0, 0, 0};

    Comp y[] = {-3, 0,
                3, 1,
                0, 0};

    CCS m1(2, 3, x);
    CCS m2(3, 2, y);
    CCS m3(2, 2);
    m3 = mult(m1, m2);  // 0 0 \ 0 0

    EXPECT_EQ(m3.data.size(), 0);
}

TEST(zagrebin_ccs_seq, Test_Dense) {
    Comp x[] = {1, 2, 3};

    Comp y[] = {1,
                2,
                3};

    CCS m1(1, 3, x);
    CCS m2(3, 1, y);
    CCS m3(1, 1);
    m3 = mult(m1, m2);  // 14
    Comp ans[] = {14};

    EXPECT_EQ(m3.data.size(), sizeof(ans) / sizeof(Comp));
    for (size_t i = 0; i < m3.data.size(); ++i)
        EXPECT_NEAR(std::abs(m3.data[i].val - ans[i]), 0, 0.0001);
}

TEST(zagrebin_ccs_seq, Test_Big) {
    Comp x[] = {0, 1, 3,
                3, 0, 1,
                1, 3, 0};

    Comp y[] = {9, 0, 1,
                8, 0, 2,
                0, 0, 0};

    CCS m1(3, 3, x);
    CCS m2(3, 3, y);
    CCS m3(3, 3);
    m3 = mult(m1, m2);  // 8 0 2 \ 27 0 3 \ 33 0 7
    Comp ans[] = {8, 27, 33, 2, 3, 7};

    EXPECT_EQ(m3.data.size(), sizeof(ans) / sizeof(Comp));
    for (size_t i = 0; i < m3.data.size(); ++i)
        EXPECT_NEAR(std::abs(m3.data[i].val - ans[i]), 0, 0.0001);
}

TEST(zagrebin_ccs_seq, Test_Random) {
    std::random_device r;
    std::default_random_engine eng(r());
    CCS m1(2, 4);
    CCS m2(4, 2);
    fill(&m1, 0.2, &eng);
    fill(&m2, 0.2, &eng);

    ASSERT_NO_THROW(mult(m1, m2));
}
