// Copyright 2023 Bulgakov Daniil


#include <gtest/gtest.h>

#include "../../../modules/task_3/bulgakov_d_slau_gradient_tbb/slau_gradient.h"


const double SML = 1.0e-4;

void GoogleAssertNear(dvec a, dvec b, double smol) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            ASSERT_NEAR(a[i], b[i], smol);
        }
    }
}

TEST(Sequential, Test_1) {
    dmat A =  generateMatrix(10, 423);
    dvec ans = generateVector(10, 234);
    dvec B = matrix_vec(A, ans);
    dvec tbb_solved = tbb_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(tbb_solved, solved, SML);
}

TEST(Sequential, Test_2) {
    dmat A =  generateMatrix(50, 243);
    dvec ans = generateVector(50, 423);
    dvec B = matrix_vec(A, ans);
    dvec tbb_solved = tbb_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(tbb_solved, solved, SML);
}

TEST(Sequential, Test_3) {
    dmat A =  generateMatrix(100, 4442);
    dvec ans = generateVector(100, 2444);
    dvec B = matrix_vec(A, ans);
    dvec tbb_solved = tbb_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(tbb_solved, solved, SML);
}

TEST(Sequential, Test_4) {
    dmat A =  generateMatrix(200, 15);
    dvec ans = generateVector(200, 51);
    dvec B = matrix_vec(A, ans);
    dvec tbb_solved = tbb_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(tbb_solved, solved, SML);
}

TEST(Sequential, Test_5) {
    dmat A =  generateMatrix(500, 155);
    dvec ans = generateVector(500, 551);
    dvec B = matrix_vec(A, ans);
    dvec tbb_solved = tbb_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(tbb_solved, solved, SML);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
