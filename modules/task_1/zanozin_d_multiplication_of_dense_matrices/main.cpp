// Copyright 2023 Zanozin Danila
#include <gtest/gtest.h>

#include <vector>

#include "./ops_omp.cpp"

TEST(Sequential, Test_Kanon_10) {
  const int size = 10;
  Matrix a(size), b(size);
  a.randomize();
  b.randomize();
  Matrix testRes = a * b;
  Matrix res = seqKannonMethod(a, b);
  ASSERT_EQ(testRes, res);
}
TEST(Sequential, Test_Kanon_100) {
  const int size = 100;
  Matrix a(size), b(size);
  a.randomize();
  b.randomize();
  Matrix testRes = a * b;
  Matrix res = seqKannonMethod(a, b);
  ASSERT_EQ(testRes, res);
}
TEST(Sequential, Test_Kanon_50) {
  const int size = 50;
  Matrix a(size), b(size);
  a.randomize();
  b.randomize();
  Matrix testRes = a * b;
  Matrix res = seqKannonMethod(a, b);
  ASSERT_EQ(testRes, res);
}
TEST(Sequential, Test_Kanon_40) {
  const int size = 40;
  Matrix a(size), b(size);
  a.randomize();
  b.randomize();
  Matrix testRes = a * b;
  Matrix res = seqKannonMethod(a, b);
  ASSERT_EQ(testRes, res);
}
TEST(Sequential, Test_Kanon_20) {
  const int size = 20;
  Matrix a(size), b(size);
  a.randomize();
  b.randomize();
  Matrix testRes = a * b;
  Matrix res = seqKannonMethod(a, b);
  ASSERT_EQ(testRes, res);
}