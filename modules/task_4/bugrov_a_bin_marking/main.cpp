// Copyright 2023 Bugrov Andrey
#include <gtest/gtest.h>

#include <vector>

#include "../../../modules/task_4/bugrov_a_bin_marking/bin_marking.h"

bool are_matrix_eq(const vector<vector<int>>& a, const vector<vector<int>>& b,
                   int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] != b[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool CheckMarking(int N, const vector<vector<int>>& image,
                  const vector<vector<int>>& etalon) {
  const int k_thread_num = 4;
  vector<vector<int>> marks(N);
  for (int i = 0; i < N; i++) {
    marks[i].resize(N);
  }
  const int k_unnamed = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      marks[i][j] = k_unnamed;
    }
  }
  par_marking(image, N, N, &marks, k_unnamed, k_thread_num);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << marks[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "SHOULD BE:\n";
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << etalon[i][j] << " ";
    }
    std::cout << "\n";
  }
  return are_matrix_eq(marks, etalon, N, N);
}

TEST(bin_marking, can_mark_empty_image) {
  const int n = 499;
  const int k_unnamed = 0;
  vector<vector<int>> image, etalon;
  image.resize(n);
  etalon.resize(n);
  for (int i = 0; i < n; i++) {
    image[i].resize(n);
    etalon[i].resize(n);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      image[i][j] = 1;
      etalon[i][j] = k_unnamed;
    }
  }
  ASSERT_EQ(true, CheckMarking(n, image, etalon));
}
TEST(bin_marking, can_mark_image_with_one_central_component) {
  const int n = 7;
  vector<vector<int>> image = {{1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 0, 0, 1},
                               {1, 1, 0, 0, 0, 1, 1}, {1, 0, 0, 0, 0, 0, 1},
                               {1, 1, 0, 0, 0, 1, 1}, {1, 1, 0, 1, 1, 1, 1},
                               {1, 1, 1, 1, 1, 1, 1}};
  vector<vector<int>> etalon = {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 0},
                                {0, 0, 1, 1, 1, 0, 0}, {0, 1, 1, 1, 1, 1, 0},
                                {0, 0, 1, 1, 1, 0, 0}, {0, 0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0}};
  ASSERT_EQ(true, CheckMarking(n, image, etalon));
}

//////////////////////////////////////////////////////////////////////
TEST(bin_marking, can_mark_image_with_many_central_components) {
  const int n = 6;
  vector<vector<int>> image = {{1, 1, 1, 1, 1, 1}, {1, 1, 0, 1, 0, 1},
                               {1, 0, 0, 1, 0, 1}, {1, 1, 1, 0, 0, 1},
                               {1, 0, 0, 1, 0, 1}, {1, 1, 1, 1, 1, 1}};
  vector<vector<int>> etalon = {{0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 2, 0},
                                {0, 1, 1, 0, 2, 0}, {0, 0, 0, 2, 2, 0},
                                {0, 3, 3, 0, 2, 0}, {0, 0, 0, 0, 0, 0}};
  ASSERT_EQ(true, CheckMarking(n, image, etalon));
}

TEST(bin_marking, can_mark_general_image) {
  const int n = 5;
  vector<vector<int>> image = {{
                                   1,
                                   1,
                                   1,
                                   0,
                                   1,
                               },
                               {
                                   0,
                                   0,
                                   1,
                                   0,
                                   0,
                               },
                               {
                                   1,
                                   0,
                                   1,
                                   1,
                                   1,
                               },
                               {
                                   0,
                                   1,
                                   0,
                                   0,
                                   1,
                               },
                               {1, 1, 0, 1, 0}};
  const vector<vector<int>> etalon = {{0, 0, 0, 1, 0},
                                      {2, 2, 0, 1, 1},
                                      {0, 2, 0, 0, 0},
                                      {3, 0, 4, 4, 0},
                                      {0, 0, 4, 0, 5}};
  ASSERT_EQ(true, CheckMarking(n, image, etalon));
}

TEST(bin_marking, can_mark_staggered_image) {
  const int n = 8;
  vector<vector<int>> image = {
      {1, 0, 1, 0, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1, 0, 1},
      {1, 0, 1, 0, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1, 0, 1},
      {1, 0, 1, 0, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1, 0, 1},
      {1, 0, 1, 0, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1, 0, 1},
  };
  const vector<vector<int>> etalon = {
      {0, 1, 0, 2, 0, 3, 0, 4},     {5, 0, 6, 0, 7, 0, 8, 0},
      {0, 9, 0, 10, 0, 11, 0, 12},  {13, 0, 14, 0, 15, 0, 16, 0},
      {0, 17, 0, 18, 0, 19, 0, 20}, {21, 0, 22, 0, 23, 0, 24, 0},
      {0, 25, 0, 26, 0, 27, 0, 28}, {29, 0, 30, 0, 31, 0, 32, 0},
  };
  ASSERT_EQ(true, CheckMarking(n, image, etalon));
}
