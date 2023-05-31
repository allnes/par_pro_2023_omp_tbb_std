// Copyright 2023 Bykova Aleksandra
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include "./multiply_matrix_fox.h"

TEST(Multiply_Matrix_Fox, Can_Multiplicate_Do_Properly_With_Wrong_Matrix) {
    matrix a;
    matrix b;
    uint aColSize = 2;
    uint aRowSize = 2;
    uint bRowSize = 3;  // bRow!=aCol

    a.resize(aRowSize);
    b.resize(bRowSize);
    for (uint i = 0; i < a.size(); i++) {
        a[i].resize(aColSize);
    }

    EXPECT_FALSE(canMultiplicate(a, b));
}

TEST(Multiply_Matrix_Fox, Can_Multiplicate_Do_Properly_With_Good_Matrix) {
    matrix a;
    matrix b;
    uint aColSize = 2;
    uint aRowSize = 2;
    uint bRowSize = 2;  // bRow==aCol

    a.resize(aRowSize);
    b.resize(bRowSize);
    for (uint i = 0; i < a.size(); i++) {
        a[i].resize(aColSize);
    }

    EXPECT_TRUE(canMultiplicate(a, b));
}

TEST(Multiply_Matrix_Fox, Prepare_Out_Matrix_Works_Properly) {
    matrix a;
    uint rowSize = 4;
    uint colSize = 4;
    prepareOutMatrix(&a, rowSize, colSize);

    for (uint i = 0; i < a.size(); i++) {
        for (uint j = 0; j < a[i].size(); j++) {
            EXPECT_DOUBLE_EQ(0, a[i][j]);
        }
    }
}

TEST(Multiply_Matrix_Fox, Can_Init_Matrix_With_Rand_Values) {
    matrix a;
    uint rowSize = 4;
    uint colSize = 4;

    EXPECT_TRUE(initMatrixRand(&a, rowSize, colSize));
}
TEST(Multiply_Matrix_Fox, Can_Multiply_Matrix_With_Simple_Method) {
    matrix a, b;
    matrix res;
    uint rowSize = 2;
    uint colSize = 2;

    prepareOutMatrix(&a, rowSize, colSize);
    prepareOutMatrix(&b, rowSize, colSize);

    for (uint i = 0; i < rowSize; i++) {  // init matrix
        for (uint j = 0; j < colSize; j++) {
            a[i][j] = (i * colSize) + (j + 1);
            b[i][j] = colSize * rowSize - ((i * colSize) + j);
        }
    }

    EXPECT_TRUE(simpleMaxtrixMultiply(a, b, &res));
}
TEST(Multiply_Matrix_Fox, Simple_Multiplication_Works_Properly) {
    matrix a, b;
    matrix expectRes, res;
    uint rowSize = 2;
    uint colSize = 2;

    prepareOutMatrix(&expectRes, rowSize, colSize);
    prepareOutMatrix(&a, rowSize, colSize);
    prepareOutMatrix(&b, rowSize, colSize);

    expectRes[0][0] = 8;
    expectRes[0][1] = 5;
    expectRes[1][0] = 20;
    expectRes[1][1] = 13;

    for (uint i = 0; i < rowSize; i++) {  // init matrix
        for (uint j = 0; j < colSize; j++) {
            a[i][j] = (i * colSize) + (j + 1);
            b[i][j] = colSize * rowSize - ((i * colSize) + j);
        }
    }

    simpleMaxtrixMultiply(a, b, &res);

    for (uint i = 0; i < rowSize; i++) {
        for (uint j = 0; j < colSize; j++) {
            EXPECT_DOUBLE_EQ(expectRes[i][j], res[i][j]);
        }
    }
}

TEST(Multiply_Matrix_Fox, Can_Use_Fox_Alg_Works_Right_With_Not_Square_Matrix) {
    matrix a, b;
    uint rowSize = 2;
    uint colSize = 3;

    prepareOutMatrix(&a, rowSize, colSize);
    prepareOutMatrix(&b, rowSize, colSize);

    EXPECT_FALSE(isSquareMatrix(a, b));
}

