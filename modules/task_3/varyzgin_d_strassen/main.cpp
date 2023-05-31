// Copyright 2023 Varyzgin Dmitry
#include <gtest/gtest.h>
#include "./strassen.h"

// eq with smth accuracy
void eq(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() != vec2.size()) throw "non equal dimentions";
    for (std::size_t i = 0; i < vec1.size(); i++)
        EXPECT_NEAR(vec1[i], vec2[i], 0.0001);
}

TEST(TestsStrassenTBB, Test1on1TBB) {
    int n = 1;
    std::vector<double> A = {2.0};
    std::vector<double> B = {3.0};

    std::vector<double> C = {6.0};
    std::vector<double> StrassenTBB = strassenTbb(A, B, n);

    eq(C, StrassenTBB);
}

TEST(TestsStrassenTBB, Test2on2TBB) {
    int n = 2;
    std::vector<double> A = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> B = {5.0, 6.0, 7.0, 8.0};

    std::vector<double> C = {19.0, 22.0, 43.0, 50.0};
    std::vector<double> StrassenTBB = strassenTbb(A, B, n);

    eq(C, StrassenTBB);
}

TEST(TestsStrassenTBB, Test4on4TBB) {
    int n = 4;
    std::vector<double> A = genVec(n * n);
    std::vector<double> B = genVec(n * n);

    std::vector<double> C = mult(A, B, n);
    std::vector<double> StrassenTBB = strassenTbb(A, B, n);

    eq(C, StrassenTBB);
}

TEST(TestsStrassenTBB, Test8on8TBB) {
    int n = 8;
    std::vector<double> A = genVec(n * n);
    std::vector<double> B = genVec(n * n);

    std::vector<double> C = mult(A, B, n);
    std::vector<double> StrassenTBB = strassenTbb(A, B, n);

    eq(C, StrassenTBB);
}

TEST(TestsStrassenTBB, Test16on16TBB) {
    int n = 16;
    std::vector<double> A = genVec(n * n);
    std::vector<double> B = genVec(n * n);

    std::vector<double> C = mult(A, B, n);
    std::vector<double> StrassenTBB = strassenTbb(A, B, n);

    eq(C, StrassenTBB);
}
