// Copyright 2023 Kryuchkov Vladimir
#include <gtest/gtest.h>
#include <omp.h>

#include <vector>

#include "./fox_algorithm.h"

TEST(Fox_Kryuchkov, Get_Random_Matrix) {
    ASSERT_NO_THROW(GetRandomMatrix(10));
    }

TEST(Fox_Kryuchkov, Get_Matrix_On_Negative_Size) {
  ASSERT_ANY_THROW(GetRandomMatrix(-1));
}

TEST(Fox_Kryuchkov, Can_Mult_Not_Same_Matrix) {
  std::vector<std::vector<double>> A = GetRandomMatrix(5);
  std::vector<std::vector<double>> B = GetRandomMatrix(6);

  ASSERT_ANY_THROW(FoxParallel(A, B, 2));
}

TEST(Fox_Kryuchkov, Can_Parallel_Mult_The_Same_Matrix_3x3) {
  std::vector<std::vector<double>> A = {
      {1.1, 7.9, 4.5}, {2.9, 2.2, 1.8}, {7.3, 2.1, 3.3}};
  std::vector<std::vector<double>> B = {
      {4.4, 5.9, 6.9}, {2.7, 5.5, 2.6}, {6.1, 2.5, 6.6}};
  std::vector<std::vector<double>> C = {
      {53.62, 61.19, 57.83}, {29.68, 33.71, 37.61}, {57.92, 62.87, 77.61}};
  std::vector<std::vector<double>> res = FoxParallel(A, B, 2);

  ASSERT_TRUE(CompareMatrix(res, C));
}

TEST(Fox_Kryuchkov, Simple_And_Parallel_The_Same_3x3) {
  std::vector<std::vector<double>> A = {
      {1.1, 7.9, 4.5}, {2.9, 2.2, 1.8}, {7.3, 2.1, 3.3}};
  std::vector<std::vector<double>> B = {
      {4.4, 5.9, 6.9}, {2.7, 5.5, 2.6}, {6.1, 2.5, 6.6}};
  std::vector<std::vector<double>> res1 = SimpleMultiplication(A, B);
  std::vector<std::vector<double>> res2 = FoxParallel(A, B, 2);

  ASSERT_EQ(CompareMatrix(res1, res2), true);
}

TEST(Fox_Kryuchkov, Block_And_Parallel_The_Same_3x3) {
  std::vector<std::vector<double>> A = {
      {1.1, 7.9, 4.5}, {2.9, 2.2, 1.8}, {7.3, 2.1, 3.3}};
  std::vector<std::vector<double>> B = {
      {4.4, 5.9, 6.9}, {2.7, 5.5, 2.6}, {6.1, 2.5, 6.6}};
  std::vector<std::vector<double>> res1 = BlockMultiplication(A, B);
  std::vector<std::vector<double>> res2 = FoxParallel(A, B, 2);

  ASSERT_EQ(CompareMatrix(res1, res2), true);
}

TEST(Fox_Kryuchkov, Simple_And_Parallel_The_Same_5x5) {
  std::vector<std::vector<double>> A = GetRandomMatrix(5);
  std::vector<std::vector<double>> B = GetRandomMatrix(5);
  std::vector<std::vector<double>> res1 = SimpleMultiplication(A, B);
  std::vector<std::vector<double>> res2 = FoxParallel(A, B, 2);

  ASSERT_EQ(CompareMatrix(res1, res2), true);
}

TEST(Fox_Kryuchkov, Block_And_Parallel_The_Same_5x5) {
  std::vector<std::vector<double>> A = GetRandomMatrix(5);
  std::vector<std::vector<double>> B = GetRandomMatrix(5);
  std::vector<std::vector<double>> res1 = BlockMultiplication(A, B);
  std::vector<std::vector<double>> res2 = FoxParallel(A, B, 2);
  ASSERT_EQ(CompareMatrix(res1, res2), true);
  ASSERT_EQ(CompareMatrix(res1, res2), true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
