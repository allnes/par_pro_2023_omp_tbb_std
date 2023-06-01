// Copyright 2023 Popov Nikita
#include <gtest/gtest.h>

#include "../../../modules/task_1/popov_n_alg_of_jarvis/alg_of_jarvis.h"

TEST(convex_jarvis_testing, return_empty_vector) {
  std::vector<Point> input;
  input.push_back(Point(1, 0));
  input.push_back(Point(1, 2));
  auto output = get_convex_body(input);
  EXPECT_EQ(output.size(), 0);
}

TEST(convex_jarvis_testing, three_points) {
  std::vector<Point> input;
  input.push_back(Point(1, 0));
  input.push_back(Point(1, 2));
  input.push_back(Point(1, 3));
  auto output = get_convex_body(input);
  std::sort(input.begin(), input.end());
  std::sort(output.begin(), output.end());
  EXPECT_TRUE(output[0] == output[0]);
  EXPECT_TRUE(output[1] == output[1]);
  EXPECT_TRUE(output[2] == output[2]);
}

TEST(convex_jarvis_testing, five_points) {
  std::vector<Point> input;
  input.push_back(Point(-1, 0));
  input.push_back(Point(0, 1));
  input.push_back(Point(0, -1));
  input.push_back(Point(1, 0));
  input.push_back(Point(0, 0));
  auto output = get_convex_body(input);
  std::cout << output.size() << std::endl;
  std::sort(output.begin(), output.end());
  EXPECT_EQ(output.size(), 4);
  EXPECT_TRUE(output[0] == Point(-1, 0));
  EXPECT_TRUE(output[1] == Point(0, -1));
  EXPECT_TRUE(output[2] == Point(0, 1));
  EXPECT_TRUE(output[3] == Point(1, 0));
}

TEST(convex_jarvis_testing, collinear_points) {
  std::vector<Point> input;
  input.push_back(Point(0, 0));
  input.push_back(Point(0, 4));
  input.push_back(Point(4, 0));
  input.push_back(Point(1, 1));
  input.push_back(Point(2, 2));
  auto output = get_convex_body(input);
  std::sort(output.begin(), output.end());
  EXPECT_EQ(output.size(), 3);
  EXPECT_TRUE(output[0] == Point(0, 0));
  EXPECT_TRUE(output[1] == Point(0, 4));
  EXPECT_TRUE(output[2] == Point(4, 0));
}

TEST(convex_jarvis_testing, just_only_collinear_points) {
  std::vector<Point> input;
  input.push_back(Point(0, 0));
  input.push_back(Point(1, 1));
  input.push_back(Point(2, 2));
  input.push_back(Point(3, 3));
  auto output = get_convex_body(input);
  std::sort(output.begin(), output.end());
  EXPECT_EQ(output.size(), 4);
  EXPECT_TRUE(output[0] == Point(0, 0));
  EXPECT_TRUE(output[1] == Point(1, 1));
  EXPECT_TRUE(output[2] == Point(2, 2));
  EXPECT_TRUE(output[3] == Point(3, 3));
}
