// Copyright 2023 Mukhin Vadim
#include <gtest/gtest.h>

#include "../mukhin_v_focs_algoritm/focs_algoritm.h"

TEST(Focs_Mukhin, Get_Random_Matrix) {
  ASSERT_NO_THROW(GetRandomMatrix(10));
}

TEST(Focs_Mukhin, Get_Matrix_On_Negative_Size) {
  ASSERT_ANY_THROW(GetRandomMatrix(-1));
}

TEST(Focs_Mukhin, Simple_Mult_With_Different_Size) {
  std::vector<std::vector<double>> A = GetRandomMatrix(5);
  std::vector<std::vector<double>> B = GetRandomMatrix(8);
  ASSERT_ANY_THROW(SimpleMultiplication(A, B));
}

TEST(Focs_Mukhin, Simple_Mult_3x3) {
  std::vector<std::vector<double>> A = {
      {1.1, 7.9, 4.5}, {2.9, 2.2, 1.8}, {7.3, 2.1, 3.3}};
  std::vector<std::vector<double>> B = {
      {4.4, 5.9, 6.9}, {2.7, 5.5, 2.6}, {6.1, 2.5, 6.6}};
  std::vector<std::vector<double>> C = {
      {53.62, 61.19, 57.83}, {29.68, 33.71, 37.61}, {57.92, 62.87, 77.61}};

  ASSERT_EQ(CompareMatrix(SimpleMultiplication(A, B), C), true);
}

TEST(Focs_Mukhin, Block_Mult_3x3) {
  std::vector<std::vector<double>> A = {
      {1.1, 7.9, 4.5}, {2.9, 2.2, 1.8}, {7.3, 2.1, 3.3}};
  std::vector<std::vector<double>> B = {
      {4.4, 5.9, 6.9}, {2.7, 5.5, 2.6}, {6.1, 2.5, 6.6}};
  std::vector<std::vector<double>> C = {
      {53.62, 61.19, 57.83}, {29.68, 33.71, 37.61}, {57.92, 62.87, 77.61}};

  ASSERT_EQ(CompareMatrix(BlockMultiplication(A, B), C), true);
}

TEST(Focs_Mukhin, Block_And_Simple_Is_Same) {
  std::vector<std::vector<double>> A = GetRandomMatrix(6);
  std::vector<std::vector<double>> B = GetRandomMatrix(6);
  ASSERT_EQ(
      CompareMatrix(SimpleMultiplication(A, B), BlockMultiplication(A, B)),
      true);
}
