// Copyright 2023 Makarov Danila
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/makarov_d_sobel/sobel.h"


TEST(SEQ, SOBEL_MATRIX_1x1_1) {
  Matrix expected(createMatrix(1, 1, 1));
  Matrix result = SobelSeq(expected);
  ASSERT_EQ(expected, result);

  /*std::cout << "Expected:" << std::endl;
  printMatrix(expected);
  std::cout << "Result:" <<std::endl;
  printMatrix(actual);*/
}

TEST(SEQ, SOBEL_MATRIX_4x4_0) {
  Matrix expected(createMatrix(4, 4, 0));
  Matrix result = SobelSeq(expected);
  ASSERT_EQ(expected, result);

  /*std::cout << "Expected:" << std::endl;
  printMatrix(expected);
  std::cout << "Result:" << std::endl;
  printMatrix(result);*/
}

TEST(SEQ, SOBEL_MATRIX_6x6_1) {
  Matrix expected = {{1, 1, 1, 1, 1, 1},
                      {1, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 1},
                      {1, 1, 1, 1, 1, 1}};
  Matrix result = SobelSeq(createMatrix(6, 6, 1));
  ASSERT_EQ(expected, result);
  /*std::cout << "Expected:" << std::endl;
  printMatrix(expected2);
  std::cout << "Result:" << std::endl;
  printMatrix(result2);*/
}

TEST(SEQ, SOBEL_MATRIX_10x10) {
  Matrix expected = {{100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
                      {100, 0, 0, 0, 0, 0, 0, 0, 0, 100},
                      {100, 0, 140, 255, 255, 255, 140, 0, 0, 100},
                      {100, 0, 255, 255, 255, 255, 255, 0, 0, 100},
                      {100, 0, 255, 255, 255, 255, 255, 0, 0, 100},
                      {100, 0, 140, 255, 255, 255, 140, 0, 0, 100},
                      {100, 0, 0, 0, 0, 0, 0, 0, 0, 100},
                      {100, 0, 0, 0, 0, 0, 0, 0, 0, 100},
                      {100, 0, 0, 0, 0, 0, 0, 0, 0, 100},
                      {100, 100, 100, 100, 100, 100, 100, 100, 100, 100}};
  Matrix matrix = createMatrix(10, 10, 100.0);
  for (int i = 3; i < 6; i++) {
    matrix[3][i] = 1;
    matrix[4][i] = 1;
  }
  Matrix result = SobelSeq(matrix);
  ASSERT_EQ(expected, result);
  /*std::cout << "Expected:" << std::endl;
  printMatrix(expected);
  std::cout << "Result:" << std::endl;
  printMatrix(result);*/
}

TEST(SEQ, SOBEL_MATRIX_4x4) {
  Matrix matrix = {{10, 20, 43, 13},
                    {0, 172, 218, 45},
                    {87, 17, 116, 211},
                    {100, 123, 115, 10}};
  Matrix expected = {{10, 20, 43, 13},
                      {0, 255, 255, 45},
                      {87, 255, 255, 211},
                      {100, 123, 115, 10}};
  Matrix result = SobelSeq(matrix);
  ASSERT_EQ(expected, result);
  /*std::cout << "Expected:" << std::endl;
  printMatrix(expected);
  std::cout << "Result:" << std::endl;
  printMatrix(result);*/
}
