// Copyright 2023 me
#include <gtest/gtest.h>

#include "../../../modules/task_2/krolevets_n_jarvis_algorithm/jarvis_algorithm.h"

void fill_vec(std::vector<Point>* vec, uint32_t size) {
  std::set<Point> unique_points;
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<int> dist(0, size << 1);
  while (unique_points.size() != size) {
    unique_points.insert(Point(dist(rng), dist(rng)));
  }
  std::copy(unique_points.begin(), unique_points.end(),
            std::back_inserter(*vec));
  std::shuffle(vec->begin(), vec->end(), rng);
}

void print_vecs(std::vector<Point> a, std::vector<Point> b) {
  std::cout << "First size is " << a.size() << std::endl;
  for (uint64_t i = 0; i < a.size(); ++i) {
    std::cout << a[i].x << " " << a[i].y << std::endl;
  }
  std::cout << "Second size is " << b.size() << std::endl;
  for (uint64_t i = 0; i < b.size(); ++i) {
    std::cout << b[i].x << " " << b[i].y << std::endl;
  }
}

TEST(convex_hull_test, return_empty_vector) {
  std::vector<Point> input;
  auto output = get_convex_hull(input);
  auto output2 = get_convex_hull_omp(input);
  EXPECT_EQ(output.size(), 0);
  EXPECT_EQ(output2.size(), 0);
}

TEST(convex_hull_test, hull_of_three) {
  std::vector<Point> input;
  fill_vec(&input, 3);
  auto output = get_convex_hull(input);
  auto output2 = get_convex_hull_omp(input);
  bool dumb_lint1 = output.size() == output2.size();
  bool dumb_lint2 = output == output2;
  bool dumb_lint3 = output.size() == 3;
  EXPECT_EQ(dumb_lint1, true);
  EXPECT_EQ(dumb_lint2, true);
  EXPECT_EQ(dumb_lint3, true);
}

TEST(convex_hull_test, hull_of_ten) {
  std::vector<Point> input;
  fill_vec(&input, 10);
  auto output = get_convex_hull(input);
  auto output2 = get_convex_hull_omp(input);
  if (output.size() != output2.size()) {
    print_vecs(output, output2);
    print_vecs(input, input);
  }
  bool dumb_lint1 = output.size() == output2.size();
  bool dumb_lint2 = output == output2;
  EXPECT_EQ(dumb_lint1, true);
  EXPECT_EQ(dumb_lint2, true);
}

TEST(convex_hull_test, hull_of_hundred) {
  std::vector<Point> input;
  fill_vec(&input, 100);
  auto output = get_convex_hull(input);
  auto output2 = get_convex_hull_omp(input);
  if (output.size() != output2.size()) {
    print_vecs(output, output2);
  }
  bool dumb_lint1 = output.size() == output2.size();
  bool dumb_lint2 = output == output2;
  EXPECT_EQ(dumb_lint1, true);
  EXPECT_EQ(dumb_lint2, true);
}

TEST(convex_hull_test, hull_of_thousand) {
  std::vector<Point> input;
  fill_vec(&input, 1000);
  auto output = get_convex_hull(input);
  auto output2 = get_convex_hull_omp(input);
  bool dumb_lint1 = output.size() == output2.size();
  bool dumb_lint2 = output == output2;
  EXPECT_EQ(dumb_lint1, true);
  EXPECT_EQ(dumb_lint2, true);
}
