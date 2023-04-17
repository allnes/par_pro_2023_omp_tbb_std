// Copyright 2023 Yurin Evgeny

#include <gtest/gtest.h>

#include "../../../modules/task_3/yurin_e_slau_gradient_tbb/slau_gradient.h"

void GoogleAssertNear(dvec a, dvec b, double eps) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            ASSERT_NEAR(a[i], b[i], eps);
        }
    }
}

TEST(Sequential, Test_1) {
    dmat randomMatrix = generateMatrix(1, 1111);
    dvec randomAnswer = generateVector(1, 2222);
    dvec matrixFromRandom = matrix_vec(randomMatrix, randomAnswer);
    dvec answer = solve(randomMatrix, matrixFromRandom);
    GoogleAssertNear(answer, randomAnswer, EPS);
}

TEST(Sequential, Test_2) {
    dmat randomMatrix = generateMatrix(3, 555);
    dvec randomAnswer = generateVector(3, 444);
    dvec matrixFromRandom = matrix_vec(randomMatrix, randomAnswer);
    dvec answer = solve(randomMatrix, matrixFromRandom);
    GoogleAssertNear(answer, randomAnswer, EPS);
}

TEST(Sequential, Test_3) {
    dmat randomMatrix = generateMatrix(6, 666);
    dvec randomAnswer = generateVector(6, 777);
    dvec matrixFromRandom = matrix_vec(randomMatrix, randomAnswer);
    dvec answer = solve(randomMatrix, matrixFromRandom);
    GoogleAssertNear(answer, randomAnswer, EPS);
}

TEST(Sequential, Test_4) {
    dmat randomMatrix = generateMatrix(10, 1234);
    dvec randomAnswer = generateVector(10, 54352);
    dvec matrixFromRandom = matrix_vec(randomMatrix, randomAnswer);
    dvec answer = solve(randomMatrix, matrixFromRandom);
    GoogleAssertNear(answer, randomAnswer, EPS);
}

TEST(Sequential, Test_5) {
    dmat randomMatrix = generateMatrix(100, 111);
    dvec randomAnswer = generateVector(100, 222);
    dvec matrixFromRandom = matrix_vec(randomMatrix, randomAnswer);
    dvec answer = solve(randomMatrix, matrixFromRandom);
    GoogleAssertNear(answer, randomAnswer, EPS);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
