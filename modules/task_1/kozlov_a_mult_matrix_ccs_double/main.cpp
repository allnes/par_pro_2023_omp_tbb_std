// Copyright 2022 Kozlov Alexey

#include <gtest/gtest.h>
#include <time.h>
#include <vector>

#include "../../../modules/task_1/kozlov_a_mult_matrix_ccs_double/matrix_ccs.h"

TEST(SprMatCCS_Test, default_constructor_test) {
  EXPECT_NO_THROW(SprMatCCS());
}

TEST(SprMatCCS_Test, Sparse_matrix_creation_with_param) {
  int cap = 5;
  int dim = 5;
  std::vector<double> val{0.4, 3.2, 8.5, 15.1, 7.4};
  std::vector<int> rows{2, 1, 1, 4, 1};
  std::vector<int> ptr{1, 2, 3, 4, 6};

  EXPECT_NO_THROW(SprMatCCS(dim, cap, val, rows, ptr));
}

TEST(SprMatCCS_Test, copy_constructor_test) {
  SprMatCCS mat;
  EXPECT_NO_THROW(SprMatCCS copy(mat));
}

TEST(SprMatCCS_Test, Sparse_matrix_copy_equality) {
  int cap = 6;
  int dim = 4;
  std::vector<double> val {2, 5.2, 4.11, -23, 44, -16.5};
  std::vector<int> rows {3, 2, 1, 4, 1, 2};
  std::vector<int> ptr {1, 2, 3, 4, 7};
  SprMatCCS mat(dim, cap, val, rows, ptr);
  SprMatCCS arr(mat);

  EXPECT_TRUE(mat == arr);
}

TEST(SprMatCCS_Test, Sparse_matrix_transposition) {
  int cap = 5;
  int dim = 4;

  std::vector<double> val {6.5, 4.3, -13.3, 15, 7};
  std::vector<int> rows {4, 2, 2, 3, 1};
  std::vector<int> ptr {1, 2, 3, 5, 6};
  SprMatCCS mat(dim, cap, val, rows, ptr);
  mat = mat.transMat();

  std::vector<double> arr_val{7, 4.3, -13.3, 15, 6.5};
  std::vector<int> arr_rows{4, 2, 3, 3, 1};
  std::vector<int> arr_ptr{1, 2, 4, 5, 6};
  SprMatCCS arr(dim, cap, arr_val, arr_rows, arr_ptr);

  EXPECT_TRUE(mat == arr);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_int) {
  int cap = 3;
  int dim = 3;

  std::vector<double> val {100, -15, 2};
  std::vector<int> rows {2, 1, 3};
  std::vector<int> ptr {1, 2, 3, 4};

  SprMatCCS A(dim, cap, val, rows, ptr);

  val = {3, 6, -23};
  rows = {3, 2, 1};
  ptr = {1, 2, 3, 4};

  SprMatCCS B(dim, cap, val, rows, ptr);

  SprMatCCS C = A * B;

  std::vector<double> res_val {6, -90, -2300};
  std::vector<int> rows_res {3, 1, 2};
  std::vector<int> ptr_res {1, 2, 3, 4};
  SprMatCCS Res(dim, res_val.size(), res_val, rows_res, ptr_res);

  EXPECT_TRUE(C == Res);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_double1) {
  int cap = 4;
  int dim = 4;

  std::vector<double> val {-10.5, 22.1, 2.4, -3.2};
  std::vector<int> rows {1, 3, 1, 3};
  std::vector<int> ptr {1, 2, 3, 4, 5};

  SprMatCCS A(dim, cap, val, rows, ptr);

  val = {2.4, 6, -39, 108};
  rows = {1, 2, 3, 1};
  ptr = {1, 2, 4, 4, 5};

  SprMatCCS B(dim, cap, val, rows, ptr);

  SprMatCCS C = A * B;

  std::vector<double> res_val {-25.2, -93.6, 132.6, -1134};
  std::vector<int> rows_res {1, 1, 3, 1};
  std::vector<int> ptr_res {1, 2, 4, 4, 5};
  SprMatCCS Res(dim, res_val.size(), res_val, rows_res, ptr_res);

  EXPECT_TRUE(C == Res);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_double2) {
  int cap = 5;
  int dim = 3;

  std::vector<double> val {-12, 3, 21.4, 8, -4.5};
  std::vector<int> rows {1, 3, 2, 3, 1};
  std::vector<int> ptr { 1, 3, 5, 6};

  SprMatCCS A(dim, cap, val, rows, ptr);

  val = {2.4, 6, -39, 108, 44};
  rows = {1, 2, 3, 1, 3};
  ptr = {1, 2, 4, 6};

  SprMatCCS B(dim, cap, val, rows, ptr);

  SprMatCCS C = A * B;

  std::vector<double> res_val {-28.8, 7.2, 175.5, 128.4, 48, -1494, 324};
  std::vector<int> rows_res {1, 3, 1, 2, 3, 1, 3};
  std::vector<int> ptr_res {1, 3, 6, 8};
  SprMatCCS Res(dim, res_val.size(), res_val, rows_res, ptr_res);

  EXPECT_TRUE(C == Res);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_1) {
  int dim = 10;
  int spr = 1;
  SprMatCCS mat1;
  mat1.randMat(dim, spr);
  SprMatCCS mat2;
  mat2.randMat(dim, spr);

  EXPECT_NO_THROW(mat1 * mat2);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_2) {
  int dim = 100;
  int spr = 1;
  SprMatCCS mat1;
  mat1.randMat(dim, spr);
  SprMatCCS mat2;
  mat2.randMat(dim, spr);

  EXPECT_NO_THROW(mat1 * mat2);
}

// TEST(SprMatCCS_Test, Sparse_matrix_multiplication_3) {
//  clock_t start, end;
//  int dim = 2000;
//  int spr = 1;
//  SprMatCCS mat1;
//  start = clock();
//  mat1.randMat(dim, spr);
//  SprMatCCS mat2;
//  mat2.randMat(dim, spr);
//  end = clock();
//  std::cout << "Time required -> " << (end - start + .0) / CLOCKS_PER_SEC
//            << " <-" << std::endl;
//  EXPECT_NO_THROW(mat1 * mat2);
// }
