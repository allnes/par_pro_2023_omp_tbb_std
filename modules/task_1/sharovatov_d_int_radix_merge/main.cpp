// Copyright 2023 Sharovatov Daniil
#include <gtest/gtest.h>
#include "../../../modules/task_1/sharovatov_d_int_radix_merge/int_radix_merge.h"

TEST(Sequential, test_zero_size_vector) {
  std::vector<int> vec = {};
  ASSERT_ANY_THROW(radixSortMerge(&vec));
}

TEST(Sequential, test_sorted_vector) {
  std::vector<int> sortedVec = getRandomVector(10);
  std::sort(sortedVec.begin(), sortedVec.end());

  std::vector<int> vec = radixSortMerge(&sortedVec);

  ASSERT_EQ(vec, sortedVec);
}

TEST(Sequential, test_random_vector_small_size) {
  const int vectorSize = 10;
  std::vector<int> vec1 = getRandomVector(vectorSize);

  std::vector<int> vec2 = radixSortMerge(&vec1);
  std::sort(vec1.begin(), vec1.end());

  ASSERT_EQ(vec1, vec2);
}

TEST(Sequential, test_random_vector_medium_size) {
  const int vectorSize = 250;
  std::vector<int> vec1 = getRandomVector(vectorSize);

  std::vector<int> vec2 = radixSortMerge(&vec1);
  std::sort(vec1.begin(), vec1.end());

  ASSERT_EQ(vec1, vec2);
}

TEST(Sequential, test_random_vector_large_size) {
  const int vectorSize = 1000000;
  std::vector<int> vec1 = getRandomVector(vectorSize);

  std::vector<int> vec2 = radixSortMerge(&vec1);
  std::sort(vec1.begin(), vec1.end());

  ASSERT_EQ(vec1, vec2);
}
