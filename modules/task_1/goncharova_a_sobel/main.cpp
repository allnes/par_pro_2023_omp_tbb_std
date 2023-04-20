// Copyright 2023 Goncharova Anna
#include <iostream>
#include <vector>
#include <ctime>
#include "../../../modules/task_1/goncharova_a_sobel/goncharova_a_sobel.h"
#include "gtest/gtest.h"

TEST(sobel, get_matrix) {
  std::vector<int> example = { 1, 5, 4, 3 };
  image Example(2, 2, example);
  ASSERT_EQ(example, Example.GetMatrix());
}

TEST(sobel, uncorrect_width) {
  std::vector<int> example = { 1, 5, 4, 3 };
  ASSERT_ANY_THROW(image Example(0, 2, example));
}

TEST(sobel, uncorrect_height) {
  std::vector<int> example = { 1, 5, 4, 3 };
  ASSERT_ANY_THROW(image Example(2, 0, example));
}

TEST(sobel, uncorrect_sizes) {
  std::vector<int> example = { 1, 5, 4, 3 };
  ASSERT_ANY_THROW(image Example(0, 0, example));
}

TEST(sobel, uncorrect_width_in_random) {
  ASSERT_ANY_THROW(image Example(0, 1));
}

TEST(sobel, uncorrect_height_in_random) {
  ASSERT_ANY_THROW(image Example(1, 0));
}

TEST(sobel, uncorrect_sizes_in_random) {
  ASSERT_ANY_THROW(image Example(0, 0));
}

TEST(sobel, seq_sobel) {
  std::vector<int> example = { 1, 0, 2, 1, 0, 2, 1, 0, 2 };
  std::vector<int> result = { 4 };
  image Example(3, 3, example);
  image K = Example.SeqSobel();
  ASSERT_EQ(result, K.GetMatrix());
}
