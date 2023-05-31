// Copyright 2023 Varyzgin Dmitry
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "./strassen.h"

// eq with smth accuracy
void eq(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() != vec2.size()) throw "non equal dimentions";
    for (std::size_t i = 0; i < vec1.size(); i++)
        EXPECT_NEAR(vec1[i], vec2[i], 0.0001);
}

TEST(TestsStrassenSeq, Test1on1) {
    int n = 1;
    std::vector<double> A = {2.0};
    std::vector<double> B = {3.0};

    std::vector<double> C = {6.0};
    std::vector<double> CStrassen = strassen(A, B, n);

    eq(C, CStrassen);
}

TEST(TestsStrassenSeq, Test2on2) {
    int n = 2;
    // our values
    std::vector<double> A = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> B = {5.0, 6.0, 7.0, 8.0};

    std::vector<double> C = {19.0, 22.0, 43.0, 50.0};
    std::vector<double> Strassen = strassen(A, B, n);

    eq(C, Strassen);
}

TEST(TestsStrassenSeq, Test4on4) {
    int n = 4;
    std::vector<double> A = genVec(n * n);
    std::vector<double> B = genVec(n * n);

    std::vector<double> C = mult(A, B, n);
    std::vector<double> Strassen = strassen(A, B, n);

    eq(C, Strassen);
}

TEST(TestsStrassenSeq, Test8on8) {
    int n = 8;
    std::vector<double> A = genVec(n * n);
    std::vector<double> B = genVec(n * n);

    std::vector<double> C = mult(A, B, n);
    std::vector<double> Strassen = strassen(A, B, n);

    eq(C, Strassen);
}

TEST(TestsStrassenSeq, Test16on16) {
    int n = pow(2, 4);
    std::vector<double> A = genVec(n * n);
    std::vector<double> B = genVec(n * n);

    std::vector<double> C = mult(A, B, n);
    std::vector<double> Strassen = strassen(A, B, n);

    eq(C, Strassen);
}
