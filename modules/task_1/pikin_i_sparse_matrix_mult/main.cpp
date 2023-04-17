// Copyright 2023 Pikin Ilya
#include <gtest/gtest.h>
#include "./sparse_matrix_mult.h"

using cmp = std::complex<double>;

TEST(Sequential_version, CRS_format_storage_test) {
  std::vector<std::vector<cmp>> M = {
      {cmp(1, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(3, 0), cmp(4, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(8, 0)}};
  CRSMatrix TestM(M);

  std::vector<cmp> val = {cmp(1, 0), cmp(3, 0), cmp(4, 0), cmp(8, 0)};
  std::vector<int> col = {0, 2, 3, 3};
  std::vector<int> rowInd = {0, 1, 3, 3, 4};
  CRSMatrix StandardM(4, 4, val, col, rowInd);

  ASSERT_EQ(TestM, StandardM);
}

TEST(Sequential_version, Matrix_transposition_test) {
  std::vector<std::vector<cmp>> M = {
      {cmp(1, 1), cmp(2, 2), cmp(3, 3), cmp(4, 4)},
      {cmp(5, 5), cmp(6, 6), cmp(7, 7), cmp(8, 8)},
      {cmp(9, 9), cmp(10, 10), cmp(11, 11), cmp(12, 12)},
      {cmp(13, 13), cmp(14, 14), cmp(15, 15), cmp(16, 16)}};
  std::vector<std::vector<cmp>> MT = {
      {cmp(1, 1), cmp(5, 5), cmp(9, 9), cmp(13, 13)},
      {cmp(2, 2), cmp(6, 6), cmp(10, 10), cmp(14, 14)},
      {cmp(3, 3), cmp(7, 7), cmp(11, 11), cmp(15, 15)},
      {cmp(4, 4), cmp(8, 8), cmp(12, 12), cmp(16, 16)}};
  CRSMatrix A(M), AT1(MT);
  CRSMatrix AT2 = getTransposed(A);
  ASSERT_EQ(AT1, AT2);
}

TEST(Sequential_version, Dense_int_matrices_3x3_product_test) {
  std::vector<std::vector<cmp>> A = {
    {cmp(1, 0), cmp(0, 0), cmp(6, 0)},
    {cmp(8, 0), cmp(9, 0), cmp(-2, 0)},
    {cmp(-5, 0), cmp(1, 0), cmp(3, 0)}};
  std::vector<std::vector<cmp>> B = {
    {cmp(1, 0), cmp(4, 0), cmp(7, 0)},
    {cmp(2, 0), cmp(5, 0), cmp(8, 0)},
    {cmp(3, 0), cmp(6, 0), cmp(9, 0)}};
  std::vector<std::vector<cmp>> C = {
    {cmp(19, 0), cmp(40, 0), cmp(61, 0)},
    {cmp(20, 0), cmp(65, 0), cmp(110, 0)},
    {cmp(6, 0), cmp(3, 0), cmp(0, 0)}};

  CRSMatrix crsA(A), crsB(B), crsC(C);
  CRSMatrix prod = getProductSeq(crsA, crsB);

  ASSERT_EQ(crsC, prod);
}

TEST(Sequential_version, Sparse_int_matrices_4x4_product_test) {
  std::vector<std::vector<cmp>> A = {
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(1, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(2, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(3, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(4, 0), cmp(0, 0)}};
  std::vector<std::vector<cmp>> B = {
      {cmp(0, 0), cmp(5, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(6, 0)},
      {cmp(7, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(8, 0), cmp(0, 0), cmp(0, 0)}};
  std::vector<std::vector<cmp>> C = {
      {cmp(0, 0), cmp(8, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(16, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(21, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(28, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)}};
  CRSMatrix crsA(A), crsB(B), crsC(C);
  CRSMatrix prod = getProductSeq(crsA, crsB);

  ASSERT_EQ(crsC, prod);
}

TEST(Sequential_version, Sparse_complex_matrices_4x4_product_test) {
  std::vector<std::vector<cmp>> A = {
      {cmp(0, 0), cmp(2, -1.5), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(5.2, 4), cmp(0, 0)},
      {cmp(1.2, 0.8), cmp(0, 0), cmp(3.1, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(3.6, -1.7)}};
  std::vector<std::vector<cmp>> B = {
      {cmp(2.7, -1), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(1.5, -1)},
      {cmp(-4.3, 1.6), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0.5, 2), cmp(0, 0)}};
  std::vector<std::vector<cmp>> C = {
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(1.5, -4.25)},
      {cmp(-28.76, -8.88), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(-9.29, 5.92), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(5.2, 6.35), cmp(0, 0)}};
  CRSMatrix crsA(A), crsB(B), crsC(C);
  CRSMatrix prod = getProductSeq(crsA, crsB);

  ASSERT_EQ(crsC, prod);
}

TEST(Sequential_version, Dense_complex_matrices_4x4_product_test) {
  std::vector<std::vector<cmp>> A = {
      {cmp(1, 0), cmp(2, -1.5), cmp(7, 0), cmp(9, 0)},
      {cmp(2, 0), cmp(4, 0), cmp(5.2, 4), cmp(10, 0)},
      {cmp(1.2, 0.8), cmp(5, 0), cmp(3.1, 0), cmp(11, 0)},
      {cmp(3, 0), cmp(6, 0), cmp(8, 0), cmp(3.6, -1.7)}};
  std::vector<std::vector<cmp>> B = {
      {cmp(2.7, -1), cmp(3, 0), cmp(7, 0), cmp(10, 0)},
      {cmp(1, 0), cmp(4, 0), cmp(8, 0), cmp(1.5, -1)},
      {cmp(-4.3, 1.6), cmp(5, 0), cmp(9, 0), cmp(11, 0)},
      {cmp(2, 0), cmp(6, 0), cmp(0.5, 2), cmp(12, 0)}};
  std::vector<std::vector<cmp>> C = {
      {cmp(-7.4, 8.7), cmp(100, -6), cmp(90.5, 6), cmp(196.5, -4.25)},
      {cmp(0.64, -10.88), cmp(108, 20), cmp(97.8, 56), cmp(203.2, 40)},
      {cmp(17.71, 5.92), cmp(105.1, 2.4), cmp(81.8, 27.6), cmp(185.6, 3)},
      {cmp(-13.1, 6.4), cmp(94.6, -10.2), cmp(146.2, 6.35), cmp(170.2, -26.4)}};
  CRSMatrix crsA(A), crsB(B), crsC(C);
  CRSMatrix prod = getProductSeq(crsA, crsB);

  ASSERT_EQ(crsC, prod);
}

TEST(Sequential_version, Multiplication_by_zero_matrix_test) {
  std::vector<std::vector<cmp>> A = {
      {cmp(1, 0), cmp(2, -1.5), cmp(7, 0), cmp(9, 0)},
      {cmp(2, 0), cmp(4, 0), cmp(5.2, 4), cmp(10, 0)},
      {cmp(1.2, 0.8), cmp(5, 0), cmp(3.1, 0), cmp(11, 0)},
      {cmp(3, 0), cmp(6, 0), cmp(8, 0), cmp(3.6, -1.7)}};
  std::vector<std::vector<cmp>> B = {
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)}};
  CRSMatrix crsA(A), crsB(B);
  CRSMatrix prod = getProductSeq(crsA, crsB);

  ASSERT_EQ(crsB, prod);
}

// TEST(Sequential_version, Time_test) {
//     CRSMatrix A = getRandCRSMatrix(10000, 50);
//     CRSMatrix B = getRandCRSMatrix(10000, 50);
//     unsigned int start_time = clock();
//     CRSMatrix C = getProductSeq(A, B);
//     unsigned int end_time = clock();
//     unsigned int search_time = end_time - start_time;
//     std::cout << static_cast<double>(search_time / 1000) << " seconds\n";
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
