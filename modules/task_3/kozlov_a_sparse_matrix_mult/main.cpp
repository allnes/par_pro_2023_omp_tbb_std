// Copyright 2023 Kozlov Alexey

#include <gtest/gtest.h>
#include <time.h>

#include <vector>

#include "../../../modules/task_3/kozlov_a_sparse_matrix_mult/matrix_ccs_tbb.h"

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_int) {
  int cap = 3;
  int dim = 3;

  std::vector<double> val{100, -15, 2};
  std::vector<int> rows{2, 1, 3};
  std::vector<int> ptr{1, 2, 3, 4};

  SprMatCCS A(dim, cap, val, rows, ptr);

  val = {3, 6, -23};
  rows = {3, 2, 1};
  ptr = {1, 2, 3, 4};

  SprMatCCS B(dim, cap, val, rows, ptr);

  SprMatCCS C = A.ParallelMult(B);

  std::vector<double> res_val{6, -90, -2300};
  std::vector<int> rows_res{3, 1, 2};
  std::vector<int> ptr_res{1, 2, 3, 4};
  SprMatCCS Res(dim, res_val.size(), res_val, rows_res, ptr_res);

  EXPECT_TRUE(C == Res);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_double1) {
  int cap = 4;
  int dim = 4;

  std::vector<double> val{-10.5, 22.1, 2.4, -3.2};
  std::vector<int> rows{1, 3, 1, 3};
  std::vector<int> ptr{1, 2, 3, 4, 5};

  SprMatCCS A(dim, cap, val, rows, ptr);

  val = {2.4, 6, -39, 108};
  rows = {1, 2, 3, 1};
  ptr = {1, 2, 4, 4, 5};

  SprMatCCS B(dim, cap, val, rows, ptr);

  SprMatCCS C = A.ParallelMult(B);

  std::vector<double> res_val{-25.2, -93.6, 132.6, -1134};
  std::vector<int> rows_res{1, 1, 3, 1};
  std::vector<int> ptr_res{1, 2, 4, 4, 5};
  SprMatCCS Res(dim, res_val.size(), res_val, rows_res, ptr_res);

  EXPECT_TRUE(C == Res);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_double2) {
  int cap = 5;
  int dim = 3;

  std::vector<double> val{-12, 3, 21.4, 8, -4.5};
  std::vector<int> rows{1, 3, 2, 3, 1};
  std::vector<int> ptr{1, 3, 5, 6};

  SprMatCCS A(dim, cap, val, rows, ptr);

  val = {2.4, 6, -39, 108, 44};
  rows = {1, 2, 3, 1, 3};
  ptr = {1, 2, 4, 6};

  SprMatCCS B(dim, cap, val, rows, ptr);

  SprMatCCS C = A.ParallelMult(B);

  std::vector<double> res_val{-28.8, 7.2, 175.5, 128.4, 48, -1494, 324};
  std::vector<int> rows_res{1, 3, 1, 2, 3, 1, 3};
  std::vector<int> ptr_res{1, 3, 6, 8};
  SprMatCCS Res(dim, res_val.size(), res_val, rows_res, ptr_res);

  EXPECT_TRUE(C == Res);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_perf100) {
  double start, end;
  double seq_time, tbb_time;
  int dim = 100;
  int spr = 1;

  SprMatCCS A;
  A.randMat(dim, spr);
  SprMatCCS B;
  B.randMat(dim, spr);

  start = clock();
  SprMatCCS C_seq = A * B;
  end = clock();
  std::cout << "SEQ time: " << (end - start + .0) / CLOCKS_PER_SEC << " sec"
            << std::endl;
  seq_time = (end - start) / CLOCKS_PER_SEC;

  start = clock();
  SprMatCCS C_tdd = A.ParallelMult(B);
  end = clock();
  std::cout << "TDD time: " << (end - start + .0) / CLOCKS_PER_SEC << " sec"
            << std::endl;
  tbb_time = (end - start) / CLOCKS_PER_SEC;

  std::cout << "Performance improvement is " << seq_time / tbb_time
            << std::endl;

  EXPECT_TRUE(C_seq == C_tdd);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_perf500) {
  double start, end;
  double seq_time, tbb_time;
  int dim = 500;
  int spr = 1;

  SprMatCCS A;
  A.randMat(dim, spr);
  SprMatCCS B;
  B.randMat(dim, spr);

  start = clock();
  SprMatCCS C_seq = A * B;
  end = clock();
  std::cout << "SEQ time: " << (end - start) / CLOCKS_PER_SEC << " sec"
            << std::endl;
  seq_time = (end - start) / CLOCKS_PER_SEC;

  start = clock();
  SprMatCCS C_tdd = A.ParallelMult(B);
  end = clock();
  std::cout << "TDD time: " << (end - start) / CLOCKS_PER_SEC << " sec"
            << std::endl;
  tbb_time = (end - start) / CLOCKS_PER_SEC;

  std::cout << "Performance improvement is " << seq_time / tbb_time
            << std::endl;

  EXPECT_TRUE(C_seq == C_tdd);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_perf1000) {
  double start, end;
  double seq_time, tbb_time;
  int dim = 1000;
  int spr = 1;

  SprMatCCS A;
  A.randMat(dim, spr);
  SprMatCCS B;
  B.randMat(dim, spr);

  start = clock();
  SprMatCCS C_seq = A * B;
  end = clock();
  std::cout << "SEQ time: " << (end - start) / CLOCKS_PER_SEC << " sec"
            << std::endl;
  seq_time = (end - start) / CLOCKS_PER_SEC;

  start = clock();
  SprMatCCS C_tdd = A.ParallelMult(B);
  end = clock();
  std::cout << "TDD time: " << (end - start) / CLOCKS_PER_SEC << " sec"
            << std::endl;
  tbb_time = (end - start) / CLOCKS_PER_SEC;

  std::cout << "Performance improvement is " << seq_time / tbb_time
            << std::endl;

  EXPECT_TRUE(C_seq == C_tdd);
}

TEST(SprMatCCS_Test, Sparse_matrix_multiplication_perf5000) {
  double start, end;
  double seq_time, tbb_time;
  int dim = 5000;
  int spr = 1;

  SprMatCCS A;
  A.randMat(dim, spr);
  SprMatCCS B;
  B.randMat(dim, spr);

  start = clock();
  SprMatCCS C_seq = A * B;
  end = clock();
  std::cout << "SEQ time: " << (end - start) / CLOCKS_PER_SEC << " sec"
            << std::endl;
  seq_time = (end - start) / CLOCKS_PER_SEC;

  start = clock();
  SprMatCCS C_tdd = A.ParallelMult(B);
  end = clock();
  std::cout << "TDD time: " << (end - start) / CLOCKS_PER_SEC << " sec"
            << std::endl;
  tbb_time = (end - start) / CLOCKS_PER_SEC;

  std::cout << "Performance improvement is " << seq_time / tbb_time
            << std::endl;

  EXPECT_TRUE(C_seq == C_tdd);
}