TEST(Multiply_Matrix_Fox, Can_Use_Fox_Alg_Works_Right_With_Square_Matrix) {
    matrix a, b;
    uint rowSize = 3;
    uint colSize = 3;

    prepareOutMatrix(&a, rowSize, colSize);
    prepareOutMatrix(&b, rowSize, colSize);

    EXPECT_TRUE(isSquareMatrix(a, b));
}

TEST(Multiply_Matrix_Fox, Fox_Alg_Matrix_Mult_Seq_Works_Properly) {
    matrix a, b;
    matrix expectRes, res;
    uint matrixSize = 2;

    prepareOutMatrix(&expectRes, matrixSize, matrixSize);
    prepareOutMatrix(&res, matrixSize, matrixSize);
    prepareOutMatrix(&a, matrixSize, matrixSize);
    prepareOutMatrix(&b, matrixSize, matrixSize);

    expectRes[0][0] = 8;
    expectRes[0][1] = 5;
    expectRes[1][0] = 20;
    expectRes[1][1] = 13;

    for (uint i = 0; i < matrixSize; i++) {  // init matrix
        for (uint j = 0; j < matrixSize; j++) {
            a[i][j] = (i * matrixSize) + (j + 1);
            b[i][j] = matrixSize * matrixSize - ((i * matrixSize) + j);
        }
    }

    algFoxMatrixMultiplySeq(a, b, &res);

    for (uint i = 0; i < matrixSize; i++) {
        for (uint j = 0; j < matrixSize; j++) {
            EXPECT_NEAR(expectRes[i][j], res[i][j], 0.01);
        }
    }
}

TEST(Multiply_Matrix_Fox, Fox_Alg_Matrix_Mult_Seq_Works_Properly_Rand) {
    matrix a, b;
    matrix expectRes, res;
    uint matrixSize = 12;

    prepareOutMatrix(&expectRes, matrixSize, matrixSize);
    initMatrixRand(&a, matrixSize, matrixSize);
    initMatrixRand(&b, matrixSize, matrixSize);

    simpleMaxtrixMultiply(a, b, &expectRes);

    algFoxMatrixMultiplySeq(a, b, &res);



    for (uint i = 0; i < matrixSize; i++) {
        for (uint j = 0; j < matrixSize; j++) {
            EXPECT_NEAR(expectRes[i][j], res[i][j], 1e-3);
        }
    }
}

TEST(Multiply_Matrix_Fox, Fox_Alg_Matrix_Mult_Par_Works_Properly) {
    matrix a, b;
    matrix expectRes, res;
    uint matrixSize = 2;

    prepareOutMatrix(&expectRes, matrixSize, matrixSize);
    prepareOutMatrix(&res, matrixSize, matrixSize);
    prepareOutMatrix(&a, matrixSize, matrixSize);
    prepareOutMatrix(&b, matrixSize, matrixSize);

    expectRes[0][0] = 8;
    expectRes[0][1] = 5;
    expectRes[1][0] = 20;
    expectRes[1][1] = 13;

    for (uint i = 0; i < matrixSize; i++) {  // init matrix
        for (uint j = 0; j < matrixSize; j++) {
            a[i][j] = (i * matrixSize) + (j + 1);
            b[i][j] = matrixSize * matrixSize - ((i * matrixSize) + j);
        }
    }

    algFoxMatrixMultiplyPar(a, b, &res);

    for (uint i = 0; i < matrixSize; i++) {
        for (uint j = 0; j < matrixSize; j++) {
            EXPECT_NEAR(expectRes[i][j], res[i][j], 0.01);
        }
    }
}
TEST(Multiply_Matrix_Fox, Fox_Alg_Matrix_Mult_Par_Works_Properly_Rand) {
    matrix a, b;
    matrix expectRes, res;
    uint matrixSize = 12;

    prepareOutMatrix(&expectRes, matrixSize, matrixSize);
    initMatrixRand(&a, matrixSize, matrixSize);
    initMatrixRand(&b, matrixSize, matrixSize);

    simpleMaxtrixMultiply(a, b, &expectRes);

    algFoxMatrixMultiplyPar(a, b, &res);

    for (uint i = 0; i < matrixSize; i++) {
        for (uint j = 0; j < matrixSize; j++) {
            EXPECT_NEAR(expectRes[i][j], res[i][j], 1e-3);
        }
    }
}
int main(int argc, char** argv) {
    tbb::task_scheduler_init init(NTHREADS);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
