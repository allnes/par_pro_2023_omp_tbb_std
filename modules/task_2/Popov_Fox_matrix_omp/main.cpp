// Copyright 2023 Popov Andrey
#include <gtest/gtest.h>
#include <vector>
#include "./Popov_Fox_matrix_omp.h"

TEST(Fox_Mult, cant_create_matrix_with_negative_size) {
  ASSERT_ANY_THROW(randM(-10));
}

TEST(Fox_Mult, can_create_random_matrix) { ASSERT_NO_THROW(randM(10)); }

TEST(Fox_Mult, cant_do_simple_mult_with_different_size) {
  Matrix X = randM(9);
  Matrix Y = randM(10);

  ASSERT_ANY_THROW(Multipli(X, Y));
}

TEST(Fox_Mult, cant_do_fox_mult_with_different_size) {
  Matrix X = randM(7);
  Matrix Y = randM(9);

  ASSERT_ANY_THROW(MultiplyFox(X, Y, 3));
}

TEST(Fox_Mult, res_simple_mult_is_correct) {
  Matrix X = {{1.1, 1.2, 1.3}, {2.4, 2.5, 2.6}, {3.7, 3.8, 3.9}};
  Matrix Y = {{4.1, 4.2, 4.3}, {5.4, 5.5, 5.6}, {6.7, 6.8, 6.9}};
  Matrix Z = {
      {19.7, 20.06, 20.42}, {40.76, 41.51, 42.26}, {61.82, 62.96, 64.1}};
  Matrix res = Multipli(X, Y);

  for (int k = 0; k < 3; k++) {
    for (int l = 0; l < 3; l++) {
      EXPECT_NEAR(res[k][l], Z[k][l], 0.001);
    }
  }
}

TEST(Fox_Mult, res_fox_mult_is_correct) {
  Matrix X = {{1.1, 1.2, 1.3}, {2.4, 2.5, 2.6}, {3.7, 3.8, 3.9}};
  Matrix Y = {{4.1, 4.2, 4.3}, {5.4, 5.5, 5.6}, {6.7, 6.8, 6.9}};
  Matrix Z = {
      {19.7, 20.06, 20.42}, {40.76, 41.51, 42.26}, {61.82, 62.96, 64.1}};
  Matrix res = MultiplyFox(X, Y, 2);
  for (int k = 0; k < 3; k++) {
    for (int l = 0; l < 3; l++) {
      EXPECT_NEAR(res[k][l], Z[k][l], 0.001);
    }
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
