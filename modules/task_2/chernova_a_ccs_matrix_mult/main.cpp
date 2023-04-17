// Copyright 2023 Chernova Anna
#include <gtest/gtest.h>

#include <complex>
#include <vector>

#include "./ccs_matrix_mult.h"

TEST(Sequential, Test_Mult_3_3) {
  size_t rows = 3;
  size_t columns = 3;
  std::vector<std::complex<double>> buff_1{
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(3, 0), std::complex<double>(0, 0),
      std::complex<double>(0, 0), std::complex<double>(1, 0),
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(0, 0)};
  std::vector<std::complex<double>> buff_2{
      std::complex<double>(0, 0), std::complex<double>(0, 0),
      std::complex<double>(6, 0), std::complex<double>(0, 0),
      std::complex<double>(2, 0), std::complex<double>(3, 0),
      std::complex<double>(0, 0), std::complex<double>(0, 0),
      std::complex<double>(4, 0)};

  std::vector<std::complex<double>> result{
      std::complex<double>(0, 0),  std::complex<double>(4, 0),
      std::complex<double>(18, 0), std::complex<double>(0, 0),
      std::complex<double>(0, 0),  std::complex<double>(4, 0),
      std::complex<double>(0, 0),  std::complex<double>(4, 0),
      std::complex<double>(6, 0)};

  MatrixCSS matrix_1 =
      MatrixCSS(buff_1, rows, columns) * MatrixCSS(buff_2, rows, columns);
  MatrixCSS matrix_2 = parallelCCSMultiplication(
      MatrixCSS(buff_1, rows, columns), MatrixCSS(buff_2, rows, columns));
  MatrixCSS matrix_3 = MatrixCSS(result, rows, columns);

  ASSERT_TRUE(matrix_1 == matrix_2 && matrix_2 == matrix_3);
}

TEST(Sequential, Test_Random_Mult_3_3) {
  size_t rows = 3;
  size_t columns = 3;
  std::vector<std::complex<double>> buff_1 = getRandomVector(rows, columns);
  std::vector<std::complex<double>> buff_2 = getRandomVector(rows, columns);

  MatrixCSS matrix_1 =
      MatrixCSS(buff_1, rows, columns) * MatrixCSS(buff_2, rows, columns);
  MatrixCSS matrix_2 = parallelCCSMultiplication(
      MatrixCSS(buff_1, rows, columns), MatrixCSS(buff_2, rows, columns));

  ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(Sequential, Test_Random_Mult_4_4) {
  size_t rows = 4;
  size_t columns = 4;
  std::vector<std::complex<double>> buff_1 = getRandomVector(rows, columns);
  std::vector<std::complex<double>> buff_2 = getRandomVector(rows, columns);

  MatrixCSS matrix_1 =
      MatrixCSS(buff_1, rows, columns) * MatrixCSS(buff_2, rows, columns);
  MatrixCSS matrix_2 = parallelCCSMultiplication(
      MatrixCSS(buff_1, rows, columns), MatrixCSS(buff_2, rows, columns));

  ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(Sequential, Test_Random_Mult_5_5) {
  size_t rows = 5;
  size_t columns = 5;
  std::vector<std::complex<double>> buff_1 = getRandomVector(rows, columns);
  std::vector<std::complex<double>> buff_2 = getRandomVector(rows, columns);

  MatrixCSS matrix_1 =
      MatrixCSS(buff_1, rows, columns) * MatrixCSS(buff_2, rows, columns);
  MatrixCSS matrix_2 = parallelCCSMultiplication(
      MatrixCSS(buff_1, rows, columns), MatrixCSS(buff_2, rows, columns));

  ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(Sequential, Test_Random_Mult_6_6) {
  size_t rows = 6;
  size_t columns = 6;
  std::vector<std::complex<double>> buff_1 = getRandomVector(rows, columns);
  std::vector<std::complex<double>> buff_2 = getRandomVector(rows, columns);

  MatrixCSS matrix_1 =
      MatrixCSS(buff_1, rows, columns) * MatrixCSS(buff_2, rows, columns);
  MatrixCSS matrix_2 = parallelCCSMultiplication(
      MatrixCSS(buff_1, rows, columns), MatrixCSS(buff_2, rows, columns));

  ASSERT_TRUE(matrix_1 == matrix_2);
}
