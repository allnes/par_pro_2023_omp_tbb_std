// Copyright 2023 Tuzhilkina Polina
#include <gtest/gtest.h>
#include "./strassen.h"

void ExpectNear(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() != vec2.size()) throw "Unequal dimensions";
    for (std::size_t i = 0; i < vec1.size(); i++)
        EXPECT_NEAR(vec1[i], vec2[i], 0.0001);
}

// Testing on 1 x 1 non-random matrices
TEST(TestsStrassenTBB, TestsStrassenTBB_1) {
    int n = 1;
    std::vector<double> A = {2.0};
    std::vector<double> B = {3.0};

    std::vector<double> C = {6.0};
    std::vector<double> CStrassenTBB = tbbStrassenMultiply(A, B, n);

    ExpectNear(C, CStrassenTBB);
}

// Testing on 2 x 2 non-random matrices
TEST(TestsStrassenTBB, TestsStrassenTBB_2) {
    int n = 2;
    std::vector<double> A = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> B = {5.0, 6.0, 7.0, 8.0};

    std::vector<double> C = {19.0, 22.0, 43.0, 50.0};
    std::vector<double> CStrassenTBB = tbbStrassenMultiply(A, B, n);

    ExpectNear(C, CStrassenTBB);
}

// Testing on 4 x 4 random matrices
TEST(TestsStrassenTBB, TestsStrassenTBB_3) {
    int n = 4;
    std::vector<double> A = genRandomVector(n * n);
    std::vector<double> B = genRandomVector(n * n);

    std::vector<double> C = usualMultiply(A, B, n);
    std::vector<double> CStrassenTBB = tbbStrassenMultiply(A, B, n);

    ExpectNear(C, CStrassenTBB);
}

// Testing on 8 x 8 random matrices
TEST(TestsStrassenTBB, TestsStrassenTBB_4) {
    int n = 8;
    std::vector<double> A = genRandomVector(n * n);
    std::vector<double> B = genRandomVector(n * n);

    std::vector<double> C = usualMultiply(A, B, n);
    std::vector<double> CStrassenTBB = tbbStrassenMultiply(A, B, n);

    ExpectNear(C, CStrassenTBB);
}

// Testing on 16 x 16 random matrices
TEST(TestsStrassenTBB, TestsStrassenTBB_5) {
    int n = 16;
    std::vector<double> A = genRandomVector(n * n);
    std::vector<double> B = genRandomVector(n * n);

    std::vector<double> C = usualMultiply(A, B, n);
    std::vector<double> CStrassenTBB = tbbStrassenMultiply(A, B, n);

    ExpectNear(C, CStrassenTBB);
}


// Testing on 256 x 256 random matrices
/* TEST(TestsStrassenTBB, TestsStrassenTBB_6) {
    int n = 256;
    std::vector<double> A = genRandomVector(n * n);
    std::vector<double> B = genRandomVector(n * n);

    auto seq_t1 = tbb::tick_count::now();
    std::vector<double> CStrassen = seqStrassenMultiply(A, B, n);
    auto seq_t2 = tbb::tick_count::now();

    auto tbb_t1 = tbb::tick_count::now();
    std::vector<double> CStrassenTBB = tbbStrassenMultiply(A, B, n);
    auto tbb_t2 = tbb::tick_count::now();

    std::cout << "Sequential time: " << (seq_t2 - seq_t1).seconds() << '\n';
    std::cout << "TBB parallel time: " << (tbb_t2 - tbb_t1).seconds() << '\n';

    ExpectNear(CStrassen, CStrassenTBB);
} */
