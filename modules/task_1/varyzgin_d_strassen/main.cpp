// Copyright 2023 Varyzgin Dmitry

#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>

#include "./strassen.h"

TEST(Strassen, Mult8x8)
{
  int size = 8;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_res(size * size);
  std::vector<double> naive_res(size * size);

  for (int i = 0; i < size * size; i++)
  {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  strassen(a.data(), b.data(), strassen_res.data(), size);
  multiplying(a.data(), b.data(), naive_res.data(), size);
  ASSERT_EQ(naive_res, strassen_res);
}

TEST(Strassen, Mult128x128)
{
  int size = 128;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_res(size * size);
  std::vector<double> naive_res(size * size);

  for (size_t i = 0; i < size * size; i++)
  {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  strassen(a.data(), b.data(), strassen_res.data(), size);
  multiplying(a.data(), b.data(), naive_res.data(), size);
  ASSERT_EQ(naive_res, strassen_res);
}

TEST(Strassen, Mult256x256)
{
  int size = 256;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_res(size * size);
  std::vector<double> naive_res(size * size);

  for (size_t i = 0; i < size * size; i++)
  {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  strassen(a.data(), b.data(), strassen_res.data(), size);
  multiplying(a.data(), b.data(), naive_res.data(), size);
  ASSERT_EQ(naive_res, strassen_res);
}

TEST(Strassen, Mult64x64)
{
  int size = 64;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_res(size * size);
  std::vector<double> naive_res(size * size);
  for (size_t i = 0; i < size * size; i++)
  {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  strassen(a.data(), b.data(), strassen_res.data(), size);
  multiplying(a.data(), b.data(), naive_res.data(), size);
  ASSERT_EQ(naive_res, strassen_res);
}

TEST(Strassen, NotPow2)
{
  int size = 57;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_res(size * size);

  for (size_t i = 0; i < size * size; i++)
  {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  ASSERT_THROW(strassen(a.data(), b.data(), strassen_res.data(), size),
               std::invalid_argument);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}