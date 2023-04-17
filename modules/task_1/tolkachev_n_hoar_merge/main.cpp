// Copyright 2023 Tolkachev
#include <gtest/gtest.h>
#include "./hoar_merge.h"

TEST(Hoar, Test_1_Hoar_10) {
  int n = 10;
  std::vector<int> vec = Getvec(n);
  std::vector<int> vec2 = vec;
  std::sort(vec2.begin(), vec2.end());
  HoarSort(&vec, 0, vec.size() - 1);
  ASSERT_EQ(vec, vec2);
}

TEST(Hoar, Test_2_Hoar_15) {
  int n = 15;
  std::vector<int> vec = Getvec(n);
  std::vector<int> vec2 = vec;
  std::sort(vec2.begin(), vec2.end());
  HoarSort(&vec, 0, vec.size() - 1);
  ASSERT_EQ(vec, vec2);
}

TEST(Merge, Test_3_Merge_10) {
  int n = 10;
  std::vector<int> vec = Getvec(n);
  std::vector<int> vec2 = vec;
  std::vector<int> vec3 = vec;
  std::sort(vec2.begin(), vec2.end());
  MergeSort(&vec, &vec3, 0, vec.size() - 1);
  ASSERT_EQ(vec, vec2);
}

TEST(Merge, Test_4_Merge_20) {
  int n = 20;
  std::vector<int> vec = Getvec(n);
  std::vector<int> vec2 = vec;
  std::vector<int> vec3 = vec;
  std::sort(vec2.begin(), vec2.end());
  MergeSort(&vec, &vec3, 0, vec.size() - 1);
  ASSERT_EQ(vec, vec2);
}

TEST(Merge, Test_5_Merge_50) {
  int n = 50;
  std::vector<int> vec = Getvec(n);
  std::vector<int> vec2 = vec;
  std::vector<int> vec3 = vec;
  std::sort(vec2.begin(), vec2.end());
  MergeSort(&vec, &vec3, 0, vec.size() - 1);
  ASSERT_EQ(vec, vec2);
}
