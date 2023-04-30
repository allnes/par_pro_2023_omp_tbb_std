// Copyright 2023 Shvandyreva Alina
#include <gtest/gtest.h>
#include "./fox_algorithm_omp.h"

TEST(OMP_Mult, SimpleTest) {
    matrix A = { {2} };
    matrix B = { {3} };
    matrix expected = seq_multiply(A, B);
    matrix res = omp_multiply(A, B, 1);
    for (int i = 0; i < expected.size(); i++) {
        for (int j = 0; j < expected[0].size(); j++) {
            ASSERT_NEAR(res[i][j], expected[i][j], 0.001);
        }
    }
}

TEST(OMP_Mult, Test_Long_By_Wide_1x1t) {
    matrix A = { {1}, {2}, {3}, {4}, {5}, {6} };
    matrix B = { {6, 5, 4, 3, 2, 1} };
    matrix expected = seq_multiply(A, B);
    matrix res = omp_multiply(A, B, 1);
    for (int i = 0; i < expected.size(); i++) {
        for (int j = 0; j < expected[0].size(); j++) {
            ASSERT_NEAR(res[i][j], expected[i][j], 0.001);
        }
    }
}

TEST(OMP_Mult, Test_Quad_By_Quad_3x3t) {
    matrix A = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    matrix B = { {10, 11, 12}, {13, 14, 15}, {16, 17, 18} };
    matrix expected = seq_multiply(A, B);
    matrix res = omp_multiply(A, B, 3);
    for (int i = 0; i < expected.size(); i++) {
        for (int j = 0; j < expected[0].size(); j++) {
            ASSERT_NEAR(res[i][j], expected[i][j], 0.001);
        }
    }
}

TEST(OMP_Mult, Any_By_Identity_4x4t) {
    matrix A = generate_matrix(4, 4);
    matrix E = generate_identity_matrix(4);
    matrix expected = A;
    matrix res = omp_multiply(A, E, 4);
    for (int i = 0; i < expected.size(); i++) {
        for (int j = 0; j < expected[0].size(); j++) {
            ASSERT_NEAR(res[i][j], expected[i][j], 0.001);
        }
    }
}

TEST(OMP_Mult, Random_16x16_by_16x16) {
    matrix A = generate_matrix(16, 16);
    matrix B = generate_matrix(16, 16);
    matrix expected = seq_multiply(A, B);
    matrix res = omp_multiply(A, B, 4);
    for (int i = 0; i < expected.size(); i++) {
        for (int j = 0; j < expected[0].size(); j++) {
            ASSERT_NEAR(res[i][j], expected[i][j], 0.001);
        }
    }
}
