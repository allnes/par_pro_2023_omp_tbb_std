// Copyright 2023 Grachev Valentin
#include <gtest/gtest.h>
#include "../../../modules/task_2/grachev_v_mult_rare_matrix/mult_rare_matrix.h"

TEST(Mult_rare_matrix_parallel, Test_1_2x2_and_2x2) {
    MatrixCRS matr(2, 2);
    matr.FillRandom(2);

    MatrixCRS matr2(2, 2);
    matr2.FillRandom(2);

    MatrixCRS res = matr.Multiple(matr2);
    MatrixCRS resPar = matr.MultipleParallel(matr2);


    EXPECT_EQ(res.Equal(resPar), true);
}

TEST(Mult_rare_matrix_parallel, Test_2_3x5_and_5x3) {
    MatrixCRS matr(3, 5);
    matr.FillRandom(2);

    MatrixCRS matr2(5, 3);
    matr2.FillRandom(2);

    MatrixCRS res = matr.Multiple(matr2);
    MatrixCRS resPar = matr.MultipleParallel(matr2);

    EXPECT_EQ(res.Equal(resPar), true);
}

TEST(Mult_rare_matrix_parallel, Test_3_6x6_and_6x6) {
    MatrixCRS matr(6, 6);
    matr.FillRandom(2);

    MatrixCRS matr2(6, 6);
    matr2.FillRandom(2);

    MatrixCRS res = matr.Multiple(matr2);
    MatrixCRS resPar = matr.MultipleParallel(matr2);

    EXPECT_EQ(res.Equal(resPar), true);
}

TEST(Mult_rare_matrix_parallel, Test_4_10x50_and_50x10) {
    MatrixCRS matr(10, 50);
    matr.FillRandom(2);

    MatrixCRS matr2(50, 10);
    matr2.FillRandom(2);

    MatrixCRS res = matr.Multiple(matr2);
    MatrixCRS resPar = matr.MultipleParallel(matr2);

    EXPECT_EQ(res.Equal(resPar), true);
}

TEST(Mult_rare_matrix_parallel, Test_5_25x80_and_80x25) {
    MatrixCRS matr(25, 80);
    matr.FillRandom(2);

    MatrixCRS matr2(80, 25);
    matr2.FillRandom(2);

    MatrixCRS res = matr.Multiple(matr2);
    MatrixCRS resPar = matr.MultipleParallel(matr2);

    EXPECT_EQ(res.Equal(resPar), true);
}
