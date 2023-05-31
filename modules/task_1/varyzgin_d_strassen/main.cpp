// Copyright 2023 Selivankin Sergey
#include <gtest/gtest.h>
#include <vector>
#include "./strassen.h"

TEST(strassen, Test_0) {
    std::vector<double> matA = { 2, 2, 2,
                                 3, 3, 3,
                                 4, 4, 4 };
    std::vector<double> matB = { 2, 2, 2,
                                 3, 3, 3,
                                 4, 4, 4 };
    std::vector<double> result = { 18, 18, 18, 0,
                                   27, 27, 27, 0,
                                   36, 36, 36, 0,
                                   0, 0, 0, 0};

    int new_size = getNewSize(3, 3, 3, 3);
    std::vector<double> a = appendZeros(matA, 3, 3, new_size);
    std::vector<double> b = appendZeros(matB, 3, 3, new_size);

    ASSERT_EQ(getStrassenSequence(a, b), result);
}

TEST(strassen, Test_1) {
    std::vector<double> matA = { 2, 2,
                                 3, 3 };
    std::vector<double> matB = { 2, 2,
                                 3, 3 };
    std::vector<double> result = { 10, 10,
                                   15, 15 };

    int new_size = getNewSize(2, 2, 2, 2);
    std::vector<double> a = appendZeros(matA, 2, 2, new_size);
    std::vector<double> b = appendZeros(matB, 2, 2, new_size);

    ASSERT_EQ(getStrassenSequence(a, b), result);
}

TEST(strassen, Test_2) {
    std::vector<double> matA = { 2, 2, 2};
    std::vector<double> matB = { 2, 2, 2,
                                 3, 3, 3,
                                 4, 4, 4 };
    std::vector<double> result = { 18, 18, 18, 0,
                                   0, 0, 0, 0,
                                   0, 0, 0, 0,
                                   0, 0, 0, 0};

    int new_size = getNewSize(1, 3, 3, 3);
    std::vector<double> a = appendZeros(matA, 1, 3, new_size);
    std::vector<double> b = appendZeros(matB, 3, 3, new_size);

    ASSERT_EQ(getStrassenSequence(a, b), result);
}

TEST(strassen, Test_3) {
    std::vector<double> matA = { 2, 2, 2};
    std::vector<double> matB = { 2,
                                 3,
                                 4};
    std::vector<double> result = { 18, 0, 0, 0,
                                   0, 0, 0, 0,
                                   0, 0, 0, 0,
                                   0, 0, 0, 0};

    int new_size = getNewSize(1, 3, 3, 1);
    std::vector<double> a = appendZeros(matA, 1, 3, new_size);
    std::vector<double> b = appendZeros(matB, 3, 1, new_size);

    ASSERT_EQ(getStrassenSequence(a, b), result);
}

TEST(strassen, Test_4) {
    std::vector<double> matA = { 2, 2, 2,
                                 3, 3, 3};
    std::vector<double> matB = { 2, 2,
                                 3, 3,
                                 4, 4};
    std::vector<double> result = { 18, 18, 0, 0,
                                   27, 27, 0, 0,
                                   0, 0, 0, 0,
                                   0, 0, 0, 0};

    int new_size = getNewSize(2, 3, 3, 2);
    std::vector<double> a = appendZeros(matA, 2, 3, new_size);
    std::vector<double> b = appendZeros(matB, 3, 2, new_size);

    ASSERT_EQ(getStrassenSequence(a, b), result);
}
