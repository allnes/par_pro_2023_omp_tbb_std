// Copyright 2023 Selivankin Sergey
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "./strassen.h"

void ExpectNear(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() != vec2.size()) throw "Unequal dimensions";
    for (std::size_t i = 0; i < vec1.size(); i++)
        EXPECT_NEAR(vec1[i], vec2[i], 0.0001);
}

// Testing on 1 x 1 non-random matrices
TEST(TestsStrassenSeq, TestsStrassenSeq_1) {
    int n = 1;
    std::vector<double> A = {2.0};
    std::vector<double> B = {3.0};

    std::vector<double> C = {6.0};
    std::vector<double> CStrassen = strassenMultiply(A, B, n);

    ExpectNear(C, CStrassen);
}

// Testing on 2 x 2 non-random matrices
TEST(TestsStrassenSeq, TestsStrassenSeq_2) {
    int n = 2;
    std::vector<double> A = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> B = {5.0, 6.0, 7.0, 8.0};

    std::vector<double> C = {19.0, 22.0, 43.0, 50.0};
    std::vector<double> CStrassen = strassenMultiply(A, B, n);

    // printMatrix(CStrassen, n);

    ExpectNear(C, CStrassen);
}

// Testing on 4 x 4 random matrices
TEST(TestsStrassenSeq, TestsStrassenSeq_3) {
    int n = 4;
    std::vector<double> A = genRandomVector(n * n);
    std::vector<double> B = genRandomVector(n * n);

    std::vector<double> C = usualMultiply(A, B, n);
    std::vector<double> CStrassen = strassenMultiply(A, B, n);

    ExpectNear(C, CStrassen);
}

// Testing on 8 x 8 random matrices
TEST(TestsStrassenSeq, TestsStrassenSeq_4) {
    int n = 8;
    std::vector<double> A = genRandomVector(n * n);
    std::vector<double> B = genRandomVector(n * n);

    std::vector<double> C = usualMultiply(A, B, n);
    std::vector<double> CStrassen = strassenMultiply(A, B, n);

    ExpectNear(C, CStrassen);
}

// Testing on 16 x 16 random matrices
TEST(TestsStrassenSeq, TestsStrassenSeq_5) {
    int n = pow(2, 4);
    std::vector<double> A = genRandomVector(n * n);
    std::vector<double> B = genRandomVector(n * n);

    std::vector<double> C = usualMultiply(A, B, n);
    std::vector<double> CStrassen = strassenMultiply(A, B, n);

    ExpectNear(C, CStrassen);
}
