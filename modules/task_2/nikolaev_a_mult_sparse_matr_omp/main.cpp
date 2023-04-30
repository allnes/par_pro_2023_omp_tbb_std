// Copyright 2023 Nikolaev Alexander
#include <gtest/gtest.h>
#include <omp.h>
#include <algorithm>
#include "./sparse_matrix.h"

TEST(Sparse_Matrix_Mult, Test_Mult1) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix resSeq;
    CCSMatrix resPar;
    A = GetRandomMatrix(8, 8, 20);
    B = GetRandomMatrix(8, 8, 20);
    A = TransposeMatrix(A);

    resSeq = GetMultiplicateSequential(A, B);
    resPar = GetMultiplicateParallel(A, B);

    ASSERT_EQ(resSeq.value, resPar.value);
}

TEST(Sparse_Matrix_Mult, Test_Mult2) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix resSeq;
    CCSMatrix resPar;
    A = GetRandomMatrix(16, 16, 20);
    B = GetRandomMatrix(16, 16, 20);
    A = TransposeMatrix(A);

    resSeq = GetMultiplicateSequential(A, B);
    resPar = GetMultiplicateParallel(A, B);

    ASSERT_EQ(resSeq.value, resPar.value);
}

TEST(Sparse_Matrix_Mult, Test_Mult3) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix resSeq;
    CCSMatrix resPar;
    A = GetRandomMatrix(40, 40, 30);
    B = GetRandomMatrix(40, 40, 30);
    A = TransposeMatrix(A);

    resSeq = GetMultiplicateSequential(A, B);
    resPar = GetMultiplicateParallel(A, B);

    ASSERT_EQ(resSeq.value, resPar.value);
}

TEST(Sparse_Matrix_Mult, Test_Mult4) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix resSeq;
    CCSMatrix resPar;
    A = GetRandomMatrix(80, 80, 40);
    B = GetRandomMatrix(80, 80, 40);
    A = TransposeMatrix(A);

    resSeq = GetMultiplicateSequential(A, B);
    resPar = GetMultiplicateParallel(A, B);

    ASSERT_EQ(resSeq.value, resPar.value);
}

TEST(Sparse_Matrix_Mult, Test_Mult5) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix resSeq;
    CCSMatrix resPar;
    A = GetRandomMatrix(120, 120, 60);
    B = GetRandomMatrix(120, 120, 60);
    A = TransposeMatrix(A);

    resSeq = GetMultiplicateSequential(A, B);
    resPar = GetMultiplicateParallel(A, B);

    ASSERT_EQ(resSeq.value, resPar.value);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
