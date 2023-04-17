  // Copyright 2023 Polyackov Lev
#include <gtest/gtest.h>
#include <vector>
  // #include <chrono>
#include <algorithm>
#include "../../modules/task_3/polyackov_l_shell_sort_tbb/polyackov_l_shell_sort_tbb.h"

const int num_of_elems = 1000;
const int num_of_parts = 4;
const int random_gen_seed = 0;

/* void PrintVec(std::vector<int> tmp) {
  for (auto& Elem : tmp) {
    std::cout << Elem << ' ';
  }
  std::cout << '\n';
}*/

TEST(TBB, Test_Sorted_Array) {
  std::vector<int> tmp = get_random_vec(num_of_elems, random_gen_seed);
  std::sort(tmp.begin(), tmp.end());
  std::vector<int> res = shell_sort_with_simple_merge_tbb(tmp, num_of_parts);
  for (int i = 1; i < res.size(); i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

TEST(TBB, Test_Reverse_Sorted_Array) {
  std::vector<int> tmp = get_random_vec(num_of_elems, random_gen_seed);
  std::sort(tmp.rbegin(), tmp.rend());  // reverse iterators
  std::vector<int> res = shell_sort_with_simple_merge_tbb(tmp, num_of_parts);
  for (int i = 1; i < res.size(); i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

TEST(TBB, Test_Partially_Sorted_Array) {
  std::vector<int> tmp = get_random_vec(num_of_elems, random_gen_seed);
  int delta = 3;  // delta * 2 elements will be sorted in the middle of the array
  std::sort(tmp.begin() + num_of_elems / 2 - delta, tmp.begin() + num_of_elems / 2 + delta);
  std::vector<int> res = shell_sort_with_simple_merge_tbb(tmp, num_of_parts);
  for (int i = 1; i < res.size(); i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

TEST(TBB, Test_Array_With_Repeating_Elements) {
  std::vector<int> tmp = get_random_vec(num_of_elems, random_gen_seed);
  int delta = 3;  // delta * 2 elements will be changed in the middle of the array
  for (int i = num_of_elems / 2 - delta; i < num_of_elems / 2; i++) {
    tmp[i] = tmp[i - 1];
  }
  for (int i = num_of_elems / 2 + delta; i > num_of_elems / 2; i--) {
    tmp[i] = tmp[i + 1];
  }
  std::vector<int> res = shell_sort_with_simple_merge_tbb(tmp, num_of_parts);
  for (int i = 1; i < res.size(); i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

TEST(TBB, Test_Array_Whose_Values_Are_All_The_Same) {
  std::vector<int> tmp(num_of_elems, 42);
  std::vector<int> res = shell_sort_with_simple_merge_tbb(tmp, num_of_parts);
  for (int i = 1; i < res.size(); i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

int main(int argc, char **argv) {
  /* std::vector<int> tmp1 = get_random_vec(num_of_elems, random_gen_seed);
  std::vector<int> tmp2 = get_random_vec(num_of_elems, random_gen_seed);

  auto start1 = std::chrono::high_resolution_clock::now();
  std::vector<int> res1 = shell_sort_with_simple_merge_tbb(tmp1, num_of_parts);
  auto stop1 = std::chrono::high_resolution_clock::now();
  auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

  auto start2 = std::chrono::high_resolution_clock::now();
  std::vector<int> res2 = shell_sort_with_simple_merge_tbb(tmp2, num_of_parts);
  auto stop2 = std::chrono::high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

  std::cout << "duration_seq: " << duration1.count() << '\n';
  std::cout << "duration_tbb: " << duration2.count() << '\n';*/
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
