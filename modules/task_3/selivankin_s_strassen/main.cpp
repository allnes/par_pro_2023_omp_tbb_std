// Copyright 2023 Selivankin Sergey
#include <gtest/gtest.h>
#include <vector>
#include "./strassen.h"

TEST(strassen_tbb, Test_0) {
    int m1 = 5, n1 = 5;
    int m2 = n1, n2 = 5;
    std::vector<double> A = getRandomMatrix(m1, n1);
    std::vector<double> B = getRandomMatrix(m2, n2);

    ASSERT_EQ(getStrassenSequence(A, B, m1, n1, m2, n2),
            getStrassenParallel(A, B, m1, n1, m2, n2));
}

TEST(strassen_tbb, Test_1) {
    int m1 = 10, n1 = 10;
    int m2 = n1, n2 = 5;
    std::vector<double> A = getRandomMatrix(m1, n1);
    std::vector<double> B = getRandomMatrix(m2, n2);

    ASSERT_EQ(getStrassenSequence(A, B, m1, n1, m2, n2),
              getStrassenParallel(A, B, m1, n1, m2, n2));
}

TEST(strassen_tbb, Test_2) {
    int m1 = 1, n1 = 10;
    int m2 = n1, n2 = 1;
    std::vector<double> A = getRandomMatrix(m1, n1);
    std::vector<double> B = getRandomMatrix(m2, n2);

    ASSERT_EQ(getStrassenSequence(A, B, m1, n1, m2, n2),
              getStrassenParallel(A, B, m1, n1, m2, n2));
}

TEST(strassen_tbb, Test_3) {
    int m1 = 20, n1 = 30;
    int m2 = n1, n2 = 5;
    std::vector<double> A = getRandomMatrix(m1, n1);
    std::vector<double> B = getRandomMatrix(m2, n2);

    ASSERT_EQ(getStrassenSequence(A, B, m1, n1, m2, n2),
              getStrassenParallel(A, B, m1, n1, m2, n2));
}

TEST(strassen_tbb, Test_4) {
    int m1 = 1, n1 = 10;
    int m2 = n1, n2 = 20;
    std::vector<double> A = getRandomMatrix(m1, n1);
    std::vector<double> B = getRandomMatrix(m2, n2);

    ASSERT_EQ(getStrassenSequence(A, B, m1, n1, m2, n2),
              getStrassenParallel(A, B, m1, n1, m2, n2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
