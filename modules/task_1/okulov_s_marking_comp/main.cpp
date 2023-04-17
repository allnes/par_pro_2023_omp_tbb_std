// Copyright 2023 Okulov Stepan
#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../../../modules/task_1/okulov_s_marking_comp/marking_comp.h"

TEST(marking, 2x2_simple) {
  std::vector<std::vector<int>> img = {{0, 0}, {0, 0}};
  std::vector<std::vector<int>> expected = {{0, 0}, {0, 0}};
  std::vector<std::vector<int>> res = img;
  marking(&img, &res);
  ASSERT_EQ(expected, res);
}

TEST(marking, 6x6) {
  std::vector<std::vector<int>> img = {{1, 0, 0, 1, 1, 1}, {1, 1, 1, 0, 1, 0},
                                       {1, 0, 0, 1, 0, 1}, {1, 1, 0, 1, 0, 1},
                                       {0, 1, 1, 1, 0, 0}, {0, 1, 1, 1, 1, 0}};
  std::vector<std::vector<int>> expected = {
      {1, 0, 0, 2, 2, 2}, {1, 1, 1, 0, 2, 0}, {1, 0, 0, 1, 0, 4},
      {1, 1, 0, 1, 0, 4}, {0, 1, 1, 1, 0, 0}, {0, 1, 1, 1, 1, 0}};
  std::vector<std::vector<int>> res = img;
  marking(&img, &res);
  ASSERT_EQ(expected, res);
}
TEST(marking, 7x7) {
  std::vector<std::vector<int>> img = {
      {0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 1, 1}, {1, 0, 1, 0, 1, 0, 1},
      {1, 1, 1, 0, 1, 0, 1}, {1, 0, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 1, 1, 0},
      {1, 0, 1, 1, 0, 0, 0}};
  std::vector<std::vector<int>> expected = {
      {0, 0, 1, 0, 0, 0, 0}, {2, 0, 0, 0, 0, 3, 3}, {2, 0, 2, 0, 5, 0, 3},
      {2, 2, 2, 0, 5, 0, 3}, {2, 0, 0, 0, 0, 6, 0}, {0, 0, 6, 6, 6, 6, 0},
      {8, 0, 6, 6, 0, 0, 0}};
  std::vector<std::vector<int>> res = img;
  marking(&img, &res);
  ASSERT_EQ(expected, res);
}
TEST(marking, 10x10) {
  std::vector<std::vector<int>> img = {
      {0, 1, 0, 1, 0, 0, 1, 0, 1, 1}, {1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
      {0, 0, 1, 0, 0, 0, 0, 0, 1, 1}, {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
      {1, 0, 1, 1, 0, 1, 0, 1, 1, 0}, {1, 1, 0, 1, 1, 0, 1, 1, 1, 1},
      {1, 1, 1, 1, 0, 0, 1, 1, 0, 1}, {1, 1, 1, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 1, 1, 1, 0}};
  std::vector<std::vector<int>> expected = {
      {0, 1, 0, 2, 0, 0, 3, 0, 3, 3},     {5, 0, 2, 2, 2, 0, 3, 3, 3, 3},
      {0, 0, 2, 0, 0, 0, 0, 0, 3, 3},     {6, 6, 2, 2, 2, 0, 3, 3, 3, 3},
      {6, 0, 2, 2, 0, 9, 0, 3, 3, 0},     {6, 6, 0, 2, 2, 0, 8, 3, 3, 3},
      {6, 6, 6, 2, 0, 0, 8, 3, 0, 3},     {6, 6, 6, 0, 0, 0, 0, 3, 0, 0},
      {0, 0, 0, 11, 11, 11, 0, 0, 0, 12}, {0, 0, 13, 0, 0, 0, 14, 14, 14, 0}};
  std::vector<std::vector<int>> res = img;
  marking(&img, &res);
  ASSERT_EQ(expected, res);
}
TEST(marking, 7x12) {
  std::vector<std::vector<int>> img = {{1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0},
                                       {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
                                       {0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
                                       {1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
                                       {0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0},
                                       {0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                                       {1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1}};
  std::vector<std::vector<int>> expected = {
      {1, 0, 2, 2, 2, 0, 0, 0, 3, 3, 0, 0},
      {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 4, 4},
      {0, 5, 0, 0, 0, 6, 0, 0, 7, 0, 0, 0},
      {5, 5, 5, 0, 0, 6, 0, 9, 0, 0, 0, 10},
      {0, 5, 5, 5, 5, 0, 0, 0, 11, 0, 0, 0},
      {0, 5, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0},
      {5, 5, 0, 0, 0, 0, 13, 0, 14, 0, 0, 15}};
  std::vector<std::vector<int>> res = img;
  marking(&img, &res);
  ASSERT_EQ(expected, res);
}
