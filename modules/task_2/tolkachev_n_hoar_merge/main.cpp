// Copyright 2023 Tolkachev
#include <gtest/gtest.h>
#include "./hoar_merge.h"

TEST(OMP, test_10) {
  std::vector<int> vec1 = Getvec(10);
  std::vector<int> vec2 = SortParallel(&vec1);
  std::sort(vec1.begin(), vec1.end());
  ASSERT_EQ(vec1, vec2);
}

TEST(OMP, test_20) {
  std::vector<int> vec1 = Getvec(20);
  std::vector<int> vec2 = SortParallel(&vec1);
  std::sort(vec1.begin(), vec1.end());
  ASSERT_EQ(vec1, vec2);
}

TEST(OMP, test_30) {
  std::vector<int> vec1 = Getvec(30);
  std::vector<int> vec2 = SortParallel(&vec1);
  std::sort(vec1.begin(), vec1.end());
  ASSERT_EQ(vec1, vec2);
}

TEST(OMP, test_150) {
  std::vector<int> vec1 = Getvec(150);
  std::vector<int> vec2 = SortParallel(&vec1);
  std::sort(vec1.begin(), vec1.end());
  ASSERT_EQ(vec1, vec2);
}

TEST(OMP, test_1000) {
  std::vector<int> vec1 = Getvec(1000);
  std::vector<int> vec2 = SortParallel(&vec1);
  std::sort(vec1.begin(), vec1.end());
  ASSERT_EQ(vec1, vec2);
}
