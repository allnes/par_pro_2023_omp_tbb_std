  // Copyright 2023 Polyackov Lev
#ifndef MODULES_TASK_4_POLYACKOV_L_SHELL_SORT_STD_POLYACKOV_L_SHELL_SORT_STD_H_
#define MODULES_TASK_4_POLYACKOV_L_SHELL_SORT_STD_POLYACKOV_L_SHELL_SORT_STD_H_

#include <random>
#include <vector>
#include <iostream>
#include "../../../3rdparty/unapproved/unapproved.h"

std::vector<int> get_random_vec(int size = 0, unsigned int seed = 0);

std::vector<int> shell_sort_seq(const std::vector<int>& vec);

std::vector<int> simple_merge(const std::vector<int>& first_vec, const std::vector<int>& second_vec);

std::vector<std::vector<int>> simple_separate(const std::vector<int>& vec, int num_of_parts);

std::vector<int> shell_sort_with_simple_merge_seq(const std::vector<int>& vec, int num_of_parts);

std::vector<int> shell_sort_with_simple_merge_std(const std::vector<int>& vec, int num_of_parts);

#endif  // MODULES_TASK_4_POLYACKOV_L_SHELL_SORT_STD_POLYACKOV_L_SHELL_SORT_STD_H_
