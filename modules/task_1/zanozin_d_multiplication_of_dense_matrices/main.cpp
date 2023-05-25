// Copyright 2023 Zanozin Danila
#include <gtest/gtest.h>

#include <vector>

#include "./multiplication_of_dense_matrices.h"

TEST(MatrixCannonMult, CorrectCompareMatrices) {
  matrix A = {{1.5, 1.7}, {3.789, 37.8}, {12.1234, 2.0}};
  matrix B = {{1.5, 1.7}, {3.789, 37.8}, {12.1234, 2.0}};

  ASSERT_TRUE(CompareMatrices(A, B));
}

TEST(MatrixCannonMult, CorrectCompareDifferentMatrices) {
  matrix A = RandomMat(3);
  matrix B = RandomMat(3);

  ASSERT_FALSE(CompareMatrices(A, B));
}

TEST(MatrixCannonMult, ThrowsWhenNaiveMultWithDifferentSize) {
  matrix A = RandomMat(3);
  matrix B = RandomMat(5);

  ASSERT_ANY_THROW(NaiveMult(A, B));
}

TEST(MatrixCannonMult, CorrectResultOfTheNaiveMultplication) {
  matrix A = {{1.5, 1.7, 2.5}, {3.7, 37.8, 2.5}, {12.1, 2.0, 2.5}};
  matrix B = {{1.5, 1.7, 3.2}, {3.7, 27.8, 3.2}, {12.1, 2.0, 3.2}};
  matrix res = {
      {38.79, 54.81, 18.24}, {175.66, 1062.13, 140.8}, {55.8, 81.17, 53.12}};

  ASSERT_TRUE(CompareMatrices(res, NaiveMult(A, B)));
}

TEST(MatrixCannonMult, CorrectResultOfTheBlockMultplication) {
  matrix A = {{1.5, 1.7, 2.5}, {3.7, 37.8, 2.5}, {12.1, 2.0, 2.5}};
  matrix B = {{1.5, 1.7, 3.2}, {3.7, 27.8, 3.2}, {12.1, 2.0, 3.2}};
  matrix res = {
      {38.79, 54.81, 18.24}, {175.66, 1062.13, 140.8}, {55.8, 81.17, 53.12}};

  ASSERT_TRUE(CompareMatrices(res, BlockMult(A, B, 2)));
}

TEST(MatrixCannonMult, MultResultsAreEqual) {
  matrix A = RandomMat(3);
  matrix B = RandomMat(3);

  ASSERT_TRUE(CompareMatrices(NaiveMult(A, B), BlockMult(A, B, 2)));
}
